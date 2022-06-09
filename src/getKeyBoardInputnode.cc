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
    : Node("minimal_publisher")
{
    publisher_speed = this->create_publisher<std_msgs::msg::Float64>("ref_vel", 10);
    publisher_angle = this->create_publisher<std_msgs::msg::Float64>("ref_ang", 10);
    publisher_control_cmd = this->create_publisher<std_msgs::msg::Int32>("CONTROL_CMD", 10);
    publisher_external_cmd = this->create_publisher<std_msgs::msg::Int32>("EXTERN_CMD", 10);

    mcm_state_sub = this->create_subscription<std_msgs::msg::Int32>(
        "mcm_status", 10, std::bind(&getKeyBoardInput::updateState, this, _1));

    sas_angle_sub = this->create_subscription<std_msgs::msg::Float64MultiArray>(
        "SAS11", 10, std::bind(&getKeyBoardInput::updateCurAngle, this, _1));


    mcm_State = STANDBY;
    message_speed.data = 0;
    message_angle.data = 0;

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

        case MCMState::PIDControl:
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
    printpidControlKey();
    message_angle.data = -cur_angle;
    clear();
    printw("cur angle : %f\n", cur_angle);
    refresh();
    //publisher_angle->publish(message_angle);
    auto message_control_cmd = std_msgs::msg::Int32();
    while (key != 'q' && returnState() == MCMState::PIDControl)
    {
        key = getch();
        if (returnState() != MCMState::PIDControl)
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
    if (returnState() == MCMState::PIDControl)
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

void getKeyBoardInput::overrideHandler()
{
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
    if (msg->data == 1)
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

void getKeyBoardInput::updateCurAngle(const std_msgs::msg::Float64MultiArray::SharedPtr msg)
{
    auto whl_ang = msg->data.begin();
    cur_angle = *whl_ang;
}

void getKeyBoardInput::updateStateTo(int state)
{
    MCM_State_Lock.lock();
    mcm_State = MCMState(state);
    refresh();
    MCM_State_Lock.unlock();
}

void getKeyBoardInput::faultHandler()
{

    refresh();
    if (returnState() == MCMState::OVERRIDE ||
        returnState() == MCMState::FAULT)
    {
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
    sleep(5);
    endwin();
    exit(0);
}

void getKeyBoardInput::printpidControlKey()
{
    printw("=====[PID TEST]=====\n");
    printw("UP   :     REF SPEED +5 km/h \n");
    printw("DOWN :     REF SPEED -5 km/h \n");
    printw("RIGHT:     REF ANGLE +5 '    \n");
    printw("LEFT :     REF ANGLE -5 '    \n");
    printw("SPACE:     Brake             \n");
    refresh();
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
