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
/// �����, ����������� ������ ����
/// </summary>
class Game : IEventListener{
private:
	// ������ ������
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	// �������� ����
	const char* APPLICATION_NAME = "Snake Game";

	// ������ ����
	const unsigned int SNAKE_SIZE = 40;

	// ���� � ������
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// ������ ���� (�������� ��� ���)
	bool game_running = true;

	// ������
	Snake snake;

	Menu* menu = NULL;

	// ������� ������������
	RecordsData records;

	// ������ � ������ ������� ����
	unsigned int background_rows, background_cols;

	// ������, ���������� �������������� ���� ������ ������� ����
	std::vector<SDL_Rect> background;

	// ������������� ��� ������ �����
	SDL_Rect toolbar;
	const unsigned int TOOLBAR_HEIGHT = 40;

	// ������
	std::vector<Fruit*> fruits;

	// �������� ��������� ����� �������
	int generation_speed = 100;

#pragma region �����������, �������������, ��������, ����� ��� ������ ���������� �����

	SDL_Surface* surface_score = NULL;
	SDL_Rect score_rect_dest;
	SDL_Texture* score_texture = NULL;

	SDL_Surface* gameover_surface = NULL;
	SDL_Rect gameover_rect;
	SDL_Texture* gameover_texture = NULL;

	SDL_Surface* result_surface = NULL;
	SDL_Rect result_rect;
	SDL_Texture* result_texture = NULL;

	TTF_Font* score_font = NULL;
	const unsigned int FONT_SCORE_SIZE = 15;

	Button* user_name_button;
	Button* save_button;

#pragma endregion

	// ���������� ����� ������
	unsigned int player_score = 0;

public:
	Game();
	~Game();

	void init();

	/// <summary>
	/// ������� ������� ����
	/// </summary>
	void game_loop();

	/// <summary>
	/// ����� �����������
	/// </summary>
	void render();

	/// <summary>
	/// ��������� ������� �� �������
	/// </summary>
	/// <param name="event">������� �������</param>
	void controller(SDL_Event& event);

	/// <summary>
	/// �������� ����� ����� �� ����
	/// </summary>
	void add_fruit();

	void show_gameover();

	void handle_click(Button* btn);
};