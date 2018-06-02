#include "stdafx.h"
#include "SL_List.h"

Book::Book()
	: UDC_num{ 0 }, FIO{ 0 }, name_book{ 0 }, publ_date{ 0 }, instances{ 0 }, next{ nullptr } {}

// Инициализация конструктора с параметрами
Book::Book(const int &a, char *b, char *c, const int &d, const int &e, Book *f)
	: UDC_num{ a }, publ_date{ d }, instances{ e }, next{ f } 
{
	// Копирует побайтно строку b в строку FIO
	strcpy_s(FIO, b);
	strcpy_s(name_book, c);
}

// Конструктор по умолчанию
SL_List::SL_List()
{
}

// Деструктор
SL_List::~SL_List()
{
	// Пока есть следующие узлы
	while (first)
	{
		temp = first->next; // Резервное копирование адреса следующего узла
		delete first;	// Удаление текущего узла
		first = temp;	// Переход на следующий узел
	}
	// Обнуление адреса последнего удаленного узла
	last = nullptr;
}

// Создание списка
void SL_List::Сreate_list(const int &a, char *b, char *c, const int &d, const int &e)
{
	// Двигаемся слева на право
	// Получение указ. адреса текущего добавленного узла
	// (адрес текущего информационного поля, адрес след. узла == 0)
	last = new Book{ a,b,c,d,e };
	if (temp != nullptr) // Если это не первый узел
	{
		temp->next = last; // Присвоить текущему узлу указатель на следующий за ним узел
		temp = temp->next; // Следующий узел становится текущим
	}
	if (first == nullptr) // Если это первый узел, адрес которого == 0
	{
		first = last; // Сохранение указателя первого узла
		temp = first; // Передача адреса первого узла временному хранителю
	}
}

// Добавление элемента в список
void SL_List::operator++()
{
	Book p;
	cout << "\nНомер УДК: "; cin >> p.UDC_num;
	// Получить один символ, чтобы заработал getline
	cin.get();
	cout << "Ф.И.О. автора: "; gets_s(p.FIO);
	cout << "Название книги: "; gets_s(p.name_book);
	cout << "Год издания: "; cin >> p.publ_date;
	cout << "Количество экземпляров в библиотеке: "; cin >> p.instances;
	Сreate_list(p.UDC_num, p.FIO, p.name_book, p.publ_date, p.instances);
}

// Взять или вернуть книгу
void SL_List::Take_Back(const char &code)
{
	if (first) // Работает если список не пустой
	{
		// Вспомогательный указатель
		Book *temp2;
		temp2 = first; // Передача указателя на первое значение списка
		Book p;
		cin.get();
		cout << "\nВведите Ф.И.О. автора книги: "; gets_s(p.FIO);
		cout << "Введите название книги: ";  gets_s(p.name_book);
		// Поиск книги в библиотеке
		while (temp2)
		{
			// Если книга найдена
			if (*p.FIO == *temp2->FIO && *p.name_book == *temp2->name_book)
			{
				// Обработка введенного кода
				switch (code)
				{
				case '-':
					// Если книги еще есть в библитеке
					if (temp2->instances != 0)
					{
						// Уменьшаем количество экземпляров
						--temp2->instances;
						cout << "\nКнига выдана пользователю!\n";
						cout << "Количество экземпляров данной книги: " << temp2->instances << endl;
					}
					else
						throw BookError1();
					break;
				case '+':
				{
					// Увеличиваем количество экземпляров
					++temp2->instances;
					cout << "\nКнига возвращена пользователем!\n";
					cout << "Количество экземпляров данной книги: " << temp2->instances << endl;
				}
					break;
				default:
					break;
				}
				// Выход
				return;
			}
			temp2 = temp2->next; // Переход к следующему узлу
		}
		throw BookError2();
	}
	else
		throw BookError3(); // Если список не имеет узлов
}

// Вывод элементов списка
void SL_List::Show()
{
	if (first) // Выводится если список не пустой
	{
		cout << endl << '|' << setw(10) << "Номер УДК" << '|';
		cout << setw(16) << "Ф.И.О. автора" << '|';
		cout << setw(20) << "Название книги" << '|';
		cout << setw(12) << "Год издания" << '|';
		cout << setw(11) << "Количество" << '|';
		// Вспомогательный указатель
		Book *temp2;
		temp2 = first; // Передача указателя на первое значение списка
		while (temp2)  // Выводится пока есть следующие узлы после first
		{
			cout << endl;
			cout << '|' << setw(10) << temp2->UDC_num << '|';
			cout << setw(16) << temp2->FIO << '|';
			cout << setw(20) << temp2->name_book << '|';
			cout << setw(12) << temp2->publ_date << '|';
			cout << setw(11) << temp2->instances << '|';
			temp2 = temp2->next; // Переход к следующему узлу
		}
		cout << endl;
	}
	else
		throw BookError3(); // Если список не имеет узлов
}

// Чтение данных из файла
void SL_List::Read_file()
{
	// Открываем в бинарном режиме
	ifstream ifs("Data.dat", ios_base::binary); // Поток, открывающий файл для чтения
	if (!ifs)
		throw FileError();
	cout << "\nЧтение данных о книгах из файла!\n";
	// Очистка предыдущего списка, для создания нового
	SL_List::~SL_List();
	// Временные буфер
	Book p;
	// Чтение
	while (ifs.read((char*)&p, sizeof(p)))
		// Создание узла с считанными параметрами
		Сreate_list(p.UDC_num, p.FIO, p.name_book, p.publ_date, p.instances); 
}

// Записать данные в файл
void SL_List::Write_file()
{
	ofstream ofs("Data.dat", ios_base::binary); // Поток, открывающий файл для записи
	cout << "\nЗапись данных о книгах в файл!\n";
	temp = first;
	while (temp)
	{
		// Запись
		ofs.write((char*)temp, sizeof(*temp));
		temp = temp->next; // Переход к следующему узлу
	}
	ofs.close(); // Закрываем поток записи
}