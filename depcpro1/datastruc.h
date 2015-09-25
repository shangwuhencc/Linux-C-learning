#ifndef DATASTRUC_H
#define DATASTRUC_H

#define MAX_BOX 19

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