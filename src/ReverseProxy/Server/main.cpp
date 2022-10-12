//
// Created by jcbjcbjc on 10/6/22.
//
#include"ReverseProxy/Util/define.h"
#include"ReverseProxy/Server/Server.h"
#include "muduo/net/EventLoop.h"

int main(){

    EventLoop loop;

    Server server(&loop,8,8000,8500);

    server.start();
    loop.loop();
}
