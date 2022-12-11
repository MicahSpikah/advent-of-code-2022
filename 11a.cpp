#include "parse_input.h"

#include <queue>

using namespace std::literals;

struct monkey
{
    std::queue< int > items;
    int op_add{};
    int op_multiply{ 1 };
    int op_pow{ 1 };
    int test{ 1 };
    int if_true{};
    int if_false{};
    int inspections{};
};

advent_t advent( std::vector< std::string > const& input )
{
    std::vector< monkey > monkeys;
    for( auto const& l : input )
    {
        if( l.starts_with( "Monkey" ) )
        {
            monkeys.push_back( monkey{} );
        }
        else if( l.starts_with( "  Starting items:" ) )
        {
            std::size_t pos{ "  Starting items: "s.size() };
            while( pos < l.size() )
            {
                monkeys.back().items.push( std::stoi( l.substr( pos ) ) );
                pos += 4;
            }
        }
        else if( l.starts_with( "  Operation:" ) )
        {
            if( l[ 23 ] == '+' )
            {
                monkeys.back().op_add = std::stoi( l.substr( 25 ) );
            }
            else if( l.substr( 23 ) == "* old" )
            {
                monkeys.back().op_pow = 2;
            }
            else
            {
                monkeys.back().op_multiply = std::stoi( l.substr( 25 ) );
            }
        }
        else if( l.starts_with( "  Test: divisible by " ) )
        {
            monkeys.back().test = std::stoi( l.substr( 21 ) );
        }
        else if( l.starts_with( "    If true: throw to monkey " ) )
        {
            monkeys.back().if_true = std::stoi( l.substr( 29 ) );
        }
        else if( l.starts_with( "    If false: throw to monkey " ) )
        {
            monkeys.back().if_false = std::stoi( l.substr( 30 ) );
        }
        else if( l.empty() )
        {
        }
        else
            throw std::runtime_error( "Parsing error at: '" + l + "'" );
    }

    auto const print_monkeys{ [ & ] {
        for( auto& m : monkeys )
        {
            std::cout << "Monkey\n";
            while( !m.items.empty() )
            {
                std::cout << m.items.front() << ' ';
                m.items.pop();
            }
            std::cout << '\n';

            std::cout << m.op_add << ' ' << m.op_multiply << ' ' << m.op_pow << ' ' << m.test << ' ' << m.if_true << ' ' << m.if_false << '\n';
        }
    } };

    for( int round{}; round < 20; ++round )
    {
        for( auto& m : monkeys )
        {
            while( !m.items.empty() )
            {
                auto old = m.items.front();
                m.items.pop();
                ++m.inspections;
                if( m.op_pow == 2 )
                    old *= old;
                old *= m.op_multiply;
                old += m.op_add;
                old /= 3;
                if( old % m.test == 0 )
                    monkeys[ m.if_true ].items.push( old );
                else
                    monkeys[ m.if_false ].items.push( old );
            }
        }
    }

    std::nth_element( monkeys.begin(), monkeys.begin() + 1, monkeys.end(), []( auto const& m1, auto const& m2 ) { return m1.inspections > m2.inspections; } );

    return monkeys[ 0 ].inspections * monkeys[ 1 ].inspections;
}
