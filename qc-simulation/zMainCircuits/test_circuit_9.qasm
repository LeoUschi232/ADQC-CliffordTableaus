OPENQASM 3;
include "stdgates.inc";
qreg q[4];
h q[0];
h q[1];
cx q[1],q[2];
cx q[1],q[2];
h q[2];
y q[0];
cx q[2],q[3];
z q[1];
s q[2];
cx q[3],q[0];
cx q[3],q[0];
s q[0];
