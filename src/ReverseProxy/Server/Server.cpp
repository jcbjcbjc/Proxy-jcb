//
// Created by jcbjcbjc on 10/5/22.
//
#include "ReverseProxy/Server/Server.h"

#include "ReverseProxy/Server/ProxyClient.h"
#include "muduo/net/EventLoop.h"

Server::Server(EventLoop* loop,int threadNum, int ctlPort, int proxyPort)
      :ctlPort_(ctlPort),
      proxyPort_(proxyPort) ,
      loop_(loop),
      hashedUnclaimedProxyMap_(new UnclaimedProxyMap()),
      ctlServer_(new TcpServer(loop_, InetAddress(static_cast<uint16_t>(ctlPort)), "ctlServer")),
      proxyServer_(new TcpServer(loop_, InetAddress(static_cast<uint16_t>(proxyPort)), "proxyServer"))
{
    //proxy
    proxyServer_->setThreadNum(threadNum);
    proxyServer_->setConnectionCallback(
            std::bind(&Server::newProxyConn,this,_1));
    /*proxyServer_->setMessageCallback(
            std::bind(&Server::OnProxyMessage,this,_1,_2,_3));*/


    //ctl
    ctlServer_->setConnectionCallback(
            std::bind(&Server::newCtlConn,this,_1));
    /*ctlServer_->setMessageCallback(
            std::bind(&Server::OnCtlMessage,this,_1,_2,_3));*/
}

void Server::newCtlConn(const TcpConnectionPtr &conn) {
    loop_->assertInLoopThread();
    LOG_DEBUG << conn->name() << (conn->connected() ? " UP" : " DOWN");
    if (conn->connected())
    {
        conn->setTcpNoDelay(true);
        string ctl_id=createCtlId();
        SP_ProxyClient proxyClient(new ProxyClient(loop_,ctl_id,conn));
        proxyClient->setInitTunnelServerCallback_( std::bind(&Server::InitTunnelServer,this,_1));

        ctlMap_.emplace(ctl_id,proxyClient);
    }
    else
    {
        auto it = ctlMap_.find(conn->name());
        if (it != ctlMap_.end())
        {
            it->second->disconnect();
            ctlMap_.erase(it);
        }
    }
}
void Server::newProxyConn(const TcpConnectionPtr &conn) {
    loop_->assertInLoopThread();
    LOG_DEBUG << conn->name() << (conn->connected() ? " UP" : " DOWN");
    if (conn->connected())
    {
        LOG_INFO<<"newProxyConn"<<"  "<<"from"<<conn->peerAddress().getSockAddr();

        conn->setTcpNoDelay(true);

        conn->setMessageCallback(
                std::bind(&Server::ClaimProxyConn,this,_1,_2,_3));
        {
            MutexLockGuard mutex(hashedUnclaimedProxyMap_->mutex_);
            hashedUnclaimedProxyMap_->conns_[conn->name()]=conn;
        }
    }
    else
    {
        //TODO fix it
    }
}

void Server::ClaimProxyConn(const TcpConnectionPtr &conn, Buffer *buffer, Timestamp receiveTime) {





}
string Server::createCtlId() {
    std::string ctl_id= rand_str(5);
    while(ctlMap_.find(ctl_id)!=ctlMap_.end()){
        ctl_id=rand_str(5);
    }
    return ctl_id;
}
void Server::InitTunnelServer(const std::unique_ptr<TcpServer> &tunnelServer) {
    tunnelServer->setThreadPool(proxyServer_->threadPool());
}



