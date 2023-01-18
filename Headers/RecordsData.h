#pragma once
#include <list>
#define _CRT_SECURE_NO_WARNINGS
#include <string>

/// <summary>
/// ����� ��� �������� � �������������� � ��������� ������������
/// </summary>
class RecordsData {
private:
	// ������ ��������
	std::vector<int> records;
	std::vector<std::string> names;
	
	/// <summary>
	/// �������� �������� �� ���������� �����
	/// </summary>
	void load();

	/// <summary>
	/// ���������� �������� � ��������� ����
	/// </summary>
	void save();

public:
	RecordsData();
	
	/// <summary>
	/// ���������� ������ �������
	/// </summary>
	/// <param name="value">���������� �����</param>
	void add_record(int value, std::string name);

	/// <summary>
	/// �������� ������ �������
	/// </summary>
	/// <param name="number">���������� ������ ��������</param>
	/// <returns></returns>
	std::vector<std::string> get_best_records(int number);
};