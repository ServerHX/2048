#include "header.h"

	char id[100][30];
	int Score[100];

     void account(per iden[], int* i, int* a, int *k) //�α��� �Լ� 
	 //(������� �÷��̾� ���� ����ü �迭, �ִ� ���� �� �ּҰ�, ���� Ȯ���ϴ� exitnum�� �ּҰ�, �� ���� ��ȣ �ּҰ�)
	 // �� ��ȣ���� ���� �Ű������� ��� 
     {
     	int number = 0;
     	int tempScore;
     	char tempId[30];
     	int cnt;
     	int loop; //���̵� �ߺ�Ȯ�� �ݺ��� ����  
		int tpnum; // �α��� ���� �ӽù�ȣ (�� ������ ��ȣ) 
		int a1; //scanf ���� 
		int b1=0, b2=0, b3=0; //�ݺ��� Ȱ�� ���� 
		per temp; //�ӽð��� (�α��� �������� ���� Ȯ�ο� ����) 
		 
	        Q:
	        	number = 0;
        	system("cls");
        	uninit(); //�α��� ���� ���� ���� 
        	puts("===========================================================");
        	gotoxy(26, 2);
        	puts("[��ŷ]");
			for(cnt=0; cnt<100; cnt++)
			{
				if((iden[cnt].id)[0] == 0 && (iden[cnt].psw)[0] == 0 && (iden[cnt].name)[0] == 0)
				{
					break;
				}
				strcpy(id[cnt], iden[cnt].id);
				Score[cnt] = iden[cnt].lc;
			}
			
			for(cnt=0; cnt<100; cnt++)
			{
				if(Score[cnt+1] == 0)
				{
					break;
				}
				
				if(Score[cnt] < Score[cnt+1])
				{
					tempScore = Score[cnt];
					Score[cnt] = Score[cnt+1];
					Score[cnt+1] = tempScore;
					
					strcpy(tempId, id[cnt]);
					memset(id[cnt], 0, sizeof(id[cnt]));
					strcpy(id[cnt], id[cnt+1]);
					memset(id[cnt+1], 0, sizeof(id[cnt]));
					strcpy(id[cnt+1], tempId);
				} //�������� ���� 
			}
			
			for(cnt=0; cnt<100; cnt++)
			{
				if((iden[cnt].id)[0] == 0 && (iden[cnt].psw)[0] == 0 && (iden[cnt].name)[0] == 0 || number > 8)
				{
					break;
				}
				gotoxy(6, 4+cnt*2);
				printf("(%d��)", cnt+1);
				gotoxy(13, 4+cnt*2);
				printf("���̵�: %s", id[cnt]);
				gotoxy(28, 4+cnt*2);
				printf("|"); 
				gotoxy(34, 4+cnt*2);
				printf("�ְ� ����: %d", Score[cnt]);
				number++; 
			} //��ŷ ��� 
			
			gotoxy(0, number*2+4); //������ �Ÿ���ŭ ���� 
			
			puts("\n===========================================================");
  		    printf("\n  *****MAIN*****\n  1. �α���\n  2. ȸ������\n  3. ����\n");
			puts("\n===========================================================");
			printf("\n  �׸��� �����ϼ���: ");
			scanf("%d", &a1);
			if(a1<=3 && a1>=1)
			{
				if(a1==1)
				{
					if((iden[0].name)[0]=='0')
					{
						curdes();
						printf("\n  ������ ������ּ���!\n"); 
						Sleep(1000);
						goto Q;
					}
					//����� ������ ���� ��  
					
					else
					{
						
						printf("  ���̵�: ");
						scanf("%s", temp.id);
						//�޾ƿ� ���̵� �ӽ� ����ü ������ ���� 
						for(b2=0; b2<*i+1; b2++)
						{
							if(!strcmp(temp.id, iden[b2].id))
							{
								tpnum=b2;
								break;
							}
							//iden ����ü �迭�� ���̵� �����ϴ� ��� �α��� ����
							 
							else
							{
								if(b2==*i)
								{
									curdes();
									printf("\n  �������� �ʴ� ���̵��Դϴ�.\n\n");
									Sleep(1000);
									goto Q;
								}
							}
							//�ִ� ���� ������ �ݺ��ߴµ� ���̵� �������� ���� ���  
						}
						
						printf("  ��й�ȣ: "); 
						scanf("%s", temp.psw); //�Է��� ��й�ȣ ������ �ӽ� ����ü ������ ���� 
						for(b3=0; b3<*i+1; b3++)
						{
							if(!strcmp(temp.psw, iden[b3].psw) && b3==tpnum)
							{
								curdes();
								*k=tpnum; //���̵�� ��й�ȣ�� ��ġ�� ��� �ӽù�ȣ tpnum�� ���� ������ ���� k�� �������� ���� ���� 
								return; //�Լ� Ż�� 
							}
							
							else
							{
								if(b3==*i)
								{
									curdes();
									printf("\n  ��й�ȣ�� Ʋ�Ƚ��ϴ�.\n\n");
									Sleep(1000);
									goto Q;
								}
							}
							//�ִ� ���� ������ �ݺ��ߴµ� ��й�ȣ�� ��ġ���� ���� ���
						}
					}
					
				}
				
				else if(a1==2)
				{ 
					printf("\n  ����: ");
					scanf("%s", iden[*i].name); 
					printf("  ���̵�: ");
					scanf("%s", (iden[*i].id));
					for(loop=0; loop<*i; loop++)
						{
							if(!strcmp(iden[*i].id, iden[loop].id))
							{
								curdes();
							    printf("  ���̵� �ߺ��˴ϴ�, �α��� ���ּ���.\n");
							    Sleep(1000);
								goto Q; //ó������ �ٽ� 
							}
							
						}
						//�̹� ����ü �迭�� ���̵� �����ϴ� ��� 
						 
					printf("  ��й�ȣ: ");
					scanf("%s", (iden[*i].psw));
					//����, ���̵�, ��й�ȣ�� ����ü �迭�� ���� 
					
					curdes(); //Ŀ�� ���� ���� (���⿡ �ɸ����ŷ��� ������, ���� �ٽ����� �ۿ��� ������ ����) 
					*k=*i;
					//�� ������ȣ�� �ִ� ������ȣ�� �ٲ�(ȸ������ �� �α���ȭ�鿡�� ���Ḧ ������ ��� �������忡 ���) 
					iden[*k].lc=0; //���� ��ô�� 0���� �ʱ�ȭ 
					printf("\n  ���� �α����� �Ͻ� �� �ֽ��ϴ�.\n");
					Sleep(1000);
					
					*i += 1;
					//�ִ� �������� +1 
					goto Q;
					//ó�� �α��� ȭ������ ���ư� 
				}
				
				else if(a1==3)
				{
					printf("\n  Exiting Process. . . . . . ");
					*a=1;
				}
				//���Ḧ ������ ���  
				
				else
				{
					flush(); //�Է¹��� ���� 
					curdes();
					printf("\n  �ٽ� �õ����ּ���.\n");
					Sleep(1000);
					goto Q;
				}
				//1, 2, 3�ܿ� �ٸ����ڸ� �Է��Ͽ��� ��� 
			}
			
			else
			{
				flush();
				curdes();
				printf("\n  �ٽ� �õ����ּ���.\n");
				Sleep(1000);
				goto Q;
			}
			//1, 2, 3�ܿ� �ٸ� ���� ���ڸ� �Է��Ͽ��� ���
		}
		
		
	
	//������� ȸ������ �� �α��� �ܰ�
