#include "command.hpp"

int main()
{
    auto receiver = std::make_shared<Receiver>();
    auto commnad_a = std::make_shared<CommandA>(receiver);
    auto commnad_b = std::make_shared<CommandB>(receiver);
    auto invoker = std::make_shared<CommandInvoker>();

    invoker->RegisterCommand(CommandInvoker::CommandType::A ,commnad_a);
    invoker->RegisterCommand(CommandInvoker::CommandType::B, commnad_b);

    invoker->Execute(CommandInvoker::CommandType::A);
    invoker->Execute(CommandInvoker::CommandType::B);
    invoker->ExecuteAll();

    return 0;
}