#include <lcom/lcf.h>
#include "../macros/mouse_macros.h"
#include "../macros/keyboard_macros.h"
#include "keyboard.h"
#include "utils.h"

#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED

int (mouse_subscribe_int)(uint8_t *bit_no);
int (mouse_unsubscribe_int)();
void (mouse_ih)();
int (mouse_parse_packet)(struct packet *pp);
int (disable_irq());
int (enable_irq());
int (disable_data_reporting)();
int (mouse_issue_cmd)(uint8_t cmd);
int (mouse_read_byte)(uint8_t *byte);

#endif 
