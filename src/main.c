#include "ip.h"
#include <raylib/raylib.h>
#include <raylib/raygui.h>

#define WINPAUSE system("pause");

int main() {
    CONNECTION_TABLE table = GetTCPNTable();

    for (uint32_t i = 0; i < table.size; i++) {
        char* buffer = GetPidName(table.connections[i].pid);
        printf("%s\n", buffer);
    }

    WINPAUSE;
    return 0;
}