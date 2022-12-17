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

struct thing;
std::ostream& operator<<(std::ostream& os, thing const& t);

struct thing
{
    thing( std::string const& text )
    {
        bool constructor_output{};
        indent_up name_this_to_keep_alive_for_raii;

        if( constructor_output )
            std::cout << std::string( indent - 1, ' ' ) << "Parsing: " << text << '\n';

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
                    std::cout << std::string( indent, ' ' ) << "nom [\n";
                thing subthing( text.substr( text_consumed ) );
                text_consumed += subthing.text_consumed;
                m_things.push_back( subthing );
            }
            break;
            case ']':
                if( constructor_output )
                    std::cout << std::string( indent, ' ' ) << "nom ]\n";
                ++text_consumed;
                return;
            case ',':
                if( constructor_output )
                    std::cout << std::string( indent, ' ' ) << "nom ,\n";
                ++text_consumed;
                break;
            default:
            {
                if( constructor_output )
                    std::cout << std::string( indent, ' ' ) << "nom an int\n";
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

    friend bool operator<=( int const l, thing const& r )
    {
        if( r.m_things.empty() )
            return 1;

        return std::visit( [ & ]( auto const& r_item ) { return l <= r_item; }, r.m_things.front() );
    }
    friend bool operator<=( thing const& l, int const r )
    {
        if( l.m_things.empty() )
            return true;
        return std::visit( [ & ]( auto const& l_item ) { return l_item <= r; }, l.m_things.front() );
    }
    friend bool operator<=( thing const& l, thing const& r )
    {
        std::cout << "Checking " << l << " vs " << r << '\n';
        for( std::size_t i{}; i < l.m_things.size(); ++i )
        {
            if( r.m_things.size() <= i )
            {
                std::cout << "false\n";
                return false;
            }
            if( !std::visit( []( auto const& l_item, auto const& r_item ) {
                             std::cout << "Compare " << l_item << " and " << r_item << "...";
                             if(l_item <= r_item) std::cout << "true\n";
                             else std::cout << "false\n";
                    return l_item <= r_item;
                },
                             l.m_things.at( i ), r.m_things.at( i ) ) )
            {
                std::cout << "false\n";
                return false;
            }
        }
                std::cout << "true\n";
        return true;
    }
};

std::ostream& operator<<(std::ostream& os, thing const& t)
{
    os << '[';
    for(auto const& whatever : t.m_things)
    std::visit([&](auto const& item){os << item << ',';},whatever);
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
        thing a(input[i]);
        thing b(input[i+1]);
        std::cout << "Parsed:\n" << a << '\n' << b << '\n';
        if(a <= b)
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
