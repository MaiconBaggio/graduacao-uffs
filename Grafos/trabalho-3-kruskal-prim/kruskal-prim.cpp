/**
 **  Maicon Dinkel Baggio
 **  maiconbaggio@outlook.com
 **
 **  Implementação dos algoritmos Kruskal e Prim
 **
 **  Compilar: make 
 **
 **/

#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define INF 100000008

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> edge;
typedef vector<ii> vi;
typedef vector<vi> vii;

class disjointSet;
int kruskal(vector<edge> &arestas, vector<edge> &arvoreMinima);
int prim(vii &grafo, int inicio, vector<edge> &arvoreMinima);

int main(void){
  int tipo, numeroVertices, numeroArestas, u, v, w;
  
  while(cin >> tipo >> numeroVertices >> numeroArestas){

    vector<edge> arestas(numeroArestas), arvoreMinima(numeroVertices - 1);
    vii grafo(numeroVertices, vi());
  
    while(numeroArestas--){
      cin >> u >> v >> w;
      if(tipo){
	grafo[u].push_back(ii(v, w));
	grafo[v].push_back(ii(u, w));
      }
      else
	arestas.push_back(edge(w, ii(u, v)));
    }

    if(tipo)
      cout << "Arvore Geradora Minima com Prim : " << prim(grafo, 0, arvoreMinima) << '\n';
    else
      cout << "Arvore Geradora Minima com Kruskal : " << kruskal(arestas,  arvoreMinima) << '\n';

    cout << "Arestas da Arvore Geradora Minima (u<-->v  w)\n";
    for(auto it : arvoreMinima)
      cout << it.second.first << ' ' << it.second.second << ' ' <<it.first << '\n';
    cout << "\n\n\n";
    
  }
  
  return 0;
}

class disjointSet{
public:
  int numSets;
  vector<int> setSize, rank;
  disjointSet(int tamanho){
    numSets = tamanho;
    setSize.assign(tamanho, 0);
    rank.assign(tamanho, 0);
    for(int i = 0; i < tamanho; i++)
      setSize[i] = i, rank[i] = 0;
  }
  int find(int x){
    return setSize[x] == x ? x : setSize[x] = find(setSize[x]);
  }
  void unity(int u, int v){
    int ru = find(u), rv = find(v);
    if(ru == rv) return;
    numSets--;
    if(rank[v] < rank[u]){
      unity(v, u);
      return;
    }
    setSize[ru] = rv;
    if(rank[u] == rank[v]) rank[v]++;
  }
};

int kruskal(vector<edge> &arestas, vector<edge> &arvoreMinima){
  int MST = 0, pos = 0;
  disjointSet muf(arestas.size());
  sort(arestas.begin(), arestas.end());
  for(auto it : arestas)
    if(muf.find(it.second.first) != muf.find(it.second.second)){
      arvoreMinima[pos++] = it;
      muf.unity(it.second.first, it.second.second);
      MST += it.first;
    }
  return MST;
}

int prim(vii &grafo, int inicio, vector<edge> &arvoreMinima){
  int resp = 0, pos = 0;
  vector<int> dist(grafo.size(), INF), vis(grafo.size(), 0);
  priority_queue< edge, vector<edge>, greater<edge> > pqueue;
  pqueue.push(edge(0, ii(inicio, 0)));
  dist[inicio] = 0;
  
  while(!pqueue.empty()){
    int u = pqueue.top().second.first, a = pqueue.top().second.second;
    pqueue.pop();
    if(vis[u]) continue;
    vis[u] = 1; resp += dist[u];
    if(u != a)
      arvoreMinima[pos++] = edge(dist[u],ii(a, u));
    for(auto v : grafo[u])
      if(v.second < dist[v.first]  && !vis[v.first]){
	dist[v.first] = v.second;
	pqueue.push(edge(dist[v.first],ii(v.first, u)));
      }
  }
  return resp;
}
