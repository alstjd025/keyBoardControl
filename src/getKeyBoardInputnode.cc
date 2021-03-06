#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <ncurses.h>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "../include/keyboardcontrol/getKeyBoardInputnode.hpp"

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
    : Node("KeyboardController")
{
    publisher_speed = this->create_publisher<ichthus_msgs::msg::Common>("ref_vel", 10);
    publisher_angle = this->create_publisher<ichthus_msgs::msg::Common>("ref_ang", 10);
    publisher_control_cmd = this->create_publisher<std_msgs::msg::Int32>("CONTROL_CMD", 10);
    publisher_external_cmd = this->create_publisher<std_msgs::msg::Int32>("extern_cmd", 10);

    mcm_state_sub = this->create_subscription<std_msgs::msg::Int32>(
        "mcm_status", 10, std::bind(&getKeyBoardInput::updateState, this, _1));

    v2x_sub = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "v2x", 10,  std::bind(&getKeyBoardInput::v2xCB, this, _1));

    mcm_State = STANDBY;
    message_speed.data = 0;
    message_angle.data = 0;
    cur_gear = 0;
    cur_gear_c = "P";

    thread j(&getKeyBoardInput::standby, this);
    j.detach();
}

void getKeyBoardInput::standby()
{
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    clear();
    while (returnState() != MCMState::QUIT)
    {
        MCMState tmp = returnState();
        switch (tmp)
        {
        case MCMState::STANDBY:
            controlSelectSequance();
            break;
        
        case MCMState::CONTROL_ENABLE:
            controllerSelectSequance();
            break;

        case MCMState::AUTOPILOT_STANDBY:
            printGearChangeAutopilot();
            break;

        case MCMState::KEYBOARDSET:
            printGearChangeKeyboard();
            break;

        case MCMState::AUTOPILOT_SET:
            controlStartSequance();
            break;

        case MCMState::AUTOPILOT_ON:
            printAutoPilotState();
            break;

        case MCMState::KEYBOARDON:
            pidControlSequance();
            break;

        case MCMState::OVERRIDE:
            printw("CASE OVERRIDE\n");
            refresh();
            message_speed.data = 0;
            //message_angle.data = 0;
            //publisher_angle->publish(message_angle);
            faultHandler();
            break;

        case MCMState::FAULT:
            // not used now
            break;

        default:
            break;
        }
    }
    return;
}

void getKeyBoardInput::pidControlSequance()
{
    clear();
    int key;
    message_angle.data = -cur_ang;
    //publisher_angle->publish(message_angle);
    auto message_control_cmd = std_msgs::msg::Int32();
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    while (key != 'q' && returnState() == MCMState::KEYBOARDON)
    {
        key = getch();
        if (returnState() != MCMState::KEYBOARDON)
        {
            return;
        }
        switch (key)
        {
            clear();
        case KEY_SPACE: // Brake for Gear Shift
            printw("Brake! \n");
            refresh();
            message_speed.data = -1;
            publisher_speed->publish(message_speed);
            message_speed.data = 0;
            break;

        case KEY_UP:
            if (message_speed.data < 100)
            {
                message_speed.data += VEL;
                printw("SPEED UP : %f \n", message_speed.data);
                refresh();
                publisher_speed->publish(message_speed);
                // PUBLISH SPEED REF HERE
            }
            else
            {
                printw("SPEED CANNOT OVER 100km/h!! \n");
                refresh();
                message_speed.data = 100;
            }
            break;

        case KEY_DOWN:
            if (message_speed.data > 0)
            {
                message_speed.data -= VEL;
                printw("SPEED DOWN : %f \n", message_speed.data);
                refresh();
                publisher_speed->publish(message_speed);
                // PUBLISH SPEED REF HERE
            }
            else
            {
                printw("SPEED CANNOT UNDER 0km/h!! \n");
                refresh();
                message_speed.data = 0;
            }
            break;

        case KEY_LEFT:
            message_angle.data -= ANG;
            printw("ANGLE LEFT : %f \n", message_angle.data);
            refresh();
            publisher_angle->publish(message_angle);
            // PUBLISH ANGLE REF HERE
            break;

        case KEY_RIGHT:
            message_angle.data += ANG;
            printw("ANGLE RIGHT : %f \n", message_angle.data);
            refresh();
            publisher_angle->publish(message_angle);
            // PUBLISH ANGLE REF HERE
            break;

        case KEY_Q:
            quitControl();
            break;

        case DOT:
            printw("Control Disable\n");
            refresh();
            message_control_cmd.data = 0;
            publisher_control_cmd->publish(message_control_cmd);
            ext_msg->data = SETPID::PID_OFF;
            publisher_external_cmd->publish(*ext_msg);
            break;

        case KEY_HOME:
            updateStateTo(MCMState::STANDBY);
            break;

        default:
            clear();
            printw("Got %d \n", key);
            printw("Clear Terminal \n");
            printw("SPEED : %f, ANGLE : %f\n", message_speed.data, message_angle.data);
            refresh();
            break;
        }
    }
    refresh();
    endwin();
}

void getKeyBoardInput::controlSelectSequance()
{
    auto message_control_cmd = std_msgs::msg::Int32();
    int key = getcontrolSelectKey();
    if (returnState() == MCMState::CONTROL_ENABLE)
    {
        return;
    }
    switch (key)
    {
    case KEY_1:
        printw("Enable ALL (ACC, BRK, STR) \n");
        refresh();
        message_control_cmd.data = 1;
        publisher_control_cmd->publish(message_control_cmd);
        break;

    case KEY_2:
        printw("Enable STR only \n");
        refresh();
        message_control_cmd.data = 2;
        publisher_control_cmd->publish(message_control_cmd);
        break;

    case KEY_3:
        printw("Enable ACC, BRK only \n");
        refresh();
        message_control_cmd.data = 3;
        publisher_control_cmd->publish(message_control_cmd);
        break;

    case KEY_Q:
        message_control_cmd.data = 0;
        publisher_control_cmd->publish(message_control_cmd);
        quitControl();
        break;

    default:
        printw("Got %d \n", key);
        refresh();
        break;
    }
    sleep(1);
}

void getKeyBoardInput::controllerSelectSequance()
{
    int key = getModeSelectKey();
    auto message_control_cmd = std_msgs::msg::Int32();
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    switch (key)
    {
    case KEY_1:
        printw("Autopilot selected\n");
        refresh();
        sleep(3);
        ext_msg->data = SETPID::PID_STANDBY;
        publisher_external_cmd->publish(*ext_msg);
        updateStateTo(MCMState::AUTOPILOT_STANDBY);
        
        break;
    case KEY_2:
        printw("Keyboard selected\n");
        refresh();
        sleep(3);
        ext_msg->data = SETPID::PID_STANDBY;
        publisher_external_cmd->publish(*ext_msg);
        updateStateTo(MCMState::KEYBOARDSET);
        break;
    case KEY_3:
        printw("Control Disable\n");
        refresh();
        message_control_cmd.data = 0;
        publisher_control_cmd->publish(message_control_cmd);
        break;
    
    case KEY_Q:
        quitControl();
        break;

    default:
        printw("Got %d \n", key);
        refresh();
        break;
    }
}

void getKeyBoardInput::controlStartSequance()
{
    int key = AutoPilotMenu();
    auto message_control_cmd = std_msgs::msg::Int32();
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    switch (key)
    {
    case KEY_1:
        ext_msg->data = SETPID::PID_ON;
        publisher_external_cmd->publish(*ext_msg);
        updateStateTo(MCMState::AUTOPILOT_ON);
        break;
    case KEY_2:
        printw("Control Disable\n");
        refresh();
        ext_msg->data = SETPID::PID_OFF;
        publisher_external_cmd->publish(*ext_msg);
        message_control_cmd.data = 0;
        publisher_control_cmd->publish(message_control_cmd);
        updateStateTo(MCMState::STANDBY);
    default:
        break;
    }
}

void getKeyBoardInput::overrideHandler()
{
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    ext_msg->data = SETPID::PID_OFF;
    publisher_external_cmd->publish(*ext_msg);
    clear();
    printw("Override Detected!! \n");
    printw("Override Detected!! \n");
    printw("Override Detected!! \n");
    printw("Press any key to continue\n");
    refresh();
}

void getKeyBoardInput::broadCastFault()
{
    // Broadcast Fault State to all nodes
}

MCMState getKeyBoardInput::returnState()
{
    MCMState tmp;
    MCM_State_Lock.lock();
    tmp = mcm_State;
    MCM_State_Lock.unlock();
    return tmp;
}

void getKeyBoardInput::updateState(const std_msgs::msg::Int32::SharedPtr msg)
{
    updateStateTo(msg->data);
    if (control_enabled == true)
    {
        printw("Control Enabled! \n");
        printw("Control Enabled! \n");
        printw("Control Enabled! \n");
        printw("Press any key to continue\n");
        refresh();
    }
    else if (msg->data == 2)
    {
        overrideHandler();
    }
}


void getKeyBoardInput::v2xCB(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
{
    switch (static_cast<int>(msg->data[1]))
    {
    case 5: //Drive
        cur_gear = 5;
        cur_gear_c = "D";
        break;
    case 0: //Parking
        cur_gear = 0;
        cur_gear_c = "P";
        break;
    case 6: //Reverse
        cur_gear = 6;    
        cur_gear_c = "N";
        break;
    case 7: //Neutral
        cur_gear = 7;
        cur_gear_c = "R";
        break;
    default:
        break;
    }
}

void getKeyBoardInput::updateStateTo(int state)
{
    MCM_State_Lock.lock();
    mcm_State = MCMState(state);
    if(mcm_State == MCMState::CONTROL_ENABLE){
        control_enabled = true;
    }
    else if(mcm_State == MCMState::STANDBY || mcm_State == MCMState::OVERRIDE ||\
           mcm_State == MCMState::FAULT || mcm_State == MCMState::QUIT){
        control_enabled = false;
    }
    refresh();
    MCM_State_Lock.unlock();
}

void getKeyBoardInput::faultHandler()
{

    refresh();
    if (returnState() == MCMState::OVERRIDE ||
        returnState() == MCMState::FAULT)
    {
        auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
        ext_msg->data = SETPID::PID_OFF;
        publisher_external_cmd->publish(*ext_msg);
        updateStateTo(MCMState::STANDBY);
    }
}

void getKeyBoardInput::quitControl()
{
    printw("QUIT CONTROL, SEND (0, 0) for speed & angle\n");
    printw("Terminate KeyboardInputNode after 5 sec\n");
    refresh();
    message_speed.data = 0;
    message_angle.data = 0;
    publisher_speed->publish(message_speed);
    publisher_angle->publish(message_angle);
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    ext_msg->data = SETPID::PID_OFF;
    publisher_external_cmd->publish(*ext_msg);
    sleep(5);
    endwin();
    exit(0);
}

void getKeyBoardInput::printDebug()
{
    clear();
    printw("=====[DEBUG]=====\n");
    printw("cur state : %d\n", returnState());
    refresh();
    sleep(3);

}

void getKeyBoardInput::printpidControlKey()
{
    clear();
    printw("=====[KEYBOARDCONTROL PID TEST]=====\n");
    printw("UP   :     REF SPEED +5 km/h \n");
    printw("DOWN :     REF SPEED -5 km/h \n");
    printw("RIGHT:     REF ANGLE +5 '    \n");
    printw("LEFT :     REF ANGLE -5 '    \n");
    printw("SPACE:     Brake             \n");
    refresh();
    sleep(3);
}

int getKeyBoardInput::getModeSelectKey()
{
    clear();
    printw("=====[MODE SELECT]=====\n");
    printw("1 : AUTOPILOT (Control by Autoware.univ - ICHTHUS) \n");
    printw("2 : KEYBOARD  (Control by KeyboardInput (DO NOT USE AUTOWARE) - USER) \n");
    printw("3 : Disable control & Return to fisrt step  \n");
    printw("Q : Quit \n");
    refresh();
    int key = getch();
    return key;
}

int getKeyBoardInput::AutoPilotMenu()
{
    clear();
    printw("=====[AUTOPILOT SET]=====\n");
    printw("1 : Start control \n");
    printw("2 : Disable control & Return to fisrt step  \n");
    refresh();
    int key = getch();
    return key;
}

void getKeyBoardInput::printAutoPilotState()
{
    auto message_control_cmd = std_msgs::msg::Int32();
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    clear();
    printw("=====[AUTOPILOT]=====\n");
    //printw("Current Velocity : %f km/h\n", cur_vel);
    //printw("Ref Velocity     : %f km/h\n", ref_vel);
    //printw("Current Steering Wheel Angle : %f deg\n", cur_ang);
    //printw("Ref Steering Wheel Angle     : %f deg\n", ref_ang);
    printw("Press Dot(') to disable autopilot\n");
    refresh();
    int key = getch();
    switch (key)
    {
    case DOT:
        ext_msg->data = SETPID::PID_OFF;
        publisher_external_cmd->publish(*ext_msg);
        message_control_cmd.data = 0;
        publisher_control_cmd->publish(message_control_cmd);
        updateStateTo(MCMState::STANDBY);
        break;
    
    default:
        break;
    }
}

void getKeyBoardInput::printGearChangeAutopilot()
{
    clear();
    printw("=====[AUTOPILOT STANDBY STEP]=====\n");
    printw("Please shift gear to D (drive) to continue\n");
    printw("Current gear : %c \n", *cur_gear_c);
    refresh();
    sleep(1);
    if(cur_gear == 5){
        sleep(1);
        updateStateTo(MCMState::AUTOPILOT_SET);
    }
}

void getKeyBoardInput::printGearChangeKeyboard()
{
    auto ext_msg = std_msgs::msg::Int32::SharedPtr(
                    new std_msgs::msg::Int32);
    clear();
    printw("=====[KEYBOARD STANDBY STEP]=====\n");
    printw("Please shift gear to D (drive) to continue\n");
    printw("Current gear : %c \n", *cur_gear_c);
    refresh();
    sleep(1);
    if(cur_gear == 5){
        sleep(1);
        updateStateTo(MCMState::KEYBOARDON);
        ext_msg->data = SETPID::PID_ON;
        publisher_external_cmd->publish(*ext_msg);
        printpidControlKey();
    }
}


int getKeyBoardInput::getcontrolSelectKey()
{
    clear();
    printw("=====[CONTROL SELECT]=====\n");
    printw("1 : Enable All (ACC, BRK, STR)\n");
    printw("2 : Enable STR only \n");
    printw("3 : Enable ACC, BRK only \n");
    printw("q : EXIT\n");
    refresh();
    int key = getch();
    return key;
}

getKeyBoardInput::~getKeyBoardInput()
{
    std::terminate();
}

int main(int argc, char *argv[])
{

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<getKeyBoardInput>());
    rclcpp::shutdown();
    return 0;
}
