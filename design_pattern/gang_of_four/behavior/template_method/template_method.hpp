#pragma once

#include <iostream>

class Game
{
public:
    Game(int num_of_players) : num_of_players_(num_of_players) {}

    void Run()
    {
        Start();
        while(!HaveWinner()){
            TakeTurn();
        }
        std::cout << "Player " << GetWinner() << " wins!\n"; 
    }

protected:
    virtual void Start() = 0;
    virtual bool HaveWinner() = 0;
    virtual void TakeTurn() = 0;
    virtual int GetWinner() = 0;

    int current_player_{0};
    int num_of_players_;
};

class Chess : public Game
{
public:
    Chess() : Game(2) {}

protected: 
    virtual void Start() override
    {
        std::cout << "Starting a game of chess with " << num_of_players_ << " players\n";
    }
    virtual bool HaveWinner() override
    {
        return turn_ == max_turns_;
    }
    virtual void TakeTurn() override
    {
        std::cout << "Turn " << turn_ << " taken by player " << current_player_ << "\n";
        ++turn_;
        current_player_ = (current_player_ + 1) % num_of_players_;
    }
    virtual int GetWinner() override
    {
        return current_player_;
    }

private:
    int turn_{0}, max_turns_{10};

};