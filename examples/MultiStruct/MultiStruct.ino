#include <Arduino.h>
#include <nahs-Bricks-Lib-RTCmem.h>

typedef struct {
  uint counter;
} MyData;

typedef struct {
  uint8_t val1;
  uint16_t val2;
  uint32_t val3;
} MySecondData;

void setup() {
  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Data looks valid: ");
  Serial.println(RTCmem.isValid());

  MyData* data1 = RTCmem.registerData<MyData>();
  MySecondData* data2 = RTCmem.registerData<MySecondData>();
  MyData* data3 = RTCmem.registerData<MyData>();
  Serial.print("data1 counter is: ");
  Serial.println(data1->counter);
  Serial.print("data2 val1 is: ");
  Serial.println(data2->val1);
  Serial.print("data2 val2 is: ");
  Serial.println(data2->val2);
  Serial.print("data2 val3 is: ");
  Serial.println(data2->val3);
  Serial.print("data3 counter is: ");
  Serial.println(data3->counter);

  uint8_t d1c, d2v1, d2v2, d2v3, d3c;
  if (data3->counter < 100) d1c = data3->counter;
  else d1c = 1;
  d2v1 = d1c + 1;
  d2v2 = d2v1 + 1;
  d2v3 = d2v2 + 1;
  d3c = d2v3 + 1;
  Serial.print("Setting data1 counter to: ");
  Serial.println(d1c);
  data1->counter = d1c;
  Serial.print("Setting data2 val1 to: ");
  Serial.println(d2v1);
  data2->val1 = d2v1;
  Serial.print("Setting data2 val2 to: ");
  Serial.println(d2v2);
  data2->val2 = d2v2;
  Serial.print("Setting data2 val3 to: ");
  Serial.println(d2v3);
  data2->val3 = d2v3;
  Serial.print("Setting data3 counter to: ");
  Serial.println(d3c);
  data3->counter = d3c;

  Serial.println("writing RTCmem");
  RTCmem.write();
}

void loop() {
}
