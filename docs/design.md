# Message Broker Integration — Design

## Design Goals

- Decouple message broker logic from business logic
- Provide reusable broker client wrapper
- Support both producer and consumer roles
- Thread-safe publishing
- Callback-driven consumption

---

## Core Components

### BrokerClient
Primary class responsible for:
- Connection handling
- Channel creation
- Queue declaration
- Publishing messages
- Consuming messages

---

## Class Responsibilities

### BrokerClient

- Initialize broker connection
- Declare queues
- Publish messages
- Register consumer callbacks
- Handle reconnect attempts
- Provide thread-safe publish API

---

## Threading Model

Producer:
- Multiple threads may publish
- Mutex protected publish call

Consumer:
- Broker callback triggers handler
- Handler dispatches to worker thread pool

---

## Error Handling

- Connection failure → retry
- Publish failure → log + retry
- Consumer failure → nack + requeue

---

## Extensibility

Future support:
- Dead letter queues
- Retry queues
- Message priority
- Metrics collection
