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
typedef struct Tetromino
{
    Vector4 upperBlocks;
    Vector4 lowerBlocks;
    Color color;
} Tetromino;



// -----
// Global Variable Declarations
// -----
const int screenWidth = 1200;
const int screenHeight = 900;

void InitGame(void)
{
    ClearBackground(WHITE);
    DrawText("Fun colors and shapes, the video game", 100, 100, 20, BLACK);
    DrawRectangle(0, 0, (GRID_CUBE_SIZE*BOARD_WIDTH), (GRID_CUBE_SIZE*BOARD_HEIGHT), LIGHTGRAY); // The tetris board
    for (int i = 1; (i < (BOARD_WIDTH+1)); i++)
    {
        for (int j = 1; (j < (BOARD_HEIGHT+1)); j++)
        {
            DrawLineV((Vector2){(GRID_CUBE_SIZE*i), 0},(Vector2){(GRID_CUBE_SIZE*i), 900}, BLACK); // Vertical Line
            DrawLineV((Vector2){0, (GRID_CUBE_SIZE*j)},(Vector2){450, (GRID_CUBE_SIZE*j)}, BLACK); // Vertical Line
        }
    }
}

int main(void)
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Softris - by ch0fas");
    SetWindowMonitor(0);

    SetTargetFPS(FPS);

    //Defining the tetrominos and their values
    Tetromino i_tetromino; // I-tetromino
    i_tetromino.upperBlocks = (Vector4){0,0,0,0};
    i_tetromino.lowerBlocks = (Vector4){1,1,1,1};
    i_tetromino.color = BLUE;

    Tetromino j_tetromino; // J-tetromino
    j_tetromino.upperBlocks = (Vector4){1,0,0,0};
    j_tetromino.lowerBlocks = (Vector4){1,1,1,0};
    j_tetromino.color = DARKBLUE;

    Tetromino l_tetromino; // L-tetromino
    l_tetromino.upperBlocks = (Vector4){0,0,1,0};
    l_tetromino.lowerBlocks = (Vector4){1,1,1,0};
    l_tetromino.color = ORANGE;

    Tetromino o_tetromino; // O-tetromino
    o_tetromino.upperBlocks = (Vector4){0,1,1,0};
    o_tetromino.lowerBlocks = (Vector4){0,1,1,0};
    o_tetromino.color = YELLOW;

    Tetromino s_tetromino; // S-tetromino
    s_tetromino.upperBlocks = (Vector4){0,1,1,0};
    s_tetromino.lowerBlocks = (Vector4){1,1,0,0};
    s_tetromino.color = DARKGREEN;

    Tetromino z_tetromino; // Z-Tetromino
    z_tetromino.upperBlocks = (Vector4){1,1,0,0};
    z_tetromino.lowerBlocks = (Vector4){0,1,1,0};
    z_tetromino.color = RED;

    Tetromino t_tetromino; // T-tetromino
    t_tetromino.upperBlocks = (Vector4){0,1,0,0};
    t_tetromino.lowerBlocks = (Vector4){1,1,1,0};
    t_tetromino.color = PURPLE;

    // Making an array of all the pieces for easy access
    Tetromino pieces[] = {i_tetromino, j_tetromino, l_tetromino, o_tetromino, s_tetromino, z_tetromino, t_tetromino};



    // Main Game Loop
    while (!WindowShouldClose())
    {
        // Variable updating here

        BeginDrawing();
            InitGame();
        EndDrawing();
    }

    //De-initializing
    CloseWindow();

    return 0;
}