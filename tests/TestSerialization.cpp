/* vim: set ai et ts=4 sw=4: */

#include <Date.h>
#include <User.h>
#include <gtest/gtest.h>

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
    Date d1(1988, 8, 5);
    rapidjson::Document json = d1.toJSON();
    Date d2 = Date::fromJSON(json);
    ASSERT_EQ(d1, d2);
}

TEST_F(TestSerialization, UserJson) {
    User u1(123, "Alex", 79161234567, Date(1988, 8, 5));
    rapidjson::Document json = u1.toJSON();
    User u2 = User::fromJSON(json);
    ASSERT_EQ(u1, u2);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
