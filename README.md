# 🌌 Projeto Satélite

Este projeto é uma simulação gráfica de um sistema solar simplificado, com foco na visualização de satélites, planetas e suas interações no espaço. Desenvolvido predominantemente em C/C++, o projeto utiliza imagens e texturas para representar os elementos do sistema solar, contando também com uma câmera interativa para explorar o ambiente 3D.

## 📁 Estrutura do Projeto

O repositório possui a seguinte estrutura:

📦 Projeto Satélite 
├── camera.cpp / camera.h # Implementação da câmera (movimentação e visualização) 
├── main.cpp # Arquivo principal da aplicação 
├── satelite.cpp / satelite.h # Lógica e estrutura dos satélites 
├── sistemasolar.cpp / sistemasolar.h # Composição e funcionamento do sistema solar 
├── textura.cpp / textura.h # Gerenciamento de texturas 
├── stb_image.cpp / stb_image.h # Biblioteca para carregamento de imagens (stb_image) 
└── trabalho/ # Pasta com materiais de apoio (relatórios, imagens, assets, etc.)


## 🛰️ Funcionalidades

- **Simulação de Satélites:** Permite a visualização de satélites orbitando os corpos celestes.
- **Sistema Solar Básico:** Renderização do sistema solar com aplicação de texturas.
- **Câmera Interativa:** Navegação livre e interativa no espaço tridimensional.
- **Carregamento de Imagens:** Uso da biblioteca `stb_image` para manipulação de imagens.

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C/C++
- **Renderização:** OpenGL (com uso de bibliotecas como GLFW, GLEW)
- **Matemática Gráfica:** GLM para cálculos e transformações no espaço 3D
- **Manipulação de Imagens:** stb_image.h

## 📌 Instruções de Execução

### Pré-requisitos

- Compilador C/C++ (g++, clang++)
- Bibliotecas de OpenGL e dependências (por exemplo, GLFW, GLEW ou GLUT)
- CMake (opcional, se for utilizado para gerar os arquivos de compilação)

### Compilação (Modo Simples)

Utilize o seguinte comando para compilar o projeto diretamente:

```bash
g++ main.cpp camera.cpp satelite.cpp sistemasolar.cpp textura.cpp stb_image.cpp -o Satelite -lGL -lGLU -lglut
./Satelite
