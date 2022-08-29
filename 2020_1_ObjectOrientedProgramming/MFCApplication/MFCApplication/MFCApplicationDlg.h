#include "Block.h"
#include "Board.h"
// MFCApplicationDlg.h: 헤더 파일
//

#pragma once


// CMFCApplicationDlg 대화 상자
class CMFCApplicationDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplicationDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	MyBoard* m_Board;
	CPoint start_point;
	CPoint end_point;
	bool iscolor;
	void StartGame();
	int board_x1;
	int board_x2;
	int board_y1;
	int board_y2;

	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnOutputColornum();
	afx_msg void OnOutputNumber();
	int logNum;
	int printNum;
};
