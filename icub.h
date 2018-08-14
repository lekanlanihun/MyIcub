#ifndef _MY_ICUB_
#define _MY_ICUB_

#include "world_entity.h"

//#ifdef _GRAPHICS_
#include <GL/glut.h> // use this on rooster
//#endif

#define EPSILON_ICUB 0.000017453
//#define M_PI  3.141592654

enum {TORSO=0, R_SHOULDER=1, R_ELBOW=2, R_WRIST=3, NECK=4, R_EYE=5, L_EYE=6, BOTH_EYES=7};

using namespace std;
 
class MyIcub : public World_Entity 
{
  
 private:
  double* torso_pos;

 public:
  MyIcub( );
  ~MyIcub();
  MyIcub(const MyIcub& other);
  MyIcub& operator=(const MyIcub &other);
  void init( void );
  void copy(const MyIcub &other);
  void destroy();
  
  
  inline void  set_pos                     ( const int which_joint, const vector <double> &pos ){
    init_pos_and_joints_rotation( pos );
  };

  inline void  set_rot                     ( const int which_joint, const vector <double> &rot ){
    set_joint_current_rotation( which_joint, rot );
  };

  inline void  update_rot                     ( const int which_joint, const vector <double> &rot ){
    update_joint_current_rotation ( which_joint, rot );
  };


  inline const vector <double> get_pos     ( const int which_joint ){};
  inline const vector <double> get_tmp_pos ( const int which_joint ){};
  inline const vector <double> get_dim     ( const int which_joint ){};
  inline const vector <double> get_colour  ( const int which_joint ){};
  inline const vector <double> get_rot     ( const int which_joint ){
    switch( which_joint )
      {
      case TORSO:
	{
	  return get_torso_rot_joints_rotation();
	  break;
	}
      case R_WRIST:
	{
	  return get_wrist_rot_joints_rotation();
	  break;
	}
      case NECK:
	{
	  return get_neck_rot_joints_rotation();
	  break;
	}
      case R_SHOULDER:
	{
	  return get_r_shoulder_joints_rotation();
	  break;
	}
      case R_ELBOW:
	{
	  return get_r_elbow_joints_rotation();
	  break;
	}
      case R_EYE:
	{
	  return get_r_eye_joints_rotation();
	  break;
	}
      case L_EYE:
	{
	  return get_l_eye_joints_rotation();
	  break;
	}
      defualt:
	{
	  std::cerr << " The joint specified does not exist " << std::endl;
	}
      }
  };
  inline const double          get_safe_dist ( void ){};

  void init_pos_and_joints_rotation( const vector <double> &pos );
  void reset_joints_to_init_angles ( void  );

  void set_joint_current_rotation      (const int which_joint, const vector <double> &updates );
  void set_torso_current_rotation      (const vector <double> &updates );
  void set_r_shoulder_current_rotation (const vector <double> &updates );
  void set_r_elbow_current_rotation    (const vector <double> &updates );
  void set_r_wrist_current_rotation    (const vector <double> &updates );
  void set_neck_current_rotation       (const vector <double> &updates );
  void set_eyes_current_rotation       (const vector <double> &r_updates, const vector <double> &l_updates);
  void set_right_eye_current_rotation  ( const vector <double> &r_updates );
  void set_left_eye_current_rotation   ( const vector <double> &l_updates );
  
  void update_joint_current_rotation      (const int which_joint, const vector <double> &updates );
  void update_torso_current_rotation      (const vector <double> &updates );
  void update_r_shoulder_current_rotation (const vector <double> &updates );
  void update_r_elbow_current_rotation    (const vector <double> &updates );
  void update_r_wrist_current_rotation    (const vector <double> &updates );
  void update_neck_current_rotation       (const vector <double> &updates );
  void update_eyes_current_rotation       (const vector <double> &r_updates, const vector<double> &l_updates);
  void update_right_eye_current_rotation  (const vector <double> &r_updates);
  void update_left_eye_current_rotation   (const vector<double> &l_updates);
  
  void apply_torso_rotation         ( void );
  void apply_r_shoulder_rotation    ( void );
  void apply_r_elbow_rotation       ( void );
  void apply_r_wrist_rotation       ( void );
  void apply_neck_rotation          ( void );
  void apply_head_rotation          ( void );
  void apply_r_eye_rotation         ( void );
  void apply_l_eye_rotation         ( void );
  
  //#ifdef _GRAPHICS_
  void render( void );
  void draw_cylinder( const double *p, const float *m, vector <double> dim, vector <double> colour );
  //#endif
  
  void get_icub_transform_matrix            ( vector <double> &rot, const double a, const double d, const double alpha, const double theta);
  void target_eye_pan_tilt_distance         ( const vector <double> rot, const vector <double> rot_matrix, vector<double> &pan_tilt_offset );
  void compute_target_visual_distance       ( const vector <double> target_rot );
  void compute_target_eyes_pan_tilt_offsets ( const vector <double> target_rot );
  void compute_target_head_pan_tilt_offsets ( const vector <double> target_rot );
  void compute_version                      ( const vector <double> target_rot );
  void compute_approx_version               ( void );
  void compute_vergence                     ( void );
  void compute_target_position_in_eye_coordinates(vector <double> &target_position, const vector<double> target_rot,const vector<double>rot_matrix); 
  
  inline vector <double> get_torso_rot_joints_rotation  ( void ) {return torso_rot; }
  inline vector <double> get_wrist_rot_joints_rotation  ( void ) {return wrist_rot; }
  inline vector <double> get_neck_rot_joints_rotation   ( void ) {return neck_rot; }
  inline vector <double> get_r_shoulder_joints_rotation ( void ) {return shoulder_rot; }
  inline vector <double> get_r_elbow_joints_rotation    ( void ) {return elbow_rot; }
  inline vector <double> get_r_eye_joints_rotation      ( void ) {return r_eye_rot; }
  inline vector <double> get_l_eye_joints_rotation      ( void ) {return l_eye_rot; }

  inline vector <bool> get_joint_bounds_reached( const int which_joint ){
    switch( which_joint ){
    case TORSO:
      return get_torso_bounds_reached();
      break;
    case R_SHOULDER:
      return get_shoulder_bounds_reached();
      break;
    case R_ELBOW:
      return get_elbow_bounds_reached();
      break;
    case R_WRIST:  
      return get_wrist_bounds_reached();
      break;
    case NECK:
      return get_neck_bounds_reached();
      break;
    default:
      cerr << " In get_joint_bounds_reached - A joints has to be specified " << endl;
      exit(0);
      break;
    }
  }
  inline vector <bool>  get_torso_bounds_reached( void ) { return torso_bounds_reached; }
  inline vector <bool>  get_shoulder_bounds_reached( void ) { return shoulder_bounds_reached; }
  inline vector <bool>  get_elbow_bounds_reached( void ) { return elbow_bounds_reached; }
  inline vector <bool>  get_wrist_bounds_reached( void ) { return wrist_bounds_reached; }
  inline vector <bool>  get_neck_bounds_reached( void ) { return neck_bounds_reached; }
  inline vector <bool>  get_r_eye_bounds_reached( void ) { return r_eye_bounds_reached; }
  inline vector <bool>  get_l_eye_bounds_reached( void ) { return l_eye_bounds_reached; }

  inline bool get_eyes_bounds_reached( void ){
    if( r_eye_bounds_reached[0] ||
	r_eye_bounds_reached[1] ||
	l_eye_bounds_reached[0] ||
	l_eye_bounds_reached[1] )
      return true;
    else false;
  }

  inline double get_vergence( void ){ return vergence;}
  inline double get_version ( int d ){ return version[d];}
  inline double get_approx_version ( int d ){ return approx_version[d];}
  inline vector <double> get_r_pan_tilt_offset( void ) {return r_pan_tilt_offset;}
  inline vector <double> get_l_pan_tilt_offset( void ) {return l_pan_tilt_offset;}
  inline vector <double> get_head_pan_tilt_offset( void ) {return head_pan_tilt_offset;}

  vector <double> T0, T1, T2;// torso T0 = pitch T1 = yaw and T2 = roll
  vector <double> RA0, RA1, RA2, RA3, RA4, RA5; //RA = right arm joints
  vector <double> N0, N1, N2; //N=neck
  vector <double> RE0, RE1, RE2; //RE = Right Eye
  vector <double> LE0, LE1, LE2; //LE = Left Eye
  vector <double> HEAD;

  vector <double> torso_rot;
  vector <double> shoulder_rot;
  vector <double> elbow_rot;
  vector <double> wrist_rot;
  vector <double> neck_rot;
  vector <double> r_eye_rot;
  vector <double> l_eye_rot;

  vector <bool> torso_bounds_reached;
  vector <bool> shoulder_bounds_reached;
  vector <bool> elbow_bounds_reached;
  vector <bool> wrist_bounds_reached;
  vector <bool> neck_bounds_reached;
  vector <bool> r_eye_bounds_reached;
  vector <bool> l_eye_bounds_reached;

  bool   r_eye_beyond_tilt_bounds;
  bool   r_eye_beyond_pan_bounds;
  double r_visual_distance;
  bool   l_eye_beyond_tilt_bounds;
  bool   l_eye_beyond_pan_bounds; 
  double l_visual_distance;

  vector <double> r_pan_tilt_offset;
  vector <double> l_pan_tilt_offset;
  vector <double> head_pan_tilt_offset;
  vector <double> approx_version;
  vector <double> version;
  double vergence;

  static constexpr double l_torso_pitch = -((22.0 * ONE_PI)+ EPSILON_ICUB);//low bound fro torso pitch movement
  static constexpr double h_torso_pitch =  (70.0 * ONE_PI)+ EPSILON_ICUB; //high bound for torse pitch movement
  static constexpr double l_torso_roll  = -((30.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_torso_roll  =  (30.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_torso_yaw   = -((50.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_torso_yaw   =  (50.0 * ONE_PI)+ EPSILON_ICUB;

  static constexpr double l_neck_pitch = -((35.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_neck_pitch =  (20.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_neck_roll  = -((40.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_neck_roll  =  (40.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_neck_yaw   = -((50.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_neck_yaw   =  (50.0 * ONE_PI)+ EPSILON_ICUB;

  /* ---- RIGTH SIDE OF THE AGENTS ---- */
  static constexpr double l_r_shoulder_pitch = -((95.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_shoulder_pitch =  (10.0 * ONE_PI) + EPSILON_ICUB;
  static constexpr double l_r_shoulder_roll  =  ( 5.0 * ONE_PI) - EPSILON_ICUB;
  static constexpr double h_r_shoulder_roll  =  (145.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_r_shoulder_yaw   = -((35.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_shoulder_yaw   =  (75.0 * ONE_PI) + EPSILON_ICUB;
  
  static constexpr double l_r_elbow_pitch =  (15.0 * ONE_PI) - EPSILON_ICUB;
  static constexpr double h_r_elbow_pitch =  (105.0 * ONE_PI)+ EPSILON_ICUB;

  static constexpr double l_r_wrist_pitch = -((90.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_wrist_pitch =  (90.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_r_wrist_roll  = -((90.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_wrist_roll  =  (90.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_r_wrist_yaw   = -((90.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_wrist_yaw   =  (90.0 * ONE_PI)+ EPSILON_ICUB;
  
  static constexpr double l_r_eye_pan  = -((30.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_eye_pan  =  (30.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_r_eye_tilt = -((38.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_r_eye_tilt =  (18.0 * ONE_PI)+ EPSILON_ICUB;

  static constexpr double l_l_eye_pan  = -((30.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_l_eye_pan  =  (30.0 * ONE_PI)+ EPSILON_ICUB;
  static constexpr double l_l_eye_tilt = -((38.0 * ONE_PI)+ EPSILON_ICUB);
  static constexpr double h_l_eye_tilt =  (18.0 * ONE_PI)+ EPSILON_ICUB;
  
  /* ---- LEFT SIDE OF THE AGENTS ---- */

};


#endif
