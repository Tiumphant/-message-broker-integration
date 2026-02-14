#include "broker_client.h"
#include <iostream>
#include <unistd.h>

BrokerClient::BrokerClient(const std::string& address)
    : addressStr(address),
      handler(nullptr),
      connection(nullptr),
      channel(nullptr) {}

BrokerClient::~BrokerClient() {
    if (connection) delete connection;
    if (channel) delete channel;
    if (handler) delete handler;
}

bool BrokerClient::connect() {
    try {
        handler = new AMQP::LibEvHandler(nullptr);
        AMQP::Address addr(addressStr);
        connection = new AMQP::TcpConnection(handler, addr);
        channel = new AMQP::TcpChannel(connection);

        connected = true;
        std::cout << "Broker connected\n";
        return true;

    } catch (...) {
        std::cout << "Broker connection failed\n";
        connected = false;
        return false;
    }
}

void BrokerClient::declareQueue(const std::string& queueName) {
    if (!connected) return;

    channel->declareQueue(
        queueName,
        AMQP::durable
    );
}

bool BrokerClient::publish(const std::string& queueName,
                           const std::string& message) {
    if (!connected) return false;

    std::lock_guard<std::mutex> lock(publishMutex);

    channel->publish(
        "",
        queueName,
        message,
        AMQP::persistent
    );

    return true;
}

void BrokerClient::consume(
    const std::string& queueName,
    std::function<void(const std::string&)> handlerFn) {

    if (!connected) return;

    channel->consume(queueName)
        .onReceived(
            [handlerFn](const AMQP::Message& msg,
                        uint64_t tag,
                        bool redelivered) {

                std::string body(msg.body(), msg.bodySize());
                handlerFn(body);
            }
        );

    while (true) {
        sleep(1);
    }
}
