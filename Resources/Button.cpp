#include "Game.h"

Button::Button(SDL_Rect rect, std::string text, SDL_Renderer *renderer)
{
	// ����������� ��������� ������
	this->rect = rect;

	// ��������� ����� ��� ������ ������
	font = TTF_OpenFont("arial.ttf", 200);
	// ������ ��������� ��� ������ �� ������ (��������� �������� ������)
	rect_text = {rect.x + ((rect.w) / 2) - (((int)text.length() * 30) / 2), rect.y + (rect.h / 2) - 20, (int)text.length() * 30, 40};

	// ����������� ��� ������
	surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	// �������� ��� ������
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

bool Button::update(SDL_Event &event)
{
	// ���� ��������� ������� �� ������ ����
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
	{
		// �������� ���������� ������� ����
		Sint32 x = event.button.x;
		Sint32 y = event.button.y;

		// ���������, ��������� �� ������ ���� � ���� ������
		if (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h))
		{
			// ��������� ���������� � ���, ��� ��������� ������� �� ������
			notify_listener();
			return true;
		}
	}

	return false;
}

void Button::render(SDL_Renderer *renderer)
{
	// ������������� ��������� ����
	SDL_SetRenderDrawColor(renderer, 58, 180, 73, 0xFF);
	// ��������� �������������� ������
	SDL_RenderFillRect(renderer, &rect);

	// ��������� ������
	SDL_RenderCopy(renderer, texture, NULL, &rect_text);
}

void Button::add_listener(IEventListener *listener)
{
	listeners.push_back(listener);
}

void Button::notify_listener()
{
	// ��������� ������� ���������
	for (auto listener : listeners)
	{
		listener->handle_click(this);
	}
}

void Button::set_text(std::string text, SDL_Renderer *renderer)
{
	SDL_Rect rect_text_new;
	// Считаем размер текста
	rect_text_new = {rect.x + ((rect.w) / 2) - (((int)text.length() * 30) / 2), rect.y + (rect.h / 2) - 20, (int)text.length() * 30, 40};

	// Если текст не помещается на кнопку
	if (rect_text_new.w > rect.w)
	{
		return;
	}

	rect_text = rect_text_new;

	this->text = text;
	// ����������� ��� ������
	surface = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
	// �������� ��� ������
	texture = SDL_CreateTextureFromSurface(renderer, surface);
}

std::string Button::get_text()
{
	return this->text;
}