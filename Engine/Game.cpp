/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    walls(0.0f, (float)gfx.ScreenHeight, 0.0f, (float)gfx.ScreenWidth),
    ball(Vec2(300.0f, 200.0f), Vec2(300.0f, 300.0f)),
    pad(Vec2(350.0f, 500.0f), 50.0f, 15.0f, 450.0f)
{
    Color bcolors[4] = { Colors::Cyan, Colors::Red, Colors::Blue, Colors::Orange };

    for (int y = 0; y < bricksDown; y++)
    {
        Color c = bcolors[y];
        for (int x = 0; x < bricksAcross; x++)
        {
            bricks[y * bricksAcross + x] = Brick(RectF((bricksOffset + Vec2(x*brickW, y*brickH)), brickW, brickH), c);
        }
    }
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    const float dt = ft.Mark();
    //Paddle
    pad.Update(wnd.kbd, walls, dt);
    pad.BallCollision(ball);

    //Bricks
    for (auto& b : bricks) b.BallCollision(ball);

    //Ball
    ball.Update(dt);
    ball.clampscreen(walls);
}

void Game::ComposeFrame()
{
    pad.Draw(gfx);
    for (const Brick& b : bricks) b.Draw(gfx);
    ball.Draw(gfx);
}
