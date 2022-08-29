#include <iostream>
#include <vector>
#include <cstdlib> //rand
#include <ctime> //time
#include <cmath> //round
using namespace std;

#define DECK 6

///////////////////////////////////////////////////
class gamer {
private:
	int holdCard;
public:
	vector<int> myCard;
	int cardSum1;
	int cardSum2;
	int resultSum;

	gamer() {
		holdCard = 0;
		cardSum1 = 0;
		cardSum2 = 0;
		myCard.clear();
	}
	~gamer() {
		vector<int>().swap(myCard);
	}
	void receiveCard(int card); // new card -> hold
	int openCard(void); //hold -> vector
	int SumofNum(void); //vector -> cardSum //return -1 when bust
	void resetCard(void) {//clear vector
		myCard.clear();
	}

	virtual int HitStatus(void) = 0; 
	// [HIT] return 1, [STAND] return 0, [BUST] return -1 //virtual function
};

void gamer::receiveCard(int Card) {
	holdCard = Card;
}

int gamer::openCard(void) {
	int temp = holdCard;
	if (temp) {
		myCard.push_back(temp);
		holdCard = 0;
	}
	return temp;
}

int gamer::SumofNum(void) {
	int temp = 0;
	cardSum1 = 0; cardSum2 = 0;
	for (int i = 0; i < myCard.size(); i++) {
		if (myCard[i] > 9) temp += 10;
		else if (myCard[i] == 1) {
			if (cardSum2 == 0) { cardSum1 += 1; cardSum2 += 11; }
			else { cardSum1 += 1; cardSum2 += 1; }
		}
		else temp += myCard[i];
	}
	cardSum1 += temp;
	if (cardSum2) cardSum2 += temp;

	if (cardSum1 > 21) return -1; //bust
	else return 0;
}


///////////////////////////////////////////////////
class betting {
private:
	int coin;
public:
	int bet;
	int winCount;
	int loseCount;

	betting() {
		winCount = 0;
		loseCount = 0;
		coin = 100000;
		bet = 100;
	}
	void betCoin(void);
	void betCoin(int);
	int getCoin(void) { return coin; }
	void setCoin(void) { coin = 100000; }
	void receiveCoin(int isWin);
};

void betting::betCoin(void) {
	coin -= bet;
}

void betting::betCoin(int count) {
	bet = count;
	coin -= bet;
}

void betting::receiveCoin(int isWin) {
	if (isWin == 2)  // black jack
		coin += (bet * 2.5);
	else if (isWin == 1) // win
		coin += (bet * 2);
	else if (isWin == 0) //draw
		coin += bet;

	if (isWin > 0) winCount++;
	if (isWin < 0) loseCount++;
}

///////////////////////////////////////////////////

class card {
private:
	int cardArr[14];
public:
	int usedCard;
	card() {
		srand(time(NULL));
		rand(); // [오류] 첫 번째 난수가 특정 수로 고정됨
		usedCard = 0;
		cardArr[0] = DECK * 4 * 13;
		Shuffle();
	}
	void Shuffle(void);
	int getCard(void);
};

void card::Shuffle(void) {
	for (int i = 1; i < 14; i++)
		cardArr[i] = DECK * 4;
	usedCard = 0;
}

int card::getCard(void) {
	int temp = (rand() * 13) / (RAND_MAX + 1) + 1; //1~13
	while (cardArr[temp] < 1) temp = (rand() * 13) / (RAND_MAX + 1) + 1;
	cardArr[temp]--;
	usedCard++;
	return temp;
}

///////////////////////////////////////////////////

class dealer : public gamer {
private:
public:
	virtual int HitStatus(void);
	int isWin(int playerSum, int playerCard);
};

int dealer::HitStatus(void) {
	if ((cardSum2) && (cardSum2 < 17)) return 1;	// [hit1] ~ 16 with ACE(11)
	else if ((cardSum2) && (cardSum2 < 22)) {		// [stand] 17 ~ 21 with ACE(11)
		resultSum = cardSum2;
		return 0;
	}
	else if (cardSum1 < 17)	 return 1;				// [hit2] ~ 16 (no 11ACE)
	else if (cardSum1 < 22) {						// [stand] 17 ~ 21 (NO 11ACE)
		resultSum = cardSum1;
		return 0;
	}
	else {											// [bust] 22 ~
		resultSum = cardSum1;
		return -1;
	}
}

int dealer::isWin(int playerSum, int playerCard) { //[black jack:2] [win:1] [draw: 0] [lose: -1]
	if (resultSum > 21) { //dealer bust
		if (playerSum > 21) return -1; // player bust
		else return 1;
	}
	else if (playerSum > 21) return -1; // player bust
	else if (resultSum == playerSum) return 0; // draw;
	else if ((playerSum == 21) && (playerCard == 2)) return 2; //black jack
	else if (resultSum < playerSum) return 1; //player win;
	else return -1; // player lose
}

///////////////////////////////////////////////////

class player1 : public gamer, public betting {
private:
	int countArr[14] = { 0, };
	float dealerArr[6] = { 0, }; // [0]17, [1]18, [2]19, [3]20, [4]21, [5]BUST 발생확률
	float nextCardArr[14] = { 0, };
public:
	void predictDealer(int dealerCard);
	void predictDealer_sub(int dealerCard, float prob, int* count);
	void predictNextCard(void);
	void countCard(int card);
	int predictWinner(int dealerSum, int playerSum, int playerCard);
	virtual int HitStatus(void);
	void clearCountArr(void) {
		for (int i = 0; i < 14; i++) countArr[i] = 0;
	}
	void clearPredictArr(void) {
		for (int i = 0; i < 6; i++) dealerArr[i] = 0;
		for (int i = 0; i < 14; i++) nextCardArr[i] = 0;
	}
};

void player1::countCard(int card) {
	countArr[card]++;
	countArr[0]++;
}

void player1::predictDealer(int dealerCard) {
	int remainArr[14];
	remainArr[0] = DECK * 4 * 13 - countArr[0];
	for (int i = 1; i < 14; i++) remainArr[i] = DECK * 4 - countArr[i];
	for (int i = 0; i < 6; i++) dealerArr[i] = 0;

	if (dealerCard == 1) predictDealer_sub(11, 1, remainArr);		//ACE(11)
	else if (dealerCard > 9) predictDealer_sub(10, 1, remainArr);
	else predictDealer_sub(dealerCard, 1, remainArr);

	return;
}

void player1::predictDealer_sub(int dealerCard, float prob, int* remain) {
	int temp;
	int arr[14] = { 0, };
	float ptemp;

	for (int i = 1; i < 14; i++) { // 다음 카드의 수가 i인 경우
		if (remain[i] == 0)  continue;//해당 카드가 더이상 없음
		for (int j = 0; j < 14; j++) arr[j] = remain[j];
		temp = dealerCard; ptemp = prob;

		if (i == 1) {					// 현재 가정에서 예상값
			if (temp < 11) temp += 11;
			else temp += 1;
		}
		else if (i > 9) temp += 10;
		else temp += i;
		ptemp *= ((float)remain[i] / remain[0]); //현재 가정에서 확률

		if (temp < 17) { // 한번 더 뽑음
			arr[i]--; arr[0]--;			// 다음 시행에서 덱에 남은 카드
			predictDealer_sub(temp, ptemp, arr); //재귀호출
		}
		else {//prob값 pArr에 저장
			if (temp > 21) dealerArr[5] += ptemp; //bust
			else  dealerArr[temp - 17] += ptemp;
		}
	}
}

void player1::predictNextCard(void) { //hit할 경우 다음 카드가 i일 확률
	int remainCard = DECK * 4 * 13 - countArr[0];
	for (int i = 1; i < 14; i++) {
		nextCardArr[i] = ((float)(DECK * 4 - countArr[i]) / remainCard); //현재 가정에서 확률
	}
}

int player1::predictWinner(int dealerSum, int playerSum, int playerCard) { //[black jack:2] [win:1] [draw: 0] [lose: -1]
	if (dealerSum > 21) { //dealer bust
		if (playerSum > 21) return -1; // player bust
		else return 1;
	}
	else if (playerSum > 21) return -1; // player bust
	else if (dealerSum == playerSum) return 0; // draw;
	else if ((playerSum == 21) && (playerCard == 2)) return 2; //black jack
	else if (dealerSum < playerSum) return 1; //player win;
	else return -1; // player lose
}

int player1::HitStatus(void) {
	float pHit = 0, pStand = 0, pBust = 0;
	int temp, w1, w2;

	if (cardSum1 > 21) { // bust
		resultSum = cardSum1;
		return -1;
	}
	else if (cardSum1 == 21) { //21, stand
		resultSum = cardSum1;
		return 0;
	}
	else if (cardSum2 == 21) { //21, stand
		resultSum = cardSum2;
		return 0;
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 14; j++) {
			if (j == 0) temp = myCard.size();
			else temp = myCard.size() + 1;

			if(j > 9) w1 = predictWinner(i + 17, 10 + cardSum1, temp);
			else w1 = predictWinner(i + 17, j + cardSum1, temp);

			if (cardSum2) w2 = predictWinner(i + 17, j + cardSum2, temp);
			else if (j == 1) w2 = predictWinner(i + 17, 11 + cardSum1, temp); // ACE(11)
			else if (j > 9) w2 = predictWinner(i + 17, 10 + cardSum1, temp);
			else w2 = -2; //no use

			if ((w1 > -1) || (w2 > -1)) { // win or draw
				if (j == 0) pStand += dealerArr[i]; //stand해서 이기거나 비김
				else pHit += dealerArr[i] * nextCardArr[j]; //hit 해서 이기거나 비김
			}
		}
	}

	for (int i = 1; i < 14; i++) {
		if ((i > 9) && (10 + cardSum1 > 21)) pBust += nextCardArr[j]; //hit해서 bust
		else if (i + cardSum1 > 21) pBust += nextCardArr[j];
	}

	if (pHit > pStand) {
		return 1; //[HIT]
	}
	else { //[STAND]
		resultSum = (w1 >= w2) ? cardSum1 : cardSum2;
		return 0;
	}
}

///////////////////////////////////////////////////
class player2 : public gamer, public betting {
private:
public:
	virtual int HitStatus(void);
};

int player2::HitStatus(void) { //dealer's rule
	if ((cardSum2) && (cardSum2 < 17)) return 1;	// [hit1] ~ 16 with ACE(11)
	else if ((cardSum2) && (cardSum2 < 22)) {		// [stand] 17 ~ 21 with ACE(11)
		resultSum = cardSum2;
		return 0;
	}
	else if (cardSum1 < 17)	 return 1;				// [hit2] ~ 16 (no 11)
	else if (cardSum1 < 22) {						// [stand] 17 ~ 21 (NO 11)
		resultSum = cardSum1;
		return 0;
	}
	else {											// [bust] 22 ~
		resultSum = cardSum1;
		return -1;
	}
}

///////////////////////////////////////////////////

class blackJack {
private:
	card c;
	dealer d;
	player1 p1;
	player2 p2;

	int n;
	int gameNo = 0;
	char pRes = 'n';
public:
	int getw1(void) { return p1.winCount; }
	int getw2(void) { return p2.winCount; }
	int getn(void) { return n; }

	void setLoopCount(void) {
		cout << "Play Game: ";
		cin >> n;
		cout << "print each result (y/n): ";
		cin >> pRes;
	}
	void playGame(void);
	void printResult(void);

	int playGame_sub(void);
	void setCard(void);
};

void blackJack::playGame(void) {
	int winner = 0;
	p1.winCount = 0; p2.winCount = 0;
	p1.loseCount = 0; p2.loseCount = 0;
	p1.setCoin(); p2.setCoin();

	for (int i = 0; i < n; i++) {
		winner = playGame_sub();
		if ((pRes == 'y') || (pRes == 'Y')) { //print each game result
			cout << "\n";
			if (winner % 2) cout << "p1 win!\t";
			if (winner > 1) cout << "p2 win!\t";
			cout << endl << "**************\t"
				<< "p1's coin: " << p1.getCoin()
				<< "\tp2's coin: " << p2.getCoin() << endl << endl;
		}
	}
}

// [0] no winner, [1] p1 win, [2] p2 win, [3] p1,p2 win
int blackJack::playGame_sub(void) {
	int winner = 0;

	if((pRes == 'y')||(pRes == 'Y')) cout << endl << "*** GAME "<<++gameNo<<" ***\t";

	//1. shuffle
	if (c.usedCard >= DECK * 4 * 13 * 0.8) { 
		c.Shuffle();
		p1.clearCountArr();
	}

	//2. setCard
	setCard(); 
	p1.betCoin();
	p2.betCoin();

	//	3. p1 play
	p1.SumofNum();
	p1.predictDealer(d.myCard[0]);
	p1.predictNextCard();

	while (p1.HitStatus() > 0) {
		p1.receiveCard(c.getCard());
		p1.openCard(); p1.countCard(p1.myCard.back());

		p1.SumofNum();
		p1.predictDealer(d.myCard[0]);
		p1.predictNextCard();
	};

	// 	4. p2 play
	p2.SumofNum();
	while (p2.HitStatus() > 0) {
		p2.receiveCard(c.getCard());
		p2.openCard(); p1.countCard(p2.myCard.back());

		p2.SumofNum();
	};

	// 	5. d
	d.openCard(); p1.countCard(d.myCard.back());
	d.SumofNum();
	while (d.HitStatus() > 0) {
		d.receiveCard(c.getCard());
		d.openCard(); p1.countCard(d.myCard.back());

		d.SumofNum();
	}

	// 	6. 승패판정
	int w1, w2;

	w1 = d.isWin(p1.resultSum, p1.myCard.size());
	w2 = d.isWin(p2.resultSum, p2.myCard.size());

	if (w1 > 0) winner += 1;
	if (w2 > 0) winner += 2;

	if ((pRes == 'y') || (pRes == 'Y'))
		cout << "p1[" << p1.resultSum << "]  " << "p2[" << p2.resultSum << "]  "
		<< "d[" << d.resultSum << "]\t";

	// 	7. 돈받기
	p1.receiveCoin(w1);
	p2.receiveCoin(w2);

	// 	8. 초기화
	d.resetCard();
	p1.resetCard(); p1.clearPredictArr();
	p2.resetCard();

	return winner;
}

void blackJack::setCard(void) {
	d.receiveCard(c.getCard()); d.openCard(); p1.countCard(d.myCard.back());
	p1.receiveCard(c.getCard()); p1.openCard(); p1.countCard(p1.myCard.back());
	p2.receiveCard(c.getCard()); p2.openCard(); p1.countCard(p2.myCard.back());

	d.receiveCard(c.getCard()); // hold card
	p1.receiveCard(c.getCard()); p1.openCard(); p1.countCard(p1.myCard.back());
	p2.receiveCard(c.getCard()); p2.openCard(); p1.countCard(p2.myCard.back());
}

void blackJack::printResult(void) {
	cout << endl << "<< Player1 >>" << endl;
	cout << "승리: " << p1.winCount 
		<< " 무승부: "<<n-p1.winCount - p1.loseCount
		<<" 패배: " << p1.loseCount << endl;
	cout << "money: " << p1.getCoin() << endl << endl;

	cout << "<< Player2 >>" << endl;
	cout << "승리: " << p2.winCount
		<< " 무승부: " << n - p2.winCount - p2.loseCount
		<< " 패배: " << p2.loseCount << endl;
	cout << "money: " << p2.getCoin() << endl << endl;

}

///////////////////////////////////////////////////

int main(void) {
	blackJack b;
	b.setLoopCount();
	b.playGame();
	b.printResult();
	/* 여러 번 실행
	float w1=0, w2=0;
	for (int i = 0; i < 1000; i++) {
		b.playGame();
		//b.printResult();

		w1 += b.getw1();
		w2 += b.getw2();
	}
	w1 /= 1000; w2 /= 1000;
	cout <<endl<< b.getn()<<"회 게임 <1000번 반복>" << endl;
	cout << "p1 평균 승률:" << w1 << endl <<"p2 평균 승률: "<< w2 << endl;
	*/

	return 0;
}