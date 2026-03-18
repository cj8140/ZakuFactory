//Elehobby3 Coding P3 VF-11B_V1.0 2025.11 By 
#define SW_rocket 2 // Rocket Fading Switch 스위치를 누르면 LED_rocket의 밝기가 점점 밝아지다 150에 다다르면 갑자기 255로 밝아짐. 그상태에서 약 5초 유지 후 꺼짐.
#define LED_rocket 3 // Rocket LED PWM pin connect to Mosfet Gate with 10k COB LED제어용 모스펫 gate
#define LED_cockpit 5 // Cockpit PWM pin 전원 켜면 상시 켜짐.
#define LED_foot 6 // Foot Nozzle PWM pin A1의 값에 따라 LED_foot의 밝기가 0~255로 변환 
#define POT_foot A1 // Foot Nozzle Bright control POT 

void setup() {
  pinMode(SW_rocket, INPUT_PULLUP);
}

void loop() {
  analogWrite(LED_cockpit, 100);

  if (digitalRead(SW_rocket) == LOW) {
    analogWrite(LED_rocket, 255);
  }
  else {
    analogWrite(LED_rocket, 0);
  }

  for(int i = 0; i <= 255; i++) {
    analogWrite(LED_foot, i);
    delay(10);
  }
  for(int i = 255; i >= 0; i--) {
    analogWrite(LED_foot, i);
    delay(10);
  }
}