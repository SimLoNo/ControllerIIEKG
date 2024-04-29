#include <Arduino.h>

std::array<int, 5> heartRate{};
std::array<int, 5> altRate{};
int currentHeartrate = 0;
int lightPin = 5;
int analogPin = 4;
hw_timer_t *My_timer = NULL;
int ekgDial;
bool displayMode;
void IRAM_ATTR onTimer();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(lightPin, OUTPUT);
  heartRate = {6, 10, 25, 8, 3};
  altRate = {25, 15, 30, 3, 14};
  displayMode = false;
  
  Serial.print("Size of array is: ");
  Serial.println(sizeof(heartRate) / sizeof(heartRate[0]));
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 10000000, true);
  timerAlarmEnable(My_timer); //Just Enable
  
}

void loop() {
  // put your main code here, to run repeatedly:
  int analogInput = analogRead(analogPin);
  double percentageDouble = (double)analogInput / 4095 * 100;
  ekgDial = (int)percentageDouble;
  if (ekgDial < 10)
  {
    ekgDial = 10;
  }
  
  Serial.print("Dial is at percentage: ");
  Serial.println(ekgDial);
  if (currentHeartrate == sizeof(heartRate) / sizeof(heartRate[0]))
  {
    currentHeartrate = 0;
  }
}

void IRAM_ATTR onTimer(){
  //Serial.print("Index of array: ");
  //Serial.println(currentHeartrate);
  if (displayMode == true)
  {
    int volume = ekgDial / 100;
    Serial.print(">HeartRate:");
    Serial.println(heartRate[currentHeartrate] * volume);
  }
  else{
    Serial.print(">AltRate:");
    Serial.println(heartRate[currentHeartrate]);
  }
  currentHeartrate++;
  

}
