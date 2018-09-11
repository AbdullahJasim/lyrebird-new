//Most networking code is taken from Microsoft's Winsock guide:
//https://docs.microsoft.com/en-us/windows/desktop/winsock/getting-started-with-winsock
#pragma once
#ifndef CLIENT
#define CLIENT

//For some reason including Windows.h first throws several errors
//This is possibly because winsock2.h is included in Windows.h and a double include is generating errors
#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <iostream>

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 512

#pragma comment(lib, "Ws2_32.lib")

class Client {
public:

	//Making this global as it will be used in several functions
	SOCKET ConnectSocket;

	Client();
	int sendData();
	int receiveData();
	int disconnect();
};

#endif