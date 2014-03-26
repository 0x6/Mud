#include<iostream>
#include<string>
#include"Calendar.h"
using namespace std;

int main(){

	Calendar owen;
	owen.insert("2014-3-26T10/PT01H Right now");
	owen.insert(2014, 7, 12, 2, 5, "c");
	owen.insert(2014, 7, 12, 2, 5, "b");
	owen.insert(2014, 7, 12, 2, 5, "a");

	owen.print();

	system("pause");
	return 0;
}