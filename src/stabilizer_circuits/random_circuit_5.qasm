OPENQASM 3;
qreg q[50];
h q[27];
cx q[29],q[35];
cx q[42],q[30];
cx q[42],q[27];
h q[42];
z q[21];
y q[31];
x q[32];
y q[19];
z q[21];
s q[14];
z q[44];
z q[2];
cx q[48],q[13];
z q[19];
h q[23];
z q[39];
cx q[40],q[26];
x q[23];
cx q[28],q[19];
z q[46];
s q[41];
h q[3];
s q[16];
s q[4];
h q[32];
h q[1];
s q[18];
x q[41];
z q[47];
y q[38];
s q[7];
y q[43];
x q[43];
y q[48];
x q[23];
y q[39];
z q[40];
cx q[23],q[26];
z q[39];
h q[33];
cx q[5],q[36];
x q[31];
cx q[29],q[7];
h q[26];
y q[47];
z q[37];
s q[26];
h q[5];
y q[20];
x q[23];
h q[13];
cx q[9],q[38];
h q[36];
h q[22];
cx q[10],q[28];
h q[6];
z q[0];
z q[16];
h q[30];
z q[7];
s q[30];
y q[11];
s q[30];
cx q[19],q[47];
h q[45];
x q[34];
h q[22];
s q[17];
cx q[30],q[21];
cx q[45],q[34];
h q[4];
x q[3];
z q[48];
x q[33];
z q[32];
cx q[33],q[8];
z q[10];
z q[17];
s q[6];
cx q[37],q[15];
cx q[30],q[18];
y q[16];
h q[28];
cx q[1],q[21];
h q[31];
cx q[49],q[47];
cx q[5],q[32];
x q[10];
y q[31];
x q[8];
cx q[49],q[32];
h q[29];
cx q[12],q[20];
y q[23];
z q[23];
h q[12];
x q[31];
z q[7];
x q[16];
h q[5];
s q[33];
y q[32];
z q[15];
s q[6];
z q[38];
cx q[9],q[47];
h q[18];
cx q[33],q[41];
s q[0];
z q[4];
cx q[31],q[41];
x q[33];
s q[4];
z q[48];
s q[48];
y q[43];
y q[23];
cx q[25],q[48];
h q[2];
h q[30];
h q[22];
y q[36];
z q[0];
h q[1];
z q[22];
z q[14];
s q[48];
y q[6];
z q[17];
s q[14];
cx q[24],q[5];
x q[34];
x q[15];
z q[44];
h q[20];
x q[45];
cx q[3],q[10];
y q[34];
y q[28];
x q[28];
x q[43];
cx q[13],q[25];
y q[26];
h q[45];
z q[4];
x q[46];
z q[28];
z q[4];
cx q[46],q[13];
cx q[15],q[0];
x q[33];
h q[42];
y q[6];
s q[32];
cx q[35],q[42];
z q[14];
x q[13];
x q[9];
cx q[19],q[29];
z q[27];
z q[1];
x q[8];
z q[41];
x q[18];
y q[0];
s q[7];
cx q[33],q[28];
s q[13];
z q[35];
z q[36];
z q[14];
y q[48];
y q[21];
z q[12];
cx q[37],q[28];
cx q[19],q[29];
h q[44];
h q[28];
s q[31];
h q[11];
x q[44];
s q[47];
cx q[34],q[22];
y q[22];
s q[42];
cx q[48],q[34];
s q[5];
cx q[14],q[38];
h q[40];
y q[20];
y q[19];
y q[33];
h q[44];
z q[12];
cx q[29],q[15];
s q[44];
x q[48];
x q[34];
z q[29];
cx q[36],q[32];
cx q[25],q[26];
h q[47];
h q[11];
cx q[32],q[19];
s q[21];
z q[30];
s q[30];
h q[23];
s q[0];
z q[23];
z q[15];
cx q[35],q[33];
x q[14];
y q[14];
cx q[19],q[30];
cx q[37],q[21];
h q[43];
y q[6];
h q[5];
x q[14];
y q[4];
z q[28];
cx q[17],q[29];
s q[27];
z q[28];
z q[1];
s q[32];
y q[48];
cx q[32],q[16];
y q[21];
cx q[11],q[44];
z q[7];
s q[18];
x q[4];
s q[21];
h q[49];
y q[44];
y q[13];
s q[40];
s q[26];
s q[35];
y q[22];
y q[5];
s q[4];
z q[45];
cx q[17],q[35];
y q[23];
x q[49];
x q[42];
s q[7];
x q[45];
s q[43];
x q[1];
y q[8];
s q[25];
s q[30];
x q[8];
y q[6];
y q[38];
s q[42];
x q[43];
h q[40];
x q[20];
s q[28];
cx q[6],q[20];
s q[1];
y q[3];
h q[49];
h q[34];
s q[18];
h q[22];
y q[21];
z q[36];
cx q[2],q[43];
z q[18];
s q[48];
z q[0];
s q[42];
z q[11];
cx q[0],q[38];
y q[17];
s q[47];
cx q[36],q[37];
cx q[8],q[16];
s q[26];
cx q[24],q[2];
s q[16];
x q[9];
y q[8];
z q[0];
z q[8];
y q[39];
z q[23];
x q[11];
cx q[43],q[17];
z q[47];
h q[46];
z q[30];
s q[35];
z q[29];
z q[1];
z q[39];
y q[8];
s q[25];
cx q[31],q[2];
y q[28];
cx q[34],q[11];
x q[49];
h q[46];
y q[13];
cx q[30],q[33];
y q[26];
s q[43];
s q[29];
z q[37];
s q[36];
s q[48];
z q[15];
x q[27];
y q[19];
h q[10];
z q[10];
z q[11];
z q[9];
h q[10];
z q[47];
cx q[28],q[36];
z q[22];
s q[24];
h q[48];
x q[11];
h q[34];
y q[12];
cx q[4],q[2];
s q[2];
y q[21];
x q[24];
x q[15];
cx q[44],q[34];
x q[48];
s q[18];
cx q[30],q[8];
s q[27];
z q[1];
z q[42];
cx q[3],q[37];
z q[33];
z q[23];
y q[22];
z q[33];
s q[26];
h q[30];
x q[44];
x q[35];
h q[49];
h q[23];
y q[10];
x q[22];
x q[33];
x q[45];
h q[13];
x q[6];
cx q[1],q[11];
x q[37];
s q[44];
cx q[16],q[45];
x q[19];
z q[32];
z q[29];
h q[16];
s q[41];
x q[25];
s q[31];
s q[0];
x q[43];
y q[15];
y q[13];
h q[21];
cx q[39],q[44];
h q[9];
x q[33];
h q[47];
cx q[22],q[34];
x q[24];
cx q[10],q[39];
x q[47];
x q[11];
h q[36];
cx q[44],q[12];
cx q[15],q[10];
z q[47];
s q[25];
s q[23];
y q[1];
x q[35];
z q[10];
z q[7];
h q[21];
cx q[36],q[18];
h q[32];
s q[23];
h q[10];
x q[13];
x q[9];
x q[29];
x q[40];
y q[43];
cx q[37],q[5];
h q[33];
h q[25];
h q[13];
h q[6];
x q[8];
h q[35];
s q[35];
z q[19];
z q[23];
cx q[28],q[42];
y q[9];
z q[10];
x q[7];
y q[8];
s q[24];
s q[6];
h q[17];
z q[36];
y q[47];
s q[1];
x q[38];
s q[37];
z q[37];
h q[4];
cx q[45],q[10];
cx q[4],q[37];
z q[27];
z q[36];
s q[29];
s q[2];
z q[48];
cx q[10],q[14];
z q[14];
z q[12];
s q[33];
z q[5];
cx q[3],q[0];
y q[27];
z q[46];
s q[0];
cx q[33],q[41];
x q[39];
y q[49];
y q[14];
z q[35];
cx q[29],q[9];
z q[3];
z q[25];
cx q[24],q[29];
x q[48];
h q[39];
x q[43];
z q[30];
y q[16];
s q[10];
s q[48];
h q[22];
y q[11];
cx q[43],q[47];
z q[24];
s q[47];
h q[35];
y q[39];
h q[24];
h q[31];
z q[35];
x q[43];
x q[24];
x q[14];
s q[42];
s q[42];
h q[9];
s q[30];
z q[38];
s q[0];
z q[48];
x q[17];
cx q[43],q[7];
x q[39];
x q[49];
cx q[49],q[23];
x q[37];
y q[24];
y q[0];
h q[31];
cx q[13],q[18];
y q[20];
cx q[6],q[21];
x q[41];
cx q[14],q[9];
s q[20];
y q[25];
cx q[6],q[11];
x q[49];
h q[4];
y q[20];
cx q[43],q[28];
y q[48];
cx q[17],q[48];
y q[39];
cx q[45],q[20];
h q[38];
h q[17];
z q[16];
h q[19];
cx q[4],q[15];
cx q[20],q[38];
s q[11];
h q[46];
h q[6];
y q[16];
x q[2];
cx q[47],q[36];
h q[0];
y q[0];
z q[26];
x q[38];
h q[15];
z q[7];
h q[44];
x q[3];
z q[12];
cx q[4],q[33];
x q[33];
cx q[40],q[12];
s q[21];
x q[21];
y q[37];
h q[27];
s q[41];
z q[43];
y q[18];
z q[36];
cx q[4],q[13];
cx q[12],q[6];
cx q[29],q[2];
s q[23];
z q[15];
s q[24];
h q[13];
x q[22];
cx q[22],q[26];
h q[34];
cx q[22],q[34];
z q[42];
s q[14];
z q[21];
s q[18];
h q[41];
cx q[9],q[25];
cx q[39],q[4];
y q[2];
z q[33];
h q[34];
h q[10];
z q[38];
h q[42];
x q[38];
s q[34];
y q[12];
x q[8];
x q[18];
x q[3];
y q[29];
y q[0];
h q[13];
cx q[44],q[18];
h q[6];
h q[9];
y q[38];
h q[22];
x q[46];
z q[2];
h q[35];
z q[39];
cx q[24],q[3];
cx q[23],q[25];
z q[44];
h q[15];
z q[24];
y q[28];
z q[20];
y q[47];
s q[8];
h q[32];
y q[23];
x q[1];
h q[39];
h q[21];
x q[27];
cx q[25],q[7];
h q[26];
y q[7];
y q[34];
cx q[32],q[13];
y q[26];
z q[6];
h q[16];
cx q[19],q[7];
z q[47];
cx q[7],q[9];
h q[6];
z q[45];
h q[28];
z q[27];
h q[4];
h q[22];
s q[45];
z q[44];
x q[4];
cx q[22],q[40];
z q[36];
cx q[43],q[19];
s q[4];
y q[45];
h q[21];
cx q[34],q[23];
x q[34];
y q[29];
x q[16];
s q[35];
x q[37];
x q[1];
y q[31];
cx q[36],q[12];
y q[38];
z q[8];
y q[0];
h q[39];
cx q[15],q[47];
cx q[11],q[22];
x q[25];
h q[29];
cx q[47],q[42];
s q[27];
y q[22];
s q[4];
y q[47];
cx q[31],q[28];
x q[43];
x q[41];
h q[7];
z q[45];
x q[49];
cx q[40],q[4];
cx q[7],q[4];
y q[31];
z q[31];
z q[19];
h q[47];
cx q[3],q[46];
x q[21];
x q[22];
z q[12];
z q[36];
y q[42];
x q[37];
x q[1];
cx q[15],q[47];
z q[5];
z q[17];
x q[22];
z q[17];
h q[19];
h q[0];
cx q[26],q[9];
s q[42];
y q[20];
y q[26];
s q[46];
s q[34];
y q[4];
s q[30];
h q[47];
z q[4];
h q[43];
x q[4];
h q[22];
x q[2];
cx q[16],q[4];
s q[11];
cx q[11],q[30];
x q[41];
cx q[1],q[26];
cx q[0],q[25];
s q[21];
cx q[32],q[3];
z q[27];
cx q[12],q[1];
s q[11];
s q[29];
h q[12];
y q[38];
h q[6];
y q[18];
x q[0];
x q[24];
x q[5];
h q[49];
y q[30];
z q[12];
x q[48];
cx q[18],q[49];
cx q[2],q[20];
cx q[15],q[8];
y q[41];
s q[31];
z q[40];
y q[24];
x q[32];
z q[49];
z q[18];
x q[3];
z q[15];
x q[39];
cx q[40],q[14];
s q[3];
y q[12];
cx q[34],q[33];
h q[19];
z q[12];
h q[31];
y q[33];
h q[46];
x q[25];
y q[42];
h q[21];
x q[24];
cx q[27],q[21];
z q[14];
y q[41];
h q[35];
s q[36];
h q[20];
h q[22];
y q[18];
s q[48];
cx q[41],q[18];
h q[46];
y q[19];
s q[2];
cx q[36],q[11];
z q[22];
z q[17];
cx q[46],q[40];
s q[12];
x q[49];
z q[19];
x q[48];
cx q[34],q[45];
h q[44];
h q[14];
z q[6];
s q[49];
h q[12];
s q[12];
cx q[11],q[5];
z q[24];
cx q[47],q[44];
x q[11];
s q[17];
y q[34];
h q[19];
s q[2];
s q[45];
s q[36];
z q[5];
y q[44];
y q[31];
h q[13];
z q[6];
cx q[18],q[16];
y q[37];
x q[34];
s q[11];
cx q[39],q[8];
s q[25];
y q[22];
x q[14];
z q[15];
cx q[44],q[41];
z q[17];
y q[11];
cx q[36],q[25];
s q[27];
h q[47];
x q[10];
cx q[31],q[27];
s q[43];
y q[25];
x q[47];
x q[17];
cx q[37],q[1];
s q[34];
s q[7];
h q[48];
h q[6];
z q[49];
h q[35];
h q[22];
z q[35];
s q[3];
z q[30];
x q[14];
y q[33];
x q[7];
y q[22];
h q[20];
z q[34];
s q[6];
s q[18];
x q[30];
y q[5];
x q[19];
y q[48];
z q[44];
x q[3];
h q[48];
s q[0];
x q[27];
z q[48];
s q[13];
h q[7];
cx q[29],q[12];
h q[44];
x q[10];
x q[20];
x q[28];
h q[27];
s q[48];
x q[13];
z q[13];
s q[22];
s q[48];
h q[20];
h q[1];
cx q[12],q[44];
h q[25];
z q[35];
s q[15];
z q[13];
cx q[18],q[44];
cx q[26],q[1];
x q[37];
s q[31];
x q[16];
cx q[16],q[46];
cx q[48],q[43];
h q[8];
x q[2];
h q[45];
y q[12];
h q[16];
s q[22];
x q[44];
z q[5];
h q[25];
y q[17];
y q[25];
h q[37];
s q[19];
z q[34];
s q[26];
h q[31];
s q[47];
y q[35];
s q[44];
y q[10];
y q[33];
cx q[17],q[31];
x q[33];
y q[27];
h q[43];
z q[13];
y q[27];
s q[7];
s q[14];
cx q[42],q[1];
cx q[31],q[35];
cx q[14],q[0];
z q[23];
x q[18];
y q[1];
z q[26];
y q[27];
x q[46];
z q[18];
cx q[4],q[25];
s q[20];
y q[7];
cx q[1],q[21];
s q[17];
z q[45];
y q[31];
h q[0];
y q[13];
s q[48];
cx q[10],q[34];
h q[5];
s q[4];
x q[28];
s q[14];
z q[34];
x q[26];
z q[33];
s q[36];
h q[47];
y q[19];
cx q[0],q[11];
h q[32];
cx q[22],q[30];
h q[48];
h q[29];
x q[41];
x q[48];
h q[45];
s q[0];
y q[33];
cx q[34],q[22];
s q[40];
y q[34];
h q[25];
z q[32];
s q[16];
h q[1];
s q[39];
y q[45];
cx q[4],q[27];
cx q[22],q[49];
x q[25];
h q[19];
cx q[34],q[40];
z q[4];
y q[23];
s q[11];
cx q[41],q[20];
h q[26];
z q[31];
z q[44];
s q[44];
s q[44];
y q[30];
cx q[16],q[6];
cx q[20],q[49];
s q[27];
z q[43];
y q[31];
h q[25];
s q[18];
h q[46];
z q[27];
x q[27];
s q[6];
z q[46];
cx q[34],q[41];
x q[14];
cx q[48],q[2];
z q[45];
x q[5];
y q[1];
cx q[5],q[8];
z q[15];
cx q[19],q[12];
z q[47];
z q[28];
s q[15];
z q[45];
x q[8];
s q[29];
s q[44];
h q[29];
x q[22];
x q[11];
s q[45];
h q[29];
s q[8];
z q[7];
h q[33];
z q[16];
z q[22];
z q[31];
x q[3];
x q[18];
cx q[34],q[45];
s q[12];
y q[43];
x q[1];
x q[21];
z q[2];
h q[25];
cx q[3],q[23];
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
measure q[16];
measure q[17];
measure q[18];
measure q[19];
measure q[20];
measure q[21];
measure q[22];
measure q[23];
measure q[24];
measure q[25];
measure q[26];
measure q[27];
measure q[28];
measure q[29];
measure q[30];
measure q[31];
measure q[32];
measure q[33];
measure q[34];
measure q[35];
measure q[36];
measure q[37];
measure q[38];
measure q[39];
measure q[40];
measure q[41];
measure q[42];
measure q[43];
measure q[44];
measure q[45];
measure q[46];
measure q[47];
measure q[48];
measure q[49];
