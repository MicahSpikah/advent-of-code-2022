#include "parse_input.h"
#include <array>

// BAD: height and width are hard coded to match the input data. Different input data may need different height and width
constexpr std::size_t height{ 160 };
constexpr std::size_t width{ 1000 };
std::array< std::array< char, height >, width > cave{};

int parse_num( std::string const& str, std::size_t& pos )
{
    std::size_t substr_pos;
    auto val = std::stoi( str.substr( pos ), &substr_pos );
    pos += substr_pos;
    return val;
}

advent_t advent( std::vector< std::string > const& input )
{
    for( auto& d1 : cave )
        for( auto& d2 : d1 )
            d2 = '.';
    for( auto& col : cave )
        col.back() = '#';
    for( auto const& l : input )
    {
        std::size_t pos{};
        int last_x = parse_num( l, pos );
        ++pos;
        int last_y = parse_num( l, pos );

        while( pos < l.size() )
        {
            pos += 4;
            int next_x = parse_num( l, pos );
            ++pos;
            int next_y = parse_num( l, pos );

            cave[ next_x ][ next_y ] = '#';
            int x_dir{};
            int y_dir{};

            if( next_x < last_x && next_y == last_y )
                x_dir = -1;
            else if( next_x > last_x && next_y == last_y )
                x_dir = 1;
            else if( next_y < last_y && next_x == last_x )
                y_dir = -1;
            else if( next_y > last_y && next_x == last_x )
                y_dir = 1;
            else
                throw std::runtime_error( "Bad rock parsing" );
            for( int x = last_x, y = last_y; x != next_x || y != next_y; x += x_dir, y += y_dir )
            {
                cave[ x ][ y ] = '#';
            }

            last_x = next_x;
            last_y = next_y;
        }
    }

    auto const draw_cave{ [ & ] {
        for( int y = 0; y < height; ++y )
        {
            for( int x = 300; x < 700; ++x )
            {
                std::cout << cave[ x ][ y ];
            }
            std::cout << '\n';
        }
    } };

    int sand{};
    while( cave[ 500 ][ 0 ] == '.' )
    {
        int x{ 500 };
        int y{ 0 };

        while( y + 1 < height )
        {
            bool no_path_out{};
            if( cave[ x ][ y + 1 ] == '.' )
            {
                ++y;
            }
            else if( cave[ x - 1 ][ y + 1 ] == '.' )
            {
                ++y;
                --x;
            }
            else if( cave[ x + 1 ][ y + 1 ] == '.' )
            {
                ++x;
                ++y;
            }
            else
            {
                no_path_out = true;
            }
            if( no_path_out )
            {
                cave[ x ][ y ] = '+';
                ++sand;
                break;
            }
        }
    }

    draw_cave();
    return sand;
}
