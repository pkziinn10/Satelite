#include "sistemasolar.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

// Vetor de estrelas
std::vector<glm::vec3> estrelasSistemaSolar;

// Planetas do sistema solar
std::vector<Planeta> planetas = {
    Planeta(0.5f, 5.0f, 0.01f, 1.0f, 1.0f, 0.0f, "Mercúrio"),
    Planeta(0.8f, 8.0f, 0.008f, 0.8f, 0.8f, 0.0f, "Vênus"),
    Planeta(1.0f, 12.0f, 0.007f, 0.0f, 0.5f, 1.0f, "Terra"),
    Planeta(0.6f, 16.0f, 0.006f, 1.0f, 0.0f, 0.0f, "Marte"),
    Planeta(2.5f, 22.0f, 0.004f, 1.0f, 0.8f, 0.0f, "Júpiter"),
    Planeta(2.0f, 28.0f, 0.003f, 0.8f, 0.8f, 1.0f, "Saturno"),
    Planeta(1.5f, 35.0f, 0.002f, 0.0f, 0.5f, 1.0f, "Urano"),
    Planeta(1.4f, 40.0f, 0.001f, 0.0f, 0.0f, 1.0f, "Netuno")
};

// Ângulos de órbita para os planetas
float angulosOrbita[8] = {0.0f};

// Gera estrelas aleatoriamente
void geraEstrelasSistemaSolar(int numEstrelas) {
    estrelasSistemaSolar.clear();
    for (int i = 0; i < numEstrelas; ++i) {
        float x = ((rand() % 2000) - 1000) / 10.0f; // Aumentar o alcance das estrelas
        float y = ((rand() % 2000) - 1000) / 10.0f;
        float z = ((rand() % 2000) - 1000) / 10.0f;

        estrelasSistemaSolar.push_back(glm::vec3(x, y, z));
    }
}

// Desenha as estrelas
void desenhaEstrelasSistemaSolar() {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glBegin(GL_POINTS);
    for (const auto& estrela : estrelasSistemaSolar) {
        glVertex3f(estrela.x, estrela.y, estrela.z);
    }
    glEnd();
}

void desenhaPlaneta(const Planeta& planeta, float x, float z) {

    // Desenha a esfera com a textura aplicada
    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    desenhaEsfera(planeta.raio, 20, 20, planeta.r, planeta.g, planeta.b);  // Alterado para usar a cor do planeta
    glPopMatrix();

    // Desativando a textura
}


// Desenha uma esfera
void desenhaEsfera(float raio, int fatias, int pilhas, float r, float g, float b) {
    glColor3f(r, g, b);
    for (int i = 0; i < fatias; i++) {
        for (int j = 0; j < pilhas; j++) {
            float theta1 = i * 2.0f * M_PI / fatias;
            float theta2 = (i + 1) * 2.0f * M_PI / fatias;
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

// Desenha o sistema solar
void desenhaSistemaSolar() {
    desenhaEstrelasSistemaSolar(); // Desenha estrelas primeiro

    glPushMatrix();
    desenhaEsfera(4.0f, 30, 30, 1.0f, 1.0f, 0.0f); // Sol
    glPopMatrix();

    // Desenho dos planetas
    for (size_t i = 0; i < planetas.size(); i++) {
        const Planeta& planeta = planetas[i];
        float x = planeta.raioOrbita * cos(angulosOrbita[i]);
        float z = planeta.raioOrbita * sin(angulosOrbita[i]);

        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        desenhaEsfera(planeta.raio, 20, 20, planeta.r, planeta.g, planeta.b);
        glPopMatrix();

        angulosOrbita[i] += planeta.velocidadeOrbita;
        if (angulosOrbita[i] >= 2 * M_PI) angulosOrbita[i] -= 2 * M_PI;
    }
}

// Inicializa o sistema solar
void inicializaSistemaSolar() {
    srand(static_cast<unsigned>(time(0))); // Semente para números aleatórios
    geraEstrelasSistemaSolar(100); // Gera 100 estrelas por padrão
}
