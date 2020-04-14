#include <GL/glew.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;
int main() {
    GLFWwindow* window;
    if (!glfwInit())
        cout << "Hello, World!" << std::endl;
    glewInit();
    cout << "ready to start...";
    return 0;
}
