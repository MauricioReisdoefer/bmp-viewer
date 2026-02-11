# BMP Viewer

Um visualizador de imagens BMP simples desenvolvido em C utilizando a biblioteca SDL3.

## Funcionalidades

* Carregamento e exibição de imagens no formato BMP.
* Redimensionamento da janela de exibição com base nas dimensões fornecidas.
* Manipulação básica de eventos da janela (fechar).

## Tecnologias Utilizadas

* **C Language**: Linguagem de programação principal.
* **SDL3**: Simple DirectMedia Layer 3 para renderização gráfica e manipulação de janelas.

## Como Compilar e Executar

Para compilar e executar este projeto, você precisará ter o compilador GCC e a biblioteca SDL3 instalados em seu sistema.

### Pré-requisitos

* GCC (GNU Compiler Collection)
* SDL3 Development Libraries

### Compilação

Navegue até o diretório raiz do projeto e execute o seguinte comando:

```bash
gcc main.c bmp.c -o bmp_viewer -IC:/libs/SDL3/include -LC:/libs/SDL3/lib -lSDL3
```

**Nota**: O caminho para os includes (`-I`) e bibliotecas (`-L`) da SDL3 pode variar dependendo da sua instalação. Certifique-se de ajustá-los conforme necessário.

### Execução

Após a compilação, você pode executar o visualizador fornecendo a **razão de escala para largura** e a **razão de escala para altura** (valores inteiros que dividirão as dimensões originais da imagem) e o caminho para o arquivo BMP como argumentos:

```bash
./bmp_viewer <ratio_largura> <ratio_altura> <caminho_para_imagem.bmp>
```

**Exemplo:**

```bash
./bmp_viewer 2 2 bitmap_image.bmp

Se a imagem original for 700x300 pixels, e você usar `2 2`, a imagem será exibida como 350x150 pixels.
```

## Estrutura do Projeto

* `main.c`: Contém a lógica principal do programa, inicialização da SDL3, criação da janela e loop de eventos.
* `bmp.h`: Define as estruturas para o cabeçalho de arquivo BMP (`BMP_FILE_HEADER`), cabeçalho de informações BMP (`BMP_INFO_HEADER`) e a estrutura `BMP_Image`.
* `bmp.c`: Implementa as funções para carregar (`BMP_Load`) e liberar (`BMP_Free`) imagens BMP.
* `bitmap_image.bmp`: Um exemplo de imagem BMP para teste.
* `LICENSE`: Arquivo de licença do projeto (MIT).

## Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.
