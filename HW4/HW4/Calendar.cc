#include"Calendar.h"
#include<sstream>
using namespace std;

const int Calendar::months[12] = {
	 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

Calendar::Calendar(){
	events = vector<CalEvent> (0);
	elements = 0;
}

Calendar::Calendar(const Calendar& _cal){
	events = _cal.events;
	elements = _cal.elements;
}

bool Calendar::insert(int _year, int _month, int _day, int _hour, int _length, const string &_title){
	bool flag = false;
	string temp;

	if (!validYear(_year)){
		temp = "Input \"" + inttostr(_year) + "\" invalid. Must be greater than or equal to 1900 and less than or equal to 2100.";
		throw temp.c_str();
	}

	if (!validMonth(_month)){
		temp = "Input \"" + inttostr(_month) + "\" invalid. Must be greater than or equal to 1 and less than or equal to 12.";
		throw temp;
	}

	if (!validDay(_day, _month, _year)){
		temp = "Input \"" + inttostr(_day) + "\" invalid. Must be greater than or equal to 1 and less than or equal to "
			+ inttostr(months[_month]) + " for month " + inttostr(_month) + ".";
		throw temp;
	}

	if (!validLength(_hour, _length)){
		temp = "Input \"" + inttostr(_length) + "\" invalid. The length of your event cannot extend past midnight.";
		throw temp;
	}

	CalEvent tempEvent(_year, _month, _day, _hour, _length, _title);

	int tempArr1[24], tempArr2[24];

	for (int i = 0; i < 24; i++){
		tempArr1[i] = 0;
		tempArr2[i] = 0;

		if (i >= tempEvent.getHour() && i < tempEvent.getHour() + tempEvent.getLength()){
			tempArr1[i] = 1;
		}
	}

	for (int k = 0; k < events.size(); k++){
		for (int i = 0; i < 24; i++){
			tempArr2[i] = 0;

			if (i >= events.at(k).getHour() && i < events.at(k).getHour() + events.at(k).getLength()){
				tempArr2[i] = 1;
			}
		}

		for (int i = 0; i < 24; i++){
			if (tempArr1[i] == 1 && tempArr2[i] == 1){
				flag = true;
			}
		}
	}

	events.push_back(tempEvent);
	elements++;
	sort();

	return flag;
}

bool Calendar::insert(const string &_str){
	string temp = _str, token;
	int year, month, day, hour, length;

	token = temp.substr(0, temp.find("-"));
	year = atoi(token);
	temp.erase(0, temp.find("-") + 1);

	token = temp.substr(0, temp.find("-"));
	month = atoi(token);
	temp.erase(0, temp.find("-") + 1);

	token = temp.substr(0, temp.find("T"));
	day = atoi(token);
	temp.erase(0, temp.find("T") + 1);

	token = temp.substr(0, temp.find("/"));
	hour = atoi(token);
	temp.erase(0, temp.find("/") + 3);

	token = temp.substr(0, temp.find("H"));
	length = atoi(token);
	temp.erase(0, temp.find("H") + 2);

	//cout << year << endl << month << endl << day << endl << hour << endl << length << endl << temp << endl;

	return insert(year, month, day, hour, length, temp);
}

int Calendar::size() const{
	return elements;
}

void Calendar::print(){
	string temp;
	for (unsigned int i = 0; i < events.size(); i++){
		temp = inttostr(events.at(i).getYear()) + "-" + inttostr(events.at(i).getMonth()) + "-" + inttostr(events.at(i).getDay()) + "T" + inttostr(events.at(i).getHour())
			+ "/PT" + inttostr(events.at(i).getLength()) + "H " + events.at(i).getTitle() + "\n";
		cout << temp;
	}
}

void Calendar::print(ostream &os) const{
	string temp;
	for (unsigned int i = 0; i < events.size(); i++){
		temp = inttostr(events.at(i).getYear()) + "-" + inttostr(events.at(i).getMonth()) + "-" + inttostr(events.at(i).getDay()) + "T" + inttostr(events.at(i).getHour())
			+ "/PT" + inttostr(events.at(i).getLength()) + "H " + events.at(i).getTitle() + "\n";
		os << temp;
	}
}

void Calendar::sort(){
	int low;

	for (int j = 0; j < events.size(); j++){
		low = j;
		for (int i = j + 1; i < events.size(); i++){
			if ( compare(events[i], events[low]) < 0) //events[i] < events[low]
				low = i;
		}
		CalEvent temp = events[j];
		events[j] = events[low];
		events[low] = temp;
	}
}

//returns 0 if the two CalEvents are the same, positive if the first argument is larger, and negative if the second argument is larger
int Calendar::compare(CalEvent eve1, CalEvent eve2){
	int valList1[4] = { eve1.getYear(), eve1.getMonth(), eve1.getDay(), eve1.getHour() };
	int valList2[4] = { eve2.getYear(), eve2.getMonth(), eve2.getDay(), eve2.getHour() };

	if (valList1[0] == valList2[0] && valList1[1] == valList2[1] && valList1[2] == valList2[2] && valList1[3] == valList2[3]){
		if (eve1.getTitle().compare(eve2.getTitle()) < 0){
			return -1;
		}
		else if (eve1.getTitle().compare(eve2.getTitle()) > 0){
			return 1;
		}
		else {
			return 0;
		}
	}

	for (int i = 0; i < 4; i++){
		if (valList1[i] > valList2[i])
			return 1;
		if (valList1[i] < valList2[i])
			return -1;
	}

	return 0;
}

void Calendar::clear(){
	events.clear();
	elements = 0;
}

bool Calendar::validDay(int _day, int _month, int _year){
	if (_month == 2 && _year % 4 == 0){
		if (_year % 100 == 0 && _year % 400 != 0){
			return false;
		}
	}
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
	if (_hour + _length > 23 || _length < 0)
		return false;
	return true;
}

vector<CalEvent> Calendar::getEvents(){
	return events;
}

Calendar Calendar::operator=(const Calendar _cal){
	events = _cal.events;
	elements = _cal.elements;
	return *this;
}


Calendar Calendar::operator|(const Calendar _cal){
	Calendar tempCal(_cal);
	
}

/*----------------------------------------------------------------------------------------------------------------*/

CalEvent::CalEvent(){

}

CalEvent::CalEvent(int _year, int _month, int _day, int _hour, int _length, string _title){
	year = _year;
	month = _month;
	day = _day;
	hour = _hour;
	length = _length;
	title = _title;
}

int CalEvent::getYear() const{
	return year;
}

int CalEvent::getMonth() const{
	return month;
}

int CalEvent::getDay() const{
	return day;
}

int CalEvent::getHour() const{
	return hour;
}

int CalEvent::getLength() const{
	return length;
}

string CalEvent::getTitle() const{
	return title;
}

/*----------------------------------------------------------------------------------------------------------------*/

string Calendar::inttostr(int _num) const{
	ostringstream conv;
	conv << _num;
	return conv.str();
}

int Calendar::atoi(string str) const{
	int temp;
	istringstream buffer(str);
	buffer >> temp;

	return temp;
}