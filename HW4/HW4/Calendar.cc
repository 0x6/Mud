#include"Calendar.h"
#include<sstream>
using namespace std;

Calendar::Calendar(){
	int temp[24];
	times = temp;

	vector<CalEvent> temp2(0);
	events = &temp2;

	for (int i = 0; i < 24; i++)
		times[i] = 0;

	size = 0;
}

Calendar::Calendar(const Calendar& _cal){
	events = _cal.events;
	size = _cal.size;
	times = _cal.times;
}

bool Calendar::insert(int _year, int _month, int _day, int _hour, int _length, string _title){
	bool flag = false;
	string temp;

	if (!validYear(_year)){
		temp = "Input \"" + inttostr(_year) + "\" invalid. Must be greater than or equal to 1900 and less than or equal to 2100.";
		throw temp.c_str();
	}

	if (!validMonth(_month)){
		temp = "Input \"" + inttostr(_month) + "\" invalid. Must be greater than or equal to 1 and less than or equal to 12.";
		throw temp.c_str();
	}

	if (!validDay(_day, _month)){
		temp = "Input \"" + inttostr(_day) + "\" invalid. Must be greater than or equal to 1 and less than or equal to "
			+ inttostr(months[_month]) + " for month " + inttostr(_month) + ".";
		throw temp.c_str();
	}

	if (!validLength(_hour, _length)){
		temp = "Input \"" + inttostr(_length) + "\" invalid. The length of your event cannot extend past midnight.";
		throw temp.c_str();
	}

	(*events).push_back(CalEvent(_year, _month, _day, _hour, _length, _title));
	size++;

	for (int i = _hour; i < _hour + _length; i++){
		if (times[i] == 1)
			flag == true;
		else
			times[i] = 1;
	}
	return flag;
}

bool Calendar::validDay(int _day, int _month){
	if (_day <= months[_month - 1] && _day > 0)
		return true;
	return false;
}

bool Calendar::validYear(int _year){
	if (_year >= 1900 && _year <= 2100)
		return true;
	return false;
}

bool Calendar::validMonth(int _month){
	if (_month <= 12 && _month >= 1)
		return true;
	return false;
}

bool Calendar::validLength(int _hour, int _length){
	if (_hour + _length > 23 || _hour + _length <= 0)
		return false;
	return true;
}

Calendar Calendar::operator=(const Calendar _cal){
	events = _cal.events;
	size = _cal.size;
	times = _cal.times;
}

/*----------------------------------------------------------------------------------------------------------------*/

CalEvent::CalEvent(int _year, int _month, int _day, int _hour, int _length, string _title){
	year = _year;
	month = _month;
	day = _day;
	hour = _hour;
	length = _length;
	title = _title;
}

int CalEvent:: getYear(){
	return year;
}

int CalEvent::getMonth(){
	return month;
}

int CalEvent::getDay(){
	return day;
}

int CalEvent::getHour(){
	return hour;
}

int CalEvent::getLength(){
	return length;
}

string CalEvent::getTitle(){
	return title;
}

/*----------------------------------------------------------------------------------------------------------------*/

string Calendar::inttostr(int _num){
	ostringstream conv;
	conv << _num;
	return conv.str();
}