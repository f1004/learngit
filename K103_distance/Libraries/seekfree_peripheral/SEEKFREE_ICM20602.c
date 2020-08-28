

#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_spi.h"
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_ICM20602.h"


int16 icm_gyro_x,icm_gyro_y,icm_gyro_z;
int16 icm_acc_x,icm_acc_y,icm_acc_z;


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self1_check(void)
{
    uint8 dat=0;
    while(0x12 != dat)   //读取ICM20602 ID
    {
        dat = simiic_read_reg(ICM20602_DEV_ADDR,ICM20602_WHO_AM_I,SIMIIC);
        systick_delay_ms(STM0, 10);
        //卡在这里原因有以下几点
        //1 ICM20602坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
		//4 可能没有调用模拟IIC的初始化函数
    }
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化ICM20602
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				调用该函数前，请先调用模拟IIC的初始化
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init(void)
{
    systick_delay_ms(STM0, 10);  //上电延时
    
    //检测
    icm20602_self1_check();
    
    //复位
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_1,0x80);               //复位设备
    systick_delay_ms(STM0, 2);                                                        //延时
    while(0x80 & simiic_read_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_1,SIMIIC));//等待复位完成
    
    //配置参数
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_1,0x01);               //时钟设置
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_PWR_MGMT_2,0x00);               //开启陀螺仪和加速度计
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_CONFIG,0x01);                   //176HZ 1KHZ
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_SMPLRT_DIV,0x07);               //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_GYRO_CONFIG,0x18);              //±2000 dps
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_ACCEL_CONFIG,0x10);             //±8g
    simiic_write_reg(ICM20602_DEV_ADDR,ICM20602_ACCEL_CONFIG_2,0x03);           //Average 4 samples   44.8HZ   //0x23 Average 16 samples
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata(void)
{
    uint8 dat[6];
    
    simiic_read_regs(ICM20602_DEV_ADDR, ICM20602_ACCEL_XOUT_H, dat, 6, SIMIIC);  
    icm_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro(void)
{
    uint8 dat[6];

    simiic_read_regs(ICM20602_DEV_ADDR, ICM20602_GYRO_XOUT_H, dat, 6, SIMIIC);  
    icm_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
    icm_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
    icm_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  以上函数是使用软件IIC通信，相比较硬件IIC，软件IIC引脚更加灵活，可以使用任意普通IO
//-------------------------------------------------------------------------------------------------------------------





////-------------------------------------------------------------------------------------------------------------------
////  以下函数是使用硬件IIC通信，相比较软件IIC，硬件IIC速度可以做到更快。
////-------------------------------------------------------------------------------------------------------------------
//
//#define IIC_NUM         IIC_1
//#define IIC_SDA_PIN     IIC1_SDA_B17
//#define IIC_SCL_PIN     IIC1_SCL_B16
////-------------------------------------------------------------------------------------------------------------------
////  @brief      ICM20602自检函数
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void icm20602_self2_check(void)
//{
//    uint8 dat=0;
//    while(0x12 != dat)   //读取ICM20602 ID
//    {
//        iic_read_reg(IIC_NUM, ICM20602_DEV_ADDR, ICM20602_WHO_AM_I, &dat);
//        systick_delay_ms(STM0, 10);
//        //卡在这里原因有以下几点
//        //1 ICM20602坏了，如果是新的这样的概率极低
//        //2 接线错误或者没有接好
//        //3 可能你需要外接上拉电阻，上拉到3.3V
//    }
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      初始化ICM20602
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:
////-------------------------------------------------------------------------------------------------------------------
//void icm20602_init_hardware(void)
//{
//    uint8 dat = 0;
//    systick_delay_ms(STM0, 10);  //上电延时
//    iic_init(IIC_NUM, IIC_SDA_PIN, IIC_SCL_PIN,400*1000);       //硬件IIC初始化     波特率400K
//
//    //检测
//    icm20602_self2_check();
//
//    //复位
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_1, 0x80);	        //解除休眠状态
//    systick_delay_ms(STM0, 2);                                                            //延时
//
//
//    while(0x80 & dat)                                                               //等待复位完成
//    {
//        iic_read_reg(IIC_NUM, ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_1, &dat);
//        systick_delay_ms(STM0, 10);
//    }
//
//    //配置参数
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_1, 0x01);	        //时钟设置
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_PWR_MGMT_2, 0x00);            //开启陀螺仪和加速度计
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_CONFIG, 0x01);                //176HZ 1KHZ
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_SMPLRT_DIV, 0x07);            //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_GYRO_CONFIG, 0x18);           //±2000 dps
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_ACCEL_CONFIG, 0x10);          //±8g
//    iic_write_reg(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_ACCEL_CONFIG_2, 0x03);		//Average 4 samples   44.8HZ   //0x23 Average 16 samples
//
//}
//
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      获取ICM20602加速度计数据
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:				执行该函数后，直接查看对应的变量即可
////-------------------------------------------------------------------------------------------------------------------
//void get_icm20602_accdata_hardware(void)
//{
//    uint8 dat[6];
//
//    iic_read_reg_bytes(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_ACCEL_XOUT_H, dat, 6);
//    icm_acc_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
//    icm_acc_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
//    icm_acc_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
//}
//
////-------------------------------------------------------------------------------------------------------------------
////  @brief      获取ICM20602陀螺仪数据
////  @param      NULL
////  @return     void
////  @since      v1.0
////  Sample usage:				执行该函数后，直接查看对应的变量即可
////-------------------------------------------------------------------------------------------------------------------
//void get_icm20602_gyro_hardware(void)
//{
//    uint8 dat[6];
//
//    iic_read_reg_bytes(IIC_NUM,ICM20602_DEV_ADDR, ICM20602_GYRO_XOUT_H, dat, 6);
//    icm_gyro_x = (int16)(((uint16)dat[0]<<8 | dat[1]));
//    icm_gyro_y = (int16)(((uint16)dat[2]<<8 | dat[3]));
//    icm_gyro_z = (int16)(((uint16)dat[4]<<8 | dat[5]));
//}






//-------------------------------------------------------------------------------------------------------------------
//  以下函数是使用硬件SPI通信，相比较IIC，速度比IIC快非常多。
//-------------------------------------------------------------------------------------------------------------------
#define SPI_NUM         SPI_0
#define SPI_SCK_PIN     SPI0_SCLK_P20_11    //接模块SPC
#define SPI_MOSI_PIN    SPI0_MOSI_P20_14    //接模块SDI
#define SPI_MISO_PIN    SPI0_MISO_P20_12    //接模块SDO
#define SPI_CS_PIN      SPI0_CS2_P20_13     //接模块CS

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602 SPI写寄存器
//  @param      cmd     寄存器地址
//  @param      val     需要写入的数据
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm_spi_w_reg_byte(uint8 cmd, uint8 val)
{
    uint8 dat[2];
    
    dat[0] = cmd | ICM20602_SPI_W;
    dat[1] = val;
    
    spi_mosi(SPI_NUM,SPI_CS_PIN,dat,dat,2,1);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602 SPI读寄存器
//  @param      cmd     寄存器地址
//  @param      *val    接收数据的地址
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm_spi_r_reg_byte(uint8 cmd, uint8 *val)
{
    uint8 dat[2];
    
    dat[0] = cmd | ICM20602_SPI_R;
    dat[1] = *val;
    
    spi_mosi(SPI_NUM,SPI_CS_PIN,dat,dat,2,1);
    
    *val = dat[1];
}
  
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602 SPI多字节读寄存器
//  @param      cmd     寄存器地址
//  @param      *val    接收数据的地址
//  @param      num     读取数量
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm_spi_r_reg_bytes(uint8 * val, uint8 num)
{
    spi_mosi(SPI_NUM,SPI_CS_PIN,val,val,num,1);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ICM20602自检函数
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm20602_self3_check(void)
{
    uint8 dat=0;
    while(0x12 != dat)   //读取ICM20602 ID
    {
        icm_spi_r_reg_byte(ICM20602_WHO_AM_I,&dat);
        systick_delay_ms(STM0, 10);
        //卡在这里原因有以下几点
        //1 ICM20602坏了，如果是新的这样的概率极低
        //2 接线错误或者没有接好
        //3 可能你需要外接上拉电阻，上拉到3.3V
    }

}
     
//-------------------------------------------------------------------------------------------------------------------
//  @brief      初始化ICM20602
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void icm20602_init_spi(void)
{
    uint8 val = 0x0;

    systick_delay_ms(STM0, 10);  //上电延时
    
    (void)spi_init(SPI_NUM, SPI_SCK_PIN, SPI_MOSI_PIN, SPI_MISO_PIN, SPI_CS_PIN, 3, 10*1000*1000);//硬件SPI初始化

    icm20602_self3_check();//检测
    
    icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1,0x80);//复位设备
    systick_delay_ms(STM0, 2);
    do
    {//等待复位成功
        icm_spi_r_reg_byte(ICM20602_PWR_MGMT_1,&val);
    }while(0x41 != val);
    
    icm_spi_w_reg_byte(ICM20602_PWR_MGMT_1,     0x01);            //时钟设置
    icm_spi_w_reg_byte(ICM20602_PWR_MGMT_2,     0x00);            //开启陀螺仪和加速度计
    icm_spi_w_reg_byte(ICM20602_CONFIG,         0x01);            //176HZ 1KHZ
    icm_spi_w_reg_byte(ICM20602_SMPLRT_DIV,     0x07);            //采样速率 SAMPLE_RATE = INTERNAL_SAMPLE_RATE / (1 + SMPLRT_DIV)
    icm_spi_w_reg_byte(ICM20602_GYRO_CONFIG,    0x18);            //±2000 dps
    icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG,   0x10);            //±8g
    icm_spi_w_reg_byte(ICM20602_ACCEL_CONFIG_2, 0x03);            //Average 4 samples   44.8HZ   //0x23 Average 16 samples
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602加速度计数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_accdata_spi(void)
{
    struct
    {
        uint8 reg;
        uint8 dat[6];
    }buf;

    buf.reg = ICM20602_ACCEL_XOUT_H | ICM20602_SPI_R;
    
    icm_spi_r_reg_bytes(&buf.reg, 7);
    icm_acc_x = (int16)(((uint16)buf.dat[0]<<8 | buf.dat[1]));
    icm_acc_y = (int16)(((uint16)buf.dat[2]<<8 | buf.dat[3]));
    icm_acc_z = (int16)(((uint16)buf.dat[4]<<8 | buf.dat[5]));
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取ICM20602陀螺仪数据
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				执行该函数后，直接查看对应的变量即可
//-------------------------------------------------------------------------------------------------------------------
void get_icm20602_gyro_spi(void)
{
    struct
    {
        uint8 reg;
        uint8 dat[6];
    }buf;

    buf.reg = ICM20602_GYRO_XOUT_H | ICM20602_SPI_R;
    
    icm_spi_r_reg_bytes(&buf.reg, 7);
    icm_gyro_x = (int16)(((uint16)buf.dat[0]<<8 | buf.dat[1]));
    icm_gyro_y = (int16)(((uint16)buf.dat[2]<<8 | buf.dat[3]));
    icm_gyro_z = (int16)(((uint16)buf.dat[4]<<8 | buf.dat[5]));
}

#define Kp 100.0f                        // 比例增益支配率收敛到加速度计/磁强计

#define Ki 0.002f                // 积分增益支配率的陀螺仪偏见的衔接

#define halfT 0.001f                // 采样周期的一半



float q0 = 1, q1 = 0, q2 = 0, q3 = 0;          // 四元数的元素，代表估计方向

float exInt = 0, eyInt = 0, ezInt = 0;        // 按比例缩小积分误差



float Yaw,Pitch,Roll;  //偏航角，俯仰角，翻滚角




void IMUupdate(float gx, float gy, float gz, float ax, float ay, float az)

{

        float norm;

        float vx, vy, vz;

        float ex, ey, ez;



        // 测量正常化

        norm = sqrt(ax*ax + ay*ay + az*az);

        ax = ax / norm;                   //单位化

        ay = ay / norm;

        az = az / norm;



        // 估计方向的重力

        vx = 2*(q1*q3 - q0*q2);

        vy = 2*(q0*q1 + q2*q3);

        vz = q0*q0 - q1*q1 - q2*q2 + q3*q3;



        // 错误的领域和方向传感器测量参考方向之间的交叉乘积的总和

        ex = (ay*vz - az*vy);

        ey = (az*vx - ax*vz);

        ez = (ax*vy - ay*vx);



        // 积分误差比例积分增益

        exInt = exInt + ex*Ki;

        eyInt = eyInt + ey*Ki;

        ezInt = ezInt + ez*Ki;



        // 调整后的陀螺仪测量

        gx = gx + Kp*ex + exInt;

        gy = gy + Kp*ey + eyInt;

        gz = gz + Kp*ez + ezInt;



        // 整合四元数率和正常化

        q0 = q0 + (-q1*gx - q2*gy - q3*gz)*halfT;

        q1 = q1 + (q0*gx + q2*gz - q3*gy)*halfT;

        q2 = q2 + (q0*gy - q1*gz + q3*gx)*halfT;

        q3 = q3 + (q0*gz + q1*gy - q2*gx)*halfT;



        // 正常化四元

        norm = sqrt(q0*q0 + q1*q1 + q2*q2 + q3*q3);

        q0 = q0 / norm;

        q1 = q1 / norm;

        q2 = q2 / norm;

        q3 = q3 / norm;



        Pitch  = asin(-2 * q1 * q3 + 2 * q0* q2)* 57.3; // pitch ,转换为度数

        //Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // rollv

        Yaw = atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;                //此处没有价值，注掉

}








