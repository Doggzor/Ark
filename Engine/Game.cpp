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
    walls(Vec2(120.0f, 30.0f), Vec2(680.0f, (float)gfx.ScreenHeight)),
    ball(Vec2(150.0f, 300.0f), Vec2(1.0f, 1.0f), 450.0f),
    pad(Vec2(400.0f, 550.0f), 50.0f, 10.0f, 450.0f)
{
    Color bcolors[5] = { Colors::Cyan, Colors::Red, Colors::Blue, Colors::Orange, Colors::Green };

    for (int y = 0; y < bricksDown; y++)
    {
        Color c = bcolors[y];
        for (int x = 0; x < bricksAcross; x++)
        {
            if ((y * bricksAcross + x) % 5 == 2)
            {
                bricks[y * bricksAcross + x] = Brick(RectF((Vec2(walls.left, walls.top) + bricksOffset + Vec2(x * brickW, y * brickH)), brickW, brickH), c, 1, false);
            }
            else
                bricks[y * bricksAcross + x] = Brick(RectF((Vec2(walls.left, walls.top) + bricksOffset + Vec2(x * brickW, y * brickH)), brickW, brickH), c, 1);
        }
    }
}

void Game::Go()
{
	gfx.BeginFrame();
    float ElapsedTime = ft.Mark();
    while (ElapsedTime > 0.0f)
    {
        const float dt = std::min(0.0025f, ElapsedTime);
        UpdateModel(dt);
        ElapsedTime -= dt;
    }
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
    if (!pad.bGameOver && !bGameWon)
    {
        //Paddle
        pad.Update(wnd.kbd, walls, dt);
        pad.BallCollision(ball);

        //Bricks
        int curBrickIndex;
        float curDistSq;
        bool ColHappened = false;

        for (int i = 0; i < nBricks; i++)
        {
            if (bricks[i].CheckBallCollision(ball))
            {
                const float newDistSq = (ball.GetRect().GetCenter() - bricks[i].GetCenter()).GetLengthSq();
                if (ColHappened)
                {
                    if (newDistSq < curDistSq)
                    {
                        curDistSq = newDistSq;
                        curBrickIndex = i;
                    }
                }
                else
                {
                    ColHappened = true;
                    curDistSq = newDistSq;
                    curBrickIndex = i;
                }
            }
        }
        if (ColHappened)
        {
            bricks[curBrickIndex].ExecutekBallCollision(ball);
            pad.ResetCoolDown();
        }



        //Ball
        if (wnd.kbd.KeyIsPressed(VK_SPACE)) ball.launch();
        ball.Update(pad.GetRect(), dt);
        if (ball.WallBounce(walls)) pad.ResetCoolDown();
        if ((ball.GetRect().GetCenter().y > pad.GetRect().top && ball.GetRect().GetCenter().y < pad.GetRect().bottom) &&
            ((ball.GetRect().left <= (walls.left + wallThickness + 1.0f) && pad.GetRect().left <= (walls.left + wallThickness + 1.0f))
                || (ball.GetRect().right >= (walls.right - wallThickness - 1.0f) && pad.GetRect().right >= (walls.right - wallThickness - 1.0f))))
        {
            ball.SetPY(pad.GetRect().bottom + ball.GetRadius() + 3.0f); //Prevent the ball from being squished to the wall by the paddle
        }                                                               //(using a huge ass line of code)
    }

    //Check if Game is won
    bGameWon = true;
    for (int i = 0; i < nBricks; i++)
    {
        if (!bricks[i].DestroyedIfPossible())
        {
            bGameWon = false;
            break;
        }
    }

}

void Game::ComposeFrame()
{
    //Draw Border
    const int wx = (int)(walls.left - wallThickness);
    const int wy = (int)(walls.top - wallThickness);
    const int wwidth = (int)(walls.right - walls.left + wallThickness * 2);
    const int wheight = (int)(walls.bottom - walls.top + wallThickness);
    gfx.DrawRectEmpty(wx, wy, wwidth, wheight, wallThickness, Colors::Magenta);
    //Draw Lifes
    pad.DrawLives(gfx);
    if (!pad.bGameOver && !bGameWon)
    {
        pad.Draw(gfx);
        for (const auto& b : bricks) b.Draw(gfx);
        ball.Draw(gfx);
    }
    else if (pad.bGameOver) Images::GameLost(310, 280, gfx);
    else Images::GameWon(320, 280, gfx);
}
