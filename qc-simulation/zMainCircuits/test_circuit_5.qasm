OPENQASM 3;
include "stdgates.inc";
qreg q[3];
x q[0];
x q[1];
cx q[0],q[2];
cx q[1],q[0];