#pragma once
#include <string>
#include <iostream>
using namespace std;

class Error
{
public:
	virtual void what() {};
};

class BookError :public Error
{
protected:
	string msg;
public:
	BookError()
	{ 
		msg = "\ошибка книги: "; 
	}
	virtual void what() 
	{ 
		cout << msg;
	}
};

class BookError1 :public BookError
{
protected:
	string msg_;
public:
	BookError1()
	{ 
		msg_ = "экземпляров данной книги нет.\n"; 
	}
	virtual void what()
	{ 
		cout << msg << msg_; 
	}
};

class BookError2 :public BookError
{
protected:
	string msg_;
public:
	BookError2()
	{
		msg_ = "книга не найдена.\n";
	}
	virtual void what()
	{
		cout << msg << msg_;
	}
};

class BookError3 :public BookError
{
protected:
	string msg_;
public:
	BookError3()
	{
		msg_ = "в библиотеке нет книг.\n";
	}
	virtual void what()
	{
		cout << msg << msg_;
	}
};

class FileError :public Error
{
protected:
	string msg;
public:
	FileError()
	{
		msg = "\ошибка файла: файл для чтения не найден.\n";
	}
	virtual void what()
	{
		cout << msg;
	}
};