# parking.py
# 주차 프로그램 
# 학번 / 윤소정
# 2019.4.8

parking = []
top = 0
carName='A'
outCar = ''
select = 9

while True :
    select = input('[1] 자동차 넣기 [2] 자동차 빼기 [3] 끝 : ')

    if  select == '1'  :
        if   top >= 5   :
            print (' 주차장이 꽉 찼습니다. 더이상 주차할 수 없습니다.\n' )
        else :
            parking.append(carName)
            print(f' ** {parking[top]} 자동차 주차 완료.\n 주차장 상태 : {parking} \n')
            top += 1
            carName = chr(ord(carName)+1)
            
    elif  select == '2'  :
        if   top <= 0   :
            print(' 주차장이 비어있습니다.\n ')
        else :
            outCar = parking.pop()
            print(f' ** {outCar} 자동차 출차 완료.\n 주차장 상태 : {parking} \n')
            top -= 1
            carName = chr(ord(carName) -1)
            
    elif  select == '3' :
        break
    
    else :
        print ('잘못 입력하셨습니다. 다시 입력하세요.\n')

print(' 현재 주차장에 {top} 대가 있습니다. ')
print(' 프로그램을 종료합니다.\n')
input('Enter 키를 누르시면 종료됩니다...')
