#ifndef CONFIG_H
#define CONFIG_H

// サーボモーターピン定義
#define SERVO_BACKPACK     9   // バックパック回転用
#define SERVO_WING_LEFT    6   // 左ウイング/武装用
#define SERVO_WING_RIGHT   7   // 右ウイング/武装用

// LEDピン定義（PS装甲エフェクト用）
#define PS_ARMOR_LED_START 8   // LED開始ピン
// 8, 9, 10, 11番ピンを使用

// LCD接続ピン定義
#define LCD_RS    12
#define LCD_ENABLE 11
#define LCD_D4     5
#define LCD_D5     4
#define LCD_D6     3
#define LCD_D7     2

// ブザーピン定義
#define BUZZER_PIN 13

// ボタンピン定義（アナログピン使用）
#define BUTTON_AILE     A0  // エールストライカー
#define BUTTON_SWORD    A1  // ソードストライカー
#define BUTTON_LAUNCHER A2  // ランチャーストライカー
#define BUTTON_BASE     A3  // 素体モード

// タイミング定数
#define DEBOUNCE_DELAY 300    // チャタリング防止遅延(ms)
#define SERVO_DELAY    500    // サーボ動作遅延(ms)
#define LED_FADE_STEP  5      // LEDフェード段階
#define LED_FADE_DELAY 20     // LEDフェード遅延(ms)

// 音響効果定数
#define PS_ARMOR_FREQ   800   // PS装甲音周波数
#define ATTACH_FREQ_1   1000  // 装着音1
#define ATTACH_FREQ_2   1200  // 装着音2
#define ATTACH_FREQ_3   1500  // 装着音3

#endif