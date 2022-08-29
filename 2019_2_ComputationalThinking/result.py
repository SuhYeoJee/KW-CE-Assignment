import sys
from PyQt5.uic import loadUi
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *


############################################

class MainWindow(QMainWindow):
    price = 0
    total = 0
    result = ''
    final_result = ''

    def __init__(self):
        super().__init__()
        loadUi('vending.ui', self)


############################################
        
class tab_1(QWidget):
    choice_c = ''
    price = 0
    total = 0
    result = ''
    final_result = ''
    btns_c = []  # 커피선택 버튼

    def __init__(self):
        super().__init__()
        loadUi('vending.ui', self)
        
        #음료 선택 버튼
        '''
        self.btns_c = [self.menu_c_push_1, self.menu_c_push_2,
                       self.menu_c_push_3, self.menu_c_push_4,
                       self.menu_c_push_5, self.menu_c_push_6,
                       self.menu_c_push_7, self.menu_c_push_8]
        for btn in self.btns_c:
            btn.clicked.connect(self.choice)
        '''
        self.menu_a_push_1.clicked.connect(self.choice)
        self.menu_d_push_2.clicked.connect(self.choice)

    def choice(self):
        print("def choice(self):")#
        sender = self.sender()
        self.price += int(sender.text())
        self.choice_c += sender.toolTip() + " "  # 선택한 음료
        MainWindow().lbl_out.setText(self.choice_c)  # 선택한 음료 레이블에 표시

############################################

'''
class tab_2(QWidget):
    choice_d = ''
    price = 0
    total = 0
    result = ''
    final_result = ''
    btns_d = []  # 음료선택 버튼

    def __init__(self):
        super().__init__()
        loadUi('vending.ui', self)

        self.btns_d = [self.menu_d_push_1, self.menu_d_push_2, self.menu_d_push_3, self.menu_d_push_4,
                       self.menu_d_push_5, self.menu_d_push_6, self.menu_d_push_7, self.menu_d_push_8]

        for btn in self.btns_d:
            btn.clicked.connect(self.choice)

    def choice(self):
        sender = self.sender()
        self.price += int(sender.text())
        self.choice_c += sender.toolTip() + " "  # 선택한 음료
        MainWindow().lbl_out.setText(self.choice_c)  # 선택한 음료 레이블에 표시


############################################

class tab_3(QTabWidget):
    choice_a = ''
    price = 0
    total = 0
    result = ''
    final_result = ''
    btns_a = []  # 에이드선택 버튼

    def __init__(self):
        super().__init__()
        loadUi('vending.ui', self)

        self.btns_a = [self.menu_a_push_1, self.menu_a_push_2, self.menu_a_push_3, self.menu_a_push_4,
                       self.menu_a_push_5, self.menu_a_push_6, self.menu_a_push_7, self.menu_a_push_8]

        for btn in self.btns_d:
            btn.clicked.connect(self.choice)

    def choice(self):
        sender = self.sender()
        self.price += int(sender.text())
        self.choice_c += sender.toolTip() + " "  # 선택한 음료
        MainWindow().lbl_out.setText(self.choice_c)  # 선택한 음료 레이블에 표시
'''
############################################


if __name__ == "__main__":
    app = QApplication(sys.argv)
    MainWindow = MainWindow()
    MainWindow.show()
    app.exec_()
