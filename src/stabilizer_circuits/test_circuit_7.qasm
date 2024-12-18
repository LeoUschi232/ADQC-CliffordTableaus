OPENQASM 3;
qreg q[10];

h q[0];

s q[1];
h q[1];

h q[2];
s q[2];
h q[2];

s q[3];
h q[3];
s q[3];
h q[3];

h q[4];
s q[4];
h q[4];
s q[4];
h q[4];

s q[5];
h q[5];
s q[5];
h q[5];
s q[5];
h q[5];

h q[6];
s q[6];
h q[6];
s q[6];
h q[6];
s q[6];
h q[6];

h q[7];
s q[7];
h q[7];
s q[7];
h q[7];
s q[7];
h q[7];
s q[7];
h q[7];

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