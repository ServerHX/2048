#include "header.h"

int main(void) //main �Լ� 
{ 
	int a1;
	int b=0;
	char trash[100]; //txt ���Ͽ��� ������ �����ϴµ� ���̴� '/' ǥ�ø� �޾ƿ��µ� ���(�����Ⱚ ����)
	int k; //���� ������ ���� ���ϰ� 
	int exitnum=0; //�α��� �������� ����
	int num=0; //�ִ� ������
	int arr[4][4]; //�ֿܼ��� �Է� ���� ���� �����ϰ� �м��ϴµ� �� 2���� �迭 
	
	per iden[100]; //ȸ������ �ִ� 100�� �޴� ����ü �迭 iden
	   
	memset(iden, 0, sizeof(iden));
	//���� ���� ���� �ʱ�ȭ 
	
	
	FILE *re=fopen("gamedb.txt", "rt"); //���� ���� �ؽ�Ʈ ����  
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
	//���� txt ������ ������ ��� gamedb.txt���Ͽ��� ���� ������ �о�� 
	
	num=b-1;
	if(num<0)
	num=0;
	
	/*for(a1=0; a1<100; a1++)
		{
		    printf("%s %s %s %d\n", iden[a1].name, iden[a1].id, iden[a1].psw, iden[a1].lc);
		}
	exit(1);*/
	account(iden, &num, &exitnum, &k); //ȸ������ �� �α��� �޴� �Լ�
	if(exitnum==1)
		return 0;	
	S:
	welcome(iden, &k); //ȯ������ ��� 
	cons_set(); //�ܼ� �ʱ�ȭ 
	gameLooper(arr); //���� ����(����� ����) 
	if(end(iden, &k, &num, arr)==1) 
	{
		score=0; //������ ���� �ʱ�ȭ 
		goto S; //�����  
	}
	
	else
	{
		return 0; 
	}
	
}

