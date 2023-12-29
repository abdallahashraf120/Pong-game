#include <GL/glut.h>
#include <stdbool.h>


int score_left = 0, score_right = 0; // Declare score variables
float ball_x = 0.0, ball_y = 0.0, ball_dx = 0.02, ball_dy = 0.02; // Even slower ball speed
float paddle_left_y = 0.0, paddle_right_y = 0.0;
const float paddle_height = 0.3; // Slower right paddle speed
const float paddle_speed = 0.1; // Slower right paddle speed

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // Set the background color to white
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the ball
    glColor3f(0.0, 0.0, 0.0); // Set the color to black
    glBegin(GL_QUADS);
    glVertex2f(ball_x - 0.05, ball_y + 0.05);
    glVertex2f(ball_x - 0.05, ball_y - 0.05);
    glVertex2f(ball_x + 0.05, ball_y - 0.05);
    glVertex2f(ball_x + 0.05, ball_y + 0.05);
    glEnd();

    // Draw the left paddle
    glColor3f(0.0, 1.0, 1.0); // Set the color to cyan
    glBegin(GL_QUADS);
    glVertex2f(-1.0, paddle_left_y + paddle_height);
    glVertex2f(-1.0, paddle_left_y - paddle_height);
    glVertex2f(-0.9, paddle_left_y - paddle_height);
    glVertex2f(-0.9, paddle_left_y + paddle_height);
    glEnd();

    // Draw the right paddle
    glColor3f(0.0, 1.0, 1.0); // Set the color to cyan
    glBegin(GL_QUADS);
    glVertex2f(0.9, paddle_right_y + paddle_height);
    glVertex2f(0.9, paddle_right_y - paddle_height);
    glVertex2f(1.0, paddle_right_y - paddle_height);
    glVertex2f(1.0, paddle_right_y + paddle_height);
    glEnd();

    glutSwapBuffers();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    // Update the ball position
    ball_x += ball_dx;
    ball_y += ball_dy;

    // Collision detection with the paddles
    if(ball_x - 0.05 < -0.9 && ball_y < paddle_left_y + paddle_height && ball_y > paddle_left_y - paddle_height)
        ball_dx = -ball_dx;
    else if(ball_x - 0.05 < -0.9)
        exit(0); // End the game if the ball hits the left edge without hitting the paddle

    if(ball_x + 0.05 > 0.9 && ball_y < paddle_right_y + paddle_height && ball_y > paddle_right_y - paddle_height)
        ball_dx = -ball_dx;
    else if(ball_x + 0.05 > 0.9)
        exit(0); // End the game if the ball hits the right edge without hitting the paddle

    // Collision detection with the top and bottom of the window
    if(ball_y + 0.05 > 1.0 || ball_y - 0.05 < -1.0)
        ball_dy = -ball_dy;

    // Update the right paddle position to follow the ball
    if(ball_y > paddle_right_y)
        paddle_right_y += paddle_speed;
    if(ball_y < paddle_right_y)
        paddle_right_y -= paddle_speed;

}


void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w':
            paddle_left_y += paddle_speed;
            break;
        case 's':
            paddle_left_y -= paddle_speed;
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Pong Game");

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
