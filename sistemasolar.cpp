#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

std::vector<glm::vec3> estrelas;

void generateestrelas(int numEstrelas) {
    estrelas.clear();
    for (int i = 0; i < numEstrelas; ++i) {
        float x = ((rand() % 1000) - 500) / 10.0f;
        float y = ((rand() % 1000) - 500) / 10.0f;
        float z = ((rand() % 1000) - 500) / 10.0f;
        estrelas.push_back(glm::vec3(x, y, z));
    }
}

void drawestrelas() {
    glColor3f(1.0f, 1.0f, 1.0f); // Branco
    glBegin(GL_POINTS);
    for (const auto& estrela : estrelas) {
        glVertex3f(estrela.x, estrela.y, estrela.z);
    }
    glEnd();
}

struct Planeta {
    float raio;
    float raioOrbita;
    float velocidadeOrbita;
    float r, g, b;
};

std::vector<Planeta> planetas = {
    {0.5f, 5.0f, 0.01f, 1.0f, 0.0f, 0.0f},
    {0.8f, 8.0f, 0.008f, 1.0f, 0.5f, 0.0f},
    {1.0f, 12.0f, 0.007f, 0.0f, 0.5f, 1.0f},
    {0.6f, 16.0f, 0.006f, 1.0f, 0.0f, 0.0f},
    {2.5f, 22.0f, 0.004f, 1.0f, 0.8f, 0.0f},
    {2.0f, 28.0f, 0.003f, 0.8f, 0.8f, 1.0f},
    {1.5f, 35.0f, 0.002f, 0.0f, 0.5f, 1.0f},
    {1.4f, 40.0f, 0.001f, 0.0f, 0.0f, 1.0f}
};

float orbitAngles[8] = {0.0f}; // Ângulos de órbita dos planetas

void drawSphere(float raio, int slices, int stacks, float r, float g, float b) {
    glColor3f(r, g, b);
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            float theta1 = i * 2.0f * M_PI / slices;
            float theta2 = (i + 1) * 2.0f * M_PI / slices;
            float phi1 = j * M_PI / stacks;
            float phi2 = (j + 1) * M_PI / stacks;

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

void drawSolarSystem() {
    drawestrelas(); // Desenhar estrelas primeiro
    drawSphere(4.0f, 30, 30, 1.0f, 1.0f, 0.0f); // Sol

    for (size_t i = 0; i < planetas.size(); i++) {
        const Planeta& planeta = planetas[i];
        float x = planeta.raioOrbita * cos(orbitAngles[i]);
        float z = planeta.raioOrbita * sin(orbitAngles[i]);

        glPushMatrix();
        glTranslatef(x, 0.0f, z);
        drawSphere(planeta.raio, 20, 20, planeta.r, planeta.g, planeta.b);
        glPopMatrix();

        orbitAngles[i] += planeta.velocidadeOrbita;
        if (orbitAngles[i] >= 2 * M_PI) orbitAngles[i] -= 2 * M_PI;
    }
}
