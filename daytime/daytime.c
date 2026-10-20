#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#define PORT 13
#define BUFFER_SIZE 1024
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Использование: %s \n", argv[0]);
		return 1;
	}
	int sockfd;
	struct sockaddr_in server_addr;
	char buffer[BUFFER_SIZE];
	socklen_t server_len = sizeof(server_addr);
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("Ошибка создания сокета");
		return 1;
	}
	memset(&server_addr, 0, 
sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
	perror("Неверный IP-адрес");
	close(sockfd);
	return 1;
}
const char *empty_msg = "";
sendto(sockfd, empty_msg, strlen(empty_msg), 0,
(const struct sockaddr *)&server_addr, server_len);
	int n = recvfrom(sockfd, buffer, BUFFER_SIZE - 1, 0,
(struct sockaddr *)&server_addr, &server_len);
	if (n < 0) {
		perror("Ошибка приема данных");
	} else {
		buffer[n] = '\0'; // Добавляем нуль-терминатор в конец строки
		printf("Время с сервера: %s", buffer);
	}
	close(sockfd);
	return 0;
}
