#pragma once

class Exchange
{ //부모클래스
private:
	double original; // 환전할 돈
	char* from; // from -> to
	int multiply = 1; //곱해서 환전하는 경우 (KRW)
	double denominator = 1; //나누어서 환전하는 경우
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
	void SetMulti(void) { // 환전할 때 곱하는 수 저장
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
		else //[오류]
			Exchange::SetMulti(-1);
	}
	double GetResult(void) { // 결과 전달
		SetMulti();
		return m_result();
	}
};

class ToUSD : public Exchange
{
public:
	ToUSD(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // 환전할 때 나누는 수 저장
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(1200);
		else //[오류]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// 결과 전달
		SetDenomi();
		return d_result();
	}
};

class ToJPY : public Exchange
{
public:
	ToJPY(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // 환전할 때 나누는 수 저장
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(11);
		else //[오류]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// 결과 전달
		SetDenomi();
		return d_result();
	}
};

class ToEUR : public Exchange
{
public:
	ToEUR(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // 환전할 때 나누는 수 저장
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(1300);
		else //[오류]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// 결과 전달
		SetDenomi();
		return d_result();
	}
};


class ToCNY : public Exchange
{
public:
	ToCNY(double _original, char* _from)
		: Exchange(_original, _from) {}
	void SetDenomi(void) { // 환전할 때 나누는 수 저장
		if (!strcmp(GetFrom(), "KRW"))
			Exchange::SetDenomi(170);
		else //[오류]
			Exchange::SetDenomi(-1);
	}
	double GetResult(void) {// 결과 전달
		SetDenomi();
		return d_result();
	}
};