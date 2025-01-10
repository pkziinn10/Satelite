#include "camera.h"

// Inicialização de variáveis globais
glm::vec3 cameraPos(0.0f, 0.0f, 30.0f); // Posição inicial da câmera
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f); // Direção da câmera
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // Vetor 'up' da câmera
float horizontal = -90.0f;  // Rotação horizontal da câmera
float vertical = 0.0f;  // Inclinação vertical da câmera
float inicialX = 400, inicialY = 400; // Coordenadas iniciais do mouse
bool firstMouse = true;

// Implementação da função de configuração da câmera
void setCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 projecao = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 200.0f);
    glLoadMatrixf(&projecao[0][0]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glLoadMatrixf(&view[0][0]);
}
// Implementação da função de callback do mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        inicialX = xpos;
        inicialY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - inicialX;
    float yoffset = inicialY - ypos;
    inicialX = xpos;
    inicialY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    horizontal += xoffset;
    vertical += yoffset;

    if (vertical > 89.0f)
        vertical = 89.0f;
    if (vertical < -89.0f)
        vertical = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(horizontal)) * cos(glm::radians(vertical));
    front.y = sin(glm::radians(vertical));
    front.z = sin(glm::radians(horizontal)) * cos(glm::radians(vertical));
    cameraFront = glm::normalize(front);
}
