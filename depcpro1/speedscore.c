/*�����ٶȺͳɼ�*/

/*��ʾ����*/
void ShowScore(int score){
	int x, y;
	char score_str[5];  /*������Ϸ�÷�*/
	setfillstyle(SOLID_FILL, BgColor);
	x = LeftWin_x;
	y = 100;
	bar(x-BSIZE, y, x+BSIZE*3, y+BSIZE*3);
	sprintf(score_str, "%3d", score);
	outtextxy(x, y, "SCORE");
	outtextxy(x, y+10, score_str);
	}
	
/*��ʾ�ٶ�*/
void ShowSpeed(int speed){
	int x, y;
	char speed_str[5];
	setfillstyle(SOLID_FILL, BgColor);
	x = LeftWin_x;
	y = 150;
	bar(x-BSIZE, y, x+BSIZE*3, y+BSIZE*3);
	/*ȷ��һ����(x1,y1)Ϊ���Ͻǣ�(x2,y2)Ϊ���½ǵľ��δ��ڣ��ٰ��涨ͼģ����ɫ���*/
	sprintf(speed_str, "%3d", speed+1);
	outtextxy(x, y, "Level");
	outtextxy(x, y+10, speed_str);
	/*����ַ���ָ��speed_str��ָ���ı��ڹ涨�ģ�x,y��λ��*/
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