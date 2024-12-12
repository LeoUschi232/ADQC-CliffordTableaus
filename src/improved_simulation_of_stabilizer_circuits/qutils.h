#pragma once

#include <vector>
#include <string>
#include <cmath>
#include <sstream>


namespace CliffordTableaus {
    /**
     * Assert that two floating point numbers are suffciently close to be considered equal.
     * @param a First number.
     * @param b Second number.
     * @param rel_tol Relative tolerance.
     * @param abs_tol Absolute tolerance.
     * @return True if the numbers are close enough, false otherwise.
     */
    static bool isclose(double a, double b, double rel_tol, double abs_tol);

    /**
     *
     * @param length
     * @return
     */
    static std::vector<std::string> get_bitstrings(int length);

    /**
     *
     * @param length
     * @return
     */
    std::vector<std::string> get_states(int length);
}