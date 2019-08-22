#include "displayer.h"

extern uint8_t *__display_buf;

void display_temp(int16_t temp, uint8_t disp_type) {
    uint32_t index;
    uint8_t *str_buff = kos_malloc(sizeof(uint8_t) * BUFFER_SIZE);

    uint8_t is_negative = (temp < 0);
    if(is_negative) {
        temp = temp - 1;
		temp = ~temp;
    }

    temp = (disp_type == CELSIUS) ? ((float)temp * 6.25 + 0.5) : 
        ((float)temp * 11.25 + 3200.9);

    *(str_buff + 0 ) = is_negative ? 10 : 11;
    *(str_buff + 1 ) = temp / 10000;
    *(str_buff + 2 ) = temp % 10000 / 1000;
    *(str_buff + 3 ) = temp % 1000 / 100;
    *(str_buff + 4 ) = 14;
    *(str_buff + 5 ) = temp % 100 / 10;
    *(str_buff + 6 ) = temp % 10;
    *(str_buff + 7 ) = (disp_type == 0) ? 13 : 12;

    for(int i = 0; i < BUFFER_SIZE; i++) {
        for(int j = 0; j < FONT_HEIGHT; j++) {
            index = ((DISP_LINE + j) << 4) + ((DISP_LINE+ j) << 2) + (i << 1);
            __display_buf[index] = fonts[*(str_buff + i)][j << 1];
            __display_buf[index + 1] = fonts[*(str_buff + i)][(j << 1) + 1];
        }
    }

    kos_free(str_buff);
}

uint8_t old_disp_type = 100;

void display_menu(uint8_t disp_type) {
    uint32_t index;
    
    if(old_disp_type != disp_type) {
        //recover old icon
        if(old_disp_type != (uint8_t)100) {
            for(int i = 0; i < 20; i++) {
                icons[old_disp_type][i] = ~icons[old_disp_type][i];
            }
        }
        //update new icon
        old_disp_type = disp_type;
        for(int i = 0; i < 20; i++) {
            icons[disp_type][i] = ~icons[disp_type][i];
        }
    }
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < ICON_HEIGHT; j++) {
            index = ((MENU_LINE + j) << 4) + ((MENU_LINE+ j) << 2) + (i << 1);
            if(i == 0) {
                __display_buf[index] = icons[0][j << 1];
                __display_buf[index + 1] = icons[0][(j << 1) + 1];
            }else if(i == 1) {
                __display_buf[index] = (icons[1][j << 1] & 0x0F) << 4;
                __display_buf[index + 1] = ((icons[1][(j << 1) + 1] & 0x0F) << 4) | 
                                            ((icons[1][j << 1] & 0xF0) >> 4);
            }else {
                __display_buf[index] = (icons[1][(j << 1) + 1] & 0xF0) >> 4;
            }
        }
    }
}
