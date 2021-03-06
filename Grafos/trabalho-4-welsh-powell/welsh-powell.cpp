/**
 **  Maicon Dinkel Baggio
 **  maiconbaggio@outlook.com
 **
 **  Implementação do algoritmo Welsh-Powell
 **
 **  Compilar: make 
 **
 **/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vii;

int welsh_powell(vii &grafo);

int main(void){
  int numeroVertices, numeroArestas, temp;
  char u, v;

  cin >> numeroVertices >> numeroArestas;
  vii grafo(numeroVertices);
  
  while(numeroArestas--){
    cin >> u >> v;
    grafo[u - 'a'].push_back(v - 'a');
    grafo[v - 'a'].push_back(u - 'a');
  }
  
  temp = welsh_powell(grafo);
  cout << "Numero de Cores: " << temp << '\n';
  
  return 0;
}

int welsh_powell(vii &grafo){
  int v = 0, cor = 0;
  vector<ii> grauVertice(grafo.size(), ii());
  vi corVertice(grafo.size(), -1);

  for(auto &vertice : grauVertice)
    vertice = ii(grafo[v].size(), v), v++;
  sort(grauVertice.begin(), grauVertice.end(), greater<ii>());
 
  for(; v; cor++){
    for(int u = 0, flag = 1; u < (int)grauVertice.size(); u++, flag = 1)
      if(corVertice[grauVertice[u].second] == -1){
	for(auto w : grafo[grauVertice[u].second])
	  if(corVertice[w] == cor)
	    flag = 0;
	if(flag)
	  corVertice[grauVertice[u].second] = cor, v--;
      }
  }
  
  cout << "Vertices: ";
  for(auto vertice : grauVertice)
    cout << (char)(vertice.second + 'a') << ' ';

  cout << "\nGrau:     ";
  for(auto vertice : grauVertice)
    cout << vertice.first << ' ';
  
  cout << "\nCor:      ";
  for(auto vertice : corVertice)
    cout << vertice << ' ';
  cout << '\n';
  
  return cor;
}
