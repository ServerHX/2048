#include "header.h"

void flush(void)
{
	while(getchar()!='\n'); //�Է� ���� Ŭ���� 
}

void cons_set()
{
	system("mode con: cols=51 lines=25 | title 2048"); //�ܼ� ũ�� ���� 
	HANDLE consolehandle=GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ� �������� 
	CONSOLE_CURSOR_INFO consolecursor; //Ŀ�� ���� �������� 
	consolecursor.bVisible=0; 
	consolecursor.dwSize=1;
	//�ֱ����� Ŀ�� ���� ���ֱ�  
	SetConsoleCursorInfo(consolehandle, &consolecursor); //���� ����
}

void curdes()
{
	HANDLE consolehandle=GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ� �������� 
	CONSOLE_CURSOR_INFO consolecursor; //Ŀ�� ���� �������� 
	consolecursor.bVisible=0; 
	consolecursor.dwSize=1;
	//�ֱ����� ���� ���ֱ�  
	SetConsoleCursorInfo(consolehandle, &consolecursor); //���� ����
}
//Ŀ�� ������ ���� �Լ�

void uninit()
{
	system("mode con cols=60 lines=40 | title LOGIN"); //�ܼ� ũ�� ���� 
	HANDLE consolehandle=GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ� �������� 
	CONSOLE_CURSOR_INFO consolecursor; //Ŀ�� ���� �������� 
	consolecursor.bVisible=1; 
	consolecursor.dwSize=20;
	//�ֱ����� Ŀ�� ���� ��Ȱ  
	SetConsoleCursorInfo(consolehandle, &consolecursor); //���� ����
}
//������ �α��� ���� �����ϴ� �Լ�
