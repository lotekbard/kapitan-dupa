#include <windows.h>
#include <time.h>
#include <math.h>
#include <cstdlib>
#include <MMSystem.h>
#include <fstream>
#define ID_TIMER 1
#if defined(_MSC_VER)
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")
#endif

HWND okno;
RECT rect;
HBRUSH brush;
HPEN pen;
HFONT font;
HDC hdc;
PAINTSTRUCT ps;
LPCWSTR klasa = L"Klasa";
LPCWSTR title = L"Kapitan Dupa by lotek";

wchar_t title2[128];

int width = 640, height = 480;
int punkty = 0;
bool klik = false;
bool gameover = false;
const int a = 32;
const int b = 16;
POINT w[4];
const int offsetx = 4*a;
const int offsety = a;
int sek = 1;
int sek0 = 0;
const int czasgry = 27;

HWND hEdit1, hButton1, hButton2;
HINSTANCE g_hInst;
HBRUSH hbr;

void dupa(){
	if(klik && sek < czasgry){
		Rectangle(hdc, offsetx+a+2*a, offsety+0, offsetx+2*a+2*a, offsety+a);
		Rectangle(hdc, offsetx+0+2*a, offsety+a, offsetx+a+2*a, offsety+2*a);
		Rectangle(hdc, offsetx+2*a+2*a, offsety+a, offsetx+3*a+2*a, offsety+2*a);
		Rectangle(hdc, offsetx+a+2*a, offsety+2*a, offsetx+2*a+2*a, offsety+3*a);
		Rectangle(hdc, offsetx+0+2*a, offsety+3*a, offsetx+4*a+2*a, offsety+4*a);
		Rectangle(hdc, offsetx+0+2*a, offsety+4*a, offsetx+3*a+2*a, offsety+6*a);
		
		w[0].x = offsetx+2*a;
		w[0].y = offsety+6*a;
		w[1].x = offsetx+3*a;
		w[1].y = offsety+6*a;
		w[3].x = offsetx+a;
		w[3].y = offsety+8*a;
		w[2].x = offsetx+2*a;
		w[2].y = offsety+8*a;

		Polygon(hdc, w, 4);

		Rectangle(hdc, offsetx+a, offsety+8*a, offsetx+2*a, offsety+9*a);
		Rectangle(hdc, offsetx+2*a, offsety+8*a, offsetx+3*a, offsety+9*a);
	}else{
		Rectangle(hdc, offsetx+a, offsety+0, offsetx+2*a, offsety+a);
		Rectangle(hdc, offsetx+0, offsety+a, offsetx+a, offsety+2*a);
		Rectangle(hdc, offsetx+2*a, offsety+a, offsetx+3*a, offsety+2*a);
		Rectangle(hdc, offsetx+a, offsety+2*a, offsetx+2*a, offsety+3*a);
		Rectangle(hdc, offsetx+0, offsety+3*a, offsetx+4*a, offsety+4*a);
		Rectangle(hdc, offsetx+0, offsety+4*a, offsetx+3*a, offsety+6*a);
		Rectangle(hdc, offsetx+a, offsety+6*a, offsetx+2*a, offsety+8*a);
		Rectangle(hdc, offsetx+a, offsety+8*a, offsetx+2*a, offsety+9*a);
		Rectangle(hdc, offsetx+2*a, offsety+8*a, offsetx+3*a, offsety+9*a);
	}

	Rectangle(hdc, offsetx+9*a, offsety+4*a, offsetx+10*a, offsety+5*a);
	Rectangle(hdc, offsetx+5*a, offsety+5*a, offsetx+8*a, offsety+6*a);
	Rectangle(hdc, offsetx+8*a, offsety+5*a, offsetx+9*a, offsety+6*a);
	Rectangle(hdc, offsetx+10*a, offsety+5*a, offsetx+11*a, offsety+6*a);
	Rectangle(hdc, offsetx+5*a, offsety+6*a, offsetx+7*a, offsety+7*a);
	Rectangle(hdc, offsetx+7*a, offsety+6*a, offsetx+8*a, offsety+8*a);
	Rectangle(hdc, offsetx+9*a, offsety+6*a, offsetx+10*a, offsety+7*a);
	Rectangle(hdc, offsetx+5*a, offsety+7*a, offsetx+6*a, offsety+8*a);
	Rectangle(hdc, offsetx+4*a, offsety+8*a, offsetx+6*a, offsety+9*a);
	Rectangle(hdc, offsetx+8*a, offsety+8*a, offsetx+9*a, offsety+9*a);
	Rectangle(hdc, offsetx+9*a, offsety+8*a, offsetx+10*a, offsety+9*a);
}

void pofory(){
	pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	brush = CreateSolidBrush(RGB(0,255,0));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	for(int i=0; i<9; i++){
		Ellipse(hdc, b+2*b*i+6*a-12, b+11*a-8, 2*b+2*b*i+6*a-12, (int)(4*b-0.5*b+11*a-8));
		Ellipse(hdc, (int)(0+0.5*b+2*b*i+6*a-12), 3*b+11*a-8, (int)(b+0.5*b+2*b*i+6*a-12), 4*b+11*a-8);
		Ellipse(hdc, (int)(2*b-0.5*b+2*b*i+6*a-12), 3*b+11*a-8, (int)(3*b-0.5*b+2*b*i+6*a-12), 4*b+11*a-8);
	}

	DeleteObject(pen);
	DeleteObject(brush);

	pen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
	brush = CreateSolidBrush(RGB(255,0,0));
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	for(int i=0; i<sek/3; i++){
		Ellipse(hdc, b+2*b*i+6*a-12, b+11*a-8, 2*b+2*b*i+6*a-12, (int)(4*b-0.5*b+11*a-8));
		Ellipse(hdc, (int)(0+0.5*b+2*b*i+6*a-12), 3*b+11*a-8, (int)(b+0.5*b+2*b*i+6*a-12), 4*b+11*a-8);
		Ellipse(hdc, (int)(2*b-0.5*b+2*b*i+6*a-12), 3*b+11*a-8, (int)(3*b-0.5*b+2*b*i+6*a-12), 4*b+11*a-8);
	}

	DeleteObject(pen);
	DeleteObject(brush);
}

LRESULT CALLBACK WndProc(HWND hWnda, UINT uMsg, WPARAM wParam, LPARAM lParam){
	GetClientRect(okno, &rect);
	switch(uMsg){
	case WM_CREATE:
		hbr = CreateSolidBrush(RGB(0,0,0));
		PlaySound(TEXT("rundapierwsza.wav"), NULL, SND_ASYNC);
		SetTimer(hWnda, ID_TIMER, 1000, NULL);
		font = CreateFont(80,0,0,0,FW_SEMIBOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Courier"));
		hEdit1 = CreateWindowA("edit", "", WS_BORDER | WS_CHILD | WS_VISIBLE, 340, 160, 260, 80, hWnda, (HMENU)1, g_hInst, NULL);
		SendMessage(hEdit1, EM_LIMITTEXT, WPARAM(5), 0);
		SendMessage(hEdit1, WM_SETFONT, (WPARAM)font, 0);
		ShowWindow(hEdit1, SW_HIDE);
		font = CreateFont(48,0,0,0,FW_SEMIBOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Courier"));
		hButton1 = CreateWindowA("button", "zapisz", WS_CHILD | WS_VISIBLE, 340, 260, 260, 80, hWnda, (HMENU)2, g_hInst, NULL);
		hButton2 = CreateWindowA("button", "nowa gra", WS_CHILD | WS_VISIBLE, 70, 260, 260, 80, hWnda, (HMENU)3, g_hInst, NULL);
		SendMessage(hButton1, WM_SETFONT, (WPARAM)font, 0);
		SendMessage(hButton2, WM_SETFONT, (WPARAM)font, 0);
		ShowWindow(hButton1, SW_HIDE);
		ShowWindow(hButton2, SW_HIDE);
		break;
	case WM_CTLCOLOREDIT:{
		HDC hdc2=(HDC)wParam;
		SetTextColor(hdc2, RGB(0,255,0));
		SetBkMode(hdc2, TRANSPARENT);
		return (LRESULT)hbr;
	}
	case WM_CTLCOLORBTN:{
		hbr = CreateSolidBrush(RGB(0,0,0));
		return (LRESULT)hbr;
	}
	case WM_COMMAND:
		if((HWND)lParam == hButton1){

		}else if((HWND)lParam == hButton2){
			sek0 = 0;
			sek = 1;
			punkty = 0;
			ShowWindow(hEdit1, SW_HIDE);
			ShowWindow(hButton1, SW_HIDE);
			ShowWindow(hButton2, SW_HIDE);
			PlaySound(TEXT("rundapierwsza.wav"), NULL, SND_ASYNC);
			InvalidateRect(hWnda, NULL, true);
		}
		break;
	case WM_KEYDOWN:
		switch(wParam){
		case VK_RETURN:
			sek = 1;
			punkty = 0;
			InvalidateRect(hWnda, NULL, true);
			break;
		case VK_SPACE:
			if(sek0>6){
				klik = true;
				InvalidateRect(hWnda, NULL, true);
			}
			break;
		}
		break;
	case WM_KEYUP:
		switch(wParam){
		case VK_SPACE:
			if(sek0>6){
				klik = false;
				if(sek<czasgry) punkty+=10;
				InvalidateRect(hWnda, NULL, true);
			}
			break;
		}
		break;
	case WM_TIMER:
		switch(wParam){
		case ID_TIMER:
			sek0++;
			if(sek0>6) sek++;
			if(sek>5 && sek<7) PlaySound(TEXT("dlaczego.wav"), NULL, SND_ASYNC);
			if(sek>11 && sek<13) PlaySound(TEXT("nicnieczuje.wav"), NULL, SND_ASYNC);
			if(sek>17 && sek<19) PlaySound(TEXT("tututu.wav"), NULL, SND_ASYNC);
			if(sek<czasgry+4 || (sek>czasgry+6 && sek<czasgry+8) || (sek>czasgry+9 && sek<czasgry+11)) InvalidateRect(hWnda, NULL, true);
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(okno, &ps);

		SetTextColor(hdc, RGB(0,255,0));
		SetBkMode(hdc, TRANSPARENT);

		if(sek<czasgry+3){
			font = CreateFont(15,0,0,0,FW_SEMIBOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Courier"));
			SelectObject(hdc, font);
			brush = CreateSolidBrush(RGB(0,255,0));
			SelectObject(hdc, brush);
			dupa();
			DeleteObject(brush);

			pen = CreatePen(PS_SOLID, 2, RGB(0,255,0));
			brush = CreateSolidBrush(RGB(0,0,0));
			SelectObject(hdc, pen);
			SelectObject(hdc, brush);

			Rectangle(hdc, a, 11*a, 4*a, 13*a);
			Rectangle(hdc, 5*a, 11*a, 15*a, 13*a);
			Rectangle(hdc, 16*a, 11*a, 19*a, 13*a);

			TextOut(hdc, a+4, 11*a+4, L"SCORE", 5);
			wsprintf(title2, L"%d", punkty);

			if(punkty<100) TextOut(hdc, 2*a+4, 11*a+24, title2, 2);
			else if(punkty<1000) TextOut(hdc, 2*a+4, 11*a+24, title2, 3);
			else TextOut(hdc, 2*a+4, 11*a+24, title2, 4);

			TextOut(hdc, 5*a+4, 11*a+22, L"HIT", 3);
			TextOut(hdc, 16*a+4, 11*a+4, L"SHOT", 4);
			wsprintf(title2, L"%d/sek", punkty/10/sek);
			TextOut(hdc, 17*a+4, 11*a+24, title2, 6);

			DeleteObject(pen);
			DeleteObject(brush);

			pofory();
			DeleteObject(font);
		}else{
			font = CreateFont(80,0,0,0,FW_SEMIBOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH,TEXT("Courier"));
			SelectObject(hdc, font);
			wsprintf(title2, L"SCORE: %d", punkty);

			if(sek<czasgry+5){
				TextOut(hdc, 80, 160, L"GAME OVER!", 10);
				PlaySound(TEXT("gameover.wav"), NULL, SND_ASYNC);
			}else if(sek<czasgry+9){
				TextOut(hdc, 40, 160, title2, 11);
				PlaySound(TEXT("najwyzszywynik.wav"), NULL, SND_ASYNC);
			}else{
				TextOut(hdc, 40, 160, L"LOGIN:", 6);
				PlaySound(TEXT("bravo.wav"), NULL, SND_ASYNC);
				ShowWindow(hEdit1, SW_SHOWNORMAL);
				ShowWindow(hButton1, SW_SHOWNORMAL);
				ShowWindow(hButton2, SW_SHOWNORMAL);
				SetFocus(hEdit1);
			}
			DeleteObject(font);
		}

		DeleteObject(font);

		SaveDC(hdc);
		SelectObject(hdc, NULL);

		EndPaint(okno, &ps);
		break;
	case WM_CLOSE:
		KillTimer(okno, ID_TIMER);
		DestroyWindow(okno);
		break;
	case WM_DESTROY:
		if(hbr) DeleteObject(hbr);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnda, uMsg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){

	WNDCLASS a;
	a.style = CS_HREDRAW | CS_VREDRAW;
	a.lpfnWndProc = WndProc;
	a.cbClsExtra = sizeof(WNDCLASS);
	a.cbWndExtra = sizeof(WNDCLASS);
	a.hInstance = hInstance;
	a.hIcon = LoadIcon(0, IDI_APPLICATION);
	a.hCursor = LoadCursor(0, IDC_ARROW);
	a.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	a.lpszMenuName = 0;
	a.lpszClassName = klasa;

	if(RegisterClass(&a) == NULL){
		MessageBox(0, L"Blad przy rejestrowaniu okna.", L"Blad!", MB_ICONWARNING | MB_OK);
		return 0;
	}

	okno = CreateWindowEx(0, klasa, title, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME, 100, 100, width, height, 0, 0, hInstance, 0);

	ShowWindow(okno, nCmdShow);
	UpdateWindow(okno);

	MSG msg;

	while(GetMessage(&msg, 0, 0, 0) > 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnregisterClass(klasa, hInstance);
	return msg.wParam;
}