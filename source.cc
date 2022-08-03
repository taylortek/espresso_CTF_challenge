#include <iostream>
#include <string.h>
#include <aio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

#define IP "127.0.0.1"
#define PORT 1234


unsigned hash_str(const char* s) {
	unsigned hs = 37;
	while (*s) {
		hs = hs+unsigned(44059)^(s[0]*unsigned(hs));
		s++;
	}
	return hs;
}

int bootServer() {
	int sockr = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in address;
	char password_two[100];
	char flag[50];
	
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	address.sin_addr.s_addr = inet_addr(IP);

	if (connect(sockr, (struct sockaddr *)&address, sizeof(address))<0) {
		cout << "Port 1234 not accepting connections\n";
		return -4;
	} else {
		cout << "Connection was succesful!\n";
	}
	send(sockr, "Password2: ", strlen("Password2: "), 0);
	recv(sockr, password_two, sizeof(password_two), 0);

	strtok(password_two, "\n");
	
	sprintf(flag, "HTB{%s}", password_two);

	if (hash_str(password_two)==1109426749) { //butterfly1
		send(sockr, flag, strlen(flag), 0);
	} else {
		send(sockr, "Incorrect.\n", strlen("Incorrect.\n"), 0);
	}
	return 0;
}

int main() {
	char password[100];
	cout << "Password: ";
	cin >> password;
	
	if (hash_str(password)==1651667741) { //UN10V3D
		cout << "Connecting to server...\n";
		bootServer();
	} else
	{
		cout << "Incorrect.\n";	
	}

	return 0;
}
