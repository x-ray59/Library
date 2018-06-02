// Описание класса Dialog (Диалог)
#pragma once
#include "Event.h"
#include "SL_List.h"
class Dialog : 
	// Наследует функции класса одн. списка
	public SL_List
{
public:
	// Конструктор без параметров
	Dialog();
	// Деструктор
	~Dialog();
	// Получить помощь
	void Get_help();
	// Получить событие
	void GetEvent(TEvent&);
	// Главный цикл обработки событий
	int Execute();
	// Обработчик
	void HandleEvent(TEvent&);
	// Очистить событие
	void ClearEvent(TEvent&);
	// Проверка атрибута EndState
	int Valid();
	// Обработка события «конец работы»
	void EndExec();
protected:
	// Конечное состояние (отвечает за выход из диалога или продолжение работы с диалогом)
	int EndState;
};