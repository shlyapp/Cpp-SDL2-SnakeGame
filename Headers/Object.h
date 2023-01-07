#pragma once

#include <SDL.h>

#include "Utils.h"

/// <summary>
/// ����� ��� ���� ������
/// </summary>
/// <param name="p_pos">������� �� ������</param>
/// <param name="p_width">������</param>
/// <param name="p_height">������</param>
/// <param name="p_orientation">����������</param>
class Object {
private:
	// ������� �� ������
	utils::vector2f pos;

	// ������ � ������
	float width, height;

	// ������������� ��� ������
	SDL_Rect rect;

	// ����������� ��������
	utils::directions orientation;
public:
	Object(utils::vector2f p_pos, float p_width, float p_height, utils::directions p_orientation);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="renderer"></param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// ��������� ������� �� X
	/// </summary>
	/// <param name="modifier"></param>
	void modify_x_by(float modifier);

	/// <summary>
	/// ��������� ������� �� Y
	/// </summary>
	/// <param name="modifier"></param>
	void modify_y_by(float modifier);

#pragma region ������ � ������� ��� ������� � ����������
	void set_pos(utils::vector2f new_pos);
	utils::vector2f& get_pos();
	void set_orientation(utils::directions new_orientation);
	utils::directions& get_orientation();
#pragma endregion
};