/*
 * pid.c
 *
 *  Created on: 2020年7月31日
 *      Author: 岑衎远
 */

#include "pid.h"
#include "SEEKFREE_MT9V03X.h"

int i=0;
int j=0;
int left[20];
int right[20];
int total;
int error;
int error_speed1;
int error_speed2;
int error_i1,error_i2;
int increase;
int out1;
int out2;
int Last_Error1;
int Last_Error2;
int last_Error;//上一次误差
int Previous_Error1;
int Previous_Error2;//上上次误差
float kp=35; //35
float ki=0;
float kd=0.6;//0.8
float kp1=3.8;//0.02
float ki1=0.01;//0.03
float kd1=0.0;//0.8
int front=40;
int width=80;
int line_mid=MT9V03X_W;

void PID_Increase(void)
{
    total=0;
    for(i=0;i<=19;i++)
    {
    left[i]=0;
    right[i]=0;
    }

    for (i=front+19;i>=front;i--)
    {
      for (j=line_mid;j>=1;j--)
      {
        if (BinaryImage[i][j]==0&&BinaryImage[i][j-1]==0&&BinaryImage[i][j+1]==255)
        {
          left[i-front]=j;
          break;
        }
        else
        {
          left[i-front]=1;
        }

      }
      for (j=line_mid;j<=MT9V03X_W-2;j++)
      {
        if (BinaryImage[i][j]==0&&BinaryImage[i][j-1]==255&&BinaryImage[i][j+1]==0)
        {
          right[i-front]=j;
          break;
        }
        else
        {
          right[i-front]=MT9V03X_W-2;
        }
      }
      if( left[i-front]!=1 && right[i-front]!=MT9V03X_W-2)
      {   width=(width+(right[i-front]-left[i-front]))/2;
          total=total+(left[i-front]+right[i-front])/2;
          line_mid=(left[i-front]+right[i-front])/2;
      }
      else if(left[i-front]==1&& right[i-front]!=MT9V03X_W-2)
      {
      	  total=total+right[i-front]-width/2;
      	 line_mid=right[i-front]-width/2;
      }
      else if(left[i-front]!=1&& right[i-front]==MT9V03X_W-2)
      {
          total=total+left[i-front]+width/2;
          line_mid=left[i-front]+width/2;
      }
      else
      {
    	  total=total+MT9V03X_W/2;


      }

    }



    error=total/20-MT9V03X_W/2;
    increase =  kp * (error)+ kd * (error  - last_Error);


     last_Error = error;



}

void speed_pid(int en1,int en2,int s)
{  Previous_Error1=Last_Error1;
   Previous_Error2=Last_Error2;
   Last_Error1=error_speed1;
   Last_Error2=error_speed2;

	error_speed1=s-en1;
	error_speed2=s-en2;


	out1 = out1+ kp1 * (error_speed1-Last_Error1)+ ki1 * (error_speed1)+kd1*(error_speed1+Previous_Error1-2*Last_Error1);
	out2 = out1+ kp1 * (error_speed2-Last_Error2)+ ki1 * (error_speed2)+kd1*(error_speed2+Previous_Error2-2*Last_Error2);

}
