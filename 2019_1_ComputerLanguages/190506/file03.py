# file03.py
# 연락처 관리 프로그램
# 학번 / 윤소정
# 2019. 5. 

import os
import pickle

menu = 0
filename = 'myFriends.dat'

if os.path.isfile(filename) :
    f = open(filename, 'rb')
    friends = pickle.load(f)
    f.close()
else :
    friends = {}

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
        print('\n**친구 목록**\n', friends, '\n')
        
    elif menu == '2' :
        name = input('\n이름을 입력하세요 : ')
        if name in friends :
            print('이미 있는 친구 입니다.')
        else :
            phone = input('전화번호를 입력하세요 : ')
            friends[name] = phone
            
    elif menu == '3' :
        del_name = input('\n삭제할 친구 이름을 입력하세요 : ')
        if del_name in friends :
            del friends[del_name]
        else :
            print('목록에 없는 친구입니다')
            
    elif menu == '4' :
        mod_name = input('\n변경할 이름을 입력하세요 : ')
        if mod_name in friends :
            phone = input('새 전화번호를 입력하세요 : ')
            friends[mod_name] = phone
        else :
            print('목록에 없는 친구입니다')
            
    elif menu == '5' :
        f = open(filename, 'wb')
        pickle.dump(friends, f)
        f.close()
        print('프로그램을 종료합니다...')
        break
    
    else :
        print('1-5 사이의 값을 입력하세요.\n')


        
