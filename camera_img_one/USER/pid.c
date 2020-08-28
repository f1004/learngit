/*
 * pid.c
 *
 *  Created on: 2020��7��31��
 *      Author: ��bԶ
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
int last_Error;//��һ�����
int Previous_Error1;
int Previous_Error2;//���ϴ����
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
char l_flag1;//ȫ���߱�־
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


    int n=100;  //�������a��Ԫ�صĸ���
    int i;  //�Ƚϵ�����
    int j;  //ÿ�ֱȽϵĴ��� //int buf;  //��������ʱ���ڴ���м�����
    int a[100],a_max,b[100],b_max,c[100],c_max;
    for (i=0; i<n-1; ++i)  //�Ƚ�n-1��
       {   a[i] = adc_convert(vadc_n, vadc_chn1, vadc_res);
           b[i] = adc_convert(vadc_n, vadc_chn2, vadc_res);
           c[i] = adc_convert(vadc_n, vadc_chn3, vadc_res);
       }

           for (j=0; j<n-1; ++j)  //ÿ�ֱȽ�n-1-i��,
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
int   LeftLoseStart  = 0;//��¼��߶��ߵĿ�ʼ��
int   RightLoseStart = 0;//��¼�ұ߱߶��ߵĿ�ʼ��
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

//�������ߣ����ߣ����ߵĳ�ʼ��ֵ
//����ÿһ�ж�Ӧ���������
//���ļ��ڲ�����
void SetInitVal()
{
  int i;

  for(i=0;i<RowMax;i++)//����ֵ
  {
      RightEdge[i]  = ColumnMax;
      LeftEdge[i]   = 0;
      MiddleLine[i] = ColumnMax/2;

  }

}


//ȫ��ɨ��ͱ�Ե�����ȡ����������
//ǰʮ��ȫ��ɨ��
//����50�У�������һ�е�Ѱ�������������ǰ�е�Ѱ�߷�ʽ�����
//�ⲿ����
 void SearchCenterBlackline(void)
{

  int16 i         = 0;
  int16 j         = 0;
  uint8 jj        = 0;
  uint8 WhiteNum  = 0;

  LeftLose        = 0;//��������
  RightLose       = 0;
  AllLose         = 0;
  WhiteNum        = 0;

  MiddleLine[RowMax]  = ColumnMax/2;//��60��
  LeftEdge[RowMax]    = 0;
  RightEdge[RowMax]   = ColumnMax;
  Width[RowMax]       = ColumnMax;

  SetInitVal();
  for(i=RowMax-10;i>=RowMax-20;i--)//������ǰʮ�У�ȫ��ɨ��
  {
    if(i ==RowMax-1)//���о���ͼ��������Ϊɨ�����
    {
       j = MidPri;//40
    }
    else
    {
        j = MiddleLine[i+1];//���������һ���е��λ����Ϊ����ɨ�����
    }
    if(j <= 2)
    {
        j = 2;
    }
    while(j >= 3)//j>=3��Ч��Χ�ڽ�����Ѱ
    {
        if(img[i][j]==White_Point&& img[i][j-1]==Black_Point && img[i][j-2]==Black_Point)//���������ҵ��װ׺�����
        {
             LeftEdge[i] =j;//�ҵ���ֵ �Ҳ�������ԭֵ0
             break;//��������Ѱ��
        }
             j--;//���������ƶ�
     }
     if(i==RowMax-1) //�����ұ߽�
     {
        j = MidPri;//������У���ͼ�����Ŀ�ʼ��Ѱ
     }
     else
     {
        j = MiddleLine[i+1];//�������һ������λ�ÿ�ʼ��Ѱ
     }
     if(j >=ColumnMax-3)//j >=ColumnMax-2��Ч��Χ����Ѱ����
     {
        j = ColumnMax-3;
     }
     while(j <= ColumnMax-3)
     {

        if(img[i][j]==White_Point && img[i][j+1]==Black_Point && img[i][j+2]==Black_Point)//���������ҵ��װ׺������
        {
               RightEdge[i] = j;//�ҵ���ֵ   �Ҳ�������ԭֵ
               break;//��������Ѱ��
        }
               j++;//���������ƶ�
     }
     if(LeftEdge[i]!=0 && RightEdge[i]!=ColumnMax)//�����жϣ�û�ж���
     {
          MiddleLine[i] = (LeftEdge[i] + RightEdge[i])/2;
     }
     else if(LeftEdge[i]!=0 && RightEdge[i]==ColumnMax)//��������
     {
          RightLose++;//��¼ֻ�����߶�������

        if( (RightEdge[i]-LeftEdge[i]) >=(RightEdge[i+1]-LeftEdge[i+1]+1))//ͻ��
        {
                MiddleLine[i] = MiddleLine[i+1];//����һ�е��е�
        }
        else
        {
                MiddleLine[i] = LeftEdge[i] + Width[i]/2;//�����Ļ����ð��
        }
     }
     else if(LeftEdge[i]==0 && RightEdge[i]!=ColumnMax)//��������
     {

        if((RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+1))//ͻ��
        {
                MiddleLine[i] = MiddleLine[i+1];//����һ��
        }
        else
        {
                MiddleLine[i] = RightEdge[i] - Width[i]/2;//�߿�
        }
     }
     else if(LeftEdge[i]==0 && RightEdge[i]==ColumnMax)//���߶����˵Ļ�
     {
         AllLose++;

        if(i ==RowMax-1)//��������о���ͼ��������Ϊ�е�
        {
                MiddleLine[i] = MidPri;
        }
        else
        {
                MiddleLine[i] = MiddleLine[i+1];//����������о�����һ�е�������Ϊ�����е�
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
          MidPri = MiddleLine[RowMax-1];//��¼��֡ͼ���59�е�����ֵ����Ϊ��һ��ͼ���59��ɨ����ʼ��
     }

  }
  for(i=49; i>0; i--)//����ʣ����
  {
    if(LeftEdge[i+1]!=0 && RightEdge[i+1]!=ColumnMax) //��һ�����߶��ҵ� ���ñ���ɨ��
    {
         j = ((LeftEdge[i+1]+10) >= ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);//������߽�
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
         j = ((RightEdge[i+1]-10) <= 1)? 1:(RightEdge[i+1]-10); //�����ұ߽�
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
    else if(LeftEdge[i+1]!=0 && RightEdge[i+1]==ColumnMax)//��һ��ֻ�ҵ���߽�
    {
         j  = ((LeftEdge[i+1]+10) >=ColumnMax-2)? ColumnMax-2:(LeftEdge[i+1]+10);//��߽��ñ���ɨ��
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
         j = MiddleLine[i+1];//��һ�ж����ұ߽���ȫ��ɨ��
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
    else if(LeftEdge[i+1]==0 && RightEdge[i+1]!=ColumnMax) //��һ��ֻ�ҵ��ұ߽�
    {
         j = ((RightEdge[i+1]-10) <= 1)?1:(RightEdge[i+1]-10);//��Ե׷�����ұ߽�
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
           j = MiddleLine[i+1]; //ȫ��ɨ������߽�
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
    else if(LeftEdge[i+1]==0 && RightEdge[i+1]==ColumnMax)  //��һ��û�ҵ��߽磬������ʮ�ֻ��߻���
    {

          j = MiddleLine[i+1];   //��ȫ������߽�
        while(j >= 1)
        {
             if(img[i][j]==White_Point && img[i][j-1]==Black_Point)
             {
                  LeftEdge[i] = j;
                  break;
             }
            j--;
        }
         j = MiddleLine[i+1];   //ȫ�����ұ߽�
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
    if( (RightEdge[i]-LeftEdge[i]) >= (RightEdge[i+1]-LeftEdge[i+1]+1) )//���������
    {
          MiddleLine[i] = MiddleLine[i+1];//����һ��
    }
    else
    {
            if(LeftEdge[i]!=0 && RightEdge[i]!=ColumnMax)
            {
                     MiddleLine[i] = (LeftEdge[i] + RightEdge[i])/2;

                     //��б��ʮ�ֽ��о���

                 if( MiddleLine[i]-MiddleLine[i+1]>8&&((abs(LeftEdge[i]-LeftEdge[i+1]>3)||abs(RightEdge[i]-RightEdge[i+1]>3)) )&& i>=30)//��������ͻ��
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
           else if(LeftEdge[i]==0 && RightEdge[i]==ColumnMax)//���߶���
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
    if( (LeftEdge[i]!=0 && LeftEdge[i]>=65) || (RightEdge[i]!=ColumnMax && RightEdge[i]<15) || (i>=1)&&(img[i-1][m]== Black_Point)) //���һ��
    {
            LastLine = i;//���һ�У���̬ǰհ
            AvaliableLines = 60 - i;//��Ч����
            break;
    }
  }
}
