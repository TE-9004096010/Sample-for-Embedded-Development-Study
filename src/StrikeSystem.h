#ifndef STRIKE_SYSTEM_H
#define STRIKE_SYSTEM_H

#include <Arduino.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// ストライカーパックタイプ定義
enum StrikerType {
  NO_PACK = 0,
  AILE_STRIKER = 1,
  SWORD_STRIKER = 2,
  LAUNCHER_STRIKER = 3,
  INTEGRATED_WEAPONS_STRIKER = 4,
  OHTORI_STRIKER = 5,
  PERFECT_STRIKE = 6
};

class ChagingStrikerPackSystem {
private:
  StrikerType currentStriker;
  Servo backpackServo;
  Servo wingServo[2];  // ウイング用サーボ
  int buzzerPin;
  LiquidCrystal lcd;
  
public:
  ChagingStrikerPackSystem();
  
  void initialize();
  void changeStriker(StrikerType newStriker);
  
private:
  void executeChangeSequence(StrikerType from, StrikerType to);
  void activatePSArmor();
  void deactivatePSArmor();
  void detachCurrentStriker(StrikerType striker);
  void attachNewStriker(StrikerType striker);
  void playPSArmorSound();
  void playAttachSound();
  void displayStatus();
};

#endif