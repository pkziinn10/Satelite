#ifndef SISTEMASOLAR_H
#define SISTEMASOLAR_H

#include <vector>
#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// Estrutura para representar um planeta
struct Planeta {
    float raio;
    float raioOrbita;
    float velocidadeOrbita;
    float r, g, b;
    std::string nome;

    // Construtor para inicializar a estrutura Planeta
    Planeta(float raio, float raioOrbita, float velocidadeOrbita, float r, float g, float b, const std::string& nome)
        : raio(raio), raioOrbita(raioOrbita), velocidadeOrbita(velocidadeOrbita), r(r), g(g), b(b), nome(nome) {}
};

// Função de gerar estrelas no sistema solar
void geraEstrelasSistemaSolar(int numEstrelas);

// Função para desenhar as estrelas no sistema solar
void desenhaEstrelasSistemaSolar();

// Função para desenhar uma esfera
void desenhaEsfera(float raio, int fatias, int pilhas, float r, float g, float b);

// Função para desenhar o sistema solar
void desenhaSistemaSolar();

// Inicializa o sistema solar (opcional, caso precise de inicializações futuras)
void inicializaSistemaSolar();

#endif // SISTEMASOLAR_H
