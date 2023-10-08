#include <Wire.h>

const byte DOUT = 0;
const byte CLK = 4;
const byte LED = 1;
const int MEDIAN_FILTER_SIZE = 3; // Adjust this value based on your requirements
const int LOW_PASS_FILTER_SIZE = 10;

void setup() {
  Wire.begin(8);
  Wire.onRequest(rx);
  pinMode(DOUT, INPUT_PULLUP);
  pinMode(CLK, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  
}

inline void rx(void) {
  unsigned long smoothedValue = readAndFilter();
  byte longBytes[4];
  memcpy(longBytes, &smoothedValue, 4);
  Wire.write(longBytes, 4);
}

unsigned long readAndFilter() {
  unsigned long buffer[MEDIAN_FILTER_SIZE];
  
  for (int i = 0; i < MEDIAN_FILTER_SIZE; i++) {
    buffer[i] = read();
  }

  unsigned long median = calculateMedian(buffer, MEDIAN_FILTER_SIZE);

  static unsigned long filterBuffer[LOW_PASS_FILTER_SIZE];
  static int index = 0;
  static unsigned long sum = 0;
  
  filterBuffer[index] = median;
  sum += filterBuffer[index] - filterBuffer[(index + 1) % LOW_PASS_FILTER_SIZE];
  index = (index + 1) % LOW_PASS_FILTER_SIZE;
  
  return sum / LOW_PASS_FILTER_SIZE;
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

unsigned long calculateMedian(unsigned long* values, int length) {
  // Sort the array to find the median
  for (int i = 0; i < length - 1; i++) {
    for (int j = i + 1; j < length; j++) {
      if (values[i] > values[j]) {
        unsigned long temp = values[i];
        values[i] = values[j];
        values[j] = temp;
      }
    }
  }

  // The median is at the middle of the sorted array
  return values[length / 2];
}
