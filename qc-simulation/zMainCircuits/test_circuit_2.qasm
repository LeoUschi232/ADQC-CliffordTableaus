OPENQASM 3;
include "stdgates.inc";
qreg q[5];
h q[0];
h q[2];
h q[4];
cx q[0],q[1];
cx q[2],q[3];

