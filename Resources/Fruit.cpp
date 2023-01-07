#include "Game.h"

Fruit::Fruit() {
	// ���������� ����� �������� ������
	create_time = utils::hire_time_in_seconds();

	// ������������ ��������� ������ ������
	if (1 + rand() % 5 == 1) {
		type = fruitType::Blue;
	}
	else {
		type = fruitType::Red;
	}
}

void Fruit::render(SDL_Renderer* renderer) {
	// ���������� ����� ������ �� ���� ������
	if (type == fruitType::Blue) {
		SDL_SetRenderDrawColor(renderer, 128, 166, 255, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}

	// ����� �������������� 
	SDL_RenderFillRect(renderer, &rect);
}

bool Fruit::is_time_over() {
	// �������� ������� �����
	float current_time = utils::hire_time_in_seconds();

	// �������� ������� ����� ������� ������ � ���, ����� ��� ������ ������, ����� ���������� � ������
	return (current_time - create_time) > 3;
}
fruitType Fruit::get_type() {
	return type;
}
