#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib> // Para gerar números aleatórios
#include <ctime>   // Para inicializar a semente do gerador de números
#include <math.h>

int renderMode = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    setCamera();

    drawSolarSystem();
    glDisable(GL_DEPTH_TEST);
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
        renderMode = 1; // Mudar para o Sistema Solar
    }

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
        renderMode = 2; // Mudar para a Lua orbitando a Terra
    }
}

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 800, "Sistema Solar e Lua Orbitando a Terra", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        if (renderMode == 1) {
            drawSolarSystem();
        } else if (renderMode == 2) {
            drawMoonOrbitingEarth();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
