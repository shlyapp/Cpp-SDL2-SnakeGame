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
	: background_rows(SCREEN_HEIGHT / SNAKE_SIZE), background_cols(SCREEN_WIDTH / SNAKE_SIZE), toolbar({0, 0, 0, 0})
{

	menu = new Menu;

	if (menu->is_closing())
	{
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
	}
	else
	{
		init();
	}
}
Game::~Game()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Game::init()
{
#pragma region ����������� ���� ����, ������� � ������

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		utils::print_sdl_error("An error occured while trying to init sdl video.");
		SDL_Quit();
		return;
	}

	window = SDL_CreateWindow(APPLICATION_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		utils::print_sdl_error("An error occured while trying to create the window.");
		SDL_Quit();
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
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

	// ����������� ������
	snake = Snake(utils::vector2f(200, 200), (float)SNAKE_SIZE);

	// ������������� �������������� ������� ����
	SDL_Rect square;
	// ������ � ������, ��� � ����
	square.w = square.h = SNAKE_SIZE;
	unsigned int x = 0, y = 0;
	// �������� ������ �� ��������
	for (unsigned int i = 0; i < background_rows; ++i)
	{
		// ������ ����������
		x = (i & 1) ? 0 : SNAKE_SIZE;
		square.y = y;

		// �������� ������ �� ��������
		for (unsigned int j = (i & 1) ? 0 : 1; j < background_cols; ++j)
		{
			square.x = x;

			background.push_back(square);

			// ����������� ���������� ��� ���������� �������������� (�����)
			x += SNAKE_SIZE * 2;
		}

		y += SNAKE_SIZE;
	}

	// ��������� �������� ������� ��� ������ ���������� �����
	toolbar.x = toolbar.y = 0;
	toolbar.w = SCREEN_WIDTH;
	toolbar.h = TOOLBAR_HEIGHT;

	srand((unsigned int)time(NULL));

	// ��������� ������ �����
	fruits.push_back(new Fruit);

	// ��������� ������� �������� ���������� ������
	fruits[0]->position.x = (float)(rand() % (background_cols - 1));
	fruits[0]->position.y = (float)(rand() % (background_rows - 1) + (TOOLBAR_HEIGHT / SNAKE_SIZE));

	// ������ ���������� � ������� ������ � ������ ������
	fruits[0]->rect.x = (int)(fruits[0]->position.x * SNAKE_SIZE);
	fruits[0]->rect.y = (int)(fruits[0]->position.y * SNAKE_SIZE);
	fruits[0]->rect.w = fruits[0]->rect.h = SNAKE_SIZE;

	// ����������� � �������� ��� ������ ���������� �����
	surface_score = TTF_RenderText_Solid(score_font, "YOUR SCORE: 0", {255, 255, 255});
	score_texture = SDL_CreateTextureFromSurface(renderer, surface_score);
	// ������� ������� � ���������� �����
	score_rect_dest.x = 20;
	score_rect_dest.y = TOOLBAR_HEIGHT / 2 - FONT_SCORE_SIZE;
	score_rect_dest.h = 20;
	score_rect_dest.w = 0;

	// ��������� ������� ������� ����
	game_loop();

	// ��������� ���� � �����, � ������� ��������
	SDL_Quit();
}

void Game::game_loop()
{

	// ��������� ������� ��� ����������
	const float delta_time = 0.1f;

	// ������� �����
	float current_time = utils::hire_time_in_seconds(),
		  accumulator = 0.0f;

	// �������
	SDL_Event event;

	// ����, ���� ���� ��������
	while (game_running)
	{

		// �������� ������� �����
		float new_time = utils::hire_time_in_seconds(),
			  // ������� ����� �����
			frame_time = new_time - current_time;
		// ��������� ������� �����
		current_time = new_time;

		accumulator += frame_time;

		// �������� �� ������������
		bool is_check = false;

		// ����� ��� ����������
		while (accumulator >= delta_time)
		{
			// �������� ��� ���� ������
			std::vector<Object> snake_body = snake.get_snake_body();

			// ������������ �������, ���� ��� ����
			controller(event);

			// ������� ����
			snake.walk(SCREEN_WIDTH, SCREEN_HEIGHT, TOOLBAR_HEIGHT);

			// ���������� �� ������� ����� ������ (����� ����)
			for (unsigned int i = 1; i < snake_body.size(); ++i)
			{
				// ��������� �� ����������� � ����� �����
				if (snake.get_head().get_pos() == snake_body[i].get_pos())
				{

					show_gameover();
				}
			}

			// ���������� �� ������� ������
			for (auto fruit : fruits)
			{
				// ���� ����� ����� ������ �������, �� ������� ���
				if (fruit->is_time_over())
				{
					auto it = std::remove(fruits.begin(), fruits.end(), fruit);
					fruits.erase(it, fruits.end());

					// ���� �� �������� ���� �������� ������ 2 �������,
					// �� ��������� �����
					if (fruits.size() < 2)
					{
						add_fruit();
					}

					break;
				}
			}

			// � ����� ������������, ��������� �� �������� ���������
			// ������� ����� ����� �� ����
			if ((1 + rand() % generation_speed) == 1)
			{
				add_fruit();
			}

			// ���� ��� �� ���� ����������� � �������
			if (!is_check)
			{
				// ���������� �� ���� �������
				for (auto fruit : fruits)
				{

					// ��������� �� ���������� ��������� ������ � ���������� ������ ������
					if (snake.get_head().get_pos() == utils::vector2f((float)fruit->rect.x, (float)fruit->rect.y))
					{

						// ���������� ������
						snake.feed();

						// ��������� ������� ����� � ����������� �� ���� ������
						if (fruit->get_type() == fruitType::Red)
							player_score++;
						else
							player_score += 5;

						// ���������� ���� ��������� �������
						if (generation_speed - 5 > 0)
						{
							generation_speed -= 5;
						}

						// ������� �����, � ������� ����������� ������
						auto it = std::remove(fruits.begin(), fruits.end(), fruit);
						fruits.erase(it, fruits.end());

						// ��������� ����� ����� �� ����� �������
						add_fruit();

						// ��������� ������� � ���������� �����
						std::string score_str = "YOUR SCORE: " + std::to_string(player_score);

						SDL_FreeSurface(surface_score);
						surface_score = TTF_RenderText_Solid(score_font, score_str.c_str(), {255, 255, 255});

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

		// ������� ���������� ������������
		render();
	}
}

void Game::add_fruit()
{
	// �������� ��� ���� ����
	std::vector<Object> snake_tail = snake.get_snake_body();
	// ��������� �� ������ �������
	bool is_valid_position = false;

	// ����� �����
	Fruit *new_fruit = new Fruit;

	// ���� ������� �� ��������� (�� ���� ������� ������ ��������� � �������� ����)
	while (!is_valid_position)
	{
		is_valid_position = true;

		// ��������� ������� �������� ������ ����� ��� ������
		new_fruit->position.x = (float)(rand() % (background_cols - 1));
		new_fruit->position.y = (float)(rand() % (background_rows - 1) + (TOOLBAR_HEIGHT / SNAKE_SIZE));

		// ��������� �� ������ �� ��� ������ �����
		for (unsigned int i = 0; i < snake_tail.size(); ++i)
			if (snake_tail[i].get_pos() == utils::vector2f((float)(new_fruit->position.x * SNAKE_SIZE), (float)(new_fruit->position.y * SNAKE_SIZE)))
				is_valid_position = false;
	}

	// ������ �������� ���������� �� ������
	new_fruit->rect.x = (int)(new_fruit->position.x * SNAKE_SIZE);
	new_fruit->rect.y = (int)(new_fruit->position.y * SNAKE_SIZE);
	new_fruit->rect.w = new_fruit->rect.h = SNAKE_SIZE;

	// ��������� � ��������� �������
	fruits.push_back(new_fruit);
}

void Game::handle_click(Button *btn)
{
	if (btn == save_button)
	{
		// ����������� �������� ����
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);

		// ��������� ������ � ������������ � �������� ����������
		records.add_record(player_score, user_name_button->get_text());
		player_score = 0;
		generation_speed = 100;
		fruits.clear();
		snake = Snake(utils::vector2f(200, 200), (float)SNAKE_SIZE);

		menu = new Menu;

		if (menu->is_closing())
		{
			SDL_DestroyWindow(window);
			SDL_DestroyRenderer(renderer);
			SDL_Quit();
			game_running = false;
		}
		else
		{
			init();
		}

		return;
	}
}

// Показываем страницу с окончанием игры
void Game::show_gameover()
{

	score_font = TTF_OpenFont("arial.ttf", 1000);
	std::string scores = "YOUR SCORE: " + std::to_string(player_score);
	result_surface = TTF_RenderText_Solid(score_font, scores.c_str(), {255, 255, 255});
	result_texture = SDL_CreateTextureFromSurface(renderer, result_surface);
	result_rect = {300, 200, 200, 50};

	gameover_surface = TTF_RenderText_Solid(score_font, "Game Over", {255, 255, 255});
	gameover_texture = SDL_CreateTextureFromSurface(renderer, gameover_surface);
	gameover_rect = {125, 50, 550, 150};

	user_name_button = new Button({175, 300, 450, 100}, "", renderer);
	save_button = new Button({275, 425, 250, 70}, "Save", renderer);
	save_button->add_listener(this);

	while (true)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				SDL_DestroyWindow(window);
				SDL_DestroyRenderer(renderer);
				game_running = false;
				return;
			}

			if (event.type == SDL_TEXTINPUT)
			{
				user_name_button->set_text(user_name_button->get_text() + event.text.text, renderer);
			}

			if (save_button->update(event))
			{
				return;
			}
		}

		SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);
		SDL_RenderClear(renderer);

		user_name_button->render(renderer);
		save_button->render(renderer);

		SDL_RenderCopy(renderer, result_texture, NULL, &result_rect);
		SDL_RenderCopy(renderer, gameover_texture, NULL, &gameover_rect);

		SDL_RenderPresent(renderer);
	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);
	// ������� ����
	SDL_RenderClear(renderer);

	// ������� ������ ������ �����
	SDL_SetRenderDrawColor(renderer, 58, 180, 73, 255);
	for (unsigned int i = 0; i < background.size(); ++i)
		SDL_RenderFillRect(renderer, &background[i]);

	// ������� ������� ��� ���������� �����
	SDL_SetRenderDrawColor(renderer, 42, 130, 53, 255);
	SDL_RenderFillRect(renderer, &toolbar);

	// ������� ������
	for (auto fruit : fruits)
	{
		fruit->render(renderer);
	}

	// ������� ������
	snake.render(renderer);

	// ������� ���������� �����
	SDL_RenderCopy(renderer, score_texture, NULL, &score_rect_dest);

	SDL_RenderPresent(renderer);
}

void Game::controller(SDL_Event &event)
{
	// �������� �� �������
	while (SDL_PollEvent(&event))
	{
		// ������� �������� ����
		if (event.type == SDL_QUIT)
			game_running = false;

		// ���� ������ �����-�� �������
		if (event.type == SDL_KEYDOWN)
		{
			// � ����������� �� �������, ������ ����������� ������
			switch (event.key.keysym.sym)
			{
			case SDLK_UP:
			{
				// ��������� �� �������������� ��������, ����� �� ���� ������������
				if (snake.get_head_direction() == utils::directions::DOWN)
					break;

				snake.change_head_direction(utils::directions::UP);

				break;
			}
			case SDLK_DOWN:
			{
				if (snake.get_head_direction() == utils::directions::UP)
					break;

				snake.change_head_direction(utils::directions::DOWN);

				break;
			}
			case SDLK_LEFT:
			{
				if (snake.get_head_direction() == utils::directions::RIGHT)
					break;

				snake.change_head_direction(utils::directions::LEFT);

				break;
			}
			case SDLK_RIGHT:
			{
				if (snake.get_head_direction() == utils::directions::LEFT)
					break;

				snake.change_head_direction(utils::directions::RIGHT);

				break;
			}
			case SDLK_f:
			{
				snake.feed();
				break;
			}
			}
		}
	}
}