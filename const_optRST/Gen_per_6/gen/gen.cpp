#include "gen.h"
#include<algorithm>
#include <fstream>
const unsigned int DEGREE = 6;
const unsigned int STOP = 1000;
const unsigned int LEFT =1;
const unsigned int RIGHT =2;
const unsigned int BOT =3;
const unsigned int TOP =4;

const unsigned int EXCL = 33;

Point::Point() {
  x = 0;
  y = 0;
}
H_Segment::H_Segment() {
  left.x = 0;
  left.y = 0;
  right.x = 0;
  right.y = 0;
  shape = 0;
}
V_Segment::V_Segment() {
  bot.x = 0;
  bot.y = 0;
  top.x = 0;
  top.y = 0;
  shape = 0;
}
Graph::Graph() {
  vertices.clear();
  h_segments.clear();
  h_vector.clear();
  for (unsigned int i = 0; i < DEGREE; i++) {
    h_vector.push_back(0);
  }
  v_segments.clear();
  v_vector.clear();
  for (unsigned int i = 0; i < DEGREE; i++) {
    v_vector.push_back(0);
  }
  boundary_left.clear();
  boundary_right.clear();
  boundary_top.clear();
  boundary_bot.clear();
  size = vertices.size();
  grown = false;
  valid = true;
  length = 0;
}
void Graph::update() {
  set_size();
  set_boundary();
  set_length();
}
void Graph::set_size() {
  size = vertices.size();
}
void Graph::set_length() {
  unsigned int total = 0;
  for (unsigned int i = 0; i < h_vector.size(); i++) {
    total = total + h_vector[i];
  }
  for (unsigned int i = 0; i < v_vector.size(); i++) {
    total = total + v_vector[i];
  }
  length = total;
}
void Graph::set_boundary() {
  unsigned int min_x = 999;
  unsigned int min_y = 999;
  unsigned int max_x = 0;
  unsigned int max_y = 0;
  boundary_left.clear();
  boundary_right.clear();
  boundary_top.clear();
  boundary_bot.clear();
  unsigned int Graph_size = vertices.size();
  for (unsigned int i = 0; i < Graph_size; i++) {
    if (vertices[i].x < min_x) min_x = vertices[i].x;
    if (vertices[i].y < min_y) min_y = vertices[i].y;
    if (vertices[i].x > max_x) max_x = vertices[i].x;
    if (vertices[i].y > max_y) max_y = vertices[i].y;
  }
  for (unsigned int i = 0; i < Graph_size; i++) {
    if (vertices[i].x == min_x) boundary_left.push_back(vertices[i]);
    if (vertices[i].y == min_y) boundary_bot.push_back(vertices[i]);
    if (vertices[i].x == max_x) boundary_right.push_back(vertices[i]);
    if (vertices[i].y == max_y) boundary_top.push_back(vertices[i]);
  }
}
OptRST::OptRST() {
  min_length = 0;
  TreeList.clear();
  Point point;
  point.x = 1;
  point.y = 1;
  plane.push_back(point);
  point.x = 4;
  point.y = 2;
  plane.push_back(point);
  point.x = 5;
  point.y = 3;
  plane.push_back(point);
  point.x = 2;
  point.y = 4;
  plane.push_back(point);
  point.x = 3;
  point.y = 5;
  plane.push_back(point);
  point.x = 6;
  point.y = 6;
  plane.push_back(point);
  Graph first;
  first.vertices = plane;
  TreeList.push_back(first);
}
Gen::Gen() {
  for (int i = 1; i <= DEGREE; i++) {
    permutation_sequence.push_back(i);
  }
}
bool Gen::permutation_generate() {
  Utility util;
  char Permutation_list[] = "permutation_list.txt";
  ofstream Print_permutation(Permutation_list, ios::out | ios::trunc);
  Point point;
  int iter = -1;
  int test = 0;
  do {
    test++;
    iter++;
    for (vector<int>::iterator iter = permutation_sequence.begin(); iter != permutation_sequence.end(); iter++) {
      Print_permutation << *iter;
    }
    Print_permutation << endl;
// --------------------------
    OptRST* rst = new OptRST;
    rst->plane.clear();
    for (int i = 0; i < permutation_sequence.size(); i++) {
      point.y = i + 1;
      point.x = permutation_sequence[i];
      rst->plane.push_back(point);
    }
    rst->TreeList.clear();
    Graph first;
    first.vertices = rst->plane;
    rst->TreeList.push_back(first);
    //util.print_vertices(rst->plane);
    //cout << " -> ";
    rst->const_optRST();
    //util.print_TreeList(rst->plane, rst->TreeList);
    delete rst;
// --------------------------
    if (test == STOP) return true;
  } while (next_permutation(permutation_sequence.begin(), permutation_sequence.end()));
  Print_permutation.close();
  return true;
}

vector<Graph> OptRST::filter(const vector<Graph>& graphs) {
  vector<Graph> new_graphs;
  vector<Graph> reverse;
  Utility util;
  for(int i=0; i<graphs.size(); i++) {

    if(graphs[i].grown==true) {

      if(!(util.find_vector(graphs[i].h_vector, graphs[i].v_vector, new_graphs))) {
         new_graphs.push_back(graphs[i]);
      }

    }
  }
  reverse = new_graphs;
  new_graphs.clear();
  for(int i=reverse.size()-1; i>=0; i--) {
    if(reverse[i].grown==true) {

      if(!(util.find_vector(reverse[i].h_vector, reverse[i].v_vector, new_graphs))) {
         new_graphs.push_back(reverse[i]);
      }

    }
  }
  return new_graphs;
}

bool OptRST::const_optRST() {
  Graph current_graph;
  Utility util;
  vector<Graph> graphs = TreeList;
  int iter = 0;
  for (int i = 0; i < graphs.size(); i++) {
    iter++;
    current_graph = graphs[i];
    if (current_graph.grown == true || current_graph.valid == false) continue;
    current_graph.update();
    while (current_graph.boundary_left.size() == 1 ||
           current_graph.boundary_right.size() == 1 ||
           current_graph.boundary_bot.size() == 1 ||
           current_graph.boundary_top.size() == 1) {
      if (current_graph.size == 1) {
        current_graph.grown = true;
        graphs[i] = current_graph;
        break;
      }
      current_graph = extreme(current_graph);
    }
    if (current_graph.boundary_left.size() == 2 ||
        current_graph.boundary_right.size() == 2 ||
        current_graph.boundary_bot.size() == 2 ||
        current_graph.boundary_top.size() == 2) {
      //if(iter==4) break;
      current_graph.valid = false;
      current_graph.update();
      graphs[i] = current_graph;
      //cout << endl << "forking G..." << endl;
      if (current_graph.boundary_left.size() == 2) graphs = fork_graph_left(current_graph, graphs);
      if (current_graph.boundary_left.size() == 2) graphs = fork_graph_right(current_graph, graphs);
      if (current_graph.boundary_left.size() == 2) graphs = fork_graph_bot(current_graph, graphs);
      if (current_graph.boundary_top.size() == 2) graphs = fork_graph_top(current_graph, graphs);
    }
  }
  TreeList = filter(graphs);
  //util.print_TreeList(plane, TreeList);
  util.print_stat(plane, TreeList);
  return true;
}
vector<Graph> OptRST::fork_graph_left(const Graph& graph, const vector<Graph>& TreeList) {
  Utility util;
  Graph new_graph_1 = graph;
  Graph new_graph_2 = graph;
  Graph new_graph_3 = graph;
  vector<Graph> new_TreeList = TreeList;
  new_graph_1.valid = true;
  new_graph_2.valid = true;
  new_graph_3.valid = true;
  if(transform_left(&new_graph_1)) new_TreeList.push_back(new_graph_1);
  if(transform_left_top(&new_graph_2))   new_TreeList.push_back(new_graph_2);
  return new_TreeList;
}
bool OptRST::transform_left(Graph* graph) {
  Utility util;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(-1);
  }
  Point old_point_1 = graph->boundary_left[0];
  Point old_point_2 = graph->boundary_left[1];
  Point new_point_1;
  new_point_1.x = old_point_1.x + 1;
  new_point_1.y = old_point_1.y;
  Point new_point_2;
  new_point_2.x = old_point_2.x + 1;
  new_point_2.y = old_point_2.y;
  H_Segment hs;
  hs.shape = LEFT;
  hs.left = old_point_1;
  hs.right = new_point_1;
  graph->h_segments.push_back(hs);
  graph->h_vector[hs.left.x]++;
  hs.left = old_point_2;
  hs.right = new_point_2;
  graph->h_segments.push_back(hs);
  graph->h_vector[hs.left.x]++;
  if (!single_exist(new_point_1, graph)) {
    replace_single(new_point_1, old_point_1, graph);
  } else
    delete_single(old_point_1, graph);
  if (!single_exist(new_point_2, graph)) {
    replace_single(new_point_2, old_point_2, graph);
  } else
    delete_single(old_point_2, graph);
  (*graph).update();
  return true;
}
bool OptRST::transform_left_top(Graph* graph) {
  Utility util;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(-1);
  }
  Point old_top;
  Point old_bot;
  if(graph->boundary_left[0].y < graph->boundary_left[1].y) {
     old_top = graph->boundary_left[1];
     old_bot = graph->boundary_left[0];
  } else {
     old_top = graph->boundary_left[0];
     old_bot = graph->boundary_left[1];     
  }
  if(old_bot.y >= old_top.y) {
    cout <<endl <<"old_bot.y >= old_top.y"<<endl;
    exit(-1);
  }

  if(old_top.y != old_bot.y + 1) return false;
  Point new_point;
  new_point.x = old_top.x + 1;
  new_point.y = old_top.y;

  H_Segment hs;
  hs.shape = LEFT;
  hs.left = old_top;
  hs.right = new_point;
  graph->h_segments.push_back(hs);
  graph->h_vector[hs.left.x]++;  

  if (!single_exist(new_point, graph)) {
    replace_single(new_point, old_top, graph);
  } else
    delete_single(old_top, graph);

  V_Segment vs;
  vs.shape = BOT;
  vs.bot = old_bot;
  vs.top = old_top;
  graph->v_segments.push_back(vs);
  graph->v_vector[vs.bot.y]++;
 
  delete_single(old_bot, graph);
  (*graph).update();
  return true;
}
vector<Graph> OptRST::fork_graph_right(const Graph& graph, const vector<Graph>& TreeList) {
  Utility util;
  Graph new_graph_1 = graph;
  Graph new_graph_2 = graph;
  Graph new_graph_3 = graph;
  new_graph_1.valid = true;
  new_graph_2.valid = true;
  new_graph_3.valid = true;
  transform_right(&new_graph_1);
  vector<Graph> new_TreeList = TreeList;
  new_TreeList.push_back(new_graph_1);
  return new_TreeList;
}
bool OptRST::transform_right(Graph* graph) {
  Utility util;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(-1);
  }
  Point old_point_1 = graph->boundary_right[0];
  Point old_point_2 = graph->boundary_right[1];
  Point new_point_1;
  new_point_1.x = old_point_1.x - 1;
  new_point_1.y = old_point_1.y;
  Point new_point_2;
  new_point_2.x = old_point_2.x - 1;
  new_point_2.y = old_point_2.y;
  H_Segment hs;
  hs.shape = RIGHT;
  hs.left = new_point_1;
  hs.right = old_point_1;
  graph->h_segments.push_back(hs);
  graph->h_vector[hs.left.x]++;
  hs.left = new_point_2;
  hs.right = old_point_2;
  graph->h_segments.push_back(hs);
  graph->h_vector[hs.left.x]++;
  if (!single_exist(new_point_1, graph)) {
    replace_single(new_point_1, old_point_1, graph);
  } else
    delete_single(old_point_1, graph);
  if (!single_exist(new_point_2, graph)) {
    replace_single(new_point_2, old_point_2, graph);
  } else
    delete_single(old_point_2, graph);
  (*graph).update();
}
vector<Graph> OptRST::fork_graph_bot(const Graph& graph, const vector<Graph>& TreeList) {
  Utility util;
  Graph new_graph_1 = graph;
  Graph new_graph_2 = graph;
  Graph new_graph_3 = graph;
  vector<Graph> new_TreeList = TreeList;
  new_graph_1.valid = true;
  new_graph_2.valid = true;
  new_graph_3.valid = true;
  if(transform_bot(&new_graph_1)) new_TreeList.push_back(new_graph_1);
  if(transform_bot_left(&new_graph_2))   new_TreeList.push_back(new_graph_2);
  return new_TreeList;
}
bool OptRST::transform_bot(Graph* graph) {
  Utility util;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(-1);
  }
  Point old_point_1 = graph->boundary_bot[0];
  Point old_point_2 = graph->boundary_bot[1];
  Point new_point_1;
  new_point_1.x = old_point_1.x;
  new_point_1.y = old_point_1.y + 1;
  Point new_point_2;
  new_point_2.x = old_point_2.x;
  new_point_2.y = old_point_2.y + 1;
  V_Segment vs;
  vs.shape = BOT;
  vs.bot = old_point_1;
  vs.top = new_point_1;
  graph->v_segments.push_back(vs);
  graph->v_vector[vs.bot.y]++;
  vs.bot = old_point_2;
  vs.top = new_point_2;
  graph->v_segments.push_back(vs);
  graph->v_vector[vs.bot.y]++;
  if (!single_exist(new_point_1, graph)) {
    replace_single(new_point_1, old_point_1, graph);
  } else
    delete_single(old_point_1, graph);
  if (!single_exist(new_point_2, graph)) {
    replace_single(new_point_2, old_point_2, graph);
  } else
    delete_single(old_point_2, graph);
  (*graph).update();
  return true;
}

bool OptRST::transform_bot_left(Graph* graph) {
  Utility util;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(-1);
  }
  Point old_left;
  Point old_right;
  if(graph->boundary_bot[0].x < graph->boundary_bot[1].x) {
     old_left = graph->boundary_bot[0];
     old_right = graph->boundary_bot[1];
  } else {
     old_left = graph->boundary_bot[1];
     old_right = graph->boundary_bot[0];     
  }
  if(old_left.x >= old_right.x) {
    cout <<endl <<"old_left.x >= old_right.x"<<endl;
    exit(-1);
  }

  if(old_right.x != old_left.x + 1) return false;

  //cout << endl <<"*****************" <<endl;

  Point new_point;
  new_point.x = old_left.x; 
  new_point.y = old_left.y + 1;

  V_Segment vs;
  vs.shape = BOT;
  vs.bot = old_left;
  vs.top = new_point;
  graph->v_segments.push_back(vs);
  graph->v_vector[vs.bot.y]++;

  if (!single_exist(new_point, graph)) {
    replace_single(new_point, old_left, graph);
  } else
    delete_single(old_left, graph);

  H_Segment hs;
  hs.shape = LEFT;
  hs.left = old_left;
  hs.right = old_right;
  graph->h_segments.push_back(hs);
  graph->h_vector[hs.left.x]++; 
 
  delete_single(old_right, graph);
  (*graph).update();
  return true;
}

vector<Graph> OptRST::fork_graph_top(const Graph& graph, const vector<Graph>& TreeList) {
  Utility util;
  Graph new_graph_1 = graph;
  Graph new_graph_2 = graph;
  Graph new_graph_3 = graph;
  new_graph_1.valid = true;
  new_graph_2.valid = true;
  new_graph_3.valid = true;
  transform_top(&new_graph_1);
  vector<Graph> new_TreeList = TreeList;
  new_TreeList.push_back(new_graph_1);
  return new_TreeList;
}
bool OptRST::transform_top(Graph* graph) {
  Utility util;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(-1);
  }
  Point old_point_1 = graph->boundary_top[0];
  Point old_point_2 = graph->boundary_top[1];
  Point new_point_1;
  new_point_1.x = old_point_1.x;
  new_point_1.y = old_point_1.y - 1;
  Point new_point_2;
  new_point_2.x = old_point_2.x;
  new_point_2.y = old_point_2.y - 1;
  V_Segment vs;
  vs.shape = TOP;
  vs.bot = new_point_1;
  vs.top = old_point_1;
  graph->v_segments.push_back(vs);
  graph->v_vector[vs.bot.y]++;
  vs.bot = new_point_2;
  vs.top = old_point_2;
  graph->v_segments.push_back(vs);
  graph->v_vector[vs.bot.y]++;
  if (!single_exist(new_point_1, graph)) {
    replace_single(new_point_1, old_point_1, graph);
  } else
    delete_single(old_point_1, graph);
  if (!single_exist(new_point_2, graph)) {
    replace_single(new_point_2, old_point_2, graph);
  } else
    delete_single(old_point_2, graph);
  (*graph).update();
}
Graph OptRST::extreme(Graph graph) {
  Utility util;
  Graph new_graph;
  Point new_point;
  Point old_point;
  while (graph.boundary_left.size() == 1) {
    if (graph.size == 1) break;
    //cout << endl <<"left_compacting..."<< endl;
    old_point = graph.boundary_left[0];
    new_point.x = old_point.x + 1;
    new_point.y = old_point.y;
    H_Segment h_segment;
    h_segment.shape = LEFT;
    h_segment.left = old_point;
    h_segment.right = new_point;
    graph.h_segments.push_back(h_segment);
    graph.h_vector[h_segment.left.x]++;
    if (!single_exist(new_point, &graph)) {
      replace_single(new_point, old_point, &graph);
    } else
      delete_single(old_point, &graph);
    //util.print_vertices(graph.vertices);
    graph.update();
  }
  while (graph.boundary_right.size() == 1) {
    if (graph.size == 1) break;
    //cout << endl <<"right_compacting..."<< endl;
    old_point = graph.boundary_right[0];
    new_point.x = old_point.x - 1;
    new_point.y = old_point.y;
    H_Segment h_segment;
    h_segment.shape = RIGHT;
    h_segment.left = new_point;
    h_segment.right = old_point;
    graph.h_segments.push_back(h_segment);
    graph.h_vector[h_segment.left.x]++;
    if (!single_exist(new_point, &graph)) {
      replace_single(new_point, old_point, &graph);
    } else
      delete_single(old_point, &graph);
    //util.print_vertices(graph.vertices);
    graph.update();
  }
  while (graph.boundary_bot.size() == 1) {
    if (graph.size == 1) break;
    //cout << endl <<"bot_compacting..."<< endl;
    old_point = graph.boundary_bot[0];
    new_point.x = old_point.x;
    new_point.y = old_point.y + 1;
    V_Segment v_segment;
    v_segment.shape = BOT;
    v_segment.bot = old_point;
    v_segment.top = new_point;
    graph.v_segments.push_back(v_segment);
    graph.v_vector[v_segment.bot.y]++;
    if (!single_exist(new_point, &graph)) {
      replace_single(new_point, old_point, &graph);
    } else
      delete_single(old_point, &graph);
    //util.print_vertices(graph.vertices);
    graph.update();
  }
  while (graph.boundary_top.size() == 1) {
    if (graph.size == 1) break;
    //cout << endl <<"top_compacting..."<< endl;
    old_point = graph.boundary_top[0];
    new_point.x = old_point.x;
    new_point.y = old_point.y - 1;
    V_Segment v_segment;
    v_segment.shape = TOP;
    v_segment.bot = new_point;
    v_segment.top = old_point;
    graph.v_segments.push_back(v_segment);
    graph.v_vector[v_segment.bot.y]++;
    if (!single_exist(new_point, &graph)) {
      replace_single(new_point, old_point, &graph);
    } else
      delete_single(old_point, &graph);
    //util.print_vertices(graph.vertices);
    graph.update();
  }
  new_graph = graph;
  //cout <<"==="<<new_graph.vertices.size()<<endl;
  return new_graph;
}
bool OptRST::single_exist(Point point, Graph* graph) {
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(0);
  }
  for (unsigned int i = 0; i < graph->vertices.size(); i++) {
    if (point.x == graph->vertices[i].x && point.y == graph->vertices[i].y) return true;
  }
  return false;
}
bool OptRST::replace_single(Point new_point, Point old_point, Graph* graph) {
  //cout << endl <<"Replacing single point..."<<endl;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(0);
  }
  for (unsigned int i = 0; i < graph->vertices.size(); i++) {
    if (graph->vertices[i].x == old_point.x && graph->vertices[i].y ==  old_point.y) {
      graph->vertices[i].x = new_point.x;
      graph->vertices[i].y = new_point.y;
    }
  }
}
bool OptRST::delete_single(Point old_point, Graph* graph) {
  Utility util;
  //cout << endl <<"Deleting single point..."<<endl;
  if (graph == NULL) {
    cout << endl << "!!! graph==NULL !!!" << endl;
    exit(0);
  }
  vector<Point> new_vertices;
  for (unsigned int i = 0; i < graph->vertices.size(); i++) {
    if (graph->vertices[i].x == old_point.x && graph->vertices[i].y ==  old_point.y) {} else
      new_vertices.push_back(graph->vertices[i]);
  }
  (*graph).vertices = new_vertices;
}
// -------------------------------------------
void Utility::print_point(Point point) {
  cout << "(" << point.x << "," << point.y << ")";
}
void Utility::print_vertices(vector<Point> vertices) {
  unsigned int size = vertices.size();
  for (unsigned int i = 0; i < size; i++) {
    print_point(vertices[i]);
    cout << " ";
  }
}
void Utility::print_H_segment(H_Segment hs) {
  cout << "[";
  print_point(hs.left);
  cout << "->";
  print_point(hs.right);
  cout << "]";
}
void Utility::print_V_segment(V_Segment vs) {
  cout << "[";
  print_point(vs.bot);
  cout << "->";
  print_point(vs.top);
  cout << "]";
}
void Utility::print_boundary(const Graph& graph) {
  cout << endl;
  cout << graph.boundary_left.size() << "=";
  print_vertices(graph.boundary_left);
  cout << endl;
  cout << graph.boundary_right.size() << "=";
  print_vertices(graph.boundary_right);
  cout << endl;
  cout << graph.boundary_bot.size() << "=";
  print_vertices(graph.boundary_bot);
  cout << endl;
  cout << graph.boundary_top.size() << "=";
  print_vertices(graph.boundary_top);
  cout << endl;
}
void Utility::print_graph(const Graph& graph) {
  for (unsigned int i = 0; i < graph.h_segments.size(); i++) {
    print_H_segment(graph.h_segments[i]);
    cout << "; ";
  }
  for (unsigned int i = 0; i < graph.v_segments.size(); i++) {
    print_V_segment(graph.v_segments[i]);
    cout << "; ";
  }
  cout << endl << "[";
  for (unsigned int i = 1; i < graph.h_vector.size(); i++) {
    cout << graph.h_vector[i] << " ";
  }
  cout << "]";
  cout << " + [";
  for (unsigned int i = 1; i < graph.v_vector.size(); i++) {
    cout << graph.v_vector[i] << " ";
  }
  cout << "]";
  cout << " = " << graph.length << endl;
}
void Utility::print_TreeList(const vector<Point>& plane, const vector<Graph>& TreeList) {

  cout <<endl<<"---------------------------------"<<endl;
  print_vertices(plane);
  cout << endl;
  unsigned int count = 0;
  for (int i = 0; i < TreeList.size(); i++) {
   if(TreeList[i].grown==true) {
      cout <<endl<<"Index_"<<++count<<": "<<endl;
      print_graph(TreeList[i]);
      cout <<endl;
      print_steiner_tree(plane, TreeList[i]);
      cout <<endl;
    }
  }
}

void Utility::print_steiner_tree(const vector<Point>& plane, const Graph& graph) {
  cout << "--- steiner_tree_diagram ---" << endl;
  const int Max_Degree = 2 * 9;
  char pixels[Max_Degree][Max_Degree];
  const char DOT = '.';
  const char PIPE = '|';
  const char DASH = '_';
  const char VERTEX = '$';
  int index_row = Max_Degree / 2;
  int index_col = 1;
  const int NUM_CHAR = 48;
  for (int i = 0; i < Max_Degree; i++) {
    for (int j = 0; j < Max_Degree; j++) {
      pixels[i][j] = ' ';
    }
  }
  for (int i = 0; i < Max_Degree; i++) {
    pixels[i][0] = index_row + NUM_CHAR;
    for (int j = 1; j < Max_Degree; j++) {
      pixels[i][j] = DOT;
      j++;
    }
    i++;
    index_row--;
  }
  for (int j = 1; j < Max_Degree; j++) {
    pixels[Max_Degree - 1][j] = index_col + NUM_CHAR;
    j++;
    index_col++;
  }
  // add vertices
  index_row = 0;
  index_col = 0;
  for (int i = 0; i < plane.size(); i++) {
    index_row = (Max_Degree - 1) - 2 * plane[i].y + 1;
    index_col = 2 * (plane[i].x) - 1;
    if (index_row < 0 || index_row >= Max_Degree) {
      cout << "!-index_row!" << endl;
      exit(0);
    }
    if (index_col < 0 || index_col >= Max_Degree) {
      cout << "!-index_col!" << endl;
      exit(0);
    }
    pixels[index_row][index_col] = VERTEX;
  }
  
  for (int i = 0; i < graph.h_segments.size(); i++) {
    index_row = 0;
    index_col = 0;
    switch (graph.h_segments[i].shape) {
      case LEFT:
        index_row = (Max_Degree - 1) - 2 * graph.h_segments[i].left.y + 1;
        index_col = 2 * (graph.h_segments[i].left.x);
        pixels[index_row][index_col] = DASH;
        break;
      case RIGHT:
        index_row = (Max_Degree - 1) - 2 * graph.h_segments[i].left.y + 1;
        index_col = 2 * (graph.h_segments[i].left.x);
        pixels[index_row][index_col] = DASH;
        break;
    }
  }

  for (int i = 0; i < graph.v_segments.size(); i++) {
    index_row = 0;
    index_col = 0;
    switch (graph.v_segments[i].shape) {
      case BOT:
        index_row = (Max_Degree - 1) - 2 * graph.v_segments[i].top.y + 2;
        index_col = 2 * (graph.v_segments[i].bot.x) - 1;
        pixels[index_row][index_col] = PIPE;
        break;
      case TOP:
        index_row = (Max_Degree - 1) - 2 * graph.v_segments[i].top.y + 2;
        index_col = 2 * (graph.v_segments[i].bot.x) - 1;
        pixels[index_row][index_col] = PIPE;
        break;
    }
  }

  cout << endl;
  for (int i = 0; i < Max_Degree; i++) {
    for (int j = 0; j < Max_Degree; j++) {
      cout << pixels[i][j];
    }
    cout << endl;
  }
}


void Utility::print_stat(const vector<Point>& plane, const vector<Graph>& TreeList) {

  cout<<endl;
  char ch = EXCL;
  unsigned int count = 0;
  for(int i=0; i<plane.size(); i++) {
    cout <<plane[i].x;
  }

  for(int i=0; i<TreeList.size(); i++) {

     if(TreeList[i].grown==true) count++;
  }
  ch = ch + count;
  cout <<":" <<ch;

  for(int i=0; i<TreeList.size(); i++) {
    if(TreeList[i].grown==true) {
       cout << endl;
       for (unsigned int j = 1; j < TreeList[i].h_vector.size(); j++) {
          cout << TreeList[i].h_vector[j] ;
       }
       for (unsigned int j = 1; j < TreeList[i].v_vector.size(); j++) {
          cout << TreeList[i].v_vector[j];
       }
    }
  }
}

bool Utility::find_vector(const vector<unsigned int>& h, const vector<unsigned int>& v, const vector<Graph>& graphs) {


   for(int i=0; i<graphs.size(); i++) {
     
     if(ge_vector(h, graphs[i].h_vector) && ge_vector(v, graphs[i].v_vector)) return true;

   }
   return false;
}

bool Utility::ge_vector(const vector<unsigned int>& left, const vector<unsigned int>& right) {

    if(left.size()!=right.size()) {
        cout << endl <<"left.size!=right.size"<<endl;
        exit(-1);
    }

    for(int i=0; i<left.size(); i++) {

      if(left[i] < right[i]) return false;

    }

    return true;

}
