# 파일명: str02.py
# 실습 5. 문자열
# 작성자: 2019202009 서여지
# 제출일: 2019.04.03


    # 1.경로명과 파일명을 분리

a=input('경로와 파일명을 입력하세요.\n\t예시 "C:\Python\1반\str02.py" \n:')
b=a.split('\\') # 문자열을 \기준으로 분리하여 리스트로 반환
print(b)
print('\n\n')


    # 2. 경로와 파일을 구분하여 출력

print('입력문자열 : ',a)


r=a.rfind('\\')     # rfind를 이용하여 문자열 가장 마지막에 사용된 \의 인덱스를 구함

print('\t경로명 : ',a[:r]) # 처음부터 마지막 \가 나오기 전까지 문자열 인덱싱

print('\t파일명 : ',b[-1]) # 인덱싱은 시퀀스 자료형 공통으로 사용가능하다

print('\n\n')


    #3. 문자열을 거꾸로 출력

c=input('거꾸로 출력할 문자열을 입력하세요.\n:')
print(c[::-1])
print('\n\n')


    #4. 사용자의 실제 이름만을 출력하기

data= open('passwd.txt').read()
k=data.split('\n') # passwd.txt의 내용을 줄단위로 분리


print('사용자의 실제 이름을 출력합니다.\n')
for n in range(len(k)): # passwd.txt의 줄 수(\n) 만큼 반복

    g=k[n].split(':') # 리스트k의 항목을 :기준으로 분리하여 리스트로 반환
    print(g[4])
