#include <iostream>
#include <vector>
#include <variant>

class FrontEndDeveloper
{
public:
    void develop() { developFrontEnd(); }
private:
    void developFrontEnd(){std::cout << "frontend" << std::endl;}
};

class BackEndDeveloper
{
public:
    void develop() { developBackEnd();}
private:
    void developBackEnd(){std::cout << "backend" << std::endl;}
};

template <typename... Devs>
class Project
{
public:
    using Developers = std::vector<std::variant<Devs...>>;

    explicit Project(Developers developers) 
        : developers_{std::move(developers)} {

    }

    void deliver(){
        for (auto &developer :  developers_){
            std::visit([](auto &dev){dev.develop(); }, developer);
        }
    } 

private:
    Developers developers_;
};

int main()
{
    using MyProject = Project<FrontEndDeveloper, BackEndDeveloper>;
    auto front = FrontEndDeveloper{};
    auto back = BackEndDeveloper{};
    auto new_project = MyProject{{front, back}};
    new_project.deliver();

    return 0;
}