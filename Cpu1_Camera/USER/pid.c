/*
 * pid.c
 *
 *  Created on: 2020年7月31日
 *      Author: 岑衎远
 */

#include "pid.h"
#include "SEEKFREE_MT9V03X.h"
#include "common.h"
#include "Vadc/Adc/IfxVadc_Adc.h"
#include "zf_assert.h"
#include "zf_vadc.h"
#include "stdio.h"

int i=0;
int j=0;
int left[20];
int right[20];
int mid[20];
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
uint8 Image_Array[MT9V03X_H][MT9V03X_W];



void PID_Increase(void)
{
//    total=0;
//    for(i=0;i<=19;i++)
//    {
//    left[i]=0;
//    right[i]=0;
//    }
//
//    for (i=front+19;i>=front;i--)
//    {
//      for (j=line_mid;j>=1;j--)
//      {
//        if (BinaryImage[i][j]==0&&BinaryImage[i][j-1]==0&&BinaryImage[i][j+1]==255)
//        {
//          left[i-front]=j;
//          break;
//        }
//        else
//        {
//          left[i-front]=1;
//        }
//
//      }
//      for (j=line_mid;j<=MT9V03X_W-2;j++)
//      {
//        if (BinaryImage[i][j]==0&&BinaryImage[i][j-1]==255&&BinaryImage[i][j+1]==0)
//        {
//          right[i-front]=j;
//          break;
//        }
//        else
//        {
//          right[i-front]=MT9V03X_W-2;
//        }
//      }
//      if( left[i-front]!=1 && right[i-front]!=MT9V03X_W-2)
//      {   width=(width+(right[i-front]-left[i-front]))/2;
//          total=total+(left[i-front]+right[i-front])/2;
//          line_mid=(left[i-front]+right[i-front])/2;
//          mid[i-front]=line_mid;
//      }
//      else if(left[i-front]==1&& right[i-front]!=MT9V03X_W-2)
//      {
//      	  total=total+right[i-front]-width/2;
//      	 line_mid=right[i-front]-width/2;
//      	 mid[i-front]=line_mid;
//      }
//      else if(left[i-front]!=1&& right[i-front]==MT9V03X_W-2)
//      {
//          total=total+left[i-front]+width/2;
//          line_mid=left[i-front]+width/2;
//          mid[i-front]=line_mid;
//      }
//      else
//      {
//    	  total=total+MT9V03X_W/2;
//    	  mid[i-front]=MT9V03X_W;
//
//
//      }
//
//    }
//
//
//
//    error=total/20-MT9V03X_W/2;
//    increase =  kp * (error)+ kd * (error  - last_Error);
//
//
//     last_Error = error;



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


int adc_get(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res)
{


    int n=60;  //存放数组a中元素的个数
    int i;  //比较的轮数
    int j;  //每轮比较的次数
    int buf;  //交换数据时用于存放中间数据
    int a[60];
    for (i=0; i<n-1; ++i)  //比较n-1轮
       {   a[i] = adc_convert(vadc_n, vadc_chn, vadc_res);

       }
    for (i=0; i<n-1; ++i)  //比较n-1轮
       {
           for (j=0; j<n-1-i; ++j)  //每轮比较n-1-i次,
           {

               if (a[j] < a[j+1])
               {
                   buf = a[j];
                   a[j] = a[j+1];
                   a[j+1] = buf;
               }
           }
       }
return a[0];

}




int   MiddleLine[RowMax+1];
int   RightEdge[RowMax+1];
int   LeftEdge[RowMax+1];
int   Width[RowMax+1]={0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,
		0,0,0,47,49,51,53,55,57,59,60,
		62,64,66,68,70,72,74,76,78,79,
		81,83,85,87,89,91,93,95,97,98,
		100,102,104,106,108,110,112,114,116,117,
		119,121,123,125,127,129,131,133,135,136,
		138,140,142,144,146,148,150,152,154,155,
		157,159,160,160,160,160,160,160,160,160,
		160,160,160,160,160,160,160,160,160,160,
		160,160,160,160,160,160,160,160,160,160,
		160,160,160,160,160,160,160,160,160,160};//
//3,13,14,15,16,17,17,18,19,20,
//        21,22,23,24,25,26,27,28,28,29,
//        30,31,32,32,33,34,35,36,37,38,
//        39,40,40,41,42,43,44,44,45,46,47,
//        48,49,50,51,52,52,53,54,55,55,56,
//        57,58,59,60,61,62,62,63,64,65,66,
//        98,99,100,101,102,103,104,105,106,107,108,
//        109,110,111,112,113,114,115,116,117,118,119,
//        120,121,122,123,124,125,126,127,128,129,130,
//        131,132,133,134,135,136,137,138,139,140,141,
//        142,143,144,145,146,147,148,149,150,152,154,
//        155,156
int   MidPri         = 80;
int   LastLine       = 0;
float AvaliableLines = 0;
int   LeftLose       = 0;
int   RightLose      = 0;
int   AllLose        = 0;
int   LeftLoseStart  = 0;//记录左边丢线的开始行
int   RightLoseStart = 0;//记录右边边丢线的开始行
int   WhiteStart     = 0;


/*********define for GetBlackEndParam**********/
int BlackEndMR      = 0;
int BlackEndML      = 0;
int BlackEndLL      = 0;
int BlackEndRR      = 0;
int BlackEndL       = 0;
//int BlackEndM       = 0;
int BlackEndR       = 0;
int BlackEndMaxMax  = 0;
int BlackEndMax     = 0;
int DropRow         = 0;

/*********define for FindInflectionPoint()**********/

int RightInflectionPointRow=0;
int RightInflectionPointCol=0;
int LeftInflectionPointRow=0;
int LeftInflectionPointCol=0;
unsigned char RightInflectionPointFlag=0;
unsigned char LeftInflectionPointFlag=0;
unsigned char LeftInflectionPointSecondFlag=0;
unsigned char RightInflectionPointSecondFlag=0;
unsigned char LoopFlag=0;
unsigned char LoopRightOkFlag=0;
unsigned char LoopLeftOkFlag=0;
unsigned int StartRow=0;
unsigned int StartCol=0;
unsigned char MilldleBlack=0;
unsigned int LoopTop=0;
unsigned int LoopRightBorderLose=0;
unsigned int LoopLeftBorderLose=0;
int LoopBorttomFlag=0;
int LoopBorttomRow=0;
int LoopMilldleRow=0;
unsigned int LoopMilldleFlag=0;
unsigned int LoopTopRow=0;
unsigned int LoopLeft=0;
unsigned int MilldlePonit=0;
unsigned int LoopRight=0;
unsigned int LoopRightR=0;
unsigned int LoopLeftL=0;
int BigLoopLeftUp[60];
int BigLoopRightUp[60];
int BigLooptUp[80];
unsigned int LeftUpExitFlag=0;
unsigned int RightUpExitFlag=0;
unsigned int  ExitFlag=0;
unsigned int  LeftExitFlag=0;
unsigned int  RightExitFlag=0;;
unsigned char ClearLoopControlFlag=0;
unsigned char LoopRightControlFlag=0;
unsigned char LoopLeftControlFlag=0;
int MotivateLoopDlayFlagR=0;
int MotivateLoopDlayFlagL=0;
unsigned char InLoopLeftInflectionPointFlag=0;
unsigned int InLoopLeftInflectionPointRow=0;
unsigned char MotivateLoopDlayFlagLOK=0;
unsigned char MotivateLoopDlayFlagROK=0;
unsigned char OpenLoopExitRepairFlagL=0;
unsigned char OpenLoopExitRepairFlagR=0;
unsigned char InLoopRightInflectionPointFlag=0;
unsigned int  InLoopRightInflectionPointRow=0;
unsigned char BreakEndL=0;
unsigned char BreakEndLFlag=0;
unsigned char BreakEndR=0;
unsigned char BreakEndRFlag=0;
unsigned char BreakStartL=0;
unsigned char BreakStartLFlag=0;
unsigned char BreakStartR=0;
unsigned char BreakStartRFlag=0;

int  WhiteNum = 0;

//设置中线，左线，右线的初始化值
//设置每一行对应的赛道宽度
//本文件内不调用


//全行扫描和边缘结合提取赛道的中线
//前十行全行扫描
//后面50行，根据上一行的寻线情况来决定当前行的寻线方式和起点
//外部调用
void SetInitVal()
{
  int i;

  for(i=0;i<RowMax;i++)//赋初值
  {
      RightEdge[i]  = ColumnMax;
      LeftEdge[i]   = 0;
      MiddleLine[i] = ColumnMax/2;

  }

}

void Search_Center_Blackline(void)
{
  int i,j,jj;
  LeftEdge[RowMax] = 0;
  RightEdge[RowMax] = ColumnMax;
  LeftLose = 0;
  RightLose = 0;
  AllLose = 0;
  WhiteNum = 0;
  AvaliableLines = 0;

  SetInitVal();
  for (i = RowMax - 1; i > RowMax - 20; i--)  //搜索底下20行
  {
    if (i == RowMax - 1)   //第一行取中点，后面用上一行的中点作为扫描中点
    {
      j = MidPri;
    }else
    {
      j = MiddleLine[i+1];
    }
    if (j <= 2)
    {
       j = 2;
    }
    while (j >= 2)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j-1] == Black_Point && Image_Array[i][j-2] == Black_Point)
      {
        LeftEdge[i] = j;
        break;
      }
      j--;
    }
    if (i == RowMax - 1)     //右边处理同上
    {
      j = MidPri;
    }
    else
    {
      j = MiddleLine[i+1];
    }
    if (j >= ColumnMax - 3)
    {
      j = ColumnMax-3;
    }
    while (j <= ColumnMax - 3)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j+1] == Black_Point && Image_Array[i][j+2] == Black_Point)
      {
        RightEdge[i] = j;
        break;
      }
      j ++;
    }
    if (LeftEdge[i] != 0 && RightEdge[i] != ColumnMax)
    {
      MiddleLine[i] = (LeftEdge[i] + RightEdge[i])/2;
    }
    else if (LeftEdge[i] != 0 && RightEdge[i] == ColumnMax)
    {
      RightLose ++;      //记录右丢线次数

      if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i+1] - LeftEdge[i+1] + 1))  //突变
      {
        MiddleLine[i] = MiddleLine[i+1];
      }else
      {
        MiddleLine[i] = LeftEdge[i] + Width[i]/2;
      }
    }
    else if (LeftEdge[i] == 0 && RightEdge[i] != ColumnMax)
    {
      LeftLose ++;        //记录左丢线次数

      if ((RightEdge[i] - LeftEdge[i]) >= (RightEdge[i+1] - LeftEdge[i+1] + 1))
      {
        MiddleLine[i] = MiddleLine[i+1];
      }else
      {
        MiddleLine[i] = RightEdge[i] -  Width[i]/2;     //补半宽
      }
    }
    else if (LeftEdge[i] == 0 && RightEdge[i] == ColumnMax)    //都丢线
    {
      AllLose ++;

    if (i == RowMax -1)
    {
      MiddleLine[i] = MidPri;
    }else
    {
      MiddleLine[i] = MiddleLine[i+1];
    }
    }
    if (MiddleLine[RowMax-1] > 140)
    {
      MidPri = 140;
    }
    else if(MiddleLine[RowMax-1] < 20)
    {
      MidPri = 20;
    }else
    {
      MidPri = MiddleLine[RowMax-1];     //记录本帧图像第127行的中线值，作为下一幅图像的127行扫描起始点
    }
//    lcd_drawpoint(LeftEdge[i],i,BLUE);
//    lcd_drawpoint(RightEdge[i],i,GREEN);
//    lcd_drawpoint(MiddleLine[i],i,RED);

  }

  for (i =RowMax-20; i > 0; i--)
  {
    if (LeftEdge[i+1] != 0 && RightEdge[i+1] != ColumnMax)
    {
      j = ((LeftEdge[i+1]+15) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+15);//先找左边界
      jj = ((LeftEdge[i+1]-5) <= 1)? 1:(LeftEdge[i+1]-5);
    while(j >= jj)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j-1] == Black_Point)
      {
        LeftEdge[i] = j;
        break;
      }
      j--;
    }
      j = ((RightEdge[i+1]-15) <= 1)? 1:(RightEdge[i+1]-15); //在找右边界
         jj = ((RightEdge[i+1])+5) >= ColumnMax-2 ? ColumnMax-2:(RightEdge[i+1]+5);
    while(j <= jj)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j+1] == Black_Point)
      {
        RightEdge[i] = j;
        break;
      }
      j++;
    }
  }
    else if(LeftEdge[i+1] != 0 && RightEdge[i+1] == ColumnMax)    //只找到左边界
    {
      j = ((LeftEdge[i+1]+15) >= ColumnMax-2)? ColumnMax-2 : (LeftEdge[i+1]+15);
      jj = ((LeftEdge[i+1-5]) <= 1) ? 1 : (LeftEdge[i+1]-5);
    while(j >= jj)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j-1] == Black_Point)
      {
        LeftEdge[i] = j;
        break;
      }
      j--;
    }
      j = MiddleLine[i+1];
    if(j >= ColumnMax-2)
    {
      j = ColumnMax-2;
    }
    while (j <= ColumnMax-2)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j+1] == Black_Point)
      {
        RightEdge[i] = j;
        break;
      }
      j++;
    }
    }
    else if (LeftEdge[i+1] == 0 && RightEdge[i+1] != ColumnMax)   //只找到右边界
    {
      j = ((RightEdge[i+1]-15)<=1)?1:( RightEdge[i+1]-15);
      jj = ((RightEdge[i+1]+5) >= ColumnMax-2)?ColumnMax-2:(RightEdge[i+1]+5);
    while(j <= jj)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j+1] == Black_Point)
      {
        RightEdge[i] = j;
        break;
      }
      j++;
    }
      j = MiddleLine[i+1];
    if (j < 2)
    {
      j = 2;
    }
    while (j >= 2)
    {
      if (Image_Array[i][j] == White_Point && Image_Array[i][j-1] == Black_Point)
      {
        LeftEdge[i] = j;
        break;
      }
      j--;
    }
    }
    else if (LeftEdge[i+1] == 0 && RightEdge[i+1] == ColumnMax)
    {
      j = MiddleLine[i+1];
      while (j >=1)
      {
        if (Image_Array[i][j] == White_Point && Image_Array[i][j-1] == Black_Point)
        {
          LeftEdge[i] = j;
          break;
        }
        j--;
      }
      j = MiddleLine[i+1];
      while (j <= ColumnMax-2)
      {
        if (Image_Array[i][j] == White_Point && Image_Array[i][j+1] == Black_Point)
        {
          RightEdge[i] = j;
          break;
        }
        j++;
      }
    }
    if ((RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+1))   //不满足畸变
    {
      MiddleLine[i] = MiddleLine[i+1];
    }
    else
    {
      if (LeftEdge[i] != 0 && RightEdge[i] != ColumnMax)
      {
        MiddleLine[i] = (LeftEdge[i]+RightEdge[i])/2;
        if (MiddleLine[i]-MiddleLine[i+1]>12 && ((abs(LeftEdge[i]-LeftEdge[i+1]>5)||abs(RightEdge[i]-RightEdge[i+1]>5)))&& i >= 64)   //中线向右（数值待定）
        {
          uint8 ii = i;

          while(1)
          {
            MiddleLine[ii+1] = MiddleLine[ii]-1;
            ii++;
            if (ii>=80||(MiddleLine[ii]-MiddleLine[ii+1]<=1))
            {
              break;
            }
          }
        }
        if ((MiddleLine[i+1]-MiddleLine[i]>8)&&((abs(LeftEdge[i]-LeftEdge[i+1]>3)||abs(RightEdge[i]-RightEdge[i+1]>3)))&&i>=64)
        {
          uint8 ii = i;
          while(1)
          {
            MiddleLine[ii+1] = MiddleLine[ii]+1;
            ii++;
            if(ii>=80||MiddleLine[ii+1]-MiddleLine[ii]<=1)
            {
              break;
            }
          }
        }
      }
      else if (LeftEdge[i] != 0 && RightEdge[i] ==ColumnMax)
      {
        RightLose++;

        if (LeftEdge[i+1] != 0)
        {
          MiddleLine[i] = MiddleLine[i+1] + LeftEdge[i] -LeftEdge[i+1];
        }
        else{
          MiddleLine[i] = LeftEdge[i] + Width[i]/2;
        }
      }
      else if (LeftEdge[i]==0 && RightEdge[i]!=ColumnMax)
      {
        LeftLose++;

        if(RightEdge[i+1] !=ColumnMax)
        {
          MiddleLine[i] = MiddleLine[i+1]+RightEdge[i]-RightEdge[i+1];
        }
        else
        {
          MiddleLine[i] = RightEdge[i] - Width[i]/2;
        }
      }
      else if (LeftEdge[i] ==0 && RightEdge[i] ==ColumnMax)
      {
        AllLose++;
        MiddleLine[i] = MiddleLine[i+1];
      }
    }
      if (i == 0)
      {
        AvaliableLines = 120;
        LastLine = 0;
        break;
      }
    uint16 m = MiddleLine[i];
    if (m < 10)
    {
      m = 10;
    }
    if (m > 150)
    {
      m = 150;
    }
    if ((LeftEdge[i] !=0 && LeftEdge[i] >=130) ||(RightEdge[i]!=ColumnMax && RightEdge[i]<30)|| (i>=1)&& (Image_Array[i-1][m] == Black_Point))
    {
      LastLine = i;
      AvaliableLines = 119 - i;
      break;
    }
}
}
