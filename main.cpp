#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
unsigned int drawValue = GL_LINE_LOOP;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int WINDOW_WIDTH = 0;
int WINDOW_HEIGHT = 0;
bool vertexMoving = false;
int vertexIndex = 0;
int threshold = 10;
double positions[8] = {
        300, 200,
        300, 300,
        400, 300,
        400, 200
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
    if(button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            //getting cursor position
            glfwGetCursorPos(window, &xpos, &ypos);
            ypos = WINDOW_HEIGHT - ypos;
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
        positions[2* vertexIndex] = xpos;
        positions[2* vertexIndex + 1] = ypos;
    }
}
int main() {
    GLFWwindow* window;
    if (!glfwInit())
        cout << "Hello, World!" << std::endl;
    auto* mode = const_cast<GLFWvidmode *>(glfwGetVideoMode(glfwGetPrimaryMonitor()));
    SCREEN_WIDTH = mode->width;
    SCREEN_HEIGHT = mode->height;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window, &WINDOW_WIDTH, &WINDOW_HEIGHT);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
//    glMatrixMode(GL_PROJECTION);
    glewInit();
    if (!window) {
        cout << "window wasnt created";
    }
    GLuint buffer;
    while (!glfwWindowShouldClose(window)) {
//        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_DOUBLE, 0, positions);
        glDrawArrays(drawValue, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    cout << "Finished";
    return 0;
}