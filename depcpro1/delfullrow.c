/*
* ���д�����
*  y��ʾ��һ����
*/

int DelFullRow(int y){
	/*������Ϸ������һ��*/
	int n, top = 0;  /*top���浱ǰ��ߵ�*/
	register m, totoal;
	for(n=y; n>=0; n--){  /*�ӵ�ǰ�����Ͽ�*/
		totoal = 0;
		for(m=0; m<Horizontal_boxs; m++){
			if(!Table_board[n][m].var){totoal++;}
			/*���в��������оͰ����д�������*/
			if(Table_board[n][m].var!=Table_board[n-1][m].var){
				Table_board[n][m].var = Table_board[n-1][m].var��
				Table_board[n][m].color = Table_board[n-1][m].color��
				}
			}
			if(totoal == Horizontal_boxs){  /*��������������������ǰ����*/
				top = n;
				break;				
				}
		}
		return top;  /*������ߵ�*/
	}
	
/*�ҵ�һ���������*/
void setFullRow(int t_boardy){
	int n, full_numb = 0, top = 0;
	register m;
	for(n=t_boardy+3; n>=t_boardy; n--){
		if(n<0 || n>=Vertical_boxs){continue;}  /*����������*/
		for(m=0; m<Horizontal_boxs; m++){  /*ˮƽ�ķ���*/
			/*�����һ���ǿվ���������*/
			if(!Table_board[n+full_numb][m].var){break;}
			}
		if(m==Horizontal_boxs){  /*�ҵ�����*/
			if(n==t_boardy+3)      /*��������е������*/
				top = DelFullRow(n+full_numb); /*�����Ϸ����У�����������*/
			else
				DelFullRow(n+full_numb);
			full_numb++;       /*ͳ���ҵ�������*/
			}
		}
	if(full_numb){  /*��������*/
		int oldx, x = Sys_x, y = BSIZE*top + Sys_y;
		oldx = x;
		score += full_numb*10    /*�ӷ���*/
		/*�����൱������ʾ��ɫ��*/
		for(n=top; n<t_boardy+4; n++){
			if(n>=Vertical_boxs){continue;}   /*��������*/
			for(m=0; m<Horizontal_boxs; m++){  /*ˮƽ����*/
				if(Table_board[n][m].var)
					setfillstyle(SOLID_FILL, Table_board[n][m].color);
				else
					setfillstyle(SOLID_FILL, BgColor);
				bar(x, y, x+BSIZE, y+BSIZE);
				line(x, y, x+BSIZE, y);
				line(x, y, x, y+BSIZE);
				line(x, y+BSIZE, x+BSIZE, y+BSIZE);
				line(x+BSIZE, y, x+BSIZE, y+BSIZE);
				x += BSIZE;
				}
				y += BSIZE;
				x = oldx;
			}
			ShowScore(score);
			if(speed!=score/speed_step){
				speed = score/speed_step;
				ShowSpeed(speed);
				}
			else
				ShowSpeed(speed);
		}
	}