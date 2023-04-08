#include <iostream>
#include "tt_platform.h"
#include "tt_sleep.h"
#include "point.h"
#include "tt_serialize.h"
#include "tt_log.h"


void Test()
{
    Point point(1, 2, 3, 4);
    std::string topic = "/test";
    common::Platform::getInstance().CreatePublisher(topic, sizeof(Point));

    common::Serialize serialize;
    serialize << point;

    common::Platform::getInstance().Publish(topic, serialize.str());

    LOG_DEBUG("Publish: ", point) << std::endl;

    common::RateSleep(2.0);
}

int main()
{
    Test();
    return 0;
}