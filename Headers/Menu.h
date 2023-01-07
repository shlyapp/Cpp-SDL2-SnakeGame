#pragma once

/// <summary>
/// Класс для отображения меню игры
/// </summary>
class Menu : public IEventListener
{
private:
	// Размер окна
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	// Название окна
	const char* APPLICATION_NAME = "Snake Game";

	// Показывается ли меню
	bool menu_showing = true;
	bool close = false;

	// Состояния меню
	enum menuType
	{
		normal, // Ничего не нажато, отображаются все кнопки
		new_game, // При клике на создание новой игры
		records, // Отображение рекордов
		info, // Отображение информации
		exit // При клике на выход
	};

	// Состояние
	menuType type = menuType::normal;

	// Шрифт для текста
	TTF_Font* font = NULL;

#pragma region Поверхности, прямоугольники и текстуры для отображения пунктов меню

	SDL_Surface* snake_surface = NULL;
	SDL_Rect snake_rect;
	SDL_Texture* snake_texture = NULL;

	SDL_Surface* records_surface = NULL;
	SDL_Rect records_rect;
	SDL_Texture* records_texture = NULL;

	SDL_Surface* info_surface = NULL;
	SDL_Rect info_rect;
	SDL_Texture* info_texture = NULL;

	SDL_Surface* game_surface = NULL;
	SDL_Rect game_rect;
	SDL_Texture* game_texture = NULL;

#pragma endregion

	// Массивы для вывода рекордов игрока
	SDL_Surface *score_surfaces[5];
	SDL_Rect score_rect[5];
	SDL_Texture *score_textures[5];

	// Окно и рендер
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// Лист кнопок для взаимодействия
	std::list<Button*> buttons;

public:
	Menu();
	~Menu();

	/// <summary>
	/// Отображение изображения на экране
	/// </summary>
	void render();

	/// <summary>
	/// Обновление состояния
	/// </summary>
	void show();

	/// <summary>
	/// Обработка событий
	/// </summary>
	/// <param name="event">Событие</param>
	void controller(SDL_Event& event);

	/// <summary>
	/// Обработка событий нажатия на кнопки
	/// </summary>
	/// <param name="btn">Кнопка, которая вызвала событие</param>
	void handle_click(Button* btn);

	/// <summary>
	/// Показывается ли меню
	/// </summary>
	/// <returns></returns>
	bool is_showing();
};