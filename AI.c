#include "header.h"

static int exiting;
int element=0;

void subMove2(int arr[]) //temp 배열에서 서로 인접한 값들 끼리의 병합을 수행하는 함수 
{
	int i, j;
	for(i=0; i<4; i++)  
	{
		if(arr[i]==arr[i+1]) //인접한 값들이 같을 때 
		{
			arr[i] *= 2; //먼저나오는 값의 값을 2배로 증가
			element += arr[i];
			for(j=i+1; j<3; j++) 
			{
				arr[j]=arr[j+1];
			}
			arr[3]=0;
			// 나머지 값들은 앞으로 한칸씩 당기고, 맨 마지막 값은 0으로 재설정  
		}
	}
}

void mainMove2(int (*arr)[4]) //배열을 위로 밀어올림 
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
		
		subMove2(temp); //temp배열에서 서로 인접한 값들 끼리의 병합 수행 
		
		for(i=0; i<4; i++)
		{
			arr[i][j]=temp[i];
		} 
		//temp배열의 값을 본래 배열의 열로 다시 옮김 
	}
}

void init2(int (*arr)[4], int cnt)
{
	if(exiting==1)
	return; //함수 종료 
	
	int i, j, k;
	
	for(k=0; k<cnt; k++)
	{
		arrRotator(arr);
	}
	
	if(!checkDirection(arr))
	{
		exiting = 1; //움직임이 불가능할 경우 1로 초기화 
	}
	
	mainMove2(arr);

	for(k=0; k<4-cnt; k++)
	{
		arrRotator(arr);
	}
	
	if(exiting != 1)
	randCreator(arr); //exiting = 1은 움직임이 불가능함을 의미하므로 무한 루프 방지를 위해 exiting이 1이 아닐때만 랜덤으로 숫자를 생성하도록 함  
} //game_func에서 init() 함수와 동일한 기능, but 인공지능 효율성을 위해 exiting 변수를 이용한 조기종료 구현  


int first_predictMove(int (*arr)[4]) //최고 등급 예측, 5수 앞을 봄 
{
  int i, c = 0;
  int a_1, a_2, a_3, a_4, a_5;
  int temp[4][4];
  int line[5] = { -1, -1, -1, -1, -1}; //line 배열의 요소를 모두 -1로 초기화
  //5번 하는 동안 wasd 키 중 무엇을 입력할지를 선택 (총 5개) 
  int max = 0; //최고 점수 = 0 초기화 
  element = 0; //game_func.c의 score와 같은 개념, 전역변수 

  for (a_1 = 0; a_1 < 4; a_1++)
  {
    for (a_2 = 0; a_2 < 4; a_2++)
    {
      for (a_3 = 0; a_3 < 4; a_3++)
      {
        for (a_4 = 0; a_4 < 4; a_4++)
        {
          for (a_5 = 0; a_5 < 4; a_5++)
          {
            element = 0; //초기화 
            memcpy(temp, arr, sizeof(int) * 16); //임시배열을 arr로 초기화 
            exiting = 0;

            init2(temp, a_1);
            init2(temp, a_2);
            init2(temp, a_3);
            init2(temp, a_4);
            init2(temp, a_5);
            //5번 진행(임시배열을 만들어 스스로 시뮬레이션), 미래 5수를 예측  

            if (element > max && exiting == 0)
            {
              max = element; //최적의 방법을 찾아 점수가 max보다 크면 변수 값 바꿈   
              line[0] = a_1;
              line[1] = a_2;
              line[2] = a_3;
              line[3] = a_4;
              line[4] = a_5;
            } //가장 최적의 방법을 찾아 line 배열의 요소를 초기화 
          }
        }
      }
    }
  }

  for (i = 0; i < 5; i++)
  {
    if (line[i] == -1)
      c++;
  }

  if (c == 5)
    return -1; //만약 가능한 경우의 수가 없으면 -1 반환  

  else
    return line[0]; //최적의 수를 찾은 후 가장 먼저 두어야 할 수를 반환  
}

int second_predictMove(int (*arr)[4]) //first_predictMove() 함수와 기능 동일, 4수 앞을 봄 
{
  int i, c = 0;
  int a_1, a_2, a_3, a_4;
  int temp[4][4];
  int line[4] = { -1, -1, -1, -1};
  int max = 0;
  element = 0;

  for (a_1 = 0; a_1 < 4; a_1++)
  {
    for (a_2 = 0; a_2 < 4; a_2++)
    {
      for (a_3 = 0; a_3 < 4; a_3++)
      {
        for (a_4 = 0; a_4 < 4; a_4++)
        {

          element = 0;
          memcpy(temp, arr, sizeof(int) * 16);
          exiting = 0;

          init2(temp, a_1);
          init2(temp, a_2);
          init2(temp, a_3);
          init2(temp, a_4);

          if (element > max && exiting == 0)
          {
            max = element;
            line[0] = a_1;
            line[1] = a_2;
            line[2] = a_3;
            line[3] = a_4;
          }

        }
      }
    }
  }

  for (i = 0; i < 4; i++)
  {
    if (line[i] == -1)
      c++;
  }

  if (c == 4)
    return -1;

  else
    return line[0];
}

int third_predictMove(int (*arr)[4]) //first_predictMove() 함수와 기능 동일, 3수 앞을 봄
{
  int i, c = 0;
  int a_1, a_2, a_3;
  int temp[4][4];
  int line[3] = { -1, -1, -1};
  int max = 0;
  element = 0;

  for (a_1 = 0; a_1 < 4; a_1++)
  {
    for (a_2 = 0; a_2 < 4; a_2++)
    {
      for (a_3 = 0; a_3 < 4; a_3++)
      {
        element = 0;
        memcpy(temp, arr, sizeof(int) * 16);
        exiting = 0;

        init2(temp, a_1);
        init2(temp, a_2);
        init2(temp, a_3);

        if (element > max && exiting == 0)
        {
          max = element;
          line[0] = a_1;
          line[1] = a_2;
          line[2] = a_3;
        }
      }
    }
  }

  for (i = 0; i < 3; i++)
  {
    if (line[i] == -1)
      c++;
  }

  if (c == 3)
    return -1;

  else
    return line[0];
}

int fourth_predictMove(int (*arr)[4]) //first_predictMove() 함수와 기능 동일, 2수 앞을 봄
{
  int i, c = 0;
  int a_1, a_2;
  int temp[4][4];
  int line[2] = { -1, -1};
  int max = 0;
  element = 0;

  for (a_1 = 0; a_1 < 4; a_1++)
  {
    for (a_2 = 0; a_2 < 4; a_2++)
    {
      element = 0;
      memcpy(temp, arr, sizeof(int) * 16);
      exiting = 0;

      init2(temp, a_1);
      init2(temp, a_2);

      if (element > max && exiting == 0)
      {
        max = element;
        line[0] = a_1;
        line[1] = a_2;
      }
    }
  }

  for (i = 0; i < 2; i++)
  {
    if (line[i] == -1)
      c++;
  }

  if (c == 2)
    return -1;

  else
    return line[0];
}

int fifth_predictMove(int (*arr)[4]) //first_predictMove() 함수와 기능 동일, 1수 앞을 봄
{
  int i, c = 0;
  int a_1;
  int temp[4][4];
  int line = -1;
  int max = 0;
  element = 0;

  for (a_1 = 0; a_1 < 4; a_1++)
  {
    element = 0;
    memcpy(temp, arr, sizeof(int) * 16);
    exiting = 0;
    init2(temp, a_1);
	
	//printf("e: %d m: %d ex: %d\n", element, max, exiting);
    if (element >= max && exiting == 0)
    {
      max = element;
      line = a_1;
    }
  }

  if(line == -1)
  return 5;

  else
  {
  	return line;
  }
}

void moveAI(int (*arr)[4])
{
	int i, c;
	int lineNum;
	
	lineNum = first_predictMove(arr);
	if(lineNum==-1){
			lineNum = second_predictMove(arr);
	}
	
	if(lineNum==-1){
			lineNum = third_predictMove(arr);
	}	
	
	if(lineNum==-1){
			lineNum = fourth_predictMove(arr);
	}

	if(lineNum==-1){
			lineNum = fifth_predictMove(arr);
	}
	
	if(lineNum==5){
			exit(1);
	}
	//최고 등급 예측 부터 아래로 내려감 
	// (ex) first_predictMove() 함수에서 -1이 반환되었다면 second_predictMove() 함수를 실행해 4수를 내다봄, 두번째에도 -1이 반환되면 점점 하위등급의 예측 시스템으로 내려감  		
	printf("\n%d", lineNum); //인공지능이 무슨 수를 두는지를 콘솔 창에 출력  
	init(arr, lineNum); //실제 게임 배열인 arr에 수를 둠  
}

void gameLooper_AI(int (*arr)[4]) //game_func.c의 gameLooper()함수와 기능은 비슷, 사용자의 입력을 받지 않고 인공지능이 자동으로 타일을 움직인다는 점이 차이 
{
	FILE * fp = fopen("map.txt", "wt");
	int i, j;
	//setGame(arr);
	arrPrinter(arr);
	int key, a;
	while(1)
	{
		if(kbhit())
		{
			key = getch();
			if(key == 'i' || key == 'I')
			{
				system("cls");
				loop_cancel = 1;
				gameLooper(arr);
				return;
			}
		}
		if(gameMove_checker(arr)==0)
		{
			return;
		}		
			moveAI(arr);
			for(i=0; i<4; i++)
			{
				for(j=0; j<4; j++)
				{
					fprintf(fp, "%d ", arr[i][j]);
				}
				fputc('\n', fp);
			}
			fputc('\n', fp);
			fputc('\n', fp);
			system("cls");
			arrPrinter(arr);
		
	}
} 
