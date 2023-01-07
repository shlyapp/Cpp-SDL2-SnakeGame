#pragma once

#include "Game.h"
#include <algorithm>
#include "Button.h"

Menu::Menu() {
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

#pragma endregion

	RecordsData recordsData;
	// Получаем 5 последних лушчих рекордов
	std::vector<int> records = recordsData.get_best_records(5);
	font = TTF_OpenFont("arial.ttf", 200);

	// Создаем текст для вывода рекордов
	for (int i = 0; i < 5; i++) {
		std::string text = std::to_string(i + 1) + ". " + std::to_string(records[i]) + " scores";
		score_surfaces[i] = TTF_RenderText_Solid(font, text.c_str(), {255, 255, 255});
		score_textures[i] = SDL_CreateTextureFromSurface(renderer, score_surfaces[i]);
		score_rect[i] = { 285, 200 + i * 50, 220, 50 };
	}

#pragma region Создание текста для заголовкой пунктов меню

	snake_surface = TTF_RenderText_Solid(font, "Snake", { 255, 255, 255 });
	snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
	snake_rect = { 185, 40, 415, 160 };

	records_surface = TTF_RenderText_Solid(font, "Records", { 255, 255, 255 });
	records_texture = SDL_CreateTextureFromSurface(renderer, records_surface);
	records_rect = { 185, 40, 415, 160 };

	info_surface = TTF_RenderText_Solid(font, "About", { 255, 255, 255 });
	info_texture = SDL_CreateTextureFromSurface(renderer, info_surface);
	info_rect = { 185, 40, 415, 160 };

	game_surface = TTF_RenderText_Solid(font, "Use arrows for move snake", { 255, 255, 255 });
	game_texture = SDL_CreateTextureFromSurface(renderer, game_surface);
	game_rect = { 145, 190, 515, 100 };

#pragma endregion

#pragma region Создание кнопок меню

	buttons.push_back(new Button({ 220, 200, 350, 70 }, "New Game", renderer));
	buttons.push_back(new Button({ 220, 290, 350, 70 }, "Records", renderer));
	buttons.push_back(new Button({ 220, 380, 350, 70 }, "About", renderer));
	buttons.push_back(new Button({ 220, 470, 350, 70 }, "Close", renderer));

	for (auto button : buttons) {
		button->add_listener(this);
	}

#pragma endregion

	show();
	SDL_Quit();
}

Menu::~Menu() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Menu::show()
{
	// Событие
	SDL_Event event;

	// Пока открыто меню игры
	while (menu_showing && !close)
	{
		// Обрабатываем событие
		controller(event);
		// Отображаем изображение
		render();
	}
}

void Menu::render() {
	SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);
	// Очищаем вывод
	SDL_RenderClear(renderer);
	
	// В зависимости от состояния меню, выводим нужное изображение
	switch (type)
	{
	case menuType::normal: {
		// Выводим кнопки и надпись
		for (auto button : buttons) {
			button->render(renderer);
		}
		SDL_RenderCopy(renderer, snake_texture, NULL, &snake_rect);
		break;
	}
	case menuType::new_game: {
		// Закрываем меню -> запускается игра
		menu_showing = false;
		break;
	}
	case menuType::records: {
		// Выводим все рекорды
		SDL_RenderCopy(renderer, records_texture, NULL, &records_rect);
		for (int i = 0; i < 5; i++) {
			SDL_RenderCopy(renderer, score_textures[i], NULL, &score_rect[i]);
		}
		break;
	}
	case menuType::info: {
		// Выводим информацию о игре
		SDL_RenderCopy(renderer, info_texture, NULL, &info_rect);
		SDL_RenderCopy(renderer, game_texture, NULL, &game_rect);
		break;
	}
	case menuType::exit: {
		// Выходим из игры
		close = true;
		SDL_Quit();
		break;
	}
	}

	SDL_RenderPresent(renderer);
}

void Menu::handle_click(Button* button)
{
	// Находим, какая кнопка из кнопок меню была нажата
	int i = 0;
	for (auto btn : buttons) {
		if (btn == button) break;
		i++;
	}

	// В зависимости от порядкового номер кнопки, меняем состояние меню
	type = static_cast<menuType>(i + 1);
}

void Menu::controller(SDL_Event& event) {
	while (SDL_PollEvent(&event)) {

		// Обновляем состояние всех кнопок
		for (auto button : buttons) {
			button->update(event);
		}

		// Событие закрытик окна
		if (event.type == SDL_QUIT) {
			close = true;
			SDL_Quit();
		}

		// По нажатию на Esc возвращаемся в главное меню
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			type = menuType::normal;
		}
	}
}

bool Menu::is_showing() {
	return menu_showing;
}