OPENQASM 3;
qreg q[25];
y q[19];
h q[7];
z q[0];
cx q[12],q[15];
h q[11];
x q[18];
s q[20];
y q[12];
y q[14];
x q[5];
s q[0];
cx q[4],q[17];
z q[19];
cx q[6],q[4];
y q[6];
x q[2];
cx q[3],q[17];
s q[17];
h q[23];
x q[20];
z q[0];
s q[8];
h q[12];
y q[22];
cx q[20],q[4];
x q[15];
y q[0];
x q[18];
x q[21];
s q[7];
x q[18];
h q[22];
z q[13];
h q[17];
z q[3];
z q[13];
x q[10];
cx q[3],q[19];
z q[9];
x q[14];
s q[16];
x q[4];
s q[11];
cx q[20],q[10];
y q[2];
h q[15];
cx q[7],q[12];
measure q[1];
z q[16];
cx q[1],q[15];
y q[19];
x q[20];
cx q[0],q[13];
s q[15];
h q[22];
z q[8];
z q[7];
h q[13];
x q[2];
y q[8];
z q[7];
h q[10];
z q[2];
x q[1];
h q[20];
x q[21];
x q[1];
y q[10];
s q[15];
y q[3];
y q[13];
z q[18];
y q[20];
x q[3];
h q[4];
y q[19];
h q[21];
h q[20];
z q[8];
s q[7];
cx q[18],q[14];
x q[7];
h q[21];
y q[22];
h q[24];
x q[8];
z q[11];
x q[4];
s q[21];
z q[9];
s q[7];
x q[2];
z q[3];
cx q[20],q[21];
cx q[3],q[16];
h q[9];
x q[14];
z q[23];
cx q[10],q[24];
z q[8];
x q[11];
cx q[14],q[20];
z q[3];
h q[6];
x q[4];
h q[14];
s q[9];
cx q[22],q[15];
x q[13];
x q[9];
h q[14];
x q[0];
h q[0];
y q[13];
y q[8];
cx q[3],q[1];
x q[1];
h q[7];
y q[5];
z q[8];
x q[16];
y q[19];
measure q[5];
y q[0];
s q[5];
measure q[10];
cx q[9],q[7];
s q[5];
y q[15];
h q[2];
cx q[8],q[14];
s q[1];
cx q[5],q[21];
s q[13];
z q[19];
x q[13];
y q[21];
x q[8];
s q[10];
z q[17];
h q[15];
y q[20];
x q[12];
cx q[3],q[14];
cx q[15],q[6];
y q[7];
z q[7];
s q[12];
y q[0];
z q[0];
y q[7];
s q[8];
s q[6];
cx q[0],q[13];
y q[16];
measure q[14];
y q[9];
cx q[11],q[18];
x q[7];
z q[3];
s q[1];
cx q[9],q[24];
h q[21];
s q[8];
x q[23];
y q[12];
z q[12];
x q[24];
cx q[2],q[11];
y q[8];
h q[7];
h q[20];
y q[12];
h q[11];
h q[14];
cx q[2],q[21];
measure q[21];
y q[1];
x q[8];
x q[11];
y q[15];
cx q[19],q[2];
s q[17];
s q[13];
z q[14];
z q[18];
h q[0];
x q[21];
s q[8];
s q[3];
z q[14];
z q[2];
cx q[7],q[12];
s q[12];
y q[0];
s q[16];
h q[14];
cx q[3],q[5];
z q[1];
x q[5];
cx q[8],q[21];
s q[2];
z q[1];
y q[4];
y q[12];
cx q[22],q[6];
y q[9];
z q[8];
h q[5];
z q[0];
z q[18];
x q[7];
y q[2];
z q[24];
cx q[18],q[5];
y q[11];
z q[18];
y q[14];
s q[24];
y q[3];
z q[20];
z q[4];
y q[17];
h q[16];
y q[5];
y q[1];
x q[12];
cx q[6],q[23];
z q[13];
z q[17];
h q[5];
h q[22];
h q[9];
x q[16];
measure q[23];
z q[8];
y q[23];
z q[1];
x q[14];
x q[5];
y q[13];
y q[3];
x q[0];
z q[18];
h q[24];
s q[8];
cx q[14],q[19];
x q[4];
z q[14];
measure q[0];
y q[21];
cx q[20],q[14];
y q[20];
x q[17];
h q[4];
z q[3];
y q[9];
y q[10];
y q[18];
s q[17];
z q[4];
z q[2];
cx q[10],q[5];
cx q[4],q[16];
y q[12];
cx q[19],q[20];
cx q[20],q[2];
s q[5];
x q[20];
y q[24];
y q[14];
z q[6];
z q[14];
s q[21];
s q[4];
x q[3];
h q[10];
cx q[9],q[7];
x q[16];
y q[0];
s q[23];
z q[0];
z q[13];
z q[11];
cx q[16],q[18];
x q[1];
h q[13];
h q[6];
x q[9];
y q[8];
z q[4];
z q[0];
s q[20];
y q[23];
h q[14];
y q[5];
z q[19];
x q[14];
s q[21];
h q[14];
x q[15];
s q[5];
x q[19];
measure q[12];
s q[15];
cx q[13],q[0];
s q[21];
h q[18];
x q[24];
y q[4];
h q[4];
s q[11];
h q[0];
z q[12];
s q[0];
z q[12];
z q[4];
s q[21];
h q[22];
measure q[4];
z q[19];
s q[0];
h q[17];
z q[21];
y q[8];
h q[18];
s q[10];
cx q[11],q[14];
h q[10];
x q[0];
cx q[2],q[18];
y q[8];
s q[18];
y q[2];
h q[9];
s q[17];
h q[9];
x q[1];
s q[21];
cx q[5],q[18];
s q[14];
s q[4];
y q[7];
y q[18];
cx q[16],q[14];
h q[20];
cx q[23],q[8];
h q[10];
h q[2];
cx q[2],q[20];
s q[22];
s q[19];
y q[17];
cx q[9],q[10];
x q[21];
x q[7];
x q[9];
z q[4];
x q[6];
x q[23];
s q[20];
cx q[6],q[18];
x q[11];
x q[12];
x q[15];
y q[16];
x q[9];
s q[5];
y q[11];
z q[22];
y q[1];
x q[24];
s q[6];
s q[7];
h q[11];
cx q[21],q[22];
h q[7];
h q[4];
y q[0];
s q[8];
s q[1];
x q[7];
x q[4];
s q[18];
z q[1];
cx q[6],q[8];
s q[22];
h q[8];
measure q[11];
cx q[6],q[3];
s q[13];
y q[20];
z q[6];
y q[10];
y q[7];
cx q[0],q[2];
y q[21];
h q[20];
z q[6];
s q[10];
x q[17];
y q[10];
s q[8];
h q[13];
y q[19];
s q[15];
cx q[21],q[14];
s q[13];
y q[1];
z q[13];
h q[24];
x q[3];
h q[9];
x q[9];
x q[7];
z q[10];
s q[10];
x q[12];
z q[0];
z q[22];
z q[1];
x q[7];
h q[5];
cx q[9],q[6];
y q[19];
h q[0];
h q[10];
x q[10];
measure q[4];
x q[13];
z q[21];
s q[18];
y q[14];
z q[22];
cx q[1],q[3];
h q[24];
measure q[11];
s q[5];
y q[24];
x q[15];
s q[7];
s q[9];
s q[23];
cx q[20],q[6];
x q[15];
cx q[1],q[20];
s q[15];
h q[7];
s q[9];
z q[6];
s q[5];
h q[15];
z q[5];
x q[23];
s q[6];
x q[17];
x q[16];
cx q[6],q[8];
h q[3];
y q[9];
measure q[11];
y q[20];
cx q[24],q[22];
z q[17];
z q[6];
y q[4];
z q[21];
z q[1];
x q[21];
x q[23];
h q[19];
y q[21];
cx q[0],q[20];
z q[6];
x q[24];
x q[4];
s q[14];
x q[10];
y q[23];
x q[11];
s q[3];
x q[19];
s q[2];
cx q[18],q[9];
y q[0];
h q[19];
cx q[14],q[8];
h q[20];
s q[15];
y q[0];
x q[0];
s q[7];
cx q[13],q[17];
cx q[8],q[22];
s q[10];
cx q[23],q[10];
y q[9];
x q[21];
x q[9];
measure q[2];