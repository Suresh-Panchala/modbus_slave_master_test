#include <ModbusMaster.h>
#include <SoftwareSerial.h>
#define RS485_CONTROL 8
SoftwareSerial modbus(18,17);

ModbusMaster node;

void preTransmission() {
  digitalWrite(RS485_CONTROL, HIGH);
}

void postTransmission() {
  digitalWrite(RS485_CONTROL, LOW);
}

void setup() {
  Serial.begin(115200);
  modbus.begin(9600); // RS485 on Serial2
  pinMode(RS485_CONTROL, OUTPUT);
  digitalWrite(RS485_CONTROL, LOW);

  node.begin(1, modbus); // Slave ID = 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}
int a = 0,b = 0, c=0;
void loop() {
  // Write to holdingRegs[2] and [3]
  a=a+1;
  b=b+2;
  c=c+3;
  node.writeSingleRegister(3, a);     // e.g., trigger relay
  node.writeSingleRegister(4, b);  // e.g., set threshold
  node.writeSingleRegister(5, c); 
  delay(100);
  if(c>350){
    a = 0; b = 0; c = 0;
  }
  // Read holdingRegs[0] and [1]
  uint8_t result = node.readHoldingRegisters(0, 3);
  if (result == node.ku8MBSuccess) {
    int temp     = node.getResponseBuffer(0) ;
    int humidity = node.getResponseBuffer(1);
    int vary     = node.getResponseBuffer(2);
    Serial.print("Temp: "); Serial.print(temp);
    Serial.print(" °C | Humidity: "); Serial.print(humidity);
    Serial.print(" °C |Vary : "); Serial.println(vary);
  } else {
    Serial.println("Modbus read failed");
  }

  delay(100);
}