#include <stdio.h>
#include <stdlib.h>

#define N 8

enum search { DFirst, BFirst };

typedef struct aresta {
  int destino, peso;
  struct aresta *prox;
} * LAdj;

typedef LAdj Grafo[N];

int mat[N][N] = {{0, 3, 0, 0, 2, 0, 0, 0}, {1, 0, 3, 0, 0, 2, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 4, 0, 0, 0, 0, 0},
                 {0, 1, 0, 0, 0, 0, 2, 3}, {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 3, 2, 0, 8, 0, 0, 0}, {0, 0, 0, 0, 0, 1, 0, 0}};

LAdj newA(int dest, int peso, LAdj a) {
  LAdj n = malloc(sizeof(struct aresta));
  n->destino = dest;
  n->peso = peso;
  n->prox = a;
  return n;
}

void constroiGrafo(int mat[N][N], Grafo g) {
  for (int i = 0; i < N; i++) {
    g[i] = NULL;
    for (int j = 0; j < N; j++)
      if (mat[i][j] != 0)
        g[i] = newA(j, mat[i][j], g[i]);
  }
}

int quantasArestas(Grafo g) {
  int n = 0;
  LAdj a;
  for (int i = 0; i < N; i++)
    for (a = g[i]; a; a = a->prox, n++)
      ;
  return n;
}

int capacidade(Grafo g, int v) {
  int n = 0;
  LAdj a;
  for (int i = 0; i < N; i++)
    for (a = g[i]; a; a = a->prox) {
      if (i == v)
        n -= a->peso;
      if (a->destino == v)
        n += a->peso;
    }
  return n;
}

int DFirstSearch(Grafo g, int v, int vis[]) {
  vis[v] = 1;
  int n = 1;
  LAdj a;
  for (a = g[v]; a; a = a->prox)
    if (!vis[a->destino])
      n += DFirstSearch(g, a->destino, vis);
  return n;
}

int BFirstSearch(Grafo g, int v, int vis[]) {
  int queue[N], frente, fim;
  int n = 0;
  queue[0] = v;
  frente = 0;
  fim = 1;
  vis[v] = 1;
  while (frente != fim) {
    v = queue[frente++];
    n++;
    for (LAdj a = g[v]; a; a = a->prox)
      if (!vis[a->destino]) {
        vis[a->destino] = 1;
        queue[fim++] = a->destino;
      }
  }
  return n;
}

int quantosAlc(Grafo g, int v, enum search s) {
  int vis[N];
  for (int i = 0; i < N; i++)
    vis[i] = 0;
  return (s == BFirst ? BFirstSearch(g, v, vis) : DFirstSearch(g, v, vis));
}

void printAlc(Grafo g, int v, enum search s) {
  int vis[N];
  for (int i = 0; i < N; vis[i] = 0, i++)
    vis[i] = 0;
  s == BFirst ? BFirstSearch(g, v, vis) : DFirstSearch(g, v, vis);
  for (int i = 0; i < N; i++)
    if (vis[i])
      printf("%d ", i);
  putchar('\n');
}

int main() {
  int v = 0;
  Grafo g;
  constroiGrafo(mat, g);
  printf("Numero de arestas: %d\n", quantasArestas(g));
  printf("Capacidade do vertice %d: %d\n", v, capacidade(g, v));
  putchar('\n');
  puts("Depth First:");
  printf("Numero de vertices alcancaveis a partir de %d: %d\n", v,
         quantosAlc(g, v, DFirst));
  printf("Vertices alcancaveis a partir de %d: ", v);
  printAlc(g, v, DFirst);
  putchar('\n');
  puts("Breadth First:");
  printf("Numero de vertices alcancaveis a partir de %d: %d\n", v,
         quantosAlc(g, v, BFirst));
  printf("Vertices alcancaveis a partir de %d: ", v);
  printAlc(g, v, BFirst);
  return 0;
}
