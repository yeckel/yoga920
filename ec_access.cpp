#include <stdint.h>
#include <sys/io.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ec_access.h"

int init()
{
    if (ioperm(EC_DATA, 1, 1) != 0 || ioperm(EC_SC, 1, 1) != 0)
        return -1;
    return 0;
}

void wait_ec(const uint32_t port, const uint32_t flag, const char value)
{
    uint8_t data;
    int i;

    i = 0;
    data = inb(port);

    while ( (((data >> flag) & 0x1) != value) && (i++ < 100) )
    {
        usleep(1000);
        data = inb(port);
    }

    if (i >= 100)
    {
        fprintf(stderr, "wait_ec error on port 0x%x, data=0x%x, flag=0x%x, value=0x%x\n", port, data, flag, value);
        exit(1);
    }
}

uint8_t read_ec(const uint32_t port)
{
    uint8_t value;

    wait_ec(EC_SC, IBF, 0);
    outb(EC_SC_READ_CMD, EC_SC);
    wait_ec(EC_SC, IBF, 0);
    outb(port, EC_DATA);
    //wait_ec(EC_SC, EC_SC_IBF_FREE);
    wait_ec(EC_SC, OBF, 1);
    value = inb(EC_DATA);

    return value;
}

void write_ec(const uint32_t port, const uint8_t value)
{
    wait_ec(EC_SC, IBF, 0);
    outb(EC_SC_WRITE_CMD, EC_SC);
    wait_ec(EC_SC, IBF, 0);
    outb(port, EC_DATA);
    wait_ec(EC_SC, IBF, 0);
    outb(value, EC_DATA);
    wait_ec(EC_SC, IBF, 0);
}
