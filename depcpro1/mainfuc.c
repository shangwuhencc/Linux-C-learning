/*main function*/

#include "prep.h";

void main(){
	int GameOver = 0;
	int key, nextbox;
	int Currentaction = 0;  /*��ǵ�ǰ����״̬*/
	int gd = VGA, gm = VGAHI, errorcode;
	initgraph(&gd, &gm, "");
	errorcode = graphresult();
	if(errorcode != grOK){
		printf("\nNotice:Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to quit!");
		getch();
		exit(1);
		}
		
		setbkcolor(BgColor);
		setcolor(FgColor);
		randomize();
		SetTimer(newtimer);  /*start*/
		initialize(Sys_x, Sys_y, Horizontal_boxs, Vertical_boxs);/*��ʼ��*/
		nextbox = MkNextBox(-1);
		
		show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
		show_box(LeftWin_x, Curbox_y+200, nextbox, shapes[nextbox].color);
		show_intro(Sys_x, Curbox_y+320);
		getch();
		while(1){
			/*Currentaction=0; flag_newbox=false����Ƿ��а���*/
			if (bioskey(1)){key = bioskey(0);}
			else {key = 0;}
				switch(key){
					case VK_LEFT:
						if(MoveAble(Curbox_x, Curbox_y, current_box_numb, MoveLeft)){
							EraseBox(Curbox_x, Curbox_y, current_box_numb);
							Curbox_x -= BSIZE;
							Currentaction = MoveLeft;
							}
						break;
					case VK_RIGHT:
						if(MoveAble(Curbox_x, Curbox_y, current_box_numb, MoveRight)){
							EraseBox(Curbox_x, Curbox_y, current_box_numb);
							Curbox_x += BSIZE;
							Currentaction = MoveRight;
							}
						break;
					case VK_DOWN:
						if(MoveAble(Curbox_x, Curbox_y, current_box_numb, MoveDown)){
							EraseBox(Curbox_x, Curbox_y, current_box_numb);
							Curbox_y += BSIZE;
							Currentaction = MoveDown;
							}
						else flag_newbox = true;
						break;
					case VK_UP:  /*��ת*/
						if(MoveAble(Curbox_x, Curbox_y, shapes[current_box_numb].next, MoveRoll)){
							EraseBox(Curbox_x, Curbox_y, current_box_numb);
							current_box_numb = shapes[current_box_numb].next;
							Currentaction = MoveRoll;
							}
						break;
					default:
						break;
					}
				if (Currentaction){
					/*��ʾ��ǰ�ж������ƶ�����ת*/
					show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
					Currentaction = 0;
					}
				/*�����¼������������ƣ��Ͳ����·���*/
				if (flag_newbox){
					/*��ʱ���鵽�ײ���������У���0*/
					ErasePreBox(LeftWin_x, Sys_y+200, nextbox);
					nextbox = MkNextBox(nextbox);
					show_box(Curbox_x, Curbox_y, current_box_numb, shapes[nextbox].color);
					/*��һ��ʼ����Ϸ����*/
					if (!MoveAble(Curbox_x, Curbox_y, current_box_numb, MoveDown)){
						show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
						GameOver = 1;
						}
						else{
							flag_newbox = false;
							}
						Currentaction = 0;
					}
					else{   /*������������*/
						if(Currentaction == MoveDown || TimerCounter > (20-speed*2)){
							if(MoveAble(Curbox_x, Curbox_y, current_box_numb, MoveDown)){
								EraseBox(Curbox_x, Curbox_y, current_box_numb);
								Curbox_y += BSIZE;
								show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
								}
							TimerCounter = 0;
							}
						}
					if(GameOver){   /*|| flag_newbox==-1*/
						printf("game over, thank you! your score is %d", score);
						getch();
						break;
						}
			}
		getch();
		KillTimer();
		closegraph();
	}