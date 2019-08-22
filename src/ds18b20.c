#include "ds18b20.h"
//@75Mhz normal mode
//little endian
//由于sys_timer_t 只能实现ms级定时
//故delay使用传统的i++延时

uint8 ds18b20_init() {
	uint8 state = 1;
	//总线拉低至少480us
	output_set(0);
	delay(3500);//520us
	//释放总线
	output_set(1);
	//等待15到60us
	delay(400);//29.56us
    //读取ds18b20响应数据,正常情况下ds18b20将拉低总线
	state = input_get();
	delay(2000);//107.2us
	output_set(1);
	return state;
}

void ds18b20_write_byte(uint8 data) {
	int i = 0;
	for(; i < 8; i++) {
		//写时隙 拉低总线2μs 释放总线
		output_set(0);
		delay(1);//1.625us
        //写入一个数据，最低位开始
		output_set(data & 0x01);
		delay(1200);//66.04us
        //释放总线，至少1us给总线恢复时间
		output_set(1);
		delay(1);//3.81us
		data >>= 1;
	}
}

uint8 ds18b20_read_byte() {
	uint8 byte = 0, data;
	int i = 0;
	for(; i < 8; i++) {
		//拉低总线2us
		output_set(0);
        delay(1);
		//读时隙产生6us后读取总线数据
		output_set(1);
		delay(2);//5.958us
        //在19us内读2次确保得到正确数据
		data = input_get();
		data = input_get();
		//移位存储, byte务必初始化
		byte |=  (data << i);
		//读时隙必须至少有60us的持续时间
		delay(1200);
		output_set(1);
		delay(1);
	}
	return byte;
}

void ds18b20_convert_temp() {
	ds18b20_init();
	delay(1800);//502.3us
    //跳过ROM操作命令
	ds18b20_write_byte(0xCC);
    //温度转换命令
	ds18b20_write_byte(0x44);
}

void ds18b20_read_temp_cmd() {
	ds18b20_init();
	delay(1800);
    //跳过ROM操作命令
	ds18b20_write_byte(0xCC);
    //发送读取温度命令
	ds18b20_write_byte(0xBE);
}

short ds18b20_read_temp() {
	short temp = 0;
	unsigned char tmh = 0,tml = 0;
    //先写入转换命令
	ds18b20_convert_temp();
    //转换完读取温度
	ds18b20_read_temp_cmd();
    //温度值16位，读低字节
	tml = ds18b20_read_byte();
    //读高字节
	tmh = ds18b20_read_byte();
    //合成温度值16位
	temp = tmh;
	temp <<= 8;
	temp |= tml;
	return temp;
}

unsigned int ds18b20_read_rom_id() {
    unsigned int rom_id = 0;
    unsigned int data;
    ds18b20_init();
	delay(1800);
	ds18b20_write_byte(0x33);
    for (int i = 0; i < 4; i++ ) {
        data = ds18b20_read_byte();
        rom_id |=  (data << (i * 8));
    }
    return rom_id;
}
