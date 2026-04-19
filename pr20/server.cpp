#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main()
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    int opt = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "Ошибка bind" << endl;
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) < 0)
    {
        cerr << "Ошибка listen" << endl;
        close(serverSocket);
        return 1;
    }

    cout << "Сервер запущен, ожидание подключений на порту 8080..." << endl;

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0)
    {
        cerr << "Ошибка accept" << endl;
        close(serverSocket);
        return 1;
    }
    cout << "Клиент подключился." << endl;

    double a, b;
    recv(clientSocket, &a, sizeof(double), 0);
    recv(clientSocket, &b, sizeof(double), 0);

    cout << "Получено: a = " << a << ", b = " << b << endl;

    double sum = a + b;
    send(clientSocket, &sum, sizeof(double), 0);

    cout << "Отправлена сумма: " << sum << endl;

    close(clientSocket);
    close(serverSocket);

    return 0;
}
