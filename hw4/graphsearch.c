#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graphsearch.h"

// dealing with sets of integers. We wrote these in class.
LLint *add_to_set(LLint *set, int val) {
  LLint *newfront = calloc(1, sizeof(LLint));
  newfront->val = val;
  newfront->next = set;

  return newfront;
}

bool set_contains(LLint *set, int val) {
  if (set == NULL) {
    return false;
  } else if (set->val == val) {
    return true;
  } else {
    return set_contains(set->next, val);
  }
}

//written path contains

bool path_contains(LLPath *path, int v)
{
  if (path == NULL) {
    return false;
  } else {
    for (int i = 0; i < path->val.steps; i++) {
      if (path->val.vertices_visited[i] == v) {
        return true;
      }
    }
  }
  return path_contains(path->next, v);
}

// Linked lists of paths. You'll need to implement these.

// Returns the new front of the queue, for a queue of Path structs.
// Usually this will be the old front of the queue, but if q is NULL, then it
// will allocate a new linked list node and return that.
LLPath *enqueue_path(LLPath *q, Path path) {
  // YOUR CODE HERE
  LLPath *newfront = calloc(1, sizeof(LLPath));
  newfront->val = path;

  if (q == NULL) {
    return newfront;
  }

  LLPath *cur = q;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = newfront;

  return q;
}

bool dequeue_path(LLPath **q, Path *ret) {
  // YOUR CODE HERE
  if (*q == NULL) {
    return false;
  }

  *ret = (*q)->val;

  LLPath *freethis = *q;
  *q = (*q)->next;
  free(freethis);
  return true;
}

// We wrote these in class.
Graph *graph_create(int vertices) {
  Graph *g = (Graph *)malloc(sizeof(Graph));
  g->vertices = vertices;
  g->matrix = (int **)calloc(vertices, sizeof(int *));
  for (int i = 0; i < vertices; i++) {
    g->matrix[i] = (int *)calloc(vertices, sizeof(int));
  }
  return g;
}

void graph_add_edge(Graph *g, int i, int j) { g->matrix[i][j] = 1; }

bool graph_has_edge(Graph *g, int i, int j) { return g->matrix[i][j]; }

// Convenience method for you -- returns a new Path where you have added another
// vertex along the path.
Path path_extend(Path path, int new_vertex) {
  Path out;
  out.steps = path.steps;

  for (int i = 0; i < path.steps; i++) {
    out.vertices_visited[i] = path.vertices_visited[i];
  }
  out.vertices_visited[path.steps] = new_vertex;
  out.steps += 1;
  return out;
}

// Print out a path nicely for the user.
void print_path(Path path) {
  if (path.steps == 0) {
    puts("(empty path)");
  }
  for (int i = 0; i < path.steps; i++) {
    printf("%s%d", (i == 0) ? "" : " -> ", path.vertices_visited[i]);
  }
  puts("");
}

// Breadth-first search!
Path graph_find_path_bfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.
  // keep track of a set of paths that we have visited
  // keep a queue of paths that we want to visit
  // while I have more paths to visit
  //    get the next path to visit
  //    see if it's where we're going (Path.vertices_visted[j] == j)
  //    if it's not, enqueue of all the neighbor paths that have not been
  //    visited
  // return false if we're out of paths

  // Path *visited = NULL;
  //LLPath *to_visit = calloc(1, sizeof(LLPath));

 LLPath *to_visit = NULL;


  to_visit->val = path_extend(to_visit->val, i);
  to_visit = enqueue_path(to_visit, to_visit->val);

  while (to_visit != NULL) {

    dequeue_path(&to_visit,  &to_visit->val);
    for (int i = 0; i < to_visit->val.steps; i++) {
        if (to_visit->val.vertices_visited[i] == j) {
            return to_visit->val;
        }
    }

    to_visit->val = path_extend(to_visit->val, i);
    to_visit = enqueue_path(to_visit, to_visit->val);

    for (int neighbor = 0; neighbor < g->vertices; neighbor++) {
      if (graph_has_edge(g, i,
                         neighbor) &&
          !(path_contains(to_visit, neighbor))) {
        to_visit->val = path_extend(to_visit->val, neighbor);
        to_visit = enqueue_path(to_visit, to_visit->val);
      }
    }
  }

  Path empty = {0, {0}};
  return empty;
}

// Depth-first search!
/*
bool path_push(LLPath *q, Path p) {
  Node *newtop = (Node *)calloc(1, sizeof(Node));
  if (newtop == NULL) {
    return false;
  }
  newtop->item = item;
  newtop->next = s->top;
  s->top = newtop;
  return true;
}
*/


Path graph_find_path_dfs(Graph *g, int i, int j) {
  // YOUR CODE HERE.

  Path empty = {0, {0}};
  return empty;
}
