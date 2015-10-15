#include "game.h"
#include "Shaders.h"

using namespace u_engine;

u_engine::graphics::Window* Game::WindowHandle = nullptr;


Game::Game()
	: Application("ChernoCraft", 960, 540)
{
}

void Game::init()
{
	Application::init();

	WindowHandle = window;
	Shaders::Init();
	Texture::LOAD();
	m_Level = new Level();


}

Game::~Game()
{
	delete m_Level;
}

void Game::update()
{
	m_Level->update();
}

void Game::render()
{
	m_Level->render();
}