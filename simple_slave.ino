#include <ModbusRtu.h>
HardwareSerial monitor(PA10, PA9);
HardwareSerial modbus(PA3, PA2);
#define SERIAL_PORT monitor
#define SLAVE_ID    1
#define SLAVE_PORT  modbus
#define SLAVE_DE    PA4
// uint16_t au16data[16] = { 3, 1415, 9265, 4, 2, 7182, 28182, 8, 0, 0, 0,111, 0, 0, 1, -1 };
uint16_t temp = 0;
uint16_t humi = 0;
uint16_t vary = 0;
uint16_t val_1;
uint16_t val_2;
uint16_t val_3;
uint16_t tx_data[6]={temp,humi,vary,val_1,val_2,val_3};
Modbus slave(SLAVE_ID,SLAVE_PORT,SLAVE_DE); 
void setup() {
  SERIAL_PORT.begin(115200); 
  SLAVE_PORT.begin(9600);
  slave.start();
}
void loop() {

  temp = temp + 1;
  humi = humi + 2;
  vary = vary + 5;
  tx_data[0] = temp;
  tx_data[1] = humi;
  tx_data[2] = vary;
  // SERIAL_PORT.println(temp);
  delay(50);
  slave.poll(tx_data,6);// data , length
  if(temp > 300){
    temp = 0 ; humi = 0 ; vary = 0 ;
  }
  val_1 = tx_data[3];
  SERIAL_PORT.println(val_1);
  val_2 = tx_data[4];
  SERIAL_PORT.println(val_2);
  val_3 = tx_data[5];
  SERIAL_PORT.println(val_3);
}
