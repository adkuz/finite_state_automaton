#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>

#include "get_cpu_time.h"

#include "../src/ax_libs.hpp"
#include "../src/machines.hpp"
#include "../src/algorithms.hpp"



int main( int argc, char* argv[] )
{
    auto machine = ax::load_machine_from_file( std::string(argv[1]) );

    int exp_count = ( argc < 3 ) ? 20 : std::stoi( std::string(argv[2]) );

    auto labmda_sum = 0.0f;
    auto deter_sum = 0.0f;
    auto all_sum = 0.0f;

    for( int i = 0; i < exp_count ; ++i ) {
        auto t1 = getCPUTime();

        auto noe_machine = algs::to_no_lambda_mashine( machine );
        auto t2 = getCPUTime();

        auto det_mach = algs::determinization( machine );
        auto t3 = getCPUTime();

        labmda_sum += t2 - t1;
        deter_sum += t3 - t2;
        all_sum += t3 - t1;
    }

    std::cout << labmda_sum << "  " << deter_sum <<  "  " << all_sum << std::cout;

}
