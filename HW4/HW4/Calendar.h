#ifndef CALENDAR_H_
#define CALENDAR_H_

#include<iostream>
#include<vector>

class Calendar{
public:
	Calendar();
	Calendar(const Calendar&);

	bool insert(int, int, int, int, int, std::string);

	std::string inttostr(int);

	Calendar operator=(const Calendar);


private:
	bool validYear(int);
	bool validMonth(int);
	bool validDay(int, int);
	bool validLength(int, int);

	std::vector<CalEvent> *events;
	int *times, size, months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
};

class CalEvent{
public:
	CalEvent(int, int, int, int, int, std::string);

	std::string label();
	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getLength();
	std::string getTitle();
	
private:
	int year, month, day, hour, length;
	std::string title;
};

#endif