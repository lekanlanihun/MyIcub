#include "icub.h"

/* ----------------------------------------------------------------------- */
/*                              CONSTRUCTOR                                */
/* ----------------------------------------------------------------------- */

MyIcub::MyIcub( void ) : World_Entity ( )
{  
  /* ---- Resize vectors ---- */
  T0.assign(16, 0.0);
  T1.assign(16, 0.0);
  T2.assign(16, 0.0);
  RA0.assign(16, 0.0);
  RA1.assign(16, 0.0);
  RA2.assign(16, 0.0);
  RA3.assign(16, 0.0);
  RA4.assign(16, 0.0);
  RA5.assign(16, 0.0);
  N0.assign(16, 0.0);
  N1.assign(16, 0.0);
  N2.assign(16, 0.0);
  RE0.assign(16, 0.0);
  RE1.assign(16, 0.0);
  RE2.assign(16, 0.0);
  LE0.assign(16, 0.0);
  LE1.assign(16, 0.0);
  LE2.assign(16, 0.0);
  HEAD.assign(16, 0.0);
  
  torso_rot.assign               (3, 0.0);
  shoulder_rot.assign            (3, 0.0);
  elbow_rot.assign               (1, 0.0);
  wrist_rot.assign               (3, 0.0);
  neck_rot.assign                (3, 0.0);
  r_eye_rot.assign               (2, 0.0);
  l_eye_rot.assign               (2, 0.0);
  
  torso_bounds_reached.assign    (3, false);
  shoulder_bounds_reached.assign (3, false);
  elbow_bounds_reached.assign    (1, false);
  wrist_bounds_reached.assign    (3, false);
  neck_bounds_reached.assign     (3, false);
  r_eye_bounds_reached.assign    (2, false);
  l_eye_bounds_reached.assign    (2, false);
  r_pan_tilt_offset.assign       (2, 0.0);
  l_pan_tilt_offset.assign       (2, 0.0);
  head_pan_tilt_offset.assign    (3, 0.0);
  version.assign                 (2, 0.0);
  approx_version.assign          (2, 0.0);
  
  torso_pos    = new double[3];
  init();
}

/* ------------------------------------------------------------ */

MyIcub::MyIcub(const MyIcub& other)
  : World_Entity(other)
{
  copy(other);
  init();
}

/* ------------------------------------------------------------ */

void MyIcub::copy(const MyIcub& other)
{
  /* ---- Resize vectors ---- */
  T0 = other.T0;
  T1 = other.T1;
  T2 = other.T2;
  RA0 = other.RA0;
  RA1 = other.RA1;
  RA2 = other.RA2;
  RA3 = other.RA3;
  RA4 = other.RA4;
  RA5 = other.RA5;
  N0 = other.N0;
  N1 = other.N1;
  N2 = other.N2;
  RE0 = other.RE0;
  RE1 = other.RE1;
  RE2 = other.RE2;
  LE0 = other.LE0;
  LE1 = other.LE1;
  LE2 = other.LE2;
  HEAD = other.HEAD;
  
  torso_rot = other.torso_rot;
  shoulder_rot = other.shoulder_rot;
  elbow_rot = other.elbow_rot;
  wrist_rot = other.wrist_rot;
  neck_rot = other.neck_rot;
  r_eye_rot = other.r_eye_rot;
  l_eye_rot = other.l_eye_rot;
  
  torso_bounds_reached = other.torso_bounds_reached;
  shoulder_bounds_reached = other.shoulder_bounds_reached;
  elbow_bounds_reached = other.elbow_bounds_reached;
  wrist_bounds_reached = other.wrist_bounds_reached;
  neck_bounds_reached = other.neck_bounds_reached;
  r_eye_bounds_reached = other.r_eye_bounds_reached;
  l_eye_bounds_reached = other.l_eye_bounds_reached;
  r_pan_tilt_offset = other.r_pan_tilt_offset;
  l_pan_tilt_offset = other.l_pan_tilt_offset;
  head_pan_tilt_offset = other.head_pan_tilt_offset;
  version = other.version;
  approx_version = other.approx_version;

  torso_pos    = new double[3];
}

/* ------------------------------------------------------------ */

void MyIcub::destroy()
{ 
  T0.clear();
  T1.clear();
  T2.clear();
  RA0.clear();
  RA1.clear();
  RA2.clear();
  RA3.clear();
  RA4.clear();
  RA5.clear();
  N0.clear(); 
  N1.clear(); 
  N2.clear(); 
  RE0.clear();
  RE1.clear();
  RE2.clear();
  LE0.clear();
  LE1.clear();
  LE2.clear();
  HEAD.clear();
  
  torso_rot.clear();
  shoulder_rot.clear();
  elbow_rot.clear();
  wrist_rot.clear();
  neck_rot.clear();
  r_eye_rot.clear();
  l_eye_rot.clear();
  
  torso_bounds_reached.clear();
  shoulder_bounds_reached.clear();
  elbow_bounds_reached.clear();
  wrist_bounds_reached.clear();
  neck_bounds_reached.clear();
  r_eye_bounds_reached.clear();
  l_eye_bounds_reached.clear();
  r_pan_tilt_offset.clear();
  l_pan_tilt_offset.clear();
  head_pan_tilt_offset.clear();
  version.clear();
  approx_version.clear();
  delete[] torso_pos;
}

/* ------------------------------------------------------------ */
MyIcub& MyIcub::operator=(const MyIcub &other)
{
  if(this != &other)
    {
      destroy();
      copy(other);
    }
  return *this;
}


MyIcub::~MyIcub( ){
  destroy();
}

void MyIcub::init( void ){
  r_visual_distance = 200.0;
  l_visual_distance = 200.0;
  vergence          = 0.0;
}

/* ----------------------------------------------------------------------- */
/*                             END CONSTRUCTOR                             */
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
/*              INIT AGENT POSITION AND JOINTS ROTATION                    */
/* ----------------------------------------------------------------------- */
void MyIcub::init_pos_and_joints_rotation( const vector <double> &pos ){
  /* ---- Position the TRUNK ---- */
  torso_pos[0] = pos[0];
  torso_pos[1] = pos[1];
  torso_pos[2] = pos[2];

  vector <double> R;
  R.assign(12, 0.0);
  getRMatrixFrom_Y_AxisAndAngle (R, -M_PI*0.5 );

  R3toR4( T0, R, torso_pos );
  reset_joints_to_init_angles();
}

/* ----------------------------------------------------------------------- */
/*                         RESET JOINTS ROTATION                           */
/* ----------------------------------------------------------------------- */
void MyIcub::reset_joints_to_init_angles ( void  ){
  
  shoulder_rot[0] = l_r_shoulder_pitch;
  shoulder_rot[1] = l_r_shoulder_roll;
  shoulder_rot[2] = l_r_shoulder_yaw;
  
  elbow_rot[0] = l_r_elbow_pitch;

  wrist_rot[0] = l_r_wrist_pitch;
  wrist_rot[1] = l_r_wrist_roll;
  wrist_rot[2] = l_r_wrist_yaw;
  
  neck_rot[0] = 0.0;//l_neck_pitch;
  neck_rot[1] = 0.0;//l_neck_roll;
  neck_rot[2] = 0.0;//l_neck_yaw;

  r_eye_rot[0] = 0.0;//l_r_eye_tilt;
  r_eye_rot[1] = 0.0;//l_r_eye_pan;

  l_eye_rot[0] = 0.0;//l_l_eye_tilt;
  l_eye_rot[1] = 0.0;//l_l_eye_pan;

  apply_torso_rotation( );
}

/* ----------------------------------------------------------------------- */
/*        SET/UPDATES BY SELECTING THE JOINT THAT HAS TO BE UPDATED        */
/* ----------------------------------------------------------------------- */
void MyIcub::set_joint_current_rotation (const int which_joint, const vector <double> &updates ){
  switch(which_joint){
  case TORSO:
    set_torso_current_rotation ( updates );
    break;
  case R_SHOULDER:
    set_r_shoulder_current_rotation ( updates );
    break;
  case R_ELBOW:
    set_r_elbow_current_rotation ( updates );
    break;
  case R_WRIST:  
    set_r_wrist_current_rotation ( updates );
    break;
  case NECK:
    set_neck_current_rotation ( updates ); 
    break;
  case R_EYE:
    set_right_eye_current_rotation ( updates );
    break;
  case L_EYE:
    set_left_eye_current_rotation ( updates );
    break;
  case BOTH_EYES:
    set_eyes_current_rotation ( updates, updates );
    break;
  default:
    cerr << " In MyIcub::set_current_rotation - A joints has to be specified " << endl;
    exit(0);
    break;
  }
}

void MyIcub::update_joint_current_rotation (const int which_joint, const vector <double> &updates ){
  switch(which_joint){
  case TORSO:
    update_torso_current_rotation ( updates );
    break;
  case R_SHOULDER:
    update_r_shoulder_current_rotation ( updates );
    break;
  case R_ELBOW:
    update_r_elbow_current_rotation ( updates );
    break;
  case R_WRIST:  
    update_r_wrist_current_rotation ( updates );
    break;
  case NECK:
    update_neck_current_rotation ( updates ); 
    break;
  case R_EYE:
    update_right_eye_current_rotation ( updates );
    break;
  case L_EYE:
    update_left_eye_current_rotation ( updates );
    break;
  case BOTH_EYES:
    update_eyes_current_rotation ( updates, updates );
    break;
  default:
    cerr << " In MyIcub::update_current_rotation - A joints has to be specified " << endl;
    exit(0);
    break;
  }
}

/* ----------------------------------------------------------------------- */
/*                SET/UPDATES TORSO ROTATION MEMORY VECTORS                */
/* ----------------------------------------------------------------------- */
void MyIcub::set_torso_current_rotation (const vector <double> &updates ){
  
  /* ---- PITCH ---- */
  torso_bounds_reached[0] = false;
  if( updates[0] >= l_torso_pitch && updates[0] <= h_torso_pitch )
    torso_rot[0] = updates[0];
  else {
    torso_rot[0] = l_torso_pitch;
    torso_bounds_reached[0] = true;
  }
  
  /* ---- ROLL ---- */
  torso_bounds_reached[1] = false;
  if( updates[1] >= l_torso_roll && updates[1] <= h_torso_roll  )
    torso_rot[1] = updates[1];
  else {
    torso_rot[1] = l_torso_roll;
    torso_bounds_reached[1] = true;
  }
  
  /* ---- YAW ---- */
  torso_bounds_reached[2] = false;
  if( updates[2] >= l_torso_yaw && updates[2] <= h_torso_yaw )
    torso_rot[2] = updates[2];
  else {
    torso_rot[2] = l_torso_yaw;
    torso_bounds_reached[2] = true;
  }
  
  apply_torso_rotation( );
}

void MyIcub::update_torso_current_rotation (const vector <double> &updates ){

  /* ---- PITCH ---- */
  if( (torso_rot[0] + updates[0] ) > l_torso_pitch   &&
      (torso_rot[0] + updates[0] ) < h_torso_pitch ){
    torso_rot[0]    += updates[0];
    torso_bounds_reached[0] = false;
  }
  else torso_bounds_reached[0] = true;
  
  /* ---- ROLL ---- */
  if( (torso_rot[1] + updates[1] ) > l_torso_roll &&
      (torso_rot[1] + updates[1] ) < h_torso_roll  ){
    torso_rot[1]    += updates[1];
    torso_bounds_reached[1] = false;
  }
  else torso_bounds_reached[1] = true;
  
  /* ---- YAW ---- */
  if( (torso_rot[2] + updates[2] ) > l_torso_yaw &&
      (torso_rot[2] + updates[2] ) < h_torso_yaw ){
    torso_rot[2]    += updates[2];
    torso_bounds_reached[2] = false;
  }
  else torso_bounds_reached[2] = true;

  apply_torso_rotation( );
}

/* ----------------------------------------------------------------------- */
/*            SET/UPDATES RIGHT SHOULDER ROTATION MEMORY VECTORS           */
/* ----------------------------------------------------------------------- */
void MyIcub::set_r_shoulder_current_rotation (const vector <double> &updates ){
 
  /* ---- PITCH ---- */
  shoulder_bounds_reached[0] = false;
  if( updates[0] >= l_r_shoulder_pitch && updates[0] <= h_r_shoulder_pitch )
    shoulder_rot[0] = updates[0];
  else {
    shoulder_rot[0] = l_r_shoulder_pitch;
    shoulder_bounds_reached[0] = true;
  }
  
  /* ---- ROLL ---- */
  shoulder_bounds_reached[1] = false;
  if( updates[1] >= l_r_shoulder_roll && updates[1]  <= h_r_shoulder_roll )
    shoulder_rot[1] =  updates[1];
  else {
    shoulder_rot[1] = l_r_shoulder_roll;
    shoulder_bounds_reached[1] = true;
  }
  
  /* ---- YAW ---- */
  shoulder_bounds_reached[2] = false;
  if( updates[2] >= l_r_shoulder_yaw && updates[2] <= h_r_shoulder_yaw )
    shoulder_rot[2] =  updates[2];
  else {
    shoulder_rot[2] = l_r_shoulder_yaw;
    shoulder_bounds_reached[2] = true;
  }

  apply_r_shoulder_rotation( );
}

void MyIcub::update_r_shoulder_current_rotation (const vector <double> &updates ){
  
  /* ---- PITCH ---- */
  if( (shoulder_rot[0] + updates[0] ) > l_r_shoulder_pitch &&
      (shoulder_rot[0] + updates[0] ) < h_r_shoulder_pitch ){
    shoulder_rot[0]    += updates[0];
    shoulder_bounds_reached[0] = false;
  }
  else shoulder_bounds_reached[0] = true;

  /* ---- ROLL ---- */
  if( (shoulder_rot[1] + updates[1] ) > l_r_shoulder_roll &&
      (shoulder_rot[1] + updates[1] ) < h_r_shoulder_roll ){
    shoulder_rot[1]    +=  updates[1];
    shoulder_bounds_reached[1] = false;
  }
  else shoulder_bounds_reached[1] = true;
  
  /* ---- YAW ---- */
  if( (shoulder_rot[2] + updates[2] ) > l_r_shoulder_yaw &&
      (shoulder_rot[2] + updates[2] ) < h_r_shoulder_yaw ){
    shoulder_rot[2]    +=  updates[2];
    shoulder_bounds_reached[2] = false;
  }
  else shoulder_bounds_reached[2] = true;

  apply_r_shoulder_rotation( );
}

/* ----------------------------------------------------------------------- */
/*              SET/UPDATES RIGHT ELBOW ROTATION MEMORY VECTORS            */
/* ----------------------------------------------------------------------- */
void MyIcub::set_r_elbow_current_rotation (const vector <double> &updates ){
  /* ---- PITCH ---- */
  elbow_bounds_reached[0] = false; 
  if( updates[0] >= l_r_elbow_pitch && updates[0] <= h_r_elbow_pitch )
    elbow_rot[0] = updates[0];
  else {
    elbow_rot[0] = l_r_elbow_pitch;
    elbow_bounds_reached[0] = true;
  }
  
  apply_r_elbow_rotation( );
}

void MyIcub::update_r_elbow_current_rotation (const vector <double> &updates ){
  
  /* ---- PITCH ---- */
  double new_pitch = elbow_rot[0] + updates[0];
  elbow_bounds_reached[0] = true;
  if( new_pitch > l_r_elbow_pitch  && new_pitch < h_r_elbow_pitch ){
    elbow_rot[0]    =  new_pitch;
    elbow_bounds_reached[0] = false;
  }
  apply_r_elbow_rotation( );

}

/* ----------------------------------------------------------------------- */
/*              SET/UPDATES RIGHT WRIST ROTATION MEMORY VECTORS            */
/* ----------------------------------------------------------------------- */
void MyIcub::set_r_wrist_current_rotation (const vector <double> &updates ){
  
  /* ---- PITCH ---- */
  wrist_bounds_reached[0] = false;
  if( updates[0] >= l_r_wrist_pitch  && updates[0] <= h_r_wrist_pitch )
    wrist_rot[0] =  updates[0];
  else {
    wrist_rot[0] = l_r_wrist_pitch;
    wrist_bounds_reached[0] = true;
  }
  
  /* ---- ROLL ---- */
  wrist_bounds_reached[1] = false;
  if( updates[1] >= l_r_wrist_roll && updates[1] <= h_r_wrist_roll )
    wrist_rot[1] =  updates[1];
  else {
    wrist_rot[1] = l_r_wrist_roll;
    wrist_bounds_reached[1] = true;
  }
  
  /* ---- YAW ---- */
  wrist_bounds_reached[2] = false;
  if( updates[2] >=  l_r_wrist_yaw && updates[2] <= h_r_wrist_yaw )
    wrist_rot[2] =  updates[2];
  else {
    wrist_rot[2] = l_r_wrist_yaw;
    wrist_bounds_reached[2] = true;
  }
  
  apply_r_wrist_rotation( );
}

void MyIcub::update_r_wrist_current_rotation (const vector <double> &updates ){
  
  /* ---- PITCH ---- */
  if( (wrist_rot[0] + updates[0] ) > l_r_wrist_pitch  &&
      (wrist_rot[0] + updates[0] ) < h_r_wrist_pitch ){
    wrist_rot[0]    +=  updates[0];
    wrist_bounds_reached[0] = false;
  }
  else wrist_bounds_reached[0] = true;

  /* ---- ROLL ---- */
  if( (wrist_rot[1] + updates[1] ) > l_r_wrist_roll &&
      (wrist_rot[1] + updates[1] ) < h_r_wrist_roll ){
    wrist_rot[1]    +=  updates[1];
    wrist_bounds_reached[1] = false;
  }
  else wrist_bounds_reached[1] = true;
  
  /* ---- YAW ---- */
  if( (wrist_rot[2] + updates[2] ) >  l_r_wrist_yaw &&
      (wrist_rot[2] + updates[2] ) <  h_r_wrist_yaw ){
    wrist_rot[2]    +=  updates[2];
    wrist_bounds_reached[2] = false;
  }
  else wrist_bounds_reached[2] = true;
  
  apply_r_wrist_rotation( );
  
}

/* ----------------------------------------------------------------------- */
/*               SET/UPDATES NECK ROTATION MEMORY VECTORS                  */
/* ----------------------------------------------------------------------- */
void MyIcub::set_neck_current_rotation (const vector <double> &updates ){

  static constexpr double l_neck_pitch = -((35.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_neck_pitch =  (20.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_neck_roll  = -((40.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_neck_roll  =  (40.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_neck_yaw   = -((50.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_neck_yaw   =  (50.0 * ONE_PI)+ EPSILON_ICUB;

  /* ---- PITCH ---- */
  neck_bounds_reached[0] = false;
  if( updates[0] >= l_neck_pitch && updates[0] <= h_neck_pitch )
    neck_rot[0] =  updates[0];
  else{
    if( updates[0] < l_neck_pitch ){
      neck_rot[0] = l_neck_pitch;
      cerr << " updates[0] < l_neck_pitch " << endl;
    }
    else if( updates[0] > h_neck_pitch ){
      neck_rot[0] = h_neck_pitch;
      cerr << " updates[0] > h_neck_pitch " << endl;
    }
    neck_bounds_reached[0] = true;
  }
  
  /* ---- ROLL ---- */
  neck_bounds_reached[1] = false;
  if( updates[1] >= l_neck_roll && updates[1] <= h_neck_roll )
    neck_rot[1] =  updates[1];
  else {
    if( updates[1] < l_neck_roll ) {
      neck_rot[1] = l_neck_roll;
      cerr << " updates[1] < l_neck_roll " << endl;
    }
    else if( updates[1] > h_neck_roll ) {
      neck_rot[1] = h_neck_roll;
      cerr << " updates[1] > h_neck_roll " << endl;
    }
    neck_bounds_reached[1] = true;
  }
  
  /* ---- YAW ---- */
  neck_bounds_reached[2] = false;
  if( updates[2] >= l_neck_yaw && updates[2] <= h_neck_yaw )
    neck_rot[2]  =  updates[2];
  else{
    if( updates[2] < l_neck_yaw ){
      neck_rot[2] = l_neck_yaw;
      cerr << " updates[2] < l_neck_yaw " << endl;
    }
    else if( updates[2] > h_neck_yaw ) {
      neck_rot[2] = h_neck_yaw;
      cerr << " updates[2] > h_neck_yaw" << endl;
    }
    neck_bounds_reached[2] = true;
  }
  //Now you apply the rotations for all three joints
  apply_neck_rotation( );
}

void MyIcub::update_neck_current_rotation (const vector <double> &updates ){
  
  /* ---- PITCH ---- */
  if( (neck_rot[0] + updates[0] ) > l_neck_pitch &&
      (neck_rot[0] + updates[0] ) < h_neck_pitch ){
    neck_rot[0]    +=  updates[0];
    neck_bounds_reached[0] = false;
  }
  else {
    if((neck_rot[0]+updates[0]) < l_neck_pitch ) neck_rot[0] = l_neck_pitch;
    else if((neck_rot[0]+updates[0]) > h_neck_pitch ) neck_rot[0] = h_neck_pitch;
    neck_bounds_reached[0] = true;
  }
  
  /* ---- ROLL ---- */
  if( (neck_rot[1] + updates[1] ) > l_neck_roll &&
      (neck_rot[1] + updates[1] ) < h_neck_roll ){
    neck_rot[1]    +=  updates[1];
    neck_bounds_reached[1] = false;
  }
  else {
    if( ( neck_rot[1] + updates[1]) < l_neck_roll ) neck_rot[1] = l_neck_roll;
    else if( (neck_rot[1] + updates[1]) > h_neck_roll ) neck_rot[1] = h_neck_roll;
    neck_bounds_reached[1] = true;
  }

  /* ---- YAW ---- */
  if( (neck_rot[2] + updates[2] ) > l_neck_yaw &&  
      (neck_rot[2] + updates[2] ) < h_neck_yaw ){
    neck_rot[2]    +=  updates[2];
    neck_bounds_reached[2] = false;
  }
  else {
    if( (neck_rot[2] + updates[2]) < l_neck_yaw ) neck_rot[2] = l_neck_yaw;
    else if( (neck_rot[2] + updates[2]) > h_neck_yaw ) neck_rot[2] = h_neck_yaw;
    neck_bounds_reached[2] = true;
  }

  //Now you apply the rotations for all three joints
  apply_neck_rotation( );
}

/* ----------------------------------------------------------------------- */
/*              SET/UPDATES RIGHT EYE ROTATION MEMORY VECTORS              */
/* ----------------------------------------------------------------------- */
void MyIcub::set_eyes_current_rotation (const vector <double> &r_updates, const vector <double> &l_updates ){
  
  /* ---- TILT ---- */
  r_eye_bounds_reached[0] = false;
  if(  r_updates[0] >= l_r_eye_tilt && r_updates[0] <= h_r_eye_tilt )
    r_eye_rot[0] =  r_updates[0];
  else{
    r_eye_rot[0] = 0.0;//l_r_eye_tilt;
    r_visual_distance = 6.0;
    r_eye_bounds_reached[0] = true;
  }
  
  l_eye_bounds_reached[0] = false;
  if( l_updates[0] >= l_l_eye_tilt && l_updates[0] <= h_l_eye_tilt )
    l_eye_rot[0] =  l_updates[0];
  else {
    l_eye_rot[0] = 0.0;//l_l_eye_tilt;
    l_visual_distance = 6.0;
    l_eye_bounds_reached[0] = true;
  }
  
  /* ---- PAN ---- */
  r_eye_bounds_reached[1] = false; 
  if( r_updates[1] >= l_r_eye_pan && r_updates[1] <= h_r_eye_pan )
    r_eye_rot[1] = r_updates[1];
  else {
    r_eye_rot[1] = 0.0;//l_r_eye_pan;
    r_visual_distance = 6.0;
    r_eye_bounds_reached[1] = true; 
  }
  
  l_eye_bounds_reached[1] = false;     
  if( l_updates[1] >= l_l_eye_pan && l_updates[1] <= h_l_eye_pan )
    l_eye_rot[1] = l_updates[1];
  else {
    l_eye_rot[1] = 0.0;//l_l_eye_pan;
    l_visual_distance = 6.0;
    l_eye_bounds_reached[1] = true;  
  }
  
  apply_r_eye_rotation( );
  apply_l_eye_rotation( );
}

void MyIcub::set_right_eye_current_rotation (const vector <double> &r_updates ){
  
  /* ---- TILT ---- */
  r_eye_bounds_reached[0] = false;
  if(  r_updates[0] >= l_r_eye_tilt && r_updates[0] <= h_r_eye_tilt )
    r_eye_rot[0] =  r_updates[0];
  else{
    //r_visual_distance = 6.0;
    r_eye_bounds_reached[0] = true;
    if( r_updates[0] < l_r_eye_tilt )
      r_eye_rot[0] = l_r_eye_tilt;
    else if(r_updates[0] > h_r_eye_tilt )
      r_eye_rot[0] = h_r_eye_tilt;
  }
  
  /* ---- PAN ---- */
  r_eye_bounds_reached[1] = false; 
  if( r_updates[1] >= l_r_eye_pan && r_updates[1] <= h_r_eye_pan )
    r_eye_rot[1] = r_updates[1];
  else {
    //r_visual_distance = 6.0;
    r_eye_bounds_reached[1] = true; 
    if( r_updates[1] < l_r_eye_pan )
      r_eye_rot[1] = l_r_eye_pan;
    else if ( r_updates[1] > h_r_eye_pan )
      r_eye_rot[1] = h_r_eye_pan;
  }
  apply_r_eye_rotation( );
}

void MyIcub::set_left_eye_current_rotation ( const vector <double> &l_updates ){
  
  /* ---- TILT ---- */
  l_eye_bounds_reached[0] = false;
  if( l_updates[0] >= l_l_eye_tilt && l_updates[0] <= h_l_eye_tilt )
    l_eye_rot[0] =  l_updates[0];
  else {
    //l_visual_distance = 6.0;
    l_eye_bounds_reached[0] = true;
    if( l_updates[0] < l_l_eye_tilt )
      l_eye_rot[0] = l_l_eye_tilt;
    else if ( l_updates[0] > h_l_eye_tilt )
      l_eye_rot[0] = h_l_eye_tilt;
  }
  
  /* ---- PAN ---- */
  l_eye_bounds_reached[1] = false;     
  if( l_updates[1] >= l_l_eye_pan && l_updates[1] <= h_l_eye_pan )
    l_eye_rot[1] = l_updates[1];
  else {
    //l_visual_distance = 6.0;
    l_eye_bounds_reached[1] = true;  
    if( l_updates[1] < l_l_eye_pan )
      l_eye_rot[1] = l_l_eye_pan;
    else if (l_updates[1] < h_l_eye_pan )
      l_eye_rot[1] = h_l_eye_pan;
  }
  apply_l_eye_rotation( );
}

void MyIcub::update_eyes_current_rotation (const vector <double> &r_updates, const vector <double> &l_updates ){
  
  /* ---- TILT ---- */
  double new_tilt = r_eye_rot[0] + r_updates[0];
  if(  new_tilt > l_r_eye_tilt && new_tilt < h_r_eye_tilt ) {
    r_eye_rot[0]            =  new_tilt;
    r_eye_bounds_reached[0] = false;
  } 
  else{
    //r_visual_distance = 6.0;
    r_eye_bounds_reached[0] = true;
    if(  new_tilt < l_r_eye_tilt )
      r_eye_rot[0] = l_r_eye_tilt;
    else if( new_tilt > h_r_eye_tilt )
      r_eye_rot[0] = h_r_eye_tilt;
  }
  
  new_tilt = l_eye_rot[0] + l_updates[0];
  if( new_tilt > l_l_eye_tilt && new_tilt < h_l_eye_tilt ) {
    l_eye_rot[0]            =  new_tilt;
    l_eye_bounds_reached[0] = false;
  }
  else {
    //l_visual_distance = 6.0;
    l_eye_bounds_reached[0] = true;  
    if( new_tilt < l_l_eye_tilt )
      l_eye_rot[0] = l_l_eye_tilt;
    else if ( new_tilt > h_l_eye_tilt )
      l_eye_rot[0] = h_l_eye_tilt;
  }
  
  /* ---- PAN ---- */
  double new_pan = r_eye_rot[1] + r_updates[1];
  if( new_pan > l_r_eye_pan && new_pan < h_r_eye_pan ) {
    r_eye_rot[1]            = new_pan;
    r_eye_bounds_reached[1] = false; 
  }
  else{
    //r_visual_distance = 6.0;
    r_eye_bounds_reached[1] = true;
    if( new_pan < l_r_eye_pan)
      r_eye_rot[1] = l_r_eye_pan;  
    else if ( new_pan > h_r_eye_pan )
      r_eye_rot[1] = h_r_eye_pan;  
  }
  
  new_pan = l_eye_rot[1] + l_updates[1];
  if( new_pan > l_l_eye_pan && new_pan < h_l_eye_pan ){ 
    l_eye_rot[1]            = new_pan;
    l_eye_bounds_reached[1] = false; 
  }
  else {
    //l_visual_distance = 6.0;
    l_eye_bounds_reached[1] = true;  
    if( new_pan < l_l_eye_pan )
      l_eye_rot[1] = l_l_eye_pan;
    else if ( new_pan > h_l_eye_pan )
      l_eye_rot[1] = h_l_eye_pan;
  }
    
  apply_r_eye_rotation( );
  apply_l_eye_rotation( );
}


void MyIcub::update_right_eye_current_rotation (const vector <double> &r_updates ){
  
  /* ---- TILT ---- */
  double new_tilt = r_eye_rot[0] + r_updates[0];
    r_eye_rot[0]            =  new_tilt;
  /*if(  new_tilt > l_r_eye_tilt && new_tilt < h_r_eye_tilt ) {
    r_eye_rot[0]            =  new_tilt;
    r_eye_bounds_reached[0] = false;
  } 
  else{
    //r_visual_distance = 6.0;
    r_eye_bounds_reached[0] = true;
    if(  new_tilt < l_r_eye_tilt )
      r_eye_rot[0] = l_r_eye_tilt;
    else if( new_tilt > h_r_eye_tilt )
      r_eye_rot[0] = h_r_eye_tilt;
  }*/
  
  /* ---- PAN ---- */
  double new_pan = r_eye_rot[1] + r_updates[1];
   r_eye_rot[1]            = new_pan; 
  /*if( new_pan > l_r_eye_pan && new_pan < h_r_eye_pan ) {
    r_eye_rot[1]            = new_pan;
    r_eye_bounds_reached[1] = false; 
  }
  else{
    //r_visual_distance = 6.0;
    r_eye_bounds_reached[1] = true;
    if( new_pan < l_r_eye_pan)
      r_eye_rot[1] = l_r_eye_pan;  
    else if ( new_pan > h_r_eye_pan )
      r_eye_rot[1] = h_r_eye_pan;  
  }*/
  
  apply_r_eye_rotation( );
}


void MyIcub::update_left_eye_current_rotation ( const vector <double> &l_updates ){
  
  /* ---- TILT ---- */
  double new_tilt = l_eye_rot[0] + l_updates[0];
  if( new_tilt > l_l_eye_tilt && new_tilt < h_l_eye_tilt ) {
    l_eye_rot[0]            =  new_tilt;
    l_eye_bounds_reached[0] = false;
  }
  else {
    //l_visual_distance = 6.0;
    l_eye_bounds_reached[0] = true;  
    if( new_tilt < l_l_eye_tilt )
      l_eye_rot[0] = l_l_eye_tilt;
    else if ( new_tilt > h_l_eye_tilt )
      l_eye_rot[0] = h_l_eye_tilt;
  }
  
  /* ---- PAN ---- */
  double new_pan = l_eye_rot[1] + l_updates[1];
  if( new_pan > l_l_eye_pan && new_pan < h_l_eye_pan ){ 
    l_eye_rot[1]            = new_pan;
    l_eye_bounds_reached[1] = false; 
  }
  else {
    //l_visual_distance = 6.0;
    l_eye_bounds_reached[1] = true;  
    if( new_pan < l_l_eye_pan )
      l_eye_rot[1] = l_l_eye_pan;
    else if ( new_pan > h_l_eye_pan )
      l_eye_rot[1] = h_l_eye_pan;
  }
    
  apply_l_eye_rotation( );
}


/* ----------------------------------------------------------------------- */
/*                             TORSO ROTATION                              */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_torso_rotation( void ){
  
  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, 3.2, 0.0, M_PI*0.5, torso_rot[0] );
  R4Multiply( T1, T0, rot );

  get_icub_transform_matrix ( rot, 0.0, -0.55, M_PI*0.5, torso_rot[1] -(M_PI*0.5) );
  R4Multiply( T2, T1, rot );
  
  apply_r_shoulder_rotation( );  
  apply_neck_rotation( );  
}

/* ----------------------------------------------------------------------- */
/*                          RIGHT SHOULDER ROTATION                        */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_r_shoulder_rotation( void ){
  
  vector <double> rot;
  rot.assign(16, 0.0);

  get_icub_transform_matrix ( rot, -2.33647, -14.33, M_PI*0.5, torso_rot[2]-(ONE_PI*15.0)-(M_PI*0.5) );
  R4Multiply( RA0, T2, rot );
  
  get_icub_transform_matrix ( rot, 0.0, -10.774, M_PI*0.5, shoulder_rot[0] -(M_PI*0.5) );
  R4Multiply( RA1, RA0, rot );

  get_icub_transform_matrix ( rot, 0.0, 0.0, -M_PI*0.5, shoulder_rot[1] - (M_PI*0.5) );
  R4Multiply( RA2, RA1, rot );
  
  apply_r_elbow_rotation( );
}

/* ----------------------------------------------------------------------- */
/*                       RIGHT ELBOW ROTATION                              */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_r_elbow_rotation( void ){

  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, 0.0, -15.228, -M_PI*0.5, shoulder_rot[2]-(ONE_PI*15.0)-(M_PI*0.5) );
  R4Multiply( RA3, RA2, rot );
  
  apply_r_wrist_rotation( );
}

/* ----------------------------------------------------------------------- */
/*                       RIGHT WRIST ROTATION                              */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_r_wrist_rotation( void ){
  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, 1.5, 0.0, M_PI*0.5, elbow_rot[0] );
  R4Multiply( RA4, RA3, rot );
  
  get_icub_transform_matrix ( rot, 0.0, -13.73, M_PI*0.5, wrist_rot[0] - (M_PI*0.5) );
  R4Multiply( RA5, RA4, rot );
  
}

/* ----------------------------------------------------------------------- */
/*                              NECK ROTATION                              */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_neck_rotation( void ){
  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, 0.0, -22.33, -M_PI*0.5, torso_rot[2]-(M_PI*0.5) );
  R4Multiply( N0, T2, rot );
  
  get_icub_transform_matrix ( rot, 0.95, 0.0, M_PI*0.5, neck_rot[0] + (M_PI*0.5) );
  R4Multiply( N1, N0, rot );
  
  get_icub_transform_matrix ( rot, 0.0, 0.0, -M_PI*0.5, neck_rot[1] - (M_PI*0.5) );
  R4Multiply( N2, N1, rot );

  
  apply_r_eye_rotation( );
  apply_l_eye_rotation( );
  apply_head_rotation( );
}

/* ----------------------------------------------------------------------- */
/*                                  HEAD ROTATION                          */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_head_rotation( void ){
  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, -5.09, 8.205, -M_PI*0.5, neck_rot[2]+(M_PI*0.5) );
  R4Multiply( HEAD, N2, rot );
}

/* ----------------------------------------------------------------------- */
/*                              RIGH EYE ROTATION                          */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_r_eye_rotation( void ){
  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, -5.09, 8.205, -M_PI*0.5, neck_rot[2]+(M_PI*0.5) );
  R4Multiply( RE0, N2, rot );
  
  get_icub_transform_matrix ( rot, 0.0, 3.4, -M_PI*0.5, r_eye_rot[0] );
  R4Multiply( RE1, RE0, rot );
  
  get_icub_transform_matrix ( rot, 0.0, 0.0, M_PI*0.5, r_eye_rot[1] - (M_PI*0.5) );
  R4Multiply( RE2, RE1, rot );
}

/* ----------------------------------------------------------------------- */
/*                              LEFT EYE ROTATION                          */
/* ----------------------------------------------------------------------- */
void MyIcub::apply_l_eye_rotation( void ){
  vector <double> rot;
  rot.assign(16, 0.0);
  get_icub_transform_matrix ( rot, -5.09, 8.205, -M_PI*0.5, neck_rot[2]+(M_PI*0.5) );
  R4Multiply( LE0, N2, rot );
  
  get_icub_transform_matrix ( rot, 0.0, -3.4, -M_PI*0.5, l_eye_rot[0] );
  R4Multiply( LE1, LE0, rot );
  
  get_icub_transform_matrix ( rot, 0.0, 0.0, M_PI*0.5, l_eye_rot[1] - (M_PI*0.5) );
  R4Multiply( LE2, LE1, rot );

}

/* ----------------------------------------------------------------------- */
/*                    openGL RENDERING FUNCTIONS                           */
/* ----------------------------------------------------------------------- */
//#ifdef _GRAPHICS_
void MyIcub::render( void ){
  vector <double> lengths, colour;
  lengths.assign(3, 0.0);
  colour.assign(3, 0.0);

  // dMatrix3 R3, N;
  vector <double> R3, N;
  R3.assign(12, 0.0);
  N.assign(12, 0.0);


  double *p = new double[3];
  float *m = new float[16];  
  
  //DRAW THE TORSO
  R4toR3andPOS(R3, p, T2/*RA0*/);
  lengths[0] = (10.774*2.0)-3;
  lengths[1] = 10.0;
  lengths[2] = (3.2+14.22);
  p[0] = 0.0;
  p[1] = 0.0;
  p[2] = torso_pos[2] + ((3.2+14.22)*0.5);
  colour[0] = 1.0;
  colour[1] = 0.0;
  colour[2] = 0.0;
  glColor3f(colour[0], colour[1], colour[2] );
  convert_rot_matrix_for_openGL( m, p, R3);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(m);
  //glTranslatef(0, -(0.8205-0.109),0);
  glScalef(lengths[0],lengths[1],lengths[2]);
  glutSolidCube(1.0f);
  glPopMatrix();
  glFlush();
  
  //DRAW THE NECK
  R4toR3andPOS(R3, p, RE0 );
  colour[0] = 0.0;
  colour[1] = 0.0;
  colour[2] = 1.0;
  p[0] = 0.0;
  p[1] = 0.0;
  p[2] = (torso_pos[2] + 22.33 + 3.2) - (22.23 - 14.33);
  lengths[0] = 1;
  lengths[1] = (0.95+8.205-5.09) + (22.23 - 14.33);
  lengths[2] = 1;
  //dRFromAxisAndAngle (N, 0.0, 0.0, 1.0, (M_PI*0.5) );
  getRMatrixFrom_Z_AxisAndAngle (N, M_PI*0.5 );

  convert_rot_matrix_for_openGL( m, p, N);
  draw_cylinder (p, m, lengths, colour );

  //DRAW THE HEAD 
  R4toR3andPOS(R3, p, HEAD );
  p[0] = 0.0;
  p[1] = 0.0;
  p[2] = (torso_pos[2] + 22.33 + 3.2) + (0.95);
  lengths[0] =  (5.09*2.0);
  lengths[1] =  (6.09*2.0);
  lengths[2] =  (5.09*2.0);
  convert_rot_matrix_for_openGL( m, p, R3);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(m);
  glTranslatef(0, -(8.205-1.09),0);
  glScalef(lengths[0],lengths[1],lengths[2]);
  glutSolidCube(1.0f);
  glPopMatrix();
  glFlush();

  //DRAW THE RIGHT ARM
  //dMatrix3 R3_b;
 /* vector <double> R3_b;
  R3_b.assign(12, 0.0);

  R4toR3andPOS(R3, p, RA0);
  R4toR3andPOS(R3_b, p, RA1);
  lengths[0] = 1;
  lengths[1] = 10.774;
  lengths[2] = 0.0;
  convert_rot_matrix_for_openGL( m, p, R3);
  draw_cylinder(p, m, lengths, colour );
  R4toR3andPOS(R3, p, RA2);
  R4toR3andPOS(R3_b, p, RA3);
  lengths[0] =  1;
  lengths[1] =  15.228;
  lengths[2] =  0.0;
  convert_rot_matrix_for_openGL( m, p, R3);
  draw_cylinder(p, m, lengths, colour );
  
  //DRAW THE RIGHT FOREARM
  R4toR3andPOS(R3, p, RA4);
  R4toR3andPOS(R3_b, p, RA5);
  lengths[0] =  1;
  lengths[1] =  13.73;
  lengths[2] =  0.0;
  convert_rot_matrix_for_openGL( m, p, R3);
  draw_cylinder(p, m, lengths, colour );*/
  
  //DRAW THE RIGHT HAND
  // colour[0] = 1.0;
//   colour[1] = 1.0;
//   colour[2] = 0.0;
//   glColor3f(colour[0], colour[1], colour[2] );
//   R4toR3andPOS(R3, p, RA5 );
//   //p[0] = 0.0;
//   //p[1] = 0.0;
//   //p[2] = (torso_pos[2] + 2.233 + 0.32) + (0.095);
//   lengths[0] =  (0.1*2.0);
//   lengths[1] =  (0.2*2.0);
//   lengths[2] =  (0.2*2.0);
//   convert_rot_matrix_for_openGL( m, p, R3);
//   glMatrixMode(GL_MODELVIEW);
//   glPushMatrix();
//   glMultMatrixf(m);
//   glTranslatef(0, -0.2, 0);
//   glScalef(lengths[0],lengths[1],lengths[2]);
//   glutSolidCube(1.0f);
//   glPopMatrix();
  
  // DRAW EYES
  //This is the copde for the right eye

  //This is the code for the ray coming out of the eye
  /*colour[0] = 1.0;
  colour[1] = 0.0;
  colour[2] = 0.0;
  lengths[0] =  0.1;
  lengths[1] =  r_visual_distance +100;
  lengths[2] =  0.0;
  p[0] = 0.0;
  p[1] = 0.0;
  p[2] = 0.0;
  R4toR3andPOS(R3, p, RE2);
  convert_rot_matrix_for_openGL( m, p, R3);
  draw_cylinder(p, m, lengths, colour );*/

  //This is the code for drawing the right eye
  /*colour[0] = 1.0;
  colour[1] = 1.0;
  colour[2] = 1.0; 
  glColor3f(colour[0], colour[1], colour[2] ); 
  lengths[0] =  0.8;
  convert_rot_matrix_for_openGL( m, p, R3);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(m);
  glutSolidSphere( lengths[0], 30, 30);
  glPopMatrix();
  glFlush();*/


  //This is the left eye
  /*colour[0] = 1.0;
  colour[1] = 0.0;
  colour[2] = 0.0;
  lengths[0] =  0.1; 
  lengths[1] =  l_visual_distance + 100;
  R4toR3andPOS(R3, p, LE2);
  convert_rot_matrix_for_openGL( m, p, R3);
  draw_cylinder(p, m, lengths, colour );

  colour[0] = 1.0;
  colour[1] = 1.0;
  colour[2] = 1.0;
  glColor3f(colour[0], colour[1], colour[2] ); 
  lengths[0] =  1;
  convert_rot_matrix_for_openGL( m, p, R3);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(m);
  glutSolidSphere( lengths[0], 30, 30);
  glPopMatrix();
  glFlush();*/


  //DRAW THE LEGS
  colour[0] = 1.0;
  colour[1] = 1.0;
  colour[2] = 1.0;
  lengths[0] = 8;
  lengths[1] = 10.0;
  lengths[2] = 30.0;
  glColor3f(colour[0], colour[1], colour[2] );
  //dRSetIdentity (N);
  set_R3_identity_matrix( N );


  p[0] = 0.0;
  p[1] = 0.0;
  p[2] = 0.0;
  convert_rot_matrix_for_openGL( m, p, T2);
  glPushMatrix();
  glMultMatrixf(m);
  glTranslatef(10.774-1.5-4, 0, -15.0);
  glScalef(lengths[0],lengths[1],lengths[2]);
  glutSolidCube(1.0f);
  glPopMatrix();
  glFlush();

  glPushMatrix();
  glMultMatrixf(m);
  glTranslatef(-(10.774-1.5-4), 0, -15.0);
  glScalef(lengths[0],lengths[1],lengths[2]);
  glutSolidCube(1.0f);
  glPopMatrix();
  glFlush();
  
  delete[] m;
  delete[] p;
}

void MyIcub::draw_cylinder( const double *p, const float *m, vector <double> dim, vector <double> colour ){
  double radius = dim[0];
  double length = dim[1];
  glColor3f(colour[0], colour[1], colour[2] );
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glMultMatrixf(m);
  
  //The following code draw the circular base of the cyclinder
  glBegin(GL_TRIANGLES);
  for (int i = 0; i<100; i++)
    {
      float n = i*(M_PI/50);
      //glColor3f((n/2),1-(n/2),sin(n));
      glVertex3f((radius*sin(n)),(radius*cos(n)), 0);
      n = (1+i)*(M_PI/50);
      glVertex3f((radius*sin(n)),(radius*cos(n)), 0);
      glVertex3f(0, 0, 0);
    }
  glEnd();
  
  //The following code draw the body of the cylinder
  GLUquadric* quad = gluNewQuadric();
  gluCylinder( quad, radius, radius, length, 30, 30 );
  gluDeleteQuadric( quad );
  
  //The followin code draw the circular top of the cylinder
  glTranslatef( 0, 0, length );
  glBegin(GL_TRIANGLES);
  for (int i = 0; i<100; i++)
    {
      float n = i*(M_PI/50);
      //glColor3f((n/2),1-(n/2),sin(n));
      glVertex3f((radius*sin(n)),(radius*cos(n)), 0);
      n = (1+i)*(M_PI/50);
      glVertex3f((radius*sin(n)),(radius*cos(n)), 0);
      glVertex3f(0, 0, 0);
    }
  glEnd();
  glPopMatrix();
  glFlush();
}
//#endif
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/*                             END GRAPHICS                                */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */



/* ----------------------------------------------------------------------- */
/*                              ICUB STUFF                                 */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
void MyIcub::get_icub_transform_matrix( vector <double> &rot, const double a, const double d, const double alpha, const double theta){
  rot[0] = cos(theta);
  rot[1] = -sin(theta)*cos(alpha);
  rot[2] = sin(theta)*sin(alpha);
  rot[3] = cos(theta)*a; // X position
  
  rot[4] = sin(theta);
  rot[5] = cos(theta)*cos(alpha);
  rot[6] = -cos(theta)*sin(alpha);
  rot[7] = sin(theta)*a; // Y position
  
  rot[8] = 0.0;
  rot[9] = sin(alpha);
  rot[10] = cos(alpha);
  rot[11] = d; //Z position

  rot[12] = 0.0;
  rot[13] = 0.0;
  rot[14] = 0.0;
  rot[15] = 1.0;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void MyIcub::compute_approx_version ( void ){
  version.clear();
  //TILT
  version.push_back( (l_eye_rot[0] + r_eye_rot[0])/2.0 );
  //PAN
  version.push_back( (l_eye_rot[1] + r_eye_rot[1])/2.0);
  
  // cerr << " APPROX V-PAN = "<< (approx_version[1]*180.0)/M_PI
  //   << " APPROX V-TILT = "<< (approx_version[0]*180.0)/M_PI
  //   << endl;
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void MyIcub::compute_vergence( void ){
  vergence = 0.0;
  if( !r_eye_bounds_reached[1] && !l_eye_bounds_reached[1] )
    vergence = l_eye_rot[1] - r_eye_rot[1];
  else vergence = 0.0;
  /* cerr << " vergence = " << ((vergence*180.0)/M_PI) */
  /* 	 << " PAN R = " <<  (r_eye_rot[1]*180.0)/M_PI << " PAN L = " << (l_eye_rot[1]*180.0)/M_PI */
  /* 	 << " TILT R = " <<  (r_eye_rot[0]*180.0)/M_PI << " TILT L = " << (l_eye_rot[0]*180.0)/M_PI */
  /* 	 << endl; */
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void MyIcub::compute_version( const vector <double> target_rot ){

  vector <double> transp;
  transp.assign(16, 0.0);
  get_R4transpose ( transp, HEAD );
  vector <double> element;
  element.assign(3, 0.0);
  
  element[0] = ( HEAD[3]  * HEAD[0] +
		 HEAD[7]  * HEAD[4] +
		 HEAD[11] * HEAD[8] );
  element[1] = ( HEAD[3]  * HEAD[1] +
		 HEAD[7]  * HEAD[5] +
		 HEAD[11] * HEAD[9] );
  element[2] = ( HEAD[3]  * HEAD[2] +
		 HEAD[7]  * HEAD[6] +
		 HEAD[11] * HEAD[10] );
  transp[3]  = -element[0];
  transp[7]  = -element[1];
  transp[11] = -element[2];
  transp[12] = 0.0;
  transp[13] = 0.0;
  transp[14] = 0.0;
  transp[15] = 1.0;
  vector <double> R4_res;
  R4_res.assign(16, 0.0);
  
  R4Multiply ( R4_res, transp, target_rot );

  version.clear();  
  //TILT                         y           x
  version.push_back(atan2(R4_res[7],  R4_res[3]) );
  
  //PAN                          z                y         y             x         x
  version.push_back(atan2(R4_res[11], sqrt((R4_res[7]*R4_res[7]) + (R4_res[3]*R4_res[3]) )) );
  
  if(version[0] <= 0.0 ){
    version[0] = -(M_PI + atan2(R4_res[7],  R4_res[3]));
  }
  else{
    version[0] = M_PI - atan2(R4_res[7],  R4_res[3]);
  }
  
  //cerr << " V-PAN = "<< (version[1]*180.0)/M_PI
  //   << " V-TILT = "<< (version[0]*180.0)/M_PI
  //<< " X = " << R4_res[3]
  //<< " Y = " << R4_res[7]
  // << " Z = " << R4_res[11]
  //   << endl;
}

/* ----------------------------------------------------------------------- */
void MyIcub::compute_target_visual_distance   ( const vector <double> target_rot ){ 
  r_visual_distance = 0.0;
  l_visual_distance = 0.0;

  //r_visual_distance
  if( r_eye_bounds_reached[0] || r_eye_bounds_reached[1] ){
    r_visual_distance = 100.0;
  }
  else{
    r_visual_distance = sqrt( ((RE2[3] - target_rot[3]) * (RE2[3] - target_rot[3])) +
			      ((RE2[7] - target_rot[7]) * (RE2[7] - target_rot[7])) +
			      ((RE2[11] - target_rot[11]) * (RE2[11] - target_rot[11])) );
  }

  //l_visual_distance
  if( l_eye_bounds_reached[0] || l_eye_bounds_reached[1] ){
    l_visual_distance = 100.0;
  }
  else{
    l_visual_distance = sqrt( ((LE2[3] - target_rot[3]) * (LE2[3] - target_rot[3])) +
			      ((LE2[7] - target_rot[7]) * (LE2[7] - target_rot[7])) +
			      ((LE2[11] - target_rot[11]) * (LE2[11] - target_rot[11])) );
  }
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void MyIcub::compute_target_eyes_pan_tilt_offsets ( const vector <double> target_rot ){
  target_eye_pan_tilt_distance   ( target_rot, RE2, r_pan_tilt_offset );
  target_eye_pan_tilt_distance   ( target_rot, LE2, l_pan_tilt_offset );
}
/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void MyIcub::compute_target_head_pan_tilt_offsets ( const vector <double> rot ){

  vector <double> R4EYE_transp;
  R4EYE_transp.assign(16, 0.0);

  get_R4transpose ( R4EYE_transp, HEAD );
  vector <double> R3Eye_transp;
  R3Eye_transp.assign(12, 0.0);

  double *pos = new double[3];
  R4toR3andPOS(R3Eye_transp, pos, R4EYE_transp);
  pos[0] = rot[3] - HEAD[3];
  pos[1] = rot[7] - HEAD[7];
  pos[2] = rot[11] - HEAD[11];
  double *res = new double[3];
  R3Vector3Multiply    ( res, R3Eye_transp, pos );
  delete[] pos;
  /*
    cerr << " res[0] " << res[0]  
    << " res[1] " << res[1]  
    << " res[2] " << res[2]  
    << endl;
  */

  head_pan_tilt_offset[1] = 0.0;

  //PAN
  head_pan_tilt_offset[2] = -atan2(res[2], sqrt((res[1]*res[1]) + (res[0]*res[0]) ));
  //TILT
  double mytest = atan2(res[0], res[1]);
  if( mytest > 0.0 ) mytest -= PI*0.5;
  else {
    mytest *= -1.0;
    mytest -= PI*0.5;
  }
  //cerr << " atan2 = " <<  mytest << endl;
  head_pan_tilt_offset[0] = mytest;

  delete[] res;
}

/* ----------------------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void MyIcub::compute_target_position_in_eye_coordinates( vector <double> &target_position, const vector<double>rot,const vector<double>rot_matrix){
  vector <double> R4EYE_transp;
  R4EYE_transp.assign(16, 0.0);
   get_R4transpose ( R4EYE_transp, rot_matrix );
  vector <double> R3Eye_transp;
  R3Eye_transp.assign(12, 0.0);
  double *pos = new double[3];
  R4toR3andPOS(R3Eye_transp, pos, R4EYE_transp);
  pos[0] = rot[3] - rot_matrix[3];
  pos[1] = rot[7] - rot_matrix[7];
  pos[2] = rot[11] - rot_matrix[11];
  double *res = new double[3];
  R3Vector3Multiply    ( res, R3Eye_transp, pos );
  target_position[0] = res[0];
  target_position[1] = res[1];
  target_position[2] = res[2];
  delete[] pos;
  delete[] res;


}



void MyIcub::target_eye_pan_tilt_distance( const vector <double> rot, const vector <double> rot_matrix, vector<double> &pan_tilt_offset ){
  
  vector <double> R4EYE_transp;
  R4EYE_transp.assign(16, 0.0);

  get_R4transpose ( R4EYE_transp, rot_matrix );
  vector <double> R3Eye_transp;
  R3Eye_transp.assign(12, 0.0);

  double *pos = new double[3];
  R4toR3andPOS(R3Eye_transp, pos, R4EYE_transp);
  pos[0] = rot[3] - rot_matrix[3];
  pos[1] = rot[7] - rot_matrix[7];
  pos[2] = rot[11] - rot_matrix[11];
  double *res = new double[3];
  R3Vector3Multiply    ( res, R3Eye_transp, pos );
  delete[] pos;
  
  //PAN
  pan_tilt_offset[1] = atan2(res[0], sqrt((res[1]*res[1]) + (res[2]*res[2]) ));
  //cerr << " pan = " << pan_tilt_offset[1] << endl;
  //TILT
  pan_tilt_offset[0] = -atan2(res[1], res[2]);
  //cerr << " tilt = " << pan_tilt_offset[0] << endl;
  delete[] res;
}
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */



