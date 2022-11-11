#include <Arduino.h>
#include <nahs-Bricks-Lib-RTCmem.h>

typedef struct {
  uint counter;
} MyData;

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Data looks valid: ");
  Serial.println(RTCmem.isValid());
  MyData* data1 = RTCmem.registerData<MyData>();
  MyData* data2 = RTCmem.registerData<MyData>();
  Serial.print("data1 counter is: ");
  Serial.println(data1->counter);
  Serial.print("data2 counter is: ");
  Serial.println(data2->counter);

  uint8_t c1, c2;
  if (data2->counter < 100) c1 = data2->counter;
  else c1 = 1;
  c2 = c1 + 1;
  Serial.print("Setting data1 counter to: ");
  Serial.println(c1);
  data1->counter = c1;
  Serial.print("Setting data2 counter to: ");
  Serial.println(c2);
  data2->counter = c2;

  Serial.println("writing RTCmem");
  RTCmem.write();
}

void loop() {
}
