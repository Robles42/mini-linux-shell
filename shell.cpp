#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string input) {
    stringstream ss(input);
    vector<string> tokens;
    string token;

    while (ss >> token)
        tokens.push_back(token);

    return tokens;
}

int main() {

    string input;

    while (true) {

        cout << "santi-shell$ ";
        getline(cin, input);

        if (input == "exit")
            break;

        vector<string> args = split(input);

        if (args.size() == 0)
            continue;

        if (args[0] == "cd") {
            chdir(args[1].c_str());
            continue;
        }

        pid_t pid = fork();

        if (pid == 0) {

            vector<char*> c_args;

            for (auto &arg : args)
                c_args.push_back(&arg[0]);

            c_args.push_back(NULL);

            execvp(c_args[0], c_args.data());

            perror("exec failed");
            exit(1);
        }

        else {
            wait(NULL);
        }
    }

    return 0;
}
