#include <stdio.h>
#include <sys/socket.h>
#include <sys/fcntl.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int main()
{
    char buf[256];
    struct sockaddr_in serv_addr;
    int error;
    int keepalive = 1;
    int timeout = 2000; // 2 sec

    int s;
    int fileflags;
    s = socket(AF_INET, SOCK_STREAM, 0);

    if(!fileflags == fcntl(s, F_GETFL))
    {
        perror("fcntl F_GETFL");
        exit(1);
    }

    // fail if -1
    // fcntl(s, F_SETFL, fileflags | FNDELAY | FASYNC);

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(8081);

    setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, (char*)&keepalive, sizeof(keepalive));
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));

    error = connect(s, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    fprintf(stderr, "error connect: %d\n", error);


    char send[] = "ping";
    uint16_t len = strlen(send);
    len = htons(len);
    write(s, &len, 2);
    write(s, &send, len);
    // error = write(s, send, strlen(send));
    // fprintf(stderr, "error send: %d\n", error);
    for (int i = 0; i < 1; ++i)
    {
        fprintf(stderr, "-----------------------------------------------\n");
        error = read(s, buf, 256);
        for (int j = 0; j < error; ++j)
        {
            fprintf(stderr, "%c", buf[j]);
        }
        bzero(buf, 256);
        write(s, (char*)strlen(send), 4);
        error = write(s, send, strlen(send));
        fprintf(stderr, "\n");
    }
    close(s);
    return 0;
}
