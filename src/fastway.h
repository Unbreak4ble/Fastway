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
     std::string reto = prox.opt;
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
           auto testProx =  components::getAproxIdx(newlab, 1, prox.idx, prox.opt);
           auto test = testProx.idx.x == -1 && testProx.idx.y == -1 ? components::getAproxIdx(newlab, 4, prox.idx, prox.opt) : testProx;
           
           if(test.idx.x == -1 && test.idx.y == -1){
           prox.idx = idx;
           prox.opt = reto;
           }else{
           prox.idx = test.idx;
           prox.opt = test.opt;
           }
           }else
           if(!(prox.idx.x == -1 && prox.idx.y == -1)){
           prox =  components::getAproxIdx(newlab, 1, prox.idx);
           
           reto = prox.opt;
           }
           else{
           needReturn = true;
           auto testProx =  components::getAproxIdx(newlab, 1, prox.idx);
           prox = testProx.idx.x == -1 && testProx.idx.y == -1 ? components::getAproxIdx(newlab, 4, prox.idx) : testProx;
           
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
     needReturn = true;
     
     if(results.size() > 0)
     for(int i=0; i<results[0].size(); i++){
       components::xy pos = results[0][i];
       prox = components::getAproxIdx(newlab, 1, pos);
       
       if(needReturn){
         components::replaceAll(newlab, components::slice(results[0], 0, i), 1);
         components::change(newlab, pos, 0);
         auto otherLabPos = start(newlab);
         for(auto rePos : otherLabPos)
           results.push_back(rePos);
         
         needReturn = false;
       }
       if(!(prox.idx.x == -1 && prox.idx.y == -1) && needReturn == false)
         needReturn = true;
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
