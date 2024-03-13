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
	WSADATA wsaData;//��������� ��� �������� ����������
	//� ������������� �������
	SOCKET _socket = NULL; //���������� ���������� ������
	SOCKET acceptSocket  = NULL;//���������� ������, ������� ������ � �������� 
	sockaddr_in addr; //��������� ����� � ����

	

	char buf[MAXSTRLEN];

	switch (uMsg)
	{
	case WM_INITDIALOG:
		////������������� �������
		//WSAStartup(MAKEWORD(2, 2), &wsaData);
		break;

	case WM_COMMAND:

		if (LOWORD(wParam == IDC_BUTTON1)) { //������ �������
			//������������� �������
			WSAStartup(MAKEWORD(2, 2), &wsaData);
			//������� ��������� �����, �������� TCP
			_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			//��������� ������� IPv4
			addr.sin_family = AF_INET;
			/*����������� ����� � ����������
			��������� �������� �������, ��������� ��������� � ���� sin_addr */
			inet_pton(AF_INET, "0.0.0.0", &addr.sin_addr);
			//��������� ����. 
			//������� htons ��������� �������������� ����� �
			//������� ������� ����, �.�. ����������� ������� 
			//�������� ������� �� �������� � ��������
			addr.sin_port = htons(20000);
			//������ ����� � ���������� ������ � �����
			bind(_socket, (SOCKADDR*)&addr, sizeof(addr));
			//��������� ����� � ������ ������������� �������� �����������
			listen(_socket, 1);
			//������� ����������� �������.
			//� ������ ��������� ����������� - �������� ����� �����
			//����� ������� ����� ����������� ����� �����������
			//� ��������.
			//������� �������� �����������.
			acceptSocket = accept(_socket, NULL, NULL);
		


			//��������� ��������� �� �������
	//������� �������� �����������
			int i = recv(_socket, buf, MAXSTRLEN, 0);
			//int i = recv(acceptSocket, buf, MAXSTRLEN, 0);

			buf[i] = '\0';
		/*	SetDlgItemTextA(hwnd, IDC_EDIT1, buf);*/
			//MessageBoxA(hwnd, buf, "��������� �� �������", MB_OK);
			SendMessageA(hwnd, EM_SETSEL, -1, -1);

			HWND hEdi1t = GetDlgItem(hwnd, IDC_EDIT1); // �������� ���������� �������� ����������
			SendMessageA(hEdi1t, EM_REPLACESEL, TRUE, (LPARAM)buf);

		}

		if (LOWORD(wParam == IDC_BUTTON2)) { //�������� ���������
			char buffer[1024];
			GetDlgItemTextA(hwnd, IDC_EDIT2, buffer, sizeof(buffer));
		

			    //���������� ��������� �������
				send(acceptSocket, buffer, strlen(buffer), 0);
			//send(_socket, buffer, strlen(buffer), 0);




		}

		break;

	





	case WM_CLOSE:
		EndDialog(hwnd, 0);
		//��������� ������
		closesocket(_socket);
		closesocket(acceptSocket);
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