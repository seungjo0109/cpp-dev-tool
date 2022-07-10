#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

// States name
std::vector<std::string> state_names{
  "off hook",
  "connecting",
  "connected",
  "on hold",
  "disconnected"
};

// State machine transition events
struct CallDialed {};
struct HungUp {};
struct CallConnected {};
struct PlacedOnHold {};
struct TakenOffHold {};
struct LeftMessage {};
struct CallDisconnect {};

// State machine
struct PhoneStateMachine : boost::msm::front::state_machine_def<PhoneStateMachine>
{
public:
    struct OffHook : boost::msm::front::state<> {};
    struct Connecting: boost::msm::front::state<>
    {
        template<class Event, class FSM>
        void on_entry(const Event &event, FSM &fsm)
        {
            std::cout << "Connecting state on entry\n";
        }

    };
    struct Connected : boost::msm::front::state<> {};
    struct OnHold : boost::msm::front::state<> {};
    struct PhoneDisconnected : boost::msm::front::state<> {};
    struct PhoneBeingDisconnected
    {
        template <class Event, class FSM, class SourceState, class TargetState>
        void operator()(Event const&, FSM&, SourceState&, TargetState&)
        {
            std::cout << "Disconnect phone" << std::endl;
        }
    };
    struct CanDisconnectPhone
    {
        template <class Event, class FSM, class SourceState, class TargetState>
        bool operator()(Event const&, FSM& fsm, SourceState&, TargetState&)
        {
            return fsm.disconnect;
        }
    };

    // State machine transition table
    struct transition_table : boost::mpl::vector<
        boost::msm::front::Row<OffHook, CallDialed, Connecting>,
        boost::msm::front::Row<Connecting, CallConnected, Connected>,
        boost::msm::front::Row<Connected, PlacedOnHold, OnHold>,
        boost::msm::front::Row<OnHold, CallDisconnect, PhoneDisconnected,
            PhoneBeingDisconnected, CanDisconnectPhone>>
    {};

    // starting state
    typedef OffHook initial_state;

    // what happens if there's nowhere to go
    template <class FSM, class Event>
    void no_transition(Event const& e, FSM&, int state)
    {
        std::cout << "No transition from state " << state_names[state]
        << " on event " << typeid(e).name() << std::endl;
    }

private:
    bool disconnect{true};
};