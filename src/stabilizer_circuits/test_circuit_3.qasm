OPENQASM 3;
qreg q[10];
h q[0];
cx q[0],q[1];
cx q[0],q[2];
cx q[0],q[3];
cx q[0],q[4];
h q[5];
cx q[5],q[6];
cx q[5],q[7];
cx q[5],q[8];
cx q[5],q[9];
measure q[0];
measure q[1];
measure q[2];
measure q[3];
measure q[4];
measure q[5];
measure q[6];
measure q[7];
measure q[8];
measure q[9];
