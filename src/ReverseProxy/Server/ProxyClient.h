//
// Created by jcbjcbjc on 10/5/22.
//

#ifndef MUDUO_PROXYCLIENT_H
#define MUDUO_PROXYCLIENT_H
#include"ReverseProxy/Util/define.h"

class ProxyClient :public std::enable_shared_from_this<ProxyClient>{
public:
    explicit ProxyClient(EventLoop* loop,string& ctl_id,const TcpConnectionPtr& conn )
    :loop_(loop),
    ctl_id_(ctl_id),
    ctl_conn_(conn)
    {
       ctl_conn_->setMessageCallback(
               std::bind(&ProxyClient::OnCtlMessage,this,_1,_2,_3)
               );


    }
    ~ProxyClient(){};

    void setInitTunnelServerCallback_(InitTunnelServerCallback cb){InitTunnelServerCallback_=std::move(cb);}
    void disconnect();

private:
    void OnCtlMessage(const TcpConnectionPtr& conn,
                        Buffer* buffer,
                        Timestamp receiveTime);

    void OnNewCtlReq(Buffer* buffer,
                     Timestamp receiveTime);
    void OnNewTunnelReq(Buffer* buffer,
                        Timestamp receiveTime);
    void OnFreePTunnelConnReq(Buffer* buffer,
                              Timestamp receiveTime);

    string createTunnelId();


    EventLoop* loop_;

    std::string ctl_id_;

    TcpConnectionPtr ctl_conn_;

    PTunnelMap pTunnelMap_;

    InitTunnelServerCallback InitTunnelServerCallback_;
};


#endif //MUDUO_PROXYCLIENT_H
