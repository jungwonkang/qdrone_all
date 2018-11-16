/** @ loc_core_void.h
 *  @ Feb, 2018
 *
 *  written by Jungwon Kang
 *
 */

#ifndef LOC_CORE_VOID_H
#define LOC_CORE_VOID_H


class Loc_core_void
{
  public:
    Loc_core_void();
    ~Loc_core_void();

    //// run
    void    run_loc(const double data_quar[]);

    //// get
    double  get_pose_uav_pos_x() { return pose_uav_pos_x; }
    double  get_pose_uav_pos_y() { return pose_uav_pos_y; }
    double  get_pose_uav_pos_z() { return pose_uav_pos_z; }

    double  get_pose_uav_ori_x() { return pose_uav_ori_x; }
    double  get_pose_uav_ori_y() { return pose_uav_ori_y; }
    double  get_pose_uav_ori_z() { return pose_uav_ori_z; }
    double  get_pose_uav_ori_w() { return pose_uav_ori_w; }

  private:
    double  pose_uav_pos_x;
    double  pose_uav_pos_y;
    double  pose_uav_pos_z;

    double  pose_uav_ori_x;
    double  pose_uav_ori_y;
    double  pose_uav_ori_z;
    double  pose_uav_ori_w;

};

#endif // LOC_CORE_VOID_H

