#include<iostream>
#include<string>
#include"Calendar.h"
using namespace std;

int main(){

	Calendar owen;
	
	owen.insert(2014, 7, 12, 2, 0, "Chase last b-day");
	cout << owen.insert(2013, 7, 12, 2, 19, "Chase b-day") << endl;

	owen.to_string();

	cout << "\n";

	owen.to_string();

	system("pause");
	return 0;
}