# Binary Tree Search (Бинарное дерево поиска)

## Description

Бинарное дерева поиска состоит из узлов, каждый из которых имеет максмум два потомка, левый потомок имеет значение меньше корневого, а правый потомок имеет либо большее значение, либо равное корневому узлу.

## O-big (in middle case)

|Операция|Значение|
| :---:  | :---:  |
|Вставка|O(log(n))|
|Удаление|O(log(n))|
|Поиск|O(log(n))|

Однако данное дерево не имеет свойства быть сбалансированным, поэтому в худшем случае обход, вставка и удаление займут O(n)

## Build

```bash
mkdir bin && cd bin
cmake ../.
make
```
Or if you are using `VSCode` with `CMake Tools` extension, then :
```bash
cd Algorithms/CPPLibs/Tree/BinaryTreeSearch
code . # starting a vscode in this directory
# ctrl+shift+p:
## >CMake: Scan for kits
## >Cmake: Configure 
## >Cmake: Select Variant (i use debug)
## >Cmake: Debug
```