OPENQASM 3;
qreg q[16];
h q[15];
s q[15];
s q[15];
h q[15];
h q[15];
h q[0];
cx q[0],q[15];
h q[0];
h q[1];
cx q[1],q[15];
h q[1];
h q[2];
cx q[2],q[15];
h q[2];
h q[3];
cx q[3],q[15];
h q[3];
h q[4];
cx q[4],q[15];
h q[4];
h q[5];
cx q[5],q[15];
h q[5];
h q[6];
cx q[6],q[15];
h q[6];
h q[7];
cx q[7],q[15];
h q[7];
h q[8];
cx q[8],q[15];
h q[8];
h q[9];
cx q[9],q[15];
h q[9];
h q[10];
cx q[10],q[15];
h q[10];
h q[11];
cx q[11],q[15];
h q[11];
h q[12];
cx q[12],q[15];
h q[12];
h q[13];
cx q[13],q[15];
h q[13];
h q[14];
cx q[14],q[15];
h q[14];
h q[15];
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
measure q[10];
measure q[11];
measure q[12];
measure q[13];
measure q[14];
measure q[15];
