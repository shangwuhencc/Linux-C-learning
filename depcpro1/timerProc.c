/*时钟中断处理*/

void interrupt newtimer(void){
	(*oldtimer)();
	TimerCounter++;
	}
	
/*设置新的时钟中断处理过程*/

void SetTimer(void interrupt(*IntProc)(void)){
	oldtimer = getvect(Timer);  /*获取中断号为TIMER的中断处理函数的入口地址*/
	disable();   /*设置新的时钟中断处理过程中，禁止所有中断*/
	setvect(TIMER, IntProc);
	enable();   /*开启中断*/
	}

/*恢复原有的时钟中断处理过程*/
void KillTimer(){
	disable();
	setvect(TIMER, oldtimer);
	enable();
	}