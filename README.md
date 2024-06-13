# 项目名称 / Project Name
### ds1302_fast

# 移植方式 / Transplantation method
#### （一）将lib文件夹放至工程根目录，将其中的ds1302文件夹添加到工程（由于不同项目工程其添加库的方式不同，此处自行处理）<br> Place the lib folder in the root directory of the project and add the ds1302 folder to the project (as different project projects have different ways of adding libraries, this is handled independently)
#### （二）实现代码 / Implementation code
#### 1.实现ds1302引脚控制和读取代码 / Implement DS1302 pin control and read code
```c
void _write_sck(u8 value) {
    /**
     * code
     */
}
void _write_dat(u8 value) {
    /**
     * code
     */
}
u8 _read_dat() {
    /**
     * code
     */
}
void _write_rst(u8 value) {
    /**
     * code
     */
}
```
#### 2.定义rtc_ds1302变量 / Define the rtc_ds1302 variable
```c
rtc_ds1302 rtc= {
    .write_sck = _write_sck,
    .write_dat = _write_dat,
    .read_dat = _read_dat,
    .write_rst = _write_rst
};
```
#### 3.使用rtc_write_time()和rtc_read_time()即可 / You can use rtc_write_time() and rtc_read_time() to complete the process

# 结构体解析 / Structural Analysis
```c
typedef struct rtc_ds1302{
    u8 time[8];
    void (*write_sck)(u8 value);
    void (*write_dat)(u8 value);
    u8 (*read_dat)();
    void (*write_rst)(u8 value);
}rtc_ds1302;
```
#### 结构体rtc_ops定义了ds1302所需的操作集和时间缓存变量。其中write_sck、write_dat、write_rst分别控制ds1302的sck、dat、rst引脚的值，read_dat用于读取ds1302上dat引脚的值。time数组存储的数据依次为年（前两位）、年（后两位）、月、日、时、分、秒和星期。<br> The structure rtc_ops defines the set of operations and time cache variables required for ds1302. Among them, writer_sck, writer_dat, and writer_rst respectively control the values of the sck, dat, and rst pins on ds1302, while read_dat is used to read the value of the dat pin on ds1302. The time array stores data in the order of year (first two digits), year (last two digits), month, day, hour, minute, second, and week.

# 重要函数解析 / Analysis of Important Functions
|函数声明 / Function declaration|函数作用 / Function action|注意 / Notice|
|:-|:-|:-|
|void rtc_init(rtc_ds1302* rtc)|初始化ds1302 / Initialize ds1302|无 / Empty|
|void rtc_write_time(rtc_ds1302* rtc)|修改ds1302的时间 / Modify the time of ds1302|在使用该函数时，请先将修改后的时间写入rtc->time/rtc.time数组 <br> When using this function, please first write the modified time into the rtc->time/rtc.time array|
|void rtc_read_time(rtc_ds1302* rtc)|读出ds1302的时间 / Read the time of ds1302|读出的数据存储在rtc->time/rtc.time数组中 <br> The read data is stored in the rtc ->time/rtc. time array|

# 示例（示例工程均位于example文件夹下）/ Example (all example projects are located in the example folder)
### 1.LCD1602显示时间 / LCD1602 display time (Vscode + EIDE + sdcc[STC89C52RC])
### 2.ds1302相互校验 / DS1302 mutual verification (Vscode + EIDE + sdcc[STC89C52RC])