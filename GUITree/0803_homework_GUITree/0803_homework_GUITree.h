#pragma once

#include "resource.h"

// �� �ڵ� ��⿡ ��� �ִ� �Լ��� ������ �����Դϴ�.
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

void Update();
void KeyProcess();
void Draw();