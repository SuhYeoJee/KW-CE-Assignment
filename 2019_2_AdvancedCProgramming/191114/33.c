#include <stdio.h>
#include <string.h>
//2:19~2:40

int main(void)
{
	int i;
	char name[10];
	//문자열 상수
	char *emps[6][2] = { "김소미","서울 서초구 국립도서관",
		"안재은","부산시 해운대","김원선","서울시 강남구 역삼동 SDS멀티 캠퍼스",
		"진달래","속초시 대포항 바다 1번지","한송이","인천시 남구 새마을 아파트",NULL,NULL };

	printf("검색할 성명 ? ");
	scanf("%s", name);
	for (i = 0; i < 5; i++)
	{
		if (strcmp(name, *emps[i]) == 0) //일치하는경우
			break;
	}
	emps[5][0] = ""; //일치하지 않는 경우
	emps[5][1] = "검색되지 않습니다";
	printf("%s, %s\n", emps[i][0], emps[i][1]);
	return 0;
}