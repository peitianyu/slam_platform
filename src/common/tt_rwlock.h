#ifndef __COMMON_RWLOCK_H__
#define __COMMON_RWLOCK_H__

#include <string>
#include <semaphore.h>
#include <fcntl.h>

namespace common
{

class RWLock {
public:
    RWLock(std::string topic);

    ~RWLock();

    void ReadLock();

    void ReadUnlock();

    void WriteLock();

    void WriteUnlock();
private:
    sem_t *sem_read_ptr_;
    sem_t *sem_write_ptr_;
};



} // namespace common






#endif // __COMMON_RWLOCK_H__