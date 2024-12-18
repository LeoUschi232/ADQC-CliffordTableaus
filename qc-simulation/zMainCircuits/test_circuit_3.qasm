OPENQASM 3;
include "stdgates.inc";
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

