#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char mensaje[100], respuesta[2000];
    int recv_size;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Error");
        return 1;
    }
    printf("Iniciando cliente\n");

    //Creando socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("No se puede crear socket");
    }
    printf("Socket creado.\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);

    //Conectando al servidor
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
        puts("connect error");
        return 1;
    }

    puts("Conectado");


    while (1) {
        printf("Mensaje a enviar : ");
        fgets(mensaje, 100, stdin);


        if (send(s, mensaje, strlen(mensaje), 0) < 0) {
            puts("Fallo de envio");
            return 1;
        }

        //Recibiendo mensaje del servidor
        if ((recv_size = recv(s, respuesta, 2000, 0)) == SOCKET_ERROR) {
            puts("recv failed");
            break;
        }

        respuesta[recv_size] = '\0';
        printf("Respuesta : %s\n", respuesta);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}

