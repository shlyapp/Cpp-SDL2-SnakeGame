#include <SDL.h>
#include <SDL_ttf.h>
#include <cmath>
#include <string>
#include <time.h>
#include <vector>

#include "Utils.h"
#include "Fruit.h"
#include "RecordsData.h"
#include "Game.h"
#include "Menu.h"
#include "Object.h"


Game::Game()
	:background_rows(SCREEN_HEIGHT / SNAKE_SIZE), background_cols(SCREEN_WIDTH / SNAKE_SIZE), toolbar({ 0,0,0,0 }) {

	menu = new Menu;

	if (menu->is_closing()) {
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	else {
		init();
	}

	
}
Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::init() {
#pragma region Иницализция окна игры, рендера и шрифта

	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		utils::print_sdl_error("An error occured while trying to init sdl video.");
		SDL_Quit();
		return;
	}

	window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		utils::print_sdl_error("An error occured while trying to create the window.");
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		utils::print_sdl_error("An error occured while trying to create the renderer.");
		SDL_Quit();
		return;
	}

	if (TTF_Init() == -1)
		utils::print_sdl_error("An error occured while trying to use TTF_Init().");

	score_font = TTF_OpenFont("arial.ttf", FONT_SCORE_SIZE);
	if (score_font == NULL)
		utils::print_sdl_error("An error occured while trying to load the score font.");

#pragma endregion

	// Инициалация змейки
	snake = Snake(utils::vector2f(200, 200), (float)SNAKE_SIZE);

	// Инициалзируем прямоугольники заднего фона
	SDL_Rect square;
	// Ширина и высота, как и змеи
	square.w = square.h = SNAKE_SIZE;
	unsigned int x = 0, y = 0;
	// Проходим циклом по строчкам
	for (unsigned int i = 0; i < background_rows; ++i) {
		// Задаем координаты
		x = (i & 1) ? 0 : SNAKE_SIZE;
		square.y = y;

		// Проходим циклом по столбцам
		for (unsigned int j = (i & 1) ? 0 : 1; j < background_cols; ++j) {
			square.x = x;

			background.push_back(square);

			// Увелививаем координаты для следующего прямоугольника (тайла)
			x += SNAKE_SIZE * 2;
		}

		y += SNAKE_SIZE;
	}

	// Настройка размеров области для вывода количества очков
	toolbar.x = toolbar.y = 0;
	toolbar.w = SCREEN_WIDTH;
	toolbar.h = TOOLBAR_HEIGHT;

	srand((unsigned int)time(NULL));

	// Добавляем первый фрукт
	fruits.push_back(new Fruit);

	// Случайным обрахом выбираем координаты ячейки
	fruits[0]->position.x = (float)(rand() % (background_cols - 1));
	fruits[0]->position.y = (float)(rand() % (background_rows - 1) + (TOOLBAR_HEIGHT / SNAKE_SIZE));

	// Задаем координаты в формате экрана и размер фрукты
	fruits[0]->rect.x = (int)(fruits[0]->position.x * SNAKE_SIZE);
	fruits[0]->rect.y = (int)(fruits[0]->position.y * SNAKE_SIZE);
	fruits[0]->rect.w = fruits[0]->rect.h = SNAKE_SIZE;

	// Поверхность и текстура для вывода количество очков
	surface_score = TTF_RenderText_Solid(score_font, "YOUR SCORE: 0", { 255, 255, 255 });
	score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);
	// Размеры надписи о количестве очков
	score_rect_dest.x = 20;
	score_rect_dest.y = TOOLBAR_HEIGHT / 2 - FONT_SCORE_SIZE;
	score_rect_dest.h = 20;
	score_rect_dest.w = 0;

	// Запускаем главный игровой цикд
	game_loop();

	// Закрываем окно и шрифт, с которым работали
	SDL_Quit();
}

void Game::game_loop() {

	// Изменение времени для обновления
	const float delta_time = 0.1f;

	// Текущее время 
	float current_time = utils::hire_time_in_seconds(),
		accumulator = 0.0f;

	// Событие 
	SDL_Event event;

	// Цикл, пока игры запушена
	while (game_running) {

		// Получаем текушее время
		float new_time = utils::hire_time_in_seconds(),
			// Находим время кадра
			frame_time = new_time - current_time;
		// Обновляем текущее время
		current_time = new_time;

		accumulator += frame_time;

		// Проверка на столкновение
		bool is_check = false;

		// Время для обновления
		while (accumulator >= delta_time) {
			// Получаем все тело змейки
			std::vector<Object> snake_body = snake.get_snake_body();

			// Обрабатываем события, если они есть
			controller(event);

			// Двигаем змею
			snake.walk(SCREEN_WIDTH, SCREEN_HEIGHT, TOOLBAR_HEIGHT);

			// Проходимся по каждому звену змеики (части тела)
			for (unsigned int i = 1; i < snake_body.size(); ++i) {
				// Проверяем на столкновени с самой собой
				if (snake.get_head().get_pos() == snake_body[i].get_pos()) {
					// уничитожаем активное окно
					SDL_DestroyWindow(window);
					SDL_DestroyRenderer(renderer);

					// сохраняем рекорд и возвращаемся к исходным настройкам
					records.add_record(player_score);
					player_score = 0;
					generation_speed = 100;
					fruits.clear();
					snake = Snake(utils::vector2f(200, 200), (float)SNAKE_SIZE);
					
					menu = new Menu;
					
					if (menu->is_closing()) {
						SDL_DestroyWindow(window);
						SDL_DestroyRenderer(renderer);
						SDL_Quit();
					}
					else {
						init();
					}

					return;
				}
			}

			// Проходимся по каждому фрукту
			for (auto fruit : fruits) {
				// Если время жизни фрукта истекло, то удаляем его
				if (fruit->is_time_over()) {
					auto it = std::remove(fruits.begin(), fruits.end(), fruit);
					fruits.erase(it, fruits.end());

					// Если на игрвовом поле осталось меньше 2 фруктов,
					// то добавляем фрукт
					if (fruits.size() < 2) {
						add_fruit();
					}

					break;
				}
			}

			// С некой вероятностью, зависящей от скорости генерации
			// создаем новый фрукт на поле
			if ((1 + rand() % generation_speed) == 1) {
				add_fruit();
			}

			// Если еще не было стокновения с фруктов
			if (!is_check) {
				// Проходимся по всем фруктам
				for (auto fruit : fruits) {

					// Проверяем на совпадение положения фрукта с положением головы змейки
					if (snake.get_head().get_pos() == utils::vector2f((float)fruit->rect.x, (float)fruit->rect.y)) {

						// Скармливем змейке
						snake.feed();

						// Обновялем счетчик очков в зависимости от типа фрукта
						if (fruit->get_type() == fruitType::Red)
							player_score++;
						else
							player_score += 5;

						// Увеличваем шанс генерации фруктов
						if (generation_speed - 5 > 0) {
							generation_speed -= 5;
						}

						// Удаляем фрукт, с которым столкнулась змейка
						auto it = std::remove(fruits.begin(), fruits.end(), fruit);
						fruits.erase(it, fruits.end());

						// Добавляем новый фрукт за место старого
						add_fruit();

						// Обновляем надпись о количестве очков
						std::string score_str = "YOUR SCORE: " + std::to_string(player_score);

						SDL_FreeSurface(surface_score);
						surface_score = TTF_RenderText_Solid(score_font, score_str.c_str(), { 255, 255, 255 });

						SDL_DestroyTexture(score_texture);
						score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);

						score_rect_dest.w = score_str.size() * FONT_SCORE_SIZE;
						is_check = true;
						break;
					}
				}
			}
			accumulator -= delta_time;
		}

		// Выводим измененное изображением
		render();
	}
}

void Game::add_fruit() {
	// Получаем все тело змеи
	std::vector<Object> snake_tail = snake.get_snake_body();
	// Корректна ли данная позиция
	bool is_valid_position = false;

	// Новый фрукт
	Fruit* new_fruit = new Fruit;

	// Если позиция не корректна (то есть позиция фрукта совпадает с позицией змеи)
	while (!is_valid_position) {
		is_valid_position = true;

		// Случайным образом выбираем ячейки карты для фрукта
		new_fruit->position.x = (float)(rand() % (background_cols - 1));
		new_fruit->position.y = (float)(rand() % (background_rows - 1) + (TOOLBAR_HEIGHT / SNAKE_SIZE));

		// Проверяем не занята ли эта ячейка змеей
		for (unsigned int i = 0; i < snake_tail.size(); ++i)
			if (snake_tail[i].get_pos() == utils::vector2f((float)(new_fruit->position.x * SNAKE_SIZE), (float)(new_fruit->position.y * SNAKE_SIZE)))
				is_valid_position = false;
	}

	// Задаем реальные координаты на экране
	new_fruit->rect.x = (int)(new_fruit->position.x * SNAKE_SIZE);
	new_fruit->rect.y = (int)(new_fruit->position.y * SNAKE_SIZE);
	new_fruit->rect.w = new_fruit->rect.h = SNAKE_SIZE;

	// Добавляем к остальным фруктам
	fruits.push_back(new_fruit);
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);
	// Очищаем окно
	SDL_RenderClear(renderer);

	// Выводим каждую ячейку карты
	SDL_SetRenderDrawColor(renderer, 58, 180, 73, 255);
	for (unsigned int i = 0; i < background.size(); ++i)
		SDL_RenderFillRect(renderer, &background[i]);

	// Выводим область под количество очков
	SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);
	SDL_RenderFillRect(renderer, &toolbar);

	// Выводим фрукты
	for (auto fruit : fruits) {
		fruit->render(renderer);
	}

	// Выводим голову
	snake.render(renderer);

	// Выводим количество очков
	SDL_RenderCopy(renderer, score_texture, NULL, &score_rect_dest);

	SDL_RenderPresent(renderer);
}

void Game::controller(SDL_Event& event) {
	// Проверка на события
	while (SDL_PollEvent(&event)) {
		// Событие закрытие окна
		if (event.type == SDL_QUIT)
			game_running = false;

		// Если нажата какая-то клавиша
		if (event.type == SDL_KEYDOWN) {
			// В зависимости от клавиши, меняем направление змейки
			switch (event.key.keysym.sym) {
			case SDLK_UP: {
				// Проверяем на противополжное движение, чтобы не было столкновения 
				if (snake.get_head_direction() == utils::directions::DOWN) break;

				snake.change_head_direction(utils::directions::UP);

				break;
			}
			case SDLK_DOWN: {
				if (snake.get_head_direction() == utils::directions::UP) break;

				snake.change_head_direction(utils::directions::DOWN);

				break;
			}
			case SDLK_LEFT: {
				if (snake.get_head_direction() == utils::directions::RIGHT) break;

				snake.change_head_direction(utils::directions::LEFT);

				break;
			}
			case SDLK_RIGHT: {
				if (snake.get_head_direction() == utils::directions::LEFT) break;

				snake.change_head_direction(utils::directions::RIGHT);

				break;
			}
			case SDLK_f: {
				snake.feed();
				break;
			}
			}
		}
	}
}