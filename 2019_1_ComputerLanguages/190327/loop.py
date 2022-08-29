# loop.py
# 작성일: 2019.03.27
# 작성자: 2019202009 서여지
# 실습5. 반복문
# 제출일: 2019.03.27



# 500부터 1000사이의 홀수의 합 구하기

print(sum(range(501,1000,2)))



#6개의 원 그리기

from turtle import *
reset()
shape('turtle')

for a in range(6):
    circle(60)
    right(60)



#로그인 프로그램 수정

loginID = 'Escher'
loginPW = 'soso423'



b=1

while b<6:

    userID = input('ID: ')
    userPW = input('PW: ')
    

    if userID == loginID and userPW == loginPW :
        print(f'환영합니다 {userID}님~')
        break
    else:
        print('\n아이디와 비밀번호를 확인하세요.\n',b,'회')
        print()
        b+=1
        continue
if b==6:
    print('입력한 정보가 올바르지 않아 로그인에 실패했습니다.')



# 다각형을 그리는 프로그램


print('''\n\n4-(1) 하나의 다각형을 그리는 프로그램
3이상의 정수를 입력하지 않으면 작동하지 않습니다
''')
n=int(input('n각형을 그립니다. \nn = '))

from turtle import *
reset()
shape('turtle')

for c in range(n):
    fd(50)
    left(360/n)


print('\n4-(2) 반복적으로 다각형을 그리는 프로그램\n')
print('\n3이상의 정수를 입력해주세요.\n0을 입력하면 프로그램이 종료됩니다.\n')
while True :
    n=int(input('\nn각형을 그립니다. \nn = '))


    if n==0:
        print('\n프로그램을 종료합니다.')
        break
    
    elif n<3:
        print('\n오류! 3 이상의 정수를 입력해주세요.\n')
        
    else :
        from turtle import *
        reset()
        shape('turtle')

        for c in range(n):
            fd(50)
            left(360/n)



