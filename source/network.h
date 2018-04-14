#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gccore.h>
#include <network.h>

#include "network/picohttpparser.h"

bool initNetwork();

s32 doRequest(const void *hostname, const void *path, const u16 port, void *buffer, u32 length, const char *requestType);
s32 getRequest(const void *hostname, const void *path, const u16 port, void *buffer, u32 length);
s32 postRequest(const void *hostname, const void *path, const u16 port, void *buffer, u32 length);

#endif
