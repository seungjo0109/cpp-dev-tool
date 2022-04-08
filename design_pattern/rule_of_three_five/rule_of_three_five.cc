#include <iostream>
#include <memory>

class PotentiallyMisleading
{
public:
    PotentiallyMisleading(){std::cout << " PotentiallyMisleading constructor" << std::endl;}
    PotentiallyMisleading(const PotentiallyMisleading &) = default;
    PotentiallyMisleading& operator=(const PotentiallyMisleading&) = default;
    PotentiallyMisleading(PotentiallyMisleading &&) = default;
    PotentiallyMisleading& operator=(PotentiallyMisleading &&) = default;
    ~PotentiallyMisleading(){ std::cout << " PotentiallyMisleading destructor" << std::endl; }

private:
    std::unique_ptr<int> int_;
};

class RuleOfZero
{
    std::unique_ptr<int> int_;
};

class RuleOfThree
{
public:
    RuleOfThree(){ std::cout << " RuleOfThree constructor" << std::endl; }
    RuleOfThree(const RuleOfThree &) = delete;
    RuleOfThree& operator=(const RuleOfThree &) = delete;
    ~RuleOfThree(){ std::cout << " RuleOfThree destructor" << std::endl; }
};

class RuleOfFive
{
public:
    RuleOfFive(){ std::cout << " RuleOfFive constructor" << std::endl; }
    RuleOfFive(const RuleOfFive &) = delete;
    RuleOfFive& operator=(const RuleOfFive &) = delete;
    RuleOfFive(RuleOfFive &&) = delete;
    RuleOfFive& operator=(RuleOfFive &&) = delete;
    ~RuleOfFive(){ std::cout << " RuleOfFive destructor" << std::endl; }
};

int main()
{
    PotentiallyMisleading ptr_potentially_misleading;
    // PotentiallyMisleading ptr_potentially_misleading2 = ptr_potentially_misleading;   // compile-error: this is because of unique_ptr

    RuleOfZero ptr_rule_zero;
    // RuleOfZero ptr_rule_zero2 = ptr_rule_zero;                                       // compile-error
    RuleOfZero ptr_rule_zero3 = std::move(ptr_rule_zero);


    RuleOfThree ptr_rule_three;
    // RuleOfThree ptr_rule_three2 = ptr_rule_three;                                    // compile-error
    // RuleOfThree ptr_rule_three3 = std::move(ptr_rule_three);                         // compile-error

    RuleOfFive ptr_rule_five;
    // RuleOfFive ptr_rule_five2 = ptr_rule_five;                                       // compile-error
    // RuleOfFive ptr_rule_five3 = std::move(ptr_rule_five);                            // compile-error

    return 0;
}