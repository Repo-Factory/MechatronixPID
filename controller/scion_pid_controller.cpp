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

    std::map<string, PID_Controller*> controllerMap = 
    {
        {"roll",  &this->roll_pid}, 
        {"pitch", &this->pitch_pid},
        {"yaw",   &this->yaw_pid},
        {"x_pos", &this->x_pos_pid},
        {"y_pos", &this->y_pos_pid},
        {"z_pos", &this->z_pos_pid},
    };

    this->controllers = controllerMap;
   

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

Scion_Position_PID_Controller::Scion_Position_PID_Controller(map<string, map<string, double>>& pid_params)
{
    Scion_Position_PID_Controller();

    // load pid parameter values from dictionary
    for (auto& ctrl_type : this->controllers)
    {
        this->controllers[ctrl_type.first]->k_p = pid_params[ctrl_type.first]["kp"];
        this->controllers[ctrl_type.first]->k_i = pid_params[ctrl_type.first]["ki"];
        this->controllers[ctrl_type.first]->k_d = pid_params[ctrl_type.first]["kd"];
        this->controllers[ctrl_type.first]->ctrl_val_offset = pid_params[ctrl_type.first]["ctrl_val_offset"];
        this->controllers[ctrl_type.first]->ctrl_val_max = pid_params[ctrl_type.first]["ctrl_val_max"];
        this->controllers[ctrl_type.first]->ctrl_val_min = pid_params[ctrl_type.first]["ctrl_val_min"];
        this->controllers[ctrl_type.first]->i_max = pid_params[ctrl_type.first]["i_max"];
        this->controllers[ctrl_type.first]->i_min = pid_params[ctrl_type.first]["i_min"];
    }
}

void Scion_Position_PID_Controller::getStatus()
{
    for (auto& ctrl_type : this->controllers)
    {
        cout << endl;
        cout << "Printing Data For " << ctrl_type.first << "Controller:" << endl;
        ctrl_type.second->getStatus();
    }

}
    //Initialize pid controllers
pair<vector<double>, vector<double>> Scion_Position_PID_Controller::update
    (
        vector<double> set_pos_point,
        vector<double> process_pos_point,
        double dt
    ) 
    {
        /**
        Perform PID controller update step and return the thrust to each of the 6 thrusters.
        
        :param set_point - The desired state of the vehicle [roll, pitch, yaw, x, y, z] 
        :param process_point - The current state of the vehicle [roll, pitch, yaw, x, y, z] 
        :param dt - Update interval in seconds (double)
        
        :return thrusts - A list of length 6 of the thrusts to apply to each motor: Range [-100, 100] 
        */
            
        pair<double, double> roll_ctrl_data = this->roll_pid.update(set_pos_point[0], process_pos_point[0], dt);
        double roll_ctrl_val = roll_ctrl_data.first;
        double roll_error = roll_ctrl_data.second;

        pair<double, double> pitch_ctrl_data = this->pitch_pid.update(set_pos_point[1], process_pos_point[1], dt);
        double pitch_ctrl_val = pitch_ctrl_data.first;
        double pitch_error = pitch_ctrl_data.second;

        pair<double, double> yaw_ctrl_data = this->yaw_pid.update(set_pos_point[2], process_pos_point[2], dt);
        double yaw_ctrl_val = yaw_ctrl_data.first;
        double yaw_error = yaw_ctrl_data.second;

        pair<double, double> x_pos_ctrl_data = this->x_pos_pid.update(set_pos_point[3], process_pos_point[3], dt);
        double x_pos_ctrl_val = x_pos_ctrl_data.first;
        double x_pos_error = x_pos_ctrl_data.second;

        pair<double, double> y_pos_ctrl_data = this->y_pos_pid.update(set_pos_point[4], process_pos_point[4], dt);
        double y_pos_ctrl_val = y_pos_ctrl_data.first;
        double y_pos_error = y_pos_ctrl_data.second;

        pair<double, double> z_pos_ctrl_data = this->z_pos_pid.update(set_pos_point[5], process_pos_point[5], dt);
        double z_pos_ctrl_val = z_pos_ctrl_data.first;
        double z_pos_error = z_pos_ctrl_data.second;

        vector<double> ctrl_vals = vector<double>
        {roll_ctrl_val, pitch_ctrl_val, yaw_ctrl_val, x_pos_ctrl_val, y_pos_ctrl_val, z_pos_ctrl_val};

        vector<double> pos_errors = vector<double>
        {roll_error, pitch_error, yaw_error, x_pos_error, y_pos_error, z_pos_error};
        
        // map the individual controller outputs to each thruster.

        cout << endl << endl;
        cout << "Control Values: " << endl;
        printVector(ctrl_vals);

        vector<double> thrusts = this->pid_thrust_mapper * ctrl_vals;

        pair<vector<double>, vector<double>> thrusts_and_errors{thrusts, pos_errors};

        return thrusts_and_errors;
    }


// Create a "velocity" pid control system for the Scion. There will be 6 controllers for
// (roll, pitch, yaw, x, y, z). These are the DOFs controllable by the actuator.


int main() 
{
    PID_Params pid_pirams_object;
    map<string, map<string, double>> pid_params = pid_pirams_object.get_pid_params();

    Scion_Position_PID_Controller controller = Scion_Position_PID_Controller();

    controller.getStatus();
    /**
     * Tune PID
    */

    controller.x_pos_pid.set_gains(.2,.13,.07);
    controller.y_pos_pid.set_gains(.3,.11,.04); 
    controller.z_pos_pid.set_gains(.15,.08,.02);  
    controller.roll_pid.set_gains(.2,.13,.07); 
    controller.pitch_pid.set_gains(.3,.11,.04); 
    controller.yaw_pid.set_gains(.15,.08,.02);
    

    controller.getStatus();


    pair<vector<double>, vector<double>> answer = controller.update
    (vector<double>{1.2, 2.4, 3.6, 4.8, 5.0, 6.1}, vector<double>{2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
    controller.getStatus();

    vector<double> thrusts = answer.first;
    vector<double> pos_errors = answer.second;

    cout << "Thrusts: ";
    printVector(thrusts);
    cout << "Error_Values: ";
    printVector(pos_errors);

    answer = controller.update
    (vector<double>{1.4, 2.6, 3.8, 4.9, 5.6, 6.6}, vector<double>{2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
    controller.getStatus();

    thrusts = answer.first;
    pos_errors = answer.second;

    cout << "Thrusts: ";
    printVector(thrusts);
    cout << "Error_Values: ";
    printVector(pos_errors);

    answer = controller.update
    (vector<double>{1.6, 2.8, 3.9, 5.0, 5.8, 6.8}, vector<double>{2.0, 3.0, 4.0, 5.0, 6.0, 7.0});
    controller.getStatus();

    thrusts = answer.first;
    pos_errors = answer.second;

    cout << "Thrusts: ";
    printVector(thrusts);
    cout << "Error_Values: ";
    printVector(pos_errors);
    
    return 0;
}