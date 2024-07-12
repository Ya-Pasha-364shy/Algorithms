## Linked list of objects implementation

### Description:

**ru**:
Здесь представлена реализация дву-связного списка **объектов**.

Есть одно строгое ограничение: каждый объект - это какая-либо структкура данных, причём если в списке
хранится *хотя бы две структуры разных типов*, то они должны быть *приводимыми* друг к другу, то есть
**хотя бы** иметь один и тот же размер в байтах (смотри файл `test.c`).


**en**:
Here is an implementation of a two-wa linked list of **objects**.

There is one strict limitation: each object is some kind of data structure, and if in the list
*at least two structures of different types* are stored, then they must be *reducible* to each other, that is
**at least** have the same size in bytes (see file `test.c`).

### Simple Build
```
mkdir bin && cd bin
cmake ../.
make
```

Enjoy !