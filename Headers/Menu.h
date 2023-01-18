#pragma once

/// <summary>
/// ����� ��� ����������� ���� ����
/// </summary>
class Menu : public IEventListener
{
private:
	// ������ ����
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;

	// �������� ����
	const char* APPLICATION_NAME = "Snake Game";

	// ������������ �� ����
	bool menu_showing = true;
	bool close = false;

	// ��������� ����
	enum menuType
	{
		normal, // ������ �� ������, ������������ ��� ������
		new_game, // ��� ����� �� �������� ����� ����
		records, // ����������� ��������
		info, // ����������� ����������
		exit // ��� ����� �� �����
	};

	// ���������
	menuType type = menuType::normal;

	// ����� ��� ������
	TTF_Font* font = NULL;

#pragma region �����������, �������������� � �������� ��� ����������� ������� ����

	SDL_Surface* snake_surface = NULL;
	SDL_Rect snake_rect;
	SDL_Texture* snake_texture = NULL;

	SDL_Surface* records_surface = NULL;
	SDL_Rect records_rect;
	SDL_Texture* records_texture = NULL;

	SDL_Surface* scr;
	SDL_Surface* about_surface = NULL;
	SDL_Rect about_rect;

#pragma endregion

	// ������� ��� ������ �������� ������
	SDL_Surface *score_surfaces[5];
	SDL_Rect score_rect[5];
	SDL_Texture *score_textures[5];

	// ���� � ������
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	// ���� ������ ��� ��������������
	std::list<Button*> buttons;
	Button* button_esc;

public:
	Menu();
	~Menu();

	/// <summary>
	/// ����������� ����������� �� ������
	/// </summary>
	void render();

	/// <summary>
	/// ���������� ���������
	/// </summary>
	void show();

	/// <summary>
	/// ��������� �������
	/// </summary>
	/// <param name="event">�������</param>
	void controller(SDL_Event& event);

	/// <summary>
	/// ��������� ������� ������� �� ������
	/// </summary>
	/// <param name="btn">������, ������� ������� �������</param>
	void handle_click(Button* btn);

	/// <summary>
	/// ������� �� ����
	/// </summary>
	/// <returns></returns>
	bool is_closing();
};