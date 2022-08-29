
// MFCApplicationDlg.cpp: 구현 파일
//

#include <fstream>
#include <string>
#include "pch.h"
#include "framework.h"
#include "MFCApplication.h"
#include "MFCApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


void CMFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
HCURSOR CMFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
CMFCApplicationDlg::CMFCApplicationDlg(CWnd* pParent)
	: CDialogEx(IDD_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	board_x1 = 0;
	board_x2 = 0;
	board_y1 = 0;
	board_y2 = 0;
	logNum = 0;
}
void CMFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CMFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_OUTPUT_COLORNUM, &CMFCApplicationDlg::OnOutputColornum)
	ON_COMMAND(ID_OUTPUT_NUMBER, &CMFCApplicationDlg::OnOutputNumber)
END_MESSAGE_MAP()

BOOL CMFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	SetWindowText(_T("2048 MFC PROJECT"));

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);		
	SetIcon(m_hIcon, FALSE);	

	MoveWindow(0, 0, 300, 350);
	logNum = 0;
	printNum = 0;
	m_Board = nullptr;
	iscolor = true;
	ofstream fout("log.txt");
	fout << logNum++ << ". start" << endl;
	fout.close();
	
	StartGame();

	return TRUE;
}

void CMFCApplicationDlg::OnPaint() 
{
	CPaintDC dc(this);
	CBrush brush;
	CRect rect;
	GetClientRect(&rect);
	dc.SetBkMode(TRANSPARENT);
	
	wchar_t* str=nullptr;
	int b_size = 64;

	for (int i = 0; i < 4; i++) {
		int x = ((rect.Width() + 1) / 2) - b_size * 2;
		int y = ((rect.Height() + 1) / 2) - b_size * 2;
		for (int j = 0; j < 4; j++) {
			int num = m_Board->gotoxy(i, j)->GetNum();

			if (num == 0) { brush.CreateSolidBrush(RGB(255, 255, 255)); str = nullptr; }
			else if (num == 2) { brush.CreateSolidBrush(RGB(255, 255, 0)); str = L"2";}
			else if (num == 4) { brush.CreateSolidBrush(RGB(255, 127, 0)); str = L"4";}
			else if (num == 8) { brush.CreateSolidBrush(RGB(0, 255, 0)); str = L"8";}
			else if (num == 16) { brush.CreateSolidBrush(RGB(0, 0, 255)); str = L"16";}
			else if (num == 32) { brush.CreateSolidBrush(RGB(166, 166, 166)); str = L"32";}
			else if (num == 64) { brush.CreateSolidBrush(RGB(255, 0, 255)); str = L"64";}
			else if (num == 128) { brush.CreateSolidBrush(RGB(0, 255, 255)); str = L"128";}
			else if (num == 256) { brush.CreateSolidBrush(RGB(128, 0, 128)); str = L"256";}
			else if (num == 512) { brush.CreateSolidBrush(RGB(112, 48, 160)); str = L"512";}
			else if (num == 1024) { brush.CreateSolidBrush(RGB(207, 110, 54)); str = L"1024";}
			else if (num == 2048) { brush.CreateSolidBrush(RGB(255, 0, 0)); str = L"2048";}
				
			if(iscolor) dc.SelectObject(brush);
			dc.Rectangle(x + b_size * j, y+ b_size * i, x + b_size * (j+1), y + b_size * (i+1) );
			dc.SetTextAlign(TA_CENTER);
			dc.TextOutW(x + b_size * j + 32, y + b_size * i + 25, str);
			if ((i == 0) && (j == 0)) {
				board_x1 = x + b_size * j;
				board_y1 = y + b_size * i;
			}
			else if ((i == 3) && (j == 3)) {
				board_x2 = x + b_size * (j+1);
				board_y2 = y + b_size * (i+1);
			}
			brush.DeleteObject();
		}
	}

	ofstream fout("log.txt", ios::app);
	if (logNum != printNum) { m_Board->print(); printNum++; }
	fout.close();
}
void CMFCApplicationDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	ofstream fout("log.txt",ios::app);
	switch (nChar)
	{
	case VK_UP: //UP
		fout << logNum++ << ". Key_Up" << endl;
		if ((!this->m_Board->Up()) && (this->m_Board->IsFull()))
			break;
		this->m_Board->random2();
		break;
	case VK_DOWN: //DOWN
		fout << logNum++ << ". Key_Down" << endl;
		if ((!this->m_Board->Down()) && (this->m_Board->IsFull()))
			break;
		this->m_Board->random2();
		break;
	case VK_LEFT: //Left
		fout << logNum++ << ". Key_Left" << endl;
		if ((!this->m_Board->Left()) && (this->m_Board->IsFull()))
			break;
		this->m_Board->random2();
		break;
	case VK_RIGHT: //RIGHT
		fout << logNum++ << ". Key_Right" << endl;
		if ((!this->m_Board->Right()) && (this->m_Board->IsFull()))
			break;
		this->m_Board->random2();
		break;
	}
	Invalidate();
	int win;
	if ((win = m_Board->IsEnd()) != 0)
	{
		int select = 0;
		if (win == 1)//승
			select = MessageBox(L"Continue ?", L"WIN!!", MB_ICONWARNING | MB_YESNO);
		else if (win == 2) //패
			select = MessageBox(L"Do you want new game ?", L"LOSE!!", MB_ICONSTOP | MB_YESNO);
		if (select == IDYES) {
			StartGame();
			fout << logNum++ << ". start" << endl;
			Invalidate();
		}
		else {
			fout << "end." << endl;
			fout.close();
			delete m_Board;
			this->DestroyWindow();
		}
			
	}
	fout.close();
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}
void CMFCApplicationDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	start_point = point;
	SetCapture();
	CDialogEx::OnLButtonDown(nFlags, point);

}
void CMFCApplicationDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect(board_x1, board_y1, board_x2, board_y2);
	if (rect.PtInRect(start_point)&&rect.PtInRect(point)) {
		ofstream fout("log.txt", ios::app);
		end_point = point;
		if ((start_point.x - end_point.x) > 0) { // <-
			fout << logNum++<<". Mouse_Right_to_Left" << endl;
			m_Board->TurnCCW();
		}
		else if ((start_point.x - end_point.x) < 0) {  // ->
			fout<<logNum++ << ". Mouse_Left_to_Right" << endl;
			m_Board->TurnCW();
		}
		Invalidate();
		ReleaseCapture();

		fout.close();
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCApplicationDlg::OnOutputColornum()
{
	iscolor = true;
	CMenu* cmenu = GetMenu();
	cmenu->CheckMenuItem(ID_OUTPUT_COLORNUM, MF_CHECKED);
	cmenu->CheckMenuItem(ID_OUTPUT_NUMBER, MF_UNCHECKED);
	Invalidate();
}
void CMFCApplicationDlg::OnOutputNumber()
{
	iscolor = false;
	CMenu* cmenu = GetMenu();
	cmenu->CheckMenuItem(ID_OUTPUT_COLORNUM, MF_UNCHECKED);
	cmenu->CheckMenuItem(ID_OUTPUT_NUMBER, MF_CHECKED);
	Invalidate();
}

void CMFCApplicationDlg::StartGame()
{
	if (m_Board != nullptr)
		delete m_Board;
	m_Board = new MyBoard;
	this->m_Board->random2();
	CMenu* cmenu = GetMenu();
	if (iscolor) {
		cmenu->CheckMenuItem(ID_OUTPUT_COLORNUM, MF_CHECKED);
		cmenu->CheckMenuItem(ID_OUTPUT_NUMBER, MF_UNCHECKED);
	}
	else {
		cmenu->CheckMenuItem(ID_OUTPUT_COLORNUM, MF_UNCHECKED);
		cmenu->CheckMenuItem(ID_OUTPUT_NUMBER, MF_CHECKED);
	}

}
