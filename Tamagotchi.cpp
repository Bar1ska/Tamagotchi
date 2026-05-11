#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <filesystem>
#include <ctime>
#include <atomic>
#include <thread>
#include <conio.h>

using namespace std;
atomic < bool > stopFlag = false;
class readFile 
{
public:
	void read(string path) 
	{
		ifstream file(path);
		if (file.is_open()) 
		{
			while (getline(file, line, '\n')) 
			{
				tamagotchi.push_back(line);
			}
		}
		file.close();
	}
	void print() 
	{
		system("CLS");
		for (int i = 0; i < tamagotchi.size(); ++i) 
		{
			cout << tamagotchi[i] << endl;
		}
	}
private:
	string line;
	vector <string> tamagotchi;
};

class TimeAndStatus
{
public:
	void start(string pathStateS, string pathTimeS) 
	{
		pathState = pathStateS;
		pathTime = pathTimeS;
		fstream fileState(pathState, ios::out | ios::in);
		fstream fileTime(pathTime, ios::out | ios::in);
		if (filesystem::file_size(pathState) == 0 && filesystem::file_size(pathTime) == 0) 
		{
			timeFile = time(0);
			fileState << state << endl;
			fileTime << timeFile << endl;
		}
		else 
		{
			fileState >> line;
			state = stoi(line);
			fileTime >> line;
			timeFile = stol(line);
		}
		fileState.close();
		fileTime.close();
	}
	int readFile()
	{
		fstream fileState(pathState, ios::in);
		fileState >> line;
		fileState.close();
		return stoi(line);
	};
	void writeFile(int state, long timeFile)
	{
		fstream fileState(pathState, ios::out);
		fstream fileTime(pathTime, ios::out);
		fileState << state << endl;
		fileTime << timeFile << endl;
		fileState.close();
		fileTime.close();
	}
	void rewriteFile(int timePeriod, int deduction)
	{
		if (stopFlag.load()) 
		{
			return;
		}
		fstream fileTime(pathTime, ios::in);
		if (state != readFile()) 
		{
			state = readFile();
			fileTime >> line;
			timeFile = stol(line);
		}
		if (time(0) - timeFile >= timePeriod * 60)
		{
			state -= deduction;
			if (state < 0) 
			{
				state = 0;
			}
			timeFile = time(0);
			writeFile(state, timeFile);
		}
		fileTime.close();
		Sleep(1000);
		rewriteFile(timePeriod, deduction);
	}
	void addition(int deduction) 
	{
		int state = readFile();
		state += deduction;
		if (state > 100) 
		{
			state = 100;
		}
		writeFile(state, time(0));
	}
private:
	int state = 100;
	string pathState, pathTime, line;
	long timeFile;
};

void button(readFile &obj, TimeAndStatus& obj1) 
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
	readFile eating, crying, idle, lose, playing, sleeping, washing;
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
	thread foodT(&TimeAndStatus::rewriteFile, &food, 1, 10);
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