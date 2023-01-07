#pragma once

#include <SDL.h>
#include <vector>

#include "Utils.h"
#include "Object.h"

/// <summary>
/// Класс для отображения и логики поведения змейки
/// </summary>
class Snake {
private:
	// Тело змеи 
	std::vector<Object> snake_body;
	// Скорость перемещения
	float snake_speed = 0.0f;
	// Размер 
	float snake_size = 0.0f;
public:
	Snake();
	Snake(utils::vector2f pos, float p_snake_size);

	/// <summary>
	/// Отображение изобржения
	/// </summary>
	/// <param name="renderer">Рендер</param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// При столкновении с фруктом
	/// </summary>
	void feed();

	/// <summary>
	/// Движение змейки
	/// </summary>
	/// <param name="width">Ширина</param>
	/// <param name="height">Длина</param>
	/// <param name="toolbar_height">Длина области для отображения очков</param>
	void walk(unsigned int width, unsigned int height, unsigned int toolbar_height);

	/// <summary>
	/// Изменение направление головы змеики
	/// </summary>
	/// <param name="new_direction">Новое направление</param>
	void change_head_direction(utils::directions new_direction);

	/// <summary>
	/// Получить направление головы змеики
	/// </summary>
	/// <returns></returns>
	utils::directions& get_head_direction();

	/// <summary>
	/// Получить голову змейки
	/// </summary>
	/// <returns></returns>
	Object& get_head();

	/// <summary>
	/// Получить тело змейки
	/// </summary>
	/// <returns></returns>
	std::vector<Object>& get_snake_body();
};