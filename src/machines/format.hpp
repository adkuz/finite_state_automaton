#pragma once

#include <fstream>
//#include <filesystem> //Серьезно? до сих пор нет?

#include "fs_machine.hpp"


namespace ax {

    using load_exception_t = std::invalid_argument;

    auto load_machine_from_file( const std::string& path )
        -> machines::finite_state_machine
	{
        using size_t = machines::finite_state_machine::state_index_t;

		auto filestream = std::ifstream(path);

        if( ! filestream.is_open() ){
            throw load_exception_t( "File opening error" );

        }

        size_t states_count = -1;
        size_t symbols_count = -1;

        if( !(filestream >> states_count) ) {
            throw load_exception_t( "States count error" );
        }

        if( !(filestream >> symbols_count) ) {
            throw load_exception_t( "Symbols count error" );
        }

        size_t start_state = -1;

        if( !(filestream >> start_state) ) {
            throw load_exception_t( "Start state error" );
        }

        auto machine = machines::finite_state_machine(states_count, symbols_count);

        machine.set_start_state( start_state );

        size_t final_count = 0;
        if( !(filestream >> final_count || final_count == 0) ) {
            throw load_exception_t( "Final states count error" );
        }

        for( size_t i = 0; i < final_count; ++i ) {
            size_t final_state = -1;
            if( !(filestream >> final_state) ) {
                throw load_exception_t( "Final state error" );
            }
            machine.set_final_state(final_state);
        }

        size_t lambda = -1;
        if( !(filestream >> lambda || lambda < symbols_count) ) {
            throw load_exception_t( "Lambda error" );
        }

        size_t state = -1;
        size_t next = -1;
        size_t symbol = -1;

        try{
            while( filestream >> state && filestream >> symbol && filestream >> next ) {
                if( symbol == lambda) {
                    symbol = machines::lambda_symbol;
                }
                machine.add_rule(state, symbol, next);
            }
        }
        catch(...){
            throw load_exception_t( "Rules error" );
        }

        return machine;
	}
}
