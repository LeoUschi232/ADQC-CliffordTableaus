OPENQASM 3;
qreg q[2];
h q[0];
cx q[0],q[1];
measure q[0];
measure q[1];
