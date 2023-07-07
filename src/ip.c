#include "ip.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define TABLE_MAX 4096

CONNECTION_TABLE GetTCPNTable() {
    CONNECTION_TABLE connection_table;

    uint32_t size = 0;
    PMIB_TCPTABLE2 table = NULL;

    GetTcpTable2(NULL, &size, 0);

    table = (PMIB_TCPTABLE2)HeapAlloc(GetProcessHeap(), 0, size);

    GetTcpTable2(table, &size, 1);

    if (table == NULL) {
        exit(1);
    }

    connection_table.size = table->dwNumEntries;
    connection_table.connections = (CONNECTION*)HeapAlloc(GetProcessHeap(), 0, table->dwNumEntries);
    
    for (uint32_t i = 0; i < table->dwNumEntries; i++) {
        connection_table.connections[i].pid = table->table[i].dwOwningPid;
    }

    return connection_table;
}

char* GetPidName(uint32_t pid) {
    DWORD buffer_size = MAX_PATH;
    char* buffer = malloc(MAX_PATH + 1);
    ZeroMemory(buffer, MAX_PATH + 1);
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, 0, pid);

    QueryFullProcessImageNameA(process, 0, buffer, &buffer_size);

    CloseHandle(process);

    if (buffer[0] == '\0') {
        buffer[0] = 'N';
        buffer[1] = '/';
        buffer[2] = 'A';
        buffer[3] = '\0';
    }

    buffer[MAX_PATH] = '\0';

    return buffer;
}