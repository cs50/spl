// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// brick properties
#define BRICK_SPACING 5
#define BRICK_WIDTH (WIDTH - BRICK_SPACING * COLS) / COLS
#define BRICK_HEIGHT HEIGHT / 40

void initBricks(GWindow window);
            
int main(void)
{
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
    setBackground(window, "red");
    setForeground(window, "black"); // set default obj color to black
    initBricks(window);
    return 0;
}

/**
 *  * Initializes window with a grid of bricks.
 *   */
void initBricks(GWindow window)
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            GRect brick = newGRect(
                    BRICK_SPACING + (BRICK_WIDTH + BRICK_SPACING) * col, 
                    BRICK_SPACING + (BRICK_HEIGHT + BRICK_SPACING) * row, 
                    BRICK_WIDTH, BRICK_HEIGHT
                    );
            //setColor(brick, "blue");
            setFilled(brick, true);
            add(window, brick);
        }
    }
}


