#include <fstream>
#include <filesystem>

#include "fs_machine.hpp"


namespace ax {

    using load_exception_t = std::invalid_argument;

    auto load_machine_from_file( const std::string& path )
        -> machines::finite_state_machine
	{
		auto filestream = std::ifstream(path);

        size_t states_count = 0;
        size_t symbols_count = 0;

        if( !(filestream >> states_count) ) {
            throw load_exception_t( "States count error" );
        }

        if( !(filestream >> symbols_count) ) {
            throw load_exception_t( "Symbols count error" );
        }

        size_t state = 0;
        size_t next =

	}
}
