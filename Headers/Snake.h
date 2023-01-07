#pragma once

#include <SDL.h>
#include <vector>

#include "Utils.h"
#include "Object.h"

/// <summary>
/// ����� ��� ����������� � ������ ��������� ������
/// </summary>
class Snake {
private:
	// ���� ���� 
	std::vector<Object> snake_body;
	// �������� �����������
	float snake_speed = 0.0f;
	// ������ 
	float snake_size = 0.0f;
public:
	Snake();
	Snake(utils::vector2f pos, float p_snake_size);

	/// <summary>
	/// ����������� ����������
	/// </summary>
	/// <param name="renderer">������</param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// ��� ������������ � �������
	/// </summary>
	void feed();

	/// <summary>
	/// �������� ������
	/// </summary>
	/// <param name="width">������</param>
	/// <param name="height">�����</param>
	/// <param name="toolbar_height">����� ������� ��� ����������� �����</param>
	void walk(unsigned int width, unsigned int height, unsigned int toolbar_height);

	/// <summary>
	/// ��������� ����������� ������ ������
	/// </summary>
	/// <param name="new_direction">����� �����������</param>
	void change_head_direction(utils::directions new_direction);

	/// <summary>
	/// �������� ����������� ������ ������
	/// </summary>
	/// <returns></returns>
	utils::directions& get_head_direction();

	/// <summary>
	/// �������� ������ ������
	/// </summary>
	/// <returns></returns>
	Object& get_head();

	/// <summary>
	/// �������� ���� ������
	/// </summary>
	/// <returns></returns>
	std::vector<Object>& get_snake_body();
};