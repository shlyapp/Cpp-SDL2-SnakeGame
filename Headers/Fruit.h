#pragma once

/// <summary>
/// ���� ������ �� ������
/// </summary>
enum fruitType {
	Red,
	Blue
};

/// <summary>
/// �����, ����������� ������ ������
/// </summary>
class Fruit {
private:
	// ��� ������
	fruitType type;
	// ����� �������� ������
	float create_time;

public:
	// ������� � ������
	utils::vector2f position;
	SDL_Rect rect;

	Fruit();

	/// <summary>
	/// ����� �� �����
	/// </summary>
	/// <param name="renderer">������</param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// ��������� ������� ������������� ������
	/// </summary>
	/// <returns>true - ������ 3 ������� � ������� ��������, false - � ��������� ������</returns>
	bool is_time_over();
	
	/// <summary>
	/// ��� ������
	/// </summary>
	/// <returns>���������� ��� ������</returns>
	fruitType get_type();
};