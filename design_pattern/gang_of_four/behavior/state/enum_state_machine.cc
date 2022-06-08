#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

enum class State
{
    OffHook,
    Connecting,
    Connected,
    OnHold,
    OnHook
};

inline std::ostream& operator<<(std::ostream& os, const State& state)
{
    switch (state)
    {
    case State::OffHook:
        os << "off the hook";
        break;
    case State::Connecting:
        os << "connecting";
        break;
    case State::Connected: 
        os << "connected";
        break;
    case State::OnHold:
        os << "on hold";
        break;
    case State::OnHook:
        os << "on the hook";
        break;
    }
    return os;
}

enum class Trigger
{
    CallDialed,
    HungUp,
    CallConnected,
    PlacedOnHold,
    TakenOffHold,
    LeftMessage,
    StopUsingPhone
};

inline std::ostream& operator<<(std::ostream& os, const Trigger& trigger)
{
    switch (trigger)
    {
    case Trigger::CallDialed:
        os << "call dialed";
        break;
    case Trigger::HungUp:
        os << "hung up";
        break;
    case Trigger::CallConnected:
        os << "call connected";
        break;
    case Trigger::PlacedOnHold:
        os << "placed on hold";
        break;
    case Trigger::TakenOffHold:
        os << "taken off hold";
        break;
    case Trigger::LeftMessage: 
        os << "left message";
        break;
    case Trigger::StopUsingPhone:
        os << "putting phone on hook";
        break;
    default: break;
    }
    return os;
}


int main(int arc, char** argv)
{
    std::map<State, std::vector<std::pair<Trigger, State>>> rules;

    rules[State::OffHook] = {
        {Trigger::CallDialed, State::Connecting},
        {Trigger::StopUsingPhone, State::OnHook}
    };

    rules[State::Connecting] = {
        {Trigger::HungUp, State::OffHook},
        {Trigger::CallConnected, State::Connected}
    };

    rules[State::Connected] = {
        {Trigger::LeftMessage, State::OffHook},
        {Trigger::HungUp, State::OffHook},
        {Trigger::PlacedOnHold, State::OnHold}
    };

    rules[State::OnHold] = {
        {Trigger::TakenOffHold, State::Connected},
        {Trigger::HungUp, State::OffHook}
    };

    State currentState{ State::OffHook },
            exitState{ State::OnHook };

    while (true)
    {
        std::cout << "The phone is currently " << currentState << std::endl;
    select_trigger:
        std::cout << "Select a trigger:" << std::endl;

        int i = 0;
        for (auto item : rules[currentState]){
        std::cout << i++ << ". " << item.first << std::endl;
        }

        int input;
        std::cin >> input;
        if (input < 0 || (input+1) > rules[currentState].size()){
            std::cout << "Incorrect option. Please try again." << std::endl;
            goto select_trigger;
        }

        currentState = rules[currentState][input].second;
        if (currentState == exitState) break;
    }

    std::cout << "We are done using the phone" << std::endl;

    getchar();
    getchar();
    return 0;
}