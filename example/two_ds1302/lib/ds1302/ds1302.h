/**
 * @file ds1302.h
 * @author  buttfa (1662332017@qq.com)
 * @brief ds1302驱动的头文件，包括ds1302寄存器地址定义、ds1302操作集结构体和ds1302驱动函数。/
 *        The header file of the ds1302 driver, including the ds1302 register address definition, 
 *        the ds1302 operation set structure, and the ds1302 driver function.
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef __RTC_H__
#define __RTC_H__

typedef unsigned char u8;

#define HIGH 1
#define LOW  0

/**
 * @brief ds1302寄存器地址的宏定义
 *        Macro Definition of DS1302 Register Address
 */
#define DS1302_SEC_ADDR			0x80		// 秒数据地址   / Second data address
#define DS1302_MIN_ADDR			0x82		// 分数据地址   / Minute data address
#define DS1302_HR_ADDR			0x84		// 时数据地址   / Hour data address
#define DS1302_DATE_ADDR		0x86		// 日数据地址   / Day data address
#define DS1302_MONTH_ADDR		0x88		// 月数据地址   / Month data address
#define DS1302_WEEK_ADDR		0x8a		// 星期数据地址 / Week data address
#define DS1302_YEAR_ADDR		0x8c		// 年数据地址   / Year data address
#define DS1302_CONTROL_ADDR		0x8e		// 控制数据地址 / Control data address
#define DS1302_CHARGER_ADDR		0x90 					 
#define DS1302_CLKBURST_ADDR	0xbe

/**
 * @brief 定义了ds1302的操作集结构体
 * 
 */
typedef struct ds1302_ops{
    void (*write_sck)(u8 value);
    void (*write_dat)(u8 value);
    u8 (*read_dat)();
    void (*write_rst)(u8 value);
}ds1302_ops;

/**
 * @brief 定义了ds1302时间缓存和操作集结构体 / Defined the DS1302 time cache and operation set architecture
 * 
 */
typedef struct rtc_ds1302{
    // 年/Year  月/Month  日/Day  时/Hour  分/Minute  秒/Secon  星期/Day of the week
    u8 time[8];
    ds1302_ops* ops;
}rtc_ds1302;


/**
 * @brief RTC初始化函数 / rtc_ds1302 initialization function
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 */
void rtc_init(rtc_ds1302* rtc);


/**
 * @brief 向DS1302指定寄存器写入一字节数据 / Write one byte of data to the specified register of DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 * @param addr 目标ds1302寄存器地址 / Target ds1302 register address
 * @param dat 需要写入的数据 / Data to be written
 */
void ds1302_write_byte(rtc_ds1302* rtc, u8 addr, u8 dat);


/**
 * @brief 从DS1302指定寄存器读取一字节数据 / Read one byte of data from the specified register in DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 * @param addr 目标ds1302寄存器地址 / Target ds1302 register address
 * @return u8 返回ds1302目标寄存器中的数据 / Return the data in the target register of ds1302
 */
u8 ds1302_read_byte(rtc_ds1302* rtc, u8 addr);


/**
 * @brief 向DS1302写入时钟数据 / Write clock data to DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 */
void rtc_write_time(rtc_ds1302* rtc);


/**
 * @brief 从DS1302读取时钟数据 / Reading clock data from DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 */
void rtc_read_time(rtc_ds1302* rtc);

#endif