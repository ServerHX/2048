#include "header.h"

	char id[100][30];
	int Score[100];

     void account(per iden[], int* i, int* a, int *k) //로그인 함수 
	 //(순서대로 플레이어 정보 구조체 배열, 최대 계정 수 주소값, 종료 확인하는 exitnum의 주소값, 현 계정 번호 주소값)
	 // 위 괄호안의 값을 매개변수로 사용 
     {
     	int number = 0;
     	int tempScore;
     	char tempId[30];
     	int cnt;
     	int loop; //아이디 중복확인 반복문 변수  
		int tpnum; // 로그인 과정 임시번호 (현 계정의 번호) 
		int a1; //scanf 변수 
		int b1=0, b2=0, b3=0; //반복문 활용 변수 
		per temp; //임시계정 (로그인 과정에서 계정 확인에 쓰임) 
		 
	        Q:
	        	number = 0;
        	system("cls");
        	uninit(); //로그인 모드로 설정 변경 
        	puts("===========================================================");
        	gotoxy(26, 2);
        	puts("[랭킹]");
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
				} //내림차순 정렬 
			}
			
			for(cnt=0; cnt<100; cnt++)
			{
				if((iden[cnt].id)[0] == 0 && (iden[cnt].psw)[0] == 0 && (iden[cnt].name)[0] == 0 || number > 8)
				{
					break;
				}
				gotoxy(6, 4+cnt*2);
				printf("(%d위)", cnt+1);
				gotoxy(13, 4+cnt*2);
				printf("아이디: %s", id[cnt]);
				gotoxy(28, 4+cnt*2);
				printf("|"); 
				gotoxy(34, 4+cnt*2);
				printf("최고 점수: %d", Score[cnt]);
				number++; 
			} //랭킹 출력 
			
			gotoxy(0, number*2+4); //적절한 거리만큼 개행 
			
			puts("\n===========================================================");
  		    printf("\n  *****MAIN*****\n  1. 로그인\n  2. 회원가입\n  3. 종료\n");
			puts("\n===========================================================");
			printf("\n  항목을 선택하세요: ");
			scanf("%d", &a1);
			if(a1<=3 && a1>=1)
			{
				if(a1==1)
				{
					if((iden[0].name)[0]=='0')
					{
						curdes();
						printf("\n  계정을 등록해주세요!\n"); 
						Sleep(1000);
						goto Q;
					}
					//저장된 계정이 없을 시  
					
					else
					{
						
						printf("  아이디: ");
						scanf("%s", temp.id);
						//받아온 아이디를 임시 구조체 변수에 저장 
						for(b2=0; b2<*i+1; b2++)
						{
							if(!strcmp(temp.id, iden[b2].id))
							{
								tpnum=b2;
								break;
							}
							//iden 구조체 배열에 아이디가 존재하는 경우 로그인 성공
							 
							else
							{
								if(b2==*i)
								{
									curdes();
									printf("\n  존재하지 않는 아이디입니다.\n\n");
									Sleep(1000);
									goto Q;
								}
							}
							//최대 계정 수까지 반복했는데 아이디가 존재하지 않을 경우  
						}
						
						printf("  비밀번호: "); 
						scanf("%s", temp.psw); //입력한 비밀번호 정보를 임시 구조체 변수에 저장 
						for(b3=0; b3<*i+1; b3++)
						{
							if(!strcmp(temp.psw, iden[b3].psw) && b3==tpnum)
							{
								curdes();
								*k=tpnum; //아이디와 비밀번호가 일치할 경우 임시번호 tpnum의 값을 포인터 변수 k를 역참조한 값에 저장 
								return; //함수 탈출 
							}
							
							else
							{
								if(b3==*i)
								{
									curdes();
									printf("\n  비밀번호가 틀렸습니다.\n\n");
									Sleep(1000);
									goto Q;
								}
							}
							//최대 계정 수까지 반복했는데 비밀번호가 일치하지 않을 경우
						}
					}
					
				}
				
				else if(a1==2)
				{ 
					printf("\n  성명: ");
					scanf("%s", iden[*i].name); 
					printf("  아이디: ");
					scanf("%s", (iden[*i].id));
					for(loop=0; loop<*i; loop++)
						{
							if(!strcmp(iden[*i].id, iden[loop].id))
							{
								curdes();
							    printf("  아이디가 중복됩니다, 로그인 해주세요.\n");
							    Sleep(1000);
								goto Q; //처음부터 다시 
							}
							
						}
						//이미 구조체 배열에 아이디가 존재하는 경우 
						 
					printf("  비밀번호: ");
					scanf("%s", (iden[*i].psw));
					//성명, 아이디, 비밀번호를 구조체 배열에 저장 
					
					curdes(); //커서 점멸 제거 (보기에 걸리적거려서 제거함, 딱히 핵심적인 작용을 하지는 않음) 
					*k=*i;
					//현 계정번호를 최대 계정번호로 바꿈(회원가입 후 로그인화면에서 종료를 선택할 경우 정보저장에 사용) 
					iden[*k].lc=0; //게임 진척도 0으로 초기화 
					printf("\n  이제 로그인을 하실 수 있습니다.\n");
					Sleep(1000);
					
					*i += 1;
					//최대 계정수에 +1 
					goto Q;
					//처음 로그인 화면으로 돌아감 
				}
				
				else if(a1==3)
				{
					printf("\n  Exiting Process. . . . . . ");
					*a=1;
				}
				//종료를 선택한 경우  
				
				else
				{
					flush(); //입력버퍼 비우기 
					curdes();
					printf("\n  다시 시도해주세요.\n");
					Sleep(1000);
					goto Q;
				}
				//1, 2, 3외에 다른글자를 입력하였을 경우 
			}
			
			else
			{
				flush();
				curdes();
				printf("\n  다시 시도해주세요.\n");
				Sleep(1000);
				goto Q;
			}
			//1, 2, 3외에 다른 수나 글자를 입력하였을 경우
		}
		
		
	
	//여기까지 회원가입 및 로그인 단계
