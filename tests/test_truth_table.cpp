#include <catch2/catch_test_macros.hpp>

#include "ready_set_bool.hpp"

using namespace m42;

template <typename Func, typename... Args>
std::string capture_stdout(Func f, const Args&... args) {
    std::streambuf *cout_buf = std::cout.rdbuf();
    std::ostringstream captured_out;
    std::cout.rdbuf(captured_out.rdbuf());
    f(args...);
    std::cout.rdbuf(cout_buf);
    return captured_out.str();
}

TEST_CASE("simple cases", "[truth_table]") {
    REQUIRE(
        capture_stdout(print_truth_table, "A") ==
        "| A | = |\n"
        "|---|---|\n"
        "| 0 | 0 |\n"
        "| 1 | 1 |\n"
    );

    REQUIRE(
        capture_stdout(print_truth_table, "BA&") ==
        "| A | B | = |\n"
        "|---|---|---|\n"
        "| 0 | 0 | 0 |\n"
        "| 0 | 1 | 0 |\n"
        "| 1 | 0 | 0 |\n"
        "| 1 | 1 | 1 |\n"
    );

    REQUIRE(
        capture_stdout(print_truth_table, "AB|") ==
        "| A | B | = |\n"
        "|---|---|---|\n"
        "| 0 | 0 | 0 |\n"
        "| 0 | 1 | 1 |\n"
        "| 1 | 0 | 1 |\n"
        "| 1 | 1 | 1 |\n"
    );

    REQUIRE(
        capture_stdout(print_truth_table, "C!") ==
        "| C | = |\n"
        "|---|---|\n"
        "| 0 | 1 |\n"
        "| 1 | 0 |\n"
    );

    REQUIRE(
        capture_stdout(print_truth_table, "HC!>") ==
        "| C | H | = |\n"
        "|---|---|---|\n"
        "| 0 | 0 | 1 |\n"
        "| 0 | 1 | 1 |\n"
        "| 1 | 0 | 1 |\n"
        "| 1 | 1 | 0 |\n"
    );

    REQUIRE(
        capture_stdout(print_truth_table, "KN!|AK&=") ==
        "| A | K | N | = |\n"
        "|---|---|---|---|\n"
        "| 0 | 0 | 0 | 0 |\n"
        "| 0 | 0 | 1 | 1 |\n"
        "| 0 | 1 | 0 | 0 |\n"
        "| 0 | 1 | 1 | 0 |\n"
        "| 1 | 0 | 0 | 0 |\n"
        "| 1 | 0 | 1 | 1 |\n"
        "| 1 | 1 | 0 | 1 |\n"
        "| 1 | 1 | 1 | 1 |\n"
    );
}

TEST_CASE("subject case", "[truth_table]") {
    REQUIRE(
        capture_stdout(print_truth_table, "AB&C|") ==
        "| A | B | C | = |\n"
        "|---|---|---|---|\n"
        "| 0 | 0 | 0 | 0 |\n"
        "| 0 | 0 | 1 | 1 |\n"
        "| 0 | 1 | 0 | 0 |\n"
        "| 0 | 1 | 1 | 1 |\n"
        "| 1 | 0 | 0 | 0 |\n"
        "| 1 | 0 | 1 | 1 |\n"
        "| 1 | 1 | 0 | 1 |\n"
        "| 1 | 1 | 1 | 1 |\n"
    );
}
