#ifndef __COMMON_PLATFORM_H__
#define __COMMON_PLATFORM_H__

#include"tt_singleton.h"
#include"tt_write.h"
#include"tt_read.h"

#include<iostream>
#include<vector>

namespace common
{

class Platform
{
public:
    static Platform* GetInstance()
    {
        static Singleton<Platform> s_instance;
        return s_instance.Get();
    }

    template<typename T>
    void Publish(const std::string& topic, const T& msg, const float rate = -1.0);

    template<typename T>
    void Subscribe(const std::string& topic, /*回调*/ T& msg, const float rate = -1.0);
    {
        readers_.emplace_back(topic);
    }

private:
    std::vector<Writer> writers_;
    std::vector<Reader> readers_;
};

} // namespace common

#endif // __COMMON_PLATFORM_H__