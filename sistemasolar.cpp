#include "textura.h"
#include "sistemasolar.h"
#include <map>

// Vetor de estrelas
std::vector<glm::vec3> estrelasSistemaSolar;

// Planetas do sistema solar
std::vector<Planeta> planetas = {
    {0.5f, 5.0f, 0.01f, 1.0f, 1.0f, 0.0f, "Mercúrio", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/mercury.jpg")},
    {0.8f, 8.0f, 0.008f, 1.0f, 1.5f, 1.0f, "Vênus", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/venus.jpg")},
    {1.0f, 12.0f, 0.007f, 0.0f, 0.5f, 1.0f, "Terra", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/earth.jpg")},
    {0.6f, 16.0f, 0.006f, 1.0f, 0.0f, 0.0f, "Marte", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/mars.jpg")},
    {2.5f, 22.0f, 0.004f, 1.0f, 0.8f, 0.0f, "Júpiter", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/jupiter.jpg")},
    {2.0f, 28.0f, 0.003f, 0.8f, 0.8f, 1.0f, "Saturno", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/saturn.jpg")},
    {1.5f, 35.0f, 0.002f, 0.0f, 0.5f, 1.0f, "Urano", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/uranus.jpg")},
    {1.4f, 40.0f, 0.001f, 0.0f, 0.0f, 1.0f, "Netuno", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/neptune.jpg")}
};

// Ângulos de órbita para os planetas
std::vector<float> angulosOrbita;

// Gera estrelas aleatoriamente
void geraEstrelasSistemaSolar(int numEstrelas) {
    estrelasSistemaSolar.clear();
    for (int i = 0; i < numEstrelas; ++i) {
        float x = ((rand() % 2000) - 1000) / 10.0f;
        float y = ((rand() % 2000) - 1000) / 10.0f;
        float z = ((rand() % 2000) - 1000) / 10.0f;

        estrelasSistemaSolar.push_back(glm::vec3(x, y, z));
    }
}

// Função para carregar uma textura a partir de um arquivo usando stb_image
GLuint carregaTextura(const std::string& caminhoArquivo) {
    GLuint texturaID;
    glGenTextures(1, &texturaID);
    glBindTexture(GL_TEXTURE_2D, texturaID);

    int largura, altura, canais;
    unsigned char* imagem = stbi_load(caminhoArquivo.c_str(), &largura, &altura, &canais, STBI_rgb_alpha);
    if (!imagem) {
        std::cerr << "Erro ao carregar a textura: " << caminhoArquivo << std::endl;
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagem);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_image_free(imagem);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texturaID;
}

// Função para desenhar as estrelas
void desenhaEstrelasSistemaSolar() {
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POINTS);
    for (const auto& estrela : estrelasSistemaSolar) {
        glVertex3f(estrela.x, estrela.y, estrela.z);
    }
    glEnd();
}

// Função para desenhar um planeta com textura
void desenhaPlanetaComTextura(Planeta& planeta, float x, float z) {
    if (planeta.textura == 0) {
        std::cerr << "Textura não encontrada para o planeta: " << planeta.nome << std::endl;
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, planeta.textura);

    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    int fatias = 20;
    int pilhas = 20;
    float raio = planeta.raio;
    for (int i = 0; i < fatias; ++i) {
        float theta1 = i * 2.0f * M_PI / fatias;
        float theta2 = (i + 1) * 2.0f * M_PI / fatias;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= pilhas; ++j) {
            float phi = j * M_PI / pilhas;

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

// Desenha o sistema solar
// Desenha o sistema solar
void desenhaSistemaSolar() {
    // Verifique se angulosOrbita foi inicializado corretamente
    if (angulosOrbita.size() != planetas.size()) {
        std::cerr << "Erro: o tamanho de angulosOrbita não corresponde ao número de planetas!" << std::endl;
        return;
    }

    // Desenha as estrelas
    desenhaEstrelasSistemaSolar();

    // Define a textura do Sol
    Planeta sol = {4.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, "Sol", carregaTextura("/home/pk/projects/C/computacao-grafica/av1/img/sun.jpg")};
    desenhaPlanetaComTextura(sol, 0.0f, 0.0f);

    // Desenha os planetas
    for (size_t i = 0; i < planetas.size(); i++) {
        // Verifica os limites do vetor angulosOrbita
        if (i >= angulosOrbita.size()) {
            std::cerr << "Erro: índice " << i << " fora dos limites de angulosOrbita." << std::endl;
            continue;
        }

        Planeta& planeta = planetas[i];

        // Verifica se o raioOrbita é válido
        if (!std::isfinite(planeta.raioOrbita) || planeta.raioOrbita < 0) {
            std::cerr << "Erro: raioOrbita inválido para o planeta " << planeta.nome << std::endl;
            continue;
        }

        // Calcula as posições
        float x = planeta.raioOrbita * cos(angulosOrbita[i]);
        float z = planeta.raioOrbita * sin(angulosOrbita[i]);

        // Desenha o planeta com textura
        desenhaPlanetaComTextura(planeta, x, z);

        // Atualiza o ângulo da órbita
        angulosOrbita[i] += planeta.velocidadeOrbita;
        if (angulosOrbita[i] >= 2 * M_PI) {
            angulosOrbita[i] -= 2 * M_PI;
        }
    }
}

// Inicializa o sistema solar
void inicializaSistemaSolar() {
    srand(static_cast<unsigned>(time(0)));
    geraEstrelasSistemaSolar(100);

    // Inicializa o vetor de ângulos de órbita com 0.0f para cada planeta
    angulosOrbita.resize(planetas.size(), 0.0f);
}

