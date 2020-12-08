# Pixteal

![GitHub](https://img.shields.io/github/license/lincolncpp/pixteal?color=red&style=flat-square)

Desenvolvido para o curso de Sistemas Operacionais I. O jogo aplica conceitos de Threads e Semáforos e foi criado utilizando C++ e SDL2 como interface

<img src="https://i.ibb.co/jbTRK7F/print.png" alt="screenshot"></a>

## O jogo
Cada personagem dentro do jogo é gerenciado por uma thread distinta fazendo o uso de semáforos para checar se a posição no mapa para onde se quer andar está vazia.

## Como compilar

Pixeal foi projetado para ser executado em sistemas Linux e utiliza as bibliotecas [SDL2](https://www.libsdl.org), [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) e [SDL2_image](https://www.libsdl.org/projects/SDL_image/)

### Instalando bibliotecas

Para sistemas baseados no Arch use

```
pacman -S sdl2 sdl2_ttf sdl2_image
```

Para os baseados no Debian

```
apt install sdl2 sdl2_ttf sdl2_image
```

### Compilando e executando

Baixe o código fonte do projeto usando

```
git clone https://github.com/lincolncpp/Pixteal.git
```

Para compilar basta usar

```
cd Pixteal
make
```

Em seguida, execute o arquivo gerado chamado _game_.

## Como jogar
Você controlará o personagem chamado **Thread 1**

Use as setas direcionais ou as teclas WASD para se mover

O objetivo do jogo é pegar os minérios que vão surgindo aleatóriamente pelo mapa

## Créditos
- Fonte - [Cal Henderson](https://www.dafont.com/pt/pixelsix.font)
- Arte gráfica - [dannorder](https://opengameart.org/content/roguedb32-plus-add-on-tiles)

## Licença

Este projeto está licenciado sob a Licença MIT - consulte o arquivo [LICENSE.md](/LICENSE) para obter detalhes.
