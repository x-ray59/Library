/****************************************************/
/********** Динамические структуры данных ***********/
/****************************************************/
#include "stdafx.h"
#include "Dialog.h"
#include <windows.h>
using namespace std;
int main()
try
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);// Установка кодировки в поток ввода (кириллица)
	SetConsoleOutputCP(1251); // Установка кодировки в поток вывода (кириллица)
	// Переход в диалог
	Dialog D;
	D.Execute();
	return 0;
}
// Обработчик ошибок
catch (Error &e)
{
	e.what(); // Переходит на вирт. функции. what, которая соответствует ошибке
	system("pause");
	return 1;
}
