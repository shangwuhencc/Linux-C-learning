/*
* �����ʼ������ʵ��
* ���̣�
*   ѭ�����ú���line()����ִ��ǰ��Ϸ��
*		����ShowScore(), ��ʾ��ʼ�÷֣�0
*   ����ShowSpeed(), ��ʾ��ʼ�ȼ��ٶȣ���ʼ�ٶ�1
*/

// m, n��ӦVertical_boxs��Horizontal_boxs
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