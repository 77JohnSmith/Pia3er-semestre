#include <Windows.h>
#include "resource1.h"
#include <fstream>
#include <Commctrl.h>
#include <CommDlg.h>

using namespace std;

struct fecha
{
	char dia[3];
	char mes[12];
	char ano[5];
};

struct usr
{
	usr* ant;
	int matricula;
	char nombre[30];
	char apPat[20];
	char apMat[20];
	fecha fechaNam;
	char sexo[20];
	char carrera[10];
	char foto[300];
	usr* sig;
};

usr* inicio, * aux, * finlist = nullptr;	
usr* registrar = nullptr;

void registrarusr(usr* nuevo);
void escribirBinario();
void leerBinario();
BOOL CALLBACK vRegistrar(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK vListas(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK vInicio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInstGlobal;
HWND hWndInicioSesion;
HWND hWndRegistar;
HWND hWndListas;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	hInstGlobal = hInstance;
	leerBinario();
	aux = inicio;

	hWndInicioSesion = CreateDialog(hInstance, MAKEINTRESOURCE(1001), NULL, vInicio);

	ShowWindow(hWndInicioSesion, cmdshow);

	MSG Mensaje;

	ZeroMemory(&Mensaje, sizeof(Mensaje));

	while (GetMessage(&Mensaje, 0, 0, 0)) {
		TranslateMessage(&Mensaje);
		DispatchMessage(&Mensaje);
	}

	return Mensaje.wParam;
};

BOOL CALLBACK vInicio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	hWndInicioSesion = hWnd;
	switch (msg) {
	case WM_INITDIALOG:
	{
		DestroyWindow(hWndRegistar);
	}break;
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			case IDD_V1:
		{
			aux = inicio;

			char usuario[30];
				char passw[30];

				if (inicio == nullptr)
				{
					MessageBox(0, "No hay usuarios registrados. Registrese primero. ", "WARNING", MB_OK | MB_ICONWARNING);
				}
				else
				{
					GetDlgItemText(hWnd, 1003, usuario, 30);
					GetDlgItemText(hWnd, 1004, usuario, 30);

					while (aux != nullptr && strcmp(usuario, aux->nombre) != 0)
					{
					
					}

					
				}
				}
		}
	}
	}
}

void registrarusr(usr* nuevo)
{
	if (inicio == nullptr)
	{
		inicio = new usr;
		aux = inicio;
		
		aux->sig = nullptr;
		aux->ant = nullptr;
		
		aux->matricula = nuevo->matricula;
		strcpy(aux->nombre, nuevo->nombre);
		strcpy(aux->apPat, nuevo->apPat);
		strcpy(aux->apMat, nuevo->apMat);
		strcpy(aux->fechaNam.dia, nuevo->fechaNam.dia);
		strcpy(aux->fechaNam.mes, nuevo->fechaNam.mes);
		strcpy(aux->fechaNam.ano, nuevo->fechaNam.ano);
		strcpy(aux->sexo, nuevo->sexo);
		strcpy(aux->carrera, nuevo->carrera);
		strcpy(aux->foto, nuevo->foto);
		
		finlist = aux;
		
	}
	else
	{
		aux = inicio;
		while (aux->sig != nullptr)
		{
			aux = aux->sig;
		}
		aux->sig = new usr;
		aux->sig->sig = nullptr;
		aux->sig->ant = aux;
		aux = aux->sig;
		
		aux->matricula = nuevo->matricula;
		strcpy(aux->nombre, nuevo->nombre);
		strcpy(aux->apPat, nuevo->apPat);
		strcpy(aux->apMat, nuevo->apMat);
		strcpy(aux->fechaNam.dia, nuevo->fechaNam.dia);
		strcpy(aux->fechaNam.mes, nuevo->fechaNam.mes);
		strcpy(aux->fechaNam.ano, nuevo->fechaNam.ano);
		strcpy(aux->sexo, nuevo->sexo);
		strcpy(aux->carrera, nuevo->carrera);
		strcpy(aux->foto, nuevo->foto);
		
		finlist = aux;
		}
}

void escribirBinario()
{
	aux = inicio;

	ofstream escribir;
	escribir.open("binario.bin", ios::out | ios::binary | ios::trunc);
		
		if (escribir.is_open())
		{
			while (aux != nullptr)
			{
				escribir.write((char*)aux, sizeof(usr));
					aux = aux->sig;
			}
			
			escribir.close();
		}
}
void leerBinario()
{
	ifstream escribir;
	escribir.open("binario.bin", ios::in | ios::binary);
	
	aux = inicio;
	if (escribir.is_open())
	{
		usr* leer = new usr;
		while (!escribir.read((char*)leer, sizeof(usr)).eof())
		{
			while (aux != nullptr && aux ->sig != nullptr)
			{
				aux = aux->sig;
			}
			if(aux == nullptr)
			{
				inicio = leer;
				inicio->sig = nullptr;
				aux = inicio;
				finlist = aux;
			}
			else
			{
				aux->sig = leer;
				aux = aux->sig;
				aux->sig = nullptr;
				finlist = aux;
			}
			
			
			leer = new usr;
		}
		escribir.close();
		delete leer;
	}
}