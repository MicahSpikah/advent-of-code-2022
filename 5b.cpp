#include "parse_input.h"
#include <numeric>

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< std::vector< char > > stacks;

    // What line tells me how many stacks I have?
    auto const index_row_it = std::find_if( input.cbegin(), input.cend(), []( auto const& raw ) { return raw.size() > 2 && raw[ 1 ] == '1'; } );

    stacks.resize( ( index_row_it->size() + 3 ) / 4 );

    std::for_each( std::make_reverse_iterator( index_row_it ), input.rend(), [ & ]( auto const& raw ) {
        for( int i = 0; i < ( raw.size() + 3 ) / 4; ++i )
        {
            if( auto const cargo = raw[ 4 * i + 1 ]; cargo != ' ' )
            {
                stacks[ i ].push_back( cargo );
            }
        }
    } );

    auto const dbg_print_stacks{ [ & ] {
        for( auto const& s : stacks )
        {
            for( auto const& c : s )
            {
                std::cout << c;
            }
            std::cout << '\n';
        }
    } };

    std::for_each( index_row_it + 2, input.cend(), [ & ]( auto const& instruction ) {
        int how_many;
        int from;
        int to;
        //std::cout << "Instruction: '" << instruction.c_str() << "'\n";
        if( 3 != std::sscanf( instruction.c_str(), "move %d from %d to %d", &how_many, &from, &to ) )
        {
            std::cerr << "Couldn't convert instruction '" << instruction.c_str() << "'\n";
            std::exit( 1 );
        }
        //std::cout << "Moving " << how_many << " from " << from << " to " << to << '\n';
        std::vector< char > buffer;
        for( int i = 0; i < how_many; ++i )
        {
            buffer.push_back( stacks[ from - 1 ].back() );
            stacks[ from - 1 ].pop_back();
            //dbg_print_stacks();
        }
        for( int i = 0; i < how_many; ++i )
        {
            stacks[ to - 1 ].push_back( buffer.back() );
            buffer.pop_back();
        }
    } );

    return std::accumulate( stacks.cbegin(), stacks.cend(), std::string{}, []( auto const& l, auto const& r ) { return l + r.back(); } );
}
