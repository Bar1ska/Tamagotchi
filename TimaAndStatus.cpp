#include "TimeAndStatus.h"
#include <fstream>
#include <filesystem>
#include <ctime>
#include <Windows.h>
using namespace std;
atomic<bool> stopFlag{ false };
void TimeAndStatus::start(string pathStateS, string pathTimeS)
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

int TimeAndStatus::readFile()
{
	fstream fileState(pathState, ios::in);
	fileState >> line;
	fileState.close();
	return stoi(line);
};

void TimeAndStatus::writeFile(int state, long timeFile)
{
	fstream fileState(pathState, ios::out);
	fstream fileTime(pathTime, ios::out);
	fileState << state << endl;
	fileTime << timeFile << endl;
	fileState.close();
	fileTime.close();
}

void TimeAndStatus::rewriteFile(int timePeriod, int deduction)
{
	while (!stopFlag.load()) 
	{
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
	}
}

void TimeAndStatus::addition(int deduction)
{
	int state = readFile();
	state += deduction;
	if (state > 100)
	{
		state = 100;
	}
	writeFile(state, time(0));
}