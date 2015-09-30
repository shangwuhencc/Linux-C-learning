/*
* 界面初始化函数实现
* 流程：
*   循环调用函数line()，回执当前游戏版
*		调用ShowScore(), 显示初始得分，0
*   调用ShowSpeed(), 显示初始等级速度，初始速度1
*/

// m, n对应Vertical_boxs和Horizontal_boxs
void initialize(int x, int y, int m, int n){
	int i, j, oldx;
	oldx = x;
	for(j=0; j<n; j++){
		for(i=0; i<m; i++){
			Table_board[j][i].var = 0;
			Table_board[j][i].color = BgColor;
			line(x, y, x+BSIZE, y);
			line(x, y, x, y+BSIZE);
			line(x, y+BSIZE, x+BSIZE, y+BSIZE);
			line(x+BSIZE, y, x+BSIZE, y+BSIZE);
			}
		y += BSIZE;
		x = oldx;
		}
	Curbox_x = x;
	Curbox_y = y;
	flag_newbox = false;
	speed = 0;
	score = 0;
	ShowScore(score);
	ShowSpeed(speed);
	}