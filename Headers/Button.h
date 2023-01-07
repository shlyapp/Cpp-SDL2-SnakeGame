#pragma once

#include <string>
#include <list>

class Button;

/// <summary>
/// Абастрактный класс, реализующий паттерн "Слушатель"
/// </summary>
class IEventListener {
protected:
	IEventListener() {};

public:
	/// <summary>
	/// Обработка нажатия на кнопку
	/// </summary>
	/// <param name="button">Кнопка, которая вызвала это событие</param>
	virtual void handle_click(Button* button) = 0;
};

class Button {
private:
	// Прямоугольник кнопки
	SDL_Rect rect;
	// Прямоугольник для текста
	SDL_Rect rect_text;

	// Поверхность, текстура и шрифт для текста
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font* font = NULL;

	std::vector<IEventListener*> listeners;

public:
	/// <summary>
	/// Графический элемент кнопка 
	/// </summary>
	/// <param name="rect">Размер и положение</param>
	/// <param name="text">Текст для отображения</param>
	/// <param name="renderer">Рендер</param>
	Button(SDL_Rect rect, std::string text, SDL_Renderer* renderer);

	/// <summary>
	/// Обновление состояния
	/// </summary>
	/// <param name="event">Событие SDL</param>
	void update(SDL_Event& event);

	/// <summary>
	/// Вывод на экран
	/// </summary>
	/// <param name="renderer">Рендер</param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// Добавить слушателя событий
	/// </summary>
	/// <param name="lisener">Сулшатель</param>
	void add_listener(IEventListener* lisener);

	/// <summary>
	/// Оповестить слушателей о событии 
	/// </summary>
	void notify_listener();
};