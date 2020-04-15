#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
unsigned int drawValue = GL_LINE_LOOP;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int SCREEN_MAX_WIDTH = 0;
int SCREEN_MAX_HEIGHT = 0;
int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;
int WINDOW_POS_X = 0;
int WINDOW_POS_Y = 0;
bool vertexMoving = false;
int vertexIndex = 0;
int threshold = 30;
double positions[8] = {
        200, 100,
        200, 300,
        500, 300,
        500, 100
};
bool distanceMeasure(double x1, double y1, double x2, double y2) {
    return (abs(x1 - x2) < threshold) && (abs(y1 - y2) < threshold);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        drawValue = drawValue == GL_LINE_LOOP ? GL_POLYGON : GL_LINE_LOOP;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    double xpos, ypos;
    //getting cursor position
    glfwGetCursorPos(window, &xpos, &ypos);
    xpos = (xpos * SCREEN_MAX_WIDTH) / WINDOW_WIDTH;
    ypos = (WINDOW_HEIGHT - ypos) * SCREEN_MAX_HEIGHT / WINDOW_HEIGHT;
//    ypos = WINDOW_HEIGHT - ypos;
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS) {
            for (int i = 0; i < 4; i++) {
                if (distanceMeasure(positions[2 * i], positions[2 * i + 1], xpos, ypos)) {
                    vertexMoving = true;
                    vertexIndex = i;
                }
            }
        } else {
            vertexMoving = false;
        }
    }
}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (vertexMoving) {
        ypos = WINDOW_HEIGHT - ypos;
        positions[2* vertexIndex] = (xpos * SCREEN_MAX_WIDTH) / WINDOW_WIDTH;;
        positions[2* vertexIndex + 1] = (ypos) * SCREEN_MAX_HEIGHT / WINDOW_HEIGHT;;
    }
}
int main() {

    GLFWwindow* window;
    if (!glfwInit())
        cout << "GLFW is not configured!!" << std::endl;
    auto* mode = const_cast<GLFWvidmode *>(glfwGetVideoMode(glfwGetPrimaryMonitor()));
    SCREEN_WIDTH = mode->width;
    SCREEN_HEIGHT = mode->height;
    SCREEN_MAX_WIDTH = mode->width - 50;
    SCREEN_MAX_HEIGHT = mode->height - 50;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "HW1 9531036", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetCursorPosCallback(window, cursor_position_callback);
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glewInit();
    if (!window) {
        cout << "window wasnt created";
    }
    GLuint buffer;
    while (!glfwWindowShouldClose(window)) {
        glfwGetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
        glfwGetWindowPos(window, &WINDOW_POS_X, &WINDOW_POS_Y);
        glViewport(0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.5,0.5,0.2,1);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_DOUBLE, 0, positions);
        glColor3f(0.1, 0.8, 0.7);
        glDrawArrays(drawValue, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    cout << "Finished";
    return 0;
}