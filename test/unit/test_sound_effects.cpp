#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock_arduino.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrictMock;

class SoundEffectsTest : public ::testing::Test {
protected:
    void SetUp() override {
        stm32Mock = &ArduinoMock::getInstance();
    }
    
    void TearDown() override {
        ::testing::Mock::VerifyAndClearExpectations(stm32Mock);
    }
    
    ArduinoMock* stm32Mock;
};

// 警告音テスト
TEST_F(SoundEffectsTest, WarningToneTest) {
    // 警告音のパターン (短-短-長)
    InSequence seq;
    
    // 短音1
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1000, 200));
    EXPECT_CALL(*stm32Mock, delay(250));
    
    // 短音2
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1000, 200));
    EXPECT_CALL(*stm32Mock, delay(250));
    
    // 長音
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1000, 500));
    EXPECT_CALL(*stm32Mock, delay(600));
    
    // 警告音実行
    tone(BUZZER_PIN, 1000, 200);
    delay(250);
    tone(BUZZER_PIN, 1000, 200);
    delay(250);
    tone(BUZZER_PIN, 1000, 500);
    delay(600);
}

// 成功音テスト
TEST_F(SoundEffectsTest, SuccessToneTest) {
    // 上昇音階パターン
    InSequence seq;
    
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 523, 150)); // C5
    EXPECT_CALL(*stm32Mock, delay(180));
    
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 659, 150)); // E5
    EXPECT_CALL(*stm32Mock, delay(180));
    
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 784, 300)); // G5
    EXPECT_CALL(*stm32Mock, delay(350));
    
    // 成功音実行
    tone(BUZZER_PIN, 523, 150); // C5
    delay(180);
    tone(BUZZER_PIN, 659, 150); // E5
    delay(180);
    tone(BUZZER_PIN, 784, 300); // G5
    delay(350);
}

// エラー音テスト
TEST_F(SoundEffectsTest, ErrorToneTest) {
    // 下降音階パターン
    InSequence seq;
    
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 880, 200)); // A5
    EXPECT_CALL(*stm32Mock, delay(220));
    
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 659, 200)); // E5
    EXPECT_CALL(*stm32Mock, delay(220));
    
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 440, 400)); // A4
    EXPECT_CALL(*stm32Mock, delay(450));
    
    // エラー音実行
    tone(BUZZER_PIN, 880, 200); // A5
    delay(220);
    tone(BUZZER_PIN, 659, 200); // E5
    delay(220);
    tone(BUZZER_PIN, 440, 400); // A4
    delay(450);
}

// ブザー連続音テスト
TEST_F(SoundEffectsTest, ContinuousBuzzerTest) {
    // 連続音のテスト
    for (int i = 0; i < 5; i++) {
        EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 2000, 100));
        EXPECT_CALL(*stm32Mock, delay(150));
    }
    
    // 連続音実行
    for (int i = 0; i < 5; i++) {
        tone(BUZZER_PIN, 2000, 100);
        delay(150);
    }
}

// ブザー無音テスト
TEST_F(SoundEffectsTest, SilenceBuzzerTest) {
    // 音を停止
    EXPECT_CALL(*stm32Mock, noTone(BUZZER_PIN));
    
    noTone(BUZZER_PIN);
}

// 複雑な音響パターンテスト（ストライカーパック換装音）
TEST_F(SoundEffectsTest, StrikerChangeSequenceTest) {
    InSequence seq;
    
    // 取り外し音（下降音）
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1000, 100));
    EXPECT_CALL(*stm32Mock, delay(120));
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 800, 100));
    EXPECT_CALL(*stm32Mock, delay(120));
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 600, 200));
    EXPECT_CALL(*stm32Mock, delay(300));
    
    // 装着音（上昇音）
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 600, 100));
    EXPECT_CALL(*stm32Mock, delay(120));
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 800, 100));
    EXPECT_CALL(*stm32Mock, delay(120));
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1000, 200));
    EXPECT_CALL(*stm32Mock, delay(250));
    
    // 完了音
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1200, 300));
    EXPECT_CALL(*stm32Mock, delay(350));
    
    // ストライカーパック換装音実行
    // 取り外し音
    tone(BUZZER_PIN, 1000, 100);
    delay(120);
    tone(BUZZER_PIN, 800, 100);
    delay(120);
    tone(BUZZER_PIN, 600, 200);
    delay(300);
    
    // 装着音
    tone(BUZZER_PIN, 600, 100);
    delay(120);
    tone(BUZZER_PIN, 800, 100);
    delay(120);
    tone(BUZZER_PIN, 1000, 200);
    delay(250);
    
    // 完了音
    tone(BUZZER_PIN, 1200, 300);
    delay(350);
}