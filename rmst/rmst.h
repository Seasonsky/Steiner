#include <vector>
#include <string>

const int Single = 1;
const int LEFT = 1;
const int RIGHT = 2;
const int TOP = 3;
const int BOTTOM = 4;

// x-axis, y-axis: all are integer
class Point {
 public:
  Point();
  int x;
  int y;
};

class Edge {
 public:
  Edge();
  Point start;
  Point end;
  int shape; 
};

class Chain {
 public:
  Chain();
  Chain(vector<Point> points);
  vector<Point> points;
  bool flag; // 0: horizontal; 1: vertical;
};

class Plane {
 public:
  Plane();
  vector<Point> terminals;
};

class Graph {
 public:
  Graph();
  void get_degree();
  void get_boundaries();
  void get_left();
  void get_right();
  void get_top();
  void get_bottom();
  vector<int> lefts;
  vector<int> rights;
  vector<int> tops;
  vector<int> bottoms;
  vector<Point> vertices;
  vector<Edge> edges;
  int degree;
};
class Node {
 public:
  Node();
  Graph graph;
  Node* next;
};
class RMST {
 public:
  RMST(const Plane& plane);
  void travel_trees();
  void process_one(Graph& graph);
  void process_one_left(Graph& graph);
  void process_one_right(Graph& graph);
  void process_one_top(Graph& graph);
  void process_one_bottom(Graph& graph);
  int is_one(Graph& graph); // 0-nothing; 1-left; 2-right; 3-top; 4-bottom;
  bool check_exist_point(const Point& point, const Graph& graph);
  void add_single_edge(Graph& graph, int direction);
  Node* tree_queue_head;
};
class Utilities {
 public:
  void output_tree_queue(const Plane& plane, const RMST& rmst);
  void output_graph_boundaries(const Graph& graph);
  void output_steiner_tree_diagram(const Plane& plane, const Graph& graph);
};
ostream& operator<<(ostream& out, const Point& point);
ostream& operator<<(ostream& out, const Edge& edge);
ostream& operator<<(ostream& out, const vector<Point>& points);
ostream& operator<<(ostream& out, const Graph& graph); 
ostream& operator<<(ostream& out, const vector<Edge> edges);
