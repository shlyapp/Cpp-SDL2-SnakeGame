#pragma once

namespace utils {
	
	/// <summary>
	/// Вывод информации о ошибке SDL
	/// </summary>
	/// <param name="error_text">Текст ошибки</param>
	void print_sdl_error(const char* error_text);

	/// <summary>
	/// Текущее время в секундах
	/// </summary>
	/// <returns></returns>
	float hire_time_in_seconds();

	/// <summary>
	/// Структура для хранения положения объкта
	/// </summary>
	struct vector2f {
		float x, y;
		vector2f() : x(0.0f), y(0.0f) {}
		vector2f(float p_x, float p_y) : x(p_x), y(p_y) {}
		/// <summary>
		/// Перегрузка оператора сравнения
		/// </summary>
		/// <param name="aux"></param>
		/// <returns></returns>
		bool operator ==(vector2f aux);
		void print();
	};

	/// <summary>
	/// Направления движения
	/// </summary>
	enum directions {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
};