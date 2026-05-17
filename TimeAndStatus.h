#pragma once
#ifndef TIMEANDSTATUS_H
#define TIMEANDSTATUS_H
#include <string>
#include <atomic>
extern std::atomic < bool > stopFlag;
class TimeAndStatus 
{
public:
	void start(std::string pathStateS, std::string pathTimeS);
	int readFile();
	void writeFile(int state, long timeFile);
	void rewriteFile(int timePeriod, int deduction);
	void addition(int deduction);
	void clearFile();
private:
	int state = 100;
	std::string pathState, pathTime, line;
	long timeFile;
};
#endif
