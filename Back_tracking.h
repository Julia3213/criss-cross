#pragma once
#include "Field.h"

//сборка схемы кроссворда
//перебор с возвратом
void back_tracking(Field& field) {
	if (field.cur_word < field.words.size()) {
		int s = field.inserted_words.size();
		field.find_letter();

		if (field.reject())
			return;

		if (field.inserted_words.size() == s) {
			if (field.cur_word - 1 == 0)
				return;

			auto it = field.inserted_words.find(field.cur_word - 1);
			field.vector_cell.clear();
			field.vector_cell.resize(it->second.size());
			field.vector_cell = it->second;
			field.delete_word();
			field.inserted_words.erase(field.cur_word - 1);
			swap(field.words[field.cur_word], field.words[field.cur_word - 1]);
			field.cur_word--;
		}

		if (field.inserted_words.size() < field.words.size())
			back_tracking(field);
		else {
			return;
		}
	}
}