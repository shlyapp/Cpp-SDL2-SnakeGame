#pragma once

/// <summary>
/// Типы фрукта по цветам
/// </summary>
enum fruitType {
	Red,
	Blue
};

/// <summary>
/// Класс, описывающий модель фрукта
/// </summary>
class Fruit {
private:
	// Тип фрукта
	fruitType type;
	// Время создания фрукта
	float create_time;

public:
	// Позиция и размер
	utils::vector2f position;
	SDL_Rect rect;

	Fruit();

	/// <summary>
	/// Вывод на экран
	/// </summary>
	/// <param name="renderer">Рендер</param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// Окончание времени существования фрукта
	/// </summary>
	/// <returns>true - прошло 3 секунды с момента создания, false - в противнов случае</returns>
	bool is_time_over();
	
	/// <summary>
	/// Тип фрукта
	/// </summary>
	/// <returns>Возвращает тип фрукта</returns>
	fruitType get_type();
};