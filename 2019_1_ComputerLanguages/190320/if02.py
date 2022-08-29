# 파일명: if02.py
# 실습4. 연산자와 조건문
# 작성자: 2019202009 서여지
# 제출일: 2019.03.20


# 아이디와 비밀번호

loginID = 'Escher' #프로그램에 저장된 값
loginPW = 'soso423'

userID = input('ID: ')
userPW = input('PW: ')

# 정보가 일치하는 경우와 아닌경우로 나누어 다른 문자열을 출력한다.
if userID == loginID and userPW == loginPW :
    print(f'환영합니다 {userID}님~')
else:
    print('아이디와 비밀번호를 확인하세요')


print('\n\n')


# 윤년확인

year = int(input('윤년인지 확인할 연도를 입력해주세요.\n'))

# 0이 아닌 다른 값은 '참'임을 이용한다.
if year%4 :
    print(f'{year}년은 윤년이 아닙니다')
else :
    if year%100 :
        print(f'{year}년은 윤년입니다')
    else:
        if year%400 :
            print(f'{year}년은 윤년이 아닙니다')
        else:
            print(f'{year}년은 윤년입니다')

print('\n\n')


# 정수판별

from turtle import *
reset()
shape('turtle')

goto(100,100)
write('거북이가 이곳에 오면 양수입니다')
home()
goto(100,0)
write('거북이가 이곳에 오면 0입니다')
home()
goto(100,-100)
write('거북이가 이곳에 오면 음수입니다')
home()

num = numinput('정수판별','정수를 입력해주세요')

if num > 0 :
    goto(100,100)
elif num == 0 :
    goto(100,0)
else :
    goto(100,-100)

