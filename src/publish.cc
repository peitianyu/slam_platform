#include <iostream>
#include "tt_platform.h"
#include "tt_sleep.h"
#include "point.h"
#include "tt_serialize.h"


void TestPublic()
{
    std::string topic = "test";
    size_t public_size = 1024;
    common::Platform::getInstance().CreatePublisher(topic, public_size);

    std::string data = "hello world ";
    while(true)
    {
        static uint cnt = 0;
        std::string out = data + std::to_string(cnt++);
        common::Platform::getInstance().Publish(topic, out);

        std::cout << "Publish: " << out << " " << out.size() << std::endl;

        common::RateSleep(1.0);
    }
}


void TestSerialize()
{
    std::string topic = "/test";
    size_t public_size = 1024;
    common::Platform::getInstance().CreatePublisher(topic, public_size);


    Point point(1.0, 2.0, 3.0, 4.0);

    common::Serialize serialize;
    serialize << point;

    std::string out = serialize.str();
    common::Platform::getInstance().Publish(topic, out);

    std::cout << "Publish: " << point << std::endl;

    common::RateSleep(2.0);

    serialize.Reset();
    point = Point(5.0, 6.0, 7.0, 8.0);
    serialize << point;

    out = serialize.str();
    common::Platform::getInstance().Publish(topic, out);

    std::cout << "Publish: " << point << std::endl;
}



int main()
{
    // TestPublic();
    TestSerialize();
    return 0;
}