#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080); 
    serverAddress.sin_addr.s_addr = INADDR_ANY; 

    bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);
    cout << "Сервер запущен. Ожидание клиента" << endl;

    int clientSocket = accept(serverSocket, nullptr, nullptr);
    cout << "Клиент подключен" << endl;

    int numbers[2];
    recv(clientSocket, numbers, sizeof(numbers), 0);
    
    int sum = numbers[0] + numbers[1];
    cout << "Получены числа: " << numbers[0] << " и " << numbers[1] << endl;
    cout << "Сумма: " << sum << ". отправка результата" << endl;

    send(clientSocket, &sum, sizeof(sum), 0);

    close(clientSocket);
    close(serverSocket);
    return 0;
}
