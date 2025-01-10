#ifndef SISTEMASOLAR_H
#define SISTEMASOLAR_H

#include <vector>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Estrutura para representar um planeta
struct Planeta {
    float raio;
    float raioOrbita;
    float velocidadeOrbita;
    float r, g, b;
};

// Funções para gerenciamento de estrelas
void generateestrelas(int numEstrelas);
void drawestrelas();

// Função para desenhar uma esfera
void drawSphereS(float raio, int slices, int stacks, float r, float g, float b);

// Função para desenhar o sistema solar
void drawSolarSystem();

// Inicializa o sistema solar (opcional, caso precise de inicializações futuras)
void initializeSolarSystem();

#endif // SISTEMASOLAR_H
