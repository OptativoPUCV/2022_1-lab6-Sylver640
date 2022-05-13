#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    int i, k, iSub, kSub;
    int *fila = calloc(10, sizeof(int));
    int *columna = calloc(10, sizeof(int));
    int *submatriz = calloc(10, sizeof(int));
    
    for (i = 0; i < 9; i++)
    {
      for (k = 0; k < 9; k++)
      {
        if (n->sudo[i][k] != 0)
        {
          if (fila[n->sudo[i][k]] == 1) 
            return 0;
          else 
            fila[n->sudo[i][k]] = 1;
        }
        
        if (n->sudo[k][i] != 0)
        {
          if (columna[n->sudo[k][i]] == 1) 
            return 0;
          else 
            columna[n->sudo[k][i]] = 1;
        }

        int p;
        for (p = 0; p < 9; p++)
        {
          iSub = 3*(k/3) + (p/3);
          kSub = 3*(k%3) + (p%3);
          for (int subA = 0; subA < 3; subA++)
          {
            for (int subB = 0; subB < 3; subB++)
            {
              if (submatriz[n->sudo[iSub][kSub]] == 1)
                return 0;
              else submatriz[n->sudo[iSub][kSub]] = 1;
            }
            for (int b = 0; b < 10; b++)
              submatriz[b] = 0;
          }
        }

      }
      for (int a = 0; a < 10; a++)
      {
        fila[a] = 0;
        columna[a] = 0;
        submatriz[a] = 0;
      }
    }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i, k;
    for (i = 0; i < 9; i++)
    {
      for (k = 0; k < 9; k++)
      {
        if (n->sudo[i][k] == 0)
        {
          for (int newValue = 1; newValue < 9; newValue++)
          {
            Node* adjNode = copy(n);
            adjNode->sudo[i][k] = newValue;
            //if (is_valid(adjNode))
            pushBack(list, adjNode);
          }
        }
      }
    }
    return list;
}


int is_final(Node* n){
    for (int i = 0; i < 9; i++)
    {
      for (int k = 0; k < 9; k++)
      {
        if (n->sudo[i][k] == 0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  int size = get_size(S);
  while (size != 0)
  {
    Node* n = top(S);
    if (!n) return NULL;
    pop(S);
    if (is_final(n) == 1) return n;

    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);
    while (aux != NULL)
    {
      push(S, aux);
      aux = next(adj);
    }
    
    free(n);
    cont++;
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/