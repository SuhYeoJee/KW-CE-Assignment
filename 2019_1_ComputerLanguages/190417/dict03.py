# dict03.py
# 작성자: 2019202009 서여지
# 실습 7. 딕셔너리
# 제출일: 2019.04.20


# 1. 친구 명단을 관리하는 프로그램

FL = {}

while True :
    print("\n"); print("-"*20)
    print("""
    1. 연락처 목록 출력
    2. 연락처 추가
    3. 연락처 삭제
    4. 연락처 변경
    5. 종료
    """)
    menu = input("메뉴를 선택하세요 : ")
    print("\n")

    if menu == "1" :
        print (FL)

    elif menu == "2" :
        name=input('이름을 입력하세요')
        if name in FL :
            print('이미 존재하는 이름입니다')
            continue
        PN=input('번호를 입력하세요')
        FL[name] = PN

    elif menu == "3" :
        name = input("삭제할 이름을 입력하세요: ")
        if not name in FL : # 삭제할 이름이 리스트에 없는경우
            print("이름을 다시 확인해주세요")
        else :
           FL.pop(name)

    elif menu == "4" :
        name = input("변경할 이름을 입력하세요: ")
        if not name in FL : # 변경할 이름이 리스트에 없는경우
            print("이름을 다시 확인해주세요")
        else :
            op = input('이름을 변경하기: 1 \n 연락처를 변경하기: 2')
            if op == '1' :
                PH = FL[name]
                FL.pop(name)
                name = input('바뀐 이름을 입력하세요')
                FL[name] = PH

            # 수정될 이름이 다른 키값일때 덮어씌워


                    
            elif op == '2' :
                PH = input('바뀐 연락처를 입력하세요')
                FL[name] = PH

            else: print('다시 확인해주세요')

  
    elif menu == "5" :
        break
    else:
        print("다시 확인해주세요")


