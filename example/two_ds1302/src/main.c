/*************************************
 * 
 *        89c52 sdcc blink demo
 * 
 * CPU: 89C52
 * FREQ: 12MHz
 * PIN: P00
 * 
 * ***********************************
*/

#include <reg52.h>
#include <stdio.h>
#include <ds1302.h>

void delay_100ms(); //@12MHz

/************************************************/
#define DS1302_SCK_1 P10
#define DS1302_DAT_1  P11
#define DS1302_RST_1 P12
void write_sck_1(u8 value) {
    DS1302_SCK_1 = value;
}
void write_dat_1(u8 value) {
    DS1302_DAT_1 = value;
}
u8 read_dat_1(){
    return DS1302_DAT_1;
}
void write_rst_1(u8 value) {
    DS1302_RST_1 = value;
}

rtc_ds1302 rtc_1= {
    .write_sck = write_sck_1,
    .write_dat = write_dat_1,
    .read_dat = read_dat_1,
    .write_rst = write_rst_1
};
/************************************************/
#define DS1302_SCK_2 P20
#define DS1302_DAT_2  P21
#define DS1302_RST_2 P22
void write_sck_2(u8 value) {
    DS1302_SCK_2 = value;
}
void write_dat_2(u8 value) {
    DS1302_DAT_2 = value;
}
u8 read_dat_2(){
    return DS1302_DAT_2;
}
void write_rst_2(u8 value) {
    DS1302_RST_2 = value;
}

rtc_ds1302 rtc_2= {
    .write_sck = write_sck_2,
    .write_dat = write_dat_2,
    .read_dat = read_dat_2,
    .write_rst = write_rst_2
};

void main()
{
    rtc_init(&rtc_1);
    rtc_init(&rtc_2);
    while (1)
    {
        delay_100ms();
        rtc_read_time(&rtc_2);
        rtc_1.time[0] = rtc_2.time[0];
        rtc_1.time[1] = rtc_2.time[1];
        rtc_1.time[2] = rtc_2.time[2];
        rtc_1.time[3] = rtc_2.time[3];
        rtc_1.time[4] = rtc_2.time[4];
        rtc_1.time[5] = rtc_2.time[5];
        rtc_1.time[6] = rtc_2.time[6];
        rtc_1.time[7] = rtc_2.time[7];
        rtc_write_time(&rtc_1);
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