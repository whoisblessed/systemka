#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        cerr << "Ошибка создания сокета" << endl;
        return 1;
    }

    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    if (connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        cerr << "Ошибка подключения к серверу" << endl;
        close(clientSocket);
        return 1;
    }
    cout << "Подключение к серверу установлено." << endl;

    double a, b;
    cout << "Введите первое число: ";
    cin >> a;
    cout << "Введите второе число: ";
    cin >> b;

    send(clientSocket, &a, sizeof(double), 0);
    send(clientSocket, &b, sizeof(double), 0);

    cout << "Числа отправлены серверу: " << a << " и " << b << endl;

    double result;
    recv(clientSocket, &result, sizeof(double), 0);

    cout << "Результат (сумма) от сервера: " << result << endl;

    close(clientSocket);

    return 0;
}
