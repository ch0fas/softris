#include <raylib.h>
#include <stdlib.h>
#include <time.h>

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
    int grid[4][4];
    Color color;
    int position_x;
    int position_y;
    int edge_l;
    int edge_r;
} Tetromino;



// -----
// Global Variable Declarations
// -----
const int screenWidth = 1200;
const int screenHeight = 900;
Tetromino currentPiece;

void InitGame(void)
{
    ClearBackground(WHITE);
    DrawText("Softris", 500, 100, 20, BLACK);
    DrawRectangle(0, 0, (GRID_CUBE_SIZE*BOARD_WIDTH), (GRID_CUBE_SIZE*BOARD_HEIGHT), LIGHTGRAY); // The tetris board
    for (int i = 1; (i < (BOARD_WIDTH+1)); i++)
    {
        for (int j = 1; (j < (BOARD_HEIGHT+1)); j++)
        {
            DrawLineV((Vector2){(GRID_CUBE_SIZE*i), 0},(Vector2){(GRID_CUBE_SIZE*i), 900}, BLACK); // Vertical Lines
            DrawLineV((Vector2){0, (GRID_CUBE_SIZE*j)},(Vector2){450, (GRID_CUBE_SIZE*j)}, BLACK); // Horizontal Lines
        }
    }
}


void DrawPiece(Tetromino current_piece)
{
    int new_positions[2] = {0,0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (current_piece.grid[j][i])
            {
                DrawRectangle(((current_piece.position_x+i)*GRID_CUBE_SIZE), ((current_piece.position_y+j)*GRID_CUBE_SIZE), GRID_CUBE_SIZE, GRID_CUBE_SIZE, current_piece.color);
            }
        }
    }
}

void rotatePiece_ccw(Tetromino *current_piece)
{
    int temp_matrix[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp_matrix[4-j-1][i] = current_piece->grid[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            current_piece->grid[i][j] = temp_matrix[i][j];
        }
    }
}

void rotatePiece_cw(Tetromino *current_piece)
{
    int temp_matrix[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            temp_matrix[j][4-i-1] = current_piece->grid[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            current_piece->grid[i][j] = temp_matrix[i][j];
        }
    }
}

int main(void)
{
    // Initialization
    InitWindow(screenWidth, screenHeight, "Softris - by ch0fas");
    SetWindowMonitor(0);

    SetTargetFPS(FPS);

    //Defining the standard tetrominos and their values
    Tetromino i_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,0,0},
            {1,1,1,1}
        },
        .color = BLUE,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 0,
        .edge_r = 0
    };

    Tetromino j_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {1,0,0,0},
            {1,1,1,0}
        },
        .color = DARKBLUE,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 0,
        .edge_r = 1
    };

    Tetromino l_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,0,1,0},
            {1,1,1,0}
        },
        .color = ORANGE,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 0,
        .edge_r = 1
    };

    Tetromino o_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0}
        },
        .color = PINK,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 1,
        .edge_r = 1
    };

    Tetromino s_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0}
        },
        .color = GREEN,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 0,
        .edge_r = 1
    };

    Tetromino z_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,1,0},
            {0,0,1,1}
        },
        .color = RED,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 1,
        .edge_r = 0
    };

    Tetromino t_tetromino =
    {
        .grid =
        {
            {0,0,0,0},
            {0,0,0,0},
            {0,1,0,0},
            {1,1,1,0}
        },
        .color = PURPLE,
        .position_x = 0,
        .position_y = 0,
        .edge_l = 0,
        .edge_r = 1
    };

    // Making an array of all the pieces for easy access
    Tetromino pieces[] = {i_tetromino, j_tetromino, l_tetromino, o_tetromino, s_tetromino, z_tetromino, t_tetromino};

    srand(time(NULL));
    //Tetromino current_piece = pieces[rand()%7];
    Tetromino current_piece = pieces[0];

    // Main Game Loop
    while (!WindowShouldClose())
    {
        // Controls
        if (IsKeyPressed(KEY_RIGHT)) current_piece.position_x++;
        if (IsKeyPressed(KEY_LEFT)) current_piece.position_x--;
        if (IsKeyPressed(KEY_DOWN)) current_piece.position_y++;
        if (IsKeyPressed(KEY_UP)) current_piece.position_y = BOARD_HEIGHT-4;
        if (IsKeyPressed(KEY_X)) rotatePiece_ccw(&current_piece);
        if (IsKeyPressed(KEY_C)) rotatePiece_cw(&current_piece);

        //Piece Rotation

        // Checking the pieces dont go OOB
        if ((current_piece.position_x+current_piece.edge_l) < 0)
        {
            current_piece.position_x = 0 - current_piece.edge_l;
        } else if (current_piece.position_x + 3 - current_piece.edge_r >= (BOARD_WIDTH)) {
            current_piece.position_x = (BOARD_WIDTH-3)+current_piece.edge_r-1;
        }

        BeginDrawing();
            InitGame();
            DrawPiece(current_piece);
        EndDrawing();
    }

    //De-initializing
    CloseWindow();

    return 0;
}
