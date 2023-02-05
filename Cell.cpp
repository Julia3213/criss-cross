#include "Cell.h"
Cell::Cell() {
	x = -1;
	y = -1;
	value = -1;
	connect_c = 1;
}

Cell::Cell(int x1, int y1, char val) {
	x = x1;
	y = y1;
	value = val;
}

Cell::Cell(const Cell& c) {
	x = c.x;
	y = c.y;
	value = c.value;
	orientation = c.orientation;
	connect_c = c.connect_c;
}