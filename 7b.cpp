#include "parse_input.h"
#include <memory>
#include <numeric>
#include <unordered_map>

struct descriptor
{
    virtual ~descriptor()    = default;
    virtual int size() const = 0;
};

struct file : descriptor
{
    file( int s ) :
        filesize( s ){};

    int filesize{};
    int size() const override { return filesize; }
};

struct dir : descriptor
{
    using descriptor::descriptor;
    std::unordered_map< std::string, std::unique_ptr< descriptor > > contents;
    int size() const override
    {
        return std::accumulate( contents.cbegin(), contents.cend(), int{}, []( int sum, auto const& string_descriptor_pair ) { return sum + string_descriptor_pair.second->size(); } );
    }

    void output_contents( int indent = 0 )
    {
        for( auto const& [ name, ptr ] : contents )
        {
            for( int i = 0; i < indent; ++i )
                std::cout << '\t';
            std::cout << name << ' ' << ptr->size() << '\n';
            if( auto d = dynamic_cast< dir* >( ptr.get() ); d )
            {
                d->output_contents( indent + 1 );
            }
        }
    }

    std::vector< int > dir_sizes()
    {
        std::vector< int > sizes{ size() };
        for( auto const& [ name, ptr ] : contents )
        {
            if( auto d = dynamic_cast< dir* >( ptr.get() ); d )
            {
                auto child_sizes{ d->dir_sizes() };
                sizes.insert( sizes.end(), child_sizes.begin(), child_sizes.end() );
            }
        }
        return sizes;
    }
};

advent_t advent( std::vector< std::string > const& input )
{
    dir root;
    std::vector< dir* > stack;

    auto const cd{ [ & ]( auto const& dirname ) {
        if( dirname == "/" )
        {
            stack = { &root };
        }
        else if( dirname == ".." )
        {
            stack.pop_back();
        }
        else
        {
            stack.push_back( dynamic_cast< dir* >( stack.back()->contents.at( dirname ).get() ) );
        }
    } };

    // Step 1: Build filesystem
    for( auto const& line : input )
    {
        if( line.starts_with( "$ cd" ) )
        {
            cd( line.substr( 5 ) );
        }
        else if( line == "$ ls" )
        {
        }
        else if( line.starts_with( "dir" ) )
        {
            stack.back()->contents.emplace( line.substr( 4 ), std::make_unique< dir >() );
        }
        else
        {
            std::size_t num_digits{};
            int size{ std::stoi( line, &num_digits ) };
            stack.back()->contents[ line.substr( num_digits + 1 ) ] = std::make_unique< file >( size );
        }
    }

    // Step 2: Calculate
    auto dir_sizes{ root.dir_sizes() };

    int capacity{ 70000000 };
    int needed{ 30000000 };
    int available{ capacity - root.size() };
    int over{ needed - available };

    std::sort( dir_sizes.begin(), dir_sizes.end() );

    return *std::lower_bound( dir_sizes.begin(), dir_sizes.end(), over );
}
