#include <iostream>
#include "tt_platform.h"
#include "tt_sleep.h"
#include "point.h"
#include "tt_deserialize.h"

void TestSubscribe()
{
    std::string topic = "/test";
    size_t subscribe_size = 1024;
    common::Platform::getInstance().CreateSubscriber(topic, subscribe_size, [](std::string data){
        std::cout << "Subscribe: " << data << " " << data.size() << std::endl;
    }, 1.0);

    common::Platform::getInstance().Spin();
}

void TestDeserialize()
{
    std::string topic = "/test";
    size_t subscribe_size = 1024;
    common::Platform::getInstance().CreateSubscriber(topic, subscribe_size, [](std::string data){
        common::Deserialize deserialize(data);
        Point point;
        deserialize >> point;
        std::cout << "Subscribe: " << point << std::endl;
    }, 1.0);

    common::Platform::getInstance().Spin();
}

int main()
{
    // TestSubscribe();
    TestDeserialize();
    return 0;
}