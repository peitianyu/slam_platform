#ifndef __COMMON_READ_H__
#define __COMMON_READ_H__

#include"tt_rwlock.h"
#include"tt_define.h"

namespace common
{

class Reader
{
public:
    Reader(std::string topic, size_t max_size = 10 * MB_1);

    ~Reader();

    void Read(std::string &data, const float rate = -1.0);
private:
    void ReadData(std::string &data);
private:
    RWLock rwlock_;
    uint64_t max_size_;
    int shm_fd_;
    void *shm_ptr_;
};

} // namespace common

#endif  // __COMMON_READ_H__