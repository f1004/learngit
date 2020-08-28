#include "headfile.h"
#pragma section all "cpu0_dsram"
int SpeedPwm1,SpeedPwm2;
int speed1,speed2,Set_Speed=18000,Speed_Kp=0.1;
void speed_control_init(void);
int speed_limit(int);
int speed_pid(int p,int i,int d,int error1);
int direciton_pid(int p,int i,int d,int error1);
void speed_run(void);
int pwm_left,pwm_right;
void speed_get(int *sp1,int *sp2);
int p1,i1,d1,p2,i2,d2,error1,error2;

int a,b,c;
int core0_main(void)
{
	speed_control_init();
	lcd_init();
    a=1,b=1,c=1;
    while (TRUE)
    {
//    	speed_get(&speed1,&speed2);
//    	error1=speed1-Set_Speed;
//    	error1=speed1-Set_Speed;
//    	SpeedPwm1=speed_pid(p1,i1,d1,error1);
//    	SpeedPwm2=speed_pid(p2,i2,d2,error2);
//
//    	pwm_duty(ATOM0_CH6_P02_6, SpeedPwm1);
//    	pwm_duty(ATOM0_CH7_P02_7, SpeedPwm2);




    	 scanf("%d %d %d",&a,&b,&c);
    	 lcd_showint8(0,0,a);
    	 lcd_showint8(1,1,b);
    	 lcd_showint8(2,2,c);
    }
}



void speed_control_init(void)
{
disableInterrupts();
	get_clk();//鑾峰彇鏃堕挓棰戠巼  鍔″繀淇濈暀

    //鐢ㄦ埛鍦ㄦ澶勮皟鐢ㄥ悇绉嶅垵濮嬪寲鍑芥暟绛�
	//浣跨敤CCU6_0妯″潡鐨勯�氶亾0 浜х敓涓�涓� 100ms鐨勫懆鏈熶腑鏂�
	pit_interrupt_ms(CCU6_0, PIT_CH0, 100);
	gtm_pwm_init(ATOM0_CH6_P02_6, 10000, 0);
	gtm_pwm_init(ATOM0_CH4_P02_4, 10000, 0);//ATOM 0妯″潡鐨勯�氶亾4 浣跨敤P02_4寮曡剼杈撳嚭PWM  PWM棰戠巼50HZ  鍗犵┖姣旂櫨鍒嗕箣0/GTM_ATOM0_PWM_DUTY_MAX*100  GTM_AT
	gtm_pwm_init(ATOM0_CH7_P02_7, 10000, 0);
	gtm_pwm_init(ATOM0_CH5_P02_5, 10000, 0);
	pwm_duty(ATOM0_CH4_P02_4, 0);//璁剧疆鍗犵┖姣斾负鐧惧垎涔�5000/GTM_ATOM0_PWM_DUTY_MAX*100
	pwm_duty(ATOM0_CH6_P02_6, 2000);
	pwm_duty(ATOM0_CH3_P02_3, 0);//璁剧疆鍗犵┖姣斾负鐧惧垎涔�5000/GTM_ATOM0_PWM_DUTY_MAX*100
	pwm_duty(ATOM0_CH7_P02_7, 2000);
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);// encoder
	gpt12_init(GPT12_T3,GPT12_T3INA_P02_6, GPT12_T3EUDA_P02_7);
	//涓柇鍑芥暟鍦╥sr.c涓� 鍑芥暟鍚嶇О涓篶c60_pit_ch0_isr
	//涓柇鐩稿叧鐨勯厤缃弬鏁板湪isr_config.h鍐�
	//鍙厤缃弬鏁版湁 CCU6_0_CH0_INT_SERVICE 鍜� CCU6_0_CH0_ISR_PRIORITY
	//CCU6_0_CH0_INT_SERVICE 涓柇鏈嶅姟鑰咃紝琛ㄧず鏀逛腑鏂敱璋佸鐞嗭紝0:CPU0 1:CPU1 3:DMA  涓嶅彲璁剧疆涓哄叾浠栧��
	//CCU6_0_CH0_ISR_PRIORITY 涓柇浼樺厛绾� 浼樺厛绾ц寖鍥�1-255 瓒婂ぇ浼樺厛绾ц秺楂� 涓庡钩鏃朵娇鐢ㄧ殑鍗曠墖鏈轰笉涓�鏍�

	//闇�瑕佺壒澶囨敞鎰忕殑鏄�  涓嶅彲浠ユ湁浼樺厛绾х浉鍚岀殑涓柇鍑芥暟 姣忎釜涓柇鐨勪紭鍏堢骇閮藉繀椤绘槸涓嶄竴鏍风殑
    enableInterrupts();



}


void speed_get(int *sp1,int *sp2)
{ int sp3,sp4;
	sp3 = gpt12_get(GPT12_T2);
	gpt12_clear(GPT12_T2);

	sp4 = gpt12_get(GPT12_T3);
	gpt12_clear(GPT12_T3);
   sp1=&sp3;
   sp2=&sp4;



}

int speed_limit(int SPW)
{  
  if(SPW>3000)
    {SPW=3000;}
  if(SPW<-3000)
   {SPW=-3000;}
  


 return SPW;

}
int p, i, d, error;
int speed_pid(int p,int i,int d,int er1)
{   int p1;
	static int error3;
	static int error2;
    error3=error2;
	error2=er1;

    p1=p*er1+i*(error3+error2+er1)+d*(er1-error2);
    return p1;


}
int direciton_pid(int p,int i,int d,int er1)
{
	int p1;
	static int error3;
	static int error2;
	error3=error2;
    error2=er1;
    p1=p*er1+i*(error3+error2+er1)+d*(er1-error2);
	return p1;
}
void speed_run(void)
{

}



#pragma section all restore
