# Webserver-linux-pthread


Lightweight Multi-Threaded Network Server

## Project Description

This project is a lightweight multi-threaded network server developed in C++ for the Linux environment. It utilizes a thread pool to efficiently handle a large number of client connections and respond to their requests promptly. Advanced technologies such as I/O multiplexing, simulated Proactor pattern, and finite state machine have been employed to further optimize the server's performance.

## Key Features

- Supports remote network communication based on Socket and utilizes **epoll** for **I/O multiplexing** and socket monitoring.
- Implements a **thread pool** to efficiently handle events (I/O operations, exceptions, and timers) from the event ready queue using multiple threads.
- Wraps **Linux locks**, placing lock creation and destruction functions in the class's constructor and destructor, simplifying multi-threaded programming.
- Uses a **finite state machine** to parse HTTP request messages and generate appropriate response messages.
- Implements a timer using a **doubly-linked list** to periodically check and close **inactive connections**, improving server resource utilization.

## Requirements

- Linux operating system
- C++11 compiler or above

## Installation and Running

1. Clone the project to your local machine:

```bash
git clone https://github.com/ElricPjYi/webserver-linux-pthread.git
cd webserver
```

2. Build the project:

```bash
g++ *.cpp -pthread
```

3. Run the server:

```bash
./a.out 80
```

## Usage Example

The following example demonstrates how to use the server to set up a simple HTTP service:

```bash
root@111:~# cd webserver
root@111:~/webserver# ./a.out 80
create the 0th thread
创建第0个线程成功
create the 1th thread
创建第1个线程成功
create the 2th thread
创建第2个线程成功
create the 3th thread
创建第3个线程成功
create the 4th thread
创建第4个线程成功
create the 5th thread
创建第5个线程成功
create the 6th thread
创建第6个线程成功
create the 7th thread
创建第7个线程成功

```

Then you can go to http://{your_ip}:{your_port}/index.html to get the home page.

The running log:
```bash
读到了数据：GET / HTTP/1.1
Host: 8.134.112.168
Connection: keep-alive
Cache-Control: max-age=0
Upgrade-Insecure-Requests: 1
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.188
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
Accept-Encoding: gzip, deflate
Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6


got 1 http line:GET / HTTP/1.1
got 1 http line:Host: 8.134.112.168
got 1 http line:Connection: keep-alive
got 1 http line:Cache-Control: max-age=0
oop! unknow header Cache-Control: max-age=0
oop! unknow header Cache-Control: max-age=0
got 1 http line:Upgrade-Insecure-Requests: 1
oop! unknow header Upgrade-Insecure-Requests: 1
oop! unknow header Upgrade-Insecure-Requests: 1
got 1 http line:User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.188
oop! unknow header User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.188
oop! unknow header User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/115.0.0.0 Safari/537.36 Edg/115.0.1901.188
got 1 http line:Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
oop! unknow header Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
oop! unknow header Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7
got 1 http line:Accept-Encoding: gzip, deflate
oop! unknow header Accept-Encoding: gzip, deflate
oop! unknow header Accept-Encoding: gzip, deflate
got 1 http line:Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
oop! unknow header Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
oop! unknow header Accept-Language: zh-CN,zh;q=0.9,en;q=0.8,en-GB;q=0.7,en-US;q=0.6
got 1 http line:
*******************do_request开始执行
---------------------字符串处理完毕，请求的文件路径是/root/webserver/resources/
----------------下面开始生成响应
```


## Contribution

Feedback and suggestions for this project are welcome! If you wish to contribute, feel free to submit a Pull Request, and we'll review and merge outstanding code.


## Author

- Author: Elric PJ
- GitHub: [ElircPjYi](https://github.com/ElircPjYi)





