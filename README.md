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

### estrutura do labirinto em arquivo
```
2,1,1,1,1
0,0,0,0,1
1,1,1,1,1
0,0,1,0,0
3,1,1,1,1
```
Códigos: <br/>
2 : inicio do labirinto <br/>
0 : parede/trilha que não pode passar <br/>
1 : trilha <br/>
3 : final do labirinto <br/>
4 : trilha percorrida <br/>
5 : posição atual (usada somente no callback)<br/>

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

# callbacks ???
Sim. Seu uso não é obrigatório, mas isso irá deixar o terminal mais legal podendo visualizar cada ação do algoritmo sobre o labirinto.

```cpp
#include "src/fastway.h"
#include <iostream>
#include <unistd.h>

using namespace std;

// Estrutura padrão da função
void func(std::vector<std::vector<int>> lab){
   int seg=1;
   system("clear");

   FastWay::print(lab, true); // imprime o labirinto em forma colorida.

   usleep(seg*100*1000);
}

int main() {
	vector<vector<int>> res = FastWay::run("file.txt", func); // imprime o labirinto e retorna um callback a cada ação.
	printf("\n");
	FastWay::print(res); // imprime o labirinto.

	return 0;
}
```
