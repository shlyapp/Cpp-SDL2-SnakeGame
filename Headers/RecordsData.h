#pragma once

/// <summary>
/// ����� ��� �������� � �������������� � ��������� ������������
/// </summary>
class RecordsData {
private:
	// ������ ��������
	std::vector<int> records;
	
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
	void add_record(int value);

	/// <summary>
	/// �������� ������ �������
	/// </summary>
	/// <param name="number">���������� ������ ��������</param>
	/// <returns></returns>
	std::vector<int> get_best_records(int number);
};