from openqasm3.visitor import QASMVisitor
from openqasm3 import ast
from typing import List, Optional, Sequence
import cmath


class SimulatorVisitor(QASMVisitor):
    def visit_UnaryExpression(self, node: ast.UnaryExpression, context=None):
        if context == "return float":
            value = self.visit(node.expression, context)
            op = node.op.name
            if op == "-":
                return -value
            raise ValueError(f"Unsupported unary operator: {op}")

    def visit_BinaryExpression(self, node: ast.BinaryExpression, context=None):
        if context == "return float":
            left_value = self.visit(node.lhs, context)
            right_value = self.visit(node.rhs, context)
            op = node.op.name

            if op == "+":
                return left_value + right_value
            if op == "-":
                return left_value - right_value
            if op == "*":
                return left_value * right_value
            if op == "/":
                return left_value / right_value
            if op == "==":
                return left_value == right_value
            if op == "!=":
                return left_value != right_value
            if op == "<":
                return left_value < right_value
            if op == ">":
                return left_value > right_value
            if op == "<=":
                return left_value <= right_value
            if op == ">=":
                return left_value >= right_value
            raise ValueError(f"Unsupported binary operator: {node.op.name}")

    def visit_IndexedIdentifier(self, node: ast.IndexedIdentifier, context=None) -> List:
        lst = []
        for index in node.indices:
            if isinstance(index, ast.DiscreteSet):
                lst.append(self.visit(index, context))
            else:
                lst.extend(self._visit_sequence(index, context))
        return lst

    def _visit_sequence(self, nodes: Sequence[ast.QASMNode], context=None) -> List:
        lst = []
        for node in nodes[:-1]:
            if isinstance(node, ast.IndexedIdentifier):
                lst.extend(self.visit(node, context))
            else:
                lst.append(self.visit(node, context))
        if nodes:
            if isinstance(nodes[-1], ast.IndexedIdentifier):
                lst.extend(self.visit(nodes[-1], context))
            else:
                lst.append(self.visit(nodes[-1], context))
        return lst

    def visit_IntegerLiteral(self, node: ast.IntegerLiteral, context=None):
        return node.value

    def visit_FloatLiteral(self, node: ast.FloatLiteral, context=None):
        return node.value

    def visit_ImaginaryLiteral(self, node: ast.ImaginaryLiteral, context=None):
        return node.value

    def visit_Identifier(self, node: ast.Identifier, context=None):
        if context == "return float":
            return float(eval(node.name.replace("pi", str(cmath.pi))))
        return node.name

    def visit_QubitDeclaration(self, node: ast.QASMNode, context=None):
        numQuBits = self.visit(node.size)
        self.initStatevector(numQuBits)

    def visit_QuantumGate(self, node: ast.QubitDeclaration, context=None):
        name = self.visit(node.name)
        qubits = self._visit_sequence(node.qubits)

        param = self.visit(node.arguments[0], context="return float") if node.arguments else None

        if len(qubits) == 1:
            getattr(self, name)(qubits[0], param)
        elif len(qubits) == 2:
            getattr(self, name)(qubits[0], qubits[1], param)
        elif len(qubits) == 3:
            getattr(self, name)(qubits[0], qubits[1], qubits[2], param)

        return self.generic_visit(node, context)

    def visit_QuantumMeasurement(self, node: ast.QuantumMeasurement, context=None):
        qubit = self.visit(node.qubit)
        self.measure(qubit[0])

    def initStatevector(self, numQuBits: int):
        raise NotImplementedError()

    def x(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def y(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def z(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def h(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def s(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def t(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def rx(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ry(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def rz(self, target: int, param: Optional[float]):
        raise NotImplementedError()

    def cx(self, control: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def cy(self, control: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def cz(self, control: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ch(self, control: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def cs(self, control: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ct(self, control: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ccx(self, control1: int, control2: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ccy(self, control1: int, control2: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ccz(self, control1: int, control2: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def cch(self, control1: int, control2: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def ccs(self, control1: int, control2: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def cct(self, control1: int, control2: int, target: int, param: Optional[float]):
        raise NotImplementedError()

    def measure(self, target: int):
        raise NotImplementedError()

    def visualize(self):
        raise NotImplementedError()
