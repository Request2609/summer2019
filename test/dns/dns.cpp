#include <iostream>

//使这段代码1字节对齐
#pragma pack(1)
struct DNSHeader
{
    /* 1. 会话标识（2字节）*/
    unsigned short usTransID;        // Transaction ID

    /* 2. 标志（共2字节）*/
    unsigned char RD : 1;            // 表示期望递归，1bit
    unsigned char TC : 1;            // 表示可截断的，1bit
    unsigned char AA : 1;            // 表示授权回答，1bit
    unsigned char opcode : 4;        // 0表示标准查询，1表示反向查询，2表示服务器状态请求，4bit
    unsigned char QR : 1;            // 查询/响应标志位，0为查询，1为响应，1bit

    unsigned char rcode : 4;         // 表示返回码，4bit
    unsigned char zero : 3;          // 必须为0，3bit
    unsigned char RA : 1;            // 表示可用递归，1bit

    /* 3. 数量字段（共8字节） */
    unsigned short Questions;        // 问题数
    unsigned short AnswerRRs;        // 回答资源记录数
    unsigned short AuthorityRRs;     // 授权资源记录数
    unsigned short AdditionalRRs;    // 附加资源记录数
};
//取消指定对齐方式，继续缺省对其
#pragma pack()

struct BitFieldDemo
{   // 假如有二进制数1011 0010B，左边为高位，右边为低位
     // 则a == 10B, b == 110B, c == 010B
    unsigned char a : 2; // 高2位
    unsigned char b : 3;
    unsigned char c : 3; // 低2位
};

bool SendDnsPack(IN unsigned short usID,
                 IN SOCKET *pSocket, 
                 IN const char *szDnsServer, 
                 IN const char *szDomainName) {
    bool bRet = false;

    if (*pSocket == INVALID_SOCKET 
        || szDomainName == NULL 
        || szDnsServer == NULL 
        || strlen(szDomainName) == 0 
        || strlen(szDnsServer) == 0)
    {
        return bRet;
    }
    
    unsigned int uiDnLen = strlen(szDomainName);

    // 判断域名合法性，域名的首字母不能是点号，域名的
    // 最后不能有两个连续的点号 
    if ('.' == szDomainName[0] || ( '.' == szDomainName[uiDnLen - 1] 
          && '.' == szDomainName[uiDnLen - 2]) 
       )
    {
        return bRet;
    }
    
    /* 1. 将域名转换为符合查询报文的格式 */
    // 查询报文的格式是类似这样的：
    //      6 j o c e n t 2 m e 0
    unsigned int uiQueryNameLen = 0;
    BYTE *pbQueryDomainName = (BYTE *)malloc(uiDnLen + 1 + 1);
    if (pbQueryDomainName == NULL)
    {
        return bRet;
    }
    // 转换后的查询字段长度为域名长度 +2
    memset(pbQueryDomainName, 0, uiDnLen + 1 + 1);

    // 下面的循环作用如下：
    // 如果域名为  jocent.me ，则转换成了 6 j o c e n t  ，还有一部分没有复制
    // 如果域名为  jocent.me.，则转换成了 6 j o c e n t 2 m e
    unsigned int uiPos    = 0;
    unsigned int i        = 0;
    for ( i = 0; i < uiDnLen; ++i)
    {
      if (szDomainName[i] == '.')
      {
          pbQueryDomainName[uiPos] = i - uiPos;
          if (pbQueryDomainName[uiPos] > 0)
          {
              memcpy(pbQueryDomainName + uiPos + 1, szDomainName + uiPos, i - uiPos);
          }
          uiPos = i + 1;
      }
    }
        
    // 如果域名的最后不是点号，那么上面的循环只转换了一部分
    // 下面的代码继续转换剩余的部分， 比如 2 m e
    if (szDomainName[i-1] != '.')
    {
      pbQueryDomainName[uiPos] = i - uiPos;
      memcpy(pbQueryDomainName + uiPos + 1, szDomainName + uiPos, i - uiPos);
      uiQueryNameLen = uiDnLen + 1 + 1;
    }
    else
    {
      uiQueryNameLen = uiDnLen + 1;    
    }
    // 填充内容  头部 + name + type + class
    DNSHeader *PDNSPackage = (DNSHeader*)malloc(sizeof(DNSHeader) + uiQueryNameLen + 4);
    if (PDNSPackage == NULL)
    {
        goto exit;
    }
    memset(PDNSPackage, 0, sizeof(DNSHeader) + uiQueryNameLen + 4);

    // 填充头部内容
    PDNSPackage->usTransID = htons(usID);  // ID
    PDNSPackage->RD = 0x1;   // 表示期望递归
    PDNSPackage->Questions = htons(0x1);  // 本文第一节所示，这里用htons做了转换

    // 填充正文内容  name + type + class
    BYTE* PText = (BYTE*)PDNSPackage + sizeof(DNSHeader);
    memcpy(PText, pbQueryDomainName, uiQueryNameLen);

    unsigned short *usQueryType = (unsigned short *)(PText + uiQueryNameLen);
    *usQueryType = htons(0x1);        // TYPE: A

    ++usQueryType;
    *usQueryType = htons(0x1);        // CLASS: IN    

    // 需要发送到的DNS服务器的地址
    sockaddr_in dnsServAddr = {};
    dnsServAddr.sin_family = AF_INET;
    dnsServAddr.sin_port = ::htons(53);  // DNS服务端的端口号为53
    dnsServAddr.sin_addr.S_un.S_addr = ::inet_addr(szDnsServer);
    
    // 将查询报文发送出去
    int nRet = ::sendto(*pSocket,
        (char*)PDNSPackage,
        sizeof(DNSHeader) + uiQueryNameLen + 4,
        0,
        (sockaddr*)&dnsServAddr,
        sizeof(dnsServAddr));
    if (SOCKET_ERROR == nRet)
    {
        printf("DNSPackage Send Fail! \n");
        goto exit;
    }
    
    // printf("DNSPackage Send Success! \n");
    bRet = true;
    
// 统一的资源清理处       
exit:
    if (PDNSPackage)
    {
        free(PDNSPackage);
        PDNSPackage = NULL;
    }

    if (pbQueryDomainName)
    {
        free(pbQueryDomainName);
        pbQueryDomainName = NULL;
    }
    
    return bRet;
}

