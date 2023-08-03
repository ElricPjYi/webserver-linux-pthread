#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/epoll.h>
#include"locker.h"
#include"threadpool.h"
#include<bits/stdc++.h>
#include<signal.h>
#include "http_conn.h"


#define MAX_FD 65535 //最大文件描述符
#define MAX_EVENT_NUMBER 10000  //一次的监听最大事件数量


//添加信号捕捉
void addsig(int sig, void(handler)(int)){
    struct sigaction sa;//信号处理
    memset(&sa,'\0',sizeof(sa));
    sa.sa_handler=handler;
    sigfillset(&sa.sa_mask);
    //sigfillset()函数用于初始化一个自定义信号集，
    //将其所有信号都填充满，也就是将信号集中的所有的标志位置为1，
    //使得这个集合包含所有可接受的信号，也就是阻塞所有信号。
    //这个函数可以用于快速创建一个包含所有信号的信号集，然后可以根据需要删除其中的某些信号。
    sigaction(sig,&sa,NULL);

}

// 添加文件描述符到epoll
extern void addfd(int epollfd, int fd, bool one_shot);

//从epoll中删除文件描述符
extern void removefd(int epollfd, int fd);

//修改
extern void modfd(int epollfd, int fd, int ev);




int main(int argc, char* argv[]){
    if(argc<=1){
        printf("按照如下格式运行：%s port_number\n",basename(argv[0]));
        exit(-1);
    }
    //获取端口号
    int port = atoi(argv[1]);
    //捕捉到SIGPIPE后忽略它，不会结束程序
    addsig(SIGPIPE,SIG_IGN);

    //创建+初始化线程池
    threadpool<http_conn> * pool = NULL;
    try{
        // printf("111\n");
        pool = new threadpool<http_conn>;//6.10 在这里卡住了,是阿里云那边限制了端口 HTTP只能是80
        // printf("222\n");
    } catch(...){
        exit(-1);
    }
    // printf("333\n");
    //创建一个数组用于保存所有的客户端信息
    http_conn *users =new http_conn[MAX_FD];
    
    //下面是socket部分
    //创建监听套接字
    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    //PF_INET是用IPV4，SOCK_STREAM是流式协议（TCP），0是不指定协议（默认TCP）
    //设置端口复用

    int reuse=1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    //绑定
    struct sockaddr_in address;
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;//多块网卡多个ip，所有ip都可以链接
    address.sin_port=htons(port);
    bind(listenfd,(struct sockaddr*)&address, sizeof(address));

    //监听
    listen(listenfd,5);

    //创建epoll对象，事件数组，添加监听文件描述符
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd=epoll_create(5);
    //将监听的文件描述符添加到epoll对象中

    addfd(epollfd, listenfd, false);

    http_conn::m_epollfd=epollfd;
    while(true){
        int num = epoll_wait(epollfd,events,MAX_EVENT_NUMBER,-1);
        //num=检测几个事件
        if((num<0)&&(errno!=EINTR)){
            printf("epoll failed\n");
            break;
        }

        //循环遍历事件数组
        // printf("111");

        for(int i=0;i<num;i++){
            //  printf("222");
            int sockfd=events[i].data.fd;
            if(sockfd==listenfd){
                //有客户端链接
                struct sockaddr_in client_address;
                socklen_t client_addrlen = sizeof(client_address);
                int connfd=accept(listenfd,(struct sockaddr*)&client_address, &client_addrlen);

                if(http_conn::m_user_count>=MAX_FD){
                    //目前连接数满了
                    //给客户端一个信息：服务器忙
                    close(connfd);
                    continue;
                }

                // 将新的客户的数据初始化，放到数组当中
                // 直接当索引比较方便
                users[connfd].init(connfd, client_address);

            }else if(events[i].events &(EPOLLRDHUP|EPOLLHUP|EPOLLERR)){
                //对方异常断开或者错误等事件
                users[sockfd].close_conn();
            }else if(events[i].events & EPOLLIN){

                

                if(users[sockfd].read()){
                    //一次性把所有数据都读完
                    pool->append(users+sockfd);
                }else
                {
                    users[sockfd].close_conn();
                }
            }else if(events[i].events & EPOLLOUT){
                //写事件，一次性写完
                if(!users[sockfd].write()){
                    users[sockfd].close_conn();
                }
            }
        }
    }

    close(epollfd);
    close(listenfd);
    delete [] users;
    delete pool;

    return 0;
}