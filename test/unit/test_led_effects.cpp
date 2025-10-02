#include <gtest/gtest.h>
<gmock/gmock.h>
#include "mock_arduino.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::AtLeast;

class LEDEffectsTest : public ::testing::Test {
protected:
    void SetUp() override {
        stm32Mock = &stm32Mock::getInstance();
    }
    
    void TearDown() override {
        ::testing::Mock::VerifyAndClearExpectations(stm32Mock);
    }
    
    stm32Mock* stm32Mock;
};

// LEDフェードイン効果テスチE
TEST_F(LEDEffectsTest, FadeInEffectTest) {
    // フェードイン効果�Eシミュレーション
    InSequence seq;
    
    // 段階的に明度を上げめE
    for (int brightness = 0; brightness <= 255; brightness += 8) {
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, brightness));
        EXPECT_CALL(*stm32Mock, delay(10));
    }
    
    // フェードイン実衁E
    for (int brightness = 0; brightness <= 255; brightness += 8) {
        analogWrite(PS_ARMOR_LED_1, brightness);
        analogWrite(PS_ARMOR_LED_2, brightness);
        analogWrite(PS_ARMOR_LED_3, brightness);
        analogWrite(PS_ARMOR_LED_4, brightness);
        delay(10);
    }
}

// LEDフェードアウト効果テスチE
TEST_F(LEDEffectsTest, FadeOutEffectTest) {
    InSequence seq;
    
    // 段階的に明度を下げめE
    for (int brightness = 255; brightness >= 0; brightness -= 8) {
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, brightness));
        EXPECT_CALL(*stm32Mock, delay(10));
    }
    
    // 完�E消�E
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, LOW));
    
    // フェードアウト実衁E
    for (int brightness = 255; brightness >= 0; brightness -= 8) {
        analogWrite(PS_ARMOR_LED_1, brightness);
        analogWrite(PS_ARMOR_LED_2, brightness);
        analogWrite(PS_ARMOR_LED_3, brightness);
        analogWrite(PS_ARMOR_LED_4, brightness);
        delay(10);
    }
    
    digitalWrite(PS_ARMOR_LED_1, LOW);
    digitalWrite(PS_ARMOR_LED_2, LOW);
    digitalWrite(PS_ARMOR_LED_3, LOW);
    digitalWrite(PS_ARMOR_LED_4, LOW);
}

// LED点滁E��果テスチE
TEST_F(LEDEffectsTest, BlinkEffectTest) {
    // 点滁E��ターンのチE��チE
    for (int i = 0; i < 3; i++) {
        // 点灯
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, HIGH));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, HIGH));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, HIGH));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, HIGH));
        EXPECT_CALL(*stm32Mock, delay(200));
        
        // 消�E
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, LOW));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, LOW));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, LOW));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, LOW));
        EXPECT_CALL(*stm32Mock, delay(200));
    }
    
    // 点滁E��衁E
    for (int i = 0; i < 3; i++) {
        digitalWrite(PS_ARMOR_LED_1, HIGH);
        digitalWrite(PS_ARMOR_LED_2, HIGH);
        digitalWrite(PS_ARMOR_LED_3, HIGH);
        digitalWrite(PS_ARMOR_LED_4, HIGH);
        delay(200);
        
        digitalWrite(PS_ARMOR_LED_1, LOW);
        digitalWrite(PS_ARMOR_LED_2, LOW);
        digitalWrite(PS_ARMOR_LED_3, LOW);
        digitalWrite(PS_ARMOR_LED_4, LOW);
        delay(200);
    }
}

// LED個別制御チE��チE
TEST_F(LEDEffectsTest, IndividualLEDControlTest) {
    // 各LEDを個別に制御
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, 64));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, 128));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, 192));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, 255));
    
    analogWrite(PS_ARMOR_LED_1, 64);   // 25%
    analogWrite(PS_ARMOR_LED_2, 128);  // 50%
    analogWrite(PS_ARMOR_LED_3, 192);  // 75%
    analogWrite(PS_ARMOR_LED_4, 255);  // 100%
}
