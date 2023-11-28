#include <iostream>
#include <raylib.h>
const int game_width = 1280;
const int game_hight = 800;
int player_score = 0;
int Cpu_score = 0;
int ball_paddle_bounce = 0;
bool isgameover = false;
class Ball
{
public:
    int speed_x = 5;
    int speed_y = 5;
    const int radius = 10;
    int x = game_width / 2;
    int y = game_hight / 2;
    void gamereset()
    {
        x = game_width / 2;
        y = game_hight / 2;
        speed_x = 5;
        speed_y = 5;
    }
    void draw()
    {
        DrawCircle(x, y, radius, WHITE);
    }
    void update()
    {
        x += speed_x;
        y += speed_y;
        if (y + radius >= game_hight || y + radius <= 0)
        {
            speed_y *= -1;
        }
        if (x + radius >= game_width)
        {
            player_score++;
            gamereset();
        }
        if (x + radius <= 0)
        {
            Cpu_score++;
            gamereset();
        }
    }
};
Ball ball;
class Paddle
{
public:
    int width = 10;
    int x = width;
    int speed = 9;
    int length = 100;
    int y = game_hight / 2 - length / 2;
    void paddle_collision()
    {
        if (y <= 0)
        {
            y = 0;
        }
        if (y >= game_hight - length)
        {
            y = game_hight - length;
        }
    }
    void draw()
    {
        DrawRectangle(x, y, width, length, WHITE);
    }
    void update()
    {
        if (IsKeyDown(KEY_W))
        {
            y = y - speed;
            paddle_collision();
        }
        if (IsKeyDown(KEY_S))
        {
            y = y + speed;
            paddle_collision();
        }
    }
};
Paddle player;
class computer : public Paddle
{
public:
    int cpu_x = game_width - 2 * width;
    int cpu_y = game_hight / 2 - length / 2;
    void draw()
    {
        DrawRectangle(cpu_x, cpu_y, width, length, WHITE);
    }
    void update()
    {
        if (cpu_y + length / 2 > ball.y)
        {
            cpu_y -= speed;
            paddle_collision();
        }
        if (cpu_y + length / 2 < ball.y)
        {
            cpu_y += speed;
            paddle_collision();
        }
    }
};
computer cpu;
void collision()
{
    if ((ball.x >= player.x && ball.x <= player.x + player.width) && (ball.y >= player.y && ball.y <= (player.y + player.length)))
    {
        ball.speed_x *= -1;
        ball_paddle_bounce++;
    }
    if (ball.x >= cpu.cpu_x && (ball.y >= cpu.cpu_y && ball.y <= (cpu.cpu_y + cpu.length)))
    {
        ball.speed_x *= -1;
    }
}
void game_difficulty()
{
    if (ball_paddle_bounce == 5)
    {
        ball.speed_x++;
        ball.speed_x++;
        ball_paddle_bounce = 0;
    }
}
void Game_Over()
{
    if (player_score >= 3 || Cpu_score >= 3)
    {
        if (player_score >= 3)
        {
            ClearBackground(BLACK);
            DrawText("Game Over !!!", (game_width) / 4, game_hight / 3, 100, GREEN);
            DrawText("Player Won ", (game_width) / 4, game_hight / 2, 100, GREEN);
        }
        if (Cpu_score >= 3)
        {
            ClearBackground(BLACK);
            DrawText("Game Over !!!", (game_width) / 4, game_hight / 3, 100, RED);
            DrawText("Cpu Won ", (game_width) / 4, game_hight / 2, 100, RED);
        }
        isgameover = true;
    }
    else
    {
        isgameover = false;
    }
}

int main()
{
    InitWindow(game_width, game_hight, "Pong");
    SetTargetFPS(60);
    while (WindowShouldClose() == false)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        if (isgameover == false)
        {
            ball.draw();
            player.draw();
            cpu.draw();
            DrawLine(game_width / 2, 0, game_width / 2, game_hight, WHITE);
            ball.update();
            DrawText(TextFormat("%i", player_score), game_width / 4, 20, 60, WHITE);
            DrawText(TextFormat("%i", Cpu_score), (3 * game_width) / 4, 20, 60, WHITE);
            player.update();
            cpu.update();
            collision();
            game_difficulty();
            Game_Over();
        }
        Game_Over();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}