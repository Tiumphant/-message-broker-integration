#pragma once

#include <amqpcpp.h>
#include <amqpcpp/libev.h>
#include <functional>
#include <string>
#include <mutex>

class BrokerClient {
public:
    BrokerClient(const std::string& address);
    ~BrokerClient();

    bool connect();
    void declareQueue(const std::string& queueName);

    bool publish(const std::string& queueName,
                 const std::string& message);

    void consume(const std::string& queueName,
                 std::function<void(const std::string&)> handler);

private:
    std::string addressStr;

    AMQP::LibEvHandler* handler;
    AMQP::TcpConnection* connection;
    AMQP::TcpChannel* channel;

    std::mutex publishMutex;

    bool connected = false;
};
