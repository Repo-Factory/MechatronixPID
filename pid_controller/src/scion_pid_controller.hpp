#include <map>
#include <string>
#include <utility>
#include <tuple>

#include "pid_controller.hpp"
#include "pid_params.hpp"
#include "/home/conner/mechatronics/pid/helpers/vector_operations.hpp"

using namespace std;

/** Create a "positional" pid control system for the Scion. This system constains a positional pid layer
  * that directly feeds into a velocity PID layer. There will be 6 directional controller for
  * (roll, pitch, yaw, x, y, z). These are the DOFs controllable by the actuator.
*/

class Scion_Position_PID_Controller
{
    public:
        PID_Controller roll_pid;
        PID_Controller pitch_pid;
        PID_Controller yaw_pid;
        PID_Controller x_pos_pid;
        PID_Controller y_pos_pid;
        PID_Controller z_pos_pid;
        PID_Controller x_vel_pid;
        PID_Controller y_vel_pid;
        PID_Controller z_vel_pid;
        std::map<string, PID_Controller*>* controllers;
        vector<vector<double>> pid_thrust_mapper;

        Scion_Position_PID_Controller();
        Scion_Position_PID_Controller(map<string, map<string, double>>& pid_params);
    
        //Initialize pid controllers
        pair<vector<double>, vector<double>> update
            (
                vector<double> set_pos_point=vector<double>{0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
                vector<double> process_pos_point=vector<double>{0.0, 0.0, 0.0, 0.0, 0.0, 0.0}, 
                double dt=0.010
            );

        void getStatus();

    private:
        

// Create a "velocity" pid control system for the Scion. There will be 6 controllers for
// (roll, pitch, yaw, x, y, z). These are the DOFs controllable by the actuator.

};