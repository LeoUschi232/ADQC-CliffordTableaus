OPENQASM 3;
qreg q[5];
x q[0];
x q[2];
x q[3];
measure q[0];
measure q[1];
measure q[2];
measure q[3];
measure q[4];
