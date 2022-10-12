//
// Created by jcbjcbjc on 10/5/22.
//

#include "ProxyClient.h"
string ProxyClient::createTunnelId() {
    string tun_id= rand_str(5);
    while(pTunnelMap_.find(tun_id)!=pTunnelMap_.end()){
        tun_id= rand_str(5);
    }
    return tun_id;
}
void ProxyClient::OnNewTunnelReq(Buffer *buffer, Timestamp receiveTime) {



}
