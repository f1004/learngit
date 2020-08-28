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
#include "stdlib.h"
extern int32 speed1_power,speed2_power;
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
float kp1=4;//0.02
float ki1=0.1;//0.03
float kd1=0.0;//0.8
int front=40;
int width=80;
int line_mid=MT9V03X_W;
int  ad_value1,pre_value1,last_value1;
int  ad_value2,pre_value2,last_value2;
int  ad_value3,pre_value3,last_value3;
int ad_error[20],ad_error1;
char l_flag1;//全丢线标志
//void PID_Increase(void)
//{
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
//
//
//
//}

void speed_pid(int en1,int en2,int s)
{  Previous_Error1=Last_Error1;
   Previous_Error2=Last_Error2;
   Last_Error1=error_speed1;
   Last_Error2=error_speed2;

	error_speed1=s-(en1+en2)/2;



	out1 = out1+ kp1 * (error_speed1-Last_Error1)+ ki1 * (error_speed1)+kd1*(error_speed1+Previous_Error1-2*Last_Error1);


}


void adc_get(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn1, VADC_CHN_enum vadc_chn2, VADC_CHN_enum vadc_chn3, VADC_RES_enum vadc_res)
{


    int n=100;  //存放数组a中元素的个数
    int i;  //比较的轮数
    int j;  //每轮比较的次数 //int buf;  //交换数据时用于存放中间数据
    int a[100],a_max,b[100],b_max,c[100],c_max;
    for (i=0; i<n-1; ++i)  //比较n-1轮
       {   a[i] = adc_convert(vadc_n, vadc_chn1, vadc_res);
           b[i] = adc_convert(vadc_n, vadc_chn2, vadc_res);
           c[i] = adc_convert(vadc_n, vadc_chn3, vadc_res);
       }

           for (j=0; j<n-1; ++j)  //每轮比较n-1-i次,
           {

               if (a_max < a[j])
               {
                  a_max=a[j];

               }
               if (b_max < b[j])
                             {
                                b_max=b[j];

                             }
               if (c_max < c[j])
                             {
                                c_max=c[j];

                             }


          }


           ad_value1=a_max;
           ad_value2=b_max;
           ad_value3=c_max;


}

void turn(void)
{  ad_error[0]=(ad_value1-ad_value3);
 ad_error1=220*ad_error[0]/(ad_value1+ad_value2+ad_value3);


if(ad_value1<20 && ad_value2<20 && ad_value3<20 )
{ for(i=19;i>0;i--)
{      l_flag1=1;
	   ad_error1=   ad_error1+ad_error[i];
//
}



}
else
{
	l_flag1=0;

}
for(i=19;i>0;i--)
          {
          	ad_error[i]=ad_error[i-1];
          }




}


#include  "common.h"

#include "pid.h"


/*********define for SearchCenterBlackline**********/

int   MiddleLine[RowMax+1];
int   RightEdge[RowMax+1];
int   LeftEdge[RowMax+1];
int   Width[RowMax+1]={2,3,3,3,4,4,5,5,6,6,
                       8,8,10,10,12,13,14,14,16,17,
                       18,18,20,20,22,22,24,24,26,26,
                       28,30,31,32,32,34,36,36,38,39,
                       41,41,43,43,45,45,47,47,49,50,
                       50,51,52,54,55,56,57,58,59,60,
					   2,3,3,3,4,4,5,5,6,6,
					    8,8,10,10,12,13,14,14,16,17,
					    18,18,20,20,22,22,24,24,26,26,
					    28,30,31,32,32,34,36,36,38,39,
					                          41,41,43,43,45,45,47,47,49,50


};

int   MidPri         = 94;
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
int BlackEndM       = 0;
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

//设置中线，左线，右线的初始化值
//设置每一行对应的赛道宽度
//本文件内不调用
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


//全行扫描和边缘结合提取赛道的中线
//前十行全行扫描
//后面50行，根据上一行的寻线情况来决定当前行的寻线方式和起点
//外部调用
 void SearchCenterBlackline(void)
{

  int16 i         = 0;
  int16 j         = 0;
  uint8 jj        = 0;
  uint8 WhiteNum  = 0;

  LeftLose        = 0;//变量清零
  RightLose       = 0;
  AllLose         = 0;
  WhiteNum        = 0;

  MiddleLine[RowMax]  = ColumnMax/2;//第60行
  LeftEdge[RowMax]    = 0;
  RightEdge[RowMax]   = ColumnMax;
  Width[RowMax]       = ColumnMax;

  SetInitVal();
  for(i=RowMax-10;i>=RowMax-20;i--)//首先找前十行，全行扫描
  {
    if(i ==RowMax-1)//首行就以图像中心作为扫描起点
    {
       j = MidPri;//40
    }
    else
    {
        j = MiddleLine[i+1];//否则就以上一行中点的位置作为本行扫描起点
    }
    if(j <= 2)
    {
        j = 2;
    }
    while(j >= 3)//j>=3有效范围内进行搜寻
    {
        if(img[i][j]==White_Point&& img[i][j-1]==Black_Point && img[i][j-2]==Black_Point)//从右向左找到白白黑跳变
        {
             LeftEdge[i] =j;//找到则赋值 找不到保持原值0
             break;//跳出本行寻线
        }
             j--;//列数往左移动
     }
     if(i==RowMax-1) //再找右边界
     {
        j = MidPri;//如果首行，从图像中心开始搜寻
     }
     else
     {
        j = MiddleLine[i+1];//否则从上一行中心位置开始搜寻
     }
     if(j >=ColumnMax-3)//j >=ColumnMax-2有效范围内搜寻右线
     {
        j = ColumnMax-3;
     }
     while(j <= ColumnMax-3)
     {

        if(img[i][j]==White_Point && img[i][j+1]==Black_Point && img[i][j+2]==Black_Point)//从左向右找到白白黑跳变点
        {
               RightEdge[i] = j;//找到则赋值   找不到保持原值
               break;//跳出本行寻线
        }
               j++;//列数往右移动
     }
     if(LeftEdge[i]!=0 && RightEdge[i]!=ColumnMax)//中线判断，没有丢线
     {
          MiddleLine[i] = (LeftEdge[i] + RightEdge[i])/2;
     }
     else if(LeftEdge[i]!=0 && RightEdge[i]==ColumnMax)//丢了右线
     {
          RightLose++;//记录只有右线丢的数量

        if( (RightEdge[i]-LeftEdge[i]) >=(RightEdge[i+1]-LeftEdge[i+1]+1))//突变
        {
                MiddleLine[i] = MiddleLine[i+1];//用上一行的中点
        }
        else
        {
                MiddleLine[i] = LeftEdge[i] + Width[i]/2;//正常的话就用半宽补
        }
     }
     else if(LeftEdge[i]==0 && RightEdge[i]!=ColumnMax)//丢了左线
     {

        if((RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+1))//突变
        {
                MiddleLine[i] = MiddleLine[i+1];//用上一行
        }
        else
        {
                MiddleLine[i] = RightEdge[i] - Width[i]/2;//线宽
        }
     }
     else if(LeftEdge[i]==0 && RightEdge[i]==ColumnMax)//两边都丢了的话
     {
         AllLose++;

        if(i ==RowMax-1)//如果是首行就以图像中心作为中点
        {
                MiddleLine[i] = MidPri;
        }
        else
        {
                MiddleLine[i] = MiddleLine[i+1];//如果不是首行就用上一行的中线作为本行中点
        }
      }
     if(MiddleLine[RowMax-1] >=160)
     {
         MidPri = 160;
     }
     else if(MiddleLine[RowMax-1] <= 10)
     {
         MidPri = 10;
     }
     else
     {
          MidPri = MiddleLine[RowMax-1];//记录本帧图像第59行的中线值，作为下一幅图像的59行扫描起始点
     }

  }
  for(i=49; i>0; i--)//查找剩余行
  {
    if(LeftEdge[i+1]!=0 && RightEdge[i+1]!=ColumnMax) //上一行两边都找到 启用边沿扫描
    {
         j = ((LeftEdge[i+1]+10) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);//先找左边界
         jj = ((LeftEdge[i+1]-5) <= 1)? 1:(LeftEdge[i+1]-5);
      while(j >= jj)
      {
          if(img[i][j]==White_Point && img[i][j-1]==Black_Point)
          {
               LeftEdge[i] = j;
               break;
          }
         j--;
      }
         j = ((RightEdge[i+1]-10) <= 1)? 1:(RightEdge[i+1]-10); //在找右边界
         jj = ((RightEdge[i+1]+5) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+5);
      while(j <= jj)
      {
          if(img[i][j]==White_Point&& img[i][j+1]==Black_Point)
          {
               RightEdge[i] = j;
               break;
          }
         j++;
      }
    }
    else if(LeftEdge[i+1]!=0 && RightEdge[i+1]==ColumnMax)//上一行只找到左边界
    {
         j  = ((LeftEdge[i+1]+10) >=ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);//左边界用边沿扫描
         jj = ((LeftEdge[i+1]-5) <= 1)? 1:(LeftEdge[i+1]-5);
      while(j >= jj)
      {
          if(img[i][j]==White_Point && img[i][j-1]==Black_Point)
          {
               LeftEdge[i] = j;
               break;
          }
         j--;
      }
         j = MiddleLine[i+1];//上一行丢了右边界用全行扫描
      if(j >= 78)
      {
           j = 78;
      }
      while(j <= ColumnMax-2)
      {
          if(img[i][j]==White_Point && img[i][j+1]==Black_Point)
          {
               RightEdge[i] = j;
               break;
          }
         j++;
      }

    }
    else if(LeftEdge[i+1]==0 && RightEdge[i+1]!=ColumnMax) //上一行只找到右边界
    {
         j = ((RightEdge[i+1]-10) <= 1)?1:(RightEdge[i+1]-10);//边缘追踪找右边界
         jj = ((RightEdge[i+1]+5) >= ColumnMax-2)? ColumnMax-2:(RightEdge[i+1]+5);
       while(j <= jj)
       {
            if(img[i][j]==White_Point&&img[i][j+1]==Black_Point)
            {
                 RightEdge[i] = j;
                 break;
            }
           j++;
       }
           j = MiddleLine[i+1]; //全行扫描找左边界
        if(j < 2)
        {
             j = 2;
        }
       while(j >= 1)
       {
            if(img[i][j]==White_Point && img[i][j-1]==Black_Point)
            {
                 LeftEdge[i] = j;
                 break;
            }
           j--;
       }
     }
    else if(LeftEdge[i+1]==0 && RightEdge[i+1]==ColumnMax)  //上一行没找到边界，可能是十字或者环形
    {

          j = MiddleLine[i+1];   //找全行找左边界
        while(j >= 1)
        {
             if(img[i][j]==White_Point && img[i][j-1]==Black_Point)
             {
                  LeftEdge[i] = j;
                  break;
             }
            j--;
        }
         j = MiddleLine[i+1];   //全行找右边界
       while(j <=ColumnMax-2)
       {
            if(img[i][j]==White_Point&&img[i][j+1]==Black_Point)
            {
                  RightEdge[i] = j;
                  break;
            }
           j++;

       }
    }
    if( (RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+1) )//不满足畸变
    {
          MiddleLine[i] = MiddleLine[i+1];//用上一行
    }
    else
    {
            if(LeftEdge[i]!=0 && RightEdge[i]!=ColumnMax)
            {
                     MiddleLine[i] = (LeftEdge[i] + RightEdge[i])/2;

                     //对斜出十字进行纠正

                 if( MiddleLine[i]-MiddleLine[i+1]>8&&((abs(LeftEdge[i]-LeftEdge[i+1]>3)||abs(RightEdge[i]-RightEdge[i+1]>3)) )&& i>=30)//中线向右突变
                 {
                           uint8 ii = i;

                      while(1)
                      {
                               MiddleLine[ii+1] = MiddleLine[ii]-1;
                               ii++;

                           if( ii>=50 || (MiddleLine[ii]-MiddleLine[ii+1]<=1) )
                           {
                                 break;
                           }
                       }
                 }
                 if( (MiddleLine[i+1]-MiddleLine[i]>8)&&((abs(LeftEdge[i]-LeftEdge[i+1]>3)||abs(RightEdge[i]-RightEdge[i+1]>3)))&& i>=30)
                 {
                           uint8 ii = i;

                      while(1)
                      {
                               MiddleLine[ii+1] = MiddleLine[ii]+1;
                               ii++;

                           if( ii>=50 || (MiddleLine[ii+1]-MiddleLine[ii]<=1) )
                           {
                                 break;
                           }
                       }
                  }
            }
            else if(LeftEdge[i]!=0 && RightEdge[i]==ColumnMax)//find left
            {
                         RightLose++;


                 if(LeftEdge[i+1] != 0)
                 {
                               MiddleLine[i] = MiddleLine[i+1]+LeftEdge[i]-LeftEdge[i+1];
                 }
                 else
                 {
                                MiddleLine[i]  = LeftEdge[i] + Width[i]/2;
                 }
            }

            else if(LeftEdge[i]==0 && RightEdge[i]!=ColumnMax)//find right
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
           else if(LeftEdge[i]==0 && RightEdge[i]==ColumnMax)//两边丢线
           {
                         WhiteNum++;
                         AllLose++;

                 if(WhiteNum == 1)
                 {
                                  WhiteStart = i;
                 }
                        MiddleLine[i] = MiddleLine[i+1];
           }

       }

    if(i == 0)
    {
            AvaliableLines = 60;
            LastLine  = 0;
            break;
    }
           uint16 m = MiddleLine[i];
    if(m < 5)
    {
            m = 5;
    }
    if(m > 75)
    {
            m = 75;
    }
    if( (LeftEdge[i]!=0 && LeftEdge[i]>=65) || (RightEdge[i]!=ColumnMax && RightEdge[i]<15) || (i>=1)&&(img[i-1][m]== Black_Point)) //最后一行
    {
            LastLine = i;//最后一行，动态前瞻
            AvaliableLines = 60 - i;//有效行数
            break;
    }
  }
}
