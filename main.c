#include <raylib.h>

// Important Defines
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define GRID_CUBE_SIZE 45
#define FPS 60

// -----
// Module Functions
// -----
static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

// -----
// Types and Structures Definitions
// -----
typedef struct Tetrimino
{
    Vector4 upperBlocks;
    Vector4 lowerBlocks;
    Color color;
} Tetrimino;

// -----
// Global Variable Declarations
// -----
const int screenWidth = 1200;
const int screenHeight = 900;

Color tetriminoColors[] = {RED, PINK, LIME, BLUE, VIOLET, MAGENTA};

int main(void)
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Softris - by ch0fas");
    SetWindowMonitor(0);

    SetTargetFPS(FPS);

    // Main Game Loop
    while (!WindowShouldClose())
    {
        // Variable updating here

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Fun colors and shapes, the video game", 100, 100, 20, WHITE);
            DrawRectangle(0, 0, (GRID_CUBE_SIZE*BOARD_WIDTH), (GRID_CUBE_SIZE*BOARD_HEIGHT), LIGHTGRAY); // The tetris board
        EndDrawing();
    }

    //De-initializing
    CloseWindow();

    return 0;
}