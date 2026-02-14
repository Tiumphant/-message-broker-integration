#include <amqp.h>
#include <amqp_tcp_socket.h>
#include <iostream>

int main() {
    amqp_connection_state_t conn = amqp_new_connection();
    amqp_socket_t* socket = amqp_tcp_socket_new(conn);

    amqp_socket_open(socket, "localhost", 5672);

    amqp_login(conn, "/", 0, 131072, 0,
        AMQP_SASL_METHOD_PLAIN,
        "guest", "guest");

    amqp_channel_open(conn, 1);
    amqp_get_rpc_reply(conn);

    amqp_basic_consume(conn, 1,
        amqp_cstring_bytes("task_queue"),
        amqp_empty_bytes,
        0, 1, 0,
        amqp_empty_table);

    std::cout << "Waiting for messages...\n";

    while (true) {
        amqp_envelope_t envelope;
        amqp_maybe_release_buffers(conn);

        amqp_rpc_reply_t res =
            amqp_consume_message(conn, &envelope, NULL, 0);

        if (res.reply_type == AMQP_RESPONSE_NORMAL) {
            std::string msg(
                (char*)envelope.message.body.bytes,
                envelope.message.body.len);

            std::cout << "Received: " << msg << "\n";

            amqp_destroy_envelope(&envelope);
        }
    }
}
