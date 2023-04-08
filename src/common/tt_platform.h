#ifndef __COMMON_PLATFORM_H__
#define __COMMON_PLATFORM_H__

#include"tt_singleton.h"
#include"tt_write.h"
#include"tt_read.h"
#include"tt_serialize.h"
#include"tt_timer.h"

#include<iostream>
#include<vector>
#include<map>
#include<memory>
#include <functional>

namespace common
{
class Publisher
{
public:
    Publisher(std::string topic, size_t max_size = 10 * MB_1);

    void Publish(std::string data);
private:
    std::unique_ptr<Writer> writer_;
};

class Subscriber
{
public:
    Subscriber(
        std::string topic, size_t max_size = 10 * MB_1,
        std::function<void(const std::string &)> callback = [](const std::string &) {},
        float period = -1.0);

    void Subscribe();
private:
    std::unique_ptr<Reader> reader_;
    std::unique_ptr<Timer> timer_;
    std::function <void(const std::string&)> callback_;
};

class Platform
{
public:
    static Platform &getInstance(){
        static Platform instance;
        return instance;
    }

    void CreatePublisher(std::string topic, size_t max_size = 10 * MB_1);

    void CreateSubscriber(
        std::string topic, size_t max_size = 10 * MB_1,
        std::function<void(const std::string &)> callback = [](const std::string &) {},
        float period = -1.0);

    void Publish(std::string topic, const std::string& data);

    void Spin();

    void SpinOnce();
private:
    Platform() {}
    Platform(const Platform &) = delete;
    Platform &operator=(const Platform &) = delete;

    std::map<std::string, std::unique_ptr<Publisher>> m_publishers;
    std::map<std::string, std::unique_ptr<Subscriber>> m_subscribers;
};


} // namespace common

#endif // __COMMON_PLATFORM_H__