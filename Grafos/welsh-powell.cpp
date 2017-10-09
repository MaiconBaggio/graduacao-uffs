#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vii;

int welsh_powell(vii &grafo);

int main(void){
  int numeroVertices, numeroArestas, u, v;

  cin >> numeroVertices >> numeroArestas;
  vii grafo(numeroVertices);
  
  while(numeroArestas--){
    cin >> u >> v;
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }
  
  cout << welsh_powell(grafo) << '\n';
  
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
    for(int u = 0, flag = 1; u < grauVertice.size(); u++, flag = 1)
      if(corVertice[grauVertice[u].second] == -1){
	for(auto w : grafo[grauVertice[u].second])
	  if(corVertice[w] == cor)
	    flag = 0;
	if(flag)
	  corVertice[grauVertice[u].second] = cor, v--;
      }
  }
  return cor;
}
