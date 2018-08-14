#ifndef MATRIX_ALGORITHM_H
#define MATRIX_ALGORITHM_H

//#ifdef _GRAPHICS_
template <typename T>
void convert_rot_matrix_for_openGL( float *m, T *p, const vector <T> &r);
//#endif

template <typename T>
void getRMatrixFrom_X_AxisAndAngle (vector <T> &R, T alpha );

template <typename T>
void getRMatrixFrom_Y_AxisAndAngle (vector <T> &R, T alpha );

template <typename T>
void getRMatrixFrom_Z_AxisAndAngle (vector <T> &R, T alpha );

template <typename T>
void set_R3_identity_matrix( vector <T> &I);

template <typename T>
void set_R4_identity_matrix( vector <T> &I);

template <typename T>
void R4Multiply           ( vector <T> &res, vector <T> m1, vector <T> m2 );

template <typename T>
void R3Multiply           ( vector <T> &res, vector <T> &m1, vector <T> &m2 );

template <typename T>
void R4SetIdentity        ( vector <T> &rot, const T *pos );

template <typename T>
void R4Vector4Multiply    ( T *res, const vector <T> m1, T *target );

template <typename T>
void R3Vector3Multiply    ( T *res, const vector <T> m1, T *target );

template <typename T>
void get_R4transpose      ( vector <T> &transp, vector <T> m1 );

template <typename T>
void R3toR4( vector <T> &R4, const vector <T> rot, const T *pos );

template <typename T>
void R4toR3andPOS(vector <T> &R3, T *pos, vector <T> R4);

template <typename T>
void Rotate_on_X_Axis( T *res, const T *pos, T theta );

template <typename T>
void Rotate_on_Y_Axis( T *res, const T *pos, T theta );

template <typename T>
void Rotate_on_Z_Axis( T *res, const T *pos, T theta );

/* ----------------------------------------------------------------------- */
//#ifdef _GRAPHICS_
template <typename T>
void convert_rot_matrix_for_openGL( float *m, T *p, const vector <T> &r){
  m[ 0] = r[0];
  m[ 1] = r[4];
  m[ 2] = r[8];
  m[ 3] = 0;
  m[ 4] = r[1];
  m[ 5] = r[5];
  m[ 6] = r[9];
  m[ 7] = 0;
  m[ 8] = r[2];
  m[ 9] = r[6];
  m[10] = r[10];
  m[11] = 0;
  m[12] = p[0];
  m[13] = p[1];
  m[14] = p[2];
  m[15] = 1;
}
//#endif
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void getRMatrixFrom_X_AxisAndAngle (vector <T> &R, T alpha ){
  R[0] = 1.0;
  R[1] = 0.0;
  R[2] = 0.0;  
  R[3] = 0.0;

  R[4] = 0.0;
  R[5] = cos(alpha);
  R[6] = -sin(alpha);
  R[7] = 0.0;

  R[8]  = 0.0;
  R[9]  = sin(alpha);
  R[10] = cos(alpha);
  R[11] = 0.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void getRMatrixFrom_Y_AxisAndAngle (vector <T> &R, T alpha ){
  R[0] = cos(alpha);
  R[1] = 0.0;
  R[2] = sin(alpha);
  R[3] = 0.0;

  R[4] = 0.0;
  R[5] = 1.0;
  R[6] = 0.0;
  R[8] = 0.0;
  
  R[8]  = -sin(alpha);
  R[9] = 0.0;
  R[10] = cos(alpha);
  R[11] = 0.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void getRMatrixFrom_Z_AxisAndAngle (vector <T> &R, T alpha ){
  R[0] = cos(alpha);
  R[1] = -sin(alpha);
  R[2] = 0.0;
  R[3] = 0.0;

  R[4] = sin(alpha);
  R[5] = cos(alpha);
  R[6] = 0.0;
  R[7] = 0.0;
  
  R[8]  = 0.0;
  R[9]  = 0.0;
  R[10] = 1.0;
  R[11] = 0.0;

}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void set_R3_identity_matrix( vector <T> &I){
  I[0] = 1.0;
  I[1] = 0.0;
  I[2] = 0.0;
  I[3] = 0.0;

  I[4] = 0.0;
  I[5] = 1.0;
  I[6] = 0.0;
  I[7] = 0.0;

  I[8] = 0.0;
  I[9] = 0.0;
  I[10] = 1.0;
  I[11] = 0.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void set_R4_identity_matrix( vector <T> &I){
  I[0] = 1.0;
  I[1] = 0.0;
  I[2] = 0.0;
  I[3] = 0.0;

  I[4] = 0.0;
  I[5] = 1.0;
  I[6] = 0.0;
  I[7] = 0.0;

  I[8]  = 0.0;
  I[9]  = 0.0;
  I[10] = 1.0;
  I[11] = 0.0;
  
  I[12] = 0.0;
  I[13] = 0.0;
  I[14] = 0.0;
  I[15] = 1.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R4Multiply( vector <T> &res, vector <T> m1, vector <T> m2 ){
  int C0=0.0, C1=0.0, C2=0.0;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      res[C0] = 0.0;
      C1 = i*4;
      for(int k=0;k<4;k++){
	C2=(4*k)+j;
	res[C0] += m1[C1]*m2[C2];
	//cerr << " " << C0 << " = row " << C1 << " times coloun " << C2 << endl;
	//getchar();
	C1++;
      }
      //cerr << " res["<<C0<<"] = "<< res[C0];
      C0++;
    }
    //cerr << endl;
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R4Vector4Multiply( T *res, const vector <T> m1, T *pos ){
  int C0=0.0, C1=0.0, C2=0.0;
  for(int i=0; i<4; i++){
    res[C0] = 0.0;
    C1 = i*4;
    for(int k=0;k<4;k++){
      res[C0] += m1[C1]*pos[k];
      C1++;
    }
    //cerr << " res["<<C0<<"] = "<< res[C0];
    C0++;
    //cerr << endl;
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R3Multiply( vector <T> &res, vector <T> &m1, vector <T> &m2 ){
  int C0=0.0, C1=0.0, C2=0.0;
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      res[C0] = 0.0;
      C1 = i*4;
      for(int k=0;k<3;k++){
	C2=(4*k)+j;
	res[C0] += m1[C1]*m2[C2];
	//cerr << " " << C0 << " " << C1 << " " << C2 << endl;
	C1++;
      }
      //cerr << " res["<<C0<<"] = "<< res[C0];
      C0++;
    }
    //cerr << endl;
  }
  res[3]  = 0.0;
  res[7]  = 0.0;
  res[11] = 0.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R3Vector3Multiply( T *res, const vector <T> m1, T *pos ){
  int C0=0.0, C1=0.0;
  for(int i=0; i<3; i++){
    res[C0] = 0.0;
    C1 = (i*4);
    for(int k=0;k<3;k++){
      res[C0] += m1[C1]*pos[k];
      //cerr << " Res["<<C0<<"]= "<< res[C0] //<< " - " << C1 << " " << k;
      // << " m1[" << C1 << "]= " << m1[C1]
      //<< " p[" << k << "]= " << pos[k];
      //cerr << " R "<< C0 <<" "<< C1 << " " << k;
      //getchar();
      //cerr << endl;
      C1++;
    }
    //getchar();
    C0++;
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R4SetIdentity( vector <T> &rot, const T *pos ){
  rot[0] = 1.0;
  rot[1] = 0.0;
  rot[2] = 0.0;
  rot[3] = pos[0];
  
  rot[4] = 0.0;
  rot[5] = 1.0;
  rot[6] = 0.0;
  rot[7] = pos[1];
  
  rot[8] = 0.0;
  rot[9] = 0.0;
  rot[10] = 1.0;
  rot[11] = pos[2];

  rot[12] = 0.0;
  rot[13] = 0.0;
  rot[14] = 0.0;
  rot[15] = 1.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void Rotate_on_X_Axis( T *res, const T *pos, T theta ){
  //dMatrix3 rot;
  vector <T> rot;
  rot.assign(12, 0.0);

  rot[0] = 1.0;
  rot[1] = 0.0;
  rot[2] = 0.0;
  
  rot[3] = 0.0;
  rot[4] = cos(theta);
  rot[5] = -sin(theta);
  
  rot[6] = 0.0;
  rot[7] = sin(theta);
  rot[8] = cos(theta);
  
  int C0=0.0, C1=0.0;
  for(int i=0; i<3; i++){
    C1 = i*3;
    res[C0] = 0.0;
    //cerr << " " << C0;
    for(int j=0; j<3; j++){
      res[C0] += rot[C1]*pos[j];
      //cerr << " " << C1 << " " << j;
      C1++;
    }
    //cerr << endl;
    C0++;
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void Rotate_on_Y_Axis( T *res, const T *pos, T theta ){
  //dMatrix3 rot;
  vector <T> rot;
  rot.assign(12, 0.0);

  rot[0] = cos(theta);
  rot[1] = 0.0;
  rot[2] = sin(theta);
  
  rot[3] = 0.0;
  rot[4] = 1.0;
  rot[5] = 0.0;
  
  rot[6] = -sin(theta);
  rot[7] = 0.0;
  rot[8] = cos(theta);
  
  int C0=0.0, C1=0.0;
  for(int i=0; i<3; i++){
    C1 = i*3;
    res[C0] = 0.0;
    //cerr << " " << C0;
    for(int j=0; j<3; j++){
      res[C0] += rot[C1]*pos[j];
      //cerr << " " << C1 << " " << j;
      C1++;
    }
    //cerr << endl;
    C0++;
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void Rotate_on_Z_Axis( T *res, const T *pos, T theta ){
  //dMatrix3 rot;
  vector <T> rot;
  rot.assign(12, 0.0);

  rot[0] = cos(theta);
  rot[1] = -sin(theta);
  rot[2] = 0.0;
  
  rot[3] = sin(theta);
  rot[4] = cos(theta);
  rot[5] = 0.0;
  
  rot[6] = 0.0;
  rot[7] = 0.0;
  rot[8] = 1.0;
  
  int C0=0.0, C1=0.0;
  for(int i=0; i<3; i++){
    C1 = i*3;
    res[C0] = 0.0;
    //cerr << " " << C0;
    for(int j=0; j<3; j++){
      res[C0] += rot[C1]*pos[j];
      //cerr << " " << C1 << " " << j;
      C1++;
    }
    //cerr << endl;
    C0++;
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R3toR4( vector <T> &R4, const vector <T> rot, const T *pos ){
  R4[0]  = rot[0];
  R4[1]  = rot[1];
  R4[2]  = rot[2];
  R4[3]  = pos[0];
  
  R4[4]  = rot[4];
  R4[5]  = rot[5];
  R4[6]  = rot[6];
  R4[7]  = pos[1];
  
  R4[8]  = rot[8];
  R4[9]  = rot[9];
  R4[10] = rot[10];
  R4[11] = pos[2];
  
  R4[12] = 0.0;
  R4[13] = 0.0;
  R4[14] = 0.0;
  R4[15] = 1.0;
  
  // int count = 0;
  // for(int i = 0; i < 4; i++){
  //   for(int j = 0; j < 4; j++){
  //     cerr << " R4["<<count<<"] = " << R4[count];
  //     count++;
  //   }
  //   cerr << endl;
  // }
  // exit(0);
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void R4toR3andPOS(vector <T> &R3, T *pos, vector <T> R4){
  
  R3[0]  = R4[0];
  R3[1]  = R4[1];
  R3[2]  = R4[2];
  R3[3]  = 0.0;
  pos[0] = R4[3];

  R3[4]  = R4[4];
  R3[5]  = R4[5];
  R3[6]  = R4[6];
  R3[7]  = 0.0;
  pos[1] = R4[7];
  
  R3[8]  = R4[8];
  R3[9]  = R4[9];
  R3[10] = R4[10];
  R3[11] = 0.0;
  pos[2] = R4[11];

 //  int count = 0;
//   for(int i=0; i<3; i++){
//     for(int j=0; j<4; j++){
//       cerr << "  SECOND ["<<count <<"] = " << R3[count];
//       count++;
//     }
//     cerr << endl;
//     //getchar();
//   }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
template <typename T>
void get_R4transpose ( vector <T> &transp, vector <T> m1 ){
  int count = 0;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++){
      transp[(j*4)+i] = m1[count];
      //cerr << " transp["<<(j*4)+i <<"] = " << transp[(j*4)+i] << " From = " << count << " to = " << (j*4)+i << endl;
      count++;
    }
    //cerr << endl;
    //getchar();
  }

  // count = 0;
//   for(int i=0; i<4; i++){
//     for(int j=0; j<4; j++){
//       cerr << "  FIRST ["<<count <<"] = " << transp[count];
//       count++;
//     }
//     cerr << endl;
//     getchar();
//   }

}
/* ----------------------------------------------------------------------- */

#endif
