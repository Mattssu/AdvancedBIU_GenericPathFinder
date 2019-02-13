//
// Created by lab on 1/15/19.
//

#include "MyParallelServer.h"

#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <iostream>
#include <thread>


/**
 * Wrap's the call to client handler.
 * @param args The arguments needed.
 * @return
 */
void callHandler(ClientHandler *h, int socket) {
    h->handleClient(socket);
}

void MyParallelServer::open(int port, ClientHandler *clientHandler) {

    int sockfd, newsockfd, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    bool first_client_served = false;

    /**
     * First call to socket() function:
     * AF_INET     - IPv4 (Domain protocol)
     * SOCK_STREAM - TCP (Communication type)
     * 0           - IP (Protocol)
     */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    /* Check of creation succeeded*/
    if (sockfd < 0) {
        perror("Error opening socket.");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t) ((size_t) port));

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Failed to bind server connection.");
        exit(1);
    }

    bool time_out = false;
    /* Now start listening for the clients. */
    while (!time_out) {

        if (first_client_served) {
            timeval timeout;
            timeout.tv_sec = 10;
            timeout.tv_usec = 0;

            setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        }

        listen(sockfd, 5);
        clilen = sizeof(cli_addr);

        /* Accept actual connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

        first_client_served = true;

        if (newsockfd < 0) {
            if (errno == EWOULDBLOCK) {
                cout << "timeout!" << endl;
            }
            time_out = true;
        } else {

            //thread handleClient();
            //handleClient.joinable();
            //handleClient.detach();
            threads.emplace_back(&callHandler, clientHandler, newsockfd);
        }
    }
    /* Free attribute */
    //pthread_attr_destroy(&attr);
    stop();
}


/**
 * Joining all the threads we opened by order and deleting allocated objects.
 */

void MyParallelServer::stop() {
    if (!threads.empty()) {
        auto iterator = this->threads.begin();
        for (; iterator != this->threads.end(); ++iterator) {
            if ((*iterator).joinable()) {
                (*iterator).join();
            }
            //free((*iterator));
        }
        //this->threads->clear();
    }
}

