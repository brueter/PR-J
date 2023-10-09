#include <Wire.h>

const byte DOUT = 0;
const byte CLK = 4;
const byte LED = 1;

void setup() {
  Wire.begin(8);
  Wire.onRequest(rx);
  pinMode(DOUT, INPUT_PULLUP);
  pinMode(CLK, OUTPUT);
  pinMode(LED, OUTPUT);
}

union LongBuffer {
  unsigned long longNumber;
  byte longBytes[3];
};

LongBuffer buffer;

void loop() {
  
}

inline void rx(void) {
  buffer.longNumber = read();
  Wire.write(buffer.longBytes, 3);
}
unsigned long read() {
  unsigned long output = 0;
  byte i;

  digitalWrite(CLK, LOW);
  
  while (digitalRead(DOUT) == HIGH);

  for (i = 0; i < 24; i++) {
    digitalWrite(CLK, HIGH);
    output = output << 1;
    digitalWrite(CLK, LOW);
    if (digitalRead(DOUT)) output++;
  }

  digitalWrite(CLK, HIGH);
  output = output ^ 0x800000;
  digitalWrite(CLK, LOW);
  
  return output;
}
