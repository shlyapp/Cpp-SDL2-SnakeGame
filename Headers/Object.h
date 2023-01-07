#pragma once

#include <SDL.h>

#include "Utils.h"

/// <summary>
/// Класс для тела змейки
/// </summary>
/// <param name="p_pos">Позиция на экране</param>
/// <param name="p_width">Ширина</param>
/// <param name="p_height">Высота</param>
/// <param name="p_orientation">Ориентация</param>
class Object {
private:
	// Позиция на экране
	utils::vector2f pos;

	// Высота и ширина
	float width, height;

	// Прямоугольник для вывода
	SDL_Rect rect;

	// Направление движения
	utils::directions orientation;
public:
	Object(utils::vector2f p_pos, float p_width, float p_height, utils::directions p_orientation);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// Изменение позиции по X
	/// </summary>
	/// <param name="modifier"></param>
	void modify_x_by(float modifier);

	/// <summary>
	/// Изменение позиции по Y
	/// </summary>
	/// <param name="modifier"></param>
	void modify_y_by(float modifier);

#pragma region Геттеы и сеттеры для позиции и ориентации
	void set_pos(utils::vector2f new_pos);
	utils::vector2f& get_pos();
	void set_orientation(utils::directions new_orientation);
	utils::directions& get_orientation();
#pragma endregion
};