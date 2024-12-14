#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
using namespace std;

int main()
{
    string input = "";
    string temp = "";
    vector<string> command;
    vector<char*> arguments;
    pid_t childPID;
    
    while (true)
    {
        cout << "Our Shell:>";
        getline(cin, input);
        
        if (input.empty())
        {
            continue;
        }
        temp = "";
        command.clear();
        arguments.clear();
        
        for (int i = 0; i < input.length(); i++)
        {
            if (input[i] == ' ')
            {
                if (!temp.empty())
                {
                    command.push_back(temp);
                    temp = "";
                }
            }
            else
            {
                temp += input[i];
            }
        }

        if (!temp.empty())
        {
            command.push_back(temp);
        }

        for (auto& cmd:command)
        {
            arguments.push_back(const_cast<char*>(cmd.c_str()));
        }
        arguments.push_back(NULL);
        
        childPID = fork();
        if(childPID == 0)
        {
            if(command.empty())
            {
                cout << endl;
            }
            else
            {
                if(command[0] == "exit")
                {
                    exit(0);
                }
                if (execvp(arguments[0], arguments.data()) == -1) 
                {
                    cout << "Invalid Command" << endl;
                }
            }
        } 
        else if(childPID > 0)
        {
            wait(NULL);
        }
    }
    
    return 0;
}