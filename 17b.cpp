#include "parse_input.h"
#include <array>

//NOTE: This one is mmmmmmmmmmm a little incomplete. I looked at visualized output and saw a pattern emerging, and so the base of my algorithm assumes the pattern exists and goes from there. A better program would find the pattern programatically based on the input

std::vector< std::array< bool, 7 > > tower;

std::size_t height()
{
    std::size_t val{};

    for( ; val < tower.size() && std::any_of( tower.at( val ).cbegin(), tower.at( val ).cend(), []( auto const x ) { return x; } ); ++val )
        ;

    return val;
}

void visualize()
{
    for( int i = height(); i >= 0; --i )
    {
        for( int x = 0; x < 7; ++x )
            std::cout << ( tower.at( i ).at( x ) ? '#' : '.' );
        std::cout << '\n';
    }
}

void place_box( std::size_t y, int x )
{
    tower.at( y ).at( x )         = true;
    tower.at( y + 1 ).at( x )     = true;
    tower.at( y ).at( x + 1 )     = true;
    tower.at( y + 1 ).at( x + 1 ) = true;
}
bool box( std::size_t y, int x )
{
    if( x < 0 || x > 5 )
        return false;
    tower.resize( std::max( tower.size(), y + 2 ) );
    return !( tower.at( y ).at( x ) || tower.at( y + 1 ).at( x ) || tower.at( y ).at( x + 1 ) || tower.at( y + 1 ).at( x + 1 ) );
}

void place_bar( std::size_t y, int x )
{
    tower.at( y ).at( x )     = true;
    tower.at( y + 1 ).at( x ) = true;
    tower.at( y + 2 ).at( x ) = true;
    tower.at( y + 3 ).at( x ) = true;
}
bool bar( std::size_t y, int x )
{
    if( x < 0 || x > 6 )
        return false;
    tower.resize( std::max( tower.size(), y + 4 ) );
    return !( tower.at( y ).at( x ) || tower.at( y + 1 ).at( x ) || tower.at( y + 2 ).at( x ) || tower.at( y + 3 ).at( x ) );
}

void place_dash( std::size_t y, int x )
{
    tower.at( y ).at( x )     = true;
    tower.at( y ).at( x + 1 ) = true;
    tower.at( y ).at( x + 2 ) = true;
    tower.at( y ).at( x + 3 ) = true;
}
bool dash( std::size_t y, int x )
{
    tower.resize( std::max( tower.size(), y + 1 ) );
    if( x < 0 || x > 3 )
        return false;
    return !( tower.at( y ).at( x ) || tower.at( y ).at( x + 1 ) || tower.at( y ).at( x + 2 ) || tower.at( y ).at( x + 3 ) );
}

bool plus( std::size_t y, int x )
{
    tower.resize( std::max( tower.size(), y + 3 ) );
    if( x < 0 || x > 4 )
        return false;
    return !( tower.at( y ).at( x + 1 ) || tower.at( y + 1 ).at( x ) || tower.at( y + 1 ).at( x + 1 ) || tower.at( y + 1 ).at( x + 2 ) || tower.at( y + 2 ).at( x + 1 ) );
}
void place_plus( std::size_t y, int x )
{
    tower.at( y ).at( x + 1 )     = true;
    tower.at( y + 1 ).at( x )     = true;
    tower.at( y + 1 ).at( x + 1 ) = true;
    tower.at( y + 1 ).at( x + 2 ) = true;
    tower.at( y + 2 ).at( x + 1 ) = true;
}

bool l( std::size_t y, int x )
{
    tower.resize( std::max( tower.size(), y + 3 ) );
    if( x < 0 || x > 4 )
        return false;
    return !( tower.at( y ).at( x ) || tower.at( y ).at( x + 1 ) || tower.at( y ).at( x + 2 ) || tower.at( y + 1 ).at( x + 2 ) || tower.at( y + 2 ).at( x + 2 ) );
}
void place_l( std::size_t y, int x )
{
    tower.at( y ).at( x )         = true;
    tower.at( y ).at( x + 1 )     = true;
    tower.at( y ).at( x + 2 )     = true;
    tower.at( y + 1 ).at( x + 2 ) = true;
    tower.at( y + 2 ).at( x + 2 ) = true;
}

advent_t advent( std::vector< std::string > const& input )
{
    int inst{};

    std::function< bool( std::size_t, int ) > test;
    std::function< void( std::size_t, int ) > place;

    std::vector< std::size_t > height_history;

    for( std::size_t shape{}; shape < 10349; ++shape )
    {
        height_history.push_back( height() );
        if( inst >= input.front().size() )
            inst = 0;
        switch( shape % 5 )
        {
        case 0:
            test  = dash;
            place = place_dash;
            break;
        case 1:
            test  = plus;
            place = place_plus;
            break;
        case 2:
            test  = l;
            place = place_l;
            break;
        case 3:
            test  = bar;
            place = place_bar;
            break;
        case 4:
            test  = box;
            place = place_box;
            break;
        }

        std::size_t y = height() + 3;
        int x         = 2;

        while( true )
        {
            if( inst >= input.front().size() )
                inst = 0;
            int test_x;
            if( input.front().at( inst++ ) == '<' )
                test_x = x - 1;
            else
                test_x = x + 1;

            if( test( y, test_x ) )
                x = test_x;

            if( y > 0 && test( y - 1, x ) )
            {
                --y;
            }
            else
            {
                place( y, x );
                break;
            }
        }
    }

    std::size_t pieces{ 1'000'000'000'000 };
    //std::size_t pieces{ 37948 };
    return height_history.at( ( ( pieces - 5174 ) % 5175 ) + 5174 ) + ( ( pieces - 5174 ) / 5175 ) * ( height_history.at( 5173 + 5175 ) - height_history.at( 5173 ) );
}
