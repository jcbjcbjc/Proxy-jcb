# Proxy-jcb
## Introduction
A proxy tool transfromed from the muduo library ,support ForwardProxy and ReverseProxy 
### Usage
#### use docker
```
docker build -t proxy-jcb
docker run --rm -it -v ${PWD}:/mnt -w /mnt proxy-jcb bash
```

在根目录dir下执行
```
cd src
chmod +x ./build.sh&&./build.sh
```
- 正向代理功能：在根目录dir下执行
   ```
   cd build&&cd release-proxy-jcb&&cd bin
   #./tcprelay 目标ip地址 目标端口 监听端口 
   ./tcprelay 127.0.0.1 8000 8500
   ```
- 反向代理功能：正在开发，目前在完善代理客户端节点和代理服务端的交互
