#include "header.h"

static int exiting;
int element=0;

void subMove2(int arr[]) //temp �迭���� ���� ������ ���� ������ ������ �����ϴ� �Լ� 
{
	int i, j;
	for(i=0; i<4; i++)  
	{
		if(arr[i]==arr[i+1]) //������ ������ ���� �� 
		{
			arr[i] *= 2; //���������� ���� ���� 2��� ����
			element += arr[i];
			for(j=i+1; j<3; j++) 
			{
				arr[j]=arr[j+1];
			}
			arr[3]=0;
			// ������ ������ ������ ��ĭ�� ����, �� ������ ���� 0���� �缳��  
		}
	}
}

void mainMove2(int (*arr)[4]) //�迭�� ���� �о�ø� 
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
		
		subMove2(temp); //temp�迭���� ���� ������ ���� ������ ���� ���� 
		
		for(i=0; i<4; i++)
		{
			arr[i][j]=temp[i];
		} 
		//temp�迭�� ���� ���� �迭�� ���� �ٽ� �ű� 
	}
}

void init2(int (*arr)[4], int cnt)
{
	if(exiting==1)
	return; //�Լ� ���� 
	
	int i, j, k;
	
	for(k=0; k<cnt; k++)
	{
		arrRotator(arr);
	}
	
	if(!checkDirection(arr))
	{
		exiting = 1; //�������� �Ұ����� ��� 1�� �ʱ�ȭ 
	}
	
	mainMove2(arr);

	for(k=0; k<4-cnt; k++)
	{
		arrRotator(arr);
	}
	
	if(exiting != 1)
	randCreator(arr); //exiting = 1�� �������� �Ұ������� �ǹ��ϹǷ� ���� ���� ������ ���� exiting�� 1�� �ƴҶ��� �������� ���ڸ� �����ϵ��� ��  
} //game_func���� init() �Լ��� ������ ���, but �ΰ����� ȿ������ ���� exiting ������ �̿��� �������� ����  


int first_predictMove(int (*arr)[4]) //�ְ� ��� ����, 5�� ���� �� 
{
  int i, c = 0;
  int a_1, a_2, a_3, a_4, a_5;
  int temp[4][4];
  int line[5] = { -1, -1, -1, -1, -1}; //line �迭�� ��Ҹ� ��� -1�� �ʱ�ȭ
  //5�� �ϴ� ���� wasd Ű �� ������ �Է������� ���� (�� 5��) 
  int max = 0; //�ְ� ���� = 0 �ʱ�ȭ 
  element = 0; //game_func.c�� score�� ���� ����, �������� 

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
            element = 0; //�ʱ�ȭ 
            memcpy(temp, arr, sizeof(int) * 16); //�ӽù迭�� arr�� �ʱ�ȭ 
            exiting = 0;

            init2(temp, a_1);
            init2(temp, a_2);
            init2(temp, a_3);
            init2(temp, a_4);
            init2(temp, a_5);
            //5�� ����(�ӽù迭�� ����� ������ �ùķ��̼�), �̷� 5���� ����  

            if (element > max && exiting == 0)
            {
              max = element; //������ ����� ã�� ������ max���� ũ�� ���� �� �ٲ�   
              line[0] = a_1;
              line[1] = a_2;
              line[2] = a_3;
              line[3] = a_4;
              line[4] = a_5;
            } //���� ������ ����� ã�� line �迭�� ��Ҹ� �ʱ�ȭ 
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
    return -1; //���� ������ ����� ���� ������ -1 ��ȯ  

  else
    return line[0]; //������ ���� ã�� �� ���� ���� �ξ�� �� ���� ��ȯ  
}

int second_predictMove(int (*arr)[4]) //first_predictMove() �Լ��� ��� ����, 4�� ���� �� 
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

int third_predictMove(int (*arr)[4]) //first_predictMove() �Լ��� ��� ����, 3�� ���� ��
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

int fourth_predictMove(int (*arr)[4]) //first_predictMove() �Լ��� ��� ����, 2�� ���� ��
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

int fifth_predictMove(int (*arr)[4]) //first_predictMove() �Լ��� ��� ����, 1�� ���� ��
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
	//�ְ� ��� ���� ���� �Ʒ��� ������ 
	// (ex) first_predictMove() �Լ����� -1�� ��ȯ�Ǿ��ٸ� second_predictMove() �Լ��� ������ 4���� ���ٺ�, �ι�°���� -1�� ��ȯ�Ǹ� ���� ��������� ���� �ý������� ������  		
	printf("\n%d", lineNum); //�ΰ������� ���� ���� �δ����� �ܼ� â�� ���  
	init(arr, lineNum); //���� ���� �迭�� arr�� ���� ��  
}

void gameLooper_AI(int (*arr)[4]) //game_func.c�� gameLooper()�Լ��� ����� ���, ������� �Է��� ���� �ʰ� �ΰ������� �ڵ����� Ÿ���� �����δٴ� ���� ���� 
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
