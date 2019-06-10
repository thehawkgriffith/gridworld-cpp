#pragma once
#include <iostream>
#include <string>

using namespace std;

class State 
{
public:
    bool terminal, active;
    int id, reward;
    int possible_moves[4], pm_loc=-1;
    string rep;

    void getConfig(int i) 
    {
        id = i;
        terminal = false;
        active = true;
        rep = "[ ]";
        reward = -1;
    }

    void addPossibleMove(int i)
    {
        pm_loc++;
        possible_moves[pm_loc] = i;
    }
};

class EnvInfo 
{
public:
    State state;
    int reward;
    bool done;

    EnvInfo(State s, int r, bool d)
    {
        state = s;
        reward = r;
        done = d;
    }
};

class Environment 
{
public:
    int num_states = 12, agent_loc = 8;
    State states[12];

    Environment() 
    {
        for (int i = 0; i < num_states; i++)
            states[i].getConfig(i);
        states[3].terminal = true;
        states[3].rep = "[T]";
        states[3].reward = 5;
        states[5].active = false;
        states[5].rep = "[#]";
        states[7].terminal = true;
        states[7].rep = "[X]";
        states[7].reward = -5;
        for (int i = 0; i < num_states; i++)
        {
            switch (i)
            {
            case 1:
            case 2:
                states[i].addPossibleMove(2);
                states[i].addPossibleMove(3);
                states[i].addPossibleMove(1);
                break;
            case 6:
                states[i].addPossibleMove(0);
                states[i].addPossibleMove(1);
                states[i].addPossibleMove(2);
                states[i].addPossibleMove(3);
                break;
            case 9:
            case 10:
                states[i].addPossibleMove(3);
                states[i].addPossibleMove(1);
                states[i].addPossibleMove(0);
                break;
            case 4:
                states[i].addPossibleMove(1);
                states[i].addPossibleMove(0);
                states[i].addPossibleMove(2);
                break;
            case 0:
                states[i].addPossibleMove(2);
                states[i].addPossibleMove(1);
                break;
            case 8:
                states[i].addPossibleMove(0);
                states[i].addPossibleMove(1);
                break;
            case 11:
                states[i].addPossibleMove(0);
                states[i].addPossibleMove(3);
                break;
            default:
                break;
            }
        }
    }

    void render() 
    {
        cout << "--Current State--" << endl;
        string strings[num_states];
        for (int i = 0; i < num_states; i++)
            strings[i] = states[i].rep;
        strings[agent_loc] = "[o]";
        for (int i = 0; i < num_states; i++) 
        {
            if ((i % 4) == 0)
                cout << endl;
            cout << strings[i];
        }
        cout << "\n-----------------" << endl;
    }

    EnvInfo step(int action)
    {   
        bool valid = false;
        for (int i = 0; i < 4; i++) 
        {
        if (states[agent_loc].possible_moves[i] == action)
            valid = true;
        }
        if (valid)
        {
        switch (action)
        {
        case 0:
            agent_loc -= 4;
            if (!states[agent_loc].active)
                agent_loc += 4;
            break;
        case 1:
            agent_loc += 1;
            if (!states[agent_loc].active)
                agent_loc -= 1;
            break;
        case 2:
            agent_loc += 4;
            if (!states[agent_loc].active)
                agent_loc -= 4;
            break;
        case 3:
            agent_loc -= 1;
            if (!states[agent_loc].active)
                agent_loc += 1;
            break;
        default:
            throw "Invalid action error.";
        }
        }
        int curr_reward = states[agent_loc].reward;
        bool curr_done = states[agent_loc].terminal;
        return EnvInfo(states[agent_loc], curr_reward, curr_done);
    }

    EnvInfo reset()
    {
        agent_loc = 0;
        return EnvInfo(states[agent_loc], 0, false);
    }

    void display()
    {
        for (int i = 0; i < num_states; i++)
        {
            cout << "ID: " << states[i].id << " Done: " << states[i].terminal << " Reward: " <<states[i].reward << endl;
        }
    }
};