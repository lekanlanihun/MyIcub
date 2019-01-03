#include "bubble_optimiser.h"

Bubble_Optimiser::Bubble_Optimiser(){

    double x0=-2.0; double y0=2.0; double x1=2.0; double y1=-2.0;
     width=4.0; height=4.0; delta= width/10.0;
     search_width= (width/4.0)+delta; search_height=(height/4.0)+delta;
     //search_width= 1.4; search_height=1.4;

quad1_center_x=-1.0; double quad1_center_y=1.0;
quad2_center_x=1.0; quad2_center_y=1.0;
quad3_center_x=-1.0; quad3_center_y=-1.0;
quad4_center_x=1.0;quad4_center_y=-1.0;
number=1144;  edge_number = 1148;
Vertex_id.assign(number, 0.0);
Vertex_x.assign(number, 0.0);
Vertex_y.assign(number, 0.0);
Vertex_nx.assign(number, 0.0);
Vertex_ny.assign(number, 0.0);
Vertex_bub_id.assign(number, 0.0);

Edge_id.assign(edge_number, 0);
Evertex1_id.assign(edge_number, 0);
Evertex2_id.assign(edge_number, 0);
Evertex1_x.assign(edge_number, 0.0);
Evertex1_y.assign(edge_number, 0.0);
Evertex2_x.assign(edge_number, 0.0);
Evertex2_y.assign(edge_number, 0.0);
Eex.assign(edge_number, 0.0);
Eey.assign(edge_number, 0.0);
Edge_bub_id.assign(edge_number, 0);

min_dists.assign(number,0.0);

vertex_x= new double[number]; vertex_y= new double[number];
vertex_id= new int[number];
vertex_nx= new double[number];vertex_ny= new double[number]; bubble_id= new int[number];
 edge_id = new int[edge_number];
edge_vertex1_id = new int[edge_number];
    edge_vertex2_id = new int[edge_number];
    edge_vertex1_x = new double[edge_number];
    edge_vertex1_y = new double[edge_number];
    edge_vertex2_x = new double[edge_number];
    edge_vertex2_y = new double[edge_number];
    ee_x = new double[edge_number];
    ee_y = new double[edge_number];
    edge_bubble_id = new int[edge_number];
min_dist= new double[number];

/*vertex_info=new double*[number];
for(int i=0;i<number;i++){
vertex_info[i]=new double[vertex_cols];
}
edge_info=new double*[number];
for(int i=0;i<number;i++){
edge_info[i]=new double[edge_cols];
}*/

/*for(int i=0;i<number;i++){
vertex_id=0;
vertex_x[i]= 0.0;
vertex_y[i]= 0.0;
vertex_nx[i]=0.0;
vertex_ny[i]=0.0;
bubble_id[i]=0;
edge_id[i]=0;
edge_vertex1_x[i]=0.0;
edge_vertex1_y[i]=0.0;
ee_x[i]=0.0;
ee_y[i]=0.0;
edge_bubble_id[i]=0;
}*/
//bubbles_data data;

b1_v_counter=10000;
b2_v_counter=10000;
b3_v_counter=10000;
b4_v_counter=10000;
b5_v_counter=10000;
b6_v_counter=10000;
b7_v_counter=10000;
b8_v_counter=10000;
b9_v_counter=10000;

b1_e_counter=10000;
b2_e_counter=10000;
b3_e_counter=10000;
b4_e_counter=10000;
b5_e_counter=10000;
b6_e_counter=10000;
b7_e_counter=10000;
b8_e_counter=10000;
b9_e_counter=10000;

/*double array1[number];
double array2[number];
for(int i=0;i<number;i++){
    array1[i]=vertex_x[i];
}
for(int i=0;i<number;i++){
    array2[i]=vertex_y[i];
}
double*array_x=sort(array1,number);
double x0=array_x[0]; double x1=array_x[number-1];
//cout<<"array x0="<<array1[0]<<"array x1="<<array1[number-1]<<endl;
double*array_y=sort(array2,number);
double y0=array_y[number-1]; double y1=array_y[0];*/
//cout<<"array y1="<<array2[0]<<"array y0="<<array2[number-1]<<endl;
simple_spatial_partition(x0,  y0, x1,  y1);
//overlapping_spatial_partition(x0,  y0, x1,  y1);
simple_edge_partition(x0,y0,x1,y1);
read_vertex_file();
read_edge_file();
//simple_spatial_partition(x0,  y0, x1,  y1);
//simple_edge_partition();
//count_boundary_box_data();



/*cout << "b1_e_counter="<< " " << b1_e_counter<< endl;
cout << "b2_e_counter="<< " " << b2_e_counter<< endl;
cout << "b3_e_counter="<< " " << b3_e_counter<< endl;
cout << "b4_e_counter="<< " " << b4_e_counter<< endl;
cout << "b5_e_counter="<< " " << b5_e_counter<< endl;
cout << "b6_e_counter="<< " " << b6_e_counter<< endl;
cout << "b7_e_counter="<< " " << b7_e_counter<< endl;
cout << "b8_e_counter="<< " " << b8_e_counter<< endl;
cout << "b9_e_counter="<< " " << b9_e_counter<< endl;*/

//cout<<"get here1"<<endl;
b1_vertex_id=new int[b1_v_counter];b1_vertex_x=new double[b1_v_counter];b1_vertex_y=new double[b1_v_counter]; b1_nx=new double[b1_v_counter];b1_ny=new double[b1_v_counter];b1_vert_b_id=new int[b1_v_counter];
b1_evertex1_x=new double[b1_e_counter];b1_evertex1_y=new double[b1_e_counter]; b1_eex=new double[b1_e_counter];b1_eey=new double[b1_e_counter];b1_edge_b_id=new int[b1_e_counter];
b2_vertex_id=new int[b2_v_counter];b2_vertex_x=new double[b2_v_counter];b2_vertex_y=new double[b2_v_counter]; b2_nx=new double[b2_v_counter];b2_ny=new double[b2_v_counter]; b2_vert_b_id=new int[b2_v_counter];
    b2_evertex1_x=new double[b2_e_counter];b2_evertex1_y=new double[b2_e_counter]; b2_eex=new double[b2_e_counter];b2_eey=new double[b2_e_counter];b2_edge_b_id=new int[b2_e_counter];
b3_vertex_id=new int[b3_v_counter]; b3_vertex_x=new double[b3_v_counter];b3_vertex_y=new double[b3_v_counter]; b3_nx=new double[b3_v_counter];b3_ny=new double[b3_v_counter];b3_vert_b_id=new int[b3_v_counter];
     b3_evertex1_x=new double[b3_e_counter];b3_evertex1_y=new double[b3_e_counter]; b3_eex=new double[b3_e_counter];b3_eey=new double[b3_e_counter];b3_edge_b_id=new int[b3_e_counter];
b4_vertex_id=new int[b4_v_counter]; b4_vertex_x=new double[b4_v_counter];b4_vertex_y=new double[b4_v_counter]; b4_nx=new double[b4_v_counter];b4_ny=new double[b4_v_counter];b4_vert_b_id=new int[b4_v_counter];
     b4_evertex1_x=new double[b4_e_counter];b4_evertex1_y=new double[b4_e_counter]; b4_eex=new double[b4_e_counter];b4_eey=new double[b4_e_counter];b4_edge_b_id=new int[b4_e_counter];

     b5_vertex_id=new int[b5_v_counter];b5_vertex_x=new double[b5_v_counter];b5_vertex_y=new double[b5_v_counter]; b5_nx=new double[b5_v_counter];b5_ny=new double[b5_v_counter];b5_vert_b_id=new int[b5_v_counter];
     b5_evertex1_x=new double[b5_e_counter];b5_evertex1_y=new double[b5_e_counter]; b5_eex=new double[b5_e_counter];b5_eey=new double[b5_e_counter];b5_edge_b_id=new int[b5_e_counter];
     b6_vertex_id=new int[b6_v_counter];b6_vertex_x=new double[b6_v_counter];b6_vertex_y=new double[b6_v_counter]; b6_nx=new double[b6_v_counter];b6_ny=new double[b6_v_counter]; b6_vert_b_id=new int[b6_v_counter];     
     b6_evertex1_x=new double[b6_e_counter];b6_evertex1_y=new double[b6_e_counter]; b6_eex=new double[b6_e_counter];b6_eey=new double[b6_e_counter];b6_edge_b_id=new int[b6_e_counter];
     b7_vertex_id=new int[b7_v_counter]; b7_vertex_x=new double[b7_v_counter];b7_vertex_y=new double[b7_v_counter]; b7_nx=new double[b7_v_counter];b7_ny=new double[b7_v_counter];b7_vert_b_id=new int[b7_v_counter];
     b7_evertex1_x=new double[b7_e_counter];b7_evertex1_y=new double[b7_e_counter]; b7_eex=new double[b7_e_counter];b7_eey=new double[b7_e_counter];b7_edge_b_id=new int[b7_e_counter];
     b8_vertex_id=new int[b8_v_counter]; b8_vertex_x=new double[b8_v_counter];b8_vertex_y=new double[b8_v_counter]; b8_nx=new double[b8_v_counter];b8_ny=new double[b8_v_counter];b8_vert_b_id=new int[b8_v_counter];
     b8_evertex1_x=new double[b8_e_counter];b8_evertex1_y=new double[b8_e_counter]; b8_eex=new double[b8_e_counter];b8_eey=new double[b8_e_counter];b8_edge_b_id=new int[b8_e_counter];
     b9_vertex_id=new int[b9_v_counter]; b9_vertex_x=new double[b9_v_counter];b9_vertex_y=new double[b9_v_counter]; b9_nx=new double[b9_v_counter];b9_ny=new double[b9_v_counter];b9_vert_b_id=new int[b9_v_counter];
     b9_evertex1_x=new double[b9_e_counter];b9_evertex1_y=new double[b9_e_counter]; b9_eex=new double[b9_e_counter];b9_eey=new double[b9_e_counter];b9_edge_b_id=new int[b9_e_counter];

//cout<<"get here2"<<endl;
out_vertex_id=new int[out_v_counter]; out_vertex_x=new double[out_v_counter];out_vertex_y=new double[out_v_counter]; out_nx=new double[out_v_counter];out_ny=new double[out_v_counter]; out_vert_b_id=new int[out_v_counter];
     out_evertex1_x=new double[out_e_counter];out_evertex1_y=new double[out_e_counter]; out_eex=new double[out_e_counter];out_eey=new double[out_e_counter];out_edge_b_id=new int[out_e_counter];
     //cout<<"get here2"<<endl;
counter=1;


assign_boundary_box_data();
b1_min_dist= new double[b1_v_counter];
b2_min_dist= new double[b2_v_counter];
b3_min_dist= new double[b3_v_counter];
b4_min_dist= new double[b4_v_counter];
b5_min_dist= new double[b5_v_counter];
b6_min_dist= new double[b6_v_counter];
b7_min_dist= new double[b7_v_counter];
b8_min_dist= new double[b8_v_counter];
b9_min_dist= new double[b9_v_counter];

int count=0;

/*for(int i=1;i<=b9_e_counter;i++){
          cout  <<  b9_evertex1_x[i] << endl;
         cout << b9_evertex1_y[i] << endl;
         cout << b9_eex[i] << endl;
          cout  << b9_eey[i] << endl;
           cout <<b9_edge_b_id[i] << endl;
           cout<<" "<<endl;
           // cout << "b4_vertex_y[" << i <<"]="<< " " << b4_vertex_y[i] << endl;
         //cout << "b2_nx[" << i <<"]="<< " " << b2_nx[i] << endl;
          //cout << "b2_ny[" << i <<"]="<< " " << b2_ny[i] << endl;
          //cout << "b2_vert_b_id[" << i <<"]="<< " " << b2_vert_b_id[i] << endl;

           count++;
}

cout<<"count="<<count<<endl;*/

for(int i=1;i<=b4_v_counter;i++){
    //cout<<"get inside loop"<<endl;
     /*cout << "b4_vertex_id[" << i <<"]="<< " " << b4_vertex_id[i] << endl;
         cout << "b4_vertex_x[" << i <<"]="<< " " << b4_vertex_x[i] << endl;
         cout << "b4_vertex_y[" << i <<"]="<< " " << b4_vertex_y[i] << endl;
         cout << "b4_nx[" << i <<"]="<< " " << b4_nx[i] << endl;
          cout << "b4_ny[" << i <<"]="<< " " << b4_ny[i] << endl;
          cout << "b4_vert_b_id[" << i <<"]="<< " " << b4_vert_b_id[i] << endl;*/
        // cout << "b1_evertex1_x[" << i <<"]="<< " " << b1_evertex1_x[i] << endl;
        // cout << "b1_evertex1_y[" << i <<"]"<< " " << b1_evertex1_y[i] << endl;
         //cout << "b1_eex[" << i <<"]"<< " " << b1_eex[i] << endl;
         //cout << "b1_eey[" << i <<"]"<< " " << b1_eey[i] << endl;

}


}


void Bubble_Optimiser::read_vertex_file(){
    int v_id=0, b_id=0; double v_x=0.0, v_y=0.0, v_nx=0.0, v_ny=0.0;
   int vid; int bid; double vnx; double vny; double vert_x=0.0;double vert_y=0.0;
//int b1_vid=0, b1_bid=0; double b1_vx=0.0, b1_vy=0.0, b1_vnx=0.0, b1_vny=0.0;
/*int b2_vid=0, b1_bid=0; double b1_vx=0.0, b1_vy=0.0, b1_vnx=0.0, b1_vny=0.0;
int b1_vid=0, b1_bid=0; double b1_vx=0.0, b1_vy=0.0, b1_vnx=0.0, b1_vny=0.0;
int b1_vid=0, b1_bid=0; double b1_vx=0.0, b1_vy=0.0, b1_vnx=0.0, b1_vny=0.0;
int b1_vid=0, b1_bid=0; double b1_vx=0.0, b1_vy=0.0, b1_vnx=0.0, b1_vny=0.0;*/
ifstream read("../input_output_files/vertex_list_output.dat");
int i=1;
while (read>>v_id>>v_x>>v_y>>v_nx>>v_ny>>b_id){
   vertex_id[i]=v_id; vertex_x[i]=v_x; vertex_y[i]=v_y; vertex_nx[i]=v_nx; vertex_ny[i]=v_ny; bubble_id[i]=b_id;
   //Vertex_id[i]=v_id; Vertex_x[i]=v_x; Vertex_y[i]=v_y; Vertex_nx[i]=v_nx; Vertex_ny[i]=v_ny; Vertex_bub_id[i]=b_id;
     //cout<<Vertex_id[i]<<" "<<Vertex_x[i]<<" "<<Vertex_y[i]<<" "<<Vertex_nx[i]<<" "<<Vertex_ny[i]<<" "<<Vertex_bub_id[i]<<endl;
i++;
}

//read_vertex_to_4quadrants();
//cout<<"counter vertex="<<" "<<i<<endl;
/*bubbles_data data;
for(int i=0;i<number_of_vertex;i++){
    data.vertex_X[number_of_vertex]=vertex_x[i];
    data.vertex_Y[number_of_vertex]=vertex_y[i];
    data.Nx[number_of_vertex]=vertex_nx[i];
    data.Ny[number_of_vertex]=vertex_ny[i];
}*/


}

void Bubble_Optimiser::read_vertex_to_4quadrants(){
    for(int i=1;i<=number;i++){
          if(BoundingBoxContainsVertices(TopLeftQuadrant, Vertex_x[i], Vertex_y[i])){
              box1_vertices.vertex_id.push_back(Vertex_id[i]);
              box1_vertices.vertex_x.push_back(Vertex_x[i]);
              box1_vertices.vertex_y.push_back(Vertex_y[i]);
              box1_vertices.vertex_nx.push_back(Vertex_nx[i]);
              box1_vertices.vertex_ny.push_back(Vertex_ny[i]);
              box1_vertices.vert_bub_id.push_back(Vertex_bub_id[i]);
          }
          else if(BoundingBoxContainsVertices(TopRightQuadrant, Vertex_x[i], Vertex_y[i])){
              box2_vertices.vertex_id.push_back(Vertex_id[i]);
              box2_vertices.vertex_x.push_back(Vertex_x[i]);
              box2_vertices.vertex_y.push_back(Vertex_y[i]);
              box2_vertices.vertex_nx.push_back(Vertex_nx[i]);
              box2_vertices.vertex_ny.push_back(Vertex_ny[i]);
              box2_vertices.vert_bub_id.push_back(Vertex_bub_id[i]);
          }else if(BoundingBoxContainsVertices(BottomLeftQuadrant, Vertex_x[i], Vertex_y[i])){
              box3_vertices.vertex_id.push_back(Vertex_id[i]);
              box3_vertices.vertex_x.push_back(Vertex_x[i]);
              box3_vertices.vertex_y.push_back(Vertex_y[i]);
              box3_vertices.vertex_nx.push_back(Vertex_nx[i]);
              box3_vertices.vertex_ny.push_back(Vertex_ny[i]);
              box3_vertices.vert_bub_id.push_back(Vertex_bub_id[i]);

          }else if(BoundingBoxContainsVertices(BottomRightQuadrant, Vertex_x[i], Vertex_y[i])){
              box4_vertices.vertex_id.push_back(Vertex_id[i]);
              box4_vertices.vertex_x.push_back(Vertex_x[i]);
              box4_vertices.vertex_y.push_back(Vertex_y[i]);
              box4_vertices.vertex_nx.push_back(Vertex_nx[i]);
              box4_vertices.vertex_ny.push_back(Vertex_ny[i]);
              box4_vertices.vert_bub_id.push_back(Vertex_bub_id[i]);

          }
    }


}

void Bubble_Optimiser::read_edge_file(){
    int e_id = 0, e_v1_id = 0;
     int e_v2_id = 0;
     double e_v1_x = 0.0;
     double e_v1_y = 0.0;
     double e_v2_x = 0.0;
     double e_v2_y = 0.0;
     double eex = 0.0;
     double eey = 0.0;
     int e_bub_id = 0;

    ifstream read("../input_output_files/edge_list_output.dat");
    int i=1;
    while (read >> e_id >>e_v1_id>>e_v2_id>> e_v1_x >> e_v1_y >> e_v2_x >> e_v2_y >> eex >> eey >> e_bub_id) {
       /* edge_id[i] = e_id;
        edge_vertex1_id[i] = e_v1_id;
        edge_vertex2_id[i] = e_v2_id;
        edge_vertex1_x[i] = e_v1_x;
        edge_vertex1_y[i] = e_v1_y;
        edge_vertex2_x[i] = e_v2_x;
        edge_vertex2_y[i] = e_v2_y;
        ee_x[i] = eex;
        ee_y[i] = eey;
        edge_bubble_id[i] = e_bub_id;*/
        // cout << Edge_id[i] << " " <<Evertex1_id[i] << " " << Evertex2_id[i] <<" "<<Evertex1_x[i] << " " << Evertex1_y[i] << " " << Evertex2_x[i] << " " << Evertex2_y[i] << " " << Eex[i] << " " << Eey[i] << " " << Edge_bub_id[i] << endl;

          edge_id[i] = e_id;
          edge_vertex1_id[i] = e_v1_id;
          edge_vertex2_id[i] = e_v2_id;
          edge_vertex1_x[i] = e_v1_x;
          edge_vertex1_y[i] = e_v1_y;
          edge_vertex2_x[i] = e_v2_x;
          edge_vertex2_y[i] = e_v2_y;
          ee_x[i] = eex;
          ee_y[i] = eey;
          edge_bubble_id[i] = e_bub_id;
         // cout << edge_id[i] << " " << edge_vertex1_id[i] << " " << edge_vertex2_id[i] << " " << edge_vertex1_x[i] << " " << edge_vertex1_y[i] << " " << edge_vertex2_x[i] << " " << edge_vertex2_y[i] << " " << ee_x[i] << " " << ee_y[i] << " " << edge_bubble_id[i] << endl;
i++;
      }
/*bubbles_data data;
    for(int i=0;i<number_of_edges;i++){
        data.edge_vertex1_X[number_of_edges]=edge_vertex1_x[i];
        data.edge_vertex1_Y[number_of_edges]=edge_vertex1_y[i];
        data.ee_X[number_of_edges]=ee_x[i];
        data.ee_Y[number_of_edges]=ee_y[i];
    }*/
//cout<<"counter edge="<<" "<<i<<endl;
}




void Bubble_Optimiser::calc_min_distance(){
   /* cout<<"b1_v_counter="<<" "<<b1_v_counter<<endl;
    cout<<"b2_v_counter="<<" "<<b2_v_counter<<endl;
     cout<<"b3_v_counter="<<" "<<b3_v_counter<<endl;
      cout<<"b4_v_counter="<<" "<<b4_v_counter<<endl;*/
    double ll, mm, denoms;
    for(int i=1;i<=b1_v_counter;i++){
        b1_min_dist[i]=4.0;
        for(int j=1;j<=b1_e_counter;j++){

           /*cout << "b1_evertex1_x[" << i <<"]="<< " " << b1_evertex1_x[i] << endl;
           cout << "b1_evertex1_y[" << i <<"]"<< " " << b1_evertex1_y[i] << endl;
           cout << "b1_eex[" << i <<"]"<< " " << b1_eex[i] << endl;
            cout << "b1_eey[" << i <<"]"<< " " << b1_eey[i] << endl;*/
            if(b1_vert_b_id[i]!=b1_edge_b_id[j]){
              denoms=b1_eex[j]*b1_ny[i]-b1_eey[j]*b1_nx[i];
            if(denoms!=0){
               ll = ((b1_eey[j]*b1_vertex_x[i]-b1_eex[j]*b1_vertex_y[i]) - (b1_evertex1_x[j]*b1_eey[j]-b1_evertex1_y[j]*b1_eex[j]) ) / denoms;

               mm = ((b1_ny[i]*b1_vertex_x[i]-b1_nx[i]*b1_vertex_y[i]) - (b1_evertex1_x[j]*b1_ny[i]-b1_evertex1_y[j]*b1_nx[i]) ) / denoms;
                if(mm>=0 && mm<=1){
                    if(abs(ll)<b1_min_dist[i]){
                        b1_min_dist[i]=abs(ll);
                    }

                }

                }
            }
           // getchar();
        }

    }

    for(int i=1;i<=b2_v_counter;i++){
         b2_min_dist[i]=4.0;
        for(int j=1;j<=b2_e_counter;j++){
           /* cout << "b2_vertex_x[" << i <<"]="<< " " << b2_vertex_x[i] << endl;
            cout << "b2_vertex_y[" << i <<"]="<< " " << b2_vertex_y[i] << endl;
            cout << "b2_nx[" << i <<"]="<< " " << b2_nx[i] << endl;
             cout << "b2_ny[" << i <<"]="<< " " << b2_ny[i] << endl;
              cout << "b2_evertex1_x[" << j <<"]="<< " " << b2_evertex1_x[j] << endl;
             cout << "b2_evertex1_y[" << j<<"]"<< " " << b2_evertex1_y[j] << endl;
              cout << "b2_eex[" << j <<"]"<< " " << b2_eex[j] << endl;
              cout << "b2_eey[" << j <<"]"<< " " << b2_eey[j] << endl;*/

           // cout<<"b2_vert_b_id["<<i<<"]="<<" "<<b2_vert_b_id[i]<<endl;
           // cout<<"b2_edge_b_id["<<j<<"]="<<" "<<b2_edge_b_id[j]<<endl;

            if(b2_vert_b_id[i]!=b2_edge_b_id[j]){
              denoms=b2_eex[j]*b2_ny[i]-b2_eey[j]*b2_nx[i];
            if(denoms!=0){
               ll = ((b2_eey[j]*b2_vertex_x[i]-b2_eex[j]*b2_vertex_y[i]) - (b2_evertex1_x[j]*b2_eey[j]-b2_evertex1_y[j]*b2_eex[j]) ) / denoms;

               mm = ((b2_ny[i]*b2_vertex_x[i]-b2_nx[i]*b2_vertex_y[i]) - (b2_evertex1_x[j]*b2_ny[i]-b2_evertex1_y[j]*b2_nx[i]) ) / denoms;

               //cout<<"mm="<<" "<<mm<<endl;
                  //cout<<"mm="<<" "<<mm<<endl;
                if(mm>=0 && mm<=1){
                   // cout<<"b2_min1["<<i<<"]="<<" "<<b2_min_dist[i]<<endl;
                    if(abs(ll)<b2_min_dist[i]){
                        b2_min_dist[i]=abs(ll);
                    //cout<<"b2_min2["<<i<<"]="<<" "<<b2_min_dist[i]<<endl;
                    }

                }

                }
            }
            //getchar();
        }

    }





    for(int i=1;i<=b3_v_counter;i++){
        b3_min_dist[i]=4.0;
        for(int j=1;j<=b3_e_counter;j++){

            if(b3_vert_b_id[i]!=b3_edge_b_id[j]){
              denoms=b3_eex[j]*b3_ny[i]-b3_eey[j]*b3_nx[i];
            if(denoms!=0){
               ll = ((b3_eey[j]*b3_vertex_x[i]-b3_eex[j]*b3_vertex_y[i]) - (b3_evertex1_x[j]*b3_eey[j]-b3_evertex1_y[j]*b3_eex[j]) ) / denoms;

               mm = ((b3_ny[i]*b3_vertex_x[i]-b3_nx[i]*b3_vertex_y[i]) - (b3_evertex1_x[j]*b3_ny[i]-b3_evertex1_y[j]*b3_nx[i]) ) / denoms;
               if(mm>=0 && mm<=1){
        if(abs(ll)<b3_min_dist[i]){
            b3_min_dist[i]=abs(ll);
        }

    }

    }
}

        }

    }

    for(int i=1;i<=b4_v_counter;i++){
         b4_min_dist[i]=4.0;
        for(int j=1;j<=b4_e_counter;j++){

            if(b4_vert_b_id[i]!=b4_edge_b_id[j]){
              denoms=b4_eex[j]*b4_ny[i]-b4_eey[j]*b4_nx[i];
            if(denoms!=0){
               ll = ((b4_eey[j]*b4_vertex_x[i]-b4_eex[j]*b4_vertex_y[i]) - (b4_evertex1_x[j]*b4_eey[j]-b4_evertex1_y[j]*b4_eex[j]) ) / denoms;

               mm = ((b4_ny[i]*b4_vertex_x[i]-b4_nx[i]*b4_vertex_y[i]) - (b4_evertex1_x[j]*b4_ny[i]-b4_evertex1_y[j]*b4_nx[i]) ) / denoms;
                 if(mm>=0 && mm<=1){
                    if(abs(ll)<b4_min_dist[i]){
                        b4_min_dist[i]=abs(ll);
                    }

                }

                }
            }

        }

    }

    for(int i=1;i<=b5_v_counter;i++){
        b5_min_dist[i]=4.0;
        for(int j=1;j<=b5_e_counter;j++){

          /* cout << "b1_evertex1_x[" << i <<"]="<< " " << b1_evertex1_x[i] << endl;
           cout << "b1_evertex1_y[" << i <<"]"<< " " << b1_evertex1_y[i] << endl;
           cout << "b1_eex[" << i <<"]"<< " " << b1_eex[i] << endl;
            cout << "b1_eey[" << i <<"]"<< " " << b1_eey[i] << endl;*/
            if(b5_vert_b_id[i]!=b5_edge_b_id[j]){
              denoms=b5_eex[j]*b5_ny[i]-b5_eey[j]*b5_nx[i];
            if(denoms!=0){
               ll = ((b5_eey[j]*b5_vertex_x[i]-b5_eex[j]*b5_vertex_y[i]) - (b5_evertex1_x[j]*b5_eey[j]-b5_evertex1_y[j]*b5_eex[j]) ) / denoms;

               mm = ((b5_ny[i]*b5_vertex_x[i]-b5_nx[i]*b5_vertex_y[i]) - (b5_evertex1_x[j]*b5_ny[i]-b5_evertex1_y[j]*b5_nx[i]) ) / denoms;
                if(mm>=0 && mm<=1){
                    if(abs(ll)<b5_min_dist[i]){
                        b5_min_dist[i]=abs(ll);
                    }

                }

                }
            }
           // getchar();
        }

    }

    for(int i=1;i<=b6_v_counter;i++){
         b6_min_dist[i]=4.0;
        for(int j=1;j<=b6_e_counter;j++){
          /* cout << "b2_vertex_x[" << i <<"]="<< " " << b2_vertex_x[i] << endl;
            cout << "b2_vertex_y[" << i <<"]="<< " " << b2_vertex_y[i] << endl;
            cout << "b2_nx[" << i <<"]="<< " " << b2_nx[i] << endl;
             cout << "b2_ny[" << i <<"]="<< " " << b2_ny[i] << endl;
              cout << "b2_evertex1_x[" << j <<"]="<< " " << b2_evertex1_x[j] << endl;
             cout << "b2_evertex1_y[" << j<<"]"<< " " << b2_evertex1_y[j] << endl;
              cout << "b2_eex[" << j <<"]"<< " " << b2_eex[j] << endl;
              cout << "b2_eey[" << j <<"]"<< " " << b2_eey[j] << endl;*/

           // cout<<"b2_vert_b_id["<<i<<"]="<<" "<<b2_vert_b_id[i]<<endl;
           // cout<<"b2_edge_b_id["<<j<<"]="<<" "<<b2_edge_b_id[j]<<endl;

            if(b6_vert_b_id[i]!=b6_edge_b_id[j]){
              denoms=b6_eex[j]*b6_ny[i]-b6_eey[j]*b6_nx[i];
            if(denoms!=0){
               ll = ((b6_eey[j]*b6_vertex_x[i]-b6_eex[j]*b6_vertex_y[i]) - (b6_evertex1_x[j]*b6_eey[j]-b6_evertex1_y[j]*b6_eex[j]) ) / denoms;

               mm = ((b6_ny[i]*b6_vertex_x[i]-b6_nx[i]*b6_vertex_y[i]) - (b6_evertex1_x[j]*b6_ny[i]-b6_evertex1_y[j]*b6_nx[i]) ) / denoms;

               //cout<<"mm="<<" "<<mm<<endl;
                  //cout<<"mm="<<" "<<mm<<endl;
                if(mm>=0 && mm<=1){
                   // cout<<"b2_min1["<<i<<"]="<<" "<<b2_min_dist[i]<<endl;
                    if(abs(ll)<b6_min_dist[i]){
                        b6_min_dist[i]=abs(ll);
                    //cout<<"b2_min2["<<i<<"]="<<" "<<b2_min_dist[i]<<endl;
                    }

                }

                }
            }
            //getchar();
        }

    }


    for(int i=1;i<=b7_v_counter;i++){
        b7_min_dist[i]=4.0;
        for(int j=1;j<=b7_e_counter;j++){
            /*cout << "b2_vertex_x[" << i <<"]="<< " " << b7_vertex_x[i] << endl;
             cout << "b2_vertex_y[" << i <<"]="<< " " << b7_vertex_y[i] << endl;
             cout << "b2_nx[" << i <<"]="<< " " << b7_nx[i] << endl;
              cout << "b2_ny[" << i <<"]="<< " " << b7_ny[i] << endl;
               cout << "b2_evertex1_x[" << j <<"]="<< " " << b7_evertex1_x[j] << endl;
              cout << "b2_evertex1_y[" << j<<"]"<< " " << b7_evertex1_y[j] << endl;
               cout << "b2_eex[" << j <<"]"<< " " << b7_eex[j] << endl;
               cout << "b2_eey[" << j <<"]"<< " " << b7_eey[j] << endl;

             cout<<"b2_vert_b_id["<<i<<"]="<<" "<<b7_vert_b_id[i]<<endl;
             cout<<"b2_edge_b_id["<<j<<"]="<<" "<<b7_edge_b_id[j]<<endl;*/


            if(b7_vert_b_id[i]!=b7_edge_b_id[j]){

              denoms=b7_eex[j]*b7_ny[i]-b7_eey[j]*b7_nx[i];
              //cout<<"denoms="<<" "<<denoms<<endl;
            if(denoms!=0){
               ll = ((b7_eey[j]*b7_vertex_x[i]-b7_eex[j]*b7_vertex_y[i]) - (b7_evertex1_x[j]*b7_eey[j]-b7_evertex1_y[j]*b7_eex[j]) ) / denoms;
//cout<<"ll="<<" "<<ll<<endl;
               mm = ((b7_ny[i]*b7_vertex_x[i]-b7_nx[i]*b7_vertex_y[i]) - (b7_evertex1_x[j]*b7_ny[i]-b7_evertex1_y[j]*b7_nx[i]) ) / denoms;
             //cout<<"mm="<<" "<<mm<<endl;
               if(mm>=0 && mm<=1){
                   //cout<<"mindist 1="<<" "<<b7_min_dist[i]<<endl;
        if(abs(ll)<b7_min_dist[i]){
            b7_min_dist[i]=abs(ll);
            //cout<<"mindist 2="<<" "<<b7_min_dist[i]<<endl;
        }

    }

    }
}
//getchar();
        }

    }


    for(int i=1;i<=b8_v_counter;i++){
         b8_min_dist[i]=4.0;
        for(int j=1;j<=b8_e_counter;j++){

            if(b8_vert_b_id[i]!=b8_edge_b_id[j]){
              denoms=b8_eex[j]*b8_ny[i]-b8_eey[j]*b8_nx[i];
            if(denoms!=0){
               ll = ((b8_eey[j]*b8_vertex_x[i]-b8_eex[j]*b8_vertex_y[i]) - (b8_evertex1_x[j]*b8_eey[j]-b8_evertex1_y[j]*b8_eex[j]) ) / denoms;

               mm = ((b8_ny[i]*b8_vertex_x[i]-b8_nx[i]*b8_vertex_y[i]) - (b8_evertex1_x[j]*b8_ny[i]-b8_evertex1_y[j]*b8_nx[i]) ) / denoms;
                 if(mm>=0 && mm<=1){
                    if(abs(ll)<b8_min_dist[i]){
                        b8_min_dist[i]=abs(ll);
                    }

                }

                }
            }

        }

    }

    for(int i=1;i<=b9_v_counter;i++){
         b9_min_dist[i]=4.0;
        for(int j=1;j<=b9_e_counter;j++){

            if(b9_vert_b_id[i]!=b9_edge_b_id[j]){
              denoms=b9_eex[j]*b9_ny[i]-b9_eey[j]*b9_nx[i];
            if(denoms!=0){
               ll = ((b9_eey[j]*b9_vertex_x[i]-b9_eex[j]*b9_vertex_y[i]) - (b9_evertex1_x[j]*b9_eey[j]-b9_evertex1_y[j]*b9_eex[j]) ) / denoms;

               mm = ((b9_ny[i]*b9_vertex_x[i]-b9_nx[i]*b9_vertex_y[i]) - (b9_evertex1_x[j]*b9_ny[i]-b9_evertex1_y[j]*b9_nx[i]) ) / denoms;
                 if(mm>=0 && mm<=1){
                    if(abs(ll)<b9_min_dist[i]){
                        b9_min_dist[i]=abs(ll);
                    }

                }

                }
            }

        }

    }



//print_mininum_distance();

}

void Bubble_Optimiser::print_mininum_distance() {

    for (int i = 1; i <= b1_v_counter; i++) {
        //cout<<b1_vertex_x[i] <<" "<< b1_vertex_y[i]<< " " << b1_min_dist[i] << endl;
       cout << "vertex[" << b1_vertex_id[i]<< "].mindistio:=" << " " << b1_min_dist[i] << endl;
    }

    for (int i = 1; i <= b2_v_counter; i++) {
        //cout<<b2_vertex_x[i] <<" "<< b2_vertex_y[i]<< " " << b2_min_dist[i] << endl;
        cout << "vertex[" << b2_vertex_id[i]<< "].mindistio:=" << " " << b2_min_dist[i] << endl;
    }

    for (int i = 1; i <= b3_v_counter; i++) {
        //cout<<b3_vertex_x[i] <<" "<< b3_vertex_y[i]<< " " << b3_min_dist[i] << endl;
        cout << "vertex[" << b3_vertex_id[i]<< "].mindistio:=" << " " << b3_min_dist[i] << endl;
    }
    for (int i = 1; i <= b4_v_counter; i++) {
        //cout<<b4_vertex_x[i] <<" "<< b4_vertex_y[i]<< " " << b4_min_dist[i] << endl;

       cout << "vertex[" << b4_vertex_id[i]<< "].mindistio:=" << " " << b4_min_dist[i] << endl;
    }

    for (int i = 1; i <= b5_v_counter; i++) {
       cout << "vertex[" << b5_vertex_id[i]<< "].mindistio:=" << " " << b5_min_dist[i] << endl;
    }

    for (int i = 1; i <= b6_v_counter; i++) {
        cout << "vertex[" << b6_vertex_id[i]<< "].mindistio:=" << " " << b6_min_dist[i] << endl;
    }
    for (int i = 1; i <= b7_v_counter; i++) {
        cout << "vertex[" << b7_vertex_id[i]<< "].mindistio:=" << " " << b7_min_dist[i] << endl;
    }
    for (int i = 1; i <= b8_v_counter; i++) {
        cout << "vertex[" << b8_vertex_id[i]<< "].mindistio:=" << " " << b8_min_dist[i] << endl;
    }

    for (int i = 1; i <= b9_v_counter; i++) {
        cout << "vertex[" << b9_vertex_id[i]<< "].mindistio:=" << " " << b9_min_dist[i] << endl;
    }


    //cout<<"b2vc"<<" "<<b2_v_counter<<endl;
    for (int i = 1; i <= number; i++) {
        //cout << "vertex[" << i << "].mindistio:=" << " " << min_dist[i] << endl;
    }

    //ofstream outfile;
    //outfile.open("../input_output_files/mininum_distance.dat");
    //outfile<<"mindistio:=\n";
    //for(int i=1;i<=number;i++){
    //outfile<<"vertex["<<i<<"].mindistio:="<<" "<<min_dist[i];
    //}
    //outfile.close();
}


void Bubble_Optimiser::calc_mindist(){

double ll, mm, denoms;
    for(int i=1;i<=number;i++){
         min_dist[i]=4.0;
        for(int j=1;j<=edge_number;j++){
            if(bubble_id[i]!=edge_bubble_id[j]){
                denoms=ee_x[j]*vertex_ny[i]-ee_y[j]*vertex_nx[i];
            if(denoms!=0){
                 ll = ((ee_y[j]*vertex_x[i]-ee_x[j]*vertex_y[i]) - (edge_vertex1_x[j]*ee_y[j]-edge_vertex1_y[j]*ee_x[j]) ) / denoms;
                 mm = ((vertex_ny[i]*vertex_x[i]-vertex_nx[i]*vertex_y[i]) - (edge_vertex1_x[j]*vertex_ny[i]-edge_vertex1_y[j]*vertex_nx[i]) ) / denoms;
                if(mm>=0 && mm<=1){
                    if(abs(ll)<min_dist[i]){
                        min_dist[i]=abs(ll);
                    }

                }

                }
            }

        }
cout<<vertex_x[i]<<" "<<vertex_y[i]<<" "<<min_dist[i]<<endl;
    }


//print_mininum_distance();

}




void Bubble_Optimiser::calc_mindist_vec(){

double ll, mm, denoms;
    for(int i=1;i<= number;i++){
         min_dist[i]=4.0;
        for(int j=1;j<=edge_number;j++){

            if(Vertex_bub_id[i]!=Edge_bub_id[j]){
                denoms=Eex[j]*Vertex_ny[i]-Eey[j]*Vertex_nx[i];
            if(denoms!=0){
                 ll = ((Eey[j]*Vertex_x[i]-Eex[j]*Vertex_y[i]) - (Evertex1_x[j]*Eey[j]-Evertex1_y[j]*Eex[j]) ) / denoms;
                 mm = ((Vertex_ny[i]*Vertex_x[i]-Vertex_nx[i]*Vertex_y[i]) - (Evertex1_x[j]*Vertex_ny[i]-Evertex1_y[j]*Vertex_nx[i]) ) / denoms;
                if(mm>=0 && mm<=1){
                    if(abs(ll)<min_dist[i]){
                        min_dist[i]=abs(ll);
                    }

                }

                }
            }

        }
    }

    /*for (int i = 1; i <=number; i++) {
        cout << "vertex[" << i << "].mindistio:=" << " " << min_dist[i] << endl;
    }*/
//print_mininum_distance();

}



void Bubble_Optimiser::simple_spatial_partition(double x0, double y0, double x1, double y1){

   // BoundingBox box=this-> boundingBox;

    double xmid= (x0 + x1)/2.0;
    double ymid= (y0 + y1)/2.0;

    TopLeftQuadrant=MakeBoundingBox(x0, y0, xmid, ymid);
    TopRightQuadrant=MakeBoundingBox(xmid, y0, x1, ymid);
    BottomLeftQuadrant=MakeBoundingBox(x0,ymid, xmid, y1);
    BottomRightQuadrant=MakeBoundingBox(xmid, ymid, x1, y1);

    double xthird=x0+1.3;
    double x_2third=xthird+1.3;
    double ythird=y0-1.3;
    double y_2third=ythird-1.3;


    box1 = MakeBoundingBox(x0, y0, xthird, ythird); // left top quadrant bounding box
    box2= MakeBoundingBox(xthird, y0, x_2third, ythird); //middle top quadrant bounding box
    box3= MakeBoundingBox(x_2third, y0, x1, ythird); //right top quadrant bounding box
    box4= MakeBoundingBox(x0, ythird, xthird, y_2third); //left middle quadrant bounding box
    box5= MakeBoundingBox(xthird, ythird, x_2third, y_2third); //Central middle quadrant bounding box
    box6= MakeBoundingBox(x_2third, ythird, x1, y_2third); //Right middle quadrant bounding box
    box7 = MakeBoundingBox(x0, y_2third, xthird, y1);
    box8 = MakeBoundingBox(xthird, y_2third, x_2third, y1);
    box9= MakeBoundingBox(x_2third, y_2third, x1, y1);

}

void Bubble_Optimiser::simple_edge_partition(double x0, double y0, double x1, double y1){

   // BoundingBox box=this-> boundingBox;

    double xmid= (x0 + x1)/2.0;
    double xquart1 = (x0 + xmid) / 2.0;
    double xquart2 = (xmid + x1) / 2.0;
    double ymid= (y0 + y1)/2.0;
    double yquart1 = (y0 + ymid) / 2.0; // first quarter along y axis
    double yquart2 = (ymid + y1) / 2.0; // second quarter along y axis

    edgebox1=MakeBoundingBox(x0, y0, xquart2, yquart2);
     edgebox2=MakeBoundingBox(xquart1, y0, x1, yquart2);
     edgebox3=MakeBoundingBox(x0,yquart1, xquart2, y1);
     edgebox4=MakeBoundingBox(xquart1, yquart1, x1, y1);



   /* edgebox1=MakeBoundingBox(-2.0, 2.0, 1.0, -1.0);
    edgebox2=MakeBoundingBox(-1.0, 2.0, 2.0, -1.0);
    edgebox3=MakeBoundingBox(-2.0,1.0, 1.0, -2.0);
    edgebox4=MakeBoundingBox(-1.0, 1.0, 2.0, -2.0);*/

    double xthird=x0+1.3;
    double x_2third=xthird+1.3;
    double ythird=y0-1.3;
    double y_2third=ythird-1.3;

    edge_box1 = MakeBoundingBox(x0, y0, x_2third, y_2third);
    edge_box2= MakeBoundingBox(x0, y0, x1, y_2third);
    edge_box3= MakeBoundingBox(xthird, y0, x1, y_2third);
    edge_box4= MakeBoundingBox(x0, y0, x_2third, y1);
    edge_box5= MakeBoundingBox(x0, y0, x1, y1);
    edge_box6= MakeBoundingBox(xthird, y0, x1, y1);
    edge_box7 = MakeBoundingBox(x0, ythird, x_2third, y1);
    edge_box8 = MakeBoundingBox(x0, ythird, x1, y1);
    edge_box9= MakeBoundingBox(xthird, ythird, x1, y1);

}


void Bubble_Optimiser::overlapping_spatial_partition(double x0, double y0, double x1, double y1){

    double xmid = (x0 + x1) / 2.0;
        double xquart1 = (x0 + xmid) / 2.0;
        double xquart1b = (x0 + xquart1) / 2.0;
        double xquart1c= (xquart1+xmid) / 2.0;
        double xquart2 = (xmid + x1) / 2.0;
        double xquart2b = (xmid + xquart2) / 2.0;
        double xquart2c = (xquart2 + x1) / 2.0;
        double ymid = (y0 + y1) / 2.0;
        double yquart1 = (y0 + ymid) / 2.0; // first quarter along y axis
        double yquart1b = (y0 + yquart1) / 2.0; // first quarter along y axis
        double yquart1c = (yquart1+ymid) / 2.0; // first quarter along y axis
        double yquart2 = (ymid + y1) / 2.0; // second quarter along y axis
        double yquart2b = (yquart2 + ymid) / 2.0;
        double yquart2c = (yquart2 + y1) / 2.0;

        double xthird=x0+1.3;
        double x_2third=xthird+1.3;
        double ythird=y0-1.3;
        double y_2third=ythird-1.3;

        /*cout << "xthird="<< " " << xthird << endl;
        cout << "x_2third="<< " " << x_2third<< endl;
        cout << "ythird="<< " " << ythird<< endl;
        cout << "y_2third="<< " " << y_2third<< endl;*/


        //creating 9 overlapping bounding boxescdcd
       TopLeftQuadrant = MakeBoundingBox(x0, y0, xmid, ymid); // left top quadrant bounding box
        TopMidQuadrant = MakeBoundingBox(xquart1, y0, xquart2, ymid); //middle top quadrant bounding box
        TopRightQuadrant = MakeBoundingBox(xmid, y0, x1, ymid); //right top quadrant bounding box
        LeftMidQuadrant = MakeBoundingBox(x0, yquart1, xmid, yquart2); //left middle quadrant bounding box
        MidMidQuadrant = MakeBoundingBox(xquart1, yquart1, xquart2, yquart2); //Central middle quadrant bounding box
        RightMidQuadrant = MakeBoundingBox(xmid, yquart1, x1, yquart2); //Right middle quadrant bounding box
        BottomLeftQuadrant = MakeBoundingBox(x0, ymid, xmid, y1);
        BottomMidQuadrant = MakeBoundingBox(xquart1, ymid, xquart2, y1);
        BottomRightQuadrant = MakeBoundingBox(xmid, ymid, x1, y1);




                //bounding boxes for in which each vertex in a box search for edges for mindist computation

                edge_box1 = MakeBoundingBox(x0, y0, x_2third, y_2third); // left top quadrant bounding box
                edge_box2= MakeBoundingBox(x0, y0, x1, y_2third); //middle top quadrant bounding box
                edge_box3= MakeBoundingBox(xthird, y0, x1, y_2third); //right top quadrant bounding box
                edge_box4= MakeBoundingBox(x0, y0, x_2third, y1); //left middle quadrant bounding box
                edge_box5= MakeBoundingBox(x0, y0, x1, y1); //Central middle quadrant bounding box
                edge_box6= MakeBoundingBox(xthird, y0, x1, y1); //Right middle quadrant bounding box
                edge_box7 = MakeBoundingBox(x0, ythird, x_2third, y1);
                edge_box8 = MakeBoundingBox(x0, ythird, x1, y1);
                edge_box9= MakeBoundingBox(xthird, ythird, x1, y1);

       /* box1 = MakeBoundingBox(x0, y0, xquart1, yquart1); // left top quadrant bounding box
        box2= MakeBoundingBox(xquart1b, y0, xquart1c, yquart1); //middle top quadrant bounding box
        box3= MakeBoundingBox(xquart1, y0, xmid, yquart1); //right top quadrant bounding box
        box4= MakeBoundingBox(xquart1c, y0, xquart2b, yquart1); //left middle quadrant bounding box
        box5= MakeBoundingBox(xmid, y0, xquart2, yquart1); //Central middle quadrant bounding box
        box6= MakeBoundingBox(xquart2b, y0, xquart2c, yquart1); //Right middle quadrant bounding box
        box7 = MakeBoundingBox(xquart2, y0, x1, yquart1);
        box8 = MakeBoundingBox(x0, yquart1b, xquart1, yquart1c);
        box9= MakeBoundingBox(xquart1b, yquart1b, xquart1c, yquart1c);
        box10= MakeBoundingBox(xquart1, yquart1b, xmid, yquart1c);
        box11 = MakeBoundingBox(xquart1c, yquart1b, xquart2b, yquart1c); // left top quadrant bounding box
        box12= MakeBoundingBox(xmid, yquart1b, xquart1, yquart1c); //middle top quadrant bounding box
        box13= MakeBoundingBox(xquart2b, yquart1b, xquart2c, yquart1c); //right top quadrant bounding box
        box14= MakeBoundingBox(xquart2, yquart1b, x1, yquart1c); //left middle quadrant bounding box
        box15= MakeBoundingBox(x0, yquart1, xquart1, ymid); //Central middle quadrant bounding box
        box16= MakeBoundingBox(xquart1b, yquart1, xquart1c, ymid); //Right middle quadrant bounding box
        box17 = MakeBoundingBox(xquart1, yquart1, xmid, ymid);
        box18 = MakeBoundingBox(xquart1c, yquart1, xquart2b, ymid);
        box19= MakeBoundingBox(xmid, yquart1, xquart2, ymid);
        box20= MakeBoundingBox(xquart2b, yquart1, xquart2c, ymid);
        box21 = MakeBoundingBox(xquart2, yquart1, x1, ymid); // left top quadrant bounding box
        box22= MakeBoundingBox(x0, yquart1c, xquart1, yquart2b); //middle top quadrant bounding box
        box23= MakeBoundingBox(xquart1b, yquart1c, xquart1c, yquart2b); //right top quadrant bounding box
        box24= MakeBoundingBox(xquart1, yquart1c, xmid, yquart2b); //left middle quadrant bounding box
        box25= MakeBoundingBox(xquart1c, yquart1c, xquart2b, yquart2b); //Central middle quadrant bounding box
        box26= MakeBoundingBox(xmid, yquart1c, xquart2, yquart2b); //Right middle quadrant bounding box
        box27 = MakeBoundingBox(xquart2b, yquart1c, xquart2c, yquart2b);
        box28 = MakeBoundingBox(xquart2, yquart1c, x1, yquart2b);
        box29= MakeBoundingBox(x0, ymid, xquart1, yquart2);
        box30= MakeBoundingBox(xquart1b, ymid, xquart1c, yquart2);
        box31 = MakeBoundingBox(xquart1, ymid, xmid, yquart2); // left top quadrant bounding box
        box32= MakeBoundingBox(xquart1c, ymid, xquart2b, yquart2); //middle top quadrant bounding box
        box33= MakeBoundingBox(xmid, ymid, xquart2, yquart2); //right top quadrant bounding box
        box34= MakeBoundingBox(xquart2b, ymid, xquart2c, yquart2); //left middle quadrant bounding box
        box35= MakeBoundingBox(xquart2, ymid, x1, yquart2); //Central middle quadrant bounding box
        box36= MakeBoundingBox(x0, yquart2b, xquart1, yquart2c); //Right middle quadrant bounding box
        box37 = MakeBoundingBox(xquart1b, yquart2b, xquart1c, yquart2c);
        box38 = MakeBoundingBox(xquart1, yquart2b, xmid, yquart2c);
        box39= MakeBoundingBox(xquart1c, yquart2b, xquart2b, yquart2c);
        box40= MakeBoundingBox(xmid, yquart2b, xquart2, yquart2c);
        box41 = MakeBoundingBox(xquart2b, yquart2b, xquart2c, yquart2c); // left top quadrant bounding box
        box42= MakeBoundingBox(xquart2, yquart2b, x1, yquart2c); //middle top quadrant bounding box
        box43= MakeBoundingBox(x0, yquart2, xquart1, y1); //right top quadrant bounding box
        box44= MakeBoundingBox(xquart1b, yquart2, xquart1c, y1); //left middle quadrant bounding box
        box45= MakeBoundingBox(xquart1, yquart2, xmid, y1); //Central middle quadrant bounding box
        box46= MakeBoundingBox(xquart1c, yquart2, xquart2b, y1); //Right middle quadrant bounding box
        box47 = MakeBoundingBox(xmid, yquart2, xquart2, y1);
        box48 = MakeBoundingBox(xquart2b, yquart2, xquart2c, y1);
        box49= MakeBoundingBox(xquart2, yquart2, x1, y1);*/




}

bool Bubble_Optimiser::BoundingBoxContainsVertices(BoundingBox boundary,double vertex_x, double vertex_y){

    bool contains_vertex_x = boundary.x0 <= vertex_x && vertex_x <=boundary.x1;
    bool contains_vertex_y = boundary.y0 >= vertex_y && vertex_y >= boundary.y1;

    return contains_vertex_x && contains_vertex_y;
}

bool Bubble_Optimiser::BoundingBoxContainsEdges(BoundingBox boundary, double e_vertex1_x, double e_vertex1_y/*,double e_vertex2_x,double e_vertex2_y*/){

       bool contains_e_vertex1_x = boundary.x0 <= e_vertex1_x && e_vertex1_x <= boundary.x1;
       bool contains_e_vertex1_y = boundary.y0 >=e_vertex1_y && e_vertex1_y >= boundary.y1;
      // bool contains_e_vertex2_x = boundary.x0 <= e_vertex2_x && e_vertex2_x <= boundary.x1;
       //bool contains_e_vertex2_y = boundary.y0 >= e_vertex2_y && e_vertex2_y >= boundary.y1;


       return contains_e_vertex1_x && contains_e_vertex1_y; /*&& contains_e_vertex2_x && contains_e_vertex2_y;*/


}

bool Bubble_Optimiser::BoundingBoxContainsData(BoundingBox boundary,double vertex_x, double vertex_y, double e_vertex1_x, double e_vertex1_y/*,double e_vertex2_x,double e_vertex2_y*/){


    bool contains_vertex_x = boundary.x0 <= vertex_x && vertex_x <=boundary.x1;
       bool contains_vertex_y = boundary.y0 >= vertex_y && vertex_y >= boundary.y1;
       bool contains_e_vertex1_x = boundary.x0 <= e_vertex1_x && e_vertex1_x <= boundary.x1;
       bool contains_e_vertex1_y = boundary.y0 >=e_vertex1_y && e_vertex1_y >= boundary.y1;
       //bool contains_e_vertex2_x = boundary.x0 <= e_vertex2_x && e_vertex2_x <= boundary.x1;
      //bool contains_e_vertex2_y = boundary.y0 >= e_vertex2_y && e_vertex2_y >= boundary.y1;

       return contains_vertex_x && contains_vertex_y && contains_e_vertex1_x && contains_e_vertex1_y; /* && contains_e_vertex2_x && contains_e_vertex2_y;*/


}


void Bubble_Optimiser::count_boundary_box_data(){

      b1_v_counter=0;  b2_v_counter=0; b3_v_counter=0; b4_v_counter=0;
      b5_v_counter=0;  b6_v_counter=0; b7_v_counter=0; b8_v_counter=0;b9_v_counter=0;
      b1_e_counter=0;  b2_e_counter=0; b3_e_counter=0; b4_e_counter=0;
      b5_e_counter=0;  b6_e_counter=0; b7_e_counter=0; b8_e_counter=0; b9_e_counter=0;

for(int i=1;i<=number;i++){
     /* if(BoundingBoxContainsVertices(box1, vertex_x[i], vertex_y[i])){
         b1_v_counter++;
      }
      else if(BoundingBoxContainsVertices(box2, vertex_x[i], vertex_y[i])){
          b2_v_counter++;
      }else if(BoundingBoxContainsVertices(box3, vertex_x[i], vertex_y[i])){
          b3_v_counter++;
      }else if(BoundingBoxContainsVertices(box4, vertex_x[i], vertex_y[i])){
          b4_v_counter++;
      }else if(BoundingBoxContainsVertices(box5, vertex_x[i], vertex_y[i])){
          b5_v_counter++;
      }else if(BoundingBoxContainsVertices(box6, vertex_x[i], vertex_y[i])){
          b6_v_counter++;
      }else if(BoundingBoxContainsVertices(box7, vertex_x[i], vertex_y[i])){
          b7_v_counter++;
      }
      else if(BoundingBoxContainsVertices(box8, vertex_x[i], vertex_y[i])){
          b8_v_counter++;
      }else if(BoundingBoxContainsVertices(box9, vertex_x[i], vertex_y[i])){
          b9_v_counter++;
      }*/

         if(BoundingBoxContainsVertices(TopLeftQuadrant, vertex_x[i], vertex_y[i])){
            b1_v_counter++;
         }
          if(BoundingBoxContainsVertices(TopRightQuadrant, vertex_x[i], vertex_y[i])){
             b2_v_counter++;
         }
          if(BoundingBoxContainsVertices(BottomLeftQuadrant, vertex_x[i], vertex_y[i])){
             b3_v_counter++;
         }
         if(BoundingBoxContainsVertices(BottomRightQuadrant, vertex_x[i], vertex_y[i])){
             b4_v_counter++;
         }


        }




for(int i=1;i<=edge_number;i++){
    /*  if(BoundingBoxContainsEdges(box1, edge_vertex1_x[i], edge_vertex1_y[i])){
         b1_e_counter++;
         b2_e_counter++;
         b4_e_counter++;
         b5_e_counter++;

      }
      else if(BoundingBoxContainsEdges(box2, edge_vertex1_x[i], edge_vertex1_y[i])){
          b1_e_counter++;
          b2_e_counter++;
           b3_e_counter++;
           b4_e_counter++;
          b5_e_counter++;
          b6_e_counter++;
      }else if(BoundingBoxContainsEdges(box3, edge_vertex1_x[i], edge_vertex1_y[i])){
          b2_e_counter++;
          b3_e_counter++;
          b5_e_counter++;
           b6_e_counter++;
      }else if(BoundingBoxContainsEdges(box4, edge_vertex1_x[i], edge_vertex1_y[i])){
          b2_e_counter++;
          b1_e_counter++;
          b4_e_counter++;
          b5_e_counter++;
           b7_e_counter++;
           b8_e_counter++;
      }else if(BoundingBoxContainsEdges(box5, edge_vertex1_x[i], edge_vertex1_y[i])){
          b2_e_counter++;
          b1_e_counter++;
           b3_e_counter++;
           b4_e_counter++;
          b5_e_counter++;
           b6_e_counter++;
            b7_e_counter++;
            b8_e_counter++;
            b9_e_counter++;
      }else if(BoundingBoxContainsEdges(box6, edge_vertex1_x[i], edge_vertex1_y[i])){
          b2_e_counter++;
           b3_e_counter++;
          b6_e_counter++;
          b5_e_counter++;
          b8_e_counter++;
          b9_e_counter++;
      }else if(BoundingBoxContainsEdges(box7, edge_vertex1_x[i], edge_vertex1_y[i])){
          b4_e_counter++;
          b7_e_counter++;
          b5_e_counter++;
          b8_e_counter++;
      }else if(BoundingBoxContainsEdges(box8, edge_vertex1_x[i], edge_vertex1_y[i])){
           b4_e_counter++;
            b6_e_counter++;
             b7_e_counter++;
           b8_e_counter++;
            b5_e_counter++;
            b9_e_counter++;
      }else if(BoundingBoxContainsEdges(box9, edge_vertex1_x[i], edge_vertex1_y[i])){
             b5_e_counter++;
            b6_e_counter++;
            b8_e_counter++;
           b9_e_counter++;

      }*/

    /*if(BoundingBoxContainsEdges(edgebox1, edge_vertex1_x[i], edge_vertex1_y[i])){
            b1_e_counter++;


         }
         if(BoundingBoxContainsEdges(edgebox2, edge_vertex1_x[i], edge_vertex1_y[i])){

             b2_e_counter++;

         }
         if(BoundingBoxContainsEdges(edgebox3, edge_vertex1_x[i], edge_vertex1_y[i])){

             b3_e_counter++;

         }
         if(BoundingBoxContainsEdges(edgebox4, edge_vertex1_x[i], edge_vertex1_y[i])){

             b4_e_counter++;

         }*/

}


//cout << "b3_e_counter="<< " " << b3_e_counter<< endl;

}

void Bubble_Optimiser::assign_boundary_box_data(){
//cout<<"get here3"<<endl;
    b1_v_counter=0;  b2_v_counter=0; b3_v_counter=0; b4_v_counter=0;
    b5_v_counter=0;  b6_v_counter=0; b7_v_counter=0; b8_v_counter=0;b9_v_counter=0;
b1_e_counter=0;b2_e_counter=0;b3_e_counter=0;b4_e_counter=0;
 b5_e_counter=0;  b6_e_counter=0; b7_e_counter=0; b8_e_counter=0; b9_e_counter=0;

double delta=0.4; //for width and height divided by 10.

//cout<<"get here1"<<endl;
    for(int i=1;i<=number;i++){
         if(BoundingBoxContainsVertices(box1, vertex_x[i], vertex_y[i])){
b1_v_counter++;

            b1_vertex_id[b1_v_counter]=vertex_id[i];
            b1_vertex_x[b1_v_counter]=vertex_x[i];
            b1_vertex_y[b1_v_counter]=vertex_y[i];
            b1_nx[b1_v_counter]=vertex_nx[i];
            b1_ny[b1_v_counter]=vertex_ny[i];
            b1_vert_b_id[b1_v_counter]=bubble_id[i];


                     //cout << "vertex_x[" << b1_v_counter <<"]="<< " " << b1_vertex_x[b1_v_counter] << endl;
          }
          else if(BoundingBoxContainsVertices(box2, vertex_x[i], vertex_y[i])){
              b2_v_counter++;
              b2_vertex_id[b2_v_counter]=vertex_id[i];
              b2_vertex_x[b2_v_counter]=vertex_x[i];
              b2_vertex_y[b2_v_counter]=vertex_y[i];
              b2_nx[b2_v_counter]=vertex_nx[i];
              b2_ny[b2_v_counter]=vertex_ny[i];
              b2_vert_b_id[b2_v_counter]=bubble_id[i];


          }else if(BoundingBoxContainsVertices(box3, vertex_x[i], vertex_y[i])){
              b3_v_counter++;
             b3_vertex_id[b3_v_counter]=vertex_id[i];
             b3_vertex_x[b3_v_counter]=vertex_x[i];
             b3_vertex_y[b3_v_counter]=vertex_y[i];
             b3_nx[b3_v_counter]=vertex_nx[i];
             b3_ny[b3_v_counter]=vertex_ny[i];
             b3_vert_b_id[b3_v_counter]=bubble_id[i];

          }else if(BoundingBoxContainsVertices(box4, vertex_x[i], vertex_y[i])){
             b4_v_counter++;
             b4_vertex_id[b4_v_counter]=vertex_id[i];
             b4_vertex_x[b4_v_counter]=vertex_x[i];
             b4_vertex_y[b4_v_counter]=vertex_y[i];
             b4_nx[b4_v_counter]=vertex_nx[i];
             b4_ny[b4_v_counter]=vertex_ny[i];
             b4_vert_b_id[b4_v_counter]=bubble_id[i];

          }else if(BoundingBoxContainsVertices(box5, vertex_x[i], vertex_y[i])){
              b5_v_counter++;
              b5_vertex_id[b5_v_counter]=vertex_id[i];
              b5_vertex_x[b5_v_counter]=vertex_x[i];
              b5_vertex_y[b5_v_counter]=vertex_y[i];
              b5_nx[b5_v_counter]=vertex_nx[i];
              b5_ny[b5_v_counter]=vertex_ny[i];
              b5_vert_b_id[b5_v_counter]=bubble_id[i];


          }else if(BoundingBoxContainsVertices(box6, vertex_x[i], vertex_y[i])){
              b6_v_counter++;
             b6_vertex_id[b6_v_counter]=vertex_id[i];
             b6_vertex_x[b6_v_counter]=vertex_x[i];
             b6_vertex_y[b6_v_counter]=vertex_y[i];
             b6_nx[b6_v_counter]=vertex_nx[i];
             b6_ny[b6_v_counter]=vertex_ny[i];
             b6_vert_b_id[b6_v_counter]=bubble_id[i];

          }else if(BoundingBoxContainsVertices(box7, vertex_x[i], vertex_y[i])){
             b7_v_counter++;
             b7_vertex_id[b7_v_counter]=vertex_id[i];
             b7_vertex_x[b7_v_counter]=vertex_x[i];
             b7_vertex_y[b7_v_counter]=vertex_y[i];
             b7_nx[b7_v_counter]=vertex_nx[i];
             b7_ny[b7_v_counter]=vertex_ny[i];
             b7_vert_b_id[b7_v_counter]=bubble_id[i];

          }else if(BoundingBoxContainsVertices(box8, vertex_x[i], vertex_y[i])){
                b8_v_counter++;
                 b8_vertex_id[b8_v_counter]=vertex_id[i];
                 b8_vertex_x[b8_v_counter]=vertex_x[i];
                 b8_vertex_y[b8_v_counter]=vertex_y[i];
                 b8_nx[b8_v_counter]=vertex_nx[i];
                 b8_ny[b8_v_counter]=vertex_ny[i];
                 b8_vert_b_id[b8_v_counter]=bubble_id[i];

              }else if(BoundingBoxContainsVertices(box9, vertex_x[i], vertex_y[i])){
                 b9_v_counter++;
                 b9_vertex_id[b9_v_counter]=vertex_id[i];
                 b9_vertex_x[b9_v_counter]=vertex_x[i];
                 b9_vertex_y[b9_v_counter]=vertex_y[i];
                 b9_nx[b9_v_counter]=vertex_nx[i];
                 b9_ny[b9_v_counter]=vertex_ny[i];
                 b9_vert_b_id[b9_v_counter]=bubble_id[i];

              }
        /*if(BoundingBoxContainsVertices(TopLeftQuadrant, vertex_x[i], vertex_y[i])){
        b1_v_counter++;

                    b1_vertex_id[b1_v_counter]=vertex_id[i];
                    b1_vertex_x[b1_v_counter]=vertex_x[i];
                    b1_vertex_y[b1_v_counter]=vertex_y[i];
                    b1_nx[b1_v_counter]=vertex_nx[i];
                    b1_ny[b1_v_counter]=vertex_ny[i];
                    b1_vert_b_id[b1_v_counter]=bubble_id[i];


                             //cout << "vertex_x[" << b1_v_counter <<"]="<< " " << b1_vertex_x[b1_v_counter] << endl;
                  }
                 if(BoundingBoxContainsVertices(TopRightQuadrant, vertex_x[i], vertex_y[i])){
                      b2_v_counter++;
                      b2_vertex_id[b2_v_counter]=vertex_id[i];
                      b2_vertex_x[b2_v_counter]=vertex_x[i];
                      b2_vertex_y[b2_v_counter]=vertex_y[i];
                      b2_nx[b2_v_counter]=vertex_nx[i];
                      b2_ny[b2_v_counter]=vertex_ny[i];
                      b2_vert_b_id[b2_v_counter]=bubble_id[i];


                  }
                 if(BoundingBoxContainsVertices(BottomLeftQuadrant, vertex_x[i], vertex_y[i])){
                      b3_v_counter++;
                     b3_vertex_id[b3_v_counter]=vertex_id[i];
                     b3_vertex_x[b3_v_counter]=vertex_x[i];
                     b3_vertex_y[b3_v_counter]=vertex_y[i];
                     b3_nx[b3_v_counter]=vertex_nx[i];
                     b3_ny[b3_v_counter]=vertex_ny[i];
                     b3_vert_b_id[b3_v_counter]=bubble_id[i];

                  }
                 if(BoundingBoxContainsVertices(BottomRightQuadrant, vertex_x[i], vertex_y[i])){
                     b4_v_counter++;
                     b4_vertex_id[b4_v_counter]=vertex_id[i];
                     b4_vertex_x[b4_v_counter]=vertex_x[i];
                     b4_vertex_y[b4_v_counter]=vertex_y[i];
                     b4_nx[b4_v_counter]=vertex_nx[i];
                     b4_ny[b4_v_counter]=vertex_ny[i];
                     b4_vert_b_id[b4_v_counter]=bubble_id[i];

                  }*/


    }
//cout<<"get here4"<<endl;
    for(int i=1;i<=edge_number;i++){
          /*if(BoundingBoxContainsEdges(box1, edge_vertex1_x[i], edge_vertex1_y[i])){
             b1_e_counter++; b2_e_counter++; b4_e_counter++;b5_e_counter++;
            b1_evertex1_x[b1_e_counter]=edge_vertex1_x[i];
            b1_evertex1_y[b1_e_counter]=edge_vertex1_y[i];
            b1_eex[b1_e_counter]=ee_x[i];
            b1_eey[b1_e_counter]=ee_y[i];
            b1_edge_b_id[b1_e_counter]=edge_bubble_id[i];


            b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
            b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
            b2_eex[b2_e_counter]=ee_x[i];
            b2_eey[b2_e_counter]=ee_y[i];
            b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];


              b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
              b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
              b4_eex[b4_e_counter]=ee_x[i];
              b4_eey[b4_e_counter]=ee_y[i];
              b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];



            b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
            b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
            b5_eex[b5_e_counter]=ee_x[i];
            b5_eey[b5_e_counter]=ee_y[i];
            b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];

                     //cout << "vertex_x[" << b1_v_counter <<"]="<< " " << b1_vertex_x[b1_v_counter] << endl;
          }
         if(BoundingBoxContainsEdges(box2, edge_vertex1_x[i], edge_vertex1_y[i])){
              b1_e_counter++;
              b2_e_counter++;
              b3_e_counter++;
              b4_e_counter++;
              b5_e_counter++;
             b1_evertex1_x[b1_e_counter]=edge_vertex1_x[i];
             b1_evertex1_y[b1_e_counter]=edge_vertex1_y[i];
             b1_eex[b1_e_counter]=ee_x[i];
             b1_eey[b1_e_counter]=ee_y[i];
             b1_edge_b_id[b1_e_counter]=edge_bubble_id[i];


               b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
               b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
               b2_eex[b2_e_counter]=ee_x[i];
               b2_eey[b2_e_counter]=ee_y[i];
               b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];


                b3_evertex1_x[b3_e_counter]=edge_vertex1_x[i];
                b3_evertex1_y[b3_e_counter]=edge_vertex1_y[i];
                b3_eex[b3_e_counter]=ee_x[i];
                b3_eey[b3_e_counter]=ee_y[i];
                b3_edge_b_id[b3_e_counter]=edge_bubble_id[i];


                  b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
                  b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
                  b4_eex[b4_e_counter]=ee_x[i];
                  b4_eey[b4_e_counter]=ee_y[i];
                  b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];



               b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
               b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
               b5_eex[b5_e_counter]=ee_x[i];
               b5_eey[b5_e_counter]=ee_y[i];
               b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];

               b6_e_counter++;
                b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
                b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
                b6_eex[b6_e_counter]=ee_x[i];
                b6_eey[b6_e_counter]=ee_y[i];
                b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];


          }
         if(BoundingBoxContainsEdges(box3, edge_vertex1_x[i], edge_vertex1_y[i])){
              b2_e_counter++;
              b3_e_counter++;
               b5_e_counter++;
               b6_e_counter++;
              b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
              b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
              b2_eex[b2_e_counter]=ee_x[i];
              b2_eey[b2_e_counter]=ee_y[i];
              b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];


              b3_evertex1_x[b3_e_counter]=edge_vertex1_x[i];
              b3_evertex1_y[b3_e_counter]=edge_vertex1_y[i];
              b3_eex[b3_e_counter]=ee_x[i];
              b3_eey[b3_e_counter]=ee_y[i];
              b3_edge_b_id[b3_e_counter]=edge_bubble_id[i];


              b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
              b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
              b5_eex[b5_e_counter]=ee_x[i];
              b5_eey[b5_e_counter]=ee_y[i];
              b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


               b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
               b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
               b6_eex[b6_e_counter]=ee_x[i];
               b6_eey[b6_e_counter]=ee_y[i];
               b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];


          }
         if(BoundingBoxContainsEdges(box4, edge_vertex1_x[i], edge_vertex1_y[i])){
              b1_e_counter++;
              b2_e_counter++;
              b4_e_counter++;
              b5_e_counter++;
              b7_e_counter++;
              b8_e_counter++;
             b1_evertex1_x[b1_e_counter]=edge_vertex1_x[i];
             b1_evertex1_y[b1_e_counter]=edge_vertex1_y[i];
             b1_eex[b1_e_counter]=ee_x[i];
             b1_eey[b1_e_counter]=ee_y[i];
             b1_edge_b_id[b1_e_counter]=edge_bubble_id[i];


             b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
             b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
             b2_eex[b2_e_counter]=ee_x[i];
             b2_eey[b2_e_counter]=ee_y[i];
             b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];


              b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
              b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
              b4_eex[b4_e_counter]=ee_x[i];
              b4_eey[b4_e_counter]=ee_y[i];
              b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];


              b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
              b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
              b5_eex[b5_e_counter]=ee_x[i];
              b5_eey[b5_e_counter]=ee_y[i];
              b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


                b7_evertex1_x[b7_e_counter]=edge_vertex1_x[i];
                b7_evertex1_y[b7_e_counter]=edge_vertex1_y[i];
                b7_eex[b7_e_counter]=ee_x[i];
                b7_eey[b7_e_counter]=ee_y[i];
                b7_edge_b_id[b7_e_counter]=edge_bubble_id[i];


                 b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
                 b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
                 b8_eex[b8_e_counter]=ee_x[i];
                 b8_eey[b8_e_counter]=ee_y[i];
                 b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];


          }
          if(BoundingBoxContainsEdges(box5, edge_vertex1_x[i], edge_vertex1_y[i])){
              b1_e_counter++;
              b2_e_counter++;
               b3_e_counter++;
               b4_e_counter++;
               b5_e_counter++;
               b6_e_counter++;
               b7_e_counter++;
               b8_e_counter++;
               b9_e_counter++;
             b1_evertex1_x[b1_e_counter]=edge_vertex1_x[i];
             b1_evertex1_y[b1_e_counter]=edge_vertex1_y[i];
             b1_eex[b1_e_counter]=ee_x[i];
             b1_eey[b1_e_counter]=ee_y[i];
             b1_edge_b_id[b1_e_counter]=edge_bubble_id[i];


             b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
             b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
             b2_eex[b2_e_counter]=ee_x[i];
             b2_eey[b2_e_counter]=ee_y[i];
             b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];


              b3_evertex1_x[b3_e_counter]=edge_vertex1_x[i];
              b3_evertex1_y[b3_e_counter]=edge_vertex1_y[i];
              b3_eex[b3_e_counter]=ee_x[i];
              b3_eey[b3_e_counter]=ee_y[i];
              b3_edge_b_id[b3_e_counter]=edge_bubble_id[i];


                b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
                b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
                b4_eex[b4_e_counter]=ee_x[i];
                b4_eey[b4_e_counter]=ee_y[i];
                b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];



               b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
               b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
               b5_eex[b5_e_counter]=ee_x[i];
               b5_eey[b5_e_counter]=ee_y[i];
               b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


                b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
                b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
                b6_eex[b6_e_counter]=ee_x[i];
                b6_eey[b6_e_counter]=ee_y[i];
                b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];


                  b7_evertex1_x[b7_e_counter]=edge_vertex1_x[i];
                  b7_evertex1_y[b7_e_counter]=edge_vertex1_y[i];
                  b7_eex[b7_e_counter]=ee_x[i];
                  b7_eey[b7_e_counter]=ee_y[i];
                  b7_edge_b_id[b7_e_counter]=edge_bubble_id[i];


                   b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
                   b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
                   b8_eex[b8_e_counter]=ee_x[i];
                   b8_eey[b8_e_counter]=ee_y[i];
                   b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];


                     b9_evertex1_x[b9_e_counter]=edge_vertex1_x[i];
                     b9_evertex1_y[b9_e_counter]=edge_vertex1_y[i];
                     b9_eex[b9_e_counter]=ee_x[i];
                     b9_eey[b9_e_counter]=ee_y[i];
                     b9_edge_b_id[b9_e_counter]=edge_bubble_id[i];


          }
          if(BoundingBoxContainsEdges(box6, edge_vertex1_x[i], edge_vertex1_y[i])){
              b2_e_counter++;
              b3_e_counter++;
              b6_e_counter++;
              b5_e_counter++;
              b8_e_counter++;
               b9_e_counter++;

              b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
              b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
              b2_eex[b2_e_counter]=ee_x[i];
              b2_eey[b2_e_counter]=ee_y[i];
              b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];


               b3_evertex1_x[b3_e_counter]=edge_vertex1_x[i];
               b3_evertex1_y[b3_e_counter]=edge_vertex1_y[i];
               b3_eex[b3_e_counter]=ee_x[i];
               b3_eey[b3_e_counter]=ee_y[i];
               b3_edge_b_id[b3_e_counter]=edge_bubble_id[i];


              b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
              b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
              b6_eex[b6_e_counter]=ee_x[i];
              b6_eey[b6_e_counter]=ee_y[i];
              b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];


              b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
              b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
              b5_eex[b5_e_counter]=ee_x[i];
              b5_eey[b5_e_counter]=ee_y[i];
              b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


               b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
               b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
               b8_eex[b8_e_counter]=ee_x[i];
               b8_eey[b8_e_counter]=ee_y[i];
               b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];


                 b9_evertex1_x[b9_e_counter]=edge_vertex1_x[i];
                 b9_evertex1_y[b9_e_counter]=edge_vertex1_y[i];
                 b9_eex[b9_e_counter]=ee_x[i];
                 b9_eey[b9_e_counter]=ee_y[i];
                 b9_edge_b_id[b9_e_counter]=edge_bubble_id[i];

          }
          if(BoundingBoxContainsEdges(box7, edge_vertex1_x[i], edge_vertex1_y[i])){
            b7_e_counter++;
            b4_e_counter++;
             b5_e_counter++;
             b8_e_counter++;
              b7_evertex1_x[b7_e_counter]=edge_vertex1_x[i];
              b7_evertex1_y[b7_e_counter]=edge_vertex1_y[i];
              b7_eex[b7_e_counter]=ee_x[i];
              b7_eey[b7_e_counter]=ee_y[i];
              b7_edge_b_id[b7_e_counter]=edge_bubble_id[i];


                b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
                b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
                b4_eex[b4_e_counter]=ee_x[i];
                b4_eey[b4_e_counter]=ee_y[i];
                b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];



              b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
              b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
              b5_eex[b5_e_counter]=ee_x[i];
              b5_eey[b5_e_counter]=ee_y[i];
              b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


               b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
               b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
               b8_eex[b8_e_counter]=ee_x[i];
               b8_eey[b8_e_counter]=ee_y[i];
               b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];

          }
           if(BoundingBoxContainsEdges(box8, edge_vertex1_x[i], edge_vertex1_y[i])){

                        b6_e_counter++;
                        b4_e_counter++;
                        b5_e_counter++;
                        b7_e_counter++;
                        b8_e_counter++;
                        b9_e_counter++;

                         b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
                         b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
                         b6_eex[b6_e_counter]=ee_x[i];
                         b6_eey[b6_e_counter]=ee_y[i];
                         b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];



                          b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
                          b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
                          b4_eex[b4_e_counter]=ee_x[i];
                          b4_eey[b4_e_counter]=ee_y[i];
                          b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];



                        b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
                        b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
                        b5_eex[b5_e_counter]=ee_x[i];
                        b5_eey[b5_e_counter]=ee_y[i];
                        b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


                          b7_evertex1_x[b7_e_counter]=edge_vertex1_x[i];
                          b7_evertex1_y[b7_e_counter]=edge_vertex1_y[i];
                          b7_eex[b7_e_counter]=ee_x[i];
                          b7_eey[b7_e_counter]=ee_y[i];
                          b7_edge_b_id[b7_e_counter]=edge_bubble_id[i];


                         b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
                         b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
                         b8_eex[b8_e_counter]=ee_x[i];
                         b8_eey[b8_e_counter]=ee_y[i];
                         b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];


                           b9_evertex1_x[b9_e_counter]=edge_vertex1_x[i];
                           b9_evertex1_y[b9_e_counter]=edge_vertex1_y[i];
                           b9_eex[b9_e_counter]=ee_x[i];
                           b9_eey[b9_e_counter]=ee_y[i];
                           b9_edge_b_id[b9_e_counter]=edge_bubble_id[i];

         }
           if(BoundingBoxContainsEdges(box9, edge_vertex1_x[i], edge_vertex1_y[i])){

                        b5_e_counter++;
                        b6_e_counter++;
                        b8_e_counter++;
                        b9_e_counter++;
                        b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
                        b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
                        b5_eex[b5_e_counter]=ee_x[i];
                        b5_eey[b5_e_counter]=ee_y[i];
                        b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];


                         b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
                         b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
                         b6_eex[b6_e_counter]=ee_x[i];
                         b6_eey[b6_e_counter]=ee_y[i];
                         b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];


                          b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
                          b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
                          b8_eex[b8_e_counter]=ee_x[i];
                          b8_eey[b8_e_counter]=ee_y[i];
                          b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];


                           b9_evertex1_x[b9_e_counter]=edge_vertex1_x[i];
                           b9_evertex1_y[b9_e_counter]=edge_vertex1_y[i];
                           b9_eex[b9_e_counter]=ee_x[i];
                           b9_eey[b9_e_counter]=ee_y[i];
                           b9_edge_b_id[b9_e_counter]=edge_bubble_id[i];

        }*/

        /*if(BoundingBoxContainsEdges(edgebox1, edge_vertex1_x[i], edge_vertex1_y[i])){
     // if(-2.0 <= edge_vertex1_x[i] && edge_vertex1_x[i] <=1.999 && 2.0 >=edge_vertex1_y[i] && edge_vertex1_y[i]>=-2.0){

           b1_e_counter++;
          b1_evertex1_x[b1_e_counter]=edge_vertex1_x[i];
          b1_evertex1_y[b1_e_counter]=edge_vertex1_y[i];
          b1_eex[b1_e_counter]=ee_x[i];
          b1_eey[b1_e_counter]=ee_y[i];
          b1_edge_b_id[b1_e_counter]=edge_bubble_id[i];

                   //cout << "vertex_x[" << b1_v_counter <<"]="<< " " << b1_vertex_x[b1_v_counter] << endl;
        }
      if(BoundingBoxContainsEdges(edgebox2, edge_vertex1_x[i], edge_vertex1_y[i])){
             b2_e_counter++;
             b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
             b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
             b2_eex[b2_e_counter]=ee_x[i];
             b2_eey[b2_e_counter]=ee_y[i];
             b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];

        }
     if(BoundingBoxContainsEdges(edgebox3, edge_vertex1_x[i], edge_vertex1_y[i])){
          b3_e_counter++;
            b3_evertex1_x[b3_e_counter]=edge_vertex1_x[i];
            b3_evertex1_y[b3_e_counter]=edge_vertex1_y[i];
            b3_eex[b3_e_counter]=ee_x[i];
            b3_eey[b3_e_counter]=ee_y[i];
            b3_edge_b_id[b3_e_counter]=edge_bubble_id[i];

        }
      if(BoundingBoxContainsEdges(edgebox4, edge_vertex1_x[i], edge_vertex1_y[i])){
          b4_e_counter++;
            b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
            b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
            b4_eex[b4_e_counter]=ee_x[i];
            b4_eey[b4_e_counter]=ee_y[i];
            b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];

        }*/

             if(BoundingBoxContainsEdges(edge_box1, edge_vertex1_x[i], edge_vertex1_y[i])){
             // if(-2.0 <= edge_vertex1_x[i] && edge_vertex1_x[i] <=1.999 && 2.0 >=edge_vertex1_y[i] && edge_vertex1_y[i]>=-2.0){

                   b1_e_counter++;
                  b1_evertex1_x[b1_e_counter]=edge_vertex1_x[i];
                  b1_evertex1_y[b1_e_counter]=edge_vertex1_y[i];
                  b1_eex[b1_e_counter]=ee_x[i];
                  b1_eey[b1_e_counter]=ee_y[i];
                  b1_edge_b_id[b1_e_counter]=edge_bubble_id[i];

                           //cout << "vertex_x[" << b1_v_counter <<"]="<< " " << b1_vertex_x[b1_v_counter] << endl;
                }
              if(BoundingBoxContainsEdges(edge_box2, edge_vertex1_x[i], edge_vertex1_y[i])){
                     b2_e_counter++;
                     b2_evertex1_x[b2_e_counter]=edge_vertex1_x[i];
                     b2_evertex1_y[b2_e_counter]=edge_vertex1_y[i];
                     b2_eex[b2_e_counter]=ee_x[i];
                     b2_eey[b2_e_counter]=ee_y[i];
                     b2_edge_b_id[b2_e_counter]=edge_bubble_id[i];

                }
             if(BoundingBoxContainsEdges(edge_box3, edge_vertex1_x[i], edge_vertex1_y[i])){
                  b3_e_counter++;
                    b3_evertex1_x[b3_e_counter]=edge_vertex1_x[i];
                    b3_evertex1_y[b3_e_counter]=edge_vertex1_y[i];
                    b3_eex[b3_e_counter]=ee_x[i];
                    b3_eey[b3_e_counter]=ee_y[i];
                    b3_edge_b_id[b3_e_counter]=edge_bubble_id[i];

                }
              if(BoundingBoxContainsEdges(edge_box4, edge_vertex1_x[i], edge_vertex1_y[i])){
                  b4_e_counter++;
                    b4_evertex1_x[b4_e_counter]=edge_vertex1_x[i];
                    b4_evertex1_y[b4_e_counter]=edge_vertex1_y[i];
                    b4_eex[b4_e_counter]=ee_x[i];
                    b4_eey[b4_e_counter]=ee_y[i];
                    b4_edge_b_id[b4_e_counter]=edge_bubble_id[i];

                }

              if(BoundingBoxContainsEdges(edge_box5, edge_vertex1_x[i], edge_vertex1_y[i])){
              // if(-2.0 <= edge_vertex1_x[i] && edge_vertex1_x[i] <=1.999 && 2.0 >=edge_vertex1_y[i] && edge_vertex1_y[i]>=-2.0){

                    b5_e_counter++;
                   b5_evertex1_x[b5_e_counter]=edge_vertex1_x[i];
                   b5_evertex1_y[b5_e_counter]=edge_vertex1_y[i];
                   b5_eex[b5_e_counter]=ee_x[i];
                   b5_eey[b5_e_counter]=ee_y[i];
                   b5_edge_b_id[b5_e_counter]=edge_bubble_id[i];

                            //cout << "vertex_x[" << b1_v_counter <<"]="<< " " << b1_vertex_x[b1_v_counter] << endl;
                 }
               if(BoundingBoxContainsEdges(edge_box6, edge_vertex1_x[i], edge_vertex1_y[i])){
                      b6_e_counter++;
                      b6_evertex1_x[b6_e_counter]=edge_vertex1_x[i];
                      b6_evertex1_y[b6_e_counter]=edge_vertex1_y[i];
                      b6_eex[b6_e_counter]=ee_x[i];
                      b6_eey[b6_e_counter]=ee_y[i];
                      b6_edge_b_id[b6_e_counter]=edge_bubble_id[i];

                 }
              if(BoundingBoxContainsEdges(edge_box7, edge_vertex1_x[i], edge_vertex1_y[i])){
                   b7_e_counter++;
                     b7_evertex1_x[b7_e_counter]=edge_vertex1_x[i];
                     b7_evertex1_y[b7_e_counter]=edge_vertex1_y[i];
                     b7_eex[b7_e_counter]=ee_x[i];
                     b7_eey[b7_e_counter]=ee_y[i];
                     b7_edge_b_id[b7_e_counter]=edge_bubble_id[i];

                 }
               if(BoundingBoxContainsEdges(edge_box8, edge_vertex1_x[i], edge_vertex1_y[i])){
                   b8_e_counter++;
                     b8_evertex1_x[b8_e_counter]=edge_vertex1_x[i];
                     b8_evertex1_y[b8_e_counter]=edge_vertex1_y[i];
                     b8_eex[b8_e_counter]=ee_x[i];
                     b8_eey[b8_e_counter]=ee_y[i];
                     b8_edge_b_id[b8_e_counter]=edge_bubble_id[i];

                 }

               if(BoundingBoxContainsEdges(edge_box9, edge_vertex1_x[i], edge_vertex1_y[i])){
                   b9_e_counter++;
                     b9_evertex1_x[b9_e_counter]=edge_vertex1_x[i];
                     b9_evertex1_y[b9_e_counter]=edge_vertex1_y[i];
                     b9_eex[b9_e_counter]=ee_x[i];
                     b9_eey[b9_e_counter]=ee_y[i];
                     b9_edge_b_id[b9_e_counter]=edge_bubble_id[i];

                 }




    }

   // cout << "b3_e_counter="<< " " << b3_e_counter<< endl;
//cout<<"get here5"<<endl;

}



double* Bubble_Optimiser::sort(double*array,int size){
    double temp_value=0.0;

    for(int i=0;i<size;i++){
        for(int j=0;j<size-1;j++){
            if(array[j]>array[j+1]){
                temp_value=array[j];
                array[j]=array[j+1];
                array[j+1]=temp_value;
            }
        }
    }

    //bounding_values[0]=array[1];
    //bounding_values[1]=array[size];

    return array;


}




Bubble_Optimiser::~Bubble_Optimiser(){
    Vertex_id.clear(); Vertex_x.clear(); Vertex_y.clear();Vertex_bub_id.clear();
    Vertex_nx.clear();Vertex_ny.clear();
    Edge_id.clear();
    Evertex1_id.clear();
    Evertex2_id.clear();
    Evertex1_x.clear();
    Evertex1_y.clear();
    Evertex2_x.clear();
    Evertex2_y.clear();
    Eex.clear();
    Eey.clear();
    Edge_bub_id.clear();

    min_dists.assign(number,0.0);


delete [] vertex_id; delete [] vertex_x;delete [] vertex_y; delete [] bubble_id;
delete [] vertex_nx; delete [] vertex_ny; delete [] vertex_id;
    delete [] edge_id;
        delete [] edge_vertex1_id;
        delete [] edge_vertex2_id;
        delete [] edge_vertex1_x;
        delete [] edge_vertex1_y;
        delete [] edge_vertex2_x;
        delete [] edge_vertex2_y;
        delete [] ee_x;
        delete [] ee_y;
        delete [] edge_bubble_id;
    delete [] min_dist; delete [] b1_min_dist; delete [] b2_min_dist; delete [] b3_min_dist; delete [] b4_min_dist;
    delete [] b5_min_dist; delete [] b6_min_dist; delete [] b7_min_dist; delete [] b8_min_dist; delete [] b9_min_dist;

   delete[] b1_vertex_id; delete [] b2_vertex_id;  delete [] b3_vertex_id;delete [] b4_vertex_id; delete [] out_vertex_id ;
   delete [] b5_vertex_id; delete [] b6_vertex_id;  delete [] b7_vertex_id;delete [] b8_vertex_id; delete [] b9_vertex_id;

   delete[] b1_vertex_x; delete [] b2_vertex_x;  delete [] b3_vertex_x;delete [] b4_vertex_x; delete [] out_vertex_x;
    delete[] b5_vertex_x; delete [] b6_vertex_x;  delete [] b7_vertex_x;delete [] b8_vertex_x; delete [] b9_vertex_x;

       delete [] b1_vertex_y;delete [] b2_vertex_y;  delete []b3_vertex_y;delete [] b4_vertex_y; delete [] out_vertex_y;  
    delete [] b5_vertex_y;delete [] b6_vertex_y;  delete []b7_vertex_y;delete [] b8_vertex_y; delete [] b9_vertex_y;

       delete[] b1_nx;delete [] b2_nx;  delete [] b3_nx;delete [] b4_nx; delete [] out_nx;
    delete[] b5_nx;delete [] b6_nx;  delete [] b7_nx;delete [] b8_nx; delete [] b9_nx;

    delete [] b1_ny;delete [] b2_ny;  delete []b3_ny;delete [] b4_ny; delete [] out_ny;
       delete [] b5_ny;delete [] b6_ny;  delete []b7_ny;delete [] b8_ny; delete [] b9_ny;

    delete [] b1_vert_b_id; delete [] b2_vert_b_id; delete [] b3_vert_b_id; delete [] b4_vert_b_id;
    delete [] b5_vert_b_id; delete [] b6_vert_b_id; delete [] b7_vert_b_id; delete [] b8_vert_b_id; delete [] b9_vert_b_id; delete [] out_vert_b_id;


       delete[] b1_evertex1_x;delete [] b2_evertex1_x;  delete [] b3_evertex1_x;delete [] b4_evertex1_x; delete [] out_evertex1_x;
       delete[] b5_evertex1_x;delete [] b6_evertex1_x;  delete [] b7_evertex1_x;delete [] b8_evertex1_x; delete [] b9_evertex1_x;

       delete [] b1_evertex1_y;delete [] b2_evertex1_y;  delete []b3_evertex1_y;delete [] b4_evertex1_y; delete [] out_evertex1_y;
       delete [] b5_evertex1_y;delete [] b6_evertex1_y;  delete []b7_evertex1_y;delete [] b8_evertex1_y; delete [] b9_evertex1_y;

      delete[] b1_eex;delete [] b2_eex;  delete [] b3_eex;delete [] b4_eex; delete [] out_eex;
     delete[] b5_eex;delete [] b6_eex;  delete [] b7_eex;delete [] b8_eex; delete [] b9_eex;

      delete[] b1_eey;delete [] b2_eey;  delete [] b3_eey;delete [] b4_eey; delete [] out_eey;
      delete[] b5_eey;delete [] b6_eey;  delete [] b7_eey;delete [] b8_eey; delete [] b9_eey;

      delete[] b1_edge_b_id;delete [] b2_edge_b_id;  delete [] b3_edge_b_id;delete [] b4_edge_b_id; delete [] b5_edge_b_id;
      delete[] b6_edge_b_id;delete [] b7_edge_b_id;  delete [] b8_edge_b_id;delete [] b9_edge_b_id;

/*for(int i=0;i<number;i++){
delete [] vertex_info[i];
}
delete [] vertex_info;
for(int i=0;i<number;i++){
delete [] edge_info[i];
}
delete [] edge_info;*/


}


