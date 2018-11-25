#include "../../header/handler/NetworkHandler.h"

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

struct IPv4 {

	int b1, b2, b3, b4;

};

bool getMyIP(struct IPv4* myIP) {

	char szBuffer[1024];
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 0);

	if (WSAStartup(wVersionRequested, &wsaData) != 0) {

		return false;

	}

	if (gethostname(szBuffer, sizeof(szBuffer)) == SOCKET_ERROR) {

		WSACleanup();

		return false;

	}

	hostent* host = gethostbyname(szBuffer);

	if (host == NULL) {

		WSACleanup();

		return false;

	}

	in_addr addr;

	for (int i = 0; host->h_addr_list[i] != 0; ++i) {

		memcpy(&addr, host->h_addr_list[i], sizeof(in_addr));

		std::cout << "IPv4 Address: " << inet_ntoa(addr) << std::endl;

	}

	myIP->b1 = (int) addr.S_un.S_un_b.s_b1;
	myIP->b2 = (int) addr.S_un.S_un_b.s_b2;
	myIP->b3 = (int) addr.S_un.S_un_b.s_b3;
	myIP->b4 = (int) addr.S_un.S_un_b.s_b4;

	WSACleanup();

	return true;

}

std::string NetworkHandler::getIP() {

	IPv4 ip;

	if (!getMyIP(&ip)) {

		std::cout << "Theres been an error !" << std::endl;

		return "";

	}

	return std::to_string(ip.b1) + "." + std::to_string(ip.b2) + "." + std::to_string(ip.b3) + "." + std::to_string(ip.b4);

}