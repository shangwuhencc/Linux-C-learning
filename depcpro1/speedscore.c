/*更新速度和成绩*/

/*显示分数*/
void ShowScore(int score){
	int x, y;
	char score_str[5];  /*保存游戏得分*/
	setfillstyle(SOLID_FILL, BgColor);
	x = LeftWin_x;
	y = 100;
	bar(x-BSIZE, y, x+BSIZE*3, y+BSIZE*3);
	sprintf(score_str, "%3d", score);
	outtextxy(x, y, "SCORE");
	outtextxy(x, y+10, score_str);
	}
	
/*显示速度*/
void ShowSpeed(int speed){
	int x, y;
	char speed_str[5];
	setfillstyle(SOLID_FILL, BgColor);
	x = LeftWin_x;
	y = 150;
	bar(x-BSIZE, y, x+BSIZE*3, y+BSIZE*3);
	/*确定一个以(x1,y1)为左上角，(x2,y2)为右下角的矩形窗口，再按规定图模和颜色填充*/
	sprintf(speed_str, "%3d", speed+1);
	outtextxy(x, y, "Level");
	outtextxy(x, y+10, speed_str);
	/*输出字符串指针speed_str所指的文本在规定的（x,y）位置*/
	outtextxy(x, y+50, "Nextbox");
	}
	
void show_help(int xs, int ys){
	char stemp[50];
	setcolor(15);
	rectangle(xs, ys, xs+239, ys+100);
	sprintf(stemp, " -Roll -Downwards");
	stemp[0] = 24;
	stemp[8] = 25;
	setcolor(14);
	outtextxy(xs+40, ys+30, stemp);
	sprintf(stemp, " -Turn Left -Turn Right");
	stemp[0] = 27;
	stemp[13] = 26;
	outtextxy(xs+40, ys+45, stemp);
	outtextxy(xs+40, ys+60, "Esc-Exit");
	setcolor(FgColor);
	}