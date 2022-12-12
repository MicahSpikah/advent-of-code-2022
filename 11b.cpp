#include "parse_input.h"

using namespace std::literals;

struct monkey
{
    std::vector< std::uint64_t > items;
    std::uint64_t op_add{};
    std::uint64_t op_multiply{ 1 };
    std::uint64_t op_pow{ 1 };
    std::uint64_t test{ 1 };
    std::uint64_t if_true{};
    std::uint64_t if_false{};
    std::uint64_t inspections{};
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
                monkeys.back().items.push_back( std::stoi( l.substr( pos ) ) );
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
            for( auto const& i : m.items )
            {
                std::cout << i << ' ';
            }
            std::cout << '\n';

            std::cout << m.op_add << ' ' << m.op_multiply << ' ' << m.op_pow << ' ' << m.test << ' ' << m.if_true << ' ' << m.if_false << '\n';
        }
    } };

    for( int round{}; round < 10000; ++round )
    {
        for( auto& m : monkeys )
        {
            for( auto old : m.items )
            {
                ++m.inspections;
                if( m.op_pow == 2 )
                    old *= old;
                old *= m.op_multiply;
                old += m.op_add;
                old %= ( 3 * 2 * 5 * 7 * 11 * 13 * 17 * 19 );
                if( old % m.test == 0 )
                {
                    monkeys[ m.if_true ].items.push_back( old );
                }
                else
                {
                    monkeys[ m.if_false ].items.push_back( old );
                }
            }
            m.items.clear();
        }
        if( round + 1 == 1 || round + 1 == 20 || round + 1 == 1000 || ( round + 1 ) % 1000 == 0 )
        {
            for( auto const& m : monkeys )
                std::cout << m.inspections << ' ';
            std::cout << "\n";
        }
    }

    std::nth_element( monkeys.begin(), monkeys.begin() + 1, monkeys.end(), []( auto const& m1, auto const& m2 ) { return m1.inspections > m2.inspections; } );

    return monkeys[ 0 ].inspections * monkeys[ 1 ].inspections;
}
