#include <NeoSWSerial.h>
extern "C"
{
  #include "min.h"
}
                    //RX, TX
NeoSWSerial serial_sw( 8, 9 );
struct min_context min_ctx;

void min_tx_start(uint8_t port){};
void min_tx_finished(uint8_t port){};
void min_tx_byte(uint8_t port, uint8_t byte)
{
 serial_sw.write(byte);
}
uint16_t min_tx_space(uint8_t port){return 512;}
uint32_t min_time_ms(void)
{
  return millis();
}
void min_application_handler(uint8_t min_id, uint8_t const *min_payload, 
                              uint8_t len_payload, uint8_t port)
{
}
void setup() {
  serial_sw.begin(9600);
  min_init_context(&min_ctx, 0);
}
void min_handle()
{
  uint8_t data;
  uint8_t len =0;
  if(serial_sw.available()>0)
  {
    data = serial_sw.read();;
    len = 1;
  }
  min_poll(&min_ctx,&data,len);
}
uint8_t sta;
void loop() {
  min_handle();
  static unsigned long t_blink;
  if(millis() - t_blink>=1000)
  {
    sta = !sta;
    min_send_frame(&min_ctx,0,&sta,1);
    t_blink = millis();
  }
}
