//
// Created by jcbjcbjc on 10/5/22.
//

#ifndef MUDUO_CLIENT_H
#define MUDUO_CLIENT_H
#include"ReverseProxy/Util/define.h"
#include "muduo/net/EventLoopThreadPool.h"
class Client{
public:

private:
    EventLoop* GetLoop(){return threadPool_->getNextLoop();}

    std::string proxy_server_host_;
    u_int32_t proxy_server_port_;

    std::string client_id_;

    EventLoop* loop_;

    std::unique_ptr<TcpClient> client_;

    LTunnelMap lTunnelMap_;

    std::unique_ptr<EventLoopThreadPool> threadPool_;

};



#endif //MUDUO_CLIENT_H
