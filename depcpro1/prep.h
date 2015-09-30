/*Ԥ������̣�����ȫ�ֱ��������������ͽṹ��*/
/*ͷ�ļ�����*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>      //��
#include <graphics.h>  //ͼ�κ�����


#define MAX_BOX 19

/*���尴����,�����ֵ*/
#define VK_LEFT 0x4b00
#define VK_RIGHT 0x4d00
#define VK_DOWN 0x5000
#define VK_UP 0x4800
#define VK_ESC 0x011b
#define TIMER 0x1c

/*���峣��*/
#define BSIZE 20
#define Sys_x 160
#define Sys_y 25         /*��ʾ�����������Ͻ�����*/
#define Horizontal_boxs 10
#define Vertical_boxs 15     /*�Է���Ϊ��λ�ĳ���*/
#define Begin_boxs_x Horizontal_boxes 2    /*��һ��������ʼλ��*/

#define EgColor 3   /*ǰ����ɫ*/
#define EgColor 0   /*������ɫ*/

#define LeftWin_x Sys_x+Horizontal_boxs*BSIZE+46     /*�ұ�״̬��x����*/

#define false 0
#define true 1

/*�ƶ��ķ���*/
#define MoveLeft 1
#define MoveRight 2
#define MoveDown 3
#define MoveRoll 4

/*����ȫ�ֱ���*/
int current_box_numb;    /*���浱ǰ������*/
/*x,y���淽�鵱ǰ����*/
int Curbox_x = Sys_x + Begin_boxs_x*BSIZE, Curbox_y = Sys_y;
int flag_newbox = false;   /*����Ƿ�����·���*/
int speed = 0;            /*�����ٶ�*/
int score = 0;             /*ÿ�ȼ�����Ҫ����*/

/*��Ϸ�װ�ṹ��*/
struct BOARD{
	int var;   /*״ֻ̬��0��1,1��ʾ�ѱ�ռ��*/
	int color;   /*��ɫ���*/
	}Table_board[Vertical_boxs][Horizontal_boxs];

/*
	��Ϸ����ṹ��
	���鶼����4*4�����
	4bits��ʾһ�У�����һ���������ֽ�
*/

struct SHAPE{
	char box[2];  /*2�ֽڱ�ʾ������״*/
	int color;  /*������ɫ*/
	int next;   /*�¸������ţ���19��*/
	};

/*
	SHAPE �ṹ����
	��ʼ���������ݣ�����MAX_BOX��SHAPE���͵Ľṹ���飬����ʼ��
*/
struct SHAPE shapes[MAX_BOX]=
{
	/*
	* *   * * *   * *      *
	* *   *         *  * * *
	* * *           * 
	*/
	{0x88,  0xc0,  CYAN,  1}��
	{0xe8,  0x0,   CYAN,  2}��
	{0xc4,  0x40,  CYAN,  3}��
	{0x2e,  0x0,   CYAN,  0}��
	
	/*
	*   *         * *  * * *
	*   * *       *        *
	* * * * * *   * 
	*/
	{0x44,  0xc0,  MAGENTA,  5}��
	{0x8e,  0x0,   MAGENTA,  6}��
	{0xc8,  0x80,  MAGENTA,  7}��
	{0xe2,  0x0,   MAGENTA,  4}��
	
	/*
	*  *            
	*  * *     * *
	*    *   * *   
	*/
	{0x8c,  0x40,  YELLOW,  9},
	{0x6c,  0x0,   YELLOW,  8},
	
	/*
	*    *            
	*  * *  * *
	*  *      * *   
	*/
	{0x4c,  0x80,  BROWN,  11},
	{0xc6,  0x0,   BROWN,  10},
	
	/*
	*   *    *    * * *     *
	* * * *  * *    *     * *
	*        *              *
	*/
	{0x4e,  0x0,   WHITE,  13}��
	{0x8c,  0x80,  WHITE,  14}��
	{0xe4,  0x0,   WHITE,  15}��
	{0x4c,  0x40,  WHITE,  12}��
	
	/*
	*  *            
	*  *   * * *
	*  *      
	*/
	{0x88,  0x88,  RED,  17},
	{0xf0,  0x0,   RED,  16},
	
	/*
	*  * *          
	*  * *      
	*/
	{0xcc,  0x0,  BLUE,  18}
	};

/*ָ��ԭʱ���жϴ��������ڵ��жϴ�����ָ��*/
void interrupt (*oldtimer)(void);

/*��ʾ����*/
void ShowScore(int score);

/*��ʾ�ٶ�*/
void ShowSpeed(int speed);

/*������ʾ*/
void show_help(int xs, int ys);

/*ʵ���µ�ʱ��*/
void interrupt newtimer(void);

/*SetTimer������ʱ�Ӵ������*/
void SetTimer(void interrupt (*IntProc)(void));

/*KillTimer�ָ�ԭ�е�ʱ�Ӵ������*/
void KillTimer();

/*initialize��ʼ������*/
void initialize(int x, int y, int m, int n);

/*DelFullRowɾ�����У�y����ɾ��������*/
int DelFullRow(int y);

/*setFullRow��ѯ����,���������*/
void setFullRow(int t_boardy);

/*MkNextBox������һ����Ϸ���飬���ط����*/
int MkNextBox(int box_numb);

/*EraseBox��������*/
void EraseBox(int x, int y, int box_numb);

/*show_box��ʾһ������*/
void show_box(int x, int y, int box_numb);

/*MoveAble����ƶ�����*/
int MoveAble(int x, int y, int box_numb, int direction);