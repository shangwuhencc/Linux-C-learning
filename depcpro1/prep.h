/*预处理过程，定义全局变量，声明函数和结构体*/
/*头文件引用*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>      //？
#include <graphics.h>  //图形函数库


#define MAX_BOX 19

/*定义按键码,虚拟键值*/
#define VK_LEFT 0x4b00
#define VK_RIGHT 0x4d00
#define VK_DOWN 0x5000
#define VK_UP 0x4800
#define VK_ESC 0x011b
#define TIMER 0x1c

/*定义常量*/
#define BSIZE 20
#define Sys_x 160
#define Sys_y 25         /*显示方块界面的左上角坐标*/
#define Horizontal_boxs 10
#define Vertical_boxs 15     /*以方块为单位的长度*/
#define Begin_boxs_x Horizontal_boxes 2    /*第一个方块起始位置*/

#define EgColor 3   /*前景颜色*/
#define EgColor 0   /*背景颜色*/

#define LeftWin_x Sys_x+Horizontal_boxs*BSIZE+46     /*右边状态栏x坐标*/

#define false 0
#define true 1

/*移动的方向*/
#define MoveLeft 1
#define MoveRight 2
#define MoveDown 3
#define MoveRoll 4

/*定义全局变量*/
int current_box_numb;    /*保存当前方块编号*/
/*x,y保存方块当前坐标*/
int Curbox_x = Sys_x + Begin_boxs_x*BSIZE, Curbox_y = Sys_y;
int flag_newbox = false;   /*标记是否产生新方块*/
int speed = 0;            /*下落速度*/
int score = 0;             /*每等级所需要分数*/

/*游戏底板结构体*/
struct BOARD{
	int var;   /*状态只有0和1,1表示已被占用*/
	int color;   /*颜色编号*/
	}Table_board[Vertical_boxs][Horizontal_boxs];

/*
	游戏方块结构体
	方块都是在4*4大块内
	4bits表示一行，四行一共用两个字节
*/

struct SHAPE{
	char box[2];  /*2字节表示方块形状*/
	int color;  /*方块颜色*/
	int next;   /*下个方块编号，有19种*/
	};

/*
	SHAPE 结构数组
	初始化方块内容，定义MAX_BOX个SHAPE类型的结构数组，并初始化
*/
struct SHAPE shapes[MAX_BOX]=
{
	/*
	* *   * * *   * *      *
	* *   *         *  * * *
	* * *           * 
	*/
	{0x88,  0xc0,  CYAN,  1}，
	{0xe8,  0x0,   CYAN,  2}，
	{0xc4,  0x40,  CYAN,  3}，
	{0x2e,  0x0,   CYAN,  0}，
	
	/*
	*   *         * *  * * *
	*   * *       *        *
	* * * * * *   * 
	*/
	{0x44,  0xc0,  MAGENTA,  5}，
	{0x8e,  0x0,   MAGENTA,  6}，
	{0xc8,  0x80,  MAGENTA,  7}，
	{0xe2,  0x0,   MAGENTA,  4}，
	
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
	{0x4e,  0x0,   WHITE,  13}，
	{0x8c,  0x80,  WHITE,  14}，
	{0xe4,  0x0,   WHITE,  15}，
	{0x4c,  0x40,  WHITE,  12}，
	
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

/*指向原时钟中断处理过程入口的中断处理函数指针*/
void interrupt (*oldtimer)(void);

/*显示分数*/
void ShowScore(int score);

/*显示速度*/
void ShowSpeed(int speed);

/*帮助提示*/
void show_help(int xs, int ys);

/*实现新的时钟*/
void interrupt newtimer(void);

/*SetTimer设置新时钟处理过程*/
void SetTimer(void interrupt (*IntProc)(void));

/*KillTimer恢复原有的时钟处理过程*/
void KillTimer();

/*initialize初始化解码*/
void initialize(int x, int y, int m, int n);

/*DelFullRow删除满行，y设置删除的行数*/
int DelFullRow(int y);

/*setFullRow查询满行,调用上面的*/
void setFullRow(int t_boardy);

/*MkNextBox生成下一个游戏方块，返回方块号*/
int MkNextBox(int box_numb);

/*EraseBox消除方块*/
void EraseBox(int x, int y, int box_numb);

/*show_box显示一个方块*/
void show_box(int x, int y, int box_numb);

/*MoveAble获得移动方向*/
int MoveAble(int x, int y, int box_numb, int direction);