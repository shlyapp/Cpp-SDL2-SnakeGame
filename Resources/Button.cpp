#include "Game.h"

Button::Button(SDL_Rect rect, std::string text, SDL_Renderer* renderer) {
	// Присваиваем положение кнопке
	this->rect = rect;

	// Открываем шрифт для вывода текста
	font = TTF_OpenFont("arial.ttf", 200);
	// Задаем положение для текста на кнопке (считается середина кнопки)
	rect_text = {rect.x + ((rect.w) / 2) - (((int)text.length() * 30) / 2), rect.y + (rect.h / 2) - 20, (int)text.length() * 30, 40};

	// Поверхность для текста
	surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	// Текстура для текста
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

void Button::update(SDL_Event& event) {
	// Если произошло нажатие на кнопку мыши
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
		// Получаем координаты курсора мыши
		Sint32 x = event.button.x;
		Sint32 y = event.button.y;

		// Проверяем, находится ли курсор мыши в зоне кнопки
		if (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h)) {
			// Оповещаем слушателей о том, что произошло нажатие на кнопку
			notify_listener();
		}
	}
}

void Button::render(SDL_Renderer* renderer) {
	// Устанавливаем необхомый цвет
	SDL_SetRenderDrawColor(renderer, 58, 180, 73, 0xFF);
	// Отрисовка прямоугольника кнопки
	SDL_RenderFillRect(renderer, &rect);

	// Отрисовка текста
	SDL_RenderCopy(renderer, texture, NULL, &rect_text);		
}

void Button::add_listener(IEventListener* listener) {
	listeners.push_back(listener);
}

void Button::notify_listener() {
	// Оповещаем каждого слушателя
	for (auto listener : listeners)
	{
		listener->handle_click(this);
	}
}