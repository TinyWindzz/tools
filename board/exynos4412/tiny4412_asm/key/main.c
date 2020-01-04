/*
* 程序说明
* 一上电，4个LED全亮，当某个按键被按下，则对应的LED熄灭（可同时按下多个键）
* 对应关系：KEY1-LED1，KEY2-LED2，KEY3-LED3，KEY4-LED4
*/
//按键对应的GPIO
#define GPX3CON (*(volatile unsigned int *)0x11000C60)
#define GPX3DAT (*(volatile unsigned int *)0x11000C64)

//LED对应的GPIO
#define GPM4CON (*(volatile unsigned int *)0x110002E0)
#define GPM4DAT (*(volatile unsigned int *)0x110002E4)

void delay(volatile int time)
{
	for(; time > 0; time-- )
	;
}

int main(void)
{
	unsigned long tmp = 0;
	unsigned char keyValue = 0;
	/*
	* GPX3_2-GPX3_5 设置为输入功能,用于检测按键引脚的状态
	*/
	tmp = GPX3CON;
	tmp &= ~(0xffff << 8);
	GPX3CON = tmp;

	/*
	* GPM4_0-GPM4_3 设置为输出功能,用于控制LED的亮灭
	*/
	tmp = GPM4CON;
	tmp &= ~0xffff;
	tmp |= 0x1111;
	GPM4CON = tmp;

	while(1)
	{
	//读按键引脚状态
	keyValue = GPX3DAT;
	keyValue = (keyValue & (0xf << 2)) >> 2;

		if(keyValue != 0xf) //说明有按键被按下，再详细判断是哪个按键被按下
		{
			delay(1000); //防抖

			keyValue = GPX3DAT;
			keyValue = (keyValue & (0xf << 2)) >> 2;

			GPM4DAT = ~keyValue; //设置LED亮、灭
		}
		else
		{
			GPM4DAT = 0x00;
		}
	}

	return 0;
}
