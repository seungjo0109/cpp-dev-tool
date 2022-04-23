#include <iostream>
#include <memory>
#include <map>

class Receiver
{
public:
    void RunCommandA() { std::cout << "Run command A" << std::endl; }
    void RunCommandB() { std::cout << "Run command B" << std::endl; }
};

class CommandBase
{
public:
    virtual void Execute(){};
};

class CommandA : public CommandBase
{
public:
    CommandA(std::shared_ptr<Receiver> receiver) : receiver_(receiver) {}
    virtual void Execute() override { receiver_->RunCommandA(); }
private:
    std::shared_ptr<Receiver> receiver_{nullptr};
};

class CommandB : public CommandBase
{
public:
    CommandB(std::shared_ptr<Receiver> receiver) : receiver_(receiver) {}
    virtual void Execute() override { receiver_->RunCommandB(); }
private:
    std::shared_ptr<Receiver> receiver_{nullptr};
};

class CommandInvoker
{
public:
    enum class CommandType
    {
        A,
        B,
    };

    void RegisterCommand(CommandType type, std::shared_ptr<CommandBase> command)
    {
        commands_[type] = command;
    }
    void Execute(CommandType type)
    {
        switch(type){
            case CommandType::A:
                commands_[CommandType::A]->Execute();
                break;
            case CommandType::B:
                commands_[CommandType::B]->Execute();
                break;
        }
    }
    void ExecuteAll()
    {
        auto iter = commands_.begin();
        while(iter != commands_.end()){
            iter->second->Execute();
            iter++;
        }
    }

private:
    std::map<CommandType, std::shared_ptr<CommandBase>> commands_;
};