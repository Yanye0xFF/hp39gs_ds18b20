#include "user_main.h"

int user_init(void){
    int32_t keycode = 0;
    uint8_t disp_type = 0;
    int16_t state = 1;
    uint32_t rom_id;
    _clear_screen();
    //family code 1位
    //rom code 低3位
    //其余数据忽略
    rom_id = ds18b20_read_rom_id();
    goto START;
	while(1) {
        keycode = get_key();
		if(keycode == KEY_EVENT_HOME){
			break;
		}else if(keycode != KEY_EVENT_NULL) {
            disp_type = keycode;
        }
        START:
        kos_PutString(10, 0, "DS18B20 TEMP SENSOR");
        kos_PutString(15, 9, "ROM ID:");
        kos_PutHexNumber(60, 9, rom_id);
        state = ds18b20_read_temp();
        display_temp(state, disp_type);
        display_menu(disp_type);
	}
    return 0;
}

int event_handler(unsigned col, unsigned row) {
	//[APLET], [ON], [HOME]// 
	if((col == 7 && row == 0) || (col == 4 && row == 6) || 
        (col == 6 && row == 6)) {
		return KEY_EVENT_HOME;
	}

    delay(1250000);
    //F1 F2
	if((col == 5) && (row < 2)) {
		return row;
	}

	return KEY_EVENT_NULL;
}
