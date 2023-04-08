#include"tt_platform.h"

namespace common
{

Publisher::Publisher(std::string topic, size_t max_size)
{
    writer_ = std::make_unique<Writer>(topic, max_size);
}

void Publisher::Publish(std::string data)
{
    writer_->Write(data);
}

Subscriber::Subscriber(std::string topic, size_t max_size, std::function<void(std::string)> callback, float period)
{
    reader_ = std::make_unique<Reader>(topic, max_size);
    if(period > 0.0)
        timer_ = std::make_unique<Timer>(period);

    callback_ = callback;
}

void Subscriber::Subscribe()
{
    if (timer_->IsTimeOut()){
        std::string data;
        reader_->Read(data);
        callback_(data);
        timer_->Reset();
    }
}

void Platform::CreatePublisher(std::string topic, size_t max_size)
{
    auto it = m_publishers.find(topic);
    if (it == m_publishers.end())
        m_publishers[topic] = std::make_unique<Publisher>(topic, max_size);
}

void Platform::CreateSubscriber(
    std::string topic, size_t max_size,
    std::function<void(std::string)> callback,
    float period)
{
    if (m_subscribers.find(topic) == m_subscribers.end())
        m_subscribers[topic] = std::make_unique<Subscriber>(topic, max_size, callback, period);
}

void Platform::Publish(std::string topic, const std::string &data)
{
    auto it = m_publishers.find(topic);
    if (it != m_publishers.end())
        static_cast<Publisher *>(it->second.get())->Publish(data);
}

void Platform::Spin()
{
    while (true)
        SpinOnce();
}

void Platform::SpinOnce()
{
    for (auto &it : m_subscribers)
        static_cast<Subscriber *>(it.second.get())->Subscribe();
}

} // namespace common

