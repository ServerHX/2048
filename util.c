#include "header.h"

void flush(void)
{
	while(getchar()!='\n'); //입력 버퍼 클리어 
}

void cons_set()
{
	system("mode con: cols=51 lines=25 | title 2048"); //콘솔 크기 조정 
	HANDLE consolehandle=GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 가져오기 
	CONSOLE_CURSOR_INFO consolecursor; //커서 정보 가져오기 
	consolecursor.bVisible=0; 
	consolecursor.dwSize=1;
	//주기적인 커서 점멸 없애기  
	SetConsoleCursorInfo(consolehandle, &consolecursor); //정보 갱신
}

void curdes()
{
	HANDLE consolehandle=GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 가져오기 
	CONSOLE_CURSOR_INFO consolecursor; //커서 정보 가져오기 
	consolecursor.bVisible=0; 
	consolecursor.dwSize=1;
	//주기적인 점멸 없애기  
	SetConsoleCursorInfo(consolehandle, &consolecursor); //정보 갱신
}
//커서 깜빡임 제거 함수

void uninit()
{
	system("mode con cols=60 lines=40 | title LOGIN"); //콘솔 크기 조정 
	HANDLE consolehandle=GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 가져오기 
	CONSOLE_CURSOR_INFO consolecursor; //커서 정보 가져오기 
	consolecursor.bVisible=1; 
	consolecursor.dwSize=20;
	//주기적인 커서 점멸 부활  
	SetConsoleCursorInfo(consolehandle, &consolecursor); //정보 갱신
}
//설정을 로그인 모드로 복구하는 함수
