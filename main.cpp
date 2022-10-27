#pragma comment(lib, "ws2_32.lib")

#include <cstdio>
#include <iostream>
#include <winsock2.h>
#include <string>

class Netrunner
{

    std::string ipAddress;
    int port;
    int role;
    SOCKET selfSocket;
    sockaddr_in targetAddress;
    //sockaddr_in opponentAddress;

public:
    Netrunner(int role = CLIENT, std::string ipAddress = "127.0.0.1", int port = 54000)
    {
        this->ipAddress = ipAddress;
        this->port = port;
        this->role = role;

        this->targetAddress.sin_family = AF_INET;
        this->targetAddress.sin_port = htons(port);
        this->targetAddress.sin_addr.s_addr = inet_addr(this->ipAddress.c_str());
    }

    enum Role
    {
        SERVER,
        CLIENT
    };

    void init()
    {
        wsaStartup();
        createSocket();
        if (this->role == CLIENT)
        {
            connectClient();
        }
        else if (this->role == SERVER)
        {
            bindServer();
        }
    }

    void wsaStartup()
    {
        WSADATA wsaData;

        if (WSAStartup(MAKEWORD(2, 0), &wsaData) == 0)
        {
            std::cout << "WSA done..." << std::endl;
        }
        else
        {
            std::cout << "WSAStartup failed!" << std::endl;
        }
    }

    void createSocket()
    {
        this->selfSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (this->selfSocket != INVALID_SOCKET)
        {
            std::cout << "Socket done..." << std::endl;
        }
        else
        {
            std::cerr << "Socket failed!" << std::endl;
            WSACleanup();
        }
    }

    void connectClient()
    {

        if (connect(this->selfSocket, (sockaddr *)&this->targetAddress, sizeof(this->targetAddress)) != SOCKET_ERROR)
        {
            std::cout << "Connect done..." << std::endl;
        }
        else
        {
            std::cerr << "Connect failed!" << std::endl;
            closesocket(this->selfSocket);
            WSACleanup();
        }
    }

    void bindServer()
    {

        if (bind(this->selfSocket, (struct sockaddr *)&this->targetAddress, sizeof(this->targetAddress)) != SOCKET_ERROR)
        {
            std::cout << "Bind done..." << std::endl;
        }
        else
        {
            std::cout << "Bind failed!" << std::endl;
        }

        if (listen(selfSocket, SOMAXCONN) != SOCKET_ERROR)
        {
            std::cout << "Listen done..." << std::endl;
        }
        else
        {
            std::cout << "Listen failed!" << std::endl;
        }
    }
};

int main(int argc, char *argv[])
{
    Netrunner test = Netrunner(Netrunner::SERVER);
    test.init();
    std::string testS;
    std::cin >> testS;
}