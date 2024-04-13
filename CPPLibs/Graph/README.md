# Graph

## Description

**ru:**

Граф - это совокупность множеств узлов и дуг (<V,E> vertices, edges), связывающих между собой узлы двусторонней или односторонней связью.

В данном разделе создаётся библиотека, помогающая удобно строить графы (в теории можно строить и деревья, дерево - это частный случай графа, но не наоборот).

**en:**

Graph is a collection of sets of vertices and edges (<V,E>), connecting the nodes with each other through a two-way or one-way connection.

In this section, a library is created that helps to conveniently build graphs (in theory, you can also build trees; a tree is a special case of a graph, but not vice versa).

## Build 

```bash
mkdir bin && cd bin
cmake ../.
make
```
Or if you are using `VSCode` with `CMake Tools` extension, then :
```bash
cd Algorithms/CPPLibs/Graph
code . # starting a vscode in this directory
# ctrl+shift+p:
## >CMake: Scan for kits
## >Cmake: Configure 
## >Cmake: Select Variant (i use debug)
## >Cmake: Debug
```