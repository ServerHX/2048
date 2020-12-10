#include "header.h"

void gotoxy(int x, int y)
{
	HANDLE consolehandle = GetStdHandle(STD_OUTPUT_HANDLE); //콘솔 가져오기 
	COORD pos; //좌표 가져오기 
	pos.X = x;
	pos.Y = y;
	//좌표값 매개변수로 전환 
	SetConsoleCursorPosition(consolehandle, pos);
	//매개변수 좌표로 이동 
}
//커서 위치 조정 함수 

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
	} //맨 처음 게임화면 프린트 
	
	printf("\n\n\n\n");
	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key==32)
			{
				break;
			} //스페이스 바 누르면 반복문 탈출 
			
			else
			{
				continue;
			} //다른 키 누르면 변화 없음 
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
	for(i=0; i<4; i++) //행 요소 
	{
		for(j=0; j<4; j++) //열 요소 
		{	
			c = j*7+13;
			d = 9+i*3;
			gotoxy(c, d);
			printf("%d", arr[i][j]);
		}
	} //죽었을 때 맵과 함께 죽었다는 알림 출력 
	gotoxy(7, 21); 
	printf("score: %d", score); //점수 출력 
	
	if(score>iden[*b].lc)
	iden[*b].lc=score; //스코어가 최고점수 초과면 최고점수를 스코어로 바꿈
	
	FILE *fp = fopen("gamedb.txt", "wt");
	for (x = 0; x < *num; x++)
	{
	  fprintf(fp, "%s ", iden[x].name);
	  fprintf(fp, "%s ", iden[x].id);
	  fprintf(fp, "%s ", iden[x].psw);
	  fprintf(fp, "%d ", iden[x].lc);
	  fprintf(fp, "/ ");
	} //텍스트 파일 열어서 게임정보 저장(바이너리 쓰면 수정이 불가능 하기 때문에 편집 편의성을 위해 텍스트 사용) 
fclose(fp); //파일 닫기 

	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key=='b' || key=='B')
			{
				return 1;
			} //b 눌리면 1 반환, 게임 재시작 
			
			else if(key=='x' || key=='X')
			{
				return 0;
			} //x 눌리면 0 반환, 게임 종료 
		}
	} 
}

void randCreator(int (*arr)[4])  
{
	int a, b, c;
	int i, j;
	
	srand(time(NULL)); //랜덤 시드 설정  
	
	A:
	a = rand()%4; //임의의 x좌표
	b = rand()%4; //임의의 y좌표 
	c = rand()%5; //20% probability
	
	if(arr[a][b]==0)
	{
		if(c==0) //20% probability
		arr[a][b]=4; //4 등장 
		else 
		arr[a][b]=2; //2 등장 
	}
	
	else
	{
		goto A; //임의로 잡은 칸이 비어있지(0) 않을 경우, 반복 재시작 
	}

}

void arrScanner(int (*arr)[4]) //stdin 스트림에서 읽어와 매개변수 arr 2차원 배열에 저장하는 함수 
{
	int i, j;
	printf("격자를 입력하시오: \n");
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			scanf("%d", &arr[i][j]); //순서대로 콘솔에서 수를 읽어옴, arr 2차원 배열에 저장 
		}
		fgetc(stdin); //개행 문자 처리 
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
	//임의의 좌표 2개 설정 후 두 좌표가 정확히 일치하지 않으면 2 생성 
	
	else goto A; //두 좌표가 일치할시 반복문 재시작 
}

void mainMove(int (*arr)[4]) //배열을 위로 밀어올림 
{
	int i, j, a;
	int temp[4]; //이차원 배열에서 각각의 열의 값들을 저장할 배열 선언 
	
	for(j=0; j<4; j++) //열이 달라짐 
	{
		memset(temp, 0, sizeof(int)*4); //temp 배열 초기화(모두 0으로) 
		a=0; //temp 배열에 값을 채울때 카운팅 변수 
		for(i=0; i<4; i++) //동일한 열, 행이 달라짐 
		{
			if(arr[i][j] != 0) //이차원 배열에서 해당 위치에 있는 값이 0이 아닐때 
			{
				temp[a]=arr[i][j]; //temp 배열에 값을 추가 
				a++; //차례대로 추가하기 위하여 a값은 1 증가 
			}
		}
		
		/*
		지금까지의 과정을 수행하면, temp배열에는 특정 열에서 0이 아닌 값들만 저장된다.
		즉 해당 열이 (2, 4, 0, 4)였다면, temp에는 (2, 4, 4, 0)이 저장되는 것이다. 
		(맨 마지막 0은 처음 temp를 memset함수로 초기화하는 과정에서 나타나는 것) 
		*/  
		
		subMove(temp); //temp배열에서 서로 인접한 값들 끼리의 병합 수행 
		
		for(i=0; i<4; i++)
		{
			arr[i][j]=temp[i];
		} 
		//temp배열의 값을 본래 배열의 열로 다시 옮김 
	}
}

void subMove(int arr[]) //temp 배열에서 서로 인접한 값들 끼리의 병합을 수행하는 함수 
{
	int i, j;
	for(i=0; i<4; i++)  
	{
		if(arr[i]==arr[i+1]) //인접한 값들이 같을 때 
		{
			arr[i] *= 2; //먼저나오는 값의 값을 2배로 증가
			score += arr[i];
			for(j=i+1; j<3; j++) 
			{
				arr[j]=arr[j+1];
			}
			arr[3]=0;
			// 나머지 값들은 앞으로 한칸씩 당기고, 맨 마지막 값은 0으로 재설정  
		}
	}
}  

void arrPrinter(int (*arr)[4])
{
	int a, b;
	printf("\n\t\t      <2048>\n\n\n");
	printf("    Join the numbers and get to the 2048 tile!\n\n\t    Press esc for a new game!");
	
	printf("\n\n\n\n"); //안내문 프린트 
	int i, j;
	for(i=0; i<4; i++) //행 요소 
	{
		for(j=0; j<4; j++) //열 요소 
		{	
			a = j*7+13;
			b = 9+i*3;
			gotoxy(a, b);
			printf("%d", arr[i][j]);  
		}
	} 
	gotoxy(7, 21);
	printf("score: %d", score);
} //배열을 출력하는 함수 

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
} //배열 회전시키는 함수(알고리즘은 C언어 열혈 프로그래밍 도전 프로그래밍 참조) 

void undo(int (*arr)[4])
{
	memcpy(map[currentNum], arr, sizeof(int)*16);
	if(currentNum == 0)
		return;
	count_undo ++; //undo 횟수 증가 
	currentNum--; //현재까지의 기록(map -> header.h에 선언) 배열의 원소를 가리키는 지시자 (undo하면 1 감소) 
	memcpy(arr, map[currentNum], sizeof(int)*16); //원 배열에 배열 기록 정보 복사 
}

void redo(int (*arr)[4])
{
	if(count_undo == 0) //undo 횟수보다 더 많이 redo 불가 
		return;
	count_undo--; //undo 횟수 차감 
	currentNum++; //현재까지의 기록(map) 배열의 원소를 가리키는 지시자 (redo하면 1 증가)
	memcpy(arr, map[currentNum], sizeof(int)*16); //원 배열에 배열 기록 정보 복사 
}

void chance(int (*tempArr)[4])
{
	count_undo = 0; //undo redo 카운팅 초기화 
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
	} //기존 2차원 배열을 전부 일차원 배열에 저장 
	
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
	} //달팽이 배열 알고리즘  
	memcpy(tempArr, newArr, sizeof(int)*16); //달팽이 배열 newArr의 내용을 기존 배열에 복사 
}

void gameLooper(int (*arr)[4]) //게임 루프 함수 
{
	int key_new;
	B:
	if(loop_cancel == 0) //AI 파트에서 종료 시 loop_cancel을 1로 바꿈 -> gameLooper 함수 종료 유도 
	setGame(arr); //게임 셋 
	arrPrinter(arr); //배열 프린트 
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
						init(arr, 3); //회전 없음(왼쪽 푸시) 
					}

					else if(key_new==77)
					{
						init(arr, 1); //회전 1회(우측 푸시) 
					}
					
					else if(key_new==72)
					{
						init(arr, 0); //회전 없음
					}
					
					else if(key_new==80)
					{
						init(arr, 2); //회전 없음(아래 푸시)
					}
			} //화살표로 움직이기! 
			
			else
			{
				switch(key)
				{
					case 'w':
				    case 'W':
				    	init(arr, 0); //회전 없음 
						break;
					
					case 'd':
				    case 'D':
				    	init(arr, 1); //회전 1회(우측 푸시) 
						break;
						
					case 's':
					case 'S':
						init(arr, 2); //회전 없음(아래 푸시) 
						break;
						
					case 'a':
					case 'A':
						init(arr, 3); //회전 없음(왼쪽 푸시) 
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
						gameLooper_AI(arr); //인공지능 모드 진입 
						return; //gameLooper_AI 종료 시 바로 return 
						
					case 'n':
					case 'N':
						score=0; //esc 누를 시에 스코어 초기화  
						goto B; //재시작  
						break;
						
					case 'x':
					case 'X':
						return;
											
					default:
						goto A; //변화 없음 
						
				}
			} //wasd로 움직이기! 
			 
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
		arrRotator(arr); //배열 회전  
	}
	
	if(!checkDirection(arr))
	{
		exiting = 1; //움직임이 불가능할 경우 1로 초기화 
	}

	mainMove(arr); //위로 밀어올리기  
	
	for(k=0; k<4-cnt; k++)
	{
		arrRotator(arr); //다시 회전시켜 원상복구  
	}
	
	if(exiting != 1)
	{
		randCreator(arr); //비어있는 자리에 2 또는 4 생성  
	}
	
}

int gameMove_checker(int (*arr)[4]) //게임이 진행가능한 지 파악하는 함수, 매개변수로 arr 2차원 배열  
{
	int i, j, k;
	int temp[4][4];
	memcpy(temp, arr, sizeof(int)*16); //temp 배열 초기화 
	
	for(k=0; k<4; k++)
	{
		for(i=0; i<3; i++)
		{
			for(j=0; j<4; j++)
			{
					if(temp[i][j]==0)
					{
						return 1;
					} //arr에 0이 하나라도 존재하면 무조건 가능 -> 1 반환 
					
					if(temp[i][j]==temp[i+1][j])
	                {
		 				return 1;
	 				} //아래쪽 수와 값이 같을 때  
			}
	 }
		arrRotator(temp); //배열 회전  
	}
	
	return 0; //게임 진행이 불가능 한 경우 0을 반환 
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
					} //arr에 0이 하나라도 존재하면 무조건 가능 -> 1 반환 
					
					if(temp[i][j]==temp[i+1][j])
	                {
		 				return 1;
	 				} //아래쪽 수와 값이 같을 때  
			}
	 	}
	
	return 0; //게임 진행이 불가능 한 경우 0을 반환 
}
