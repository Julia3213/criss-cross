#include "Back_tracking.h"
int main(int argc, char* argv[]) {
	Field h;
	h.read_words("in2.txt");
	ofstream out("out2.txt");

	h.add_first_word();
	back_tracking(h);

	if (h.inserted_words.size() < h.words.size()) {
		out << "it is impossible to make a grid";
		cout << "it is impossible to make a grid";
	}
	else {
		h.resize();
		out << h;
		//cout << h;
	}
}