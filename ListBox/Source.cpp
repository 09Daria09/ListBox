#include <windows.h>
#include <tchar.h>
#include <windowsX.h>
#include "resource.h"


HWND hDialog, hEdit1, hEdit2, hList1, hList2;
BOOL CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}

void Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hList1 = GetDlgItem(hwnd, IDC_LIST1);
	hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);

	TCHAR str[20];

	for (int i = 0; i < 20; i++)
	{
		int num = (rand() % 20) - 10;
		if (num == 0)
			num += 2;
		wsprintf(str, TEXT("%d"), num);
		SendMessage(hList1, LB_ADDSTRING, 0, LPARAM(str));
	}

	HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));
	// Присоединим меню к главному окну приложения
	SetMenu(hwnd, hMenu);


	return TRUE;
}

void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{

}

BOOL CALLBACK DlgProc(HWND hwnd,  UINT message, WPARAM wParam, LPARAM lParam)
{
	TCHAR str[100];
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
		
	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK)
		{
			int nCount = SendMessage(hList1, LB_GETSELCOUNT, 0, 0);
			// выделим память необходимого размера для хранения индексов выбранных элементов списка
			int* p = new int[nCount];
			// Заполним динамический массив индексами выделенных элементов списка 
			SendMessage(hList1, LB_GETSELITEMS, nCount, LPARAM(p));
			LRESULT result = SendDlgItemMessage(hwnd, IDC_RADIO1, BM_GETCHECK, 0, 0);
			if (result == BST_CHECKED)
			{
				int sum = 0;
				for (int i = 0; i < nCount; i++) {

					SendMessage(hList1, LB_GETTEXT, p[i], LPARAM(str));
					sum += _wtoi(str);
				}
				delete[] p;
				wsprintf(str, TEXT("%d"), sum);
				SendMessage(hEdit1, WM_SETTEXT, 0, LPARAM(str));
			}
			result = SendDlgItemMessage(hwnd, IDC_RADIO2, BM_GETCHECK, 0, 0);
			if (result == BST_CHECKED)
			{
				int sum = 1;
				for (int i = 0; i < nCount; i++) {

					SendMessage(hList1, LB_GETTEXT, p[i], LPARAM(str));
					sum *= _wtoi(str);
				}
				delete[] p;
				wsprintf(str, TEXT("%d"), sum);
				SendMessage(hEdit1, WM_SETTEXT, 0, LPARAM(str));
			}
			result = SendDlgItemMessage(hwnd, IDC_RADIO3, BM_GETCHECK, 0, 0);
			if (result == BST_CHECKED)
			{
				double sum = 0;
				for (int i = 0; i < nCount; i++) {

					SendMessage(hList1, LB_GETTEXT, p[i], LPARAM(str));
					sum += _wtoi(str)/(double)nCount;
				}
				delete[] p;
				_stprintf_s(str, TEXT("%.2f"), sum);
				SendMessage(hEdit1, WM_SETTEXT, 0, LPARAM(str));
			}

		}
	case ID_MENU_EXIT:
		EndDialog(hwnd, 0);
	}
	return FALSE;
}