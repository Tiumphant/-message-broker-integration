cmake_minimum_required(VERSION 3.10)
project(MessageBroker)

set(CMAKE_CXX_STANDARD 17)

add_executable(producer src/broker/producer.cpp)
add_executable(consumer src/broker/consumer.cpp)

target_link_libraries(producer rabbitmq)
target_link_libraries(consumer rabbitmq)
