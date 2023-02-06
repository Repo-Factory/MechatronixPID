#include <chrono>
#include <memory>
#include <ctime>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "rclcpp/rclcpp.hpp"
#include "robot_types/msg/position.hpp"             // Custom message types defined in time_types package
// #include "time_types/srv/convert_time.hpp"


using namespace std::chrono_literals;
using namespace std;

/**
 *  Node Subclass will post dummy data to be used by PID system
**/
class DummyBrain : public rclcpp::Node
{

public:
    DummyBrain() : Node("dummy_brain") 
    {
        /** 
         * Constructor creates publisher that sends int64 data (epoch time) 
         * and a timer that calls callback every 5 seconds 
        **/
        publisher_ = this->create_publisher<robot_types::msg::Position>("desired_position", 10);
        timer_ = this->create_wall_timer(10000ms, std::bind(&DummyBrain::timer_callback, this));
    }

private:
    /** 
     * DummyBrain() node subclass I made up must declare pointer fields to a timer and publisher object
    **/
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<robot_types::msg::Position>::SharedPtr publisher_;

    vector<double> generateRandomCoordinates()
    /** 
     * Helper function to return seconds passed since epoch - 0
     **/
    {   
        srand(time(0));
        double random_roll = (double)rand()/RAND_MAX*10;
        double random_pitch = (double)rand()/RAND_MAX*10;
        double random_yaw = (double)rand()/RAND_MAX*10;
        double randomX = (double)rand()/RAND_MAX*10;
        double randomY = (double)rand()/RAND_MAX*10;
        double randomZ = (double)rand()/RAND_MAX*10;
        vector<double> randomPosition{random_roll, random_pitch, random_yaw, randomX, randomY, randomZ};
        return randomPosition;
    }

    void printVector(vector<double> vector)
    {
        for (double number : vector)
        {
            std::cout << number << " " << endl;
        }
    }

    void publishMessage() 
    {
    /** 
    * First the publisher builds its message to send node2 by calling UnixEpochTime() (will look something like 160234897)
    * Also return message to be used by other functions that will make the request for conversion
    **/
        auto message = robot_types::msg::Position();
        message.position_vector = this->generateRandomCoordinates();
        RCLCPP_INFO(this->get_logger(), "Publishing Random Desired Coordinates: ");
        printVector(message.position_vector);     
        publisher_->publish(message);
    }

    void timer_callback()
    /** 
     * Function called from clock every five seconds
     * Executes helper functions to publish message, and then send/accept request for unix to human time conversion
    **/
    {
        publishMessage();
    }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<DummyBrain>()); // simply call constructor of DummySensor Node
  rclcpp::shutdown();
  return 0;
}