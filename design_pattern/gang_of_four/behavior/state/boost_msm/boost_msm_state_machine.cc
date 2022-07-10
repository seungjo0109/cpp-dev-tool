#include "boost_msm_state_machine.hpp"

int main()
{
    boost::msm::back::state_machine<PhoneStateMachine> phone;

    auto info = [&]()
    {
        auto i = phone.current_state()[0];
        std::cout << "The phone is currently " << state_names[i] << "\n";
    };

    // State transtion according to transition table
    info();
    phone.process_event(CallDialed{});
    info();
    phone.process_event(CallConnected{});
    info();
    phone.process_event(PlacedOnHold{});
    info();
    phone.process_event(CallDisconnect{});
    info();

    // Try transition disconnected to connected
    phone.process_event(CallDialed{});

    return 0;
}