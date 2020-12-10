#include "header.h"

int main(void) //main 함수 
{ 
	int a1;
	int b=0;
	char trash[100]; //txt 파일에서 계정을 구분하는데 쓰이는 '/' 표시를 받아오는데 사용(쓰레기값 제거)
	int k; //현재 접속한 계정 리턴값 
	int exitnum=0; //로그인 과정에서 종료
	int num=0; //최대 계정수
	int arr[4][4]; //콘솔에서 입력 받은 수를 저장하고 분석하는데 쓸 2차원 배열 
	
	per iden[100]; //회원정보 최대 100개 받는 구조체 배열 iden
	   
	memset(iden, 0, sizeof(iden));
	//계정 정보 전부 초기화 
	
	
	FILE *re=fopen("gamedb.txt", "rt"); //정보 복구 텍스트 열기  
    if(re != NULL)
    {
		while(1)
		{
		    if(feof(re) != 0)
		    break;
		    fscanf(re, "%s %s %s %d %s", iden[b].name, iden[b].id, iden[b].psw, &iden[b].lc, trash);
		    b++;
		}
	}
	//읽을 txt 파일이 존재할 경우 gamedb.txt파일에서 계정 정보를 읽어옴 
	
	num=b-1;
	if(num<0)
	num=0;
	
	/*for(a1=0; a1<100; a1++)
		{
		    printf("%s %s %s %d\n", iden[a1].name, iden[a1].id, iden[a1].psw, iden[a1].lc);
		}
	exit(1);*/
	account(iden, &num, &exitnum, &k); //회원가입 및 로그인 메뉴 함수
	if(exitnum==1)
		return 0;	
	S:
	welcome(iden, &k); //환영문구 출력 
	cons_set(); //콘솔 초기화 
	gameLooper(arr); //게임 루프(사용자 버전) 
	if(end(iden, &k, &num, arr)==1) 
	{
		score=0; //죽으면 점수 초기화 
		goto S; //재시작  
	}
	
	else
	{
		return 0; 
	}
	
}

