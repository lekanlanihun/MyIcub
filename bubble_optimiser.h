#ifndef BUBBLE_OPTIMISER
#define BUBBLE_OPTIMISER
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include  "../Quad_Tree/QuadTree.h"
//#include <iomanip>
#define number_of_vertex 1145
#define number_of_edges 1145
#define vertex__file_cols 6
#define edge__file_rows 1148
#define edge__file_cols 6



using namespace std;

class Bubble_Optimiser{

public:
Bubble_Optimiser ();
void read_vertex_file();
void read_edge_file();
void calc_minimum_distance();
void calc_min_distance();
void calc_mindist();
void calc_mindist_vec();
void print_mininum_distance();
void mininum_distance(double, double, double, double, double, double, double, double,double);
void simple_spatial_partition(double, double, double, double);
void overlapping_spatial_partition(double, double, double, double);
void simple_edge_partition(double, double, double, double);
void assign_boundary_box_data();
void read_vertex_to_4quadrants();
void count_boundary_box_data();
double *sort(double*,int);

typedef struct BoundingBox{
  double x0; double y0;
    double x1; double y1;

}BoundingBox;

typedef struct vertex_data{
vector<int>vertex_id;
 vector<double>vertex_x;
    vector<double>vertex_y;
vector<double>vertex_nx;
vector<double>vertex_ny;
vector<int>vert_bub_id;

}vertex_data;

typedef struct edge_data{
 vector<double>evertex1_x;
    vector<double>evertex1_y;
vector<double>ee_x;
vector<double>ee_y;
vector<int>edge_bub_id;

}edge_data;

BoundingBox boundingBox;

vertex_data box1_vertices;
vertex_data box2_vertices;
vertex_data box3_vertices;
vertex_data box4_vertices;


edge_data box1_edges;
edge_data box2_edges;
edge_data box3_edges;
edge_data box4_edges;

BoundingBox MakeBoundingBox(double x0, double y0, double x1, double y1){
    boundingBox.x0=x0;
    boundingBox.y0=y0;
    boundingBox.x1=x1;
    boundingBox.y1=y1;

return boundingBox;

}

BoundingBox TopLeftQuadrant;BoundingBox TopRightQuadrant;BoundingBox BottomLeftQuadrant;BoundingBox BottomRightQuadrant;
BoundingBox TopMidQuadrant;BoundingBox  LeftMidQuadrant;BoundingBox  MidMidQuadrant;BoundingBox  RightMidQuadrant; BoundingBox BottomMidQuadrant;
BoundingBox box1;BoundingBox  box2;BoundingBox box3;BoundingBox  box4; BoundingBox box5;
BoundingBox box6;BoundingBox  box7;BoundingBox box8;BoundingBox  box9; BoundingBox box10;
BoundingBox box11;BoundingBox  box12;BoundingBox box13;BoundingBox  box14; BoundingBox box15;
BoundingBox box16;BoundingBox  box17;BoundingBox box18;BoundingBox  box19; BoundingBox box20;
BoundingBox box21;BoundingBox  box22;BoundingBox box23;BoundingBox  box24; BoundingBox box25;
BoundingBox box26;BoundingBox  box27;BoundingBox box28;BoundingBox  box29; BoundingBox box30;
BoundingBox box31;BoundingBox  box32;BoundingBox box33;BoundingBox  box34; BoundingBox box35;
BoundingBox box36;BoundingBox  box37;BoundingBox box38;BoundingBox  box39; BoundingBox box40;
BoundingBox box41;BoundingBox  box42;BoundingBox box43;BoundingBox  box44; BoundingBox box45;
BoundingBox box46;BoundingBox  box47;BoundingBox box48;BoundingBox  box49; 

//bounding boxes for in which each vertex in a box search for edges for mindist computation
BoundingBox edgebox1;BoundingBox  edgebox2;BoundingBox edgebox3;BoundingBox edgebox4; BoundingBox edgebox5;
BoundingBox edgebox6;BoundingBox edgebox7;BoundingBox edgebox8;BoundingBox edgebox9;

BoundingBox edge_box1;BoundingBox  edge_box2;BoundingBox edge_box3;BoundingBox edge_box4; BoundingBox edge_box5;
BoundingBox edge_box6;BoundingBox edge_box7;BoundingBox edge_box8; BoundingBox edge_box9;

bool BoundingBoxContainsVertices(BoundingBox boundary, double,double);
bool BoundingBoxContainsEdges(BoundingBox boundary, double,double/*, double,double*/);
bool BoundingBoxContainsData(BoundingBox boundary, double, double, double,double/*,double,double*/);


virtual ~ Bubble_Optimiser();

private:
vector<int>Vertex_id;vector<double>Vertex_x;vector<double>Vertex_y;vector<double>Vertex_nx;vector<double>Vertex_ny;vector<int>Vertex_bub_id;
vector<int>Edge_id; vector<int>Evertex1_id;vector<int>Evertex2_id; vector<double>Evertex1_x;vector<double>Evertex1_y;vector<double>Evertex2_x;vector<double>Evertex2_y;vector<double>Eex;vector<double>Eey;vector<int>Edge_bub_id;
vector<double>min_dists;

int *vertex_id; double *vertex_x; double *vertex_y; int number; int vertex_cols; double nx; double ny; double mindists; int vert_id;
double *vertex_nx; double *vertex_ny; int *bubble_id; int *min_vertex_id;
int *edge_id; int*edge_vertex1_id;  int*edge_vertex2_id; double*edge_vertex1_x; double*edge_vertex1_y; double *ee_x; double *ee_y; int *edge_bubble_id;
 double*edge_vertex2_x;
    double*edge_vertex2_y;
double *min_dist; double *b1_min_dist;double *b2_min_dist;double *b3_min_dist; double *b4_min_dist;double *b5_min_dist;double *b6_min_dist;double *b7_min_dist; double *b8_min_dist;  double *b9_min_dist;  double *out_min_dist;  double**vertex_info; double**edge_info; int i; int edge_number;int  v_counter; int e_counter;
 int *b1_vertex_id; int *b2_vertex_id; int *b3_vertex_id; int *b4_vertex_id;  int *b5_vertex_id; int *b6_vertex_id; int*b7_vertex_id; int *b8_vertex_id; int *b9_vertex_id;int*out_vertex_id;
    double *b1_vertex_x;double* b2_vertex_x;  double *b3_vertex_x;double* b4_vertex_x; double *b5_vertex_x;double* b6_vertex_x;  double *b7_vertex_x;double* b8_vertex_x; double* b9_vertex_x;  double* out_vertex_x; 
    double *b1_vertex_y;double* b2_vertex_y;  double *b3_vertex_y;double* b4_vertex_y; double *b5_vertex_y;double* b6_vertex_y;  double *b7_vertex_y;double* b8_vertex_y; double* b9_vertex_y; double* out_vertex_y;  
    double *b1_nx;double* b2_nx;  double *b3_nx;double* b4_nx;  double *b5_nx;double* b6_nx;  double *b7_nx;double* b8_nx; double* b9_nx;double* out_nx; 
    double *b1_ny;double* b2_ny;  double *b3_ny;double* b4_ny;double *b5_ny;double* b6_ny;  double *b7_ny;double* b8_ny; double* b9_ny;  double* out_ny; 
    int*b1_vert_b_id;   int *b2_vert_b_id;int *b3_vert_b_id;int *b4_vert_b_id;int *b5_vert_b_id;   int *b6_vert_b_id;int *b7_vert_b_id;int *b8_vert_b_id;int *b9_vert_b_id; int *out_vert_b_id; 
    double *b1_evertex1_x;double* b2_evertex1_x;  double *b3_evertex1_x;double* b4_evertex1_x;  double *b5_evertex1_x;double* b6_evertex1_x;  double *b7_evertex1_x;double* b8_evertex1_x;double* b9_evertex1_x; double* out_evertex1_x; 
    double *b1_evertex1_y;double* b2_evertex1_y;  double *b3_evertex1_y;double* b4_evertex1_y;double *b5_evertex1_y;double* b6_evertex1_y;  double *b7_evertex1_y;double* b8_evertex1_y;double* b9_evertex1_y; double* out_evertex1_y; 
    double *b1_eex;double* b2_eex;  double *b3_eex;double* b4_eex; double *b5_eex;double* b6_eex;  double *b7_eex;double* b8_eex; double* b9_eex; double* out_eex; 
    double *b1_eey;double* b2_eey;  double *b3_eey;double* b4_eey;  double *b5_eey;double* b6_eey;  double *b7_eey;double* b8_eey; double* b9_eey;  double* out_eey; 
    int *b1_edge_b_id;   int *b2_edge_b_id;int *b3_edge_b_id;int *b4_edge_b_id;int*b5_edge_b_id;   int *b6_edge_b_id;int *b7_edge_b_id;int *b8_edge_b_id;int *b9_edge_b_id; int *out_edge_b_id; 

int edge_cols, counter, b1_v_counter, b1_e_counter, b2_v_counter, b2_e_counter, b3_v_counter,  b3_e_counter, b4_v_counter, b4_e_counter;
int b5_v_counter, b5_e_counter, b6_v_counter, b6_e_counter, b7_v_counter,  b7_e_counter, b8_v_counter,  b8_e_counter, b9_v_counter,b9_e_counter, out_v_counter, out_e_counter;
double minimum; double mindist; double width, height, delta, search_width, search_height;

double quad1_center_x; double quad1_center_y;  double quad2_center_x;double quad2_center_y; double quad3_center_x; double quad3_center_y; double quad4_center_x;double quad4_center_y;


};

#endif
