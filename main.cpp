#include "src/fastway.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void func(std::vector<std::vector<int>> lab){
   int seg=1;
   system("clear");

   FastWay::print(lab, true);

   usleep(seg*1*1000);
}

int main() {
	vector<vector<int>> res = FastWay::run("file.txt", func);
	printf("\n");
	FastWay::print(res, true);

	return 0;
}
