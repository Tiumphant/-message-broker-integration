# Message Broker Integration — Architecture

## High Level Architecture

                +------------------+
                | Producer Threads |
                +--------+---------+
                         |
                         v
                 BrokerClient.publish()
                         |
                         v
                  +--------------+
                  |  RabbitMQ    |
                  |   Broker     |
                  +------+-------+
                         |
                         v
                BrokerClient.consume()
                         |
                         v
                Consumer Worker Pool

---

## Component Diagram

Application Layer
    |
    v
BrokerClient Wrapper
    |
    v
AMQP-CPP Library
    |
    v
RabbitMQ Server

---

## Message Flow

1. Worker thread generates event
2. BrokerClient publishes message
3. RabbitMQ stores message
4. Consumer receives message
5. Callback handler processes message

---

## Reliability Strategy

- Durable queues
- Persistent messages
- Manual acknowledgements
- Retry on failure
- Dead-letter queue (future)

---

## Deployment Context

Environment: WSL Ubuntu  
Broker: RabbitMQ local  
Protocol: AMQP  
Language: C++17  
Build: CMake
