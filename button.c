///************************************************************
//  * @brief   ��������
//	* @param   NULL
//  * @return  NULL
//  * @author  jiejie
//  * @github  https://github.com/jiejieTop
//  * @date    2018-xx-xx
//  * @version v1.0
//  * @note    button.c
//  ***********************************************************/
//#include "button.h"
//#include "headfile.h"
///*******************************************************************
// *                          ��������
// *******************************************************************/
//char Menu_Page,ITEM1,ITEM2;
//int16 max_speed,nor_speed,rou_speed,Break_speed,Bar_speed,Bar_speed,Bar_Left_para,Bar_Right_para,BDet_distance,G_yuzhi,Arrow_Position;
//
//
///*******************************************************************
// *                         ��������
// *******************************************************************/
//
//void lcd_show_menu()
//{
//
//  //�жϲ��뿪�ص�״̬
//
//	      oled_p8x16str(30,0,"Camera_Menu");
//      //һ���˵�
//      if(Menu_Page==1)
//      {
//    	  oled_p8x16str(20,1,"1.Speed_Set");
//    	  oled_p8x16str(20,2,"2.Berrier_Set");
//    	  oled_p8x16str(20,3,"3.Break_Set");
//    	  oled_p8x16str(20,4,"4.Quit");
//      }
//      //�����˵�
//      else if(Menu_Page==2)
//      {
//        switch(ITEM1)
//        {
//        case 0://�ٶ�����
//          {
//        	  oled_p8x16str(20,1,"1.Max_Speed");//����ٶ�
//        	  oled_p8x16str(20,2,"2.Normal_Speed");//��ͨ�ٶ�
//        	  oled_p8x16str(20,3,"3.Round_Speed");//�����ٶ�
//        	  oled_p8x16str(20,4,"4.Break_Speed");//��·�ٶ�
//        	  oled_p8x16str(20,5,"5.Barrier_Speed");//�ϰ��ٶ�
//            break;
//          }
//        case 1://�ϰ�����
//          {
//        	  oled_p8x16str(20,1,"1.Bar_Left_para");//��תϵ��
//        	  oled_p8x16str(20,2,"2.Bar_Right_para");//��תϵ��
//        	  oled_p8x16str(20,3,"3.Bar_distance");//��ת����
//            break;
//          }
//        case 2://��·����
//          {
//        	  oled_p8x16str(20,1,"1.Break_Threshold");//��·��ֵ
//            break;
//          }
//        }
//      }
//      //�����˵�
//      else if(Menu_Page==3)
//      {
//        switch(ITEM1)
//        {
//        case 0://�ٶ�����
//          {
//            switch(ITEM2)
//            {
//            case 0://ֱ���ٶ�
//              {
//            	  oled_p8x16str(0,1," Max_Speed:");
//            	  oled_uint16(45,2,max_speed);
//                break;
//              }
//            case 1://����ٶ�
//              {
//            	oled_p8x16str(0,1," Normal_Speed:");
//                oled_uint16(45,2,nor_speed);
//                break;
//              }
//            case 2://Բ���ٶ�
//              {
//            	oled_p8x16str(0,1," Round_Speed:");
//                LCD_Print16(45,2,rou_speed);
//                break;
//              }
//            case 3://��·�ٶ�
//              {
//            	oled_p8x16str(0,1," Break_Speed:");
//                oled_uint16(45,2,Break_speed);
//                break;
//              }
//            case 4://���ϰ��ٶ�
//              {
//            	oled_p8x16str(0,1," Barrier_Speed:");
//                oled_uint16(45,2,Bar_speed);
//                break;
//              }
//            }
//            break;
//          }
//        case 1://·������
//          {
//            switch(ITEM2)
//            {
//            case 0://��ƫ��
//              {
//                LCD_P6x8Str(20,1," Bar_Left_offset:");
//                oled_uint16(45,2,Bar_Left_para);
//                break;
//              }
//            case 1://��ƫ��
//              {
//                LCD_P6x8Str(20,1," Bar_Right_offset:");
//                LCD_Print16(45,2,Bar_Right_para);
//                break;
//              }
//            case 2:
//              {
//                LCD_P6x8Str(20,1," Bar_Distance:");
//                LCD_PrintU16(45,2,BDet_distance);
//                break;
//              }
//            }
//            break;
//          }
//        case 2://��·����
//          {
//            LCD_P6x8Str(20,1," Break_Threshold:");
//            LCD_PrintU16(45,2,G_yuzhi);
//            break;
//          }
//        }
//      }
//  if(Menu_Page<3)
//    LCD_P6x8Str(5,Arrow_Position,"->");
//
//}
//
//
//
//
//


