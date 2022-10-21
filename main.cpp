#include "src/fastway.h"
#include <iostream>
#include <unistd.h>

using namespace std;

void func(std::vector<std::vector<int>> lab){
   int seg=1;
   system("clear");

   FastWay::print(lab, true);

   usleep(seg*100*1000);
}

int main() {
	vector<vector<int>> lab = {
   {2,1,1,1,1},
   {0,0,0,0,1},
   {1,1,0,1,1},
   {0,0,1,0,1},
   {3,1,1,1,1}
  };

	vector<vector<int>> res = FastWay::run(lab, func);

	FastWay::print(res);

	return 0;
}
