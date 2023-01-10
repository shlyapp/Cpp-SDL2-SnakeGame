#include <fstream>
#include <algorithm>

#include "Game.h"

RecordsData::RecordsData() {
	// ��� �������� ��������� ������
	load();
}

void RecordsData::load() {
	records.clear();

	// ��������� ���� �� ������
	std::ifstream file("records.txt");
	// �������� �� �����
	int value;

	// ���� ���� �� ����������
	while (!file.eof()) {
		// �������� �������� ������� �� �����
		file >> value;
		// ��������� ���
		records.push_back(value);
	}

	// ���� ���������
	file.close();
}

void RecordsData::save() {
	// ��������� ���� �� ������, ������� ���
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
}

void RecordsData::add_record(int value) {
	records.push_back(value);
	// ��������� ����������� ����
	save();
}

std::vector<int> RecordsData::get_best_records(int number) {
	load();
	std::vector<int> output;

	// ��������� �� ����������� �������
	std::sort(records.begin(), records.end());
	// ��������������, ������� ���������� �� ��������
	std::reverse(records.begin(), records.end());

	// �������� ������ �������
	for (int i = 0; i < number; i++)
	{
		// ���� ���������� ������������� �������� ������, ��� ���� ��������
		if (i > records.size() - 1) {
			// ��������� �������
			output.push_back(0);
			continue;
		}

		output.push_back(records[i]);
	}

	return output;
}