#ifndef _HEADER_H_
#define _HEADER_H_

#include <stdio.h>
#include <string.h> //memset �Լ� ���� ��� 
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#endif


#ifndef _ACCOUNT_
#define _ACCOUNT_

typedef struct
{
	char name[50]; //�̸� 
	char id[50]; //���̵� 
	char psw[50]; //��ȣ 
	int lc; //���� ��ô�� 
}per; //����ü ��Ī per 
//���� ���� ����ü 

#endif

#ifndef _MAIN_FUNC_
#define _MAIN_FUNC_

int score;
int loop_cancel;
int map[100000][4][4];
int currentNum;
int count_undo;

void gotoxy(int x, int y);
int end(per iden[], int *b, int *num, int (*arr)[4]);
void cons_set();
void arrRotator(int (*arr)[4]);
int gameMove_checker(int (*arr)[4]);
void randCreator(int (*arr)[4]);
void arrScanner(int (*arr)[4]);
void subMove(int arr[]);
void mainMove(int (*arr)[4]);
void arrPrinter(int (*arr)[4]);
void init(int (*arr)[4], int cnt);
void gameLooper(int (*arr)[4]);
void account(per iden[], int* i, int* a, int *k);
void curdes();
void flush();
void uninit();
int checkDirection(int (*arr)[4]);
void subMove2(int arr[]);
void mainMove2(int (*arr)[4]);
void init2(int (*arr)[4], int cnt);
int first_predictMove(int (*arr)[4]);
int second_predictMove(int (*arr)[4]);
int third_predictMove(int (*arr)[4]);
int fourth_predictMove(int (*arr)[4]);
int fifth_predictMove(int (*arr)[4]);
void moveAI(int (*arr)[4]);
void gameLooper_AI(int (*arr)[4]);
//�Լ� ����
 
#endif
