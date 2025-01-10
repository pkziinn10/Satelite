#ifndef SATELITE_H
#define SATELITE_H

#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Estrutura para corpos celestes
struct Body {
    float raio;          // Raio do corpo
    float raioOrbita;    // Raio da órbita
    float velocidadeOrbita;  // Velocidade de órbita
    float r, g, b;       // Cor (RGB)
};

// Variáveis globais para os corpos celestes
extern Body earth;
extern Body lua;

// Variáveis globais para órbitas
extern float orbitaLua;

// Funções de desenho
void drawSphere(float raio, int fatias, int pilhas, float r, float g, float b);
void drawEarthAndlua();

// Inicializa a cena
void initializeScene();

#endif // SATELITE_H
