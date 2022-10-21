### como funciona
O algoritmo escolhe uma posição estável para passar, caso a trajetória dê errado, ela volta para trás e começa tudo de novo até achar a posição estável, se não achar, ela volta para trás novamente e assim em diante até achar a posição certa que leva para o final do labirinto

###### o algoritmo foi pensado para calcular a trajetória de um labirinto. Mas ele pode ser usado em outros casos, como calcular a trajetória de um lugar para o outro

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
0 : parede/trilha que não pode passar <br/>
1 : trilha <br/>
3 : final do labirinto <br/>
4 : trilha percorrida <br/>

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


### Saída
```
2 4 4 4 4
0 0 0 0 4
1 1 4 4 4
0 0 4 0 1
3 4 4 1 1
```
