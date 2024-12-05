// #define _XOPEN_SOURCE
#define _DEFAULT_SOURCE
#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>

// 回调函数，用于处理捕获到的数据包
void packet_handler(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *packet) {
    printf("捕获到数据包，长度：%d 字节\n", pkt_header->len);

    // 提取源IP地址和目标IP地址
    struct iphdr *ip_header = (struct iphdr *)(packet + 14); // 假设是以太网帧，前面有14字节的以太网头部
    char src_ip[INET_ADDRSTRLEN];
    char dst_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ip_header->saddr), src_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_header->daddr), dst_ip, INET_ADDRSTRLEN);
    printf("源IP地址：%s，目标IP地址：%s\n", src_ip, dst_ip);
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // 查找可用的网络设备
    char *dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "无法找到网络设备：%s\n", errbuf);
        return 1;
    }
    printf("网络设备：%s\n", dev);

    // 打开网络设备，进行数据包捕获
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "无法打开网络设备：%s\n", errbuf);
        return 1;
    }

    // 设置回调函数，用于处理捕获到的数据包
    pcap_loop(handle, 0, packet_handler, NULL);

    // 关闭网络设备
    pcap_close(handle);

    return 0;
}