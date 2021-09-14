# Fastway
Algoritmo que busca o final de um labirinto

### uso com arquivo
```cpp
#include "fastway.h"
#include <iostream>

int main() {
  std::vector<std::vector<int>> result = FastWay::run("labirinto.txt");
  
  components::print(result); //imprime o vetor bidimensional
  
  return 0;
}
```

### estrutura do arquivo
```
2,1,1,1,1
0,0,0,0,1
1,1,1,1,1
0,0,1,0,1
3,1,1,1,1
```
Onde:
2 : começo do labirinto/posição atual
0 : parede
1 : trilha
3 : final do labirinto
4 : trilha percorrida
