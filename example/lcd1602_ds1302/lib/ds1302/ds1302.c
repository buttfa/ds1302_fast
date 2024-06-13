/**
 * @file ds1302.c
 * @author  buttfa (1662332017@qq.com)
 * @brief ds1302驱动源文件
 * @version 0.1
 * @date 2024-06-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <ds1302.h>


/**
 * @brief RTC初始化函数 / rtc_ds1302 initialization function
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 */
void rtc_init(rtc_ds1302* rtc) {
    rtc->write_sck(LOW);
    rtc->write_rst(LOW);
}


/**
 * @brief 向DS1302指定寄存器写入一字节数据 / Write one byte of data to the specified register of DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 * @param addr 目标ds1302寄存器地址 / Target ds1302 register address
 * @param dat 需要写入的数据 / Data to be written
 */
void ds1302_write_byte(rtc_ds1302* rtc, u8 addr, u8 dat) {
    rtc->write_rst(HIGH);
    addr = addr & 0xFE;
    
    for (u8 i = 0; i < 8; i++) {
        if (addr & 0x01) {
            rtc->write_dat(HIGH);
        } else {
            rtc->write_dat(LOW);
        }
        rtc->write_sck(HIGH);
        rtc->write_sck(LOW);
        addr >>= 1;
    }

    
    for (u8 i = 0; i < 8; i++) {
        if (dat & 0x01) {
            rtc->write_dat(HIGH);
        } else {
            rtc->write_dat(LOW);
        }
        rtc->write_sck(HIGH);
        rtc->write_sck(LOW);
        dat >>= 1;
    }
    rtc->write_rst(LOW);
}


/**
 * @brief 从DS1302指定寄存器读取一字节数据 / Read one byte of data from the specified register in DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 * @param addr 目标ds1302寄存器地址 / Target ds1302 register address
 * @return u8 返回ds1302目标寄存器中的数据 / Return the data in the target register of ds1302
 */
u8 ds1302_read_byte(rtc_ds1302* rtc, u8 addr) {
    u8 temp = 0x00;
    rtc->write_rst(HIGH);
    addr = addr | 0x01;
    for (u8 i = 0; i < 8; i++) {
        if (addr & 0x01) {
            rtc->write_dat(HIGH);
        } else {
            rtc->write_dat(LOW);
        }
        rtc->write_sck(HIGH);
        rtc->write_sck(LOW);
        addr >>= 1;
    }

    for (u8 i = 0; i < 8; i++) {
        temp = temp >> 1;
        if (rtc->read_dat() == 1) {
            temp |= 0x80;
        }
        rtc->write_sck(HIGH);
        rtc->write_sck(LOW);
    }
    rtc->write_rst(LOW);
    return temp;
}


/**
 * @brief 向DS1302写入时钟数据 / Write clock data to DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 */
void rtc_write_time(rtc_ds1302* rtc) {
    ds1302_write_byte(rtc, DS1302_CONTROL_ADDR,0x00);			
	ds1302_write_byte(rtc, DS1302_SEC_ADDR,0x80);			
	//ds1302_write_byte(rtc, DS1302_charger_ADDR,0xa9);	   
	ds1302_write_byte(rtc, DS1302_YEAR_ADDR,((rtc->time[1]/10)<<4)|(rtc->time[1]%10));	
	ds1302_write_byte(rtc, DS1302_MONTH_ADDR,((rtc->time[2]/10)<<4)|(rtc->time[2]%10));	
	ds1302_write_byte(rtc, DS1302_DATE_ADDR,((rtc->time[3]/10)<<4)|(rtc->time[3]%10));	
	ds1302_write_byte(rtc, DS1302_HR_ADDR,((rtc->time[4]/10)<<4)|(rtc->time[4]%10));		
	ds1302_write_byte(rtc, DS1302_MIN_ADDR,((rtc->time[5]/10)<<4)|(rtc->time[5]%10));		
	ds1302_write_byte(rtc, DS1302_SEC_ADDR,((rtc->time[6]/10)<<4)|(rtc->time[6]%10));	
	ds1302_write_byte(rtc, DS1302_WEEK_ADDR,((rtc->time[7]/10)<<4)|(rtc->time[7]%10));	
	ds1302_write_byte(rtc, DS1302_CONTROL_ADDR,0x80);		
}


/**
 * @brief 从DS1302读取时钟数据 / Reading clock data from DS1302
 * 
 * @param rtc ds1302操作集结构体 / Ds1302 operation set architecture
 */
void rtc_read_time(rtc_ds1302* rtc) {
    u8 time_buf[8];
    time_buf[1]=ds1302_read_byte(rtc, DS1302_YEAR_ADDR);	
	time_buf[2]=ds1302_read_byte(rtc, DS1302_MONTH_ADDR);	
	time_buf[3]=ds1302_read_byte(rtc, DS1302_DATE_ADDR);	
	time_buf[4]=ds1302_read_byte(rtc, DS1302_HR_ADDR);		
	time_buf[5]=ds1302_read_byte(rtc, DS1302_MIN_ADDR);	
	time_buf[6]=((ds1302_read_byte(rtc, DS1302_SEC_ADDR))&0x7f);
	time_buf[7]=ds1302_read_byte(rtc, DS1302_WEEK_ADDR);	
    
    rtc->time[1] = (time_buf[1]>>4)*10 + (time_buf[1]&0x0f);
    rtc->time[2] = (time_buf[2]>>4)*10 + (time_buf[2]&0x0f);
    rtc->time[3] = (time_buf[3]>>4)*10 + (time_buf[3]&0x0f);
    rtc->time[4] = (time_buf[4]>>4)*10 + (time_buf[4]&0x0f);
    rtc->time[5] = (time_buf[5]>>4)*10 + (time_buf[5]&0x0f);
    rtc->time[6] = (time_buf[6]>>4)*10 + (time_buf[6]&0x0f);
    rtc->time[7] = (time_buf[7]>>4)*10 + (time_buf[7]&0x0f);
}
