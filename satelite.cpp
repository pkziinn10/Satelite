#include "satelite.h"
#include <cmath>

// Vetor de estrelas
std::vector<glm::vec3> estrelasSatelite;
// Corpos celestes: Terra e Lua
Body terra = {2.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f};  // Terra fixa no centro
Body lua = {0.5f, 5.0f, 0.02f, 0.7f, 0.7f, 0.7f};  // Lua orbitando a Terra

// Ângulo de órbita da Lua
float orbitaLua = 0.0f;

void geraEstrelasSatelite(int numEstrelas) {
    estrelasSatelite.clear();
    for (int i = 0; i < numEstrelas; ++i) {
        float x = ((rand() % 1000) - 500) / 10.0f;
        float y = ((rand() % 1000) - 500) / 10.0f;
        float z = ((rand() % 1000) - 500) / 10.0f;
        estrelasSatelite.push_back(glm::vec3(x, y, z));
    }
}

// Desenha as estrelas
void desenhaEstrelasSatelite() {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glBegin(GL_POINTS);
    for (const auto& estrela : estrelasSatelite) {
        glVertex3f(estrela.x, estrela.y, estrela.z);
    }
    glEnd();
}

// Função para desenhar uma esfera
void desenhaEsferas(float raio, int fatias, int pilhas, float r, float g, float b) {
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

// Função para desenhar a Terra e a Lua
void desenhaTerraELua() {
    desenhaEstrelasSatelite();
    // Desenha a Terra
    desenhaEsferas(terra.raio, 30, 30, terra.r, terra.g, terra.b);

    // Calcula a posição da Lua
    float luaX = lua.raioOrbita * cos(orbitaLua);
    float luaZ = lua.raioOrbita * sin(orbitaLua);

    glPushMatrix();
    glTranslatef(luaX, 0.0f, luaZ);
    desenhaEsferas(lua.raio, 20, 20, lua.r, lua.g, lua.b); // Lua
    glPopMatrix();

    // Atualiza o ângulo de órbita da Lua
    orbitaLua += lua.velocidadeOrbita;
    if (orbitaLua >= 2 * M_PI) orbitaLua -= 2 * M_PI;
}

// Inicializa a cena (caso seja necessário configurar algo adicional no futuro)
void inicializaSatelite() {
    // Configurações iniciais, se necessárias
    srand(static_cast<unsigned>(time(0)));
    geraEstrelasSatelite(100); // Gera 100 estrelas por padrão
}
