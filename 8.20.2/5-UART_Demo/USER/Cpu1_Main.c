#include "headfile.h"
#include "pid.h"
#include "key.h"
#include "Ks103.h"
#include "zf_uart.h"
#include "img.h"
#pragma section all "cpu1_dsram"
int16 encoder1;
int16 encoder2;//123
int16 run_flag;
extern float yuan_Angle,yuan_Angle1;
extern int yuan_flag;
extern int32 Road_Lenth;
extern float gyrox;
int LeftValue,RightValue,BothValue;
int LeftVal,RightVal,BothVal,FinalPWM_Left,FinalPWM_Right;
int16 SpeedPWM;
extern int last_error1;
int32 road;

int error1,all_error;
int32 speed1_power;
int32 speed2_power;
extern int Road_Angle,Road_Angle1;
int set_speed=330;

// slow_down  cross
#define RowMax	    120  //����
unsigned char LEndFlag  = 0;//��־λ
unsigned char MEndFlag  = 0;
unsigned char REndFlag  = 0;
int BlackEndM    = 0;
//int BlackEndL    = 0;
//int BlackEndR    = 0;


//cross
/*********define for CrossConduct**********/
unsigned char  CrossFlag  = 0;//ʮ�ֱ�־
unsigned char  LastCrossFlag  = 0;
unsigned char  LastLastCrossFlag  = 0;
unsigned char  CrossNumberFalg=0;
unsigned char  CloseLoopFlag=0;

/*********define for RecognitionObstacle**********/
unsigned char  ObstacleLfetRowStart=0;
unsigned char  ObstacleLfetColStart=0;
unsigned char  ObstacleLfetOkFlag=0;
unsigned char  ObstacleRightRowStart=0;
unsigned char  ObstacleRightColStart=0;
unsigned char  ObstacleRightOkFlag=0;


//lose and stop

int BlackPoint;
int BlackAllLose;
int lose_stop_flag;
extern int outpwm;
int limit_increase;
int limit_out=8000;
int error_limit=80; //60
int show_flag=1;
int adc_limit=140;
int left_pwm=400,right_pwm=400;//400
int16 adc_pwm;
int adc_error,adc_lasterror;
char adc_p1=1,adc_p2=1,adc_p3=5;
int32 out_distance;
extern int32 distance;


int stop_flag,ten_flag,ten_sequence,hightop;
int32 hightop_distance;
extern int stop_road;





int speed_flag,sq_flag;
float adc_p=40,adc_d=10;// 60
//int stop_num,stop_flag;
void reddistance(void);
void stop(void);
void NormalCrossConduct(void);
void slow_down( void );
void AllBlackPacking(void);
void core1_main(void)
{
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    //uart_init(UART_0, 9600, UART0_TX_P14_0, UART0_RX_P14_1);
    //�û��ڴ˴����ø��ֳ�ʼ��������
	lcd_init();
	adc_init(ADC_0, ADC0_CH0_A0);
	adc_init(ADC_0, ADC0_CH1_A1);
	adc_init(ADC_0, ADC0_CH2_A2);//ADC0_CH3_A3
	adc_init(ADC_0, ADC0_CH6_A6);
	//uart_init(UART_1, 115200, UART1_TX_P11_12, UART1_RX_P11_10);
    //uart_putstr(UART_1, "\n---uart test---\n");
    //�û��ڴ˴����ø��ֳ�ʼ��������
	printf("printf demo");
//	icm20602_init_spi();
	 pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
	 //pit_interrupt_ms(CCU6_0, PIT_CH1, 100);
	gtm_pwm_init(MOTOR1_A, 17000, 0);
	gtm_pwm_init(MOTOR1_B, 17000, 0);
	gtm_pwm_init(MOTOR2_A, 17000, 0);
	gtm_pwm_init(MOTOR2_B, 17000, 0);
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	gpt12_init(GPT12_T5, GPT12_T5INB_P10_3, GPT12_T5EUDB_P10_1);
	//key_init();
	//icm20602_init_spi();

    enableInterrupts();
    //icm20602_init_spi();
    //oled_init();
    mt9v03x_init();
   // int* histogram;
    //int* histogram;
    unsigned char Threshold2;
    while (TRUE)
    {    //systick_start(STM1);
//     	adc_get(ADC_0, ADC0_CH0_A0,ADC0_CH1_A1,ADC0_CH2_A2,ADC0_CH3_A3, ADC_8BIT);
//
      	//get_icm20602_gyro_spi();
//      //	time1=systick_getval_us(STM1);
      	key_get();
//      	lcd_showint16(80,7,ad_value1);
//     	lcd_showint16(80,6,ad_value2);
//      	lcd_showint16(80,5,ad_value3);
//     	lcd_showint16(80,4,ad_value4);
//      	lcd_showint16(80,3,yuan_flag);
//    	lcd_showint16(80,3,yuan_flag);




//      	lcd_showint16(80,6,Road_Lenth);
//      	lcd_showint16(80,5,yuan_Angle);
//     	lcd_showint16(80,4,yuan_Angle1);
//     // 	lcd_showint16(80,7,speed_flag);
//      	lcd_showint16(80,6,Road_Angle);
//      	lcd_showint32(80,5,road,5);
//        lcd_showint16(80,2,set_speed);
////     lcd_showint16(80,4,Road_Angle1);
//       lcd_showint16(80,3,error1);
//        // printf("%d\n",icm_gyro_x);
////	    lcd_showfloat(80,4,adc_d,2,2);
////	    lcd_showfloat(80,3,adc_p,3,2);
////     lcd_showfloat(80,3,adc_p,3,2);
//	    lcd_showint32(80,1,stop_road,6);

//	    lcd_showint16(80,1,icm_gyro_x);
//       lcd_showfloat(0,0,adc_p,2,1);

//       lcd_showfloat(55,0,adc_d,2,1);
 //   	lcd_showint16(90,2,ad_value3);
//
//	    lcd_showint32(80,2,adc_error,3);
//        lcd_showint32(80,1,speed1_power,7);
//	    lcd_showint32(80,0,speed2_power,7);
//////	    lcd_showstr(0,7,"stop_flag");
////   	lcd_showstr(0,7,"ad_value1");
////	    lcd_showstr(0,6,"RAngle");
// 	    lcd_showstr(0,2,"error1");
// 	    lcd_showstr(0,1,"power1");
// 	    lcd_showstr(0,0,"power2");
////	    lcd_showstr(0,4,"RAngle1");
////	    lcd_showstr(0,4,"adc_d");
//	    lcd_showstr(0,3,"error1");
////	    lcd_showstr(0,3,"adc_p");
//	    lcd_showstr(0,4,"adc_d");
//	    lcd_showstr(0,3,"ad_value1");
//	    lcd_showstr(0,1,"distance");
//	    lcd_showstr(0,0,"sd2");
//	    //lcd_showstr(0,0,"RAngle1");
//	    lcd_showstr(0,2,"set_speed");
//	    lcd_showstr(0,1,"stop_road");
//	    lcd_showstr(0,4,"AllLose");
//	 	lcd_showint16(80,4 ,AllLose);
	    if(ad_value1>230)
	        {
	    	stop_flag=1;



	        }
	    if (mt9v03x_finish_flag==1)
	    {  // stop();

	    	//histogram = Histo(*mt9v03x_image);
//	    	Threshold2=adapt_otsuThreshold( mt9v03x_image[ROW][COL],  COL, ROW);
	    //Threshold2 = OtsuThreshold(histogram);
	    				//Threshold2 = IterationThreshold(histogram);
//	    				free(histogram);
//	    				histogram=NULL;
	    			   	//Image_Binary(*mt9v03x_image, *img,Threshold2);
     	adapt_otsuThreshold(mt9v03x_image[0],COL ,  ROW, &Threshold2);
	    	Image_Binary(*mt9v03x_image, *Image_Array,Threshold2);
	    	Search_Center_Blackline();
	    		   //	slow_down( );
//	    		   	NormalCrossConduct();
	    		   	AllBlackPacking();
//		   	lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
//		   	lcd_displayimage032(*Image_Array, MT9V03X_W, MT9V03X_H);
//		    for (int i=MT9V03X_H;i>=80;i--)
//		        {
//		       		    	if (MiddleLine[i]>128) MiddleLine[i]=128;
//		       		   	    	 lcd_drawpoint((uint8)MiddleLine[i],i,RED);
//
//		       		   	          }
	    	all_error=0;
		   	for (int i=40;i<=50;i++)  //4050
		   	{
		   		all_error=all_error+MiddleLine[i];
		   	}

//		   	for (int i=35;i<=44;i++)
//		   			   	{
//		   			   		error1=error1+0.5*MiddleLine[i];
//		   			   	}

		   	error1=80-(all_error/11);
		   	lcd_showint16(80,2 ,error1);

	    	mt9v03x_finish_flag=0;

	    }
   if (key1_flag)
  {


	speed_flag++;
	if(speed_flag>2)
	{speed_flag=0;}

	key1_flag=0;
  }

        //	        speed1_power = out1+increase;
        //	        speed2_power = out2-increase;


  if(key2_flag)
  {
	  sq_flag++;
	  if(sq_flag>2)
	  {
		  sq_flag=0;

	  }
	  key2_flag=0;

  }
  if(key3_flag)
  {

	  switch(sq_flag)
	  {  case 0:adc_p=adc_p+1;break;
	      case 1:adc_d=adc_d+1;break;
	      case 2:set_speed=set_speed+10;break;

	  }

	  key3_flag=0;
  }

  if(key4_flag)
  {

	  switch(sq_flag)
	  {  case 0:adc_p=adc_p-1;break;
	      case 1:adc_d=adc_d-1;break;
	      case 2:set_speed=set_speed-10;break;

	  }
	  key4_flag=0;

  }





    	

    }
}

void slow_down( void )
{    	MEndFlag = 0;
        BlackEndM=0;
        BlackEndL=0;
        LEndFlag=0;
        BlackEndR=0;
        REndFlag=0;
	for (int i = RowMax-10; i >= 3 ; i--)
	{
		if(Image_Array[i][ColumnMax/2] == White_Point && !MEndFlag )//!MEndFlag=1 //40
	        {
			BlackEndM++;//�к��߽�����
	        }
		else if(i > 1 && Image_Array[i-1][ColumnMax/2] == Black_Point && Image_Array[i-2][ColumnMax/2] == Black_Point)//���������Ǻ�ɫ
	        {
			MEndFlag = 1;
	        }



	if(Image_Array[i][ColumnMax/4] == White_Point && !LEndFlag )//20
        {
		BlackEndL++;//����߽�����
        }
	else if(i > 1 && Image_Array[i-1][ColumnMax/4] == Black_Point && Image_Array[i-2][ColumnMax/4] == Black_Point)
        {
		LEndFlag = 1;
        }
	if(Image_Array[i][ColumnMax*3/4] == White_Point && !REndFlag )//60
        {
		BlackEndR++;//�Һ��߽�����
	}
	else if(i > 1 && Image_Array[i-1][ColumnMax*3/4] == Black_Point && Image_Array[i-2][ColumnMax*3/4] == Black_Point)
        {
		REndFlag = 1;
        }
	 }

	 if(yuan_flag!=1 &&run_flag==1)
	 {
	if(BlackEndM<50)
	{
		set_speed=200;//180 200
	 adc_p=40,adc_d=10;//   100 30   60  15

	}
	else {

		set_speed=400;
		 adc_p=40,adc_d=10;// 60

	}
	 }




}



//��ʮ�ֽ���ʶ��ͽ������⴦��
void NormalCrossConduct(void)
{
     unsigned char i;

     LastLastCrossFlag=LastCrossFlag;//��¼���ϴ��Ƿ���ʮ��
     LastCrossFlag=CrossFlag;//��¼��һ���Ƿ���ʮ��
     CrossFlag=0;//����


   if((AllLose>=15))//����ͬʱ����
      {
             CrossFlag=1;//���ʮ��
      }
      if(CrossFlag)
       {


       if((BlackEndM>=BlackEndL)&&(BlackEndM>=BlackEndR))//�м�������
       {
         for(int i=40;i<=50;i++)
         {
          MiddleLine[i]=80;//ֱ��
         }
       }
       else if((BlackEndL>BlackEndM)&&(BlackEndL>BlackEndR))//������߰׵���࣬����ƫ���ˣ�������
       {
          for(int i=40;i<=50;i++)
          {
                  MiddleLine[i]=70;
          }
       }
       else if((BlackEndR>BlackEndM)&&(BlackEndR>BlackEndL))//�����ұ߰׵���࣬����ƫ���ˣ�������
       {
         for(int i=40;i<=50;i++)
         {

              MiddleLine[i]=90;
          }
         }
       }


    // IsOrNotCrossLoop();

}


void AllBlackPacking()
{
  BlackAllLose = 0;
  for (int i=100;i>80;i--)
  {
    BlackPoint = 0;
    for(int j=140;j>20;j--)
    {
      if (Image_Array[i][j]==Black_Point)
      {
        BlackPoint++;
      }
    }
      if (BlackPoint>=100)
      {
        BlackAllLose++;
      }
  }
  if (BlackAllLose>=20)
  {
	  lose_stop_flag=1;
  }
}

void reddistance(void)
{  ten_flag=0;
	  if(ad_value1>230)
		        {
		    	ten_flag=1;



		        }


		    if(ten_flag==1 && ten_sequence==0)
		    {
		    	hightop=1;


		    }

		    if(ten_flag==1 && hightop_distance>=10000)
		    {
		    	stop_flag=1;


		    }





}


#pragma section all restore
