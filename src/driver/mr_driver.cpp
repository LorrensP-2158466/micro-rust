// i need this because all of this forward declarating bullshit i hate it

#include "mr_driver.hpp"

void print_duration(std::chrono::nanoseconds duration) {
    if (duration.count() < 1'000) {
        // Nanoseconds
        std::cout << "Interpreting took " << duration.count() << " nanoseconds"
                  << std::endl;
    } else if (duration.count() < 1'000'000) {
        // Microseconds
        auto microseconds =
            std::chrono::duration_cast<std::chrono::microseconds>(duration);
        std::cout << "Interpreting took " << microseconds.count() << " microseconds"
                  << std::endl;
    } else if (duration.count() < 1'000'000'000) {
        // Milliseconds
        auto milliseconds =
            std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        std::cout << "Interpreting took " << milliseconds.count() << " milliseconds"
                  << std::endl;
    } else {
        // Seconds
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        std::cout << std::fixed << std::setprecision(2) // For fractions of seconds
                  << "Interpreting took " << seconds.count() << " seconds" << std::endl;
    }
}

int mr::driver::MRDriver::start() {
    Lexer lexer(_input_file, false);

    Parser parser(*this, lexer, false, file_name);

    if (parser.parse()) {
        std::cerr << "Parsing failure\n";
        return 1;
    }
    _ast->print();

    auto ir = _middle_phase.run(std::move(_ast));

    auto interp = middle_interpreter::Interpreter(std::move(ir));

    auto start = std::chrono::high_resolution_clock::now();

    interp.interp();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    print_duration(duration);

    return 0;
};
