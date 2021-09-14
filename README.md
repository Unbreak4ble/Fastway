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

### estrutura do labirinto
```
2,1,1,1,1
0,0,0,0,1
1,1,1,1,1
0,0,1,0,0
3,1,1,1,1
```
Códigos: <br/>
2 : começo do labirinto/posição atual <br/>
0 : parede <br/>
1 : trilha <br/>
3 : final do labirinto <br/>
4 : trilha percorrida <br/>

### Saída
```
2,4,4,4,4
0,0,0,0,4
1,1,4,4,4
0,0,4,0,0
3,4,4,1,1
```

### usando vetores
```cpp
#include "fastway.h"
#include <iostream>

int main() {
  std::vector<std::vector<int>> labirinto = {
   {2,1,1,1,1},
   {0,0,0,0,1},
   {1,1,1,1,1},
   {0,0,1,0,1},
   {3,1,1,1,1}
  };
  
  std::vector<std::vector<int>> result = FastWay::run(labirinto);
  
  components::print(result); //imprime o vetor bidimensional
  
  return 0;
}
```
