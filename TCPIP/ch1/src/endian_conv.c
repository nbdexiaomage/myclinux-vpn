#include <stdio.h>
#include <arpa/inet.h>

int main()
{
    unsigned short host_port = 0x1234;
    unsigned short net_port;
    unsigned long host_addr = 0x12345678;
    unsigned long net_addr;

    net_port = htons(host_port);
    net_addr = htonl(host_addr);

    printf("host ordered port: %#x\n", host_port);
    printf("net ordered port: %#x\n", net_port);
    printf("host ordered address: %#lx\n", host_addr);
    printf("net ordered address: %#lx\n", net_addr);
}