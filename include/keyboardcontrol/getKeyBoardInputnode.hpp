#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <ncurses.h>
#include <iostream>
#include <mutex>
#include <unistd.h>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float64_multi_array.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::thread;

#define KEY_SPACE 32
#define KEY_Q     113
#define KEY_W     119
#define KEY_1     49
#define KEY_2     50
#define KEY_3     51
#define DOT       46

#define ANG       13
#define VEL       5

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */


/*
 space : 32
 w : 119
 1 : 49
 2 : 50
 3 : 51
*/

// Save MCM State in enum 
// for
// 0 : MCM in READY (Standby)
// 1 : MCM in PID control
// 2 : MCM in Override (similar as fault)
// 3 : MCM in Fault

enum MCMState{
  STANDBY,
  CONTROL_ENABLE,
  OVERRIDE,
  FAULT,
  QUIT,
  AUTOPILOT_STANDBY,
  AUTOPILOT_SET,
  AUTOPILOT_ON,
  WAITGEAR,
  KEYBOARDSET,
  KEYBOARDON,
};

enum SETPID{
  PID_STANDBY = 1,
  PID_ON ,
  PID_OFF,
};

class getKeyBoardInput : public rclcpp::Node
{
  public:
    
    std_msgs::msg::Float64 message_speed;
    std_msgs::msg::Float64 message_angle;
    std_msgs::msg::Int32 message_control_cmd;
    std_msgs::msg::Int32 message_external_cmd;
  
    getKeyBoardInput();
    ~getKeyBoardInput();
  
    void standby();
    void controlSelectSequance();
    void controllerSelectSequance();
    void controlStartSequance();

    int getcontrolSelectKey();  
    void pidControlSequance();
    void printpidControlKey();
    void printGearChangeAutopilot();
    void printGearChangeKeyboard();
    int getModeSelectKey();
    int AutoPilotMenu();
    void printAutoPilotState();
    void printDebug();


    void overrideHandler();
    void faultHandler();
    void broadCastFault();


    void quitControl();

    //Use this function as callback for mcm_state Subscriptor
    void updateState(const std_msgs::msg::Int32::SharedPtr msg);
    void updateCurAngle(const std_msgs::msg::Float64MultiArray::SharedPtr msg);

    void v2xCB(const std_msgs::msg::Float64MultiArray::SharedPtr msg);
    void curAngCB(const std_msgs::msg::Float64::SharedPtr msg);
    void curVelCB(const std_msgs::msg::Float64::SharedPtr msg);

    void refAngCB(const std_msgs::msg::Float64::SharedPtr msg);
    void refVelCB(const std_msgs::msg::Float64::SharedPtr msg);



    void externCMD();

    MCMState returnState();

    void updateStateTo(int state);

  private:
    bool control_enabled;
    int cur_gear;
    char* cur_gear_c;

    float cur_vel;
    float cur_ang;
    float ref_ang;
    float ref_vel;

    MCMState mcm_State;
    std::mutex MCM_State_Lock;
    std::mutex General_State_Lock;


    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_speed;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_angle;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_control_cmd;
    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_external_cmd;

    //MCM State Subscription. Subject to change.
    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr mcm_state_sub;
    rclcpp::Subscription<std_msgs::msg::Float64MultiArray>::SharedPtr v2x_sub;

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr cur_angle_sub;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr cur_vel_sub;

    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr ref_angle_sub;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr ref_vel_sub;
};
