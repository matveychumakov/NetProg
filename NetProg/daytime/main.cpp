#include <iostream>
#include <cstring> // с строки
#include <sys/socket.h> //работа с сокетами
#include <netinet/in.h> // тоже сокеты
#include <arpa/inet.h> // ip адреса и их преобразования
#include <unistd.h> //системные процессы
#include <ctime> // работа с временем и датой 

int main()
{
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); //создание сокета ipv4, upd
    memset(&servaddr, 0, sizeof(servaddr)); //обнуление структуры в нули для избежания ошибок  
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); // порт 
    servaddr.sin_addr.s_addr = inet_addr("82.179.90.12"); // ip адрес
    sendto(sockfd, "", sizeof(""), 0, (struct sockaddr*)&servaddr, sizeof(servaddr)); // отправление данных в структуру
    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL); // получение данных через сокет, запись в буфер
    time_t rawtime;
    struct tm * timeinfo; //указатель на структуру tm
    time ( &rawtime ); //возврат тек. времени 
    timeinfo = localtime ( &rawtime ); //конвертирование времени rawtime в локальное
    std::cout << "текущее время: " << asctime (timeinfo) << std::endl;

    close(sockfd);

    return 0;
}
