
#include <due_can.h>
#include <iso-tp.h>

IsoTp isotp(&Can0);

struct Message_t TxMsg, RxMsg;
uint8_t sf_test[] = { 0x00, 0x01 };
uint8_t mf_test[] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, \
                      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F };
uint32_t can_id = 0x7E0;

void setup()
{
  Serial.begin(1000000);
	Can0.enable();
  Can0.begin(500000, 255); //enable bus at 500k speed
  Can0.watchFor(); //allow all traffic through
}

void loop()
{ 
  TxMsg.len=sizeof(mf_test);
  TxMsg.Buffer=(uint8_t *)calloc(MAX_MSGBUF,sizeof(uint8_t));
  TxMsg.tx_id=can_id;
  TxMsg.rx_id=can_id+0x20;
  memcpy(TxMsg.Buffer,sf_test,sizeof(sf_test));
  Serial.println(F("Send..."));
  isotp.send(&TxMsg);
  
  RxMsg.tx_id=can_id;
  RxMsg.rx_id=can_id+0x20;
  RxMsg.Buffer=(uint8_t *)calloc(MAX_MSGBUF,sizeof(uint8_t));
  Serial.println(F("Receive..."));
  isotp.receive(&RxMsg);
	isotp.print_buffer(RxMsg.rx_id, RxMsg.Buffer, RxMsg.len);
}
