#include <wiringPi.h>
#include <stdio.h>

#define SDI 0
#define RCLK 1
#define SRCLK 2

unsigned char code_L[8] = {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f};
unsigned char code_H[8] = {0xfc, 0xb4, 0xaf, 0xb4, 0xb4, 0xaf, 0xb4, 0xfc};

void init(void)
{
	pinMode(SDI, OUTPUT);
	pinMode(RCLK, OUTPUT);
	pinMode(SRCLK, OUTPUT);

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

void hc595_in(unsigned char dat)
{
	int i;

	for(i=0; i<8; i++) {
		digitalWrite(SDI, 0x80 & (dat << i));       
		digitalWrite(SRCLK, 1);
		digitalWrite(SRCLK, 0);
	}
}

void hc595_out()
{
	digitalWrite(RCLK, 1);
	delay(1);
	digitalWrite(RCLK, 0);
}

int main(void)
{
	int i;

	if(wiringPiSetup() == -1) {
		printf("setup wiringPi failed !");
		return 1;
	}

	init();

	while(1) {
		for(i=0; i<sizeof(code_H) ;i++) {
			hc595_in(code_L[i]);
			hc595_in(code_H[i]);
			hc595_out();
			
		}
	}
	return 0;
}