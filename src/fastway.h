#include <vector>
#include <iostream>
#include <fstream>
#include "components.h"

namespace FastWay {
  
   void print(std::vector<std::vector<int>> res, bool color=false){
     for(int i=0; i<res.size(); i++){
       for(int j=0; j<res[i].size(); j++)
         if(!color)
         std::cout << res[i][j] << (j != res[i].size()-1 ? " " : "");
	 else{
	 int pos = res[i][j];
	 std::string color = "97";

	switch(pos){
	case 0:
	color = "30";
	break;

	case 1:
	color = "37";
	break;

	case 2:
	color = "31";
	break;

	case 3:
	color = "32";
	break;

	case 4:
	color = "33";
	break;

	case 5:
	color = "34";
	break;
	}

	 std::cout << "\x1b[" << color << "m" << "◼" << "\033[0m" << (j != res[i].size()-1 ? " " : "");
         }
         std::cout << std::endl;
      }
   }


   // responsavel por calcular a trajetória
   std::vector<std::vector<components::xy>> start(std::vector<std::vector<int>> lab, void(*callback)(std::vector<std::vector<int>>), bool optimize=true){
     auto newlab = lab, cbnewlab = lab;
     auto SE = components::getSE(lab);
     auto prox = components::getAproxIdx(lab, 1, SE[0]);
     bool stop = prox.idx.x == -1 && prox.idx.y == -1;
     std::vector<std::vector<components::xy>> results; // armazena possibilidade de varias posicoes do inicio ao fim
     std::vector<components::xy> passed; // armazena posicoes do inicio ao fim
     std::string reto = prox.opt; // direcao atual da posicao
     bool needReturn = false;
     
     while(!stop){
       auto idx3 = components::getAproxIdx(newlab, 3, prox.idx);
     
       passed.push_back(prox.idx); // adiciona

       // checa se a posicao final foi encontrada
       if(!(idx3.idx.x == -1 && idx3.idx.y == -1)){
       //se for encontrada, ira asicionar o array de posicoes para um outro array que armazena probabilidade de posicoes corretas que levam do inicio ao fim
       results.push_back(passed);
       stop = true;
       }
       
       if(!needReturn){
          // define o valor 4 (trilha percorrida) na posicao prox.idx
          components::change(newlab, prox.idx, 4);
         
	   // anda para a proxima posicao
           auto idx = components::walk(newlab, prox.idx, reto);
           if(!(idx.x == -1 && idx.y == -1) && components::getPos(newlab, idx) == 1){
           auto testProx =  components::getAproxIdx(newlab, 1, prox.idx, prox.opt);
           auto test = testProx.idx.x == -1 && testProx.idx.y == -1 ? components::getAproxIdx(newlab, 4, prox.idx, prox.opt) : testProx;
           
           if(test.idx.x == -1 && test.idx.y == -1){
           prox.idx = idx;
           prox.opt = reto;
           }else{
           prox.idx = test.idx;
           prox.opt = test.opt;
           }
           }else if(!(prox.idx.x == -1 && prox.idx.y == -1)){
           prox =  components::getAproxIdx(newlab, 1, prox.idx);
           
           reto = prox.opt;
           }
           else{
           needReturn = true;
           auto testProx =  components::getAproxIdx(newlab, 1, prox.idx);
           prox = testProx.idx.x == -1 && testProx.idx.y == -1 ? components::getAproxIdx(newlab, 4, prox.idx) : testProx;
           }

          cbnewlab = newlab;
          components::change(cbnewlab, prox.idx, 5);
       }else{
          for(int i=passed.size()-1; i>=0 && needReturn == true; i--){
            prox = components::getAproxIdx(newlab, 1, passed[i]);
            auto prox2 = components::getAproxIdx(newlab, 2, passed[i]);
           
           if(!(prox.idx.x == -1 && prox.idx.y == -1))
           {
             reto = prox.opt;
             passed.push_back(prox.idx);
             components::change(newlab, prox.idx, 4);
             needReturn = false;
           }else if(!(prox2.idx.x == -1 && prox2.idx.y == -1)){
             reto = prox2.opt;
             passed.erase(passed.end()-1);
             components::change(newlab, passed[i], 0);
             prox = components::getAproxIdx(newlab, 1, prox2.idx);
             needReturn = false;
           }else
            passed.erase(passed.end()-1);
          }
          
         stop = needReturn;
       }
     if(callback != nullptr)
     callback(cbnewlab);
     }
     needReturn = true;

     if(results.size() > 0 && optimize)
     for(int i=0; i<results[0].size(); i++){
       components::xy pos = results[0][i];
       prox = components::getAproxIdx(newlab, 1, pos);
       
       if(needReturn){
         components::replaceAll(newlab, components::slice(results[0], 0, i), 1);
         components::change(newlab, pos, 0);
         auto otherLabPos = start(newlab, callback, optimize);
         for(auto rePos : otherLabPos)
           results.push_back(rePos);
         
         needReturn = false;
       }
       if(!(prox.idx.x == -1 && prox.idx.y == -1) && needReturn == false)
         needReturn = true;
     }
     
     return results;
   }
  

   std::vector<std::vector<int>> run(std::vector<std::vector<int>> lab, void(*callback)(std::vector<std::vector<int>>)=nullptr, bool optimize=true){
     auto results = start(lab, callback, optimize);
     std::vector<components::xy> better = components::getBetter(results);
     components::replaceAll(lab, better, 4);

     return lab;
   }
   
   std::vector<std::vector<int>> run(std::string filename, void(*callback)(std::vector<std::vector<int>>)=nullptr, bool optimize=true){
     std::string content = components::readFile(filename);
     auto lab = components::interpret(content);
     return run(lab, callback, optimize);
   }

   
}
