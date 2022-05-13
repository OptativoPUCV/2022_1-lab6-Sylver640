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
    int i, k;
    int *fila = calloc(10, sizeof(int));
    int *columna = calloc(10, sizeof(int));
    //int submatriz[10] = {0,0,0,0,0,0,0,0,0,0};

    for (i = 0; i < 9; i++)
    {
      for (k = 0; k < 9; k++)
      {
        if (fila[n->sudo[i][k]] == 0)
          fila[n->sudo[i][k]] = 1;
        else return 0;
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
    return 0;
}

Node* DFS(Node* initial, int* cont){
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