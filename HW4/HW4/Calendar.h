#ifndef CALENDAR_H_
#define CALENDAR_H_

#include<iostream>
#include<vector>
#include<string>

class CalEvent{
public:
	CalEvent();
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

class Calendar{
public:
	Calendar();
	Calendar(const Calendar&);

	bool insert(int, int, int, int, int, std::string);
	bool insert(std::string str);
	int size();
	void clear();

	std::string inttostr(int);
	
	Calendar operator|=(const Calendar);
	Calendar operator|(const Calendar);
	Calendar operator=(const Calendar);

	void to_string(){
		for (unsigned int i = 0; i < events.size(); i++){
			std::string temp = inttostr(events.at(i).getYear()) + "-" + inttostr(events.at(i).getMonth()) + "-" + inttostr(events.at(i).getDay()) + "T" + inttostr(events.at(i).getHour())
				+ "/PT" + inttostr(events.at(i).getLength()) + "H " + events.at(i).getTitle() + "\n";
			std::cout << temp;
		}
	}

private:
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