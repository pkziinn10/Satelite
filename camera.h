#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

// Declaração de variáveis globais
extern glm::vec3 cameraPos;
extern glm::vec3 cameraFront;
extern glm::vec3 cameraUp;
extern float horizontal;
extern float vertical;
extern float inicialX, inicialY;
extern bool firstMouse;

// Funções da câmera
void setCamera();
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

#endif // CAMERA_H
