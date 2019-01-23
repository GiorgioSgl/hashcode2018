using namespace std;
#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <queue>

struct macchina{
  int tempo = 0;
  int rowCella = 0;
  int colCella = 0;
  queue<int> coda;
  //bool operator() (int i,int j) { return (i<j);}
};

struct corsa{
  int rowPart;  
  int colPart;
  int rowArr;
  int colArr;
  int minPart;
  int maxArr;
  bool val = true;
  bool vis = false;
  
};

vector<corsa> corse;
vector<macchina> macchine;

int distanza(int rowPart, int colPart, int rowArr, int colArr);

int scegli(int row, int col, int tempo,int &timePartenza){
  int percorso=-1;
  int min=INT_MAX;
  int temp;
  int dist;
  int soglia;
  for(int i=0; i<corse.size(); i++){
    
    if(corse[i].vis==false && corse[i].val==true){ //se non è gia stato visitato
      dist = distanza(row,col,corse[i].rowPart,corse[i].colPart);
      if(corse[i].minPart>=tempo+dist)
        soglia=corse[i].minPart;
      else
        soglia=tempo+dist;
    
      if (soglia<min){
        min=soglia;
        percorso=i;
      }
    }
  }
  //cout << min << endl;
  timePartenza=min;
  return percorso;
}

bool finito(){
  
  for(int i=0; i<corse.size(); i++){
    if(corse[i].vis==false)
      return false;
  }
  
  return true;
}

void printCoda(){
  ofstream out("output5.txt");
  for(int i=0; i<macchine.size();i++){
    out << macchine[i].coda.size() << " ";
    while(!macchine[i].coda.empty()){
      out << macchine[i].coda.front() << " ";
      macchine[i].coda.pop();
    }
    out << endl;
  }
}

void ordina(vector <macchina> &macchine){
   
   int alto;
   for (alto = macchine.size() - 1; alto > 0; alto— )
     { 
         for (int i=0; i<alto; i++)
         {
           if (macchine[i].tempo>macchine[i+1].tempo) /* sostituire ">" con "<" per avere un ordinamento decrescente */
           { 
             macchina tmp = macchine[i]; 
             macchine[i] = macchine[i+1]; 
             macchine[i+1] = tmp;
           } 
         }
     }
     
}

int scegliMacchina(){
  int res;
  int minTempo=INT_MAX;
  for(int i=0;i<macchine.size();i++){
    if(minTempo>macchine[i].tempo){
      res=i;
      minTempo=macchine[i].tempo;
    }
  }
  
  return res;
}

int main(){
  
  int nRighe;
  int nColonne;
  int nVeicoli;
  int nCorse;
  int bonus;
  int nStep;
  
  
  ifstream in("input5.txt");
  in»nRighe»nColonne»nVeicoli»nCorse»bonus»nStep;
  
  
  corse.resize(nCorse);
  macchine.resize(nVeicoli);
  
  
  for(int i=0; i<nCorse; i++){
  
    in » corse[i].rowPart » corse[i].colPart 
       » corse[i].rowArr » corse[i].colArr
       » corse[i].minPart » corse[i].maxArr;
       
    if(corse[i].maxArr < corse[i].minPart + distanza(corse[i].rowPart, corse[i].colPart, corse[i].rowArr, corse[i].colArr)) corse[i].val = false;
  
  }
  
  
  
  int m;
  while(!finito()){
    m=scegliMacchina();
    
    int timePartenza;
    int way = scegli(macchine[m].rowCella,macchine[m].colCella,macchine[m].tempo,timePartenza);
    
    if(way!=-1){
      macchine[m].tempo=timePartenza+distanza(corse[way].rowPart,corse[way].colPart,corse[way].rowArr,corse[way].colArr);
      macchine[m].rowCella=corse[way].rowArr;
      macchine[m].colCella=corse[way].colArr;  
      macchine[m].coda.push(way);  
      corse[way].vis=true;
    }
    
    
  }
  printCoda();
  
  
  
  
//  for(int i=0; i<nCorse; i++){
//    
//    cout<<" corsa "<<i<<endl;
//  
//    cout << corse[i].rowPart << corse[i].colPart 
//       << corse[i].rowArr << corse[i].colArr
//       << corse[i].minPart << corse[i].maxArr <<corse[i].val;
//       
//    cout<<endl;
//  
//  }
  
  

  return 0;
  
}




int distanza(int rowPart, int colPart, int rowArr, int colArr){
  int rowDist=0, colDist=0, distanza=0;
  rowDist = rowArr-rowPart;
  colDist = colArr-colPart;
  if(rowDist<0)
     rowDist= -rowDist;
  if(colDist<0)
    colDist=-colDist;
  distanza=rowDist+colDist;
  return distanza;    
}
