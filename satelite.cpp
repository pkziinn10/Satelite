#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <ctime>
#include <cmath>

float orbitaTerra = 0.0f; // Ângulo da órbita da Terra
float orbitaLua = 0.0f;  // Ângulo da órbita da Lua
glm::vec3 cameraPos(0.0f, 0.0f, 30.0f); // Posição inicial da câmera
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f); // Direção da câmera
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // Vetor 'up' da câmera

float horizontal = -90.0f;  // Rotação horizontal da câmera
float vertical = 0.0f;  // Inclinação vertical da câmera
float inicialX = 400, inicialY = 400; // Coordenadas iniciais do mouse
bool firstMouse = true;

// Estrutura para corpos celestes
struct Body {
    float raio;          // Raio do corpo
    float raioOrbita;     // Raio da órbita
    float velocidadeOrbita;      // Velocidade de órbita
    float r, g, b;         // Cor (RGB)
};

// Terra e Lua
Body earth = {2.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f};  // Fixo no centro
Body lua = {0.5f, 5.0f, 0.02f, 0.7f, 0.7f, 0.7f}; // Orbitando a Terra

void drawSphere(float raio, int fatias, int pilhas, float r, float g, float b) {
    glColor3f(r, g, b);
    for (int i = 0; i < fatias
  ; i++) {
        for (int j = 0; j < pilhas; j++) {
            float theta1 = i * 2.0f * M_PI / fatias
          ;
            float theta2 = (i + 1) * 2.0f * M_PI / fatias
          ;
            float phi1 = j * M_PI / pilhas;
            float phi2 = (j + 1) * M_PI / pilhas;

            glm::vec3 p1(raio * sin(phi1) * cos(theta1), raio * sin(phi1) * sin(theta1), raio * cos(phi1));
            glm::vec3 p2(raio * sin(phi1) * cos(theta2), raio * sin(phi1) * sin(theta2), raio * cos(phi1));
            glm::vec3 p3(raio * sin(phi2) * cos(theta2), raio * sin(phi2) * sin(theta2), raio * cos(phi2));
            glm::vec3 p4(raio * sin(phi2) * cos(theta1), raio * sin(phi2) * sin(theta1), raio * cos(phi2));

            glBegin(GL_QUADS);
                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p3.x, p3.y, p3.z);
                glVertex3f(p4.x, p4.y, p4.z);
            glEnd();
        }
    }
}

void setCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glm::mat4 projection = glm::perspective(glm::radians(30.0f), 1.0f, 0.1f, 200.0f);
    glLoadMatrixf(&projection[0][0]);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glLoadMatrixf(&view[0][0]);
}

void drawEarthAndlua() {
    // Desenha a Terra
    drawSphere(earth.raio, 30, 30, earth.r, earth.g, earth.b);

    // Calcula a posição da Lua
    float luaX = lua.raioOrbita * cos(orbitaLua);
    float luaZ = lua.raioOrbita * sin(orbitaLua);

    glPushMatrix();
    glTranslatef(luaX, 0.0f, luaZ);
    drawSphere(lua.raio, 20, 20, lua.r, lua.g, lua.b); // Lua
    glPopMatrix();

    // Atualiza o ângulo de órbita da Lua
    orbitaLua += lua.velocidadeOrbita;
    if (orbitaLua >= 2 * M_PI) orbitaLua -= 2 * M_PI;
}

void processInput(GLFWwindow *window) {
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
}

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


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    setCamera();

    drawEarthAndlua();

    glDisable(GL_DEPTH_TEST);
}

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 800, "Lua Orbitando a Terra", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
