#include <iostream>
using namespace std;
#include "rmst.h"

// Point
Point::Point() {
  x = 0;
  y = 0;
}
void Point::print(){
  cout << endl << "Point(" << x <<","<<y<<")"<<endl;
}

// Edge
Edge::Edge() {
  
}

// Line
Chain::Chain() {
    
}
Chain::Chain(vector<Point> points) {
  this->points = points;
}

// Plane
Plane::Plane() {
  Point p;
  p.x=1;
  p.y=1;
  terminals.push_back(p);
  p.x=2;
  p.y=2;
  terminals.push_back(p);
  p.x=3;
  p.y=3;
  terminals.push_back(p);
  p.x=5;
  p.y=4;
  terminals.push_back(p);
  p.x=4;
  p.y=5;
  terminals.push_back(p);
}

// Graph
Graph::Graph() {
  vertices.clear();
  edges.clear();
  degree = vertices.size();
}
void Graph::get_degree() {
  degree = vertices.size();
}
// get the 4 boundaries
void Graph::get_boundaries() {
  get_left();
  get_right();
  get_top();
  get_bottom();
}
// get MinX
void Graph::get_left() {
  lefts.clear();
  int minX = vertices[0].x;
  for(int i=1; i<vertices.size(); i++) {
    if(vertices[i].x < minX) {
      minX = vertices[i].x;
    }
  }
  for(int i=0; i<vertices.size(); i++) {
    if(vertices[i].x == minX) {
      lefts.push_back(i);
    }
  }
}

// get MaxX
void Graph::get_right() {
  rights.clear();
  int maxX = vertices[0].x;
  for(int i=1; i<vertices.size(); i++) {
    if(vertices[i].x > maxX) {
      maxX = vertices[i].x;
    }
  }
  for(int i=0; i<vertices.size(); i++) {
    if(vertices[i].x == maxX) {
      rights.push_back(i);
    }
  }
}
//get minY
void Graph::get_bottom() {
  bottoms.clear();
  int minY = vertices[0].y;
  for(int i=1; i<vertices.size(); i++) {
    if(vertices[i].y < minY) {
      minY = vertices[i].y;
    }
  }
  for(int i=0; i<vertices.size(); i++) {
    if(vertices[i].y == minY) {
      bottoms.push_back(i);
    }
  }
}
//get maxY
void Graph::get_top() {
  tops.clear();
  int maxY = vertices[0].y;
  for(int i=1; i<vertices.size(); i++) {
    if(vertices[i].y > maxY) {
      maxY = vertices[i].y;
    }
  }
  for(int i=0; i<vertices.size(); i++) {
    if(vertices[i].y == maxY) {
      tops.push_back(i);
    }
  }
}

// class RMST
RMST::RMST(const Plane& plane) {
  Node* new_node = new Node;
  new_node->graph.vertices = plane.terminals;
  new_node->next = NULL;
  trees_head = new_node;
}
void RMST::travel_trees() {
  Node* list = trees_head;
  while(list) {
    cout << endl << "--- travel_trees ---" << endl;
    process_one(list->graph);
    list = list->next;
  }
}
void RMST::process_one(Graph& graph) {
  int type = -1;
   do {
      type = is_one(graph);
      cout << endl << "type= " << type << endl;
      if(type == LEFT) {
        process_one_left(graph);
        graph.get_boundaries();
      }  
      if(type == RIGHT) {
        process_one_right(graph);
        graph.get_boundaries();
      }
      if(type == TOP) {
        process_one_top(graph);
        graph.get_boundaries();
      }
      if(type == BOTTOM) {
        process_one_bottom(graph);
        graph.get_boundaries();
      }
   } while(type);
}

void RMST::add_single_edge(Graph& graph, int direction) {
    graph.get_boundaries();
    Point new_point; 
    Edge edge;
    int index = -1;
    switch (direction) {
      case LEFT: 
        index = graph.lefts[0];
        new_point.x = graph.vertices[index].x + 1;
        new_point.y = graph.vertices[index].y;
        edge.shape = LEFT;
        break;      
      case RIGHT:
        index = graph.rights[0];
        new_point.x = graph.vertices[index].x - 1;
        new_point.y = graph.vertices[index].y;
        edge.shape = RIGHT;
        break;
      case TOP:
        index = graph.tops[0];
        new_point.x = graph.vertices[index].x;
        new_point.y = graph.vertices[index].y - 1;
        edge.shape = TOP;
        break;
      case BOTTOM:
        index = graph.bottoms[0];
        new_point.x = graph.vertices[index].x;
        new_point.y = graph.vertices[index].y + 1;
        edge.shape = BOTTOM;
        break;
      case -1:
        cout << endl << "! add_single_edge !" << endl;
        exit(0);
    }
    edge.start = graph.vertices[index];
    cout << endl <<"index= "<<index<<endl;
    cout << endl <<"++ " <<edge.start.x<<","<<edge.start.y<<" ++" << endl;
    vector<Point> temp = graph.vertices;
    graph.vertices.clear();
      for(int i=0; i<temp.size(); i++) {
        if(i!=index) graph.vertices.push_back(temp[i]);
      }
    Utilities util;
    util.output_graph_vertices(&graph);
    edge.end = new_point;
    graph.edges.push_back(edge);
    if(check_exist_point(new_point, graph) == false) {
        new_point.print();
        graph.vertices.push_back(new_point);
    }
    util.output_graph_vertices(&graph);
    graph.get_boundaries();
}
void RMST::process_one_left(Graph& graph) {
  cout << endl << "--- process_one_left ---" << endl;
  if(graph.lefts.size()!=1) {
    cout << endl << "! process_one_left !" << endl;
    exit(0);
  }
  add_single_edge(graph, LEFT);
}
void RMST::process_one_right(Graph& graph) {
  cout << endl << "--- process_one_right ---" << endl;
    if(graph.rights.size()!=1) {
      cout << endl << "! process_one_left !" << endl;
      exit(0);
    }
  add_single_edge(graph, RIGHT);
}
void RMST::process_one_top(Graph& graph) {
  cout << endl << "--- process_one_top ---" << endl;
    if(graph.tops.size()!=1) {
      cout << endl << "! process_one_left !" << endl;
      exit(0);
    }
  add_single_edge(graph, TOP);
}
void RMST::process_one_bottom(Graph& graph) {
  cout << endl << "--- process_one_bottom ---" << endl;
    if(graph.bottoms.size()!=1) {
      cout << endl << "! process_one_left !" << endl;
      exit(0);
    }
  add_single_edge(graph, BOTTOM);
}
int RMST::is_one(Graph& graph) {
  graph.get_boundaries();
  graph.get_degree();
  if(graph.degree == Single) return 0;
  if(graph.lefts.size() == Single) return LEFT;
  else if(graph.rights.size() == Single) return RIGHT;
  else if(graph.tops.size() == Single) return TOP;
  else if(graph.bottoms.size() == Single) return BOTTOM;
  else return 0;
}
bool RMST::check_exist_point(const Point& point, const Graph& graph) {
  for(int i=0; i<graph.vertices.size(); i++) {
    if((point.x == graph.vertices[i].x) && (point.y == graph.vertices[i].y)) {
      return true;
    }
  }
  return false;
}
void RMST::output_trees(const Plane& plane) {
  Utilities util;
  Node* iter = trees_head;
  while(iter) {
    util.output_graph(&iter->graph);
    util.output_steiner_tree_diagram(plane, (*iter).graph);
    iter = iter->next;
  }
}
// class Node
Node::Node() {
  next = NULL;
}
// class Utilities
void Utilities::output_vector_points(vector<Point> points) {
  cout << endl << "--- vector_points ---" << endl;
  cout << "size=" << points.size() << endl;
  for(int i=0; i<points.size(); i++) {
    cout << "(" << points[i].x <<"," << points[i].y << ") "; 
  }
  cout << endl;
}
void Utilities::output_graph(Graph* graph) {
  cout << endl << "--- graph ---" << endl;
  output_graph_vertices(graph);
  output_graph_edges(graph);
  output_graph_boundaries(graph);
  cout << endl;
}
void Utilities::output_graph_vertices(Graph* graph) {
  cout << endl << "--- graph_vertices ---" << endl;
  output_vector_points(graph->vertices);
  cout << endl;
}
void Utilities::output_graph_edges(Graph* graph) {
  cout << endl << "--- graph_edges ---" << endl;
  for(int i=0; i<graph->edges.size(); i++) {
    cout << "(<" << graph->edges[i].start.x << "," << graph->edges[i].start.y << ">, " 
      << "<" << graph->edges[i].end.x << "," << graph->edges[i].end.y << "> :" << graph->edges[i].shape <<") ";
  }
  cout << endl;
}
void Utilities::output_graph_boundaries(Graph* graph) {
  vector<Point> points;
  cout << endl << "--- graph_boundaries ---" << endl;
  cout << endl << "--- left ---" << endl;
  points.clear();
  for(int i=0; i<graph->lefts.size(); i++) {
    points.push_back(graph->vertices[graph->lefts[i]]);
  }
  output_vector_points(points);
  cout << endl << "--- right ---" << endl;
  points.clear();
  for(int i=0; i<graph->rights.size(); i++) {
    points.push_back(graph->vertices[graph->rights[i]]);
  }
  output_vector_points(points);
  cout << endl << "--- top ---" << endl;
  points.clear();
  for(int i=0; i<graph->tops.size(); i++) {
    points.push_back(graph->vertices[graph->tops[i]]);
  }
  output_vector_points(points);
  cout << endl << "--- bottom ---" << endl;
  points.clear();
  for(int i=0; i<graph->bottoms.size(); i++) {
    points.push_back(graph->vertices[graph->bottoms[i]]);
  }
  output_vector_points(points);
  cout << endl;
}
void Utilities::output_steiner_tree_diagram(const Plane& plane, const Graph& graph) {

  cout << endl << "--- steiner_tree_diagram ---" << endl;
  const int Max_Degree = 2*9;
  char pixels[Max_Degree][Max_Degree];
  const char DOT = '.';
  const char PIPE = '|';
  const char DASH = '_';
  const char VERTEX = '$';
  int index_row = Max_Degree/2;
  int index_col = 1;
  const int NUM_CHAR = 48;

    for(int i=0; i<Max_Degree; i++) {
    for(int j=0; j<Max_Degree; j++) {
      pixels[i][j]=' ';
    }
  }
  for(int i=0; i<Max_Degree; i++) {
    pixels[i][0] = index_row + NUM_CHAR;
    for(int j=1; j<Max_Degree; j++) {
      pixels[i][j] = DOT;
      j++;
    }
    i++;
    index_row--;
  }
  for(int j=1; j<Max_Degree; j++) {
    pixels[Max_Degree-1][j] = index_col + NUM_CHAR;
    j++;
    index_col++;
  }

  // add vertices
  index_row = 0;
  index_col = 0;
  for(int i=0; i<plane.terminals.size(); i++) {
    index_row = (Max_Degree-1) - 2*plane.terminals[i].y+1;
    index_col = 2*(plane.terminals[i].x)-1;
    if(index_row<0 || index_row>=Max_Degree) {
      cout << "! index_row !" << endl;
      exit(0);
    }
    if(index_col<0 || index_col>=Max_Degree) {
      cout << "! index_col !" << endl;
      exit(0);
    }
   pixels[index_row][index_col] = VERTEX;
  }
  cout << endl << "&&&&&&&&&&& size= "<<graph.edges.size() << endl;
  for(int i=0; i<graph.edges.size(); i++) {
    index_row = 0; 
    index_col = 0;
    switch(graph.edges[i].shape) {
      case LEFT:
        index_row = (Max_Degree-1) - 2*graph.edges[i].start.y+1;
        index_col = 2*(graph.edges[i].start.x);
        pixels[index_row][index_col] = DASH;
        break;
      case RIGHT:
        index_row = (Max_Degree-1) - 2*graph.edges[i].start.y+1;
        index_col = 2*(graph.edges[i].end.x);
        pixels[index_row][index_col] = DASH;
        break;
      case TOP:
        index_row = (Max_Degree-1) - 2*graph.edges[i].start.y+2;
        index_col = 2*(graph.edges[i].start.x)-1;
        pixels[index_row][index_col] = PIPE;
        break;
      case BOTTOM:
        index_row = (Max_Degree-1) - 2*graph.edges[i].end.y+2;
        index_col = 2*(graph.edges[i].start.x)-1;
        pixels[index_row][index_col] = PIPE;
        break;
      default:
        cout << endl << "! graph.edges[" << i << "].shape !" << endl;
        exit(0);
    }
  }
  // print
  cout << endl;
  for(int i=0; i<Max_Degree; i++) {
    for(int j=0; j<Max_Degree; j++) {
      cout << pixels[i][j];
    }
    cout << endl;
  }
}

