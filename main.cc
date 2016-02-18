#include "calendar.h"
#include <boost/program_options.hpp>

namespace opt = boost::program_options;
typedef unsigned short uns_short;

int main(int argc, char **argv) {
    opt::options_description description("Options");
    description.add_options()
            ("help,h", "Print help message")
            ("year,y", opt::value<uns_short>(), "Display calendar for given year");

    opt::variables_map variablesMap;
    try {
        opt::store(opt::parse_command_line(argc, argv, description), variablesMap);
        opt::notify(variablesMap);

        if (variablesMap.count("help")) {
            std::cout << description << "\n";
            return 0;
        }
        if (variablesMap.count("year")) {
            auto year = variablesMap["year"].as<uns_short>();
            if(year < 1400 || year > 10000)
                throw opt::error("Year argument is out of valid range [1400, 10000].");
            Calendar::Calendar calendar(year);
            calendar.display(std::cout);
            return 1;
        }
        std::cout << description << "\n";
        return 0;
    }
    catch (opt::error &error) {
        std::cerr << "ERROR: " << error.what() << "\n";
        std::cerr << description << "\n";
        return -1;
    }
}