#include"sendInfo.h"
#include<iostream>
/* 填充arp包 */
struct ether_arp *fillArpPacket(const unsigned char *src_mac_addr, const char *src_ip, const char *dst_ip)
{
    struct ether_arp *arp_packet;
    struct in_addr src_in_addr, dst_in_addr;
    unsigned char dst_mac_addr[ETH_ALEN] = BROADCAST_ADDR;

    /* IP地址转换 */
    inet_pton(AF_INET, src_ip, &src_in_addr);
    inet_pton(AF_INET, dst_ip, &dst_in_addr);


    /* 整个arp包 */
    arp_packet = (struct ether_arp *)malloc(ETHER_ARP_LEN);
    arp_packet->arp_hrd = htons(ARPHRD_ETHER);
    arp_packet->arp_pro = htons(ETHERTYPE_IP);
    arp_packet->arp_hln = ETH_ALEN;
    arp_packet->arp_pln = IP_ADDR_LEN;
    arp_packet->arp_op = htons(ARPOP_REQUEST);
    memcpy(arp_packet->arp_sha, src_mac_addr, ETH_ALEN);
    memcpy(arp_packet->arp_tha, dst_mac_addr, ETH_ALEN);
    memcpy(arp_packet->arp_spa, &src_in_addr, IP_ADDR_LEN);
    memcpy(arp_packet->arp_tpa, &dst_in_addr, IP_ADDR_LEN);
    return arp_packet;
}

void getIpList(int sockFd, const char*deviceName, char ipList[][128]) {

    struct ifreq ifr;
    bzero(&ifr, sizeof(ifr)) ;
    //获取网卡索引
    char ip[1000] ;
    setInfo(sockFd, ip, ifr, deviceName) ;
    std::string srcIp = ip ;
      //  inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr);
    /* 获取网卡接口IP */
    int a = srcIp.find_last_of(".") ; 

    std::string s = srcIp.substr(0, a) ;
    for(int i=1; i <= 254; i++) {
        sprintf(ipList[i],"%s.%d",s.c_str(), i)  ;
    }   
}

int getSock(int& sockfd) {
    
    if ((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP))) == -1)
        return -1 ;
    return sockfd ;
}

void setInfo(int sockFd, char* srcIp, struct ifreq&ifr, const char* if_name) {

    memcpy(ifr.ifr_name, if_name, strlen(if_name));
    /* 获取网卡接口索引 */
    if (ioctl(sockFd, SIOCGIFINDEX, &ifr) == -1) {
        printf("获取网卡接口索引失败！") ;
        return ;
    }
    /* 获取网卡接口IP */
    if (ioctl(sockFd, SIOCGIFADDR, &ifr) == -1) {
        printf("获取网卡接口ip失败！") ;
        return  ;
    }
    strcpy(srcIp, inet_ntoa(((struct sockaddr_in *)&(ifr.ifr_addr))->sin_addr));
}
    
/* arp请求 */
int arpRequest(int& sockfd, const char *if_name, const char *dst_ip) {

    struct sockaddr_ll saddr_ll;
    struct ether_header *eth_header;
    struct ether_arp *arp_packet;
    struct ifreq ifr;
    char buf[ETHER_ARP_PACKET_LEN];
    unsigned char src_mac_addr[ETH_ALEN];
    unsigned char dst_mac_addr[ETH_ALEN] = BROADCAST_ADDR;
    char src_ip[100];
    int ret_len;
    bzero(&saddr_ll, sizeof(struct sockaddr_ll));
    bzero(&ifr, sizeof(struct ifreq));
    setInfo(sockfd, src_ip, ifr, if_name) ;
    /* 网卡接口名 */
    saddr_ll.sll_ifindex = ifr.ifr_ifindex;
    saddr_ll.sll_family = PF_PACKET;
    
    if (ioctl(sockfd, SIOCGIFHWADDR, &ifr)) {
        printf("获取mac地址失败！") ;
        return -1 ; 
    }
    memcpy(src_mac_addr, ifr.ifr_hwaddr.sa_data, ETH_ALEN);

    bzero(buf, ETHER_ARP_PACKET_LEN);
    /* 填充以太首部 */
    eth_header = (struct ether_header *)buf;
    memcpy(eth_header->ether_shost, src_mac_addr, ETH_ALEN);
    memcpy(eth_header->ether_dhost, dst_mac_addr, ETH_ALEN);
    eth_header->ether_type = htons(ETHERTYPE_ARP);
    /* arp包 */
    arp_packet = fillArpPacket(src_mac_addr, src_ip, dst_ip);
    memcpy(buf + ETHER_HEADER_LEN, arp_packet, ETHER_ARP_LEN);

    /* 发送请求 */
    ret_len = sendto(sockfd, buf, ETHER_ARP_PACKET_LEN, 0, (struct sockaddr *)&saddr_ll, sizeof(struct sockaddr_ll));
    if ( ret_len < 0) {
        printf("发送请求出错！\n")  ;  
        return -1 ;
    }
    return 1 ;
}

//向外部所有arp广播请求
int sendRequest(int sockfd, const char ipList[][128], const char* deviceName) {
    
    for(int i=1; i<=254; i++) {
        printf("%s\n", ipList[i]) ;
       int ret =  arpRequest(sockfd, deviceName, ipList[i]) ;
       if(ret < 0) {
            printf("发送请求失败！\n") ;
            return -1 ;
       }
       //通知另一端线程已经发送完成
    }
    return 1 ;
}
