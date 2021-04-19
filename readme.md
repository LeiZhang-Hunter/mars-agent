# node-agent

## 项目背景

由于部门所有业务都迁移到了K8S，需要一个强有力的agent作为支撑，所以打算使用cpp，基于libevent，开发一个高性能
的agent，所以开发这个作品,希望可以用在部门中

为了最大利用多核和cpu，采用纯异步，将会最大限度利用内核态

## 目标集成功能

1.Apollo 携程稳定的配置中心

2.Eureka 服务注册中心，跨语言，任何服务都可以无侵入方式接入

3.健康检查

4.日志收集,直接继承旧的Atel的功能

5.普罗米修斯客户端

6.IPTABLES网络流量监控过滤，由于虎扑linux内核很老，不支持当下最新的伯里克过滤器技术

## 采用的第三方库

1. 网路通讯库libevent

下载地址:https://github.com/libevent/libevent/releases/download/release-2.1.12-stable/libevent-2.1.12-stable.tar.gz

2.yaml-cpp

mars使用的配置文件格式是yaml

yaml-cpp的github地址为

https://github.com/jbeder/yaml-cpp

