#pragma once

#include <app/Application.h>
#include "level/level.h"

class Game : public u_engine::Application
{
public:
	static u_engine::graphics::Window* WindowHandle;
private:
	Level* m_Level;
public:
	Game();
	~Game();

	void init() override;
	void update() override;
	void render() override;

};