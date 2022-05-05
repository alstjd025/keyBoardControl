#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <ncurses.h>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "include/getKeyBoardInputnode.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */


/*
 space : 32
 w : 119
 1 : 49
 2 : 50
 3 : 51
*/
getKeyBoardInput::getKeyBoardInput()
: Node("minimal_publisher")
{
    publisher_speed = this->create_publisher<std_msgs::msg::Float32>("SPEED", 10);
    publisher_angle = this->create_publisher<std_msgs::msg::Float32>("ANGLE", 10);
    mcm_State = STANDBY;
    standby();
}

void getKeyBoardInput::standby()
{
    auto message_speed = std_msgs::msg::Float32();
    auto message_angle = std_msgs::msg::Float32();
    message_speed.data = 0;
    message_angle.data = 0;
    int key;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    printw("Arrow Up : ++5km/h Arrow Down : --5km/h\n");
    printw("Arrow Left : --5' Arrow Right : ++5'\n");
    printw("q : EXIT\n");
    while ((key = getch()) != 'q') {
        switch (mcm_State)
        {
        case MCMState::PIDControl:

            break;
        case MCMState::OVERRIDE:
            
            break;
        case MCMState::FAULT:

            break;
            
        default:
            break;
        }
        pidControlSequance(key);
        
    }
    refresh();
    endwin();
    std::cout << "End KeyBoard Input Control \n";
    message_speed.data = 0;
    message_angle.data = 0;
    std::cout << "Set Speed, Angle 0 \n";
    std::cout << "SPEED : " << message_angle.data <<" ANGLE : " << message_speed.data << "\n";    
    publisher_speed->publish(message_speed);
    publisher_angle->publish(message_angle);
    return;
}

void getKeyBoardInput::pidControlSequance(int key){
    switch(key) {
        case KEY_UP:
            if(message_speed.data < 100){ 
                message_speed.data += 5;
                printw("SPEED UP : %f \n" , message_speed.data);
                publisher_speed->publish(message_speed);
                //PUBLISH SPEED REF HERE
            }else{
                printw("SPEED CANNOT OVER 100km/h!! \n");
                message_speed.data = 100;
            }
            break;

        case KEY_DOWN:
            if(message_speed.data > 0){ 
                message_speed.data -= 5;
                printw("SPEED DOWN : %f \n" , message_speed.data);
                publisher_speed->publish(message_speed);
                //PUBLISH SPEED REF HERE
            }else{
                printw("SPEED CANNOT UNDER 0km/h!! \n");
                message_speed.data = 0;
            }
            break;

        case KEY_LEFT: 
            message_angle.data -= 5;
            printw("ANGLE LEFT : %f \n" , message_angle.data);
            publisher_angle->publish(message_angle);
            //PUBLISH ANGLE REF HERE
            break;

        case KEY_RIGHT:
            message_angle.data += 5;
            printw("ANGLE RIGHT : %f \n" , message_angle.data);
            publisher_angle->publish(message_angle);
            //PUBLISH ANGLE REF HERE
            break;

        default:
            clear();
            printw("Got %d \n", key);
            printw("Clear Terminal \n");
            printw("SPEED : %f, ANGLE : %f\n", message_speed.data, message_angle.data);
            break;
        }
}

int getKeyBoardInput::controlSelectSequance(int key){

}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<getKeyBoardInput>());
  rclcpp::shutdown();
  return 0;
}