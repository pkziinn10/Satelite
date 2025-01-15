#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib> // Para gerar números aleatórios
#include <ctime>   // Para inicializar a semente do gerador de números
#include <math.h>
#include "camera.h"
#include "sistemasolar.h"  // Incluindo o cabeçalho do sistema solar
#include "satelite.h"     // Incluindo o cabeçalho da Terra e Lua

int renderMode = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    setCamera(); // Configura a câmera antes de desenhar

    if (renderMode == 1) {
        desenhaSistemaSolar(); // Desenha o Sistema Solar
    } else if (renderMode == 2) {
        desenhaTerraELua(); // Desenha a Terra com a Lua orbitando
    }

    glDisable(GL_DEPTH_TEST);
}

void processInput(GLFWwindow* window) {
    float cameraSpeed = 0.5f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPos.y += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPos.y -= cameraSpeed;

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
    // Inicialização do GLFW
    if (!glfwInit()) return -1;

    // Criação da janela
    GLFWwindow* window = glfwCreateWindow(800, 800, "Sistema Solar e Lua orbitando a Terra", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Contexto OpenGL
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Inicialização do sistema solar e das estrelas
    inicializaSistemaSolar(); // Gera as estrelas e inicializa o sistema solar
    inicializaSatelite(); // Gera as estrelas e inicializa o satelite
    // Configuração da câmera
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        processInput(window); // Processa entradas do teclado

        display(); // Chama a função para renderizar o conteúdo

        glfwSwapBuffers(window); // Troca os buffers para mostrar a renderização
        glfwPollEvents(); // Processa eventos (como teclados, mouse, etc.)
    }

    // Finaliza o GLFW
    glfwTerminate();
    return 0;
}
