#include "pid_controller.hpp"

using namespace std;

/** PID controller typically used in control feed back systems. */


PID_Controller::PID_Controller
    (
        double k_p, 
        double k_i, 
        double k_d, 
        double i_min, 
        double i_max, 
        double cmd_min, 
        double cmd_max, 
        double cmd_offset, 
        bool angle_wrap
    )

    {
        this->k_p = k_p;
        this->k_i = k_i;
        this->k_d = k_d;
        this->i_min = i_min;
        this->i_max = i_max;
        this->cmd_min = cmd_min;
        this->cmd_max = cmd_max;
        this->cmd_offset = cmd_offset;
        this->angle_wrap = angle_wrap;

        this->integral = 0.0;
        this->previous_error = 0.0;
    }

    void PID_Controller::set_gains(double k_p, double k_i, double k_d)
    {
        /**
        Reset the gain parameters.
        Parameters:
            k_p: Proportional gain
            k_i: Integral gain
            k_d: Derivative gain
        */
        this->k_p = k_p;
        this->k_i = k_i;
        this->k_d = k_d;
    }


    pair<double, double> PID_Controller::update(double set_point, double process_point, double dt)
    {
    /**
    Perfrom a control step to correct for error in control system.
    
    Parameters:
        set_point: The current state of the system
        process_point: The desired state of the system
        dt: The interval between update steps.
    Returns:
        cmd: A PID output control value to correct for error in system
    */
    
    //compute the error
    double error = process_point - set_point;
    
    //if error is for angular inputs, perform angle wrapping.
    if (this->angle_wrap)
    {
        if (error > M_PI)
        {
            error = error - 2 * M_PI;
        }
        else if (error < -1 * M_PI)
        {
            error = error + 2 * M_PI;

        }
    }
        
    double proportional = (this->k_p * error);  //proportional term

    this->integral = this->integral + (error * dt);
    
    if (this->i_min < this->i_max)
    {
        if (this->integral < this->i_min)
        {
            this->integral = this->i_min;
        }
        else if (this->integral > this->i_max)
        {
            this->integral = this->i_max;
        }
    }

    double integral = this->k_i * this->integral;

    double derivative = this->k_d * (error - this->previous_error) / dt;

    this->previous_error = error;

    double pre_cmd = proportional + integral + derivative;

    double cmd;

    if(pre_cmd >= 0)
    {
        cmd = pre_cmd + this->cmd_offset;
    }
    else
    {
        cmd = pre_cmd - this->cmd_offset;
    }

    if(this->cmd_min < this->cmd_max)
    {
        if(cmd < this->cmd_min)
        {
            cmd = this->cmd_min;
        }
        else if(cmd > this->cmd_max)
        {
            cmd = this->cmd_max;
        }
    }

    pair<double, double> ret_val(cmd, error);

    return ret_val;
}


// test
// int main()
// {
//     PID_Controller controller = PID_Controller(0.0F, 0.0F, 0.0F);

//     pair<double, double> cmd_error = controller.update(5.0F, 3.0F, .5);

//     std::cout << cmd_error.first;
//     std::cout << cmd_error.second;

//     return 0;
// }