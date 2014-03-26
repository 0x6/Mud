#ifndef CALENDAR_H_
#define CALENDAR_H_

#include"CalendarBase.h"
#include<iostream>
#include<vector>
#include<string>

class CalEvent{
public:
	CalEvent();
	CalEvent(int, int, int, int, int, std::string);

	std::string label();
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	int getHour() const;
	int getLength() const;
	std::string getTitle() const;

private:
	int year, month, day, hour, length;
	std::string title;
};

class Calendar:CalendarBase{
public:
	Calendar();
	Calendar(const Calendar&);

	bool insert(int year, int mon, int day, int hour, int length, const std::string &title);
	bool insert(const std::string &);
	int size() const;
	void clear();

	vector<CalEvent> getEvents();
	std::string inttostr(int) const;
	int atoi(std::string) const;
	void print();
	
	Calendar operator|=(const Calendar);
	Calendar operator|(const Calendar);
	Calendar operator=(const Calendar);

private:
	void print(std::ostream &) const;
	bool validYear(int);
	bool validMonth(int);
	bool validDay(int, int, int);
	bool validLength(int, int);
	void sort();
	int compare(CalEvent, CalEvent); //returns 0 if the two CalEvents are the same, positive if the first argument is larger, and negative if the second argument is smaller
	

	std::vector<CalEvent> events;
	static const int months[12];
	int elements;
};

#endif