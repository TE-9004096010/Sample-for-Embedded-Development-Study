#include "StrikeSystem.h"
#include "config.h"

ChagingStrikerPackSystem::ChagingStrikerPackSystem() : lcd(LCD_RS, LCD_ENABLE, LCD_D4, LCD_D5, LCD_D6, LCD_D7) {}

void ChagingStrikerPackSystem::initialize() {
  currentStriker = NO_PACK;
  
  // サーボ初期化
  backpackServo.attach(SERVO_BACKPACK);
  wingServo[0].attach(SERVO_WING_LEFT);
  wingServo[1].attach(SERVO_WING_RIGHT);
  
  // PS装甲LED初期化
  for(int i = 0; i < 4; i++) {
    psArmorLED[i] = PS_ARMOR_LED_START + i;
    pinMode(psArmorLED[i], OUTPUT);
    digitalWrite(psArmorLED[i], LOW);
  }
  
  // ブザー初期化
  buzzerPin = BUZZER_PIN;
  pinMode(buzzerPin, OUTPUT);
  
  // LCD初期化
  lcd.begin(16, 2);
  lcd.clear();
  
  // 初期ポジション設定
  backpackServo.write(90);
  wingServo[0].write(0);
  wingServo[1].write(0);
  
  displayStatus();
}

void ChagingStrikerPackSystem::changeStriker(StrikerType newStriker) {
  if (newStriker == currentStriker) return;
  
  lcd.clear();
  lcd.print("Changing...");
  
  // 換装シーケンス実行
  executeChangeSequence(currentStriker, newStriker);
  currentStriker = newStriker;
  displayStatus();
}

void ChagingStrikerPackSystem::executeChangeSequence(StrikerType from, StrikerType to) {
  // 1. PS装甲展開
  activatePSArmor();
  
  // 2. 現在パック取り外し
  detachCurrentStriker(from);
  
  // 3. 新パック装着
  attachNewStriker(to);
  
  // 4. PS装甲収納
  deactivatePSArmor();
}

void ChagingStrikerPackSystem::activatePSArmor() {
  // PS装甲展開エフェクト
  for(int brightness = 0; brightness <= 255; brightness += 5) {
    for(int i = 0; i < 4; i++) {
      analogWrite(psArmorLED[i], brightness);
    }
    playPSArmorSound();
    delay(20);
  }
  delay(500);
}

void ChagingStrikerPackSystem::deactivatePSArmor() {
  // PS装甲収納エフェクト
  for(int brightness = 255; brightness >= 0; brightness -= 5) {
    for(int i = 0; i < 4; i++) {
      analogWrite(psArmorLED[i], brightness);
    }
    delay(20);
  }
  
  // 完全消灯
  for(int i = 0; i < 4; i++) {
    digitalWrite(psArmorLED[i], LOW);
  }
}

void ChagingStrikerPackSystem::detachCurrentStriker(StrikerType striker) {
  switch(striker) {
    case AILE_STRIKER:
      // ウイング格納
      wingServo[0].write(0);
      wingServo[1].write(0);
      delay(500);
      break;
      
    case SWORD_STRIKER:
      // ソード格納モーション
      for(int pos = 180; pos >= 0; pos -= 2) {
        wingServo[0].write(pos);
        delay(10);
      }
      break;
      
    case LAUNCHER_STRIKER:
      // ランチャー格納モーション
      wingServo[0].write(0);
      wingServo[1].write(0);
      delay(500);
      break;
      
    case NO_PACK:
      // 既に素体状態
      break;
  }
  
  // バックパック中央位置
  backpackServo.write(90);
  delay(500);
}

void ChagingStrikerPackSystem::attachNewStriker(StrikerType striker) {
  playAttachSound();
  
  switch(striker) {
    case AILE_STRIKER:
      // エールストライカー装着
      backpackServo.write(45);
      delay(500);
      // ウイング展開
      wingServo[0].write(90);
      wingServo[1].write(90);
      delay(1000);
      break;
      
    case SWORD_STRIKER:
      // ソードストライカー装着
      backpackServo.write(135);
      delay(500);
      // シュベルトゲベール展開モーション
      for(int pos = 0; pos <= 180; pos += 2) {
        wingServo[0].write(pos);
        delay(10);
      }
      delay(500);
      break;
      
    case LAUNCHER_STRIKER:
      // ランチャーストライカー装着
      backpackServo.write(180);
      delay(500);
      // ランチャー展開
      wingServo[0].write(45);
      wingServo[1].write(45);
      delay(1000);
      break;
      
    case NO_PACK:
      // 素体状態
      backpackServo.write(90);
      wingServo[0].write(0);
      wingServo[1].write(0);
      delay(500);
      break;
  }
}

void ChagingStrikerPackSystem::playPSArmorSound() {
  tone(buzzerPin, 800, 30);
}

void ChagingStrikerPackSystem::playAttachSound() {
  // 換装完了音
  tone(buzzerPin, 1000, 200);
  delay(250);
  tone(buzzerPin, 1200, 200);
  delay(250);
  tone(buzzerPin, 1500, 300);
}

void ChagingStrikerPackSystem::displayStatus() {
  lcd.clear();
  lcd.print("Strike Gundam");
  lcd.setCursor(0, 1);
  
  switch(currentStriker) {
    case NO_PACK:
      lcd.print("Base Mode");
      break;
    case AILE_STRIKER:
      lcd.print("Aile Striker");
      break;
    case SWORD_STRIKER:
      lcd.print("Sword Striker");
      break;
    case LAUNCHER_STRIKER:
      lcd.print("Launcher Striker");
      break;
  }
}