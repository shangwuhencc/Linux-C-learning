/*显示/消除方块*/

void show_box(int x, int y, int box_numb, int color){
	int i, ii, ls_x = x;
	if*(box_numb<0 || box_numb>=MAX_BOX){
		box_numb = MAX_BOX / 2;
		}
	setfillstyle(SOLID_FILL, color);
	/*
	* 移位判断哪一位是1，方块是每一行用半个字节表示
	* 128d=1000 0000b
	*/
	for(ii=0; ii<2; ii+){
		int mask = 128;
		for(i=0; i<8; i++){
			if(i%4==0 && i!=0){
				y += BSIZE;
				x = ls_x;
				}
			if((shapes[box_numb].box[ii]) & mask){
				bar(x, y, x+BSIZE, y+BSIZE);
				line(x, y, x+BSIZE, y);
				line(x, y, x, y+BSIZE);
				line(x, y+BSIZE, x+BSIZE, y+BSIZE);
				line(x+BSIZE, y, x+BSIZE, y+BSIZE);
				}
			x += BSIZE;
			mask /= 2;
			}
			y += BSIZE;
			x = ls_x;
		}
	}
	
/*消除原box*/
void EraseBox(int x, int y, int box_numb){
	int mask = 128, t_boardx, t_boardy, n, m;
	setfillstyle(SOLID_FILL, BgColor);
	for(n=0; n<4; n++){
		for(m=0; m<4; m++){
			/*最左边有方块并且当前游戏也有方块*/
			if((shapes[box_numb].box[n/2]) & mask){
				bar(x+m*BSIZE, y+n*BSIZE, x+m*BSIZE+BSIZE, y+n*BSIZE+BSIZE);
				line(x+m*BSIZE, y+n*BSIZE, x+m*BSIZE+BSIZE, y+n*BSIZE);
				line(x+m*BSIZE, y+n*BSIZE, x+m*BSIZE, y+n*BSIZE+BSIZE);
				line(x+m*BSIZE, y+n*BSIZE+BSIZE, x+m*BSIZE+BSIZE, y+n*BSIZE+BSIZE);
				line(x+m*BSIZE+BSIZE, y+n*BSIZE, x+m*BSIZE+BSIZE, y+n*BSIZE+BSIZE);
				}
			mask = mask / (2);
			if(mask==0) mask = 128;
			}
		}
	}
	
/*将新形状的方块放置在游戏板上，并返回此方块号*/
int MkNextBox(int box_numb){
	int mask = 128, t_boardx, t_boardy, n, m;
	t_boardx = (Curbox_x-Sys_x) / BSIZE;
	t_boardy = (Curbox_y-Sys_y) / BSIZE;
	for(n=0; n<4; n++){
		for(m=0; m<4; m++){
			if((shapes[box_numb].box[n/2]) & mask){
				Table_board[t_boardy+n][t_boardx+m].var = 1;  /*设置游戏板*/
				Table_board[t_boardy+n][t_boardx+m].color = shape[current_box_numb].color;
				}
			mask = mask / (2);
			if(mask==0)mask = 128;
			}
		}
		setFullRow(t_boardy);
		Curbox_x = Sys_x + Begin_boxs_x * BSIZE;
		Curbox_y = Sys_y;  /*再次初始化坐标*/
		if(box_numb==-1) box_numb = rand()%MAX_BOX;
		current_box_numb = box_numb;
		flag_newbox = false;
		return(rand()%MAX_BOX);
	}
	
/*操作方块移动*/
int MoveAble(int x, int y, int box_numb, int direction){
	/*t_boardx是当前方块最左边在游戏板位置*/
	int n, m, t_boardx, t_boardy;
	int mask;
	if(direction==MoveLeft){    /*如果左移*/
		mask = 128;
		x -= BSIZE;   /*方块左移一个块的长度*/
		t_boardx = (x-Sys_x) / BSIZE;
		t_boardy = (y-Sys_y) / BSIZE;
		for(n=0; n<4; n++){
			for(m=0; m<4; m++){
				/*如果最左边有方块并且当前游戏板也有方块*/
				if((shapes[box_numb].box[n/2]) & mask){
					if((x+BSIZE)<Sys_x)
						return false;   /*表示碰到最左边*/
					/*左移后与游戏板有冲突*/
					else if(Table_board[t_boardy+n][t_boardx+m].var)
						return false;
					}
					mask = mask / (2);
					if(mask==0) mask = 128;
				}
			}
			return true;
		}
	else if(direction==MoveRight){    /*如果右移*/
		mask = 128;
		x += BSIZE;   /*方块左移一个块的长度*/
		t_boardx = (x-Sys_x) / BSIZE;
		t_boardy = (y-Sys_y) / BSIZE;
		for(n=0; n<4; n++){
			for(m=0; m<4; m++){
				/*如果最右边有方块并且当前游戏板也有方块*/
				if((shapes[box_numb].box[n/2]) & mask){
					if((x+BSIZE*m)>=(Sys_x+BSIZE*Horizontal_boxs))
						return false;   /*表示碰到最右边*/
					/*右移后与游戏板有冲突*/
					else if(Table_board[t_boardy+n][t_boardx+m].var)
						return false;
					}
					mask = mask / (2);
					if(mask==0) mask = 128;
				}
			}
			return true;
		}
	else if(direction==MoveDown){    /*如果下移*/
		mask = 128;
		y += BSIZE;   /*方块下移一个块的长度*/
		t_boardx = (x-Sys_x) / BSIZE;
		t_boardy = (y-Sys_y) / BSIZE;
		for(n=0; n<4; n++){
			for(m=0; m<4; m++){   /*看最下边4个单元*/
				/*最下边有方块并且当前游戏板也有方块*/
				if((shapes[box_numb].box[n/2]) & mask){
					if((y+BSIZE*n)>=(Sys_y+BSIZE*Vertical_boxs) || Table_board[t_boardy+n][t_boardx+m].var)
					{
						flag_newbox = true;   
						break;
						}
					mask = mask / (2);
					if(mask==0) mask = 128;
				}
			}
			if(flag_newbox)
				return false;
			else
				return true;
		}
	}
	else if(direction==MoveRoll){    /*如果转动*/
		mask = 128;
		t_boardx = (x-Sys_x) / BSIZE;
		t_boardy = (y-Sys_y) / BSIZE;
		for(n=0; n<4; n++){
			for(m=0; m<4; m++){   /*看最下边4个单元*/
				/*最下边有方块并且当前游戏板也有方块*/
				if((shapes[box_numb].box[n/2]) & mask){
					/*如果碰到最下边*/
					if((y+BSIZE*n)>=(Sys_y+BSIZE*Vertical_boxs)
						return false;
					/*如果碰到最左边*/
					if((x+BSIZE*n)>=(Sys_x+BSIZE*Horizontal_boxs)
						return false;
					/*如果碰到最右边*/
					if((x+BSIZE*m)>=(Sys_x+BSIZE*Horizontal_boxs)
						return false;
					else if(Table_board[t_boardy+n][t_boardx+m].var)
						return false;
				}
				mask = mask / (2);
				if(mask==0) mask = 128;
			}
		}
		return true;
	}
	else 
		return false;
}