# login.py
#
#
#

import os
import pickle

login_file = 'member.dat'

def registration() :
    if os.path.isfile(login_file) :
        f = open(login_file, 'rb')
        member = pickle.load(f)
        f.close()
    else :
        member = {}

    inputID = input('\t아이디를 입력하세요 : ')

    if inputID in member :
        print('\t이미 존재하는 아이디입니다')
    else :
        member[inputID] = input('\t비밀번호를 입력하세요 : ')
        print('** 등록되었습니다')
        f = open(login_file, 'wb')
        pickle.dump(member, f)
        f.close()

    

def login() :
    if os.path.isfile(login_file) :
        f = open(login_file, 'rb')
        member = pickle.load(f)
        f.close()
    else :
        member = {}

    for i in range(5) :
        inputID = input('\tID : ')
        inputPW = input('\tPW : ')
        
        if inputID in member and member[inputID] == inputPW :
            print(f'\t환영합니다 {inputID} 님~')
            return True
        else :
            print(f'\t아이디나 비밀번호가 틀렸습니다[{i+1}회 실패]\n')
    else :
        print('\t로그인을 5회 실패하여 더이상 로그인 하실 수 없습니다')
        return False

if __name__ == '__main__' :
    registration()
    login()
