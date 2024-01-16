#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0); //ipv4, tcp
    if (sock == -1) {
        std::cerr << "ошибка при создании сокета" << std::endl;
        return 1;
    }

    sockaddr_in serverAddress; // хранение адреса/порта
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7); // порт 
    inet_pton(AF_INET, "82.179.90.12", &serverAddress.sin_addr); // адрес, преобразование в двоичный формат

    int connectResult = connect(sock, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); //соеднение с сервером
    if (connectResult == -1) {
        std::cerr << "соедениться не удалось" << std::endl;
        close(sock); //закрытие сокета
        return 1;
    }

    const char* message = "Hello, world!";
    send(sock, message, strlen(message), 0); //отправление сообщения(длина в байтах)

    char buffer[1024] = {0}; //буфер для хранения полученных данных(инициализация с нулевыми символами)
    recv(sock, buffer, 1024, 0); //прием данных через сокет
    std::cout << "получено: " << buffer << std::endl;

    close(sock);
    return 0;
}