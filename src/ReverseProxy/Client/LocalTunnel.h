//
// Created by jcbjcbjc on 10/5/22.
//

#ifndef MUDUO_PROXYTUNNEL_H
#define MUDUO_PROXYTUNNEL_H
#include"ReverseProxy/Util/define.h"

class LocalTunnel {
public:
    LocalTunnel(
            EventLoop* loop,
            string& tun_id,
            string& local_server_host,
            u_int32_t local_server_port,
            string& proxy_server_host,
            u_int32_t proxy_server_port);
    ~LocalTunnel();
    //TODO look at
    void setGetLoopCallback(GetLoopCallback cb){getLoopCallback_=std::move(cb);}

private:
    void newLocalConn(const TcpConnectionPtr&);
    void newProxyConn(const TcpConnectionPtr&);

    EventLoop* loop_;

    std::string tun_id_;

    std::string local_server_host_;
    u_int32_t local_server_port_;
    std::string proxy_server_host_;
    u_int32_t proxy_server_port_;

    LTunnelConnMap localTunnelMap_;

    GetLoopCallback  getLoopCallback_;

};


#endif //MUDUO_PROXYTUNNEL_H
