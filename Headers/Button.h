#pragma once

#include <string>
#include <list>

class Button;

/// <summary>
/// ������������ �����, ����������� ������� "���������"
/// </summary>
class IEventListener {
protected:
	IEventListener() {};

public:
	/// <summary>
	/// ��������� ������� �� ������
	/// </summary>
	/// <param name="button">������, ������� ������� ��� �������</param>
	virtual void handle_click(Button* button) = 0;
};

class Button {
private:
	// ������������� ������
	SDL_Rect rect;
	// ������������� ��� ������
	SDL_Rect rect_text;

	// �����������, �������� � ����� ��� ������
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
	TTF_Font* font = NULL;

	std::vector<IEventListener*> listeners;

public:
	/// <summary>
	/// ����������� ������� ������ 
	/// </summary>
	/// <param name="rect">������ � ���������</param>
	/// <param name="text">����� ��� �����������</param>
	/// <param name="renderer">������</param>
	Button(SDL_Rect rect, std::string text, SDL_Renderer* renderer);

	/// <summary>
	/// ���������� ���������
	/// </summary>
	/// <param name="event">������� SDL</param>
	void update(SDL_Event& event);

	/// <summary>
	/// ����� �� �����
	/// </summary>
	/// <param name="renderer">������</param>
	void render(SDL_Renderer* renderer);

	/// <summary>
	/// �������� ��������� �������
	/// </summary>
	/// <param name="lisener">���������</param>
	void add_listener(IEventListener* lisener);

	/// <summary>
	/// ���������� ���������� � ������� 
	/// </summary>
	void notify_listener();
};