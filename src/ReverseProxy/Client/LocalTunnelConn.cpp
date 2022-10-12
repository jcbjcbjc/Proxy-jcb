//
// Created by jcbjcbjc on 10/6/22.
//

#include "LocalTunnelConn.h"
LocalTunnelConn::LocalTunnelConn(EventLoop* loop,
                                 string& client_id,
                                 string& tun_id,
                                 string& TConn_id,
                                 string& local_server_host,
                                 u_int32_t local_server_port,
                                 string& proxy_server_host,
                                 u_int32_t proxy_server_port)
:loop_(loop),
TConn_id_(TConn_id),
 local_server_host_(local_server_host),
 local_server_port_(local_server_port),
 proxy_server_host_(proxy_server_host),
 proxy_server_port_(proxy_server_port)
{
    if(getLoopCallback_){
        EventLoop* ioLoop=getLoopCallback_();
        //TODO NAME
        local_ctl_=std::unique_ptr<TcpClient>(
                new TcpClient(ioLoop, InetAddress(local_server_host, static_cast<uint16_t>(local_server_port)), ""));
        proxy_ctl=std::unique_ptr<TcpClient> (
                new TcpClient(ioLoop, InetAddress(proxy_server_host, static_cast<uint16_t>(proxy_server_port)), ""));
    }
    else{

    }
}
void LocalTunnelConn::setup() {
    assert(localConnectionCallback_);
    assert(proxyConnectionCallback_);
    local_ctl_->setConnectionCallback(localConnectionCallback_);
    proxy_ctl->setConnectionCallback(proxyConnectionCallback_);
    local_ctl_->setMessageCallback(
            std::bind(&LocalTunnelConn::OnLocalMessage,this,_1,_2,_3));
    proxy_ctl->setMessageCallback(
            std::bind(&LocalTunnelConn::OnProxyMessage,this,_1,_2,_3));

}