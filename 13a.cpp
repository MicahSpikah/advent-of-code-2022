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
        bool constructor_output{};

        if( constructor_output )
            dbg_indented() << "Parsing: "s << text << '\n';

        //indent_up name_this_to_keep_alive_for_raii;

        if( text.front() != '[' )
            throw std::runtime_error( "Parse error, expected [" );

        text_consumed = 1;

        while( true )
        {
            switch( text.at( text_consumed ) )
            {
            case '[':
            {
                if( constructor_output )
                    dbg_indented() << "nom [\n";
                thing subthing( text.substr( text_consumed ) );
                text_consumed += subthing.text_consumed;
                m_things.push_back( subthing );
            }
            break;
            case ']':
                if( constructor_output )
                    dbg_indented() << "nom ]\n";
                ++text_consumed;
                return;
            case ',':
                if( constructor_output )
                    dbg_indented() << "nom ,\n";
                ++text_consumed;
                break;
            default:
            {
                if( constructor_output )
                    dbg_indented() << "nom an int\n";
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
        std::cout << "Checking " << l << " vs " << r << '\n';
        for( std::size_t i{}; i < l.m_things.size(); ++i )
        {
            if( r.m_things.size() <= i )
            {
                std::cout << "false bc right ran out of stuff\n";
                return std::strong_ordering::greater;
            }
            if( auto const itemwise_compare = std::visit( []( auto const& l_item, auto const& r_item ) {
                    std::cout << "Compare " << l_item << " and " << r_item << "...";
                    auto output_value{ l_item <=> r_item };
                    if( output_value < 0 )
                    {
                        std::cout << "Less\n";
                    }
                    else if( output_value > 0 )
                    {
                        std::cout << "Greater\n";
                    }
                    else
                        std::cout << "Equal\n";
                    return output_value;
                },
                                                          l.m_things.at( i ), r.m_things.at( i ) );
                itemwise_compare != 0 )
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
    int sum{};
    for( int i = 0; i + 1 < input.size(); i += 3 )
    {
        std::cout << input[ i ] << '\n'
                  << input[ i + 1 ] << '\n';
        thing a( input[ i ] );
        thing b( input[ i + 1 ] );
        std::cout << "Parsed:\n"
                  << a << '\n'
                  << b << '\n';
        if( a <= b )
        {
            std::cout << "Pair " << i / 3 << " Good. Less than\n\n";
            sum += 1 + i / 3;
        }
        else
        {
            std::cout << "NOT Less than\n\n";
        }
    }

    return sum;
}
