#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock_arduino.h"

// チE��ト用にArduino.hを置き換ぁE
#define Arduino_h
#include "StrikeSystem.h"
#include "config.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;
using ::testing::InSequence;

class StrikeSystemTest : public ::testing::Test {
protected:
    void SetUp() override {
        // テスト前の初期化
        stm32Mock = &ArduinoMock::getInstance();
        
        // デフォルトの期待値を設定
        EXPECT_CALL(*stm32Mock, pinMode(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, digitalWrite(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, analogWrite(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, delay(_)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, tone(_, _, _)).Times(AtLeast(0));
        
        system = new ChagingStrikerPackSystem();
    }
    
    void TearDown() override {
        delete system;
        ::testing::Mock::VerifyAndClearExpectations(stm32Mock);
    }
    
    ArduinoMock* stm32Mock;
    ChagingStrikerPackSystem* system;
};

// 初期化テスチE
TEST_F(StrikeSystemTest, InitializationTest) {
    // PS裁E��LED初期化�E確誁E
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_1, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_2, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_3, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_4, OUTPUT));
    
    // LED初期状態！EOW�E��E確誁E
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, LOW));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, LOW));
    
    // ブザー初期匁E
    EXPECT_CALL(*stm32Mock, pinMode(BUZZER_PIN, OUTPUT));
    
    // 初期化実衁E
    system->initialize();
}

// エールストライカー換裁E��スチE
TEST_F(StrikeSystemTest, AileStrikerChangeTest) {
    // 初期匁E
    system->initialize();
    
    // PS裁E��展開エフェクト�E確誁E
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, _))
        .Times(AtLeast(1));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_2, _))
        .Times(AtLeast(1));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_3, _))
        .Times(AtLeast(1));
    EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_4, _))
        .Times(AtLeast(1));
    
    // PS裁E��音の確誁E
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 800, 30))
        .Times(AtLeast(1));
    
    // 換裁E��の確誁E
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1000, 200));
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1200, 200));
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, 1500, 300));
    
    // エールストライカー換裁E��衁E
    system->changeStriker(AILE_STRIKER);
}

// ソードストライカー換裁E��スチE
TEST_F(StrikeSystemTest, SwordStrikerChangeTest) {
    system->initialize();
    
    // ソード展開モーションの遁E��確誁E
    EXPECT_CALL(*stm32Mock, delay(10))
        .Times(AtLeast(90));  // 180度めE度刻みで90囁E
    
    system->changeStriker(SWORD_STRIKER);
}

// パ�Eフェクトストライク換裁E��スチE
TEST_F(StrikeSystemTest, PerfectStrikeChangeTest) {
    system->initialize();
    
    // 非対称展開の確誁E
    EXPECT_CALL(*stm32Mock, delay(15))
        .Times(AtLeast(60));  // 180度めE度刻みで60囁E
    
    system->changeStriker(PERFECT_STRIKE);
}

// 同じストライカーパック選択時のチE��チE
TEST_F(StrikeSystemTest, SameStrikerSelectionTest) {
    system->initialize();
    
    // 最初にエールストライカーに換裁E
    system->changeStriker(AILE_STRIKER);
    
    // 同じエールストライカーを�E選択（何も起こらなぁE�Eず！E
    // PS裁E��エフェクトが発生しなぁE��とを確誁E
    EXPECT_CALL(*stm32Mock, analogWrite(_, _))
        .Times(0);
    EXPECT_CALL(*stm32Mock, tone(_, _, _))
        .Times(0);
    
    system->changeStriker(AILE_STRIKER);
}

// 全ストライカーパック頁E��換裁E��スチE
TEST_F(StrikeSystemTest, AllStrikerPacksSequentialTest) {
    system->initialize();
    
    // 全てのストライカーパックに頁E��換裁E
    StrikerType strikers[] = {
        AILE_STRIKER,
        SWORD_STRIKER,
        LAUNCHER_STRIKER,
        INTEGRATED_WEAPONS_STRIKER,
        OHTORI_STRIKER,
        PERFECT_STRIKE,
        NO_PACK
    };
    
    for (auto striker : strikers) {
        // 吁E��裁E��PS裁E��エフェクトが発生することを確誁E
        EXPECT_CALL(*stm32Mock, analogWrite(PS_ARMOR_LED_1, _))
            .Times(AtLeast(1));
        
        system->changeStriker(striker);
        
        // 期征E��をクリア
        ::testing::Mock::VerifyAndClearExpectations(stm32Mock);
        
        // 次のチE��ト�EためにチE��ォルト期征E��を�E設宁E
        EXPECT_CALL(*stm32Mock, pinMode(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, digitalWrite(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, analogWrite(_, _)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, delay(_)).Times(AtLeast(0));
        EXPECT_CALL(*stm32Mock, tone(_, _, _)).Times(AtLeast(0));
    }
}
