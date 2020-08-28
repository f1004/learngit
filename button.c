///************************************************************
//  * @brief   按键驱动
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
// *                          变量声明
// *******************************************************************/
//char Menu_Page,ITEM1,ITEM2;
//int16 max_speed,nor_speed,rou_speed,Break_speed,Bar_speed,Bar_speed,Bar_Left_para,Bar_Right_para,BDet_distance,G_yuzhi,Arrow_Position;
//
//
///*******************************************************************
// *                         函数声明
// *******************************************************************/
//
//void lcd_show_menu()
//{
//
//  //判断拨码开关的状态
//
//	      oled_p8x16str(30,0,"Camera_Menu");
//      //一级菜单
//      if(Menu_Page==1)
//      {
//    	  oled_p8x16str(20,1,"1.Speed_Set");
//    	  oled_p8x16str(20,2,"2.Berrier_Set");
//    	  oled_p8x16str(20,3,"3.Break_Set");
//    	  oled_p8x16str(20,4,"4.Quit");
//      }
//      //二级菜单
//      else if(Menu_Page==2)
//      {
//        switch(ITEM1)
//        {
//        case 0://速度设置
//          {
//        	  oled_p8x16str(20,1,"1.Max_Speed");//最大速度
//        	  oled_p8x16str(20,2,"2.Normal_Speed");//普通速度
//        	  oled_p8x16str(20,3,"3.Round_Speed");//环岛速度
//        	  oled_p8x16str(20,4,"4.Break_Speed");//断路速度
//        	  oled_p8x16str(20,5,"5.Barrier_Speed");//障碍速度
//            break;
//          }
//        case 1://障碍设置
//          {
//        	  oled_p8x16str(20,1,"1.Bar_Left_para");//左转系数
//        	  oled_p8x16str(20,2,"2.Bar_Right_para");//右转系数
//        	  oled_p8x16str(20,3,"3.Bar_distance");//左转距离
//            break;
//          }
//        case 2://断路设置
//          {
//        	  oled_p8x16str(20,1,"1.Break_Threshold");//断路阈值
//            break;
//          }
//        }
//      }
//      //三级菜单
//      else if(Menu_Page==3)
//      {
//        switch(ITEM1)
//        {
//        case 0://速度设置
//          {
//            switch(ITEM2)
//            {
//            case 0://直线速度
//              {
//            	  oled_p8x16str(0,1," Max_Speed:");
//            	  oled_uint16(45,2,max_speed);
//                break;
//              }
//            case 1://弯道速度
//              {
//            	oled_p8x16str(0,1," Normal_Speed:");
//                oled_uint16(45,2,nor_speed);
//                break;
//              }
//            case 2://圆环速度
//              {
//            	oled_p8x16str(0,1," Round_Speed:");
//                LCD_Print16(45,2,rou_speed);
//                break;
//              }
//            case 3://断路速度
//              {
//            	oled_p8x16str(0,1," Break_Speed:");
//                oled_uint16(45,2,Break_speed);
//                break;
//              }
//            case 4://过障碍速度
//              {
//            	oled_p8x16str(0,1," Barrier_Speed:");
//                oled_uint16(45,2,Bar_speed);
//                break;
//              }
//            }
//            break;
//          }
//        case 1://路障设置
//          {
//            switch(ITEM2)
//            {
//            case 0://左偏差
//              {
//                LCD_P6x8Str(20,1," Bar_Left_offset:");
//                oled_uint16(45,2,Bar_Left_para);
//                break;
//              }
//            case 1://右偏差
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
//        case 2://断路设置
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


