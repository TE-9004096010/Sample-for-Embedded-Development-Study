#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "StrikeSystem.h"
#include "mock_arduino.h"
#include "config.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::AtLeast;

class IntegrationTest : public ::testing::Test {
protected:
    void SetUp() override {
        stm32Mock = &stm32Mock::getInstance();
        system = new ChagingStrikerPackSystem();
        
        // 繝・ヵ繧ｩ繝ｫ繝医・譛溷ｾ・､險ｭ螳・
        EXPECT_CALL(*stm32Mock, pinMode(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, digitalWrite(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, analogWrite(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, tone(_, _, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, delay(_)).Times(AtLeast(0));
    }
    
    void TearDown() override {
        delete system;
        ::testing::Mock::VerifyAndClearExpectations(stm32Mock);
    }
    
    stm32Mock* stm32Mock;
    ChagingStrikerPackSystem* system;
};

// 繧ｷ繧ｹ繝・Β蛻晄悄蛹也ｵｱ蜷医ユ繧ｹ繝・
TEST_F(IntegrationTest, SystemInitializationIntegrationTest) {
    // 蛻晄悄蛹匁凾縺ｮ譛溷ｾ・､
    EXPECT_CALL(*stm32Mock, pinMode(STRIKER_SERVO_PIN, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(LEFT_ARM_SERVO_PIN, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(RIGHT_ARM_SERVO_PIN, OUTPUT));
    
    // LED蛻晄悄蛹・
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_1, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_2, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_3, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_4, OUTPUT));
    
    // 繝悶じ繝ｼ蛻晄悄蛹・
    EXPECT_CALL(*stm32Mock, pinMode(BUZZER_PIN, OUTPUT));
    
    // LCD蛻晄悄蛹厄ｼ・egin・峨・閾ｪ蜍慕噪縺ｫ蜻ｼ縺ｰ繧後ｋ
    
    system->initialize();
}

// 螳悟・縺ｪ繧ｹ繝医Λ繧､繧ｫ繝ｼ繝代ャ繧ｯ謠幄｣・す繝ｼ繧ｱ繝ｳ繧ｹ繝・せ繝・
TEST_F(IntegrationTest, CompleteStrikerChangeSequenceTest) {
    // 繧ｷ繧ｹ繝・Β蛻晄悄蛹・
    system->initialize();
    
    // Aile Striker縺ｸ縺ｮ謠幄｣・
    InSequence seq;
    
    // 繧ｵ繝ｼ繝懷虚菴懈悄蠕・､
    EXPECT_CALL(*stm32Mock, delay(SERVO_MOVEMENT_DELAY)).Times(AtLeast(1));
    
    // LED蜉ｹ譫懈悄蠕・､
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, HIGH));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, HIGH));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, HIGH));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, HIGH));
    
    // 髻ｳ髻ｿ蜉ｹ譫懈悄蠕・､
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, _, _)).Times(AtLeast(1));
    
    // 繧ｹ繝医Λ繧､繧ｫ繝ｼ繝代ャ繧ｯ謠幄｣・ｮ溯｡・
    system->changeStriker(AILE_STRIKER);
    
    // 繧ｹ繝・・繧ｿ繧ｹ陦ｨ遉ｺ遒ｺ隱・
    system->displayStatus();
}

// 隍・焚繧ｹ繝医Λ繧､繧ｫ繝ｼ繝代ャ繧ｯ騾｣邯壽鋤陬・ユ繧ｹ繝・
TEST_F(IntegrationTest, MultipleStrikerChangesTest) {
    system->initialize();
    
    // 騾｣邯壽鋤陬・す繝ｼ繧ｱ繝ｳ繧ｹ
    StrikerType strikers[] = {
        AILE_STRIKER,
        SWORD_STRIKER,
        LAUNCHER_STRIKER,
        FORCE_STRIKER,
        PERFECT_STRIKE
    };
    
    for (int i = 0; i < 5; i++) {
        // 蜷・鋤陬・〒譛菴朱剞縺ｮ蜍穂ｽ懊′陦後ｏ繧後ｋ縺薙→繧堤｢ｺ隱・
        EXPECT_CALL(*stm32Mock, delay(_)).Times(AtLeast(1));
        
        system->changeStriker(strikers[i]);
        system->displayStatus();
        
        // 謠幄｣・俣縺ｮ蠕・ｩ滓凾髢・
        delay(1000);
    }
}

// 繧ｨ繝ｩ繝ｼ繝上Φ繝峨Μ繝ｳ繧ｰ邨ｱ蜷医ユ繧ｹ繝・
TEST_F(IntegrationTest, ErrorHandlingIntegrationTest) {
    system->initialize();
    
    // 辟｡蜉ｹ縺ｪ繧ｹ繝医Λ繧､繧ｫ繝ｼ繧ｿ繧､繝励〒縺ｮ謠幄｣・ｩｦ陦・
    // ・亥ｮ溯｣・↓繧医▲縺ｦ縺ｯ繧ｨ繝ｩ繝ｼ繝上Φ繝峨Μ繝ｳ繧ｰ縺悟ｿ・ｦ・ｼ・
    system->changeStriker(static_cast<StrikerType>(99));
    
    // 繧ｷ繧ｹ繝・Β縺悟ｮ牙ｮ壹＠縺溽憾諷九ｒ邯ｭ謖√☆繧九％縺ｨ繧堤｢ｺ隱・
    system->displayStatus();
}

// 繝代ヵ繧ｩ繝ｼ繝槭Φ繧ｹ繝・せ繝・
TEST_F(IntegrationTest, PerformanceTest) {
    system->initialize();
    
    // 鬮倬滄｣邯壽鋤陬・ユ繧ｹ繝・
    auto start_time = millis();
    
    for (int i = 0; i < 10; i++) {
        system->changeStriker(AILE_STRIKER);
        system->changeStriker(SWORD_STRIKER);
    }
    
    auto end_time = millis();
    auto duration = end_time - start_time;
    
    // 繝代ヵ繧ｩ繝ｼ繝槭Φ繧ｹ隕∽ｻｶ縺ｮ遒ｺ隱搾ｼ井ｾ具ｼ・0蝗槭・謠幄｣・′10遘剃ｻ･蜀・ｼ・
    EXPECT_LT(duration, 10000);
}

// 繝｡繝｢繝ｪ菴ｿ逕ｨ驥上ユ繧ｹ繝・
TEST_F(IntegrationTest, MemoryUsageTest) {
    // STM32F103C8T6縺ｯ20KB RAM縺励°縺ｪ縺・◆繧√√Γ繝｢繝ｪ菴ｿ逕ｨ驥上・驥崎ｦ・
    
    system->initialize();
    
    // 隍・焚蝗槭・謠幄｣・ｾ後ｂ繝｡繝｢繝ｪ繝ｪ繝ｼ繧ｯ縺後↑縺・％縺ｨ繧堤｢ｺ隱・
    for (int i = 0; i < 50; i++) {
        system->changeStriker(static_cast<StrikerType>(i % 7));
    }
    
    // 繝｡繝｢繝ｪ菴ｿ逕ｨ驥上′螳牙ｮ壹＠縺ｦ縺・ｋ縺薙→繧堤｢ｺ隱・
    // (螳滄圀縺ｮ螳溯｣・〒縺ｯ freeMemory() 髢｢謨ｰ縺ｪ縺ｩ縺悟ｿ・ｦ・
}

// 繧ｷ繧ｹ繝・Β迥ｶ諷倶ｸ雋ｫ諤ｧ繝・せ繝・
TEST_F(IntegrationTest, SystemStateConsistencyTest) {
    system->initialize();
    
    // 蜷・せ繝医Λ繧､繧ｫ繝ｼ繝代ャ繧ｯ縺ｸ縺ｮ謠幄｣・ｾ後√す繧ｹ繝・Β迥ｶ諷九′荳雋ｫ縺励※縺・ｋ縺薙→繧堤｢ｺ隱・
    StrikerType allStrikers[] = {
        NO_PACK, AILE_STRIKER, SWORD_STRIKER, LAUNCHER_STRIKER,
        FORCE_STRIKER, LIGHTNING_STRIKER, PERFECT_STRIKE
    };
    
    for (auto striker : allStrikers) {
        system->changeStriker(striker);
        
        // 迥ｶ諷玖｡ｨ遉ｺ縺梧ｭ｣蟶ｸ縺ｫ蜍穂ｽ懊☆繧九％縺ｨ繧堤｢ｺ隱・
        system->displayStatus();
        
        // 繧ｷ繧ｹ繝・Β縺悟ｿ懃ｭ泌庄閭ｽ縺ｧ縺ゅｋ縺薙→繧堤｢ｺ隱・
        EXPECT_NO_THROW(system->changeStriker(NO_PACK));
    }
}
