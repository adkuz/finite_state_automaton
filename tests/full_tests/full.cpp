#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <regex>

#include "../../src/machines.hpp"
#include "../../src/algorithms.hpp"

#include "../main_test.hpp"


static const std::map<std::string, std::string>
    re_to_files = {
        { "tests/full_tests/machines/001.fsa", "(1|2)(00)+((11)+|2)" },
        { "tests/full_tests/machines/002.fsa", "(000(00)*|010|0|1(00)*)" },
        { "tests/full_tests/machines/003.fsa", "(00|1)*" },
    };

TEST_CASE( "Testing like a god" )
{
    std::srand( 42 );
    auto seq_number = 100'000; //cool!!!
    auto max_seq_length = 20;

    using sequence_t = std::vector<size_t>;
    auto generate_sequence = []( size_t n, size_t k )
        {
            auto sequence = sequence_t( n );
            for( size_t i = 0; i < n; ++i ) {
                sequence[i] = std::rand() % k;
            }
            return sequence;
        };
    auto to_string = []( const sequence_t& sequence ) {
        auto result = std::string("");
        for( size_t i = 0; i < sequence.size(); ++i ) {
            result += std::to_string(sequence[i]);
        }
        return result;
    };

    for( auto it = std::begin(re_to_files); it != std::end(re_to_files); ++it ) {
        auto section_name = std::string("Regexp = ");
        section_name += "\'" + it->second + "\'  file = " + it->first;

        auto filename = it->first;
        auto regexp = std::regex( it->second );

        SECTION( section_name )
        {
            try {
                auto machine = ax::load_machine_from_file( filename );
                auto no_e_machine = algs::to_no_lambda_mashine( machine );
                auto heptapod = algs::determinization( no_e_machine );

                auto good_counter = size_t( 0 );

                for( auto i = seq_number; i > 0; --i ) {
                    auto sequence = generate_sequence(
                        std::rand() % max_seq_length + 1,
                        machine.symbols_count()
                    );
                    bool machine_result = heptapod( sequence );
                    bool regexp_result = std::regex_match( to_string(sequence), regexp );

                    if( regexp_result ) {
                        ++good_counter;
                    }

                    CAPTURE( machine );
                    CAPTURE( no_e_machine );
                    CAPTURE( heptapod );
                    CAPTURE( section_name );
                    CAPTURE( to_string(sequence) );

                    REQUIRE( machine_result == regexp_result );
                }

                REQUIRE( good_counter > 1 );
            }
            catch( ax::load_exception_t& le ) {
                std::cout << le.what() << std::endl;
            }
        }
    }

}

/*
int main()
{
    std::vector<std::vector<size_t>> sequences( 1000000 );
    std::srand( 42 );

    try {
        auto machine = ax::load_machine_from_file("tests/full_tests/machines/001.fsa");

        for( auto& seq : sequences ) {
            seq = generate_sequence( std::rand() % 10 + 1, 3 );
        }
        auto no_e_machine = algs::to_no_lambda_mashine( machine );
        std::cout << no_e_machine << std::endl;
        auto heptapod = algs::determinization( no_e_machine );

        bool is_ar = true;
        size_t counter = 0;

        std::regex txt_regex("(1|2)(00)+((11)+|2)");
        for (const auto& seq : sequences) {
                bool flag = std::regex_match(to_string(seq), txt_regex);
                bool answer = heptapod( seq );
                if( flag ) {
                    ++counter;
                }
                if( flag != answer ) {
                    is_ar = false;
                    std::cout << to_string(seq) << "  ERROR " << flag << " " << answer << '\n';
                }
        }

        if( ! is_ar ) {
            std::cout << '\n' << machine << std::endl;
            std::cout << heptapod << std::endl;
        }else{
            std::cout << "God, " << float(counter)/1000000 << std::endl;
        }
    }
    catch( ax::load_exception_t& le ) {
        std::cout << le.what() << std::endl;
    }


}
*/
