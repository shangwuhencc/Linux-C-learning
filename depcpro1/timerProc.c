/*ʱ���жϴ���*/

void interrupt newtimer(void){
	(*oldtimer)();
	TimerCounter++;
	}
	
/*�����µ�ʱ���жϴ������*/

void SetTimer(void interrupt(*IntProc)(void)){
	oldtimer = getvect(Timer);  /*��ȡ�жϺ�ΪTIMER���жϴ���������ڵ�ַ*/
	disable();   /*�����µ�ʱ���жϴ�������У���ֹ�����ж�*/
	setvect(TIMER, IntProc);
	enable();   /*�����ж�*/
	}

/*�ָ�ԭ�е�ʱ���жϴ������*/
void KillTimer(){
	disable();
	setvect(TIMER, oldtimer);
	enable();
	}