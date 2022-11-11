#include <Arduino.h>
#include <nahs-Bricks-Lib-RTCmem.h>

typedef struct {
  uint counter;
} SmallData;

typedef struct {
  uint counter1;
  uint counter2;
  uint counter3;
} BigData;

typedef struct {
  uint8_t counter;
} FragmentedData1;

typedef struct {
  uint8_t counter;
  uint counter2;
} FragmentedData2;

void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.println("\nEmpty:");
  Serial.print("using: ");
  Serial.print(RTCmem.getSpaceUsed());
  Serial.print("/");
  Serial.print(RTCmem.getSpaceTotal());
  Serial.print(" free: ");
  Serial.println(RTCmem.getSpaceLeft());

  SmallData* data1 = RTCmem.registerData<SmallData>();

  Serial.println("\nSmallData:");
  Serial.print("using: ");
  Serial.print(RTCmem.getSpaceUsed());
  Serial.print("/");
  Serial.print(RTCmem.getSpaceTotal());
  Serial.print(" free: ");
  Serial.println(RTCmem.getSpaceLeft());

  BigData* data2 = RTCmem.registerData<BigData>();

  Serial.println("\nBigData:");
  Serial.print("using: ");
  Serial.print(RTCmem.getSpaceUsed());
  Serial.print("/");
  Serial.print(RTCmem.getSpaceTotal());
  Serial.print(" free: ");
  Serial.println(RTCmem.getSpaceLeft());

  FragmentedData1* data3 = RTCmem.registerData<FragmentedData1>();

  Serial.println("\nFragmentedData1:");
  Serial.print("using: ");
  Serial.print(RTCmem.getSpaceUsed());
  Serial.print("/");
  Serial.print(RTCmem.getSpaceTotal());
  Serial.print(" free: ");
  Serial.println(RTCmem.getSpaceLeft());

  FragmentedData2* data4 = RTCmem.registerData<FragmentedData2>();

  Serial.println("\nFragmentedData2:");
  Serial.print("using: ");
  Serial.print(RTCmem.getSpaceUsed());
  Serial.print("/");
  Serial.print(RTCmem.getSpaceTotal());
  Serial.print(" free: ");
  Serial.println(RTCmem.getSpaceLeft());
}

void loop() {
}
