You call constructor of Scion_Position_PID_Controller

This makes a bunch of PID controller objects for all the axes of the robot so now you have:

    roll
    pitch
    yaw
    x
    y
    z

each being monitored by a PID


Each of these PIDs carries a bunch of information tp perform the calculation like:

    k_p
    k_i
    k_d
    i_min
    i_max
    cmd
    angle_wrap

etc.....


These have default values, but you can use a parameter guide to set all of these PIDs, so you may start roll with its attributes like:

    k_p = 2.0
    k_i = 1.0
    k_d = 5.0

etc........


So now, your PIDs are waiting for information. 

Your sensor and brain send you information on the current and desired points. 

This may look like:
    
    current - [1,1,1,0,1,1]
    desired - [1,1,1,5,1,1]

This means you have to move 5 in the x direction



So you call Scion_Position_PID_Controller.update() with four parameters, current_point, desired_point, current_vel, time interval

The first three parameters are each any array of six pieces of information (like shown above)



The Scion_PID object sends each of these PIDs the information they need in one array. So Scion PID gets 6 values, and each 1 of those values goes to a different PID object. Once these PIDs get passed information about current and desired point, the PIDs work by calling an update function.

This update function takes in a current point, desired point, and time interval BUT this time it only takes it for ONE dimension (for example, just in the x direction or just y direction)

This means that a single PID determines its movement by calling update which let's say x right now is 5 and we want it to be ten. It does its calcuation by finding the error between 5 and 10 and performing PID algorithm stuff. It then outputs **cmd which is a PID control value that attempts to fix the error** along with the error that was reported.


So who gets this output? Well good question, that would be the Scion_PID who called the PIDs update function in its OWN update function, the point of this is to get all PID information at once. So each PID has now sent a control value back up to Scion_PID_Controller object. 

