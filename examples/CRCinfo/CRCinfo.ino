#include <Arduino.h>
#include <nahs-Bricks-Lib-RTCmem.h>

typedef struct {
  uint counter;
} MyData;

void setup() {
  Serial.begin(115200);
  Serial.println();

  MyData* data1 = RTCmem.registerData<MyData>();
  MyData* data2 = RTCmem.registerData<MyData>();
  Serial.print("stored CRC is: ");
  Serial.println(RTCmem.crcStored(), HEX);

  Serial.print("calculated CRC is: ");
  Serial.println(RTCmem.crcCalculated(), HEX);

  Serial.println("Changing the stored data");
  if (data2->counter < 100) data1->counter = data2->counter + 1;
  else data1->counter = 1;
  data2->counter = data1->counter + 1;

  Serial.println("Recalculating CRC");
  RTCmem.reCalculateCrc();

  Serial.print("calculated CRC is now: ");
  Serial.println(RTCmem.crcCalculated(), HEX);

  Serial.println("writing RTCmem");
  RTCmem.write();
}

void loop() {
}
