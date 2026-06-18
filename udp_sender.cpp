#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>

using namespace std;

struct Packet {
    int seqNo;
    char data[1024];
};

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, recvAddr;
    socklen_t addrLen = sizeof(recvAddr);

    Packet pkt;
    int ack;

    string messages[] = {
        "Hello",
        "This is Packet 2",
        "Reliable Transport",
        "END"
    };

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9093);

    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    cout << "Sender started...\n";

    for (int i = 0; i < 4; i++) {

        pkt.seqNo = i;
        strcpy(pkt.data, messages[i].c_str());

        bool ackReceived = false;

        while (!ackReceived) {

            sendto(sockfd,
                   &pkt,
                   sizeof(pkt),
                   0,
                   (struct sockaddr*)&serverAddr,
                   sizeof(serverAddr));

            cout << "\nSent Packet " << pkt.seqNo << endl;

            fd_set readfds;
            FD_ZERO(&readfds);
            FD_SET(sockfd, &readfds);

            struct timeval tv;
            tv.tv_sec = 2;
            tv.tv_usec = 0;

            int rv = select(sockfd + 1,
                            &readfds,
                            NULL,
                            NULL,
                            &tv);

            if (rv > 0) {

                recvfrom(sockfd,
                         &ack,
                         sizeof(ack),
                         0,
                         (struct sockaddr*)&recvAddr,
                         &addrLen);

                if (ack == pkt.seqNo) {

                    cout << "ACK "
                         << ack
                         << " received\n";

                    ackReceived = true;
                }

            } else {

                cout << "Timeout -> Resending Packet "
                     << pkt.seqNo
                     << endl;
            }
        }
    }

    close(sockfd);

    return 0;
}
