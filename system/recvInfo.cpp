#include"recvInfo.h"
#include"ownSource.h"
//随便初始化一下
RecvInfo :: RecvInfo() {
    arp_packet = NULL ;
    bzero(buf, ETHER_ARP_PACKET_LEN);
    ret_len = 0 ;
    i = 0 ;
}

RecvInfo :: ~RecvInfo() {
    sfd.closeUnixSock() ;
}   

void RecvInfo :: recvMsg(int sockfd) {
    //接收消息a
    while (1)
    {
        ret_len = recv(sockfd, buf, ETHER_ARP_PACKET_LEN, 0);
       /// cout << ret_len << endl;
        if (ret_len > 0)
        {
            /* 剥去以太头部 */
            arp_packet = (struct ether_arp *)(buf + ETHER_HEADER_LEN);
            /* arp操作码为2代表arp应答 */
            if (ntohs(arp_packet->arp_op) == 2)
            {
                std::string mac, ip ;
                char tmp[10] ;
                bzero(tmp, sizeof(tmp)) ;
                for (i = 0; i < IP_ADDR_LEN; i++) {
                    sprintf(tmp, "%u", arp_packet->arp_spa[i]) ;
                    ip+=tmp ;
                    if(i != IP_ADDR_LEN-1) {
                        ip+="." ;
                    }
                }

                for (i = 0; i < ETH_ALEN; i++) {
                    sprintf(tmp, "%02x", arp_packet->arp_sha[i]) ;
                    mac+=tmp ;
                    if(i != ETH_ALEN-1) {
                        mac+=":" ;
                    } 
                }
                
                pair<string, string> pp ;
                pp.first = ip ;
                pp.second = mac ;
                macExist(mac) ;
                ipMac.insert(pp) ;
                cout << mac << "     " << ip << endl ;
            }
            //何时接收完成？
            //对端发送完成的话
        }
    }
}
