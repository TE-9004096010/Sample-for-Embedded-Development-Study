#include <Servo.h>
#include <LiquidCrystal.h>
#include "StrikeSystem.h"
#include "config.h"

// グローバルインスタンス
ChagingStrikerPackSystem strikeSystem;

void setup() {
  Serial.begin(9600);
  
  // ボタン初期化
  pinMode(BUTTON_AILE, INPUT_PULLUP);
  pinMode(BUTTON_SWORD, INPUT_PULLUP);
  pinMode(BUTTON_LAUNCHER, INPUT_PULLUP);
  pinMode(BUTTON_BASE, INPUT_PULLUP);
  
  strikeSystem.initialize();
  
  Serial.println("Strike Gundam System Ready!");
}

void loop() {
  // ボタン入力チェック
  if (digitalRead(BUTTON_AILE) == LOW) {
    strikeSystem.changeStriker(AILE_STRIKER);
    delay(300); // チャタリング防止
  }
  
  if (digitalRead(BUTTON_SWORD) == LOW) {
    strikeSystem.changeStriker(SWORD_STRIKER);
    delay(300);
  }
  
  if (digitalRead(BUTTON_LAUNCHER) == LOW) {
    strikeSystem.changeStriker(LAUNCHER_STRIKER);
    delay(300);
  }
  
  if (digitalRead(BUTTON_BASE) == LOW) {
    strikeSystem.changeStriker(NO_PACK);
    delay(300);
  }
}