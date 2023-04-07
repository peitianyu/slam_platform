#ifndef __COMMON_WRITE_H__
#define __COMMON_WRITE_H__

#include"tt_rwlock.h"
#include"tt_define.h"

namespace common
{

class Writer
{
public:
    Writer(std::string topic, uint64_t max_size = 10 * MB_1);

    ~Writer();

    void Write(const std::string& data, float rate = -1.0);
private:
    void WriteData(const std::string& data);
private:
    RWLock rwlock_;
    uint64_t max_size_;
    int shm_fd_;
    void *shm_ptr_;
};

} // namespace common

#endif  // __COMMON_WRITE_H__