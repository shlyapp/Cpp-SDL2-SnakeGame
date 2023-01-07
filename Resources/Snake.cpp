#include <SDL.h>
#include <vector>

#include "Snake.h"
#include "Utils.h"
#include "Object.h"

Snake::Snake()
	: snake_size(0.0f) {}

Snake::Snake(utils::vector2f pos, float p_snake_size)
	: snake_size(p_snake_size) {

	// Инициализируем змейку
	snake_body.push_back(Object(pos, snake_size, snake_size, utils::directions::UP));
	snake_speed = snake_size;

	// Добавить два звена
	feed();
	feed();
}

void Snake::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 201, 62, 218, 255);
	// Отображаем голову змейки
	get_head().render(renderer);

	// Отображаем тело змейки
	SDL_SetRenderDrawColor(renderer, 238, 130, 238, 255);
	for (unsigned int i = 1; i < snake_body.size(); ++i)
		snake_body[i].render(renderer);
}

void Snake::feed() {
	// Получаем последние элемент тела змейки
	Object& tail_end = snake_body[snake_body.size() - 1];
	// его позиция 
	utils::vector2f pos = tail_end.get_pos();

	// В зависимости от направления выбираем положение
	switch (tail_end.get_orientation()) {
	case utils::directions::UP: {
		pos.y = tail_end.get_pos().y + snake_size;

		break;
	}
	case utils::directions::DOWN: {
		pos.y = tail_end.get_pos().y - snake_size;

		break;
	}
	case utils::directions::LEFT: {
		pos.x = tail_end.get_pos().x + snake_size;

		break;
	}
	case utils::directions::RIGHT: {
		pos.x = tail_end.get_pos().x - snake_size;

		break;
	}
	}

	snake_body.push_back(Object(pos, snake_size, snake_size, tail_end.get_orientation()));
}

void Snake::walk(unsigned int width, unsigned int height, unsigned int toolbar_height) {

	// Старая позиция змеики
	utils::vector2f old_pos = get_head().get_pos();
	// Старое направление змейки
	utils::directions old_orientation = get_head_direction();

	// В зависимости от направление головы меняем положение
	switch (get_head_direction()) {
	case utils::directions::UP: {
		snake_body[0].modify_y_by(-snake_speed);

		break;
	}
	case utils::directions::DOWN: {
		snake_body[0].modify_y_by(snake_speed);

		break;
	}
	case utils::directions::LEFT: {
		snake_body[0].modify_x_by(-snake_speed);

		break;
	}
	case utils::directions::RIGHT: {
		snake_body[0].modify_x_by(snake_speed);

		break;
	}
	}

	utils::vector2f aux_pos;
	utils::directions aux_dir;

	// Сдвигаем тело змейки
	for (unsigned int i = 1; i < snake_body.size(); ++i) {
		aux_pos = snake_body[i].get_pos();
		aux_dir = snake_body[i].get_orientation();

		snake_body[i].set_pos(old_pos);
		snake_body[i].set_orientation(old_orientation);

		old_pos = aux_pos;
		old_orientation = aux_dir;
	}

	// Если змейка сталкивается с пределами картами,
	// то она просто появляется с другой стороны
	Object& head = get_head();
	float new_x = head.get_pos().x, new_y = head.get_pos().y;

	if (head.get_pos().y < toolbar_height)
		new_y = (float)height;
	else if (head.get_pos().y >= height)
		new_y = (float)toolbar_height;

	if (head.get_pos().x < 0)
		new_x = (float)width;
	else if (head.get_pos().x >= width)
		new_x = 0;

	head.set_pos(utils::vector2f(new_x, new_y));
}

void Snake::change_head_direction(utils::directions new_direction) {
	snake_body[0].set_orientation(new_direction);
}

utils::directions& Snake::get_head_direction() {
	return snake_body[0].get_orientation();
}

Object& Snake::get_head() {
	return snake_body[0];
}

std::vector<Object>& Snake::get_snake_body() {
	return snake_body;
}