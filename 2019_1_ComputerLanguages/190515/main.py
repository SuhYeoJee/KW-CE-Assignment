# main.py
#
#
#

import os
import pickle
import login

filename = 'myFriends.dat'

if os.path.isfile(filename) :
    f = open(filename, 'rb')
    friends = pickle.load(f)
    f.close()
else :
    friends = {}

def contact() :
    print('\n\n1. 연락처 관리 프로그램 \n')
    while True :
        print('----------------------------')
        print('1. 연락처 목록 출력')
        print('2. 연락처 추가')
        print('3. 연락처 삭제')
        print('4. 연락처 변경')
        print('5. 종료')

        menu = input('\n메뉴를 선택하세요 : ') 
        
        if menu == '1' :
            print('\n\t**친구 목록**\n', friends, '\n')
            
        elif menu == '2' :
            name = input('\n\t이름을 입력하세요 : ')
            if name in friends :
                print('\t이미 있는 친구 입니다.')
            else :
                phone = input('\t전화번호를 입력하세요 : ')
                friends[name] = phone
                
        elif menu == '3' :
            del_name = input('\n\t삭제할 친구 이름을 입력하세요 : ')
            if del_name in friends :
                del friends[del_name]
            else :
                print('\t목록에 없는 친구입니다')
                
        elif menu == '4' :
            mod_name = input('\n\t변경할 이름을 입력하세요 : ')
            if mod_name in friends :
                phone = input('\t새 전화번호를 입력하세요 : ')
                friends[mod_name] = phone
            else :
                print('\t목록에 없는 친구입니다')
                
        elif menu == '5' :
            f = open(filename, 'wb')
            pickle.dump(friends, f)
            f.close()
            print('\t*** 연락처 관리 프로그램을 종료합니다\n\n')
            break
        
        else :
            print('\n[오류] 1-5 사이의 값을 입력하세요.\n')


def main() :
    while True :
        print('\n\n[1] 회원등록')
        print('[2] 로그인')
        print('[3] 종료\n')

        menu = input('메뉴를 입력하세요 : ')

        if menu == '1' :
            login.registration()
        elif menu == '2' :
            if login.login() :
                contact()
            else :
                break
        elif menu == '3' :
            print('프로그램을 종료합니다')
            break
        else :
            print('입력을 확인하세요')

if __name__ == '__main__' :
    main()
