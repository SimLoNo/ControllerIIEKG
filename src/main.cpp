#include <Arduino.h>

std::array<int, 5> heartRate{};
int currentHeartrate = 0;
int lightPin = 4;
hw_timer_t *My_timer = NULL;
int static_variable = 0;
void IRAM_ATTR onTimer();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(lightPin, OUTPUT);
  heartRate = {6, 10, 25, 8, 3};
  
  Serial.print("Size of array is: ");
  Serial.println(sizeof(heartRate) / sizeof(heartRate[0]));
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 2000000, true);
  timerAlarmEnable(My_timer); //Just Enable
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (currentHeartrate == sizeof(heartRate) / sizeof(heartRate[0]))
  {
    currentHeartrate = 0;
  }
}

void IRAM_ATTR onTimer(){
  //Serial.print("Index of array: ");
  //Serial.println(currentHeartrate);
  Serial.print(">HeartRate:");
  Serial.println(heartRate[currentHeartrate]);
  currentHeartrate++;
  

}
