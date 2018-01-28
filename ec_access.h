#ifndef EC_ACCESS_H
#define EC_ACCESS_H

#define EC_SC 0x66
#define EC_DATA 0x62
#define IBF 1
#define OBF 0
#define EC_SC_READ_CMD 0x80
#define EC_SC_WRITE_CMD 0x81
#define EC_SC_SCI_CMD 0x84

#include <stdint.h>

int init();
void wait_ec(const uint32_t port, const uint32_t flag, const char value);
uint8_t read_ec(const uint32_t port);
void write_ec(const uint32_t port, const uint8_t value);

#endif
