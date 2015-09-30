/*main function*/

#include "prep.h";

void main(){
	int GameOver = 0;
	int key, nextbox;
	int Currentaction = 0;  /*标记当前动作状态*/
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
		initialize(Sys_x, Sys_y, Horizontal_boxs, Vertical_boxs);/*初始化*/
		nextbox = MkNextBox(-1);
		
		show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
		show_box(LeftWin_x, Curbox_y+200, nextbox, shapes[nextbox].color);
		show_intro(Sys_x, Curbox_y+320);
		getch();
		while(1){
			/*Currentaction=0; flag_newbox=false检测是否有按键*/
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
					case VK_UP:  /*旋转*/
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
					/*表示当前有动作，移动或旋转*/
					show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
					Currentaction = 0;
					}
				/*按向下键，但不能下移，就产生新方块*/
				if (flag_newbox){
					/*此时方块到底部，清除满行，置0*/
					ErasePreBox(LeftWin_x, Sys_y+200, nextbox);
					nextbox = MkNextBox(nextbox);
					show_box(Curbox_x, Curbox_y, current_box_numb, shapes[nextbox].color);
					/*刚一开始，游戏结束*/
					if (!MoveAble(Curbox_x, Curbox_y, current_box_numb, MoveDown)){
						show_box(Curbox_x, Curbox_y, current_box_numb, shapes[current_box_numb].color);
						GameOver = 1;
						}
						else{
							flag_newbox = false;
							}
						Currentaction = 0;
					}
					else{   /*自由下落的情况*/
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