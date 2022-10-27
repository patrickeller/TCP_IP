#include <iostream>
#include <string>
#include <winsock2.h>

int main()
{
    std::string ipAddress = "192.168.123.77"; // IP Address of the server
    int port = 54000;                         // Listening port # on the server

    // Initialize WinSock
    WSAData wsaData;
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res == 0)
    {
        std::cout << "WSA done..." << std::endl;
    }
    else
    {
        std::cerr << "WSA failed!" << std::endl;
        return -1;
    }

    // Create socket
    SOCKET clientConnect = socket(AF_INET, SOCK_STREAM, 0);
    if (clientConnect != INVALID_SOCKET)
    {
        std::cout << "Socket done..." << std::endl;
    }
    else
    {
        std::cerr << "Socket failed!" << std::endl;
        WSACleanup();
        return -1;
    }

    // Fill in a hint structure
    sockaddr_in info;
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = inet_addr(ipAddress.c_str());

    // Connect to server
    int server = connect(clientConnect, (sockaddr *)&info, sizeof(info));

    if (server != SOCKET_ERROR)
    {
        std::cout << "Connect done..." << std::endl;
    }
    else
    {
        std::cerr << "Connect failed!" << std::endl;
        closesocket(clientConnect);
        WSACleanup();
        return -1;
    }

    // Do-while loop to send and receive data
    char buf[4096];
    std::string userInput;

    do
    {
        // Prompt the user for some text
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if (userInput.size() > 0) // Make sure the user has typed in something
        {
            // Send the text
            int sendResult = send(clientConnect, userInput.c_str(), userInput.size() + 1, 0);
            if (sendResult != SOCKET_ERROR)
            {
                // Wait for response
                ZeroMemory(buf, 4096);
                int bytesReceived = recv(clientConnect, buf, 4096, 0);
                if (bytesReceived > 0)
                {
                    // Echo response to console
                    std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
                }
            }
        }

    } while (userInput.size() > 0);

    // Gracefully close down everything
    closesocket(clientConnect);
    WSACleanup();

    return 0;
}
