#include <vector>
#include <iostream>
#include <fstream>
#include "components.h"

namespace FastWay {
  
   // responsavel por calcular a trajetória
   std::vector<std::vector<components::xy>> start(std::vector<std::vector<int>> lab){
     auto newlab = lab;
     auto SE = components::getSE(lab);
     auto prox = components::getAproxIdx(lab, 1, SE[0]);
     bool stop = prox.idx.x == -1 && prox.idx.y == -1;
     std::vector<std::vector<components::xy>> results;
     std::vector<components::xy> passed;
     std::string reto = !stop ? prox.opt : "";
     bool needReturn = false;
     
     while(!stop){
       auto idx3 = components::getAproxIdx(newlab, 3, prox.idx);
     
       passed.push_back(prox.idx);
       
       if(!(idx3.idx.x == -1 && idx3.idx.y == -1)){
       results.push_back(passed);
       stop = true;
       }
       
       if(!needReturn){
          components::change(newlab, prox.idx, 4);
         
            auto idx = components::walk(newlab, prox.idx, reto);
            
           if(!(idx.x == -1 && idx.y == -1) && components::getPos(newlab, idx) == 1){
           prox.idx = idx;
           prox.opt = reto;
           }else
           if(!(prox.idx.x == -1 && prox.idx.y == -1)){
           prox = components::getAproxIdx(newlab, 1, prox.idx);
           reto = prox.opt;
           }
           else{
           needReturn = true;
           prox = components::getAproxIdx(newlab, 1, prox.idx);
           }
      
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
     }
     
     for(auto vetor : results){
       components::replaceAll(newlab, {vetor[0], vetor[vetor.size()-1]}, 0);
       auto newTraje = start(newlab);
       if(newTraje.size() > 0){
         for(auto traje : newTraje)
           results.push_back(traje);
       }
     }
     
     return results;
   }
  
   
   std::vector<std::vector<int>> run(std::vector<std::vector<int>> lab){
     auto results = start(lab);
     std::vector<components::xy> better = components::getBetter(results);
     components::replaceAll(lab, better, 4);
     
     return lab;
   }
   
   std::vector<std::vector<int>> run(std::string filename){
     std::string content = components::readFile(filename);
     auto lab = components::interpret(content);
     return run(lab);
   }

}
