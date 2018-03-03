// 0803_homework_GUITree.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "0803_homework_GUITree.h"
#include "BinarySearchTree.h"
#include "RedBlackTree.h"
#include "AVLTree.h"
#include <time.h>
#include <crtdbg.h>

#define ARRAY_MAX 50

// 전역 변수:
HINSTANCE hInst;								// 현재 인스턴스입니다.
HWND hWnd;

bool arrayFull;
RECT windowRect;

WCHAR inputDeleteNum[1];
BYTE tmpArr[ARRAY_MAX] = { 0, };
RedBlackTree* redBlackTree;
AVLTree* avlTree;
int recentNum = -1;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 	// TODO: 여기에 코드를 입력합니다.
	MSG msg;
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0803_HOMEWORK_GUITREE));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"0803_homework_GUITree";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	RegisterClassEx(&wcex);
	
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	hWnd = CreateWindow(L"0803_homework_GUITree", L"0803_homework_GUITree", WS_OVERLAPPEDWINDOW,
		SCREEN_WIDTH, 600, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	windowRect.top = 0;
	windowRect.left = 0;
	windowRect.right = SCREEN_WIDTH;
	windowRect.bottom = 300;

	AdjustWindowRect(&windowRect, GetWindowStyle(hWnd), GetMenu(hWnd) != NULL);

	MoveWindow(hWnd, (GetSystemMetrics(SM_CXSCREEN) - SCREEN_WIDTH) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - 300) / 2, windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, TRUE);
		
	// 기본 메시지 루프입니다.

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Update();
		}
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	return (int) msg.wParam;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND	- 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT	- 주 창을 그립니다.
//  WM_DESTROY	- 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		srand((unsigned int)time(NULL));
		
		arrayFull = false;
		avlTree = new AVLTree();
		
		/*for (int i = 0; i < 50; i++)
		{
			int randNum = ARRAY_MAX / 2;

			while (tmpArr[randNum] != 0)
			{
				randNum = rand() % ARRAY_MAX;
			}

			tmpArr[randNum] = 1;
			
			avlTree->InsertNode(randNum);
		}

		arrayFull = true;*/

		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 그리기 코드를 추가합니다.
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		delete avlTree;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 다이얼로그 윈도우 프로시저
INT_PTR CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND editBox;

	switch (msg)
	{
	case WM_INITDIALOG:
		editBox = GetDlgItem(hWnd, ID_EDIT);

		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case ID_OK:
			GetDlgItemText(hWnd, ID_EDIT, inputDeleteNum, 16);
			EndDialog(hWnd, 0);

			if (lstrcmp(inputDeleteNum, L"") == 0)
			{
				DialogBox(hInst, MAKEINTRESOURCE(ID_INPUTDELETEKEY), NULL, DialogProc);
			}

			return TRUE;
		default:
			break;
		}
		break;
	default:
		DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}

	return FALSE;
}

void Update()
{
	KeyProcess();

	Draw();

	Sleep(1000 / 60);
}

void KeyProcess()
{
	static int checkArrayNum = 0;

	if (GetAsyncKeyState(0x5A) & 0x8001)		// z키 : 생성
	{
		if (arrayFull)
		{
			return;
		}

		int randNum = ARRAY_MAX / 2;

		while (tmpArr[randNum] != 0)
		{
			randNum = rand() % ARRAY_MAX;
		}
		
		tmpArr[randNum] = 1;
		checkArrayNum++;

		if (checkArrayNum >= ARRAY_MAX)
		{
			arrayFull = true;
		}
		else
		{
			arrayFull = false;
		}

		avlTree->InsertNode(randNum);

		recentNum = randNum;
		
		Sleep(1000 / 5);
	}
	else if (GetAsyncKeyState(0x58) & 0x8001)	// x키 : 삭제
	{
		if (checkArrayNum == 0)
		{
			return;
		}

		/*DialogBox(hInst, MAKEINTRESOURCE(ID_INPUTDELETEKEY), NULL, DialogProc);

		int deleteNum = _wtoi(inputDeleteNum);
		
		avlTree->DeleteNode(deleteNum);
		tmpArr[deleteNum] = 0;
		recentNum = deleteNum;*/

		int randNum = rand() % ARRAY_MAX;

		while (tmpArr[randNum] != 1)
		{
			randNum = rand() % ARRAY_MAX;
		}
		
		avlTree->DeleteNode(randNum);
		tmpArr[randNum] = 0;

		recentNum = randNum;
				
		checkArrayNum--;

		arrayFull = false;

		Sleep(1000 / 5);
	}
	else if (GetAsyncKeyState(0x43) & 0x8001)	// c키 : 전체 삭제
	{
		avlTree->ReleaseTree();

		memset(tmpArr, 0, sizeof(tmpArr));

		arrayFull = false;
		checkArrayNum = 0;

		Sleep(1000 / 5);
	}
}

void Draw()
{
	HDC hdc = GetDC(hWnd), memDC;
	HBITMAP memBitmap, oldMemBitmap;

	memDC = CreateCompatibleDC(hdc);
	memBitmap = CreateCompatibleBitmap(hdc, windowRect.right, windowRect.bottom);
	oldMemBitmap = SelectBitmap(memDC, memBitmap);

	PatBlt(memDC, 0, 0, windowRect.right, windowRect.bottom, WHITENESS);
		
	POINT point = { SCREEN_WIDTH / 2, 0 };

	avlTree->InOrderPrint(hdc, memDC, point);

	WCHAR tmpChar[8] = { 0, };
	wsprintf(tmpChar, L"%2d", recentNum);

	TextOut(memDC, 0, 0, tmpChar, lstrlen(tmpChar));

	BitBlt(hdc, 0, 0, windowRect.right, windowRect.bottom, memDC, 0, 0, SRCCOPY);

	DeleteBitmap(SelectBitmap(memDC, oldMemBitmap));
	ReleaseDC(hWnd, memDC);
	DeleteDC(memDC);

	ReleaseDC(hWnd, hdc);
}