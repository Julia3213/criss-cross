#pragma once
#include<iostream>
#include<fstream>
using namespace std;
/*!
* класс Cell для хранения одной клетки в поле
*/
class Cell {
public:
	int x;
	int y;
	int connect_c = 1;
	char value;
	bool orientation;
	Cell();
	Cell(int x1, int y1, char val);
	Cell(const Cell& a);

	Cell& operator=(const Cell& a) {
		x = a.x;
		y = a.y;
		value = a.value;
		orientation = a.orientation;
		connect_c = a.connect_c;
		return *this;
	}

	friend ostream& operator <<(ostream& os, const Cell& c) {
		os << c.value;
		return os;
	}
};