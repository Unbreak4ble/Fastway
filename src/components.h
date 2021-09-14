namespace components {
  struct xy {
    int x;
    int y;
  };
  
  struct reOpt {
    std::string opt;
    xy idx;
  };
  
  void print(std::vector<std::vector<int>> res){
     for(int i=0; i<res.size(); i++){
       for(int j=0; j<res[i].size(); j++)
         std::cout << res[i][j] << (j != res[i].size()-1 ? " " : "");

         std::cout << std::endl;
      }
   }

   xy walk(std::vector<std::vector<int>> lab, xy idx, std::string opt){
     xy pos = {-1, -1};
     
    for(int i=0; i<lab.size(); i++){
       for(int j=0; j<lab[i].size(); j++){
         if(i == idx.y && j == idx.x){
           if(opt == "t"){
             if(i > 0)
               pos = {j, i-1};
           }else if(opt == "b"){
             if(i < lab.size()-1)
               pos = {j, i+1};
           }else if(opt == "r"){
             if(j < lab[i].size()-1)
               pos = {j+1, i};
           }else if(opt == "l"){
             if(j > 0)
               pos = {j-1, i};
           }else if(opt == "br"){
             if(j < lab[i].size()-1 && i < lab.size()-1)
               pos = {j+1, i+1};
           }else if(opt == "bl"){
             if(j > 0 && i < lab.size()-1)
               pos = {j-1, i+1};
           }else if(opt == "tr"){
             if(i > 0 && j < lab[i].size()-1)
               pos = {j+1, i-1};
           }else if(opt == "tl"){
             if(i > 0 && j > 0)
               pos = {j-1, i-1};
           }else throw std::string("Invalid walk option");
         }
       }
    }
    

     return pos;
   }

   int getPos(std::vector<std::vector<int>> lab, xy posis){
    for(int i=0; i<lab.size(); i++)
       for(int j=0; j<lab[i].size(); j++)
         if(i == posis.y && j == posis.x)
           return lab[i][j];
         
     return -1;
   }

   std::vector<xy> getSE(std::vector<std::vector<int>> lab){
        std::vector<xy> x = {{-1, -1}, {-1, -1}};
        int h = -1;
     for(int i=0; i<lab.size(); i++){
       if(h == -1)
          h = lab[i].size();
       else if(h != lab[i].size())
         throw std::string("size of horizontal dimensions does not match");
         
         
       for(int j=0; j<lab[i].size(); j++)
         if(lab[i][j] == 2){
           if(x[0].x == -1 && x[0].y == -1)
           x[0] = {j, i};
           else
           throw "cannot be started twice";
          }else if(lab[i][j] == 3){
           if(x[1].x == -1 && x[1].y == -1)
           x[1] = {j, i};
           else
           throw "cannot be end twice";
         }
       }

     return x;
   }
   
 void change(std::vector<std::vector<int>>& lab, xy posis, int value){
    
    for(int i=0; i<lab.size(); i++)
       for(int j=0; j<lab[i].size(); j++)
       {
         if(i == posis.y && j == posis.x)
         lab[i][j] = value;
       }
  }
  
  reOpt getAproxIdx(std::vector<std::vector<int>> lab, int alvo, xy idx){
    reOpt res = {"", {-1, -1}};
    std::vector<xy> posis = {
      walk(lab, idx, "r"),
      walk(lab, idx, "l"),
      walk(lab, idx, "t"),
      walk(lab, idx, "b"),
    };
    std::vector<std::string> sides = {"r", "l", "t", "b"};
    
    for(int i=0; i<posis.size(); i++)
      if(!(posis[i].x == -1 && posis[i].y == -1) && getPos(lab, posis[i]) == alvo)
       res = {sides[i], posis[i]};
    
    return res;
  }
  
  void replaceAll(std::vector<std::vector<int>>& lab, std::vector<xy> idxs, int val){
    for(auto i : idxs)
      change(lab, i, val);
  }
  
  void replaceAll(std::vector<std::vector<int>>& lab, std::vector<std::vector<xy>> idxs, int val){
    for(auto i : idxs)
       for(xy j : i)
         change(lab, j, val);
  }
  
  std::string readFile(std::string filename){
     std::ifstream file;
     std::string line, content;
     int l=0;
  
     file.open(filename);
     if(file.is_open())
     while(std::getline(file, line)){
     content += (l > 0 ? "\n" : "") + line;
     ++l;
     }
     else
     throw std::string("cannot open file");
  
     file.close();
     
     return content;
  }
  
  
  
  std::vector<std::vector<int>> interpret(std::string content){
    std::vector<std::vector<int>> lab;
    std::string num_s;
    std::vector<int> current;
   
    for(int i=0; i<=content.length(); i++){
      if(i < content.length()){
      char t = content[i];
      switch(t){
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
          if(num_s.length() == 0)
          num_s+=t;
          else
          throw std::string("Invalid number");
        break;
        
        case ',':
          if(num_s.length() == 1){
          current.push_back(atoi(num_s.c_str()));
          num_s = "";
          }
          else
          throw std::string("Invalid number");
        break;
        
        case '\n':
          if(num_s.length() == 1){
          current.push_back(atoi(num_s.c_str()));
          num_s = "";
          }
          else
          throw std::string("Invalid number");
          
          if(current.size() > 0){
          lab.push_back(current);
          current = {};
          }
          else
          throw std::string("Invalid text");
        break;
        
        default: 
          if(t != ' ')
          throw std::string("Invalid text");
        break;
      }
     }else{
          if(num_s.length() == 1){
          current.push_back(atoi(num_s.c_str()));
          num_s = "";
          }
          else
          throw std::string("Invalid number");
          
          if(current.size() > 0){
          lab.push_back(current);
          current = {};
          }
          else
          throw std::string("Invalid text");
     }
    }
    
    
    return lab;
  }
}

