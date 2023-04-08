#include <iostream>
#include "tt_platform.h"
#include "tt_sleep.h"
#include "point.h"
#include "tt_deserialize.h"
#include "tt_test.h"
#include "tt_log.h"

void Callback(std::string data)
{
    common::Deserialize deserialize(data);
    Point point;
    deserialize >> point;
    
    LOG_DEBUG("Subscribe: ", point) << std::endl;

    ASSERT_EQ(point.x, 1);
    ASSERT_EQ(point.y, 2);
    ASSERT_EQ(point.z, 3);
    ASSERT_EQ(point.intensity, 2); // 测试失败
}

TEST(Platform, Deserialize)
{
    std::string topic = "/test";
    common::Platform::getInstance().CreateSubscriber(topic, sizeof(Point), Callback, 1.0);

    // common::Platform::getInstance().Spin();
    common::Platform::getInstance().SpinOnce();
}

int main()
{
    RunAllTests();
    return 0;
}