//
// Created by lab on 1/9/19.
//

#include "MySerialServer.h"
#include <thread>
//
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>

#include <sys/socket.h>

//to keep arguments data
struct arg_struct {
    int port;
    ClientHandler *handler;
};

void runServer(int port, ClientHandler *handler, bool *stopRunning) {
    //getting the struct ready
    //struct arg_struct *args = (struct arg_struct *) param;
    //int port = args->port;
    //ClientHandler *handler = args->handler;

    //setting up the server socket
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);
    serv.sin_family = AF_INET;
    if (bind(s, (sockaddr *) &serv, sizeof(serv)) < 0) {
        cerr << "Bad!" << endl;
    }

    int new_sock;
    listen(s, 5);
    struct sockaddr_in client;
    socklen_t clilen = sizeof(client);

    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
    // waits for clients
    while (stopRunning) {
        new_sock = accept(s, (struct sockaddr *) &client, &clilen);
        if (new_sock < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
                exit(2);
            } else {
                perror("other error");
                exit(3);
            }
        }
        //handles the data passage
        cout << "Send to Handler" << endl;
        handler->handleClient(new_sock);
        //test msg
        cout << "handled" << endl;
        close(new_sock);
    }
    close(s);
}

void MySerialServer::open(int port, ClientHandler *ch) {
    //thread
    /* Accept actual connection from the client */
    thread server(&runServer, port, ch, &stopRunning);
    server.detach();
}

