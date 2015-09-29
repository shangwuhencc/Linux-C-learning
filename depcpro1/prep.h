/*预处理过程，定义全局变量，声明函数和结构体*/
/*头文件引用*/
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>      //？
#include <graphics.h>  //图形函数库
#include "datastruc.h";   /*底板结构、方块结构、方块初始化*/

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

/*指向原时钟中断处理过程入口的中断处理函数指针*/
void interrupt (*oldtimer)(void);
