#include"tt_crc.h"

namespace common{
namespace crc16{

uint16_t Update(const uint8_t* data, uint32_t size)
{
    uint16_t crc = 0xffff;
    while (size--)
    {
        crc = (crc >> 8) | (crc << 8);
        crc ^= *data++;
        crc ^= (crc & 0xff) >> 4;
        crc ^= crc << 12;
        crc ^= (crc & 0xff) << 5;
    }
    return crc;
}

bool CheckCRC(const uint8_t* data, uint32_t size, uint16_t crc)
{
    return Update(data, size) == crc;
}

} // namespace crc16
} // namespace common

