# io01.py
# 작성일: 2019.03.13 ~ 2019.03.15
# 작성자: 2019202009 서여지
# 여러가지 문제를 해결하는 프로그램
# 제출일: 2019.03.15


# 문제1. 구의 부피 구하기

r= float(input('반지름의 길이를 입력하세요.\nr= '))
V=(4/3)*(3.141592)*(r**3)
print(f'반지름이 {r} 인 구의 부피(V)는 4/3 x π x ({r})^3 이므로,')
print('소수 셋째자리에서 반올림 하여 V=%.2f 입니다'%V)


print('.\n.\n.')
#문제2. BMI 구하기

Key= float(input('키(cm)를 입력하세요 :'))
Mommuge= float(input('몸무게(kg)를 입력하세요 :'))
BMI= Mommuge/(Key/100)**2
print(f'키: {Key}cm, 몸무게: {Mommuge}kg \nBMI:{BMI}')


print('.\n.\n.')
#문제3. 2차 방정식의 두 근 구하기

print('ax^2 + bx + c = ?\n단, a,b,c는 모두 정수이다\n')
a= float(input('x^2의 계수(a)=:'))
b= float(input('x의 계수(b)='))
c= float(input('상수항(c)='))

Geun1= (-b+(b**2-4*a*c)**0.5)/(2*a)
Geun2= (-b-(b**2-4*a*c)**0.5)/(2*a)

if Geun1==Geun2:
    print(f'\n{a}x^2 + {b}x + {c} = {Geun1} 중근을 갖는다.')
else: print(f'\n{a}x^2 + {b}x + {c} = {Geun1},{Geun2}')


print('.\n.\n.')
#문제4. 두 점을 지는 직선을 그리고, 직선의 길이 구하기.

x1= float(input('한 점의 x좌표 x1 ='))
y1= float(input('한 점의 y좌표 y1 ='))
x2= float(input('다음 점의 x좌표 x2 ='))
y2= float(input('다음 점의 y좌표 y2 ='))

print(f'점({x1},{y1})과 점({x2},{y2})을 연결하는 직선을 거북이가 그려줍니다.')

from turtle import *
reset()
shape('turtle')

up()
goto(x1,y1)
down()
goto(x2,y2)
up()

L= ((x1-x2)**2+(y1-y2)**2)**0.5

write(f'점({x1},{y1})과 점({x2},{y2}) 사이의 거리는\n')
write('소수 셋째자리에서 반올림 하여 %.2f입니다.'%L)

print('.\n.')
print(f'점({x1},{y1})과 점({x2},{y2}) 사이의 거리는')
print('소수 셋째자리에서 반올림 하여 %.2f입니다.'%L)
