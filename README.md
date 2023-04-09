## 该程序实现了类似于ros的多进程发布订阅模式[共享内存]

```c++
// publish.cc


void Test()
{
    Point point(1, 2, 3, 4);
    std::string topic = "/test";
  
    // 创建publisher
    common::Platform::getInstance().CreatePublisher(topic, sizeof(Point));

    // 序列化Point
    common::Serialize serialize;
    serialize << point;

    common::Platform::getInstance().Publish(topic, serialize.str());
}


// subscribe.cc

// 实现回调
void Callback(const std::string& data)
{
    // 反序列化 
    common::Deserialize deserialize(data);
    Point point;
    deserialize >> point;
  
    LOG_DEBUG("Subscribe: ", point) << std::endl;
}

TEST(Platform, Deserialize)
{
    std::string topic = "/test";

    // 注册订阅者
    common::Platform::getInstance().CreateSubscriber(topic, sizeof(Point), Callback, 1.0);

    // 类似ros::spin()与spinOnce()
    // common::Platform::getInstance().Spin();
    common::Platform::getInstance().SpinOnce();
}
```


* 编译测试文件

```
mkdir -vp install/test
mkdir build && cd build
cmake .. -DCOMPILE_MODE=TEST
make
```

* 编译库文件

```
mkdir -vp install/lib install/include
mkdir build && cd build
cmake ..
make && make install
```
