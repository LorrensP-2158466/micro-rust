// i need this because all of this forward declarating bullshit i hate it

#include "mr_driver.hpp"

void print_duration(std::chrono::nanoseconds duration, const std::string& action) {
    using namespace std::chrono;
    if (duration.count() < 1'000) {
        // Nanoseconds
        std::cout << action << " took " << duration.count() << " nanoseconds"
                  << std::endl;
    } else if (duration.count() < 1'000'000) {
        // Microseconds
        auto dur = duration_cast<microseconds>(duration);
        std::cout << action << " took " << dur.count() << " microseconds" << std::endl;
    } else if (duration.count() < 1'000'000'000) {
        // Milliseconds
        auto dur = duration_cast<milliseconds>(duration);
        std::cout << action << " took " << dur.count() << " milliseconds" << std::endl;
    } else {
        // Seconds
        auto dur = duration_cast<seconds>(duration);
        std::cout << std::fixed << std::setprecision(2) // For fractions of seconds
                  << action << " took " << dur.count() << " seconds" << std::endl;
    }
}

int mr::driver::MRDriver::start() {
    using clock = std::chrono::high_resolution_clock;

    Lexer lexer(_input_file, false);

    Parser parser(*this, lexer, false, file_name);

    auto start_compile = clock::now();
    if (parser.parse()) {
        std::cerr << "Parsing failure\n";
        return 1;
    }

    _ast->print();

    auto ir = _middle_phase.run(std::move(_ast));

    auto end_compile = clock::now();
    auto dur_compile =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end_compile - start_compile);

    auto interp = middle_interpreter::Interpreter(std::move(ir));

    if (_err_ctx.has_errors()) {
        _input_file.seekg(0);
        std::vector<std::string> source_in_lines;
        std::string              line;
        while (std::getline(_input_file, line)) {
            source_in_lines.push_back(line);
        }
        std::cout << "-------------------------\n";
        for (const auto& line : source_in_lines){
            std::cout << line << "\n";
        }
        _err_ctx.show_errors(source_in_lines);
        std::cout << "-------------------------\n";
        print_duration(dur_compile, "Compiling");
        return 1;
    }
    auto start_interp = clock::now();

    interp.interp();

    auto end_interp = clock::now();
    auto dur_interp =
        std::chrono::duration_cast<std::chrono::nanoseconds>(end_interp - start_interp);

    std::cout << "-------------------------\n";
    print_duration(dur_compile, "Compiling");
    print_duration(dur_interp, "Interpreting");

    return 0;
};
