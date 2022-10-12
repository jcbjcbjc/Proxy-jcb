//
// Created by jcbjcbjc on 10/5/22.
//

#ifndef MUDUO_SERVER_H
#define MUDUO_SERVER_H
#include"ReverseProxy/Util/define.h"

class Server : std::enable_shared_from_this<Server>{

public:
    Server(EventLoop* eventLoop,int threadNum,int ctlPort,int proxyPort);
    ~Server();

    void start();
private:
    static const int UnclaimedProxyMapLen = 4;
    struct UnclaimedProxyMap {
        std::unordered_map<string, TcpConnectionPtr> conns_;
        MutexLock mutex_;
    };

    void ClaimProxyConn(const TcpConnectionPtr& conn,
                        Buffer* buffer,
                        Timestamp receiveTime);
    void newCtlConn(const TcpConnectionPtr& conn);
    void newProxyConn(const TcpConnectionPtr& conn);



    string createCtlId();
    void InitTunnelServer(const std::unique_ptr<TcpServer>& tunnelServer);

    int ctlPort_;
    int proxyPort_;

    EventLoop* loop_;

    ctlMap ctlMap_;
    //TODO improve it
    std::shared_ptr<UnclaimedProxyMap> hashedUnclaimedProxyMap_;

    std::unique_ptr<TcpServer> ctlServer_;
    std::unique_ptr<TcpServer> proxyServer_;

};
#endif //MUDUO_SERVER_H
