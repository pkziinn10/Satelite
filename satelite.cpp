#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib> // Para gerar números aleatórios
#include <ctime>   // Para inicializar a semente do gerador de números
#include <math.h>


float orbitAngles[8] = {0.0f}; // Ângulos de órbita dos planetas
glm::vec3 cameraPos(0.0f, 0.0f, 30.0f); // Posição inicial da câmera
glm::vec3 cameraFront(0.0f, 0.0f, -1.0f); // Direção da câmera
glm::vec3 cameraUp(0.0f, 1.0f, 0.0f); // Vetor 'up' da câmera
float yaw = -90.0f;  // Rotação horizontal da câmera
float pitch = 0.0f;  // Inclinação vertical da câmera
float lastX = 400, lastY = 400; // Coordenadas iniciais do mouse
bool firstMouse = true;

std::vector<glm::vec3> stars; // Coordenadas das estrelas

struct Planet {
    float radius;
    float orbitRadius;
    float orbitSpeed;
    float r, g, b;
};

std::vector<Planet> planets = {
    {0.5f, 5.0f, 0.01f, 1.0f, 0.0f, 0.0f},
    {0.8f, 8.0f, 0.008f, 1.0f, 0.5f, 0.0f},
    {1.0f, 12.0f, 0.007f, 0.0f, 0.5f, 1.0f},
    {0.6f, 16.0f, 0.006f, 1.0f, 0.0f, 0.0f},
    {2.5f, 22.0f, 0.004f, 1.0f, 0.8f, 0.0f},
    {2.0f, 28.0f, 0.003f, 0.8f, 0.8f, 1.0f},
    {1.5f, 35.0f, 0.002f, 0.0f, 0.5f, 1.0f},
    {1.4f, 40.0f, 0.001f, 0.0f, 0.0f, 1.0f}
};

void generateStars(int numStars) {
    stars.clear();
    for (int i = 0; i < numStars; ++i) {
        float x = ((rand() % 1000) - 500) / 10.0f; // Coordenadas aleatórias no intervalo [-10, 10]
        float y = ((rand() % 1000) - 500) / 10.0f;
        float z = ((rand() % 1000) - 500) / 10.0f;
        stars.push_back(glm::vec3(x, y, z));
    }
}

void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glBegin(GL_POINTS);
    for (const auto& star : stars) {
        glVertex3f(star.x, star.y, star.z);
    }
    glEnd();
}

void drawSphere(float radius, int slices, int stacks, float r, float g, float b) {
    glColor3f(r, g, b);
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            float theta1 = i * 2.0f * M_PI / slices;
            float theta2 = (i + 1) * 2.0f * M_PI / slices;
            float phi1 = j * M_PI / stacks;
            float phi2 = (j + 1) * M_PI / stacks;

            glm::vec3 p1(radius * sin(phi1) * cos(theta1), radius * sin(phi1) * sin(theta1), radius * cos(phi1));
            glm::vec3 p2(radius * sin(phi1) * cos(theta2), radius * sin(phi1) * sin(theta2), radius * cos(phi1));
            glm::vec3 p3(radius * sin(phi2) * cos(theta2), radius * sin(phi2) * sin(theta2), radius * cos(phi2));
            glm::vec3 p4(radius * sin(phi2) * cos(theta1), radius * sin(phi2) * sin(theta1), radius * cos(phi2));

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

void drawSolarSystem() {
    drawStars(); // Desenhar estrelas primeiro
    drawSphere(4.0f, 30, 30, 1.0f, 1.0f, 0.0f);
    for (size_t i = 0; i < planets.size(); i++) {
        const Planet& planet = planets[i];
        float x = planet.orbitRadius * cos(orbitAngles[i]);
        float z = planet.orbitRadius * sin(orbitAngles[i]);

        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        drawSphere(planet.radius, 20, 20, planet.r, planet.g, planet.b);
        glPopMatrix();

        orbitAngles[i] += planet.orbitSpeed;
        if (orbitAngles[i] >= 2 * M_PI) orbitAngles[i] -= 2 * M_PI;
    }
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
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    setCamera();

    drawSolarSystem();
    glDisable(GL_DEPTH_TEST);
}

int main(void) {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 800, "Sistema Solar", NULL, NULL);
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

    srand(static_cast<unsigned>(time(0))); // Inicializar a semente do gerador de números aleatórios
    generateStars(500); // Gerar 500 estrelas

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
