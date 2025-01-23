#ifndef TEXTURA_H
#define TEXTURA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "sistemasolar.h"
#include "stb_image.h"

// Função para carregar uma textura a partir de um arquivo usando stb_image
GLuint carregaTextura(const std::string& caminhoArquivo);

// Função para inicializar texturas para os planetas
void inicializaTexturas();

// Função para desenhar um planeta com textura
void desenhaPlanetaComTextura(Planeta& planeta, float x, float z);


#endif
