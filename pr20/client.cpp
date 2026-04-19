#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cout << "Ошибка подключения!" << endl;
        return 1;
    }

    int numbers[2];
    cout << "Введите первое число: ";
    cin >> numbers[0];
    cout << "Введите второе число: ";
    cin >> numbers[1];

    send(clientSocket, numbers, sizeof(numbers), 0);

    int sum;
    recv(clientSocket, &sum, sizeof(sum), 0);

    cout << "Ответ от сервера (сумма): " << sum << endl;

    close(clientSocket);
    return 0;
}
