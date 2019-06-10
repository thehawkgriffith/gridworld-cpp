#include <iostream>
#include "agent.h"
#include "environment.h"

int main()
{
    Environment env;
    Agent agent;
    agent.initQValue();
    for (int i = 0; i < 100; i++)
    {
        int rew = agent.playOne(env);
        cout<< "Reward this episode: " << rew << endl;
    }
    agent.printPolicy();
}