#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    int c, num;
    char *mensaje;

    printf("Iniciando servidor...\n");

    // Inicializar Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        printf("Error al inicializar Winsock. Código de error: %d\n", WSAGetLastError());
        return 1;
    }

    // Crear socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Error al crear socket. Código de error: %d\n", WSAGetLastError());
        return 1;
    }

    // Configurar estructura del servidor
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);

    // Enlazar socket
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR) {
        printf("Error al enlazar socket. Código de error: %d\n", WSAGetLastError());
        closesocket(s);
        return 1;
    }

    // Escuchar conexiones entrantes
    listen(s, 3);

    printf("Esperando conexiones entrantes...\n");

    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);

    if (new_socket == INVALID_SOCKET) {
        printf("Error al aceptar conexión entrante. Código de error: %d\n", WSAGetLastError());
        closesocket(s);
        return 1;
    }

    printf("Conexión aceptada desde %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

// Leer números del cliente y enviar respuestas
do {
    mensaje = (char*)malloc(50 * sizeof(char));
    recv(new_socket, mensaje, 50, 0);
    num = atoi(mensaje);
    free(mensaje);

    if (num != 0) {
        num++;
        mensaje = (char*)malloc(50 * sizeof(char));
        sprintf(mensaje, "%d", num);
        send(new_socket, mensaje, strlen(mensaje), 0);
        free(mensaje);
    }
} while (num != 0);


    // Cerrar conexión
    closesocket(new_socket);
    WSACleanup();
    printf("Conexión cerrada\n");

    return 0;
}



