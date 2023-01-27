# WorldCup
## Moteur de Jeu 2D et Implémentation mini-jeu

Le moteur de jeu développé contient notamment un système de gestion des Component, efficace et facilement adaptable.

Toutes les textures du mini-jeu sont en 32x32 et on été designées à l'aide de GIMP.

## Important

DES WARNING CONCERNANT LA SDL PEUVENT APPARAITRE SOUS MacOS
(mais pas de warning sur Linux)

Dans le fichier  `/apps/main.cpp`
NE JAMAIS PASSER L'ARGUMENT `FULLSCREEN` À `True`  SUR MacOS
(si vous le faites, il faut faire `Cmd+Q` pour quitter)

SOUS VALGRIND:
Des erreurs peuvent apparaître mais une bonne partie de ces erreurs sont dûes à des bugs internes à la SDL2 qui ne peuvent être corrigés.
Le reste des fuites de mémoire reste très léger.

## Installations

### Installation de la librairie SDL2

L'interface graphique du jeu a été réalisé avec la librairie SDL2

Pour l'installer sur:

Mac OS sans Xcode

```sh
brew install sdl2 sdl2_image
```

Linux

```sh
sudo apt-get install libsdl2-dev libsdl2_image-dev
```

### Installation de CMake
Se référer dans: https://cmake.org/install/

Download: https://cmake.org/download/

Add Cmake dans le PATH:

Windows

(Utilisation d'un ordinateur sous Windows non recommandée)
Lors de l'intallation utiliser l'option pour modifier les variables d'environment du system PATH ou sinon le faire manuellement en mettant le répertoire (e.g. C:\Program Files\CMake\bin) dans le PATH.

Mac OS
```sh
brew install cmake
```
Ou installer manuellement :
1. Copier CMake.app dans Applications
2. Lancer CMake.app
3. Dans l'onglet "Tools/How to Install For Command Line Use” suivre les instructions pour rendre disponbles les outils de ligne de commande dans le PATH

```sh
PATH="/Applications/CMake.app/Contents/bin":"$PATH"
```
Ou sinon le faire manuellement en mettant le repértoire (e.g. /Applications/CMake.app/Contents/bin) dans le PATH

Configuration:

Linux

S'il n'y a aucune version de CMake préexistante:
```sh
./bootstrap
make
make install
```

Sinon:

```sh
cmake .
make      
make install
```

Ou:

```sh
sudo apt-get install cmake
```

## Lancer le jeu

```sh
mkdir build
cd build
```

ATTENTION : LE DOSSIER `build` DOIT ÊTRE VIDE AVANT TOUTE MANIPULATION

Dans le répertoire `\ProjetCPP\build` lancer:
```sh
cmake ..
make
```
(cmake génère également une règle `clean`)

Exécution:
```sh
./Game
```

Pour quitter le mini-jeu il suffit de fermer la fenêtre.
