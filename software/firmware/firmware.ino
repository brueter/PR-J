#include <Wire.h>

const byte DOUT = 0;
const byte CLK = 4;
const byte LED = 1;

void setup() {
  digitalWrite(LED, LOW);
  Wire.begin(0x69);                 // I2C address
  Wire.onRequest(tx);
  Wire.onReceive(rx);
}

void loop() {

}

inline void tx(void) {
  Wire.write(read());
}

unsigned long lowThreshold = 0;
unsigned long highThreshold = 0;

#define OP_LED_OFF      0
#define OP_LED_LMH      1
#define OP_LED_HML      2
#define OP_LED_HLH      3

#define OP_STRAIN_LOW   4
#define OP_STRAIN_HIGH  5

int ledEncoding = 0;

#define IS_OP_LED(opCode) (opCode < OP_STRAIN_LOW)

void rx(int bytes) {
  while(Wire.available()) {
    byte opCode = Wire.read();

    if (IS_OP_LED(opCode)) {
    ledEncoding = opCode;
    } else {
      unsigned long value = 0;
      
      for (byte i = 0 ; i < 2 ; i++) {
        value += Wire.read();
        
        if(i == 1) break;

        value = value << 8;
      }
      
      if (opCode == OP_STRAIN_LOW) {
          lowThreshold = value;
      } else {
          highThreshold = value;
      }
    }
  }
}

int ledBrightness = 0;

unsigned long read() {
  int ledWrite = 0;
  unsigned long output = 0;
  byte i;

  digitalWrite(CLK, LOW);

  while (digitalRead(DOUT));         // wait for DOUT to go low, indicating ready to output

  for (i = 0 ; i < 24 ; i++) {       // send 25 pulses, indicating to read from channel A with a gain of 128
    digitalWrite(CLK, HIGH);         // clock high
    output = output << 1;            // bit shift left
    digitalWrite(CLK, LOW);          // clock low
    if (digitalRead(DOUT)) output++; // set last bit of output based on DOUT
  }

  digitalWrite(CLK, HIGH);           // finish signal
  output = output ^ 0x800000;        // clipping
  digitalWrite(CLK, LOW);            // keep CLK low to prevent sleep

  switch(ledEncoding) {
    case OP_LED_LMH:
      ledWrite = ((output - lowThreshold) << 8) / (highThreshold - lowThreshold);
      break;
    case OP_LED_HML:
      ledWrite = 255 - (((output - lowThreshold) << 8) / (highThreshold - lowThreshold));
      break;
    case OP_LED_HLH:
      unsigned long middle;
      middle = lowThreshold + ((highThreshold - lowThreshold) >> 1);
      
      if (output <= middle) {
        ledWrite = 255 - ((output - lowThreshold) << 8) / (middle - lowThreshold);
      } else {
        ledWrite = ((output - middle) << 8) / (highThreshold - middle);
      }
      break;
    default:
      ledWrite = 0;
      break;
  }

  ledWrite = ledWrite < 0 ? 0 : (ledWrite > 255 ? 255 : ledWrite);  // Clip at 0 and 255

  if(ledWrite != ledBrightness) {
    analogWrite(LED, ledWrite);
    ledBrightness = ledWrite;
  }

  return output;
}
