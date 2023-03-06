Normal People Talk For How This Actually Works
______________________________________________________


You call a "constructor" of Scion_Position_PID_Controller which is just a function that initializes it

"Initialize" meaning that it makes a bunch of PID controller objects for all the axes of the robot so now you have:

    roll
    pitch
    yaw
    x
    y
    z

each being monitored by a PID (objects just means they are recognized by the program and storing data)

Each of these PIDs carries a bunch of information to perform the calculation like:

    k_p     }
    k_i     }   These are set when tuning
    k_d     }
    i_min
    i_max
    ctrl_val
    angle_wrap

etc.....


These have default values, but you can use a parameter guide to set all of these PIDs, so you may start roll with its attributes like:

    k_p = .4
    k_i = .21
    k_d = .05

etc........


So now, your PIDs are waiting for information. 

Your sensor and brain send you information on the current and desired points. 

This may look like:
    
    current - [1,1,1,0,1,1]
    desired - [1,1,1,5,1,1]

This means you have to move 5 in the x direction



So you call Scion_Position_PID_Controller.update() with three parameters, current_point, desired_point, time interval

The first two parameters are each any array of six pieces of information (like shown above)



The Scion_PID object sends each of these PIDs the information they need in one array. So Scion PID gets arrays with 6 values, and each 1 of those values goes to a different PID object. Once these PIDs get passed information about current and desired point, the PIDs work by calling an update function.

This update function takes in a current point, desired point, and time interval BUT this time it only takes it for ONE dimension (for example, just in the x direction or just y direction)

This means that a single PID determines its movement by calling update which let's say x right now is 5 and we want it to be ten. It does its calcuation by finding the error between 5 and 10 and performing PID algorithm stuff. It then outputs **ctrl_val which is a PID control value that attempts to fix the error** along with the error that was reported.


So who gets this output? Well good question, that would be the Scion_PID who called the PIDs update function in its OWN update function, the point of this is to get all PID information at once. So each PID has now sent a control value back up to Scion_PID_Controller object. The PID_Controller does matrix multiplication ( I used operator overloading for multiplying 2D and 1D vector ;) ) with the thrust mapper to get some thrust values to give to the 8 - you guessed it - thrusters.


General PID Algorithm to study (may or may not be directly copied from ChatGPT)

Here is a simple implementation of a PID controller in C++:


#include <iostream>
#include <cmath>

class PIDController
{
public:
    PIDController(double kp, double ki, double kd)
        : kp(kp), ki(ki), kd(kd), prevError(0), integral(0)
    {
    }

    double control(double setPoint, double processVariable)
    {
        // Calculate error
        double error = setPoint - processVariable;

        // Calculate integral
        integral += error;

        // Calculate derivative
        double derivative = error - prevError;

        // Save error for next iteration
        prevError = error;

        // Return control signal
        return kp * error + ki * integral + kd * derivative;
    }

private:
    double kp, ki, kd;
    double prevError, integral;
};

int main()
{
    // Create PID controller with gains
    PIDController pid(1.0, 0.1, 0.01);

    // Set point
    double setPoint = 10.0;

    // Process variable (simulated with a sine wave)
    double processVariable = sin(0.1 * M_PI);

    // Calculate control signal
    double controlSignal = pid.control(setPoint, processVariable);

    // Print control signal
    std::cout << "Control signal: " << controlSignal << std::endl;

    return 0;
}


In a PID (proportional-integral-derivative) controller, kp, ki, and kd are constants that determine the behavior of the controller.

kp (proportional gain) determines the proportion of the control signal that is proportional to the error between the set point and the process variable. The larger the value of kp, the stronger the controller will respond to the error.

ki (integral gain) determines the proportion of the control signal that is proportional to the integral of the error over time. This term helps to eliminate any residual error that may be present after the proportional term has done its job.

kd (derivative gain) determines the proportion of the control signal that is proportional to the rate of change of the error. This term helps to reduce overshoot and oscillations in the control signal, by predicting the future error based on the current rate of change.

By tuning the values of kp, ki, and kd, you can adjust the behavior of the PID controller to best control the system being regulated.

So it's more or less the same algorithm implementated in the PID_Controller update function.
It just looks different because of on when the constants are applied.
