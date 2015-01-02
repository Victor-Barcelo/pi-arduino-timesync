#include <Wire.h>
#include <Time.h>

#define SLAVE_ADDRESS 0x04
#define DEBUG true

bool isTimeSet = false;

void setup(){
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  if(DEBUG) Serial.println("Ready!");
}

void loop(){
  delay(1000);
  if(isTimeSet){
    digitalClockDisplay(); 
  }
}

void receiveData(int byteCount){
  if(DEBUG){
    Serial.print("Number of bytes recieved: ");
    Serial.println(byteCount);
  }
  int cmd = Wire.read();
  if(cmd == 1){
    unsigned long bytes[4];
    int i = 0;
    while(Wire.available()){
      bytes[i] = Wire.read();
      i++;
    }
    setActualTime(bytes);
  }
}

void setActualTime(unsigned long bytes[4]){
  unsigned long result = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);
  setTime(result);
  isTimeSet = true;
}

void digitalClockDisplay(){
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(dayStr(weekday()));
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(monthStr(month()));
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  Serial.print(":");
  if(digits < 10)
  Serial.print('0');
  Serial.print(digits);
}