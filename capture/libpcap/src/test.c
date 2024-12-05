#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>


int main(int argc, char const *argv[])
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *alldevs, *d;
    pcap_addr_t *a;
    char *dev;
    int i = 0;


    // 查找可用的网络设备
    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
        exit(1);
    }

        // 遍历设备列表
    for (d = alldevs; d != NULL; d = d->next) {
        printf("%d. %s", ++i, d->name);
        if (d->description)
            printf(" (%s)\n", d->description);
        else
            printf(" (No description available)\n");
 
        // 列出每个设备的地址
        for (a = d->addresses; a != NULL; a = a->next) {
            if (a->addr->sa_family == AF_INET) { // 仅处理IPv4地址
                struct sockaddr_in *saddr = (struct sockaddr_in *)a->addr;
                printf("  Address: %s\n", inet_ntoa(saddr->sin_addr));
            }
        }
    }
 
    // 假设我们选择第一个设备（在实际应用中，你可能需要更复杂的逻辑来选择设备）
    pcap_t *handle = pcap_open_live(alldevs->name, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", alldevs->name, errbuf);
        pcap_freealldevs(alldevs); // 释放设备列表
        exit(1);
    }
 
    // 在这里你可以使用handle进行数据包捕获等操作
 
    // 关闭捕获句柄并释放设备列表
    pcap_close(handle);
    pcap_freealldevs(alldevs);
    return 0;
}
