#include <Arduino.h>

// STM32用基本テストプログラム
// このプログラムは各コンポーネントの動作を個別にテストします

// ピン定義 (STM32F103C8T6)
#define SERVO_PIN PA6
#define LED_PIN PB12
#define BUTTON_PIN PC13
#define BUZZER_PIN PB1

void setup() {
  Serial.begin(9600);
  
  // ピン初期化
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 内部プルアップ使用
  
  Serial.println("Strike Gundam Basic Test (STM32)");
  Serial.println("Press button to test components");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Testing components...");
    
    // LED テスト
    Serial.println("LED Test");
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(LED_PIN, LOW);
    delay(500);
    
    // ブザーテスト
    Serial.println("Buzzer Test");
    tone(BUZZER_PIN, 1000, 200);
    delay(300);
    tone(BUZZER_PIN, 1500, 200);
    delay(300);
    
    Serial.println("Test complete");
    delay(1000); // チャタリング防止
  }
  
  delay(50);
}