#include <SDL.h>

#include "Object.h"
#include "Utils.h"

Object::Object(utils::vector2f p_pos, float p_width, float p_height, utils::directions p_orientation)
	:pos(p_pos), width(p_width), height(p_height) {

	// Иницализируем поля
	rect.x = (int)pos.x;
	rect.y = (int)pos.y;
	rect.w = (int)width;
	rect.h = (int)height;

	orientation = p_orientation;
}

void Object::render(SDL_Renderer* renderer) {
	rect.x = (int)pos.x;
	rect.y = (int)pos.y;

	// Выводим изображения
	SDL_RenderFillRect(renderer, &rect);
}

void Object::modify_x_by(float modifier) {
	// Изменяем положение по X
	pos.x += modifier;
}

void Object::modify_y_by(float modifier) {
	// Изменяем положение по Y
	pos.y += modifier;
}

void Object::set_pos(utils::vector2f new_pos) {
	pos = new_pos;
}

utils::vector2f& Object::get_pos() {
	return pos;
}

void Object::set_orientation(utils::directions new_orientation) {
	orientation = new_orientation;
}

utils::directions& Object::get_orientation() {
	return orientation;
}