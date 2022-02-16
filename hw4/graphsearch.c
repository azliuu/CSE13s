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

// written path contains

bool path_contains(LLPath *path, int v) {
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

LLint *enqueue(LLint *q, int val) {
  LLint *newnode = calloc(1, sizeof(LLint));
  newnode->val = val;

  if (q == NULL) {
    return newnode;
  }

  LLint *cur = q;
  while (cur->next != NULL) {
    cur = cur->next;
  }
  cur->next = newnode;
  return q;
}

bool dequeue(LLint **q, int *ret) {
  if (*q == NULL) {
    return false;
  }

  *ret = (*q)->val;

  LLint *freethis = *q;
  *q = (*q)->next;
  free(freethis);
  return true;
}

// Breadth-first search!
Path graph_find_path_bfs(Graph *g, int i, int j) {
  // YOUR CODE HERE
  // LLPath *to_visit = NULL;
  // LLPath *visited = NULL;
  //
  if (i == j) {
    Path node;
    node.steps = 1;
    node.vertices_visited[0] = i;
    return node;
  }

  LLPath *to_visit = calloc(1, sizeof(LLPath));
  LLint *visited = NULL;
  // to_visit2->val.steps = 1;
  // LLint *visited = NULL;
  // LLint *to_visit = NULL;

  // to_visit = enqueue(to_visit, i);
  Path starting; // starting node
  starting = to_visit->val;
  starting = path_extend(starting, i);
  // to_visit->val.vertices_visited[i] = i;

  to_visit = enqueue_path(to_visit, starting); // enqueue the starting node

  while (to_visit != NULL) {
    Path current;
    // dequeue_path(&to_visit, &to_visit->val);
    dequeue_path(&to_visit, &current);

    for (int k = 0; k < current.steps; i++) {
      if (current.vertices_visited[k] == j) {
        return current;
      }
    }
    // visited = add_to_set(visited, current);
    // current.vertices_visited[current.steps] = j;
    visited = add_to_set(visited, current.vertices_visited[i]);

    // paths->next.val = path_extend(paths->val, i);
    // paths->next->val.vertices_visited[paths->val.steps] = i;
    // to_visit2->val.vertices_visited[current] = current;

    for (int neighbor = 0; neighbor < g->vertices; neighbor++) {
      if (graph_has_edge(g, current.vertices_visited[current.steps],
                         neighbor) &&
          !set_contains(visited, neighbor)) {
        // to_visit = enqueue(to_visit, neighbor);
        Path temp;
        temp = current;
        temp = path_extend(temp, neighbor);
        // to_visit->val = path_extend(current, neighbor);
        to_visit = enqueue_path(to_visit, temp);
      }
    }
  }
  Path empty = {0, {0}};
  return empty;
}

// Depth-first search!

bool stack_push(LLPath *q, Path path) {
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

bool stack_pop(LLPath **q, Path *ret) {
  if (*q == NULL) {
    return false;
  }

  *ret = (*q)->val;

  LLPath *freethis = *q;
  *q = (*q)->next;
  free(freethis);
  return true;
}

void graph_destroy(Graph **g) {
  int **child = (*g)->matrix;
  while (child != NULL) {
    free(&child);
  }
  free(*g);
  g = NULL;
  return;
}

Path graph_find_path_dfs(Graph *g, int i, int j) {
  // YOUR CODE HERE

Path empty = {0, {0}};
return empty;
}
