#include "scion_pid_controller.hpp"

/** Create a "positional" pid control system for the Scion. This system constains a positional pid layer
  * that directly feeds into a velocity PID layer. There will be 6 directional controller for
  * (roll, pitch, yaw, x, y, z). These are the DOFs controllable by the actuator.
*/


Scion_Position_PID_Controller::Scion_Position_PID_Controller()
{
    this->roll_pid = PID_Controller(0.0, 0.0, 0.0);
    this->roll_pid.angle_wrap=true;
    this->pitch_pid = PID_Controller(0.0, 0.0, 0.0);
    this->pitch_pid.angle_wrap=true;
    this->yaw_pid = PID_Controller(0.0, 0.0, 0.0);
    this->yaw_pid.angle_wrap=true;

    this->x_pos_pid = PID_Controller(0.0, 0.0, 0.0);
    this->y_pos_pid = PID_Controller(0.0, 0.0, 0.0);
    this->z_pos_pid = PID_Controller(0.0, 0.0, 0.0);
    this->x_vel_pid = PID_Controller(0.0, 0.0, 0.0);
    this->y_vel_pid = PID_Controller(0.0, 0.0, 0.0);
    this->z_vel_pid = PID_Controller(0.0, 0.0, 0.0);

    this->controllers = 
    {
        {"roll", this->roll_pid}, 
        {"pitch", this->pitch_pid},
        {"yaw", this->yaw_pid},
        {"x_pos", this->x_pos_pid},
        {"y_pos", this->y_pos_pid},
        {"z_pos", this->z_pos_pid},
        {"x_vel", this->x_vel_pid},
        {"y_vel", this->y_vel_pid},
        {"z_vel", this->z_vel_pid},
    };
}

Scion_Position_PID_Controller::Scion_Position_PID_Controller(map<string, map<string, double>>& pid_params)
{
    this->roll_pid = PID_Controller(0.0, 0.0, 0.0);
    this->roll_pid.angle_wrap=true;
    this->pitch_pid = PID_Controller(0.0, 0.0, 0.0);
    this->pitch_pid.angle_wrap=true;
    this->yaw_pid = PID_Controller(0.0, 0.0, 0.0);
    this->yaw_pid.angle_wrap=true;

    this->x_pos_pid = PID_Controller(0.0, 0.0, 0.0);
    this->y_pos_pid = PID_Controller(0.0, 0.0, 0.0);
    this->z_pos_pid = PID_Controller(0.0, 0.0, 0.0);
    this->x_vel_pid = PID_Controller(0.0, 0.0, 0.0);
    this->y_vel_pid = PID_Controller(0.0, 0.0, 0.0);
    this->z_vel_pid = PID_Controller(0.0, 0.0, 0.0);

    this->controllers = 
    {
        {"roll", this->roll_pid}, 
        {"pitch", this->pitch_pid},
        {"yaw", this->yaw_pid},
        {"x_pos", this->x_pos_pid},
        {"y_pos", this->y_pos_pid},
        {"z_pos", this->z_pos_pid},
        {"x_vel", this->x_vel_pid},
        {"y_vel", this->y_vel_pid},
        {"z_vel", this->z_vel_pid},
    };

    // load pid parameter values from dictionary
    map<string, map<string, double>>* pid_params_ptr = &pid_params;

    if(pid_params_ptr != nullptr)
    {
        for (auto ctrl_type : this->controllers)
        {
            this->controllers[ctrl_type.first].k_p = pid_params[ctrl_type.first]["kp"];
            this->controllers[ctrl_type.first].k_i = pid_params[ctrl_type.first]["ki"];
            this->controllers[ctrl_type.first].k_d = pid_params[ctrl_type.first]["kd"];
            this->controllers[ctrl_type.first].cmd_offset = pid_params[ctrl_type.first]["cmd_offset"];
            this->controllers[ctrl_type.first].cmd_max = pid_params[ctrl_type.first]["cmd_max"];
            this->controllers[ctrl_type.first].cmd_min = pid_params[ctrl_type.first]["cmd_min"];
            this->controllers[ctrl_type.first].i_max = pid_params[ctrl_type.first]["i_max"];
            this->controllers[ctrl_type.first].i_min = pid_params[ctrl_type.first]["i_min"];
        }
    }
    // matrix mapping the 6 pid controller outputs to the 8 thrusters
    // -----roll---pitch---yaw---x---y---z
    //| T0
    //| T1
    //| T2
    //| T3
    //| T4
    //| T5
    //| T6
    //| T7
    
    this->pid_thrust_mapper = vector<vector<double>>
                                    {
                                        {-1,  1,  0,  0,  0,  1},
                                        { 0,  0,  1,  1,  1,  0},
                                        {-1, -1,  0,  0,  0,  1},
                                        { 0,  0,  1,  1, -1,  0},
                                        { 1, -1,  0,  0,  0,  1},
                                        { 0,  0, -1,  1,  1,  0},
                                        { 1,  1,  0,  0,  0,  1},
                                        { 0,  0, -1,  1, -1,  0}
                                    };
}


    //Initialize pid controllers
tuple<vector<double>, vector<double>, vector<double>> Scion_Position_PID_Controller::update
    (
        vector<double> set_pos_point,
        vector<double> process_pos_point, 
        vector<double> process_vel_point,
        double dt
    ) 
    {
        /**
        Perform PID controller update step and return the thrust to each of the 6 thrusters.
        
        :param set_point - The desired state of the vehicle [roll, pitch, yaw, x, y, z] (np.array)
        :param process_point - The current state of the vehicle [roll, pitch, yaw, x, y, z] (np.array)
        :param dt - Update interval in seconds (double)
        
        :return thrusts - A list of length 6 of the thrusts to apply to each motor: Range [-100, 100] (np.array)
        */
            
        pair<double, double> roll_cmd_error = this->roll_pid.update(set_pos_point[0], process_pos_point[0], dt);
        double roll_cmd = roll_cmd_error.first;
        double roll_error = roll_cmd_error.second;

        pair<double, double> pitch_cmd_error = this->pitch_pid.update(set_pos_point[1], process_pos_point[1], dt);
        double pitch_cmd = pitch_cmd_error.first;
        double pitch_error = pitch_cmd_error.second;

        pair<double, double> yaw_cmd_error = this->yaw_pid.update(set_pos_point[2], process_pos_point[2], dt);
        double yaw_cmd = yaw_cmd_error.first;
        double yaw_error = yaw_cmd_error.second;

        pair<double, double> x_pos_cmd_error = this->x_pos_pid.update(set_pos_point[3], process_pos_point[3], dt);
        double x_pos_cmd = x_pos_cmd_error.first;
        double x_pos_error = x_pos_cmd_error.second;

        pair<double, double> y_pos_cmd_error = this->y_pos_pid.update(set_pos_point[4], process_pos_point[4], dt);
        double y_pos_cmd = y_pos_cmd_error.first;
        double y_pos_error = y_pos_cmd_error.second;

        pair<double, double> z_pos_cmd_error = this->z_pos_pid.update(set_pos_point[5], process_pos_point[5], dt);
        double z_pos_cmd = z_pos_cmd_error.first;
        double z_pos_error = z_pos_cmd_error.second;

        
        pair<double, double> z_vel_cmd_error = this->z_vel_pid.update(z_pos_cmd, process_vel_point[5], dt);
        double z_vel_cmd = z_vel_cmd_error.first;
        double z_vel_error = z_vel_cmd_error.second; 


        vector<double> cmds = vector<double>{roll_cmd, pitch_cmd, yaw_cmd, 0.0, 0.0, z_vel_cmd};
        vector<double> pos_errors = vector<double>{roll_error, pitch_error, yaw_error, 0.0, 0.0, z_pos_error};
        vector<double> vel_errors = vector<double>{0.0, 0.0, 0.0, 0.0, 0.0, z_vel_error};
        
        // map the individual controller outputs to each thruster.
        vector<double> thrusts = this->pid_thrust_mapper * cmds;

        tuple<vector<double>, vector<double>, vector<double>> ret_val{thrusts, pos_errors, vel_errors};

        return ret_val;
    }


// Create a "velocity" pid control system for the Scion. There will be 6 controllers for
// (roll, pitch, yaw, x, y, z). These are the DOFs controllable by the actuator.


int main() 
{
    PID_Params pid_pirams_object;
    map<string, map<string, double>> pid_params = pid_pirams_object.get_pid_params();

    Scion_Position_PID_Controller controller = Scion_Position_PID_Controller(pid_params);
    tuple<vector<double>, vector<double>, vector<double>> answer = controller.update(vector<double>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0}, vector<double>{2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
    
    vector<double> thrusts = get<0>(answer);
    vector<double> pos_errors = get<1>(answer);
    vector<double> vel_errors = get<2>(answer);

    printVector(thrusts);
    printVector(pos_errors);
    printVector(vel_errors);
    
    return 0;
}