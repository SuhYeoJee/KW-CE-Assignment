# list03.py
# 작성자: 2019202009 서여지
# 실습 6.리스트
# 제출일: 2019.04.10

'''
# 1. 친구 명단을 관리하는 프로그램

FL = []

while True :
    print("\n"); print("-"*20)
    print("""
    1. 친구 목록 출력
    2. 친구 추가
    3. 친구 삭제
    4. 이름 변경
    5. 종료
    """)
    menu = input("메뉴를 선택하세요 : ")
    print("\n")

    if menu == "1" :
        print (FL)

    elif menu == "2" :
        FL.append(input("이름을 입력하세요 : "))

    elif menu == "3" :
        name = input("삭제할 이름을 입력하세요: ")
        if not name in FL : # 삭제할 이름이 리스트에 없는경우
            print("이름을 다시 확인해주세요")
        else :
           FL.pop(FL.index(name))

    elif menu == "4" :
        name = input("변경할 이름을 입력하세요: ")
        if not name in FL : # 변경할 이름이 리스트에 없는경우
            print("이름을 다시 확인해주세요")
        else :
           FL[FL.index(name)] = input("새로운 이름을 입력하세요: ")
        
    elif menu == "5" :
        break
    else:
        print("다시 확인해주세요")


'''

# 2. 500바이트 이상인 파일의 목록

import os
import glob
files = glob.glob("*.py")  # 파이썬 파일 목록을 리스트로 저장

print("\n크기가 500바이트가 넘는 파일 목록은 :")

for i in files:
    size = os.path.getsize(i)
    if size >= 500 :
        print(f"{i:>20} : {size:<7}")
