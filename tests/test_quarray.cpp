#include "quarray.h"
#include "gtest/gtest.h"

using QuArray = CliffordTableaus::QuArray;
using namespace std::complex_literals;


TEST(QuArrayTest, Construction) {
    // Test the construction of a QuArray object on 4 valid matrices
    QuArray q(8, {
            0, 1, 0, 0, 0, 0, 0, 0,
            1, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 1i, 0, 0, 0, 0,
            0, 0, 1i, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, -1, 0, 0,
            0, 0, 0, 0, -1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, -1i,
            0, 0, 0, 0, 0, 0, -1i, 0
    });
    QuArray q2(4, {
            0.707106781186548, 0, 0.707106781186548, 0,
            0, 0.5 + 0.5i, 0, 0.5 + 0.5i,
            0.707106781186548, 0, -0.707106781186548, 0,
            0, 0.5 + 0.5i, 0, -0.5 - 0.5i
    });
    QuArray q3(16, {
            0, -0.5i, 0, -0.5i, 0, 0, 0, 0, 0, -0.5i, 0, -0.5i, 0, 0, 0, 0,
            0.5i, 0, 0.5i, 0, 0, 0, 0, 0, 0.5i, 0, 0.5i, 0, 0, 0, 0, 0,
            0, -0.5i, 0, 0.5i, 0, 0, 0, 0, 0, -0.5i, 0, 0.5i, 0, 0, 0, 0,
            0.5i, 0, -0.5i, 0, 0, 0, 0, 0, 0.5i, 0, -0.5i, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0.5i, 0, 0.5i, 0, 0, 0, 0, 0, 0.5i, 0, 0.5i,
            0, 0, 0, 0, -0.5i, 0, -0.5i, 0, 0, 0, 0, 0, -0.5i, 0, -0.5i, 0,
            0, 0, 0, 0, 0, 0.5i, 0, -0.5i, 0, 0, 0, 0, 0, 0.5i, 0, -0.5i,
            0, 0, 0, 0, -0.5i, 0, 0.5i, 0, 0, 0, 0, 0, -0.5i, 0, 0.5i, 0,
            0, -0.5i, 0, -0.5i, 0, 0, 0, 0, 0, 0.5i, 0, 0.5i, 0, 0, 0, 0,
            0.5i, 0, 0.5i, 0, 0, 0, 0, 0, -0.5i, 0, -0.5i, 0, 0, 0, 0, 0,
            0, -0.5i, 0, 0.5i, 0, 0, 0, 0, 0, 0.5i, 0, -0.5i, 0, 0, 0, 0,
            0.5i, 0, -0.5i, 0, 0, 0, 0, 0, -0.5i, 0, 0.5i, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0.5i, 0, 0.5i, 0, 0, 0, 0, 0, -0.5i, 0, -0.5i,
            0, 0, 0, 0, -0.5i, 0, -0.5i, 0, 0, 0, 0, 0, 0.5i, 0, 0.5i, 0,
            0, 0, 0, 0, 0, 0.5i, 0, -0.5i, 0, 0, 0, 0, 0, -0.5i, 0, 0.5i,
            0, 0, 0, 0, -0.5i, 0, 0.5i, 0, 0, 0, 0, 0, 0.5i, 0, -0.5i, 0
    });
    QuArray q4(8, {
            0, -1i, 0, 0, 0, 0, 0, 0,
            1i, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, -1i, 0, 0, 0, 0,
            0, 0, 1i, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0, -1, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 1,
            0, 0, 0, 0, 0, 0, -1, 0
    });

    // The next 2 matrix should throw invalid_argument because the matrix is not square
    ASSERT_THROW(QuArray(8, {
            1, 0, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 1, 0, 0, 0, 1,
    }), std::invalid_argument);
    ASSERT_THROW(QuArray(4, {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
    }), std::invalid_argument);

    // The next 2 matrix should throw invalid_argument because the matrix dimension is not a power of 2
    ASSERT_THROW(QuArray(8, {
            1, 0, 0, 0, 1, 0, 0,
            0, 1, 0, 0, 0, 1, 0,
            0, 0, 1, 0, 0, 0, 1,
            1, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 1, 0,
            0, 0, 0, 1, 0, 0, 1
    }), std::invalid_argument);
    ASSERT_THROW(QuArray(4, {
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
    }), std::invalid_argument);

    // The next 2 matrix should throw invalid_argument because the matrix is not Unitary
    ASSERT_THROW(QuArray(8, {
            1, 0, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 1, 0, 0, 0, 1,
            1, 0, 0, 0, 1, 0, 0, 0,
            0, 1, 0, 0, 0, 1, 0, 0,
            0, 0, 1, 0, 0, 0, 1, 0,
            0, 0, 0, 1, 0, 0, 0, 1
    }), std::invalid_argument);
    ASSERT_THROW(QuArray(4, {
            1, 0, 0, 1,
            0, 1, 1, 0,
            0, 1, 1, 0,
            1, 0, 0, 1,
    }), std::invalid_argument);
}

TEST(QuArrayTest, Arithmetic) {

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
