#pragma comment(lib, "ws2_32.lib")

#include <cstdio>
#include <iostream>
#include <winsock2.h>
#include <string>

int main()
{

    int res;

    std::string ipAddress = "192.168.123.77";
    int port = 54000;

    WSADATA wsaData;
    res = WSAStartup(MAKEWORD(2, 0), &wsaData);

    if (res == 0)
    {
        std::cout << "WSA done..." << std::endl;
    }
    else
    {
        std::cout << "WSAStartup failed!" << std::endl;
    }

    SOCKET slisten, client;

    slisten = socket(AF_INET, SOCK_STREAM, 0);

    if (slisten != INVALID_SOCKET)
    {
        std::cout << "Socket done..." << std::endl;
    }
    else
    {
        std::cout << "Socket failed!" << std::endl;
    }

    sockaddr_in info;
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    int infolen = sizeof(info);

    res = bind(slisten, (struct sockaddr *)&info, infolen);

    if (slisten != SOCKET_ERROR)
    {
        std::cout << "Bind done..." << std::endl;
    }
    else
    {
        std::cout << "Bind failed!" << std::endl;
    }

    res = listen(slisten, SOMAXCONN);

    if (res != SOCKET_ERROR)
    {
        std::cout << "Listen done..." << std::endl;
    }
    else
    {
        std::cout << "Listen failed!" << std::endl;
    }

    sockaddr_in clientinfo;
    int clientinfolen = sizeof(clientinfo);

    while (1)
    {
        client = accept(slisten, (struct sockaddr *)&clientinfo, &clientinfolen);
        if (client != SOCKET_ERROR)
            std::cout << "Client accepted: " << inet_ntoa(clientinfo.sin_addr) << " on Port: " << ntohs(clientinfo.sin_port) << "..." << std::endl;
        else
            std::cout << "Listen failed!" << std::endl;
    }

    closesocket(client);
    closesocket(slisten);
    WSACleanup();

    return 0;
}
