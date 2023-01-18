#include <fstream>
#include <algorithm>
#include <cstring>
#include "Game.h"

RecordsData::RecordsData() {
	// ��� �������� ��������� ������
	load();

	get_best_records(5);
}

void RecordsData::load() {
	records.clear();
	names.clear();
	
	// ��������� ���� �� ������
	std::ifstream file("records.txt");
	// �������� �� �����
	int value = 0;

	// ���� ���� �� ����������
	while (!file.eof()) {
		// �������� �������� ������� �� �����
		file >> value;
		records.push_back(value);
	}

	// ���� ���������
	file.close();

	// ��������� ���� �� ������
	std::ifstream file2("usernames.txt");
	// �������� �� �����
	std::string name;

	// ���� ���� �� ����������
	while (!file2.eof()) {
		// �������� �������� ������� �� �����
		file2 >> name;
		names.push_back(name);
	}

	// ���� ���������
	file2.close();
}

void RecordsData::save() {
	std::fstream file("records.txt", std::ios::out);
	
	// ��������� �� ���������� ��������
	for (int i = 0; i < records.size(); i++) {
		// ���������� ������ � ����
		file << records[i];
		if (i != records.size() - 1) {
			file << std::endl;
		}
	}

	// ��������� ���� 
	file.close();

	std::fstream file2("usernames.txt", std::ios::out);

	// ��������� �� ���������� ��������
	for (int i = 0; i < names.size(); i++) {
		// ���������� ������ � ����
		file2 << names[i];
		if (i != records.size() - 1) {
			file2 << std::endl;
		}
	}

	// ��������� ���� 
	file2.close();
}

void RecordsData::add_record(int value, std::string name) {
	records.push_back(value);
	names.push_back(name);
	// ��������� ����������� ����
	save();
}

std::vector<std::string> RecordsData::get_best_records(int number) {
	load();

	std::vector<std::string> records_info;

	for (int i = 0; i < records.size(); i++) {
		for (int j = 0; j < records.size(); j++) {
			if (records[i] > records[j]) {
				int temp_record = records[i];
				records[i] = records[j];
				records[j] = temp_record;

				std::string temp_username = names[i];
				names[i] = names[j];
				names[j] = temp_username;
			}
		}
	}

	for (int i = 0; i < number; i++) {
		if (i > records.size() - 1) {
			records_info.push_back("---");
			continue;
		}

		records_info.push_back(names[i] + " " + std::to_string(records[i]));
	}

	return records_info;
}