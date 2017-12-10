#include "src/ax_libs.hpp"
#include "src/machines.hpp"
#include "src/algorithms.hpp"


int main(int argc, char* argv[])
{
    auto machine = ax::load_machine_from_file(argv[1]);

    std::cout << machine << std::endl;
    return 0;
}
