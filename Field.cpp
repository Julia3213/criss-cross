#include"Field.h"
#include<fstream>

Field::Field() {
	field = new Cell * [FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++) {
		field[i] = new Cell[FIELD_SIZE];
	}
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			field[i][j].value = '0';
			field[i][j].x = i;
			field[i][j].y = j;
		}
	}
	square = 0;
}

Field::Field(const Field& field1) {
	field = new Cell * [FIELD_SIZE];
	for (int i = 0; i < FIELD_SIZE; i++) {
		field[i] = new Cell[FIELD_SIZE];
	}
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			field[i][j].value = field1.field[i][j].value;
			field[i][j].x = field1.field[i][j].x;
			field[i][j].y = field1.field[i][j].y;
		}
	}
	vector_cell.resize(field1.vector_cell.size());
	vector_cell = field1.vector_cell;
	words.resize(field1.words.size());
	words = field1.words;
	cur_word = field1.cur_word;
	square = field1.square;
}

char Field::find_val(int x1, int y1) {
	bool a = 0;
	char g = '-1';
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			if ((field[i][j].x == x1) && (field[i][j].y == y1)) {
				g = field[i][j].value;
				break;
			}
		}
	}
	return g;
}

void Field::read_words(const char* fname) {
	ifstream in(fname);
	string s;
	while (!in.eof()) {
		in >> s;
		words.push_back(s);
	}
	vector<string> temp_vector;
	temp_vector.resize(words.size());
	int min = words.front().size();
	int max = words.front().size();
	for (int i = 0; i < words.size(); i++) {
		if (words[i].size() < min)
			min = words[i].size();
		if (words[i].size() > max)
			max = words[i].size();
	}
	int k = 0;
	for (int j = min; j < max + 1; j++) {
		for (int i = 0; i < words.size(); i++) {
			if (words[i].size() == j) {
				temp_vector[k] = words[i];
				k++;
			}
		}
	}
	words.clear();
	words.resize(temp_vector.size());
	for (int i = 0, j = temp_vector.size() - 1; i < temp_vector.size(), j >= 0; i++, j--) {
		words[j] = temp_vector[i];
	}
	connect_v.resize(words.size());
}

void Field::set_access() {
	for (vector<Cell>::iterator it = vector_cell.begin(); it != vector_cell.end(); ++it) {
		if ((find_val((*it).x - 1, (*it).y - 1) != '0') && (find_val((*it).x - 1, (*it).y - 1) != '1')) {

			if ((find_val((*it).x - 1, (*it).y) != '0') && (find_val((*it).x - 1, (*it).y) != '1'))
				field[(*it).x][(*it).y - 1].value = '1';

			if ((find_val((*it).x, (*it).y - 1) != '0') && (find_val((*it).x, (*it).y - 1) != '1'))
				field[(*it).x - 1][(*it).y].value = '1';
		}
		if ((find_val((*it).x + 1, (*it).y + 1) != '0') && (find_val((*it).x + 1, (*it).y + 1) != '1')) {

			if ((find_val((*it).x, (*it).y + 1) != '0') && (find_val((*it).x, (*it).y + 1) != '1'))
				field[(*it).x + 1][(*it).y].value = '1';

			if ((find_val((*it).x + 1, (*it).y) != '0') && (find_val((*it).x + 1, (*it).y) != '1'))
				field[(*it).x][(*it).y + 1].value = '1';

		}
		if ((find_val((*it).x + 1, (*it).y - 1) != '0') && (find_val((*it).x + 1, (*it).y - 1) != '1')) {

			if ((find_val((*it).x, (*it).y - 1) != '0') && (find_val((*it).x, (*it).y - 1) != '1'))
				field[(*it).x + 1][(*it).y].value = '1';

			if ((find_val((*it).x + 1, (*it).y) != '0') && (find_val((*it).x + 1, (*it).y) != '1'))
				field[(*it).x][(*it).y - 1].value = '1';

		}
		if ((find_val((*it).x - 1, (*it).y + 1) != '0') && (find_val((*it).x - 1, (*it).y + 1) != '1')) {

			if ((find_val((*it).x - 1, (*it).y) != '0') && (find_val((*it).x - 1, (*it).y) != '1'))
				field[(*it).x][(*it).y + 1].value = '1';

			if ((find_val((*it).x, (*it).y + 1) != '0') && (find_val((*it).x, (*it).y + 1) != '1'))
				field[(*it).x - 1][(*it).y].value = '1';

		}
	}
}

void Field::add_first_word() {
	int size_of_word = words[0].size();
	int middle_x = FIELD_SIZE / 2;
	int middle_y = FIELD_SIZE / 2;
	int i = 0;
	field[middle_x][middle_y - size_of_word / 2 - 2].value = '1';
	field[middle_x][middle_y - size_of_word / 2 - 1].connect_c = 1;
	for (i = 0; i < size_of_word; i++) {
		field[middle_x][middle_y - size_of_word / 2 - 1 + i].value = words[0][i];
		field[middle_x][middle_y - size_of_word / 2 - 1 + i].x = middle_x;
		field[middle_x][middle_y - size_of_word / 2 - 1 + i].y = middle_y - size_of_word / 2 - 1 + i;
		field[middle_x][middle_y - size_of_word / 2 - 1 + i].orientation = 0;
		vector_cell.push_back(field[middle_x][middle_y - size_of_word / 2 - 1 + i]);
		square++;
	}
	inserted_words.insert(make_pair(0, vector_cell));
	field[middle_x][middle_y - size_of_word / 2 - 1 + i].value = '1';
	cur_word = 1;
	connect_v.push_back(0);
}

bool Field::is_delete_access(int x, int y) {
	int flag = 0;
	if (((field[x - 1][y].value == '0') || (field[x - 1][y].value == '1')) || ((field[x][y + 1].value == '0') || (field[x][y + 1].value == '1')))
		flag = 1;
	else return false;
	if (((field[x][y + 1].value == '0') || (field[x][y + 1].value == '1')) || ((field[x + 1][y].value == '0') || (field[x + 1][y].value == '1')))
		flag = 1;
	else return false;
	if (((field[x + 1][y].value == '0') || (field[x + 1][y].value == '1')) || ((field[x][y - 1].value == '0') || (field[x][y - 1].value == '1')))
		flag = 1;
	else return false;
	if (((field[x][y - 1].value == '0') || (field[x][y - 1].value == '1')) || ((field[x - 1][y].value == '0') || (field[x - 1][y].value == '1')))
		flag = 1;
	else return false;
	return true;
}

void Field::delete_word() {
	bool orientation;
	connect--;
	if (connect_v.size() != 0) {
		connect_v.pop_back();
	}
	for (auto it = vector_cell.begin(); it != vector_cell.end(); ++it) {
		if ((*it).connect_c != 2) {
			field[(*it).x][(*it).y].value = '0';
			field[(*it).x][(*it).y].x = -1;
			field[(*it).x][(*it).y].y = -1;
			square--;
		}
	}
	coupling = (float)connect / (float)square;
	for (auto it = vector_cell.begin(); it != vector_cell.end(); ++it) {
		orientation = (*it).orientation;
		if (field[(*it).x + 1][(*it).y + 1].value == '1') {
			if (is_delete_access((*it).x + 1, (*it).y + 1)) {
				field[(*it).x + 1][(*it).y + 1].value = '0';
			}
		}
		if (field[(*it).x + 1][(*it).y - 1].value == '1') {
			if (is_delete_access((*it).x + 1, (*it).y - 1)) {
				field[(*it).x + 1][(*it).y - 1].value = '0';
			}
		}
		if (field[(*it).x - 1][(*it).y + 1].value == '1') {
			if (is_delete_access((*it).x - 1, (*it).y + 1)) {
				field[(*it).x - 1][(*it).y + 1].value = '0';
			}
		}
		if (field[(*it).x - 1][(*it).y - 1].value == '1') {
			if (is_delete_access((*it).x - 1, (*it).y - 1)) {
				field[(*it).x - 1][(*it).y - 1].value = '0';
			}
		}
		if (orientation == 0) {
			if (field[(*it).x][(*it).y + 1].value == '1')
				field[(*it).x][(*it).y + 1].value = '0';
			if (field[(*it).x][(*it).y - 1].value == '1')
				field[(*it).x][(*it).y - 1].value = '0';
		}
		if (orientation == 1) {
			if (field[(*it).x + 1][(*it).y].value == '1')
				field[(*it).x + 1][(*it).y].value = '0';
			if (field[(*it).x - 1][(*it).y].value == '1')
				field[(*it).x - 1][(*it).y].value = '0';
		}
	}
	int s = words[cur_word - 1].size();
	auto it = inserted_words.find(cur_word - 2);
	vector_cell.resize(it->second.size());
	vector_cell = it->second;
}

void Field::insertw(Cell a) {
	incr = 2;
	int i, j;
	int size_of_word = words[cur_word].size();
	field[a.x][a.y].connect_c = 2;
	vector_cell.clear();

	if (a.orientation == 1) {

		for (i = tmp_let2, j = 0; i < size_of_word, j < size_of_word - tmp_let2; i++, j++) {
			if (field[a.x + j][a.y].value == '0') {
				square++;
			}
			field[a.x][a.y].connect_c = 2;
			field[a.x + j][a.y].value = words[cur_word][i];
			field[a.x + j][a.y].x = a.x + j;
			field[a.x + j][a.y].y = a.y;
			field[a.x + j][a.y].orientation = 1;
			vector_cell.push_back(field[a.x + j][a.y]);
		}

		field[a.x + j][a.y].value = '1';

		for (i = tmp_let2 - 1, j = 1; i >= 0, j <= tmp_let2; i--, j++) {
			if (field[a.x - j][a.y].value == '0')
				square++;
			field[a.x - j][a.y].value = words[cur_word][i];
			field[a.x - j][a.y].x = a.x - j;
			field[a.x - j][a.y].y = a.y;
			field[a.x - j][a.y].orientation = 1;
			vector_cell.push_back(field[a.x - j][a.y]);
		}

		inserted_words.insert(make_pair(cur_word, vector_cell));
		field[a.x - j][a.y].value = '1';
		set_access();
		cur_word++;
	}

	if (a.orientation == 0) {

		vector_cell.clear();
		int size_of_word = words[cur_word].size();
		field[a.x][a.y].connect_c = 2;

		for (i = tmp_let2, j = 0; i < size_of_word, j < size_of_word - tmp_let2; i++, j++) {
			if (field[a.x][a.y + j].value == '0')
				square++;
			field[a.x][a.y + j].value = words[cur_word][i];
			field[a.x][a.y + j].x = a.x;
			field[a.x][a.y + j].y = a.y + j;
			field[a.x][a.y + j].orientation = 0;
			vector_cell.push_back(field[a.x][a.y + j]);
		}

		field[a.x][a.y + j].value = '1';

		for (i = tmp_let2 - 1, j = 1; i >= 0, j <= tmp_let2; i--, j++) {
			if (field[a.x][a.y - j].value == '0')
				square++;
			field[a.x][a.y - j].value = words[cur_word][i];
			field[a.x][a.y - j].x = a.x;
			field[a.x][a.y - j].y = a.y - j;
			field[a.x][a.y - j].orientation = 0;
			vector_cell.push_back(field[a.x][a.y - j]);
		}

		inserted_words.insert(make_pair(cur_word, vector_cell));
		field[a.x][a.y - j].value = '1';
		set_access();
		cur_word++;
	}
	coupling = (float)connect / (float)square;
	connect_v.push_back(coupling);
}

void Field::is_access_func(int x, int y, int k) {
	if ((field[x][y].value == '1') || ((field[x][y].value != '0') && (field[x][y].value != words[cur_word][k]))) {
		is_access = false;
	}
}

void Field::is_zero(int x, int y) {
	if (field[x][y].value != '0')
		is_access = false;
}

void Field::find_letter() {// будем обращаться к x y or value клетки
	int i, j, k;
	int size_of_word = words[cur_word].size();

	for (vector<Cell>::iterator it = vector_cell.begin(); it != vector_cell.end(); ++it) {
		for (i = 0; i < words[cur_word].size(); i++) {
			is_access = true;
			if ((*it).value == words[cur_word][i]) {
				cell.connect_c = 2;
				cell.value = (*it).value;
				cell.x = (*it).x;
				cell.y = (*it).y;
				cell.orientation = !((*it).orientation);
				tmp_let2 = i;
				if ((*it).orientation == 0) {
					for (j = 0, k = tmp_let2; j < size_of_word - tmp_let2, k < size_of_word; j++, k++) {
						is_access_func(cell.x + j, cell.y, k);
					}
					is_zero(cell.x + size_of_word - i, cell.y);
					for (j = 1, k = tmp_let2 - 1; j <= tmp_let2, k >= 0; j++, k--) {
						is_access_func(cell.x - j, cell.y, k);
					}
					is_zero(cell.x - tmp_let2 - 1, cell.y);
				}
				else if ((*it).orientation == 1) {
					for (j = 0, k = tmp_let2; j < size_of_word - tmp_let2, k < size_of_word; j++, k++) {
						is_access_func(cell.x, cell.y + j, k);
					}
					is_zero(cell.x, cell.y + size_of_word - tmp_let2);
					for (j = 1, k = tmp_let2 - 1; j <= tmp_let2, k >= 0; j++, k--) {
						is_access_func(cell.x, cell.y - j, k);
					}
					is_zero(cell.x, cell.y - tmp_let2 - 1);
				}
				if (is_access == true) {
					connect++;
					cell.connect_c = 2;
					//unused_w.erase(unused_w.begin()+cur_w);
					insertw(cell);
					return;
				}
			}
		}
	}

	auto it = inserted_words.find(cur_word - incr);
	if (it != inserted_words.end()) {
		vector_cell.clear();
		vector_cell.resize(it->second.size());
		vector_cell = it->second;
		incr++;
		find_letter();
	}
	incr = 2;
}

void Field::shift(int i) {
	int j;
	for (j = i; j < words.size() - 1; j++) {
		swap(words[j], words[j + 1]);
	}
}

bool Field::reject() {
	if (connect_v.size() == 0)
		return false;
	if (connect_v[cur_word - 1] > connect_v[cur_word])
		return true;
	else
		return false;
}

void Field::resize() {
	int minX = FIELD_SIZE;
	int maxX = 0;
	int minY = FIELD_SIZE;
	int maxY = 0;
	for (int i = 0; i < FIELD_SIZE; i++) {
		for (int j = 0; j < FIELD_SIZE; j++) {
			if (field[i][j].value != '1' && field[i][j].value != '0') {
				if (field[i][j].x > maxX)
					maxX = field[i][j].x;
				if (field[i][j].x < minX)
					minX = field[i][j].x;
				if (field[i][j].y > maxY)
					maxY = field[i][j].y;
				if (field[i][j].y < minY)
					minY = field[i][j].y;
			}
		}
	}
	sizeX = maxX - minX+1;
	sizeY = maxY - minY+1;

	Cell** temp = new Cell*[sizeX];
	for (int i = 0; i < sizeX; i++) {
		temp[i] = new Cell[sizeY];
	}
	for (int i = 0; i < sizeX; i++) {
		for (int j = 0; j < sizeY; j++) {
			temp[i][j].x = i;
			temp[i][j].y = j;
		}
	}
	int ii=0, jj = 0;
	for (int i = minX; i <= maxX; i++) {
		for (int j = minY; j <= maxY; j++) {
			temp[ii][jj].value = field[i][j].value;
			jj++;
		}
		jj = 0;
		ii++;
	}

	field = temp;
}