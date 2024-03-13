#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "WinSock2.h" 
#include <ws2tcpip.h> 
#pragma comment(lib, "Ws2_32.lib") 
#include "Windows.h"
#include "tchar.h"
#include "resource.h"
using namespace std;

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	const int MAXSTRLEN = 255;
	WSADATA wsaData;//структура для хранения информацию
	//о инициализации сокетов
	SOCKET _socket = NULL; //дескриптор слушающего сокета
	SOCKET acceptSocket  = NULL;//дескриптор сокета, который связан с клиентом 
	sockaddr_in addr; //локальный адрес и порт

	

	char buf[MAXSTRLEN];

	switch (uMsg)
	{
	case WM_INITDIALOG:
		////инициализация сокетов
		//WSAStartup(MAKEWORD(2, 2), &wsaData);
		break;

	case WM_COMMAND:

		if (LOWORD(wParam == IDC_BUTTON1)) { //запуск сервера
			//инициализация сокетов
			WSAStartup(MAKEWORD(2, 2), &wsaData);
			//создаем потоковый сокет, протокол TCP
			_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			//Семейство адресов IPv4
			addr.sin_family = AF_INET;
			/*Преобразуем адрес в правильную
			структуру хранения адресов, результат сохраняем в поле sin_addr */
			inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
			//Указываем порт. 
			//Функиця htons выполняет преобразование числа в
			//сетевой порядок байт, т.к. стандартным сетевым 
			//является порядок от старшего к младшему
			addr.sin_port = htons(20000);
			//биндим сокет к указанному адресу и порту
			bind(_socket, (SOCKADDR*)&addr, sizeof(addr));
			//открываем сокет в режиме прослушивания входящих подключений
			listen(_socket, 1);
			//ожидаем подключения клиента.
			//в случае успешного подключения - получаем новый сокет
			//через который будет происходить обмен сообщениями
			//с клиентом.
			//Функция является блокирующей.
			acceptSocket = accept(_socket, NULL, NULL);
		


			//Принимаем сообщение от клиента
	//Функция является блокирующей
			int i = recv(_socket, buf, MAXSTRLEN, 0);
			//int i = recv(acceptSocket, buf, MAXSTRLEN, 0);

			buf[i] = '\0';
		/*	SetDlgItemTextA(hwnd, IDC_EDIT1, buf);*/
			//MessageBoxA(hwnd, buf, "Сообщение от сервера", MB_OK);
			SendMessageA(hwnd, EM_SETSEL, -1, -1);

			HWND hEdi1t = GetDlgItem(hwnd, IDC_EDIT1); // Получаем дескриптор элемента управления
			SendMessageA(hEdi1t, EM_REPLACESEL, TRUE, (LPARAM)buf);

		}

		if (LOWORD(wParam == IDC_BUTTON2)) { //отправка сообщения
			char buffer[1024];
			GetDlgItemTextA(hwnd, IDC_EDIT2, buffer, sizeof(buffer));
		

			    //Отправляем сообщение клиенту
				send(acceptSocket, buffer, strlen(buffer), 0);
			//send(_socket, buffer, strlen(buffer), 0);




		}

		break;

	





	case WM_CLOSE:
		EndDialog(hwnd, 0);
		//Закрываем сокеты
		closesocket(_socket);
		closesocket(acceptSocket);
		//Освобождаем ресурсы
		WSACleanup();
		system("pause");
		break;
	
	}
	return FALSE;
}

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DLGPROC(DlgProc));
}