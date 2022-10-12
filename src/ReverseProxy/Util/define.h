//
// Created by jcbjcbjc on 10/5/22.
//

#ifndef MUDUO_DEFINE_H
#define MUDUO_DEFINE_H

#include <mutex>
#include <unordered_map>
#include <random>
#include "muduo/net/TcpServer.h"
#include "muduo/net/TcpClient.h"
#include "muduo/base/Logging.h"
#include "muduo/base/Mutex.h"

using namespace muduo;
using namespace muduo::net;

int socketBindListen(int port) {
    if (port < 0 || port > 65535) {
        return -1;
    }

    // 设置reuseaddr
    int listen_fd = 0;
    if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
    int optval = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
        close(listen_fd);
        return -1;
    }
}

template <typename keyT, typename valueT>
struct safe_unordered_map {
    std::mutex mutex_;
    std::unordered_map<keyT, valueT> map;
    bool isExist(keyT key) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (map.find(key) == map.end()) {
            return false;
        } else {
            return true;
        }
    }

    void erase(keyT key) {
        std::unique_lock<std::mutex> lock(mutex_);
        map.erase(key);
    }

    valueT get(keyT key, bool& isExist) {
        std::unique_lock<std::mutex> lock(mutex_);
        if (map.find(key) == map.end()) {
            isExist = false;
            return valueT{};
        } else {
            isExist = true;
        }
        return map[key];
    }

    valueT get(keyT key) {
        std::unique_lock<std::mutex> lock(mutex_);
        return map[key];
    }

    void add(keyT key, valueT val) {
        std::unique_lock<std::mutex> lock(mutex_);
        map.emplace(key, val);
    }

    bool empty() { return map.empty(); }
};

std::string rand_str(int len) {
    char tmp;                                 // tmp: 暂存一个随机数
    std::string buffer;                       // buffer: 保存返回值
    std::random_device rd;                    // 产生一个 std::random_device 对象 rd
    std::default_random_engine random(rd());  // 用 rd 初始化一个随机数发生器 random

    for (int i = 0; i < len; i++) {
        tmp = random() % 36;  // 随机一个小于 36 的整数，0-9、A-Z 共 36 种字符
        if (tmp < 10) {       // 如果随机数小于 10，变换成一个阿拉伯数字的 ASCII
            tmp += '0';
        } else {  // 否则，变换成一个大写字母的 ASCII
            tmp -= 10;
            tmp += 'A';
        }
        buffer += tmp;
    }
    return buffer;
};


class ProxyClient;
class ProxyTunnel;
class LocalTunnel;
class ProxyTunnelConn;
class LocalTunnelConn;


typedef std::shared_ptr<ProxyTunnel> SP_ProxyTunnel;
typedef std::shared_ptr<LocalTunnel> SP_LocalTunnel;
typedef std::shared_ptr<ProxyClient> SP_ProxyClient;
typedef std::shared_ptr<ProxyTunnelConn> SP_PTunnelConn;
typedef std::shared_ptr<LocalTunnelConn> SP_LTunnelConn;

//TODO safety!
typedef std::map<string,SP_ProxyClient> ctlMap;
typedef std::map<string,SP_ProxyTunnel> PTunnelMap;
typedef std::map<string,SP_LocalTunnel> LTunnelMap;
typedef safe_unordered_map<string,SP_PTunnelConn> PTunnelConnMap;
typedef std::vector<SP_PTunnelConn> freePTunnelConns;
typedef safe_unordered_map<string,SP_LTunnelConn> LTunnelConnMap;

typedef std::function<void(const std::unique_ptr<TcpServer>&)> InitTunnelServerCallback;

typedef std::function<EventLoop*()> GetLoopCallback;


#endif //MUDUO_DEFINE_H
