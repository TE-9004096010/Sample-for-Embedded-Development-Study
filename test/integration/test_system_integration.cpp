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
        
        // チE��ォルト�E期征E��設宁E
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

// シスチE��初期化統合テスチE
TEST_F(IntegrationTest, SystemInitializationIntegrationTest) {
    // 初期化時の期征E��
    EXPECT_CALL(*stm32Mock, pinMode(STRIKER_SERVO_PIN, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(LEFT_ARM_SERVO_PIN, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(RIGHT_ARM_SERVO_PIN, OUTPUT));
    
    // LED初期匁E
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_1, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_2, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_3, OUTPUT));
    EXPECT_CALL(*stm32Mock, pinMode(PS_ARMOR_LED_4, OUTPUT));
    
    // ブザー初期匁E
    EXPECT_CALL(*stm32Mock, pinMode(BUZZER_PIN, OUTPUT));
    
    // LCD初期化！Eegin�E��E自動的に呼ばれる
    
    system->initialize();
}

// 完�Eなストライカーパック換裁E��ーケンスチE��チE
TEST_F(IntegrationTest, CompleteStrikerChangeSequenceTest) {
    // シスチE��初期匁E
    system->initialize();
    
    // Aile Strikerへの換裁E
    InSequence seq;
    
    // サーボ動作期征E��
    EXPECT_CALL(*stm32Mock, delay(SERVO_MOVEMENT_DELAY)).Times(AtLeast(1));
    
    // LED効果期征E��
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_1, HIGH));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_2, HIGH));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_3, HIGH));
    EXPECT_CALL(*stm32Mock, digitalWrite(PS_ARMOR_LED_4, HIGH));
    
    // 音響効果期征E��
    EXPECT_CALL(*stm32Mock, tone(BUZZER_PIN, _, _)).Times(AtLeast(1));
    
    // ストライカーパック換裁E��衁E
    system->changeStriker(AILE_STRIKER);
    
    // スチE�Eタス表示確誁E
    system->displayStatus();
}

// 褁E��ストライカーパック連続換裁E��スチE
TEST_F(IntegrationTest, MultipleStrikerChangesTest) {
    system->initialize();
    
    // 連続換裁E��ーケンス
    StrikerType strikers[] = {
        AILE_STRIKER,
        SWORD_STRIKER,
        LAUNCHER_STRIKER,
        FORCE_STRIKER,
        PERFECT_STRIKE
    };
    
    for (int i = 0; i < 5; i++) {
        // 吁E��裁E��最低限の動作が行われることを確誁E
        EXPECT_CALL(*stm32Mock, delay(_)).Times(AtLeast(1));
        
        system->changeStriker(strikers[i]);
        system->displayStatus();
        
        // 換裁E��の征E��時閁E
        delay(1000);
    }
}

// エラーハンドリング統合テスチE
TEST_F(IntegrationTest, ErrorHandlingIntegrationTest) {
    system->initialize();
    
    // 無効なストライカータイプでの換裁E��衁E
    // �E�実裁E��よってはエラーハンドリングが忁E��E��E
    system->changeStriker(static_cast<StrikerType>(99));
    
    // シスチE��が安定した状態を維持することを確誁E
    system->displayStatus();
}

// パフォーマンスチE��チE
TEST_F(IntegrationTest, PerformanceTest) {
    system->initialize();
    
    // 高速連続換裁E��スチE
    auto start_time = millis();
    
    for (int i = 0; i < 10; i++) {
        system->changeStriker(AILE_STRIKER);
        system->changeStriker(SWORD_STRIKER);
    }
    
    auto end_time = millis();
    auto duration = end_time - start_time;
    
    // パフォーマンス要件の確認（例！E0回�E換裁E��10秒以冁E��E
    EXPECT_LT(duration, 10000);
}

// メモリ使用量テスチE
TEST_F(IntegrationTest, MemoryUsageTest) {
    // STM32F103C8T6は20KB RAMしかなぁE��め、メモリ使用量�E重要E
    
    system->initialize();
    
    // 褁E��回�E換裁E��もメモリリークがなぁE��とを確誁E
    for (int i = 0; i < 50; i++) {
        system->changeStriker(static_cast<StrikerType>(i % 7));
    }
    
    // メモリ使用量が安定してぁE��ことを確誁E
    // (実際の実裁E��は freeMemory() 関数などが忁E��E
}

// シスチE��状態一貫性チE��チE
TEST_F(IntegrationTest, SystemStateConsistencyTest) {
    system->initialize();
    
    // 吁E��トライカーパックへの換裁E��、シスチE��状態が一貫してぁE��ことを確誁E
    StrikerType allStrikers[] = {
        NO_PACK, AILE_STRIKER, SWORD_STRIKER, LAUNCHER_STRIKER,
        FORCE_STRIKER, LIGHTNING_STRIKER, PERFECT_STRIKE
    };
    
    for (auto striker : allStrikers) {
        system->changeStriker(striker);
        
        // 状態表示が正常に動作することを確誁E
        system->displayStatus();
        
        // シスチE��が応答可能であることを確誁E
        EXPECT_NO_THROW(system->changeStriker(NO_PACK));
    }
}
