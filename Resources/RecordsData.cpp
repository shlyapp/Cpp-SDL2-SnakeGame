#include <fstream>
#include <algorithm>

#include "Game.h"

RecordsData::RecordsData() {
	// При создании загружаем данные
	load();
}

void RecordsData::load() {
	records.clear();

	// Открываем файл на чтение
	std::ifstream file("records.txt");
	// Значение из файла
	int value;

	// Пока файл на закончился
	while (!file.eof()) {
		// Получаем значение рекорда из файла
		file >> value;
		// Добавляем его
		records.push_back(value);
	}

	// Файл закрываем
	file.close();
}

void RecordsData::save() {
	// Открываем файл на запись, очистив его
	std::fstream file("records.txt", std::ios::out);
	
	// Пробегаем по количеству рекордов
	for (int i = 0; i < records.size(); i++) {
		// Записываем рекорд в файл
		file << records[i];
		if (i != records.size() - 1) {
			file << std::endl;
		}
	}

	// Закрываем файд 
	file.close();
}

void RecordsData::add_record(int value) {
	records.push_back(value);
	// Сохраняем добавленный файл
	save();
}

std::vector<int> RecordsData::get_best_records(int number) {
	load();
	std::vector<int> output;

	// Сортируем по возрастанию рекорды
	std::sort(records.begin(), records.end());
	// Переворчаиваем, получая сортировку по убыванию
	std::reverse(records.begin(), records.end());

	// Получаем лучшие рекорды
	for (int i = 0; i < number; i++)
	{
		// Если количество запрашиваемых рекордов больше, чем всех рекордов
		if (i > records.size() - 1) {
			// Добавляем единицу
			output.push_back(0);
			continue;
		}

		output.push_back(records[i]);
	}

	return output;
}