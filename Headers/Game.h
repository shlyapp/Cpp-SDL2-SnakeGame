#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#include "RecordsData.h"
#include "Button.h"
#include "Menu.h"
#include "Snake.h"
#include "Fruit.h"

/// <summary>
/// Класс, описывающий логику игры
/// </summary>
class Game {
private:
	// Размер экрана
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	// Название окна
	const char* APPLICATION_NAME = "Snake Game";

	// Размер змеи
	const unsigned int SNAKE_SIZE = 40;

	// Окно и рендер
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// Статус игры (запущена или нет)
	bool game_running = true;

	// Змейка
	Snake snake;

	Menu* menu = NULL;

	// Рекорды пользователя
	RecordsData records;

	// Строки и столбы заднего фона
	unsigned int background_rows, background_cols;

	// Вектор, содержащий прямоугольники длля вывода заднего фона
	std::vector<SDL_Rect> background;

	// Прямоугольник для вывода очков
	SDL_Rect toolbar;
	const unsigned int TOOLBAR_HEIGHT = 40;

	// Фрукты
	std::vector<Fruit*> fruits;

	// Скорость генерации новых фруктов
	int generation_speed = 100;

#pragma region Поверхность, прямоугольник, текстура, шрифт для вывода количество очков

	SDL_Surface* surface_score = NULL;
	SDL_Rect score_rect_dest;
	SDL_Texture* score_texture = NULL;
	TTF_Font* score_font = NULL;
	const unsigned int FONT_SCORE_SIZE = 15;

#pragma endregion

	// Количество очков игрока
	unsigned int player_score = 0;

public:
	Game();
	~Game();

	void init();

	/// <summary>
	/// Главный игровок цикл
	/// </summary>
	void game_loop();

	/// <summary>
	/// Вывод изображения
	/// </summary>
	void render();

	/// <summary>
	/// Обработка нажатий на клавиши
	/// </summary>
	/// <param name="event">Событие нажатия</param>
	void controller(SDL_Event& event);

	/// <summary>
	/// Добавить новый фрукт на поле
	/// </summary>
	void add_fruit();
};