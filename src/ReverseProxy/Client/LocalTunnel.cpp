//
// Created by jcbjcbjc on 10/5/22.
//

#include "LocalTunnel.h"
LocalTunnel::LocalTunnel(EventLoop *loop,
                         string &tun_id,
                         string &local_server_host,
                         u_int32_t local_server_port,
                         string &proxy_server_host,
                         u_int32_t proxy_server_port)
:loop_(loop),
tun_id_(tun_id),
local_server_host_(local_server_host),
local_server_port_(local_server_port),
proxy_server_host_(proxy_server_host),
proxy_server_port_(proxy_server_port)
{


}
