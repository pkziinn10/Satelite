#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <filesystem>
#include "camera.h"
#include "textura.h"
#include "sistemasolar.h"
#include "satelite.h"
#include "stb_image.h"

int renderMode = 1;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    setCamera(); // Configura a câmera antes de desenhar

    if (renderMode == 1) {
        desenhaSistemaSolar();
    } else if (renderMode == 2) {
        desenhaTerraELua();
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

    // Carregar as texturas
    GLuint solTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/sun.jpg");
    GLuint mercurioTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/mercury.jpg");
    GLuint venusTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/venus.jpg");
    GLuint terraTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/earth.jpg");
    GLuint marteTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/mars.jpg");
    GLuint jupiterTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/jupiter.jpg");
    GLuint saturnoTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/saturn.jpg");
    GLuint uranoTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/uranus.jpg");
    GLuint netunoTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/neptune.jpg");

std::cout << "Diretório atual: " << std::filesystem::current_path() << std::endl;
    if (std::filesystem::exists("/home/pk/projects/C/computacao-grafica/av1/img/earth.jpg")) {
        std::cout << "Imagem encontrada!" << std::endl;
    } else {
        std::cerr << "Imagem não encontrada!" << std::endl;
        return -1;
    }


    // Carrega a textura do planeta
    GLuint texturaPlaneta = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/earth.jpg");

    // Inicialização do sistema solar e das estrelas
    inicializaSistemaSolar();
    inicializaSatelite();

    // Configuração da câmera
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Inicializa os planetas com as texturas carregadas
    planetas[0].textura = mercurioTextura;
    planetas[1].textura = venusTextura;
    planetas[2].textura = terraTextura;
    planetas[3].textura = marteTextura;
    planetas[4].textura = jupiterTextura;
    planetas[5].textura = saturnoTextura;
    planetas[6].textura = uranoTextura;
    planetas[7].textura = netunoTextura;
    // Se quiser adicionar textura para o Sol também
    solTextura = carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/sun.jpg");

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        display();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
