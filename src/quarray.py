from random import choice, uniform
from typing import Iterable
from sympy import (
    pretty, Matrix, re, im, simplify, shape, sqrt, S, ImmutableMatrix, ImmutableDenseMatrix, ImmutableSparseMatrix,
    MatrixBase, Symbol, pprint, Eq
)
from sympy.physics.quantum import TensorProduct as kron
from sympy.physics.quantum import Dagger as dag
from math import log2
from numpy import isclose as isclose_num
from numpy import array, dot, ndarray, sum
from numpy.linalg import eig
from scipy.linalg import eig as scipy_eig
from itertools import product, combinations

h_fac = 0.5 * sqrt(2)


def vector_abs(vector):
    if isinstance(vector, MatrixBase):
        if vector.shape[1] != 1:
            raise RuntimeError("Can't use vec_abs on not-a-vector!")
        return sqrt(vector.dot(vector))
    if isinstance(vector, ndarray):
        if len(vector.shape) != 1:
            raise RuntimeError("Can't use vec_abs on not-a-vector!")
        return sqrt(dot(vector, vector))


def get_bitstrings(length: int):
    return ["".join(bits) for bits in product("01", repeat=length)]


def get_states(length: int):
    return [f"|{bitstring}⟩" for bitstring in get_bitstrings(length)]


def binstring(i: int, length: int = 0):
    return format(i, f"0{length}b")


def isclose_sym(a, b, threshold=1e-12):
    return abs(S(a).evalf() - S(b).evalf()) < threshold


def fix(value, threshold=1e-12):
    x = simplify(S(value)).evalf()
    try:
        if abs(x - round(x)) < threshold:
            return round(x)
    except TypeError:
        pass
    return (
        0 if abs(x) < threshold else
        float(re(x)) if abs(im(x)) < threshold else
        float(im(x)) * 1j if abs(re(x)) < threshold else complex(x)
    )


def fix_round(value, threshold=1e-12):
    x = simplify(S(value)).evalf()
    try:
        if abs(x - round(x)) < threshold:
            return round(x)
        for precision in range(1, 12):
            if abs(x - round(x, precision)) < threshold:
                return round(x, precision)
    except TypeError:
        pass
    return (
        0 if abs(x) < threshold else
        float(re(x)) if abs(im(x)) < threshold else
        float(im(x)) * 1j if abs(re(x)) < threshold else complex(x)
    )


def fix_matrix(matrix: Matrix, threshold=1e-12):
    return simplify(matrix.applyfunc(lambda x: fix(x, threshold)))


def qupretty(matrix: Matrix):
    return pretty(fix_matrix(matrix), num_columns=1000)


class Quarray(Matrix):
    def __new__(cls, input_matrix):
        my_matrix = Matrix(input_matrix)
        ndim = len(my_matrix.shape)
        rows, cols = my_matrix.shape
        if ndim != 2:
            raise ValueError("Input array must be 0-dimensional, 1-dimensional, or 2-dimensional.")
        if not log2(rows).is_integer() or not log2(cols).is_integer():
            raise ValueError("All dimensions must have lengths that are a power of 2.")
        if rows != cols and cols != 1:
            raise ValueError("The matrix must be square.")
        return super().__new__(cls, my_matrix)

    def __mul__(self, other):
        # Here the arguments of kron should be sympy matrices.
        # How can I convert the self and other (which are quarrays) into sympy matrices?
        return Quarray(kron(Matrix(self), Matrix(other)))

    def __matmul__(self, other):
        return Quarray(Matrix(self) @ Matrix(other))

    def __truediv__(self, other):
        my_matrix = Matrix(self)
        other_matrix = Matrix(other)

        if other_matrix.rows == 1 and other_matrix.cols == 1:
            return Quarray(my_matrix / other_matrix[0, 0])
        if other_matrix.rows == 1 or other_matrix.cols == 1:
            raise ValueError("Cannot divide by a vector.")

        return Quarray(other_matrix.inv() @ my_matrix)

    def __str__(self):
        my_matrix = fix_matrix(Matrix(self))
        if my_matrix.shape == (1, 1):
            return f"Quarray({my_matrix[0, 0]})"

        rows, cols = my_matrix.shape
        states_length = int(log2(rows))
        full_string = "Quarray(\n"

        my_rows = qupretty(Matrix(self)).split("\n")
        for index, row_string in enumerate(my_rows):
            full_string += f"\t{row_string}"
            if index % 2 == 1:
                full_string += "\n"
                continue

            i = index // 2
            row = my_matrix.row(i)
            non_zero_indices = [j for j, val in enumerate(row) if not isclose_sym(val, 0)]

            if cols == 1:
                full_string += f"\t|{binstring(i, states_length)}⟩"
            elif len(non_zero_indices) == 1:
                j = non_zero_indices[0]
                value = row[j]

                if isclose_sym(value, 1):
                    full_string += f"\t|{binstring(j, states_length)}⟩ → |{binstring(i, states_length)}⟩"
                elif isclose_sym(abs(S(value).evalf()), 1):
                    full_string += f"\t|{binstring(j, states_length)}⟩ → |{binstring(i, states_length)}⟩ x ({value})"

            full_string += "\n"
        return f"{full_string})"

    def __eq__(self, other):
        if not isinstance(other, Quarray):
            return False

        my_eval = Matrix(self).evalf()
        other_eval = Matrix(other).evalf()

        # Convert to pure Python numeric values
        my_matrix = array([complex(v) for v in my_eval]).reshape(my_eval.shape)
        other_matrix = array([complex(v) for v in other_eval]).reshape(other_eval.shape)

        return my_matrix.shape == other_matrix.shape and isclose_num(my_matrix, other_matrix).all()

    def __ne__(self, other):
        if not isinstance(other, Quarray):
            return True
        return not self.__eq__(other)

    def __abs__(self):
        my_matrix = Matrix(self)
        rows, cols = my_matrix.shape
        if rows == 1 and cols == 1:
            return my_matrix.values()[0]
        if cols == 1:
            return abs(array(my_matrix))
        return fix(my_matrix.det())

    def eigenvalues(self):
        my_matrix = Matrix(self)
        if my_matrix.shape[1] == 1 or my_matrix.shape[0] == 1 or my_matrix.rows != my_matrix.cols:
            return None

        try:
            return [fix(simplify(v)) for v in my_matrix.eigenvals()]
        except Exception:
            try:
                # If sympy fails, fallback to numeric computation.
                return [fix(ev) for ev in eig(array(my_matrix.evalf()))[0]]
            except Exception:
                return None

    def eigenstates(self, normalize=True):
        my_matrix = Matrix(self)
        if my_matrix.shape[1] == 1 or my_matrix.shape[0] == 1 or my_matrix.rows != my_matrix.cols:
            return None

        try:
            not_normalized_states = [simplify(v[2][0]) for v in my_matrix.eigenvects()]
            if normalize:
                return [Quarray(v / vector_abs(v)) for v in not_normalized_states]
            return [Quarray(v) for v in not_normalized_states]
        except Exception:
            try:
                # If sympy fails, fallback to numeric computation.
                return [Quarray(eigenvector / abs(eigenvector)) for eigenvector in eig(array(my_matrix.evalf()))[1]]
            except Exception:
                return None


id = Quarray([[1, 0], [0, 1]])
m0 = Quarray([[1, 0], [0, 0]])
m1 = Quarray([[0, 0], [0, 1]])
x = Quarray([[0, 1], [1, 0]])
y = Quarray([[0, -1j], [1j, 0]])
z = Quarray([[1, 0], [0, -1]])
h = h_fac * Quarray([[1, 1], [1, -1]])
s = Quarray([[1, 0], [0, 1j]])
t = Quarray([[1, 0], [0, 0.5 * sqrt(2) * (1 + 1j)]])

# Syntax of cnot gates:
# cx_ctl with:
# c = control
# t = target
# l = leave alone
cx_012 = (m0 * id + m1 * x) * id
cx_102 = (id * m0 + x * m1) * id
cx_120 = id * (m0 * id + m1 * x)
cx_210 = id * (id * m0 + x * m1)
cx_201 = id * id * m0 + x * id * m1
cx_021 = m0 * id * id + m1 * id * x

# Syntax of toffoli gates:
# ccx_abt with:
# a = control 1
# b = control 2
# t = target
ccx_012 = (m0 * m0 + m0 * m1 + m1 * m0) * id + m1 * m1 * x
ccx_120 = id * (m0 * m0 + m0 * m1 + m1 * m0) + x * m1 * m1
ccx_201 = m0 * id * m0 + m0 * id * m1 + m1 * id * m0 + m1 * x * m1

# Syntax of swap gates:
# swap_abl with:
# a = target 1
# b = target 2
# l = leave alone
swap_012 = cx_012 @ cx_102 @ cx_012
swap_102 = cx_102 @ cx_012 @ cx_102
swap_120 = cx_120 @ cx_210 @ cx_120
swap_210 = cx_210 @ cx_120 @ cx_210
swap_201 = cx_201 @ cx_021 @ cx_201
swap_021 = cx_021 @ cx_201 @ cx_021

# Syntax of fredkin gates
# fred_cab with:
# c = control
# a = target 1
# b = target 2
fred_012 = ccx_012 @ ccx_201 @ ccx_012
fred_021 = ccx_201 @ ccx_012 @ ccx_201
fred_120 = ccx_120 @ ccx_012 @ ccx_120
fred_102 = ccx_012 @ ccx_120 @ ccx_012
fred_201 = ccx_201 @ ccx_120 @ ccx_201
fred_210 = ccx_120 @ ccx_201 @ ccx_120

# The four error syndromes corresponding to the four projection operators
p0 = m0 * m0 * m0 + m1 * m1 * m1
p1 = m1 * m0 * m0 + m0 * m1 * m1
p2 = m0 * m1 * m0 + m1 * m0 * m1
p3 = m0 * m0 * m1 + m1 * m1 * m0

# id = Quarray([[1, 0], [0, 1]])
# x = Quarray([[0, 1], [1, 0]])
# y = Quarray([[0, -1j], [1j, 0]])
# z = Quarray([[1, 0], [0, -1]])
# h = h_fac * Quarray([[1, 1], [1, -1]])
# s = Quarray([[1, 0], [0, 1j]])
# t = Quarray([[1, 0], [0, 0.5 * sqrt(2) * (1 + 1j)]])
if __name__ == "__main__":
    random_matrices = [
        z * s * x,
        s * id * y,
        h * t,
        h * z * h * y
    ]
    for i in random_matrices:
        print(i)
