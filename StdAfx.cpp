// stdafx.cpp : source file that includes just the standard includes
//	Sceleton.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

extern HINSTANCE hInst;


LRESULT CALLBACK WFunc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hTextHeight, // Текст "Введите свой рост (СМ)" 
				hTextMass, // Текст "Введите свой вес" 
				hEnterHeight, // Поле для ввода роста
				hEnterMass, // Поле для ввода веса
				hBtnRes, hBtnClear, // Кнопка результата и очистки
				hTextRes, // Текст "Результат"
				hViewRes, // Поле результата
				hTextResOut; // Вывод результата текстом

	static HFONT hFontTextHeight, // Создание шрифта тексту с ростом
				 hFontTextMass, // Создание шрифта тексту с весом
				 hFontEnterHeight, // Создание шрифта полю ввода с ростом
			   	 hFontEnterMass, // Создание шрифта полю ввода с весом
				 hFontBtnRes, hFontBtnClear, // Шрифт для кнопки вычисления и очистки
				 hFontTextRes, // Шрифт для "Результат"
				 hFontView, // Шрифт для поля с результатом
				 hFontTextResOut; // Шрифт для вывода результата текстом

	static double userHeight, userMass; // Информация о пользователе
	static double res; // Результат
	
	switch (message)
	{
	case WM_CREATE:
		hTextHeight = CreateWindow("static", "Введите свой рост:", WS_VISIBLE | WS_CHILD, 15, 5, 200, 30, hwnd, 0, hInst, 0);
		hFontTextHeight = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hTextHeight, WM_SETFONT, WPARAM(hFontTextHeight), TRUE);
		hEnterHeight = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 15, 45, 300, 30, hwnd, 0, hInst, 0);
		hFontEnterHeight = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hEnterHeight, WM_SETFONT, WPARAM(hFontEnterHeight), TRUE);
		SetFocus(hEnterHeight);

		hTextMass = CreateWindow("static", "Введите свой вес:", WS_VISIBLE | WS_CHILD, 15, 110, 200, 30, hwnd, 0, hInst, 0);
		hFontTextMass = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hTextMass, WM_SETFONT, WPARAM(hFontTextMass), TRUE);
		hEnterMass = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 15, 150, 300, 30, hwnd, 0, hInst, 0);
		hFontEnterMass = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hEnterMass, WM_SETFONT, WPARAM(hFontEnterMass), TRUE);

		hBtnRes = CreateWindow("button", "Вычислить", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 15, 210, 140, 50, hwnd, 0, hInst, 0);
		hFontBtnRes = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hBtnRes, WM_SETFONT, WPARAM(hFontBtnRes), TRUE);
		hBtnClear = CreateWindow("button", "Очистить", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 175, 210, 140, 50, hwnd, 0, hInst, 0);
		hFontBtnClear = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hBtnClear, WM_SETFONT, WPARAM(hFontBtnClear), TRUE);

		hTextRes = CreateWindow("static", "Реультат:", WS_VISIBLE | WS_CHILD, 15, 300, 100, 30, hwnd, 0, hInst, 0);
		hFontTextRes = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hTextRes, WM_SETFONT, WPARAM(hFontTextRes), TRUE);
		hViewRes = CreateWindow("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 15, 340, 300, 30, hwnd, 0, hInst, 0);
		hFontView = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hViewRes, WM_SETFONT, WPARAM(hFontView), TRUE);

		hTextResOut = CreateWindow("static", "", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 400, 350, 70, hwnd, 0, hInst, 0);
		hFontTextResOut = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "Arial");
		SendMessage(hTextResOut, WM_SETFONT, WPARAM(hFontTextResOut), TRUE);
		break;
	case WM_COMMAND:
		if ((HWND)lParam == hBtnRes)
		{
			SendMessage(hEnterHeight, WM_GETTEXT, 256, (LPARAM)str);
			userHeight = atof(str);
			if (userHeight > 273 || userHeight < 54)
			{
				MessageBox(hwnd, "Людей с таким ростом ещё не было. Пожалуйста введите правильное значение!", "Ошибка!", MB_OK|MB_ICONINFORMATION);
			}
			else
			{
				userHeight /= 100;

				SendMessage(hEnterMass, WM_GETTEXT, 256, (LPARAM)str);
				userMass = atof(str);
				if (userMass <= 0)
				{ 
					MessageBox(hwnd, "Заполните поле с массой!", "Ошибка!", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					res = userMass / (userHeight*userHeight);

					sprintf(str, "%.3lf", res);
					SendMessage(hViewRes, WM_SETTEXT, 256, (LPARAM)str);

					if (res < 18.5)
					{
						SendMessage(hTextResOut, WM_SETTEXT, 256, (LPARAM)(TCHAR*)"Ниже нормального веса!");
					}
					else if (res >= 18.5 && res < 25)
					{
						SendMessage(hTextResOut, WM_SETTEXT, 256, (LPARAM)(TCHAR*)"У вас нормальный вес");
					}
					else if (res >= 25 && res < 30)
					{
						SendMessage(hTextResOut, WM_SETTEXT, 256, (LPARAM)(TCHAR*)"У вас лишний вес");
					}
					else if (res >= 30 && res < 35)
					{
						SendMessage(hTextResOut, WM_SETTEXT, 256, (LPARAM)(TCHAR*)"У вас ожирение!");
					}
					else
					{
						SendMessage(hTextResOut, WM_SETTEXT, 256, (LPARAM)(TCHAR*)"Вы интересный человек ;)");
					}
				}
			}
		}
		if ((HWND)lParam == hBtnClear)
		{
			SendMessage(hEnterHeight, WM_SETTEXT, 0, (LPARAM)(TCHAR*)"");
			SendMessage(hEnterMass, WM_SETTEXT, 0, (LPARAM)(TCHAR*)"");
			SendMessage(hViewRes, WM_SETTEXT, 0, (LPARAM)(TCHAR*)"");
			SendMessage(hTextResOut, WM_SETTEXT, 0, (LPARAM)(TCHAR*)"");

			SetFocus(hEnterHeight);
		}
		break;
	case WM_DESTROY:
			        PostQuitMessage(0); //корректная обработка окончания сообщения
			        break;
	default:
		return
			DefWindowProc(hwnd,message,wParam,lParam);//возврат неотработанного сообщения
	}
	return 0L;
}

