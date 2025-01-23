#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "textura.h"
#include <map>
#include <iostream>
#include <string>
#include <GL/glew.h>

std::map<std::string, GLuint> texturas;

// Função para carregar uma textura a partir de um arquivo usando stb_image
GLuint carregarTextura(const std::string &caminhoArquivo) {
    GLuint texturaID;
    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    // Carregar imagem
    int largura, altura, canais;
    unsigned char* imagem = stbi_load(caminhoArquivo.c_str(), &largura, &altura, &canais, 0);

    if (!imagem) {
        std::cerr << "Erro ao carregar a imagem: " << caminhoArquivo << std::endl;
        return 0;  // Retorna 0 em caso de erro
    } else {
        std::cout << "Imagem carregada com sucesso: " << caminhoArquivo << std::endl;
    }

    // Configura a textura
    GLenum formato;
    if (canais == 3) {
        formato = GL_RGB;
    } else if (canais == 4) {
        formato = GL_RGBA;
    } else {
        std::cerr << "Formato de imagem não suportado!" << std::endl;
        stbi_image_free(imagem);
        return 0;  // Retorna 0 se o formato não for suportado
    }

    // Envia a imagem para o OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, formato, largura, altura, 0, formato, GL_UNSIGNED_BYTE, imagem);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Configura parâmetros de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Libera a imagem da memória
    stbi_image_free(imagem);

    // Desvincula a textura
    glBindTexture(GL_TEXTURE_2D, 0);

    return texturaID;
}

// Função para inicializar texturas para os planetas
void inicializaTexturas() {
    texturas["Mercúrio"] = carregarTextura("img/mercury.jpg");
    texturas["Vênus"] = carregarTextura("img/venus.jpg");
    texturas["Terra"] = carregarTextura("img/earth.jpg");
    texturas["Marte"] = carregarTextura("img/mars.jpg");
    texturas["Júpiter"] = carregarTextura("img/jupiter.jpg");
    texturas["Saturno"] = carregarTextura("img/saturn.jpg");
    texturas["Urano"] = carregarTextura("img/uranus.jpg");
    texturas["Netuno"] = carregarTextura("img/neptune.jpg");
}

// Função para desenhar um planeta com textura
void desenhaPlanetaComTextura(Planeta& planeta, float x, float z) {
    auto it = texturas.find(planeta.nome);
    if (it == texturas.end()) {
        std::cerr << "Textura não encontrada para o planeta: " << planeta.nome << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, it->second);

    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    // Criar esfera manualmente com coordenadas de textura
    int fatias = 20;
    int pilhas = 20;
    float raio = planeta.raio;
    for (int i = 0; i < fatias; ++i) {
        float theta1 = i * 2.0f * M_PI / fatias;
        float theta2 = (i + 1) * 2.0f * M_PI / fatias;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= pilhas; ++j) {
            float phi = j * M_PI / pilhas;

            // Coordenadas de textura e vértices
            for (int k = 0; k < 2; ++k) {
                float theta = (k == 0) ? theta1 : theta2;

                float x = raio * sin(phi) * cos(theta);
                float y = raio * cos(phi);
                float z = raio * sin(phi) * sin(theta);

                float s = theta / (2.0f * M_PI);
                float t = phi / M_PI;

                glTexCoord2f(s, t);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }

    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}
