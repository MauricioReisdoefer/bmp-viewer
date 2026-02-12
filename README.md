# BMP Viewer

Um visualizador de imagens BMP simples desenvolvido em C utilizando a biblioteca SDL3.

## Funcionalidades

* Carregamento e exibição de imagens no formato BMP.
* Redimensionamento da janela de exibição com base nas dimensões fornecidas.
* Manipulação básica de eventos da janela (fechar).
* Conversão para preto e branco (`bw`).
* Inversão de cores (`inv`).
* Ajuste de brilho (`bright <valor>`).

## Como Usar

Para utilizar o BMP Viewer, siga os passos abaixo:

### Pré-requisitos

Você precisará ter o compilador GCC e a biblioteca SDL3 instalados em seu sistema.

* **GCC** (GNU Compiler Collection)
* **SDL3 Development Libraries**

### Compilação

Navegue até o diretório raiz do projeto e execute o seguinte comando para compilar o programa:

```shell
gcc main.c bmp.c utils.c -o bmp_viewer -IC:/libs/SDL3/include -LC:/libs/SDL3/lib -lSDL3
```

**Nota**: O caminho para os includes (`-I`) e bibliotecas (`-L`) da SDL3 (`C:/libs/SDL3/include` e `C:/libs/SDL3/lib`) pode variar dependendo da sua instalação. Certifique-se de ajustá-los conforme necessário para o seu ambiente.

### Execução

Após a compilação, você pode executar o visualizador fornecendo os seguintes argumentos:

```shell
./bmp_viewer <ratio_largura> <ratio_altura> <caminho_para_imagem.bmp> [filtros]
```

#### Argumentos

* `<ratio_largura>`: Fator de escala horizontal (ex: 1, 2, 4). Um valor de `2` exibirá a imagem com metade da largura original.
* `<ratio_altura>`: Fator de escala vertical (ex: 1, 2, 4). Um valor de `2` exibirá a imagem com metade da altura original.
* `<caminho_para_imagem.bmp>`: O caminho completo para o arquivo de imagem BMP de 24 bits que você deseja visualizar.
* `[flags]`: (Opcional) Um ou mais flags a serem aplicados à imagem. As flags disponíveis são:
  * `bw`: Converte a imagem para preto e branco.
  * `inv`: Inverte as cores da imagem.
  * `bright <valor>`: Ajusta o brilho da imagem. O `<valor>` deve ser um número inteiro.
  * `contrast <valor>`: Ajusta o contraste da image. O `<valor>` deve ser um número inteiro.
  * `sepia`: Aplica um efeito de fotografia antiga, ajustando os canais RGB para tons amarelados/marrom.
  * `save <valor>`: Salva a imagem no local determinado em `<valor>`. `<valor>` deve ser uma string.

#### Exemplos de Uso

1. **Visualizar uma imagem sem filtros, com redimensionamento:**

    ```shell
    ./bmp_viewer 2 2 bitmap_image.bmp
    ```

    *Se a imagem original for 700x300 pixels, ela será exibida como 350x150 pixels.*

2. **Visualizar uma imagem em preto e branco:**

    ```shell
    ./bmp_viewer 1 1 bitmap_image.bmp bw
    ```

3. **Visualizar uma imagem com cores invertidas e brilho ajustado:**

    ```shell
    ./bmp_viewer 1 1 bitmap_image.bmp inv bright 50
    ```

4. **Visualizar uma imagem com múltiplos filtros:**

    ```shell
    ./bmp_viewer 2 2 bitmap_image.bmp bw inv bright -100
    ```

## Licença

Este projeto está licenciado sob a Licença MIT. Veja o arquivo `LICENSE` no repositório para mais detalhes.
