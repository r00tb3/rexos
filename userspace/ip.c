/*
    RExOS - embedded RTOS
    Copyright (c) 2011-2015, Alexey Kramarenko
    All rights reserved.
*/

#include "ip.h"
#include "stdio.h"

void ip_print(const IP* ip)
{
    int i;
    for (i = 0; i < 4; ++i)
    {
        printf("%d", ip->u8[i]);
        if (i < 4 - 1)
            printf(".");
    }
}

uint16_t ip_checksum(void* buf, unsigned int size)
{
    unsigned int i;
    uint32_t sum = 0;
    for (i = 0; i < (size >> 1); ++i)
        sum += (((uint8_t*)buf)[i << 1] << 8) | (((uint8_t*)buf)[(i << 1) + 1]);
    //padding zero
    if (size & 1)
        sum += ((uint8_t*)buf)[size - 1] << 8;
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);
    return ~((uint16_t)sum);
}

void ip_set(HANDLE tcpip, const IP* ip)
{
    ack(tcpip, HAL_REQ(HAL_IP, IP_SET), 0, ip->u32.ip, 0);
}

void ip_get(HANDLE tcpip, IP* ip)
{
    ip->u32.ip = get(tcpip, HAL_REQ(HAL_IP, IP_GET), 0, 0, 0);
}
