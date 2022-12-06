#include "parse_input.h"

struct parsed_sections
{
    int min0;
    int max0;
    int min1;
    int max1;
};

std::vector< parsed_sections > parse_sections( std::vector< std::string > const& input )
{
    std::vector< parsed_sections > out;

    for( auto const& str : input )
    {
        auto const elf{ []( auto const& raw_elf ) {
            auto const dash_index{ raw_elf.find( '-' ) };
            return std::make_pair< int, int >( std::stoi( raw_elf.substr( 0, dash_index ) ), std::stoi( raw_elf.substr( dash_index + 1 ) ) );
        } };

        auto const comma_index{ str.find( ',' ) };
        auto const elf0{ elf( str.substr( 0, comma_index ) ) };
        auto const elf1{ elf( str.substr( 1 + comma_index ) ) };
        out.push_back( parsed_sections{ elf0.first, elf0.second, elf1.first, elf1.second } );
    }
    return out;
}

advent_t advent( std::vector< std::string > const& raw_input )
{
    auto const sections{ parse_sections( raw_input ) };

    int sum{};
    for( auto const& section : sections )
    {
        if( ( section.min0 <= section.min1 && section.max0 >= section.max1 ) || ( section.min1 <= section.min0 && section.max1 >= section.max0 ) )
        {
            ++sum;
        }
    }

    return sum;
}
