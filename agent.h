#pragma once
#include <iostream>
#include "environment.h"

using namespace std;

double max(double* arr)
{
    double max_val = -10000000.0000;
    int n = 4;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
            max_val = arr[i];
    }
    return max_val;
}

double argmax(double* arr)
{
    double max_val = -10000000.0000;
    int n = 4;
    int max_ind;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
            max_ind = i;
        }
    }
    return max_ind;
}

class Policy
{
public:
    int mapping[12];
    int num_states = 12;

    void setPolicy(int state, double* q_state)
    {
        int max_act = argmax(q_state);
        mapping[state] = max_act;
    }

    void printPolicy()
    {
        auto printAction = [](int act) 
        {
            switch (act)
            {
                case 1:
                    return 'R';
                case 0:
                    return 'U';
                case 2:
                    return 'D';
                case 3:
                    return 'L';
            }
        };

        for (int i = 0; i < num_states; i++)
        {
            if ((i % 4) == 0)
                cout << endl;
            cout << "[" << printAction(mapping[i]) << "]";
        }
        cout << endl;
    }
};

class Agent
{
public:
    Policy policy;
    double qval[12][4];
    double epsilon = 0.1;
    double alpha = 0.1;
    double gamma = 0.9;

    void initQValue()
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                double temp = (double)rand();
                qval[i][j] = temp;
            }
        }
    }

    int move(int s)
    {
        if ((double)rand() / RAND_MAX < epsilon)
            return rand() % 4;
        else
        {
            double action_value = 0;
            int best_action = 0;
            for (int i = 0; i < 4; i++) {
                if (qval[s][i] >= action_value)
                {
                    action_value = qval[s][i];
                    best_action = i;
                }
            }
            return best_action;
        }   
    }

    int playOne(Environment env)
    {
        bool done = false;
        EnvInfo env_inf = env.reset();
        State s = env_inf.state;
        int total_reward = 0;
        while (!done)
        {
            int a = this->move(s.id);
            env_inf = env.step(a);
            State s_prime = env_inf.state;
            int r = env_inf.reward;
            bool done = env_inf.done;
            //env.render();
            qval[s.id][a] = alpha * (r + (gamma * max(qval[s_prime.id])) - qval[s.id][a]);
            s = s_prime;
            total_reward += r;
            if (done)
                break;
        }
        return total_reward;
    }

    void printPolicy()
    {
        for (int i = 0; i < 12; i++)
        {
            policy.setPolicy(i, qval[i]);
        }
        policy.printPolicy();
    }
};