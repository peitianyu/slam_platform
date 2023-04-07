#include"tt_read.h"
#include"tt_assert.h"
#include"tt_sleep.h"

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <cstring>

namespace common
{

Reader::Reader(std::string topic, size_t max_size):rwlock_(topic), max_size_(max_size)
{
    // 创建或打开共享内存对象
    shm_fd_ = shm_open((topic + "_shm").c_str(), O_CREAT | O_RDWR, 0666);
    tt_assert(shm_fd_ != -1);

    // 设置共享内存对象的大小
    if (ftruncate(shm_fd_, max_size) == -1)
    tt_assert(ftruncate(shm_fd_, max_size) != -1);

    // 将共享内存对象映射到进程的虚拟地址空间
    shm_ptr_ = mmap(NULL, max_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd_, 0);
    tt_assert(shm_ptr_ != MAP_FAILED);
}

Reader::~Reader()
{
    // 取消映射共享内存对象
    tt_assert(munmap(shm_ptr_, max_size_) != -1);

    // 关闭共享内存对象和信号量
    tt_assert(close(shm_fd_) != -1);
}

void Reader::ReadData(std::string &data)
{
    // 加读锁
    rwlock_.ReadLock();

    // 读数据 size + data
    size_t size;
    memcpy(&size, shm_ptr_, sizeof(size_t));
    char *buf = new char[size + 1];
    memcpy(buf, (char *)shm_ptr_ + sizeof(size_t), size);
    buf[size] = '\0';
    data = buf;
    delete[] buf;

    // 解读锁
    rwlock_.ReadUnlock();
}

void Reader::Read(std::string &data, const float rate)
{
    if (rate < 0.0)
    {
        ReadData(data);
        return;
    }

    while(rate > 0.0)
    {
        ReadData(data);
        RateSleep(rate);
    }
}


} // namespace common
