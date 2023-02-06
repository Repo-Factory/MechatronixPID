#include "pid_params.hpp"

PID_Params::PID_Params()

{
    this->roll = 
    {
        {"kp", 0.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 0.0},
        {"cmd_max", 1.0},
        {"cmd_min", -1.0},
        {"i_max", -1.0},
        {"i_min", 1.0}
    };

    this->pitch = 
    {
        {"kp", 1.0},
        {"ki", 0.01},
        {"kd", 0.0},
        {"cmd_offset", 15.0},
        {"cmd_max", 2.0},
        {"cmd_min", -2.0},
        {"i_max", -1.0},
        {"i_min", 1.0}
    };


    this->yaw = 
    {
        {"kp", 2.0},
        {"ki", 0.05},
        {"kd", 0.0},
        {"cmd_offset", 10.0},
        {"cmd_max", 35.0},
        {"cmd_min", -35.0},
        {"i_max", 1},
        {"i_min", -1}
    };
    
    this->x_pos =
    {
        {"kp", 0.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 0.0},
        {"cmd_max", 60.0},
        {"cmd_min", -60.0},
        {"i_max", -1.0},
        {"i_min", 1.0}
    };


    this->y_pos = 
    {
        {"kp", 0.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 16.0},
        {"cmd_max", 100.0},
        {"cmd_min", -100.0},
        {"i_max", -1.0},
        {"i_min", 1.0}
    };

    this->z_pos =
    {
        {"kp", 1.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 20.0},
        {"cmd_max", 100.0},
        {"cmd_min", -100.0},
        {"i_max", -1.0},
        {"i_min", 1.0}
    };

    this->x_vel =
    {
         {"kp", 20.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 0.0},
        {"cmd_max", 60.0},
        {"cmd_min", -60.0},
        {"i_max", -1.0},
        {"i_min", 1.0}     
    };


    this->y_vel = 
    {
        {"kp", 0.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 0.0},
        {"cmd_max", 60.0},
        {"cmd_min", -60.0},
        {"i_max", -1.0},
        {"i_min", 1.0}    
    };

    this->z_vel =
    {
        {"kp", 1.0},
        {"ki", 0.0},
        {"kd", 0.0},
        {"cmd_offset", 4.0},
        {"cmd_max", 60.0},
        {"cmd_min", -60.0},
        {"i_max", -1.0},
        {"i_min", 1.0}
    };

    this->pid_params = 
    {
        {"roll", this->roll},
        {"pitch", this->pitch},
        {"yaw", this->yaw},
        {"x_pos", this->x_pos},
        {"y_pos", this->y_pos},
        {"z_pos", this->z_pos},
        {"x_vel", this->x_vel},
        {"y_vel", this->y_vel},
        {"z_vel", this->z_vel},
    };
}

map<string, map<string, double>> PID_Params::get_pid_params()
    {
        return this->pid_params;
    }


