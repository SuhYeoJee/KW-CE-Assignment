#pragma once

class Exchange
{ //�θ�Ŭ����
private:
	double original; // ȯ���� ��
	char* from; // from -> to
	int multiply = 1; //���ؼ� ȯ���ϴ� ��� (KRW)
	double denominator = 1; //����� ȯ���ϴ� ���
public:
	Exchange(double _original, char* _from) {
		original = _original; from = _from;
	}
	double GetOriginal(void) { return original; }
	char* GetFrom(void) { return from; }
	void SetMulti(int _multi) { multiply = _multi; return; }
	void SetDenomi(float _denomi) { denominator = _denomi; return; }
	double m_result(void) { return (GetOriginal() * multiply); }
	double d_result(void) { return (GetOriginal() / denominator); }
};

class ToKRW : public Exchange
{
public:
	ToKRW(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetMulti(void) { // ȯ���� �� ���ϴ� �� ����
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetMulti(1);
		else if (!strcmp(GetFrom(), "USD"))
			Exchange::SetMulti(1200);
		else if (!strcmp(GetFrom(), "JPY"))
			Exchange::SetMulti(11);
		else if (!strcmp(GetFrom(), "EUR"))
			Exchange::SetMulti(1300);
		else if (!strcmp(GetFrom(), "CNY"))
			Exchange::SetMulti(170);
		else //[����]
			Exchange::SetMulti(-1);
	}
	double GetResult(void) { // ��� ����
		SetMulti();
		return m_result();
	}
};

class ToUSD : public Exchange
{
public:
	ToUSD(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // ȯ���� �� ������ �� ����
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(1200);
		else //[����]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// ��� ����
		SetDenomi();
		return d_result();
	}
};

class ToJPY : public Exchange
{
public:
	ToJPY(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // ȯ���� �� ������ �� ����
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(11);
		else //[����]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// ��� ����
		SetDenomi();
		return d_result();
	}
};

class ToEUR : public Exchange
{
public:
	ToEUR(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // ȯ���� �� ������ �� ����
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(1300);
		else //[����]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// ��� ����
		SetDenomi();
		return d_result();
	}
};


class ToCNY : public Exchange
{
public:
	ToCNY(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // ȯ���� �� ������ �� ����
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(170);
		else //[����]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// ��� ����
		SetDenomi();
		return d_result();
	}
};