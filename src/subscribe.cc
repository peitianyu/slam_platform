#include <iostream>
#include "tt_platform.h"
#include "point.h"
#include "tt_deserialize.h"
#include "tt_test.h"
#include "tt_log.h"

void Callback(const std::string &data)
{
    common::Deserialize deserialize(data);
    Point point;
    deserialize >> point;
    
    LOG_INFO("Subscribe: ", point) << std::endl;
    LOG_WARN("Subscribe: ", point) << std::endl;
    LOG_DEBUG("Subscribe: ", point) << std::endl;
    LOG_ERROR("Subscribe: ", point) << std::endl;

    ASSERT_EQ(point.x, 1);
    ASSERT_EQ(point.y, 2);
    ASSERT_EQ(point.z, 3);
    ASSERT_EQ(point.intensity, 2); // fail
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