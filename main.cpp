#include "src/fastway.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void func(std::vector<std::vector<int>> lab){
   int seg=1;
   system("clear");

   FastWay::print(lab, true); // imprime o labirinto em forma colorida.

   usleep(seg*100*1000);
}

int main() {
	vector<vector<int>> res = FastWay::run("file.txt", func); // imprime o labirinto e retorna um callback a cada ação.
	printf("\n");
	FastWay::print(res, true); // imprime o labirinto em forma colorida.

	return 0;
}
