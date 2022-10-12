//
// Created by jcbjcbjc on 10/6/22.
//

#ifndef MUDUO_PROXYTUNNELCONN_H
#define MUDUO_PROXYTUNNELCONN_H


#include "ReverseProxy/Util/define.h"

class ProxyTunnelConn {
private:
    string TConn_id_;

    TcpConnectionPtr proxy_conn_;
    TcpConnectionPtr public_conn_;
};


#endif //MUDUO_PROXYTUNNELCONN_H
