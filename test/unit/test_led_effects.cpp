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

// LED繝輔ぉ繝ｼ繝峨う繝ｳ蜉ｹ譫懊ユ繧ｹ繝・
TEST_F(LEDEffectsTest, FadeInEffectTest) {
    // 繝輔ぉ繝ｼ繝峨う繝ｳ蜉ｹ譫懊・繧ｷ繝溘Η繝ｬ繝ｼ繧ｷ繝ｧ繝ｳ
    InSequence seq;
    
    // 谿ｵ髫守噪縺ｫ譏主ｺｦ繧剃ｸ翫￡繧・
    for (int brightness = 0; brightness <= 255; brightness += 8) {
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, brightness));
        EXPECT_CALL(*stm32Mock, delay(10));
    }
    
    // 繝輔ぉ繝ｼ繝峨う繝ｳ螳溯｡・
    for (int brightness = 0; brightness <= 255; brightness += 8) {
        analogWrite(PS_ARMOR_LED_1, brightness);
        analogWrite(PS_ARMOR_LED_2, brightness);
        analogWrite(PS_ARMOR_LED_3, brightness);
        analogWrite(PS_ARMOR_LED_4, brightness);
        delay(10);
    }
}

// LED繝輔ぉ繝ｼ繝峨い繧ｦ繝亥柑譫懊ユ繧ｹ繝・
TEST_F(LEDEffectsTest, FadeOutEffectTest) {
    InSequence seq;
    
    // 谿ｵ髫守噪縺ｫ譏主ｺｦ繧剃ｸ九￡繧・
    for (int brightness = 255; brightness >= 0; brightness -= 8) {
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, brightness));
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, brightness));
        EXPECT_CALL(*stm32Mock, delay(10));
    }
    
    // 螳悟・豸育・
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, LOW));
    
    // 繝輔ぉ繝ｼ繝峨い繧ｦ繝亥ｮ溯｡・
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

// LED轤ｹ貊・柑譫懊ユ繧ｹ繝・
TEST_F(LEDEffectsTest, BlinkEffectTest) {
    // 轤ｹ貊・ヱ繧ｿ繝ｼ繝ｳ縺ｮ繝・せ繝・
    for (int i = 0; i < 3; i++) {
        // 轤ｹ轣ｯ
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, HIGH));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, HIGH));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, HIGH));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, HIGH));
        EXPECT_CALL(*stm32Mock, delay(200));
        
        // 豸育・
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, LOW));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, LOW));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, LOW));
        EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, LOW));
        EXPECT_CALL(*stm32Mock, delay(200));
    }
    
    // 轤ｹ貊・ｮ溯｡・
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

// LED蛟句挨蛻ｶ蠕｡繝・せ繝・
TEST_F(LEDEffectsTest, IndividualLEDControlTest) {
    // 蜷ЛED繧貞句挨縺ｫ蛻ｶ蠕｡
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, 64));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, 128));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, 192));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, 255));
    
    analogWrite(PS_ARMOR_LED_1, 64);   // 25%
    analogWrite(PS_ARMOR_LED_2, 128);  // 50%
    analogWrite(PS_ARMOR_LED_3, 192);  // 75%
    analogWrite(PS_ARMOR_LED_4, 255);  // 100%
}
