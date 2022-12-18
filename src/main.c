/**
 * reference:
 * original author: Husamuldeen <https://github.com/hussamaldean>
 */
#include "ADXL.h"
#include "I2C.h"
#include "delay.h"
extern void SysClockConfig(void);
// #include "stdio.h"

#define BREATH_THRESHOLD (10)
//#define BREATH_ALERT_TIME_SEC (10)
#define BREATH_ALERT_TIME (5000)

accleration_values_t accleration_values;
volatile int timerstarted;
volatile long systickcount;

int check_difference(int xa, int xm);
void alert();

int main(void)
{
	//int i = 0;
	uint8_t hasbreathflag = 1;
	int xm=0, ym=0, zm=0;
	long nobreathframecount = 0;
	timerstarted = 0;
	systickcount = 0;
	I2C_Init();
	adxl345_init(accl_2g);
	while(1)
		{
			int xa, ya, za;
			adxl345_update();
			adxl345_get_values(&accleration_values);
			//printf("%0.5f, %0.5f, %0.5f\n",accleration_values.ax,accleration_values.ay,accleration_values.az);
			xa = (int)accleration_values.ax;
			ya = (int)accleration_values.ay;
			za = (int)accleration_values.az;

			hasbreathflag = (check_difference(xa,xm)*check_difference(ya,ym)*check_difference(za,zm));
			if (hasbreathflag>0) nobreathframecount = 0;
			else nobreathframecount += 1;
			if(nobreathframecount >= BREATH_ALERT_TIME) alert();
			/*if(hasbreathflag>0) {
				xm = xa; ym = ya; zm = za;
				if(timerstarted != 0) endTimer();
			}
			else {
				if(timerstarted == 0) startTimer(1);//startTimer(BREATH_ALERT_TIME_SEC);
				else {
					printf("%lx\n",getTimerEnded());
					//if(getTimerEnded()!=0) alert();
				}
			}*/

			//i += 1;
			//if(i==50) {printf("%d, %d, %d\n",xa,ya,za); i=0;}
			//printf("%d: %d, %d, %d\n",i, xa,ya,za);
			delay(20);

		}

}





int check_difference(int xa, int xm){
	return xa>xm ? 
		(xa-xm>BREATH_THRESHOLD ? 1 : 0) :
		(xm-xa>BREATH_THRESHOLD ? 1 : 0);
}

void alert(){
	printf("ALERT\n");
	//while(1) printf("ALERT\n");
}
