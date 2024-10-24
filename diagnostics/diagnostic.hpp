#pragma once

#include "../parser/parser.tab.hpp" // Make sure to include the generated parser header
#include "../parser/location.hh"

namespace mr
{
    namespace diag
    {
        class Diagnostic{
            // includes file_name and location in file
            Parser::location_type location; 

        };
    } // namespace diag
    
} // namespace mr
