#!/usr/bin/env python

import random

def generate_automata( states, symbols, lambdas, transitions ):

    start = random.randint( 0, states - 1 )
    final_states_count = random.randint( 1, states / 2 )
    final_states = random.sample([s for s in range(states)], final_states_count)

    lambda_symbol = states * 2 + 1

    line = "{} {}\n".format( states, symbols )
    line += str(start) + '\n'
    line += str(final_states_count) + " "
    line += " ".join([str(s) for s in final_states]) + '\n'
    line += str(lambda_symbol) + '\n'

    rule = "{} {} {}\n"

    for i in range( lambdas ):
        state = random.randint( 0, states - 1 )
        next_state = random.randint( 0, states - 1 )
        while next_state == state and states > 1:
            next_state = random.randint( 0, states - 1 )
        line += rule.format( state, lambda_symbol, next_state )

    for i in range( transitions ):
        state = random.randint( 0, states - 1 )
        next_state = random.randint( 0, states - 1 )
        symbol = random.randint( 0, symbols - 1 )
        line += rule.format( state, symbol, next_state )

    return line


if __name__ == '__main__':
    print generate_automata( 10, 4, 4, 19 )
