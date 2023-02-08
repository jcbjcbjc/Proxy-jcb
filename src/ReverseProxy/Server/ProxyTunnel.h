//
// Created by jcbjcbjc on 10/5/22.
//

#ifndef MUDUO_PROXYTUNNEL_H
#define MUDUO_PROXYTUNNEL_H
#include"ReverseProxy/Util/define.h"

class ProxyTunnel :public std::enable_shared_from_this<ProxyTunnel>{
public:
    explicit ProxyTunnel(EventLoop* loop,string tun_id,InitTunnelServerCallback cb);
    ~ProxyTunnel();

private:
    void newPublicConn(const TcpConnectionPtr&);
    //TODO MOVE TO NEXT LEVEL:PROXYTUNNELCONN
    /*void OnPublicConnMessage(const TcpConnectionPtr&,
                             Buffer*,
                             Timestamp);*/

    int listenFd_;
    int listenPort_;
    string listenAddr_;

    string tun_id_;

    EventLoop* loop_;

    std::unique_ptr<TcpServer> PTunnelServer_;

    //MutexLock public_fds_mutex_;
    //MutexLock free_proxy_tunnel_conns_mutex_;

    ///safe map In a Loop
    PTunnelConnMap proxyTunnelMap_;
    freePTunnelConns freeProxyTunnelConns_; //GUARDED_BY(free_proxy_tunnel_conns_mutex_);
    std::vector<TcpConnectionPtr> undeal_public_Conns_; //GUARDED_BY(public_fds_mutex_);
};


#endif //MUDUO_PROXYTUNNEL_H
