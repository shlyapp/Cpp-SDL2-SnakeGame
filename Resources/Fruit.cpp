#include "Game.h"

Fruit::Fruit() {
	// Записываем время создания фрукта
	create_time = utils::hire_time_in_seconds();

	// Вероястность появления синего фрукта
	if (1 + rand() % 5 == 1) {
		type = fruitType::Blue;
	}
	else {
		type = fruitType::Red;
	}
}

void Fruit::render(SDL_Renderer* renderer) {
	// Разделение цвета вывода по типу фрукта
	if (type == fruitType::Blue) {
		SDL_SetRenderDrawColor(renderer, 128, 166, 255, 255);
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	}

	// Вывод прямоугольника 
	SDL_RenderFillRect(renderer, &rect);
}

bool Fruit::is_time_over() {
	// Получаем текущее время
	float current_time = utils::hire_time_in_seconds();

	// Считыаем разницу между текущим времен и тем, когда был создан обьект, затем сравниваем с числом
	return (current_time - create_time) > 3;
}
fruitType Fruit::get_type() {
	return type;
}
