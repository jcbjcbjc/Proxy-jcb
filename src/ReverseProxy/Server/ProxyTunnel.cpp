//
// Created by jcbjcbjc on 10/5/22.
//
#include <arpa/inet.h>
#include <netinet/in.h>
#include "ProxyTunnel.h"
#include "muduo/net/Socket.h"
#include "muduo/net/SocketsOps.h"
#include "muduo/net/TcpServer.h"

ProxyTunnel::ProxyTunnel(EventLoop *loop, string tun_id,InitTunnelServerCallback cb)
: listenFd_(socketBindListen(0)),
  tun_id_(tun_id),
  loop_(loop),

  //TODO FIXME
  PTunnelServer_(new TcpServer(loop,InetAddress(sockets::getAddr(listenFd_)),"TunnelServer"+tun_id))
  //public_fds_mutex_(),
  //free_proxy_tunnel_conns_mutex_()
{
    struct sockaddr_in listenAddr;
    socklen_t listenAddrLen = sizeof(listenAddr);
    getsockname(listenFd_, (struct sockaddr*)&listenAddr, &listenAddrLen);
    listenPort_ = ntohs(listenAddr.sin_port);
    listenAddr_ = inet_ntoa(listenAddr.sin_addr);

    //TunnelServer
    PTunnelServer_->setConnectionCallback(
            std::bind(&ProxyTunnel::newPublicConn,this,_1));
    PTunnelServer_->setMessageCallback(
            std::bind(&ProxyTunnel::OnPublicConnMessage,this,_1,_2,_3));
    if(cb){
        cb(PTunnelServer_);
    }
    PTunnelServer_->startWithSameThreadPool();
}