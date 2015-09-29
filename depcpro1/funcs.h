/*函数声明*/
#include "prep.h"

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
