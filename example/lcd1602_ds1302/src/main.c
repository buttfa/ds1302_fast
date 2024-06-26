/**
 * @file main.c
 * @author  buttfa (1662332017@qq.com)
 * @brief LCD1602显示DS1302实时时钟 / LCD1602 displays DS1302 real-time clock
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <reg52.h>
#include <stdio.h>
#include <LCD1602.h>
#include <ds1302.h>
void delay_100ms(); //@12MHz


#define DS1302_SCK P10
#define DS1302_DAT  P11
#define DS1302_RST P12
void write_sck(u8 value) {
    DS1302_SCK = value;
}
void write_dat(u8 value) {
    DS1302_DAT = value;
}
u8 read_dat(){
    return DS1302_DAT;
}
void write_rst(u8 value) {
    DS1302_RST = value;
}

ds1302_ops ops = {
    .write_sck = write_sck,
    .write_dat = write_dat,
    .read_dat = read_dat,
    .write_rst = write_rst
};

rtc_ds1302 rtc= {
    .ops = &ops
};

void main()
{
    LCD_Init();
    rtc_init(&rtc);

    // 2013年6月2日星期7 17点47分12秒 / Sunday, June 2, 2013 17:47:12
    rtc.time[0] = 20;
    rtc.time[1] = 13;
    rtc.time[2] = 6;
    rtc.time[3] = 2;
    rtc.time[4] = 17;
    rtc.time[5] = 47;
    rtc.time[6] = 12;
    rtc.time[7] = 7;
    rtc_write_time(&rtc); 
    rtc_read_time(&rtc);
    while (1)
    {
        delay_100ms();
        rtc_read_time(&rtc);
        
        LCD_ShowNum(1,1,rtc.time[0],2);
        LCD_ShowNum(1,3,rtc.time[1],2);

        LCD_ShowNum(1,6,rtc.time[2],2);

        LCD_ShowNum(1,9,rtc.time[3],2);

        LCD_ShowNum(1,12,rtc.time[7],2);

        LCD_ShowNum(2,1,rtc.time[4],2);

        LCD_ShowNum(2,4,rtc.time[5],2);

        LCD_ShowNum(2,7,rtc.time[6],2);
    }
}

void delay_100ms()
{
    unsigned char i, j;

    i = 195;
    j = 138;

    do
    {
        while (--j)
            ;
    } while (--i);
}