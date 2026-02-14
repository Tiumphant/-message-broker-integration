#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <iostream>

int main() {
    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t *socket = amqp_tcp_socket_new(conn);

    amqp_socket_open(socket, "localhost", 5672);

    amqp_login(conn, "/", 0, 131072, 0,
        AMQP_SASL_METHOD_PLAIN, "guest", "guest");

    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn);

    amqp_basic_publish(conn, 1,
        amqp_cstring_bytes(""),
        amqp_cstring_bytes("task_queue"),
        0, 0, NULL,
        amqp_cstring_bytes("Hello from Producer"));

    std::cout << "Sent\n";

    amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS);
    amqp_connection_close(conn, AMQP_REPLY_SUCCESS);
    amqp_destroy_connection(conn);
}
