# TCPsocket函数详解

### 1.socket套接字
`socket()` 函数是一个在网络编程中常用的函数，用于创建一个新的套接字（socket）。

```c
#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain, int type, int protocol);
```

参数解释：
- `domain`：指定协议族或地址族。常见的协议族有 `AF_INET`（IPv4），`AF_INET6`（IPv6），以及 `AF_UNIX`（本地套接字）。你也可以使用相应的常数代替这些符号。
    AF_INET: IPV4的协议族
    AF_INET6:IPV6的协议族
    AF_BLUETOOTH:蓝牙协议族
    AF_UNIX/AF_LOCAL:unix域协议，本地网络协议，用于IPC
    ...
- `type`：指定套接字类型。常见的类型有 `SOCK_STREAM`（流式套接字，用于 TCP）和 `SOCK_DGRAM`（数据报套接字，用于 UDP）。其他可选类型可以通过查阅相关文档。
    SOCK_STREAM: 流式套接字，针对 TCP 应用
    SOCK_DGRAM : 数据报套接字，针对 UDP 应用
    SOCK_RAW   : 原始套接字
- `protocol`：指定具体的传输协议。通常使用 `0` 来自动选择合适的默认协议。
指定协议，如果指定0，表示使用默认的协议；
   - IPPROTO_IP  IP传输协议
   - IPPROTO_TCP  TCP传输协议
   - IPPROTO_UDP  UDP协议
   - IPPROTO_SCTP  SCTP传输协议
   - IPPROTO_ICMP   ICMP协议
   - IPPROTO_IGMP  IGMP协议

返回值：
- 如果套接字创建成功，则返回一个非负整数作为套接字描述符（socket descriptor），可以用于后续的网络通信操作。
- 如果套接字创建失败，则返回 `-1`，并设置全局变量 `errno` 表示错误码。

创建套接字成功后，你可以使用该套接字进行各种网络通信操作，例如建立连接、发送和接收数据等。请注意，在使用套接字之前，可能需要配置套接字的一些属性，如绑定地址和端口号（使用 `bind()` 函数）以及监听连接请求（使用 `listen()` 函数）。

### 2.配置服务器IP地址和端口号(套接字地址互联网)
`struct sockaddr_in` 是一种用于表示 IPv4 地址和端口的结构体，它是网络编程中常用的结构体类型之一。 该结构体用于在套接字编程中指定通信的目标地址和端口号。  
```c
     struct sockaddr_in {
         sa_family_t    sin_family; /* address family: AF_INET */
         in_port_t      sin_port;   /* port in network byte order */
         struct in_addr sin_addr;   /* internet address */
     };

     /* Internet address. */
     struct in_addr {
         uint32_t       s_addr;     /* address in network byte order */
     };

    // 2.配置服务器的IP地址和端口号  --- sockaddr_in 新结构体
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                   // IPV4 网络协议
    server_addr.sin_port = htons(SERVER_PORT);          // 本机器端口号转化为网络段 host to net short
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP); // 本机IP转化为网络IP
    socklen_t addrlen = sizeof(struct sockaddr_in);
```
**Linux 提供了用于转化“主机字节序”与“网络字节序”之间进行的相互转化函数**
```c
NAME
       htonl, htons, ntohl, ntohs - convert values between host and network byte order

SYNOPSIS
     #include <arpa/inet.h>

     uint32_t htonl(uint32_t hostlong);
     将32位无符号整数从主机字节序转换为网络字节序（大端序）。

     uint16_t htons(uint16_t hostshort);
    将16位无符号整数从主机字节序转换为网络字节序（大端序）。

     uint32_t ntohl(uint32_t netlong);
    将32位无符号整数从网络字节序（大端序）转换为主机字节序。

     uint16_t ntohs(uint16_t netshort);
    将16位无符号整数从网络字节序（大端序）转换为主机字节序。
```
**将“点分式IP字符串”和“标准的IP地址结构体”进行转换可以使用以下函数：**

1. `inet_pton` 函数：将“点分式IP字符串”转换为标准的IP地址结构体。
```C
#include <arpa/inet.h>

int inet_pton(int af, const char *src, void *dst);
```
   - 参数 `af`：地址族，可以是 `AF_INET` (IPv4) 或 `AF_INET6` (IPv6)。
   - 参数 `src`：指向包含Ipv4或IPv6地址的“点分式IP字符串”的指针。
   - 参数 `dst`：指向存储转换后IP地址的目标结构的指针。
   - 返回值：如果转换成功，则返回 1；如果提供的源IP地址无效或发生错误，则返回 0。

2. `inet_ntop` 函数：将标准的IP地址结构体转换为“点分式IP字符串”显示。
```C
#include <arpa/inet.h>

const char *inet_ntop(int af, const void *src, char *dst, socklen_t size);
```
   - 参数 `af`：地址族，可以是 `AF_INET` (IPv4) 或 `AF_INET6` (IPv6)。
   - 参数 `src`：指向要转换的标准IP地址结构体的指针。
   - 参数 `dst`：用于存储转换后“点分式IP字符串”的缓冲区。
   - 参数 `size`：指定缓冲区大小。
   - 返回值：如果转换成功，则返回指向缓冲区中转换后的“点分式IP字符串”的指针；如果发生错误，则返回 NULL。

这两个函数可以方便地在“点分式IP字符串”和标准的IP地址结构体之间进行相互转换，使得我们能够更方便地处理网络编程中的IP地址。

3. `inet_aton` 函数是一个 C 库函数，用于将 IPv4 地址从其字符串表示形式转换为其二进制形式。该函数将字符串作为输入，并将其转换为表示 IP 地址的 32 位二进制值。 
 
**函数原型：**
```c 
#include <arpa/inet.h>

int inet_aton(const char *cp, struct in_addr *inp);
```
**参数解释：**
    cp：指向以 null 结尾的字符串的指针，该字符串包含点十进制表示法的 IPv4 地址（例如，“192.168.0.1”）。
    inp：指向结构 （ struct in_addr） 将存储转换后的二进制 IP 地址。

**返回值：**

    如果字符串是有效的 IPv4 地址，则该函数返回 1，并且转换后的 IP 地址存储在 inp 结构。
    如果字符串不是有效的 IPv4 地址，或者发生错误，则该函数返回 0。

4. `inet_addr` 函数是一个用于将点分十进制的 IPv4 地址转换为网络字节序的 32 位无符号整数的函数。它的声明如下：
**函数原型：**
```c
#include <arpa/inet.h>

in_addr_t inet_addr(const char *cp);
```

**参数说明：**
- `cp`：指向包含点分十进制 IPv4 地址的字符串。

**返回值：**
- 如果转换成功，返回转换后的网络字节序的 IPv4 地址。
- 如果转换失败，返回 `INADDR_NONE`。

示例用法：

```c
#include <stdio.h>
#include <arpa/inet.h>

int main() {
    const char *ipAddress = "192.168.0.1";
    in_addr_t addr = inet_addr(ipAddress);
    
    if (addr != INADDR_NONE) {
        printf("IPv4 Address: %s => 0x%08X\n", ipAddress, addr);
    } else {
        printf("Invalid IPv4 Address\n");
    }
    
    return 0;
}
```

该示例将打印点分十进制的 IPv4 地址及其对应的网络字节序的值。注意，在使用 `inet_addr` 函数时，请务必保证传入的 IPv4 地址字符串格式正确，否则可能导致错误的结果或者转换失败。

5. `setsockopt()`函数用于设置套接字选项。它可以配置套接字的行为，例如启用/禁用某些功能、设置超时时间等。

以下是`setsockopt()`函数的详细说明：

**函数原型：**
```c
int setsockopt(int sockfd, int level, int optname, const void *optval, socklen_t optlen);
```

**参数解释：**
- `sockfd` 参数是要进行设置的套接字的描述符。
- `level` 参数指定了要设置的选项的协议级别或层级。
- `optname` 参数指定了具体要设置的选项名称。
- `optval` 参数是一个指针，指向包含设置选项值的缓冲区。
- `optlen` 参数是 `optval` 缓冲区中数据的大小。

**返回值：**
- 如果设置选项成功，返回0。
- 如果出现错误，返回-1，并设置相应的错误码。

**具体解释：**
通过调用`setsockopt()`函数，可以根据需要设置套接字的不同选项，以满足特定的通信要求。这些选项可以在不同的协议级别上设置，涉及连接管理、流控制、超时、广播等方面。

使用`level`和`optname`来指定具体要设置的选项，在`optval`缓冲区中提供要设置的选项值，并使用`optlen`指定选项值的大小。

下面是一些常见的选项级别和选项名称的示例：
- `SOL_SOCKET` 表示设置套接字级别的选项，常见于通用套接字操作。
- `IPPROTO_TCP` 表示设置TCP协议级别的选项，用于TCP套接字操作。
- `IPPROTO_IP` 表示设置IP协议级别的选项，常见于IP套接字操作。

具体的选项名称以及它们所属的级别取决于特定的通信需求和协议。

### 3.blind
`bind()`函数是C语言中用于将一个套接字（socket）与一个特定的IP地址和端口号绑定在一起的函数。它通常在进行TCP网络编程时使用。

在TCP网络编程中，服务器程序需要监听一个特定的IP地址和端口号，以便能够接收客户端的连接请求。`bind()`函数就是用来完成这个绑定过程的。

**函数原型：**
```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

**参数解释：**
- `sockfd`参数为套接字描述符，即之前调用`socket()`函数创建的套接字。
- `addr`参数为一个指向`struct sockaddr`结构体的指针，其中包含了待绑定的IP地址和端口号。
- `addrlen`参数为`addr`结构体的长度。

**返回值：**
- 如果绑定成功，返回值为0；
- 如果出现错误，返回值为-1。

**具体解释：**
通过`bind()`函数，我们将一个已经创建的套接字与特定的IP地址和端口号绑定在一起。这样使得该套接字可以接收到指定IP地址和端口号上的数据传输操作。

在调用`bind()`函数时，我们需要提供一个`struct sockaddr`结构体作为参数，用于指定要绑定的IP地址和端口号。`sockaddr`结构体包含了多个字段，如`sin_family`、`sin_addr`和`sin_port`。其中，`sin_family`字段表示网络协议族，通常设置为`AF_INET`表示IPv4；`sin_addr`字段表示IP地址；`sin_port`字段表示端口号。

绑定成功后，服务器套接字将会监听指定的IP地址和端口号，以便能够接受客户端的连接请求。如果绑定失败，通常会返回一个错误码，我们可以通过检查返回值来判断是否绑定成功。
### 4.listen
`listen()`函数是C语言中用于将一个绑定到指定IP地址和端口号的套接字设置为监听状态的函数。在进行TCP网络编程时，该函数常用于服务器程序中。

**函数原型：**
```c
int listen(int sockfd, int backlog);
```

**参数解释：**
- `sockfd`参数是已经绑定到指定IP地址和端口号的套接字描述符。
- `backlog`参数是等待连接队列的最大长度。

**返回值：**
- 如果成功监听，返回值为0；
- 如果出现错误，返回值为-1。

**具体解释：**
通过调用`listen()`函数，我们可以将一个绑定到指定IP地址和端口号的套接字设置为监听状态。这样，服务器就能够接受客户端的连接请求了。

在调用`listen()`函数时，我们需要提供一个已经绑定的套接字描述符作为参数。此外，还可以指定等待连接队列的最大长度。等待连接队列是由操作系统维护的一种数据结构，用于存储客户端连接请求，当新的客户端请求到达时，它们会被加入到等待队列中。`backlog`参数定义了该队列的最大长度，如果队列已满，则额外的连接请求可能会被丢弃。

当服务器套接字处于监听状态时，它会开始接受客户端连接请求。对于每个连接请求，服务器可以通过`accept()`函数接受并处理。

### 5.connect
`connect()` 函数是在网络编程中常用的函数之一，用于建立与远程主机的连接。

```c
#include <sys/types.h>
#include <sys/socket.h>

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

参数解释：
- `sockfd`：指定已创建的套接字描述符（socket descriptor），即要使用的套接字。
- `addr`：指向 `struct sockaddr` 类型（包含目标主机地址和端口号）的指针。根据套接字的协议族不同，可以将 `struct sockaddr` 强制转换为对应的地址结构体类型，例如 `struct sockaddr_in`（IPv4）或 `struct sockaddr_in6`（IPv6）。
- `addrlen`：指定 `addr` 所指向的地址结构体的长度。

返回值：

- 如果成功连接到远程主机，则返回 `0`。
- 如果连接失败，则返回 `-1`，并设置全局变量 `errno` 表示错误码。

注意事项：
- 在调用 `connect()` 函数前，必须先创建一个套接字，并通过 `bind()` 函数绑定本地地址（可选），然后才能进行连接操作。
- `connect()` 函数会阻塞程序的执行，直到连接成功建立或出现错误。
- 当连接建立成功后，你可以使用该套接字来发送和接收数据，也可以关闭连接。

成功建立连接后，你可以与远程主机进行数据交换，例如通过套接字的 `send()` 和 `recv()` 函数发送和接收数据。注意，在使用套接字进行数据交互前，请务必确保连接已经成功建立。
### 6.accept
`accept()`函数是C语言中用于接受客户端连接请求并创建新的套接字用于与客户端通信的函数。在进行TCP网络编程时，该函数常用于服务器程序中。

**函数原型：**
```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

**参数解释：**
- `sockfd`参数为已经处于监听状态的套接字描述符。
- `addr`参数是一个指向`struct sockaddr`结构体的指针，用于存储客户端的地址信息。
- `addrlen`参数为`addr`结构体的长度，调用前需要初始化该值。

**返回值：**
- 如果成功接受客户端连接，返回一个新的套接字描述符，可以使用该套接字与客户端通信；
- 如果出现错误，返回值为-1。

**具体解释：**
通过调用`accept()`函数，服务器可以接受客户端的连接请求，并在成功连接后创建一个新的套接字。这样，服务器就可以使用新的套接字与客户端进行通信了。

当使用`accept()`函数接受客户端连接请求时，它会阻塞当前线程直到有新的连接请求到达。一旦有新的连接请求到达，`accept()`函数会返回一个新的套接字描述符，该套接字已经与客户端建立了连接，并且可以使用该套接字进行数据传输操作。

此外，`addr`参数提供了一个用于存储客户端地址信息的结构体指针，可以通过它获取客户端的IP地址和端口号等信息。`addrlen`参数需要传递一个指向`addr`结构体长度的指针，因为在调用`accept()`函数时，操作系统会更新这个长度值。

**注意：** 在多线程或多进程的服务器程序中，通常将新的套接字与客户端的连接分发给一个新的线程或进程来处理。这样可以使服务器同时处理多个客户端连接，提高并发性能。

### 7.往套接字上面发送数据
在TCP和UDP的网络编程中，你可以使用`write()`、`send()`和`sendto()`这三个函数来发送数据。然而，`sendto()`函数通常更适合于UDP应用程序，而`write()`和`send()`则更常用于TCP应用程序。

`send()` 函数用于通过已连接的套接字发送数据。它位于 `<sys/types.h>` 和 `<sys/socket.h>` 头文件中，并具有如下原型：

```c
#include <sys/types.h>
#include <sys/socket.h>

ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```

参数解释：
- `sockfd`：指定已连接的套接字描述符（socket descriptor），即要使用的套接字。
- `buf`：指向要发送数据的缓冲区的指针。
- `len`：指定要发送数据的大小（以字节为单位）。
- `flags`：可选标志，默认为 0。常见的标志有 `MSG_DONTWAIT`（非阻塞发送）和 `MSG_NOSIGNAL`（禁止发送 SIGPIPE 信号）等。

返回值：
- 如果成功发送数据，则返回实际发送的字节数。这个值可以小于等于 `len`。
- 如果发送失败，则返回 `-1`，并设置全局变量 `errno` 表示错误码。

注意事项：
- `send()` 函数会阻塞程序的执行，直到所有请求的数据都已经发送出去或出现错误。
- 其中的数据是按字节发送的，所以如果需要发送结构体等复杂类型的数据，需要进行适当的转换和处理。
- 发送的数据可能会在网络上被分成多个包进行传输，因此不能保证一次 `send()` 调用就将所有数据完全发送出去。
- 在发送大数据块或连续的数据时，可能需要进行多次 `send()` 调用，以确保将所有数据发送出去。

在TCP和UDP的网络编程中，你可以使用`write()`、`send()`和`sendto()`这三个函数来发送数据。然而，`sendto()`函数通常更适合于UDP应用程序，而`write()`和`send()`则更常用于TCP应用程序。

让我们看一下每个函数的具体解释：

1. **write()**
   - 用于在已连接的套接字上发送数据。
   - 函数原型：`ssize_t write(int sockfd, const void *buf, size_t count);`
   - 参数包括套接字描述符 `sockfd`、指向要发送数据的缓冲区 `buf` 的指针以及待发送数据的长度 `count`。
   - 返回值为发送的字节数，如果出现错误，则返回-1。

2. **send()**
   - 用于在已连接的套接字上发送数据，与`write()`函数类似。
   - 函数原型：`ssize_t send(int sockfd, const void *buf, size_t len, int flags);`
   - 参数包括套接字描述符 `sockfd`、指向要发送数据的缓冲区 `buf` 的指针、待发送数据的长度 `len` 以及其他可选的标志参数 `flags`。
   - 返回值为发送的字节数，如果出现错误，则返回-1。

3. **sendto()**
   - 用于在无连接的套接字上（如UDP套接字）发送数据。
   - 函数原型：`ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);`
   - 参数包括套接字描述符 `sockfd`、指向要发送数据的缓冲区 `buf` 的指针、待发送数据的长度 `len`、其他可选的标志参数 `flags`，以及目标地址 `dest_addr` 和地址结构体的长度 `addrlen`。
   - 返回值为发送的字节数，如果出现错误，则返回-1。

注意：UDP套接字在每次发送数据时都需要指定目标地址和端口号，并使用`sendto()`函数发送数据。这是因为UDP是一种面向无连接的协议，不同于TCP中已建立的连接，可以直接通过套接字进行发送。而TCP套接字在连接建立后，可以使用`write()`或`send()`进行连续发送，操作系统会自动将数据发送到对应的目标地址。

总结：
- 在TCP应用程序中，可以使用`write()`和`send()`函数在已连接的套接字上发送数据；
- 在UDP应用程序中，通常更适合使用`sendto()`函数，在无连接的套接字上发送数据，需要显式指定目标地址和端口号。


### 8.从套接字上面接收数据
在TCP和UDP的网络编程中，你可以使用`read()`、`recv()`和`recvfrom()`这三个函数来接收数据。

让我们看一下每个函数的具体解释：

1. **read()**
   - 用于从已连接的套接字读取数据。
   - 函数原型：`ssize_t read(int sockfd, void *buf, size_t count);`
   - 参数包括套接字描述符 `sockfd`、指向接收数据的缓冲区 `buf` 的指针以及期望接收的数据长度 `count`。
   - 返回值为实际读取的字节数，如果出现错误或到达文件结尾，则返回0或-1。

2. **recv()**
   - 用于从已连接的套接字读取数据，类似于`read()`函数，但提供了更多的控制选项。
   - 函数原型：`ssize_t recv(int sockfd, void *buf, size_t len, int flags);`
   - 参数包括套接字描述符 `sockfd`、指向接收数据的缓冲区 `buf` 的指针、期望接收的最大数据长度 `len`、额外的可选标志参数 `flags`。
   - 返回值为实际读取的字节数，如果出现错误或到达文件结尾，则返回0或-1。

3. **recvfrom()**
   - 用于从无连接的套接字（如UDP套接字）接收数据。
   - 函数原型：`ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);`
   - 参数包括套接字描述符 `sockfd`、指向接收数据的缓冲区 `buf` 的指针、期望接收的最大数据长度 `len`、额外的可选标志参数 `flags`、以及用于存储发送方地址信息的结构体指针 `src_addr` 和地址结构体的长度变量 `addrlen`。
   - 返回值为实际读取的字节数，如果出现错误或到达文件结尾，则返回0或-1。

注意：UDP套接字在每次接收数据时需要获取发送方的地址信息，并使用`recvfrom()`函数接收数据。这是因为UDP是一种面向无连接的协议，每个数据包在发送时都必须包含目标地址和端口号，所以接收数据时需要获取发送方的地址信息和端口号。

总结：
- 在TCP应用程序中，可以使用`read()`和`recv()`函数从已连接的套接字接收数据；
- 在UDP应用程序中，通常更适合使用`recvfrom()`函数，以便接收来自不同发送方的数据，并获取发送方的地址信息。

`recv()`函数是在TCP和UDP程序中用于接收数据的函数之一。它可以从已连接的套接字或无连接的套接字上接收数据。

下面是`recv()`函数的详细解释：

**函数原型：**
```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
```

**参数解释：**
- `sockfd` 参数是一个套接字描述符，用于标识要接收数据的套接字。
- `buf` 参数是指向接收数据缓冲区的指针，用于存储从套接字接收到的数据。
- `len` 参数表示接收缓冲区的大小，即期望接收的最大数据长度。
- `flags` 参数是可选的标志，用于控制接收操作的行为。

**返回值：**
- 如果成功接收到数据，返回实际接收到的字节数；
- 如果连接关闭，则返回0，表示没有更多的数据可接收；
- 如果出现错误，返回-1。

**具体解释：**
通过调用`recv()`函数，程序会阻塞当前线程，直到有数据到达套接字。一旦有数据到达，`recv()`函数会将数据存储到指定的缓冲区中，并返回实际接收到的字节数。

需要注意的是，`recv()`函数适用于已连接的套接字（如TCP套接字）和无连接的套接字（如UDP套接字）。对于无连接的套接字，因为每个数据包都需要附带发送方的地址信息，所以在接收数据时可以通过`recvfrom()`函数获取发送方的地址信息。

### 9.关闭套接字(shutdown/close)
  `shutdown()`函数用于关闭一个套接字的发送或接收功能，以结束与对方的通信。

以下是`shutdown()`函数的详细说明：

**函数原型：**
```c
int shutdown(int sockfd, int how);
```

**参数解释：**
- `sockfd` 参数是要关闭的套接字的描述符。
- `how` 参数指定了关闭操作的类型：
  - `SHUT_RD`：关闭接收功能 (Read)。此标志使得套接字无法接收数据。
  - `SHUT_WR`：关闭发送功能 (Write)。此标志使得套接字无法发送数据。
  - `SHUT_RDWR`：同时关闭接收和发送功能。相当于按顺序调用两次 `shutdown()`，先关闭接收再关闭发送。

**返回值：**
- 如果关闭操作成功，返回0。
- 如果出现错误，返回-1，并设置相应的错误码。

**具体解释：**
通过调用`shutdown()`函数，可选择性地关闭套接字的发送和/或接收功能。这个函数通常在完成所有的数据收发后用于关闭连接。

使用 `SHUT_RD` 标志来关闭接收功能将使得套接字无法接收更多的数据，但已经接收到的数据可以继续读取。使用 `SHUT_WR` 标志来关闭发送功能将使得套接字无法发送数据，但仍然可以接收对方发送的数据。若需同时关闭接收和发送功能，可以使用 `SHUT_RDWR` 标志。

需要注意，关闭一个套接字并不会立即终止连接，它只是停止在该套接字上的数据收发。通常情况下，需要调用 `close()` 函数来彻底关闭套接字并释放相关资源。

`close()`函数用于关闭一个套接字，终止与对方的连接并释放相关的资源。

以下是`close()`函数的详细说明：

**函数原型：**
```c
int close(int sockfd);
```

**参数解释：**
- `sockfd` 参数是要关闭的套接字的描述符。

**返回值：**
- 如果关闭操作成功，返回0。
- 如果出现错误，返回-1，并设置相应的错误码。

**具体解释：**
通过调用`close()`函数，可以关闭指定的套接字。关闭套接字会终止与对方的连接并释放相应的资源。

需要注意的是，在调用`close()`函数之前，建议先使用`shutdown()`函数关闭套接字的发送或接收功能，以确保数据传输的完整性。这样做可以确保所有待发送或已接收的数据都被正确处理。

##### 线程
`pthread_detach()` 函数用于分离线程。分离线程时，线程退出时会自动释放其资源，而无需调用另一个线程  `pthread_join()` 并检索其退出状态。 

的函数原型  `pthread_detach()`` 具体如下： 

```c 

#include <pthread.h>

int pthread_detach(pthread_t thread);
```




### UDP流程

