//
// Created by jcbjcbjc on 10/6/22.
//

#ifndef MUDUO_LOCALTUNNELCONN_H
#define MUDUO_LOCALTUNNELCONN_H
#include"ReverseProxy/Util/define.h"

class LocalTunnelConn {
public:
    LocalTunnelConn(EventLoop* loop,
                    string& client_id,
                    string& tun_id,
                    string& TConn_id,
                    string& local_server_host,
                    u_int32_t local_server_port,
                    string& proxy_server_host,
                    u_int32_t proxy_server_port);


    ~LocalTunnelConn();
    void setup();
    void connect();
private:
    void OnLocalMessage(const TcpConnectionPtr&,
                        Buffer*,
                        Timestamp);
    void OnProxyMessage(const TcpConnectionPtr&,
                        Buffer*,
                        Timestamp);

    EventLoop* loop_;

    string TConn_id_;

    ConnectionCallback localConnectionCallback_;
    ConnectionCallback proxyConnectionCallback_;

    std::string local_server_host_;
    u_int32_t local_server_port_;
    std::string proxy_server_host_;
    u_int32_t proxy_server_port_;

    std::unique_ptr<TcpClient> local_ctl_;
    std::unique_ptr<TcpClient> proxy_ctl;
    TcpConnectionPtr local_conn_;
    TcpConnectionPtr proxy_conn_;

    GetLoopCallback  getLoopCallback_;

};


#endif //MUDUO_LOCALTUNNELCONN_H
