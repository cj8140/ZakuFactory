//Elehobby3 Coding P3 VF-11B_V1.0 2025.11.07 By C.J.
#define SW_ROCKET 2 // Rocket Fading Switch 스위치를 누르면 LED_ROCKET의 밝기가 점점 밝아지다 150에 다다르면 갑자기 255로 밝아짐. 그상태에서 약 5초 유지 후 꺼짐.
#define LED_ROCKET 3 // Rocket LED PWM pin connect to Mosfet Gate with 10k COB LED제어용 모스펫 gate
#define LED_COCKPIT 5 // Cockpit PWM pin 전원 켜면 상시 켜짐.
#define LED_FOOT 6 // Foot Nozzle PWM pin A1의 값에 따라 LED_FOOT의 밝기가 0~255로 변환 
#define POT_FOOT A1 // Foot Nozzle Bright control POT 

int brightness_rocket = 0;

void setup() {
  pinMode(SW_ROCKET, INPUT_PULLUP);

  analogWrite(LED_COCKPIT, 150);
  analogWrite(LED_ROCKET, 0);
}

void loop() {
  int brightness_foot = map(analogRead(POT_FOOT), 0, 1023, 0, 255); // foot 밝기 제어
  analogWrite(LED_FOOT, brightness_foot);
  
  //로켓 밝기 제어
  analogWrite(LED_ROCKET, brightness_rocket);
  // 버튼 눌리면 밝아지게
  if (digitalRead(SW_ROCKET) == LOW) {
    //초기에 충전
    if(brightness_rocket < 100) {
      brightness_rocket += 1;
      delay(20);
    }
    //임계값 넘어가면 255로 고정
    else {
      brightness_rocket = 255;
    }
  }
  // 땠을 때 밝기를 0으로. for문 통제로 제거하면 페이딩 없어짐
  else {
    //끝까지 눌렸을때
    if(brightness_rocket == 255) {
      delay(500);
      // 일렁거리는 페이딩 3번 반복. for문 제거하면 없어짐
      for(int i = 0; i < 3; i++) {
        for(int j = 255; j >= 150; j--) {
          analogWrite(LED_ROCKET, j);
          delay(8);
        }
        for(int j = 150; j <= 255; j++) {
          analogWrite(LED_ROCKET, j);
          delay(3);
        }
      }
      // 꺼지는 페이딩. for문 제거하면 없어짐
      for(int i = 255; i >= 0; i--) {
        analogWrite(LED_ROCKET, i);
        delay(8);
      }
    }
    // 중간에 때졌을때 꺼지는 용
    else if(brightness_rocket > 0) {
      for (int i = brightness_rocket; i >= 0; i--){
        analogWrite(LED_ROCKET, i);
        delay(10);
      }
    }
    brightness_rocket = 0;
  }
}