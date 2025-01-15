#ifndef SATELITE_H
#define SATELITE_H

#include <ctime>
#include <vector>
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
extern Body terra;
extern Body lua;

// Variáveis globais para órbitas
extern float orbitaLua;

// Função para gerar estrelas no satelite ( Terra e Lua )
void geraEstrelasSatelite(int numEstrelas);

// Função que desenha as estrelas no satelite ( Terra e Lua )
void desenhaEstrelasSatelite();

// Funções que desenha as esferas
void desenhaEsferas(float raio, int fatias, int pilhas, float r, float g, float b);

//Função de desenhar Terra e Lua
void desenhaTerraELua();

// Inicializa a cena
void inicializaSatelite();

#endif // SATELITE_H
