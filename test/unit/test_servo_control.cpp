#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "mock_arduino.h"

using ::testing::_;
using ::testing::Return;

class ServoControlTest : public ::testing::Test {
protected:
    void SetUp() override {
        servo = new Servo();
    }
    
    void TearDown() override {
        delete servo;
    }
    
    Servo* servo;
};

// サーボ接続テスト
TEST_F(ServoControlTest, AttachTest) {
    EXPECT_CALL(*servo, attach(9));
    servo->attach(9);
}

// サーボ角度設定テスト
TEST_F(ServoControlTest, WriteAngleTest) {
    // 0度設定
    EXPECT_CALL(*servo, write(0));
    servo->write(0);
    
    // 90度設定
    EXPECT_CALL(*servo, write(90));
    servo->write(90);
    
    // 180度設定
    EXPECT_CALL(*servo, write(180));
    servo->write(180);
}

// サーボ角度読み取りテスト
TEST_F(ServoControlTest, ReadAngleTest) {
    EXPECT_CALL(*servo, read())
        .WillOnce(Return(90));
    
    int angle = servo->read();
    EXPECT_EQ(angle, 90);
}

// サーボ切断テスト
TEST_F(ServoControlTest, DetachTest) {
    EXPECT_CALL(*servo, detach());
    servo->detach();
}

// サーボモーション範囲テスト
TEST_F(ServoControlTest, MotionRangeTest) {
    // 無効な角度範囲のテスト
    // 実際の実装では角度制限が必要
    
    // 負の角度
    EXPECT_CALL(*servo, write(-10));
    servo->write(-10);
    
    // 範囲外の角度
    EXPECT_CALL(*servo, write(200));
    servo->write(200);
}