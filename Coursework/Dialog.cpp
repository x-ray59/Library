// Определение методов класса Dialog
#include "stdafx.h"
#include "Dialog.h"

// Конструктор
Dialog::Dialog()
{
	EndState = 0;
	// Удаление файла с предыдущими данными
	remove("Log.dat");
}

// Деструктор
Dialog::~Dialog()
{
}

// Справка
void Dialog::Get_help()
{
	cout << endl;
	cout << 'a' << "\t" << "Добавить книгу в библиотеку.\n";
	cout << 's' << "\t" << "Вывести информацию о книгах в библиотеке.\n";
	cout << '-' << '\t' << "Пользователь хочет получить книгу.\n";
	cout << '+' << '\t' << "Пользователь хочет вернуть книгу.\n";
	cout << 'r' << "\t" << "Считать данные о книгах из файла.\n";
	cout << 'w' << "\t" << "Сохранить данные о книгах в файле.\n";
	cout << 'q' << "\t" << "Выход.\n";
}

// Получение события односвязного списка
void Dialog::GetEvent(TEvent &event)
{
	// Строка содержит знаки операций
	string menu = "?as-+rwq";
	char code;
	cout << "\n>";
	cin >> code;
	// Является ли символ кодом операции 
	if (menu.find(code) < 8)
	{
		// Присвоение событию статуса непустого
		event.what = evMessage;
		// Поиск введенной операции
		switch (code)
		{
		// Присваивание командам кодов операций
		case '?': event.command = help; break;
		case 'a': event.command = add; break;
		case 's': event.command = show; break;
		case '-': event.command = take; break;
		case '+': event.command = back; break;
		case 'r': event.command = r_file; break;
		case 'w': event.command = w_file; break;
		case 'q': event.command = quit; break;	
		}
	}
	// Присвоение событию статуса пустого
	else
	{
		event.what = evNothing;
		cout << "\nКоманда не найдена! Чтобы увидеть список команд нажмите '?'." << endl;
	}
}

// Главный цикл обработки событий
int Dialog::Execute()
{
	TEvent event;
	do {
		ClearEvent(event);	// Очищаем предыдущее событие
		GetEvent(event);	// Получаем новое событие
		HandleEvent(event); // Обрабатываем полученное событие
	} while (!Valid());		// Проверка на выход
	return EndState;
}

// Проверка выхода из диалога
int Dialog::Valid()
{
	// Если выход, то EndState == 1
	if (EndState == 0) return 0;
	else return 1;
}

// Очистить событие
void Dialog::ClearEvent(TEvent& event)
{
	event.what = evNothing;		// Пустое событие
	event.command = evNothing;	// Пустая команда
	event.a = evNothing;		// Пустой параметр а
}

// Конец выполнения диалога, выход
void Dialog::EndExec() 
{
	EndState = 1;
}

// Обработка полученного события односвязного списка
void Dialog::HandleEvent(TEvent& event)
{
	if (event.what == evMessage) // Проверка на непустое событие
	{
		switch (event.command) // Поиск кода команды
		{
		case help:
			Get_help();
			break;
		case add:
			++*this;
			break;
		case show:
			Show();
			break;
		case take:	
			Take_Back('-');
			break;
		case back:
			Take_Back('+');
			break;
		case r_file:
			Read_file();
			break;
		case w_file:
			Write_file();
			break;
		case quit:
			EndExec();
			break;
		default:
			break;
		};
	};
}