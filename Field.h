#pragma once
#include "Cell.h"
#include<vector>
#include<map>
#define FIELD_SIZE 160
/*!
* класс Field для хранения поля кроссворда
*/
class Field {
public:
	Cell** field;
	int sizeX = FIELD_SIZE;
	int sizeY = FIELD_SIZE;
	vector<Cell> vector_cell;
	vector<string> words;
	map<int, vector<Cell>> inserted_words;
	Cell cell;
	int connect = 0;
	int square;
	float coupling;
	vector<int> connect_v;
	int cur_word;
	int tmp_let2;
	int incr = 2;
	bool is_access = true;

	Field();
	Field(const Field& f);
	char find_val(int x1, int y1);
	void read_words(const char* fname);
	void set_access();
	void add_first_word();
	bool is_delete_access(int x, int y);
	void delete_word();
	void insertw(Cell a);
	void is_access_func(int x, int y, int k);
	void is_zero(int x, int y);
	void find_letter();
	void shift(int i);
	bool reject();
	void resize();

	friend ostream& operator<<(ostream& os, const Field& f) {
		for (int i = 0; i < f.sizeX; i++) {
			for (int j = 0; j < f.sizeY; j++) {
				if ((f.field[i][j].value == '0') || (f.field[i][j].value == '1'))
					os << " ";
				else
					os << f.field[i][j];
			}
			os << endl;
		}
		return os;
	}

};