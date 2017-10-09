#include <iostream>
#include <vector>
#include <queue>

#define INICIO 1

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vii;

bool isBipartiteBFS(vii &grafo, int w);
bool isBipartiteDFS(vii &grafo, int u, vi &cor);

int main(void){
  int numeroVertices, numeroArestas, u, v;

  cin >> numeroVertices >> numeroArestas;
  vii grafo(numeroVertices + 1, vi());

  while(numeroArestas--){
    cin >> u >> v;
    grafo[u].push_back(v);
    grafo[v].push_back(u);
  }

  vi corDFS(grafo.size(), -1);
  corDFS[INICIO] = 0;
  
  cout << "Check bipartido BFS: " << (isBipartiteBFS(grafo, INICIO) ? "SIM\n" : "NAO\n" );
  cout << "Check bipartido DFS: " << (isBipartiteDFS(grafo, INICIO, corDFS)  ? "SIM\n" : "NAO\n");
  
  return 0;
}

bool isBipartiteBFS(vii &grafo, int w){
  vi cor(grafo.size(), -1);
  queue<int> fila;
  cor[w] = 0;
  fila.push(w);
  
  while(!fila.empty()){
    int u = fila.front();
    fila.pop();

    for(auto v : grafo[u])
      if(cor[v] == -1){
	cor[v] = !cor[u];
	fila.push(v);
      }
      else if(cor[u] == cor[v])
	return false;      
  }
  return true;
}

bool isBipartiteDFS(vii &grafo, int u, vi &cor){
  for(auto v : grafo[u])
    if(cor[v] == -1){
      cor[v] = !cor[u];
      isBipartiteDFS(grafo, v, cor);
    }
    else if(cor[u] == cor[v])
      return false;
  return true;
}
