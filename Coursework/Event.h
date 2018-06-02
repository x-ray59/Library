// Описание класса Event (Событие)
#pragma once

constexpr int evNothing = 0;	// Пустое событие
constexpr int evMessage = 100;	// Непустое событие
constexpr int quit = 101;		// Выход 'q'
constexpr int help = 102;		// Вызов описания меню '?'
constexpr int add = 103;		// Добавить книгу в динамическую структуру '+'
constexpr int show = 104;		// Вывести динамическую структуру 's'
constexpr int take = 105;		// Получить книгу в библиотеке '-'
constexpr int back = 106;		// Вернуть книгу в библиотеку '+'
constexpr int r_file = 107;		// Чтение файла 'r'
constexpr int w_file = 108;		// Запись в файл 'w'

// Класс событие
struct TEvent
{
	int what;	// Тип события
	int a;		// Параметр команды
	// union объединяет command и message, то есть они используют одну область памяти.
	// При изменении значения command меняется message, и наоборот
	union
	{
		int command; // Код команды
		int message; // Сообщение
	};
};