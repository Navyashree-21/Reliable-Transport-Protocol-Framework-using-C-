#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

struct Packet {
    int seqNo;
    char data[1024];
};

int main() {

    int sockfd;

    struct sockaddr_in serverAddr,
                        clientAddr;

    socklen_t addrLen =
        sizeof(clientAddr);

    Packet pkt;
    int ack;

    sockfd =
        socket(AF_INET,
               SOCK_DGRAM,
               0);

    if (sockfd < 0) {

        perror("socket");
        return 1;
    }

    memset(&serverAddr,
           0,
           sizeof(serverAddr));

    serverAddr.sin_family =
        AF_INET;

    serverAddr.sin_addr.s_addr =
        inet_addr("127.0.0.1");

    serverAddr.sin_port =
        htons(9093);

    if (bind(sockfd,
             (struct sockaddr*)&serverAddr,
             sizeof(serverAddr)) < 0) {

        perror("bind");
        return 1;
    }

    cout << "Receiver running on "
         << "127.0.0.1:9093\n";

    bool ackLost = false;

    while (true) {

        recvfrom(sockfd,
                 &pkt,
                 sizeof(pkt),
                 0,
                 (struct sockaddr*)&clientAddr,
                 &addrLen);

        cout << "\nPacket received\n";
        cout << "Sequence Number : "
             << pkt.seqNo
             << endl;

        cout << "Data : "
             << pkt.data
             << endl;

        ack = pkt.seqNo;

        if (pkt.seqNo == 1 &&
            !ackLost) {

            cout << "Simulating ACK Loss...\n";

            ackLost = true;

            continue;
        }

        sendto(sockfd,
               &ack,
               sizeof(ack),
               0,
               (struct sockaddr*)&clientAddr,
               addrLen);

        cout << "ACK "
             << ack
             << " sent\n";

        if (strcmp(pkt.data,
                   "END") == 0) {

            cout << "\nTransmission Complete\n";

            break;
        }
    }

    close(sockfd);

    return 0;
}
