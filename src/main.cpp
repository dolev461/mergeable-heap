#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "[!] Usage: ./main.exe OPERATION_FILE\n";
        return 1;
    }

    ifstream ops_file(argv[1]);
    string op;

    while (getline(ops_file, op)) {
        cout << op << std::endl;
    }

    return 0;
}
