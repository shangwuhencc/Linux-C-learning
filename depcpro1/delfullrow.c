/*
* 满行处理函数
*  y表示哪一行满
*/

int DelFullRow(int y){
	/*该行游戏板下移一行*/
	int n, top = 0;  /*top保存当前最高点*/
	register m, totoal;
	for(n=y; n>=0; n--){  /*从当前行网上看*/
		totoal = 0;
		for(m=0; m<Horizontal_boxs; m++){
			if(!Table_board[n][m].var){totoal++;}
			/*上行不等于下行就把上行传给下行*/
			if(Table_board[n][m].var!=Table_board[n-1][m].var){
				Table_board[n][m].var = Table_board[n-1][m].var；
				Table_board[n][m].color = Table_board[n-1][m].color；
				}
			}
			if(totoal == Horizontal_boxs){  /*发现上面有连续空行提前结束*/
				top = n;
				break;				
				}
		}
		return top;  /*返回最高点*/
	}
	
/*找到一行满的情况*/
void setFullRow(int t_boardy){
	int n, full_numb = 0, top = 0;
	register m;
	for(n=t_boardy+3; n>=t_boardy; n--){
		if(n<0 || n>=Vertical_boxs){continue;}  /*超过底线了*/
		for(m=0; m<Horizontal_boxs; m++){  /*水平的方向*/
			/*如果有一个是空就跳过该行*/
			if(!Table_board[n+full_numb][m].var){break;}
			}
		if(m==Horizontal_boxs){  /*找到满行*/
			if(n==t_boardy+3)      /*如果是满行的最高行*/
				top = DelFullRow(n+full_numb); /*清除游戏板该行，并下移数据*/
			else
				DelFullRow(n+full_numb);
			full_numb++;       /*统计找到的行数*/
			}
		}
	if(full_numb){  /*存在满行*/
		int oldx, x = Sys_x, y = BSIZE*top + Sys_y;
		oldx = x;
		score += full_numb*10    /*加分数*/
		/*这里相当于重显示调色板*/
		for(n=top; n<t_boardy+4; n++){
			if(n>=Vertical_boxs){continue;}   /*超过底线*/
			for(m=0; m<Horizontal_boxs; m++){  /*水平方向*/
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