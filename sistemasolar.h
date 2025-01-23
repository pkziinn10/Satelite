#ifndef SISTEMASOLAR_H
#define SISTEMASOLAR_H

#include <GL/glew.h>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "textura.h"

// Estrutura para representar um planeta
struct Planeta {
    float raio;               // Raio do planeta
    float raioOrbita;         // Raio da órbita
    float velocidadeOrbita;   // Velocidade da órbita
    float r, g, b;            // Cor do planeta
    std::string nome;         // Nome do planeta
    GLuint textura;           // Textura associada ao planeta


    // Construtor para inicializar os atributos do planeta
    Planeta(float raio, float raioOrbita, float velocidadeOrbita, float r, float g, float b,  const std::string& nome, GLuint textura)
        : raio(raio), raioOrbita(raioOrbita), velocidadeOrbita(velocidadeOrbita), r(r), g(g), b(b), nome(nome), textura(textura) {}
};
extern std::vector<Planeta> planetas;
extern std::vector<float> angulosOrbita;
extern std::vector<glm::vec3> estrelasSistemaSolar;

// Função para gerar estrelas no sistema solar
void geraEstrelasSistemaSolar(int numEstrelas);

// Função para desenhar o sistema solar
void desenhaSistemaSolar();

// Inicializa o sistema solar (opcional, caso precise de inicializações futuras)
void inicializaSistemaSolar();

// Função para carregar uma textura a partir de um arquivo usando stb_image
GLuint carregaTextura(const std::string& caminhoArquivo);

// Função para inicializar texturas para os planetas
void inicializaTexturas();

// Função para desenhar as estrelas no sistema solar
void desenhaEstrelasSistemaSolar();

// Função para desenhar um planeta com textura
void desenhaPlanetaComTextura(Planeta& planeta, float x, float z);

// Função para desenhar uma esfera
void desenhaEsfera(float raio, int fatias, int pilhas, float r, float g, float b);

#endif // SISTEMASOLAR_H
