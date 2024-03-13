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

	const int MAXSTRLEN = 255;
	WSADATA wsaData;//��������� ��� �������� ����������
	//� ������������� �������
	SOCKET _socket = NULL; //���������� ������
	sockaddr_in addr; //��������� ����� � ����

INT_PTR CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{



	char buf[MAXSTRLEN];
	char str[MAXSTRLEN];
	switch (uMsg)
	{

	case WM_INITDIALOG:
		//������������� �������
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		break;

	case WM_COMMAND:

		if (LOWORD(wParam == IDC_BUTTON1)) { //�������� ���������
			char buffer[1024];
			GetDlgItemTextA(hwnd, IDC_EDIT2, buffer, sizeof(buffer));
			//���������� ��������� �� ��������� �����
			send(_socket, buffer, strlen(buffer), 0);
			

		}

		if (LOWORD(wParam == IDC_BUTTON2)) { //����������� � �������
	
			//������� ��������� �����, �������� TCP
			_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			//��������� ������� IPv4
			addr.sin_family = AF_INET;
			/*����������� ����� � ����������
			��������� �������� �������, ��������� ��������� � ���� sin_addr */
			inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
			//��������� ����. 
			//������� htons ��������� �������������� ����� �
			//������� ������� ����, �.�. ����������� ������� 
			//�������� ������� �� �������� � ��������
			addr.sin_port = htons(20000);
			//��������� ����������� � �������, ��������
            //���������� ������, ����� � ������ ���������
			connect(_socket, (SOCKADDR*)&addr, sizeof(addr));
		


			//��������� ��������� �� �������
	//������� �������� �����������
			int i = recv(_socket, buf, MAXSTRLEN, 0);
			buf[i] = '\0';
			const char* text = "texttt";
			SetDlgItemTextA(hwnd, IDC_EDIT1, buf);
			MessageBoxA(hwnd, buf, "��������� �� �������", MB_OK);

			
		}

		break;







	case WM_CLOSE:
		EndDialog(hwnd, 0);
		//��������� �����
		closesocket(_socket);
		//����������� �������
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