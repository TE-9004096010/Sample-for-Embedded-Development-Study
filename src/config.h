#ifndef CONFIG_H
#define CONFIG_H

// STM32F103C8T6 Pin Definitions

// サーボモーターピン定義 (PWM対応ピン)
#define SERVO_BACKPACK     PA6  // Timer 3, Channel 1
#define SERVO_WING_LEFT    PA7  // Timer 3, Channel 2
#define SERVO_WING_RIGHT   PB0  // Timer 3, Channel 3

// LEDピン定義（PS装甲エフェクト用）
#define PS_ARMOR_LED_1     PB12
#define PS_ARMOR_LED_2     PB13
#define PS_ARMOR_LED_3     PB14
#define PS_ARMOR_LED_4     PB15

// LCD接続ピン定義
#define LCD_RS    PA8
#define LCD_ENABLE PA9
#define LCD_D4     PA10
#define LCD_D5     PA11
#define LCD_D6     PA12
#define LCD_D7     PA15

// ブザーピン定義 (PWM対応)
#define BUZZER_PIN PB1  // Timer 3, Channel 4

// ボタンピン定義 (デジタルピン、内部プルアップ使用)
#define BUTTON_AILE     PC13  // エールストライカー
#define BUTTON_SWORD    PC14  // ソードストライカー
#define BUTTON_LAUNCHER PC15  // ランチャーストライカー
#define BUTTON_BASE     PA0   // 素体モード

// タイミング定数
#define DEBOUNCE_DELAY 300    // チャタリング防止遅延(ms)
#define SERVO_DELAY    500    // サーボ動作遅延(ms)
#define LED_FADE_STEP  8      // LEDフェード段階 (STM32は高速なので大きく)
#define LED_FADE_DELAY 10     // LEDフェード遅延(ms) (STM32は高速)

// 音響効果定数
#define PS_ARMOR_FREQ   800   // PS装甲音周波数
#define ATTACH_FREQ_1   1000  // 装着音1
#define ATTACH_FREQ_2   1200  // 装着音2
#define ATTACH_FREQ_3   1500  // 装着音3

// STM32固有設定
#define PWM_FREQUENCY   50    // サーボPWM周波数 (Hz)
#define PWM_RESOLUTION  16    // PWM分解能 (bits)

#endif