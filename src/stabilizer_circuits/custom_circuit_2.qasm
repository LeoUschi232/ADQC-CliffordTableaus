OPENQASM 3;
qreg q[5];
h q[0];
h q[2];
h q[4];
cx q[0],q[1];
cx q[2],q[3];
measure q[0];
measure q[1];
measure q[2];
measure q[3];
measure q[4];

