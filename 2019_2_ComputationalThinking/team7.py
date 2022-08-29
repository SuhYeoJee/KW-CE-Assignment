import sys
from PyQt5.uic import loadUi
from PyQt5.QtWidgets import *

############################################

class MainWindow(QMainWindow):
    price = 0
    total = 0
    result = ''
    name=''
    pri=0
    
############################################

    def pay(self):
        result = QMessageBox.question(self, '결제', f"카드로 결제 합니까?\n결제금액: {str(self.price)}원", QMessageBox.Yes | QMessageBox.No)
        if result == QMessageBox.Yes:
            QMessageBox.about(self, "카드 결제","결제완료")
        else:
            total=self.price
            QMessageBox.about(self,"현금 결제", "idle에서 현금 입력")
            while(total>=0):
                cost=int(input("현금 입력: "))
                total-=cost
            if total<0:
                QMessageBox.about(self, "현금 결제",f"잔돈을 받아주세요.\n  잔돈:{total*(-1)}원")
            QMessageBox.about(self, "현금 결제","결제완료")
                
        self.clear()

    def clear(self):
        self.price=0
        self.result=''
        self.lbl_out.setText(self.result)
        self.lcdprice.display(self.price)
        


############################################
    
    def c_choice(self,name,pri):
        result = QMessageBox.question(self, '사이즈 업', "사이즈업 합니까? \n(+600원)", QMessageBox.Yes| QMessageBox.No)
        if result == QMessageBox.Yes:
            pri+=600
            name+=' [큰 컵]'
        else:
            name+=' [작은 컵]'

        result = QMessageBox.question(self, '샷추가', "샷추가 합니까? \n(1샷 +400원, 2샷 +800원)", QMessageBox.Yes | QMessageBox.No)
        if result == QMessageBox.Yes:
            result2 = QMessageBox.question(self, '샷추가', "1샷만 추가 합니까? \n(1샷 +400원, 2샷 +800원)", QMessageBox.Yes | QMessageBox.No)
            if result2 == QMessageBox.Yes:
                pri+=400
                name+=' [1샷 추가]'
            else:
                pri+=800
                name+=' [2샷 추가]'
                
        result = QMessageBox.question(self, '온도 선택', "따뜻한 커피로 합니까?", QMessageBox.Yes| QMessageBox.No)
        if result == QMessageBox.Yes:
            pri+=600
            name+=' [Hot]'
        else:
            name+=' [Cold]'
            
        self.price+=pri
        pri=str(self.price)
        self.result+=name+'\n'
        self.lbl_out.setText(self.result) #출력
        self.lcdprice.display(self.price)

    def d_choice(self,name,pri):
        result = QMessageBox.question(self, '사이즈 업', "사이즈업 합니까? \n(+600원)", QMessageBox.Yes| QMessageBox.No)
        if result == QMessageBox.Yes:
            pri+=600
            name+=' [큰 컵]'
        else:
            name+=' [작은 컵]'

        result = QMessageBox.question(self, '시럽추가', "시럽추가 합니까? \n(1번 +200원, 2번 +400원)", QMessageBox.Yes | QMessageBox.No)
        if result == QMessageBox.Yes:
            result2 = QMessageBox.question(self, '시럽추가', "1번만 추가 합니까? \n(1번 +200원, 2번 +400원)", QMessageBox.Yes | QMessageBox.No)
            if result2 == QMessageBox.Yes:
                pri+=200
                name+=' [1번 추가]'
            else:
                pri+=400
                name+=' [2번 추가]'
        self.price+=pri
        pri=str(self.price)
        self.result+=name+'\n'
        self.lbl_out.setText(self.result) #출력
        self.lcdprice.display(self.price)


    def a_choice(self,name,pri):
        result = QMessageBox.question(self, '사이즈 업', "사이즈업 합니까? \n(+600원)", QMessageBox.Yes| QMessageBox.No)
        if result == QMessageBox.Yes:
            pri+=600
            name+=' [큰 컵]'
        else:
            name+=' [작은 컵]'
            
        self.price+=pri
        pri=str(self.price)
        self.result+=name+'\n'
        self.lbl_out.setText(self.result) #출력
        self.lcdprice.display(self.price)

############################################

    def __init__(self):
        super().__init__()
        loadUi('vending.ui', self)
        self.Button()

############################################
        
    def Button(self):
        self.menu_c_push_1.clicked.connect(self.c1_clicked)
        self.menu_c_push_2.clicked.connect(self.c2_clicked)
        self.menu_c_push_3.clicked.connect(self.c3_clicked)
        self.menu_c_push_4.clicked.connect(self.c4_clicked)
        self.menu_c_push_5.clicked.connect(self.c5_clicked)
        self.menu_c_push_6.clicked.connect(self.c6_clicked)
        self.menu_c_push_7.clicked.connect(self.c7_clicked)
        self.menu_c_push_8.clicked.connect(self.c8_clicked)

        self.menu_d_push_1.clicked.connect(self.d1_clicked)
        self.menu_d_push_2.clicked.connect(self.d2_clicked)
        self.menu_d_push_3.clicked.connect(self.d3_clicked)
        self.menu_d_push_4.clicked.connect(self.d4_clicked)
        self.menu_d_push_5.clicked.connect(self.d5_clicked)
        self.menu_d_push_6.clicked.connect(self.d6_clicked)
        
        self.menu_a_push_1.clicked.connect(self.a1_clicked)
        self.menu_a_push_2.clicked.connect(self.a2_clicked)
        self.menu_a_push_3.clicked.connect(self.a3_clicked)
        self.menu_a_push_4.clicked.connect(self.a4_clicked)
        self.menu_a_push_5.clicked.connect(self.a5_clicked)
        self.menu_a_push_6.clicked.connect(self.a6_clicked)        

        self.pushButton_pay.clicked.connect(self.pay)
        self.pushButton_clear.clicked.connect(self.clear)       

############################################

    def c1_clicked(self):
        self.c_choice('아메리카노',900)
    def c2_clicked(self):
        self.c_choice('카페라떼',2100)
    def c3_clicked(self):
        self.c_choice('더블모카라떼',2900)
    def c4_clicked(self):
        self.c_choice('바닐라라떼',2300)
    def c5_clicked(self):
        self.c_choice('카페모카',2400)
    def c6_clicked(self):
        self.c_choice('콜드브루(컵)',1700)
    def c7_clicked(self):
        self.c_choice('콜드브루(보틀)',1700)
    def c8_clicked(self):
        self.c_choice('콜드브루라떼',2000)

    def d1_clicked(self):
        self.d_choice('초코위드베리',2900)
    def d2_clicked(self):
        self.d_choice('베리딸기',2800)
    def d3_clicked(self):
        self.d_choice('초코밀크',2300)
    def d4_clicked(self):
        self.d_choice('대만밀크',2400)
    def d5_clicked(self):
        self.d_choice('솔티카라멜밀크',2200)
    def d6_clicked(self):
        self.d_choice('몽키바나나밀크',2200)

    def a1_clicked(self):
        self.a_choice('그린레몬아이스티',2900)
    def a2_clicked(self):
        self.a_choice('레몬패션에이드',2800)
    def a3_clicked(self):
        self.a_choice('자몽에이드',2300)
    def a4_clicked(self):
        self.a_choice('상큼자몽블랙티',2400)
    def a5_clicked(self):
        self.a_choice('블루몬스터',2200)
    def a6_clicked(self):
        self.a_choice('확깨수',2200)

############################################

if __name__ == "__main__":
    app = QApplication(sys.argv)
    MainWindow = MainWindow()
    MainWindow.show()
    app.exec_()
