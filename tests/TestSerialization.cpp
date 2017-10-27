/* vim: set ai et ts=4 sw=4: */

#include <Date.h>
#include <User.h>
#include <gtest/gtest.h>
#include <iostream>

class TestSerialization : public ::testing::Test {
public:
    TestSerialization() { /* init protected members here */ }

    void SetUp() { /* do nothing */ }

    void TearDown() { /* do nothing */ }

    ~TestSerialization() { /* free protected members here */ }

protected:
    /* none */
};

TEST_F(TestSerialization, DateJson) {
    ASSERT_TRUE(true);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
