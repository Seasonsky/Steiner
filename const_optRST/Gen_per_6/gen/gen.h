#include<iostream>
#include<vector>
using namespace std;
class Point {
 public:
  Point();
  unsigned int x;
  unsigned int y;
};
class H_Segment {
 public:
  H_Segment();
  Point left;
  Point right;
  unsigned int shape;
};
class V_Segment {
 public:
  V_Segment();
  Point bot;
  Point top;
  unsigned int shape;
};
class Graph {
 public:
  Graph();
  unsigned int size;
  bool grown;
  bool valid;
  vector<Point> vertices;
  vector<H_Segment> h_segments;
  vector<unsigned int> h_vector;
  vector<V_Segment> v_segments;
  vector<unsigned int> v_vector;
  void update();
  void set_boundary();
  void set_size();
  void set_length();
  vector<Point> boundary_left;
  vector<Point> boundary_right;
  vector<Point> boundary_bot;
  vector<Point> boundary_top;
  unsigned int length;
};
class OptRST {
 public:
  OptRST();
  bool const_optRST();
  vector<Graph> TreeList;
  vector<Point> plane;
  Graph extreme(Graph graph);
  bool replace_single(Point new_point, Point old_point, Graph* graph);
  bool delete_single(Point old_point, Graph* graph);
  bool single_exist(Point point, Graph* graph);

  vector<Graph> fork_graph_left(const Graph& graph, const vector<Graph>& TreeList);
  bool transform_left(Graph* graph);
  bool transform_left_top(Graph* graph);

  vector<Graph> fork_graph_right(const Graph& graph, const vector<Graph>& TreeList);
  bool transform_right(Graph* graph);

  vector<Graph> fork_graph_bot(const Graph& graph, const vector<Graph>& TreeList);
  bool transform_bot(Graph* graph);
  bool transform_bot_left(Graph* graph);
  bool transform_bot_right(Graph* graph);

  vector<Graph> fork_graph_top(const Graph& graph, const vector<Graph>& TreeList);
  bool transform_top(Graph* graph);

  vector<Graph> filter(const vector<Graph>& graphs);
  unsigned int min_length;
};
class Gen {
 public:
  Gen();
  bool permutation_generate();
  vector<int> permutation_sequence;
};
class Utility {
 public:
  void print_point(Point point);
  void print_H_segment(H_Segment hs);
  void print_V_segment(V_Segment vs);
  void print_vertices(vector<Point> vertices);
  void print_boundary(const Graph& graph);
  void print_graph(const Graph& graph);
  void print_TreeList(const vector<Point>& plane, const vector<Graph>& TreeList);
  void print_steiner_tree(const vector<Point>& plane, const Graph& graph);
  void print_stat(const vector<Point>& plane, const vector<Graph>& TreeList);
  bool find_vector(const vector<unsigned int>& h, const vector<unsigned int>& v, const vector<Graph>& graphs);
  bool ge_vector(const vector<unsigned int>& left, const vector<unsigned int>& right);
};
