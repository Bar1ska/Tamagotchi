#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <conio.h>
#include "Textures.h"
#include "TimeAndStatus.h"
using namespace std;

void button(Textures &obj, TimeAndStatus& obj1) 
{
	obj.print();
	obj1.addition(20);
	Sleep(5000);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("mode con cols=54 lines=50");
	int ind = 0;
	char b;
	string displayedButton [4] = {"Покормить", "Поиграть", "Помыть", "Уложить"};
	string selectedButton[4] = { ">Покормить<", ">Поиграть<", ">Помыть<", ">Уложить<" };
	Textures eating, crying, idle, lose, playing, sleeping, washing;
	TimeAndStatus bath, food, play, sleep;
	eating.read(EATING);
	crying.read(CRYING);
	idle.read(IDLE);
	lose.read(LOSE);
	playing.read(PLAYING);
	sleeping.read(SLEEPING);
	washing.read(WASHING);
	bath.start(STATEBATH, TIMEBATH);
	food.start(STATEFOOD, TIMEFOOD);
	play.start(STATEPLAY, TIMEPLAY);
	sleep.start(STATESLEEP, TIMESLEEP);
	thread bathT(&TimeAndStatus::rewriteFile, &bath, 7, 10);
	bathT.detach();
	thread foodT(&TimeAndStatus::rewriteFile, &food, 3, 10);
	foodT.detach();
	thread playT(&TimeAndStatus::rewriteFile, &play, 5, 10);
	playT.detach();
	thread sleepT(&TimeAndStatus::rewriteFile, &sleep, 10, 10);
	sleepT.detach();
	while (true) 
	{
		system("CLS");
		if (bath.readFile() == 0 || food.readFile() == 0 || play.readFile() == 0 || sleep.readFile() == 0)
		{
			lose.print();
			stopFlag = true;
			return 0;
		}
		if (bath.readFile() <= 20 || food.readFile() <= 20 || play.readFile() <= 20 || sleep.readFile() <= 20)
		{
			crying.print();
			stopFlag = true;
			return 0;
		}
		idle.print();
		cout << endl;
		for (int i = 0; i < 54; ++i)
		{
			cout << "-";
		}
		cout << "Сытость - " << food.readFile() << "\tws - выбор кнопки" << endl;
		cout << "Игривость - " << play.readFile() << "\t enter - нажатие на кнопку" << endl;
		cout << "Чистота - " << bath.readFile() << "\t x - выход из программы" << endl;
		cout << "Бодрость - " << sleep.readFile() << endl << endl;
		for (int i = 0; i < ind; ++i)
		{
			cout << displayedButton[i] << endl;
		}
		cout << selectedButton[ind] << endl;
		for (int i = ind + 1; i < 4; ++i)
		{
			cout << displayedButton[i] << endl;
		}
		b = _getch();
		switch (b)
		{
		case 'w':
			--ind;
			if (ind <= -1)
			{
				ind = 3;
			}
			break;
		case 's':
			++ind;
			if (ind >= 4)
			{
				ind = 0;
			}
			break;
		case '\r':
			switch (ind) 
			{
			case 0:
				button(eating, food);
				break;
			case 1:
				button(playing, play);
				break;
			case 2:
				button(washing, bath);
				break;
			case 3:
				button(sleeping, sleep);
				break;
			}
			break;
		case 'x':
			stopFlag = true;
			return 0;
		}
	}
}