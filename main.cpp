#include <GL/glew.h>
//#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
unsigned int drawValue = GL_LINE_LOOP;
float positions[8] = {
        427, 284430,
        200, 300,
        150, 200,
        200, 250
};
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        drawValue = drawValue == GL_LINE_LOOP ? GL_POLYGON : GL_LINE_LOOP;
        positions[0] = 0.0f;
    }
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)

}
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    cout << xpos << " " << ypos;
}
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
int main() {
    GLFWwindow* window;
    if (!glfwInit())
        cout << "Hello, World!" << std::endl;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello world!!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glewInit();
    if (!window) {
        cout << "window wasnt created";
    }
    GLuint buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(float), 0);
    while (!glfwWindowShouldClose(window)) {
//        glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_DYNAMIC_DRAW);
        glClear(GL_COLOR_BUFFER_BIT);
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_FLOAT, 0, positions);
        glDrawArrays(drawValue, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    cout << "Finished";
    return 0;
}