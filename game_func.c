#include "header.h"

void gotoxy(int x, int y)
{
	HANDLE consolehandle = GetStdHandle(STD_OUTPUT_HANDLE); //�ܼ� �������� 
	COORD pos; //��ǥ �������� 
	pos.X = x;
	pos.Y = y;
	//��ǥ�� �Ű������� ��ȯ 
	SetConsoleCursorPosition(consolehandle, pos);
	//�Ű����� ��ǥ�� �̵� 
}
//Ŀ�� ��ġ ���� �Լ� 

void welcome(per iden[], int* b)
{
	int key;
	cons_set();
	printf("\n\t\t      <2048>\n\n\n");
	printf("\n\n        Welcome, %s! (Press space to play)", iden[*b].name);
	if(iden[*b].lc==0)
	{
		printf("\n\n\n\n        You have not played any games yet...");
	}
	else
	{
		printf("\n\n\n\n            Your best score is %d!", iden[*b].lc);
	} //�� ó�� ����ȭ�� ����Ʈ 
	
	printf("\n\n\n\n");
	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key==32)
			{
				break;
			} //�����̽� �� ������ �ݺ��� Ż�� 
			
			else
			{
				continue;
			} //�ٸ� Ű ������ ��ȭ ���� 
		}
	}
}

int end(per iden[], int* b, int *num, int (*arr)[4])
{
	int x, key;
	cons_set();
	
	int c, d;
	printf("\n\t\t      <2048>\n\n\n");
	printf("    You died! (b: play again | x: quit)");
	printf("\n\n\n\n");  
	int i, j;
	for(i=0; i<4; i++) //�� ��� 
	{
		for(j=0; j<4; j++) //�� ��� 
		{	
			c = j*7+13;
			d = 9+i*3;
			gotoxy(c, d);
			printf("%d", arr[i][j]);
		}
	} //�׾��� �� �ʰ� �Բ� �׾��ٴ� �˸� ��� 
	gotoxy(7, 21); 
	printf("score: %d", score); //���� ��� 
	
	if(score>iden[*b].lc)
	iden[*b].lc=score; //���ھ �ְ����� �ʰ��� �ְ������� ���ھ�� �ٲ�
	
	FILE *fp = fopen("gamedb.txt", "wt");
	for (x = 0; x < *num; x++)
	{
	  fprintf(fp, "%s ", iden[x].name);
	  fprintf(fp, "%s ", iden[x].id);
	  fprintf(fp, "%s ", iden[x].psw);
	  fprintf(fp, "%d ", iden[x].lc);
	  fprintf(fp, "/ ");
	} //�ؽ�Ʈ ���� ��� �������� ����(���̳ʸ� ���� ������ �Ұ��� �ϱ� ������ ���� ���Ǽ��� ���� �ؽ�Ʈ ���) 
fclose(fp); //���� �ݱ� 

	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key=='b' || key=='B')
			{
				return 1;
			} //b ������ 1 ��ȯ, ���� ����� 
			
			else if(key=='x' || key=='X')
			{
				return 0;
			} //x ������ 0 ��ȯ, ���� ���� 
		}
	} 
}

void randCreator(int (*arr)[4])  
{
	int a, b, c;
	int i, j;
	
	srand(time(NULL)); //���� �õ� ����  
	
	A:
	a = rand()%4; //������ x��ǥ
	b = rand()%4; //������ y��ǥ 
	c = rand()%5; //20% probability
	
	if(arr[a][b]==0)
	{
		if(c==0) //20% probability
		arr[a][b]=4; //4 ���� 
		else 
		arr[a][b]=2; //2 ���� 
	}
	
	else
	{
		goto A; //���Ƿ� ���� ĭ�� �������(0) ���� ���, �ݺ� ����� 
	}

}

void arrScanner(int (*arr)[4]) //stdin ��Ʈ������ �о�� �Ű����� arr 2���� �迭�� �����ϴ� �Լ� 
{
	int i, j;
	printf("���ڸ� �Է��Ͻÿ�: \n");
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			scanf("%d", &arr[i][j]); //������� �ֿܼ��� ���� �о��, arr 2���� �迭�� ���� 
		}
		fgetc(stdin); //���� ���� ó�� 
	} 
}

void setGame(int (*arr)[4])
{
	
	system("cls");
	memset(arr, 0, sizeof(int)*16);
	int a_1, a_2, a_3, a_4;
	A:
	srand(time(NULL));
	a_1=rand()%4;
	a_2=rand()%4;
	a_3=rand()%4;
	a_4=rand()%4;
	int random_point = rand()%2;
	int ano = rand()%2;
	if(a_1 != a_2 || a_3 != a_4)
	{
		if(random_point == 1)
		{
			if(ano == 1)
			{
				arr[a_1][a_3]=2;
				arr[a_2][a_4]=2;
			}
			
			else if(ano == 0)
			{
				arr[a_1][a_3]=4;
				arr[a_2][a_4]=4;
			}
		}
		
		else if(random_point == 0)
		{
			arr[a_1][a_3]=2;
			arr[a_2][a_4]=4;
		}
		
	}
	//������ ��ǥ 2�� ���� �� �� ��ǥ�� ��Ȯ�� ��ġ���� ������ 2 ���� 
	
	else goto A; //�� ��ǥ�� ��ġ�ҽ� �ݺ��� ����� 
}

void mainMove(int (*arr)[4]) //�迭�� ���� �о�ø� 
{
	int i, j, a;
	int temp[4]; //������ �迭���� ������ ���� ������ ������ �迭 ���� 
	
	for(j=0; j<4; j++) //���� �޶��� 
	{
		memset(temp, 0, sizeof(int)*4); //temp �迭 �ʱ�ȭ(��� 0����) 
		a=0; //temp �迭�� ���� ä�ﶧ ī���� ���� 
		for(i=0; i<4; i++) //������ ��, ���� �޶��� 
		{
			if(arr[i][j] != 0) //������ �迭���� �ش� ��ġ�� �ִ� ���� 0�� �ƴҶ� 
			{
				temp[a]=arr[i][j]; //temp �迭�� ���� �߰� 
				a++; //���ʴ�� �߰��ϱ� ���Ͽ� a���� 1 ���� 
			}
		}
		
		/*
		���ݱ����� ������ �����ϸ�, temp�迭���� Ư�� ������ 0�� �ƴ� ���鸸 ����ȴ�.
		�� �ش� ���� (2, 4, 0, 4)���ٸ�, temp���� (2, 4, 4, 0)�� ����Ǵ� ���̴�. 
		(�� ������ 0�� ó�� temp�� memset�Լ��� �ʱ�ȭ�ϴ� �������� ��Ÿ���� ��) 
		*/  
		
		subMove(temp); //temp�迭���� ���� ������ ���� ������ ���� ���� 
		
		for(i=0; i<4; i++)
		{
			arr[i][j]=temp[i];
		} 
		//temp�迭�� ���� ���� �迭�� ���� �ٽ� �ű� 
	}
}

void subMove(int arr[]) //temp �迭���� ���� ������ ���� ������ ������ �����ϴ� �Լ� 
{
	int i, j;
	for(i=0; i<4; i++)  
	{
		if(arr[i]==arr[i+1]) //������ ������ ���� �� 
		{
			arr[i] *= 2; //���������� ���� ���� 2��� ����
			score += arr[i];
			for(j=i+1; j<3; j++) 
			{
				arr[j]=arr[j+1];
			}
			arr[3]=0;
			// ������ ������ ������ ��ĭ�� ����, �� ������ ���� 0���� �缳��  
		}
	}
}  

void arrPrinter(int (*arr)[4])
{
	int a, b;
	printf("\n\t\t      <2048>\n\n\n");
	printf("    Join the numbers and get to the 2048 tile!\n\n\t    Press esc for a new game!");
	
	printf("\n\n\n\n"); //�ȳ��� ����Ʈ 
	int i, j;
	for(i=0; i<4; i++) //�� ��� 
	{
		for(j=0; j<4; j++) //�� ��� 
		{	
			a = j*7+13;
			b = 9+i*3;
			gotoxy(a, b);
			printf("%d", arr[i][j]);  
		}
	} 
	gotoxy(7, 21);
	printf("score: %d", score);
} //�迭�� ����ϴ� �Լ� 

void arrRotator(int (*arr)[4])
{
	int i, j;
	int temp[4][4];
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			temp[3-j][i]=arr[i][j];
		}
	}
	memcpy(arr, temp, sizeof(int)*16);
} //�迭 ȸ����Ű�� �Լ�(�˰����� C��� ���� ���α׷��� ���� ���α׷��� ����) 

void undo(int (*arr)[4])
{
	memcpy(map[currentNum], arr, sizeof(int)*16);
	if(currentNum == 0)
		return;
	count_undo ++; //undo Ƚ�� ���� 
	currentNum--; //��������� ���(map -> header.h�� ����) �迭�� ���Ҹ� ����Ű�� ������ (undo�ϸ� 1 ����) 
	memcpy(arr, map[currentNum], sizeof(int)*16); //�� �迭�� �迭 ��� ���� ���� 
}

void redo(int (*arr)[4])
{
	if(count_undo == 0) //undo Ƚ������ �� ���� redo �Ұ� 
		return;
	count_undo--; //undo Ƚ�� ���� 
	currentNum++; //��������� ���(map) �迭�� ���Ҹ� ����Ű�� ������ (redo�ϸ� 1 ����)
	memcpy(arr, map[currentNum], sizeof(int)*16); //�� �迭�� �迭 ��� ���� ���� 
}

void chance(int (*tempArr)[4])
{
	count_undo = 0; //undo redo ī���� �ʱ�ȭ 
	memcpy(map[currentNum], tempArr, sizeof(int)*16);
	currentNum++;
	
	int count = 0;
	int newArr[4][4];
	int arr[16];
	int i, j;
	int limit = 4;
	int cnt = 0;
	int po = 1;
	int x=-1, y=0;
	
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			arr[count] = tempArr[i][j];
			count++;
		}
	} //���� 2���� �迭�� ���� ������ �迭�� ���� 
	
	while(1)
	{
		for(i=0; i<limit; i++)
		{
			x += po;
			if(cnt==16) break;
			newArr[y][x]= arr[cnt];
			cnt++;
		}
		if(cnt==16) break;
		
		limit--;
		
		for(j=0; j<limit; j++)
		{
			y += po;
			if(cnt==16) break;
			newArr[y][x] = arr[cnt];
			cnt++;
		}
		if(cnt==16) break;
		po *= -1;
	} //������ �迭 �˰���  
	memcpy(tempArr, newArr, sizeof(int)*16); //������ �迭 newArr�� ������ ���� �迭�� ���� 
}

void gameLooper(int (*arr)[4]) //���� ���� �Լ� 
{
	int key_new;
	B:
	if(loop_cancel == 0) //AI ��Ʈ���� ���� �� loop_cancel�� 1�� �ٲ� -> gameLooper �Լ� ���� ���� 
	setGame(arr); //���� �� 
	arrPrinter(arr); //�迭 ����Ʈ 
	int key, a;
	while(1)
	{
		if(gameMove_checker(arr)==0)
		{
			return;
		}
		A:
		if(kbhit())
		{
			key = getch();
			if(key==224)
			{
			    	key_new = getch();
			    	if(key_new==75)
					{
						init(arr, 3); //ȸ�� ����(���� Ǫ��) 
					}

					else if(key_new==77)
					{
						init(arr, 1); //ȸ�� 1ȸ(���� Ǫ��) 
					}
					
					else if(key_new==72)
					{
						init(arr, 0); //ȸ�� ����
					}
					
					else if(key_new==80)
					{
						init(arr, 2); //ȸ�� ����(�Ʒ� Ǫ��)
					}
			} //ȭ��ǥ�� �����̱�! 
			
			else
			{
				switch(key)
				{
					case 'w':
				    case 'W':
				    	init(arr, 0); //ȸ�� ���� 
						break;
					
					case 'd':
				    case 'D':
				    	init(arr, 1); //ȸ�� 1ȸ(���� Ǫ��) 
						break;
						
					case 's':
					case 'S':
						init(arr, 2); //ȸ�� ����(�Ʒ� Ǫ��) 
						break;
						
					case 'a':
					case 'A':
						init(arr, 3); //ȸ�� ����(���� Ǫ��) 
						break;
						
					case 'u': //UNDO 
					case 'U':
						undo(arr);
						break;
						
					case 'r': //REDO
					case 'R':
						redo(arr);
						break;
						
					case 'c': //Chance
					case 'C':
						chance(arr);
						break;
						
					case 'i':
					case 'I':
						gameLooper_AI(arr); //�ΰ����� ��� ���� 
						return; //gameLooper_AI ���� �� �ٷ� return 
						
					case 'n':
					case 'N':
						score=0; //esc ���� �ÿ� ���ھ� �ʱ�ȭ  
						goto B; //�����  
						break;
						
					case 'x':
					case 'X':
						return;
											
					default:
						goto A; //��ȭ ���� 
						
				}
			} //wasd�� �����̱�! 
			 
			system("cls");
			arrPrinter(arr);
		}
	}
} 

void init(int (*arr)[4], int cnt)
{
	count_undo = 0;
	int i, j, k;
	int exiting = 0;
	
	memcpy(map[currentNum], arr, sizeof(int)*16);
	currentNum++;
	
	for(k=0; k<cnt; k++)
	{
		arrRotator(arr); //�迭 ȸ��  
	}
	
	if(!checkDirection(arr))
	{
		exiting = 1; //�������� �Ұ����� ��� 1�� �ʱ�ȭ 
	}

	mainMove(arr); //���� �о�ø���  
	
	for(k=0; k<4-cnt; k++)
	{
		arrRotator(arr); //�ٽ� ȸ������ ���󺹱�  
	}
	
	if(exiting != 1)
	{
		randCreator(arr); //����ִ� �ڸ��� 2 �Ǵ� 4 ����  
	}
	
}

int gameMove_checker(int (*arr)[4]) //������ ���డ���� �� �ľ��ϴ� �Լ�, �Ű������� arr 2���� �迭  
{
	int i, j, k;
	int temp[4][4];
	memcpy(temp, arr, sizeof(int)*16); //temp �迭 �ʱ�ȭ 
	
	for(k=0; k<4; k++)
	{
		for(i=0; i<3; i++)
		{
			for(j=0; j<4; j++)
			{
					if(temp[i][j]==0)
					{
						return 1;
					} //arr�� 0�� �ϳ��� �����ϸ� ������ ���� -> 1 ��ȯ 
					
					if(temp[i][j]==temp[i+1][j])
	                {
		 				return 1;
	 				} //�Ʒ��� ���� ���� ���� ��  
			}
	 }
		arrRotator(temp); //�迭 ȸ��  
	}
	
	return 0; //���� ������ �Ұ��� �� ��� 0�� ��ȯ 
} 

int checkDirection(int (*arr)[4])
{
	int i, j;
	int temp[4][4];
	memcpy(temp, arr, sizeof(int)*16); 
	
	for(i=0; i<3; i++)
		{
			for(j=0; j<4; j++)
			{
					if(temp[i][j]==0)
					{
						return 1;
					} //arr�� 0�� �ϳ��� �����ϸ� ������ ���� -> 1 ��ȯ 
					
					if(temp[i][j]==temp[i+1][j])
	                {
		 				return 1;
	 				} //�Ʒ��� ���� ���� ���� ��  
			}
	 	}
	
	return 0; //���� ������ �Ұ��� �� ��� 0�� ��ȯ 
}
