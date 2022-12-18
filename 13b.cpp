#include "parse_input.h"

using namespace std::literals;

int indent{};

struct indent_up
{
    indent_up()
    {
        ++indent;
    }
    ~indent_up()
    {
        --indent;
    }
};

std::ostream& dbg_indented()
{
    return std::cout << std::string( indent, ' ' );
}

struct thing;
std::ostream& operator<<( std::ostream& os, thing const& t );

struct thing
{
    thing( std::string const& text )
    {
        if( text.front() != '[' )
            throw std::runtime_error( "Parse error, expected [" );

        text_consumed = 1;

        while( true )
        {
            switch( text.at( text_consumed ) )
            {
            case '[':
            {
                thing subthing( text.substr( text_consumed ) );
                text_consumed += subthing.text_consumed;
                m_things.push_back( subthing );
            }
            break;
            case ']':
                ++text_consumed;
                return;
            case ',':
                ++text_consumed;
                break;
            default:
            {
                std::size_t consumed_for_int;
                m_things.push_back( std::stoi( text.substr( text_consumed ), &consumed_for_int ) );
                text_consumed += consumed_for_int;
            }
            }
        }

        throw std::runtime_error( "Missing ]" );
    }

    std::size_t text_consumed{};
    std::vector< std::variant< thing, int > > m_things;

    friend std::strong_ordering operator<=>( int const l, thing const& r )
    {
        return thing( "[" + std::to_string( l ) + "]" ) <=> r;
    }
    friend std::strong_ordering operator<=>( thing const& l, int const r )
    {
        return l <=> thing( "[" + std::to_string( r ) + "]" );
    }
    friend std::strong_ordering operator<=>( thing const& l, thing const& r )
    {
        for( std::size_t i{}; i < l.m_things.size(); ++i )
        {
            if( r.m_things.size() <= i )
            {
                return std::strong_ordering::greater;
            }
            if( auto const itemwise_compare = std::visit( []( auto const& l_item, auto const& r_item ) { return l_item <=> r_item; }, l.m_things.at( i ), r.m_things.at( i ) ); itemwise_compare != 0 )
            {
                return itemwise_compare;
            }
        }
        return l.m_things.size() <=> r.m_things.size();
    }
};

std::ostream& operator<<( std::ostream& os, thing const& t )
{
    os << '[';
    for( auto const& whatever : t.m_things )
        std::visit( [ & ]( auto const& item ) { os << item << ','; }, whatever );
    os << ']';

    return os;
}

advent_t advent( std::vector< std::string > const& input )
{
    int lt2{ 1 };
    int lt6{ 2 };

    auto const test{ [ & ]( auto const& a ) {
        if( a < thing( "[[6]]" ) )
        {
            ++lt6;
            if( a < thing( "[[2]]" ) )
                ++lt2;
        }
    } };

    for( int i = 0; i + 1 < input.size(); i += 3 )
    {
        test( thing( input[ i ] ) );
        test( thing( input[ i + 1 ] ) );
    }

    return lt2 * lt6;
}
