#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"
#include "keyboard_macros.h"
#include "utils.h"

extern uint8_t bb[];
extern uint8_t two_byte;
extern int size;
extern int kbd_error;
uint8_t kbc_cmd_byte=0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status, r;
  uint8_t keyboard_sel;
  message msg;
  bool make;

  if(timer_subscribe_int(&keyboard_sel))
    return 1;
  int irq_set = BIT(keyboard_sel);
  int process = 1;

    while( process ) { /* You may want to use a different condition */
     /* Get a request message. */
     if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
         printf("driver_receive failed with: %d", r);
         continue;
     }
     if (is_ipc_notify(ipc_status)) { /* received notification */
         switch (_ENDPOINT_P(msg.m_source)) {
             case HARDWARE: /* hardware interrupt notification */       
                 if (msg.m_notify.interrupts & irq_set) { /* subscribed interrupt */
                      kbc_ih();/* process it */
                      if(two_byte || kbd_error){
                        continue;
                      }
                      keyboard_get_code(&make, bb);
                      kbd_print_scancode(make, size, bb);
                 }
                 break;
             default:
                 break; /* no other notifications expected: do nothing */ 
         }
         if(keyboard_check_esc(bb))
            process=0;
     } else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
     }
  }
  timer_unsubscribe_int();
  kbd_print_no_sysinb(getCounter());
  return OK;
}

int(kbd_test_poll)() {
  /* reads the command byte and stores it */
  kbd_write_command(READ_CMD_BYTE, 0, false);
  kbd_read_outbuf(&kbc_cmd_byte);

  int processing = 1;
  bool make;

  while(processing){
    kbd_polling();/* process it */
    if(two_byte || kbd_error){
      continue;
    }
    keyboard_get_code(&make, bb);
    kbd_print_scancode(make, size, bb);
    if(keyboard_check_esc(bb)){
        processing=0;
    }
  }

  kbd_enable_int();
  kbd_print_no_sysinb(getCounter());
  return OK;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

