#ifndef QNFD_IP_H
#define QNFD_IP_H

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct CONNECTION {
	uint32_t ip;
	uint32_t port;
	uint32_t pid;
	uint32_t state;
} CONNECTION;

typedef struct CONNECTION_TABLE {
	uint32_t size;
	CONNECTION* connections;
} CONNECTION_TABLE;

CONNECTION_TABLE GetTCPNTable();
char* GetPidName(uint32_t pid);

#endif