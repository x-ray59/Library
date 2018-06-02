#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include "Error.h"
using namespace std;
// Структура книга
struct Book
{
	Book();
	Book(const int&, char*, char*, const int&, const int&, Book* = nullptr);
	int UDC_num; // Номер УДК
	char FIO[30];	// Ф.И.О. автора
	char name_book[30]; // Название книги
	int publ_date; // Год издания
	int instances; // Количество экземпляров в библиотеке
	Book *next;	// Следующий адрес узла
};

// Класс однонаправленный список
class SL_List
{
public:
	// Конструктор по умолчанию
	SL_List();
	// Деструктор
	~SL_List();
	// Создание списка с книгами
	void Сreate_list(const int&, char*, char*, const int&, const int&);
	// Добавление книги в список
	void operator++();
	// Взять или вернуть книгу
	void Take_Back(const char&);
	// Вывод элементов списка
	void Show();
	// Чтение данных из файла
	void Read_file();
	// Записать данные в файл
	void Write_file();
protected:
	// Первый узел списка
	Book *first;
	// Последний узел списка
	Book *last;
	// Временный хранитель текущего указателя узла. Необходим, чтобы предотвратить изменения
	// first и last в функциях-членах
	Book *temp;
};