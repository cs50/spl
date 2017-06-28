//
// breakout.c
//
// David J. Malan
// malan@harvard.edu
//

// standard libraries
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// height of a brick in pixels
#define BRICK_HEIGHT 10

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// gap between bricks in pixels
#define GAP 5

// height and width of paddle
#define PADDLE_WIDTH 60
#define PADDLE_HEIGHT 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// margin above bricks and below paddle
#define MARGIN 50

// how many milliseconds to wait after ball's moved before moving again
#define NAPTIME 10

// how many different colors we have for the rows of bricks
#define NUM_COLORS 5

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(int argc, char* argv[])
{
    printf("v.2.0\n");

    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
        // wait for click to begin
        waitForClick();

        // decrement lives
        lives--;

        // center ball
        setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 - RADIUS);

        // generate random horizontal velocity for ball in [1.0, 2.0)
        double vx = drand48() + 1.0;

        // invert direction with 50/50 probability
        if (drand48() < 0.5)
        {
            vx = -vx;
        }

        // vertical velocity of ball
        double vy = 5.0;

        // while bricks remain and the ball's not missed the paddle
        while (bricks > 0 && getY(ball) < HEIGHT - 2 * RADIUS)
        {
    
            // check for mouse event
            /*GEvent e = getNextEvent(MOUSE_EVENT);*/
            GEvent e = getNextEvent(MOUSE_EVENT);

            // if we heard one
            
            if (e != NULL)
            {
                // if the event was movement
                if (getEventType(e) == MOUSE_MOVED)
                {
                    // keep paddle centered with cursor, unless at edge
                    double px = getX(e) - PADDLE_WIDTH / 2;
                    if (px < 0)
                    {
                        px = 0;
                    }
                    else if (px > WIDTH - PADDLE_WIDTH)
                    {
                        px = WIDTH - PADDLE_WIDTH;
                    }
                    setLocation(paddle, px, getY(paddle));
                }
                freeEvent(e);
            }

            // if we didn't
            else
            {

                // move ball
                move(ball, vx, vy);

                // if ball's at left or right edge, bounce
                if (getX(ball) < 0 || getX(ball) > WIDTH - 2 * RADIUS)
                {
                    vx = -vx;
                }

                // if ball's at top edge, bounce
                if (getY(ball) < 0)
                {
                    vy = -vy;
                }

                // check whether ball's collided with anything
                GObject object = detectCollision(window, ball);
                if (object != NULL)
                {
                    // if ball's collided with paddle, bounce
                    if (object == paddle)
                    {
                        vy = -vy;
                        setLocation(ball, getX(ball), getY(paddle) - 2 * RADIUS);
                    }

                    // if ball's collided with brick
                    else if (strcmp(getType(object), "GRect") == 0)
                    {
                        // remove brick from window
                        removeGWindow(window, object);

                        // decrement counter
                        bricks--;

                        // increment points
                        points++;

                        // update scoreboard
                        updateScoreboard(window, label, points);

                        // bounce
                        vy = -vy;
                    }
                }

                // slow down animation
                /*pause(NAPTIME);*/
            }
        }
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    // determine width of each brick
    double width = (WIDTH - GAP * COLS) / COLS;

    string colors[NUM_COLORS] = {"RED", "ORANGE", "YELLOW", "GREEN", "CYAN"};

    // for each row
    for (int row = 0; row < ROWS; row++)
    {
        // determine vertical position of brick
        double y = MARGIN + row * (BRICK_HEIGHT + GAP);

        // for each column
        for (int col = 0; col < COLS; col++)
        {
            // determine horizontal position of brick
            double x = GAP / 2 + col * (width + GAP);

            // instantiate brick
            GRect brick = newGRect(x, y, width, BRICK_HEIGHT);

            // set brick's color
            setColor(brick, colors[row % NUM_COLORS]);

            // fill brick with color
            setFilled(brick, true);

            // add brick to window
            add(window, brick);
        }
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    double bx = WIDTH / 2 - RADIUS;
    double by = HEIGHT / 2 - RADIUS;
    GOval ball = newGOval(bx, by, 2 * RADIUS, 2 * RADIUS);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    double x = (WIDTH - PADDLE_WIDTH) / 2;
    double y = HEIGHT - PADDLE_HEIGHT - MARGIN;
    GRect paddle = newGRect(x, y, PADDLE_WIDTH, PADDLE_HEIGHT);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    add(window, paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setColor(label, "LIGHT_GRAY");
    setFont(label, "arial-48");
    add(window, label);
    sendToBack(label);
    updateScoreboard(window, label, 0);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
