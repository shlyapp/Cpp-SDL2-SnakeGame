#pragma once
#include <list>
#define _CRT_SECURE_NO_WARNINGS
#include <string>

/// <summary>
/// Класс для хранения и взаимодействия с рекордами пользователя
/// </summary>
class RecordsData {
private:
	// Вектор рекордов
	std::vector<int> records;
	std::vector<std::string> names;
	
	/// <summary>
	/// Загрузка рекордов из текстового файла
	/// </summary>
	void load();

	/// <summary>
	/// Сохранение рекордов в текстовый файл
	/// </summary>
	void save();

public:
	RecordsData();
	
	/// <summary>
	/// Добавление нового рекорда
	/// </summary>
	/// <param name="value">Количество очков</param>
	void add_record(int value, std::string name);

	/// <summary>
	/// Получить лучшие рекорды
	/// </summary>
	/// <param name="number">Количество лучших рекордов</param>
	/// <returns></returns>
	std::vector<std::string> get_best_records(int number);
};