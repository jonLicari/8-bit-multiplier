#include <systemc.h>
#include "mul.h"

sc_bv<8> a, b; // Input register arrays

//sc_bv<4> a, b;
sc_bv<16> co; sc_bv<16> so; // Carry-out array and Sum-out array

//sc_bv<8> p;	// Output product
sc_bv<16> p;

sc_bit andgt; // stores AND gate output



void cpa(sc_bit aval, sc_bit bval, sc_bit cval, int indexa, int indexb) {
	

	so[indexa] = ((aval^bval)^cval);

	co[indexa] = (aval&bval)|(cval&(aval^bval));


	if (indexa == 0) { // if the index a is 0, the product is directly equal to sum out

		p[indexb] = so[indexa];
		//cout << "Pout = " << p << endl;

	}

	// else {essentially do nothing

}



void csa (sc_bit a, sc_bit b, sc_bit c, sc_bit s, int indexa, int indexb) {



	andgt = a&b; // performs A.B
	//cout << "AND A.B = " << andgt << endl;
	//cout << "index = " << indexa << endl;

	cpa(andgt, s, c, indexa, indexb); // Sends the variables to the full adder function 

}

void mul :: multiply() {
	// Write in values to a and b 
	a = rA.read(); b = rB.read();
	// Initialize/ reset other variables
	//co = "00000000"; so = "00000000"; p = "00000000"; // For 4 bit mult
	co = "0000000000000000"; so = "0000000000000000"; p = "0000000000000000"; // 8 bit 

	sc_bit ta, tb; // Temporary variable for holding specific bit index of array a and b

	sc_bit sin, cin; // Temp var for holding the sum-in and carry-in bit

	

	//printf( "\n4 x 4 Multiplier\n\n" );
	printf( "\n8 x 8 Multiplier\n\n" );
	cout << "Reg. A = " << a << endl;
	cout << "Reg. B = " << b << endl; 

	

	for (int m=0; m<8; m++) { // 8 - 8bit, 4 - 4bit

		for (int n=0; n<8; n++) { // 8 - 8bit, 4 - 4bit

			tb = b[m]; ta = a[n]; // Assign current index of a and b to temp value

			cin = co[n]; // Carry in tracks the a array index

			

			if (n == 7) { // 7 - 8bit, 3 - 4bit

				sin = 0;

			}

			else {
				//cout << "Sum In = " << sin << endl;

				sin = so[n+1]; // Sum in is the value of the previous sum of index n+1
				//cout << "Sum In = " << sin << endl;

			}
		//cout << "\n\nm = " << m << endl;
		//cout << "n = " << n << endl;
		//cout << "tA = " << ta << endl;
		//cout << "tb = " << tb << endl;
		//cout << "cin = " << cin << endl;
		//cout << "sin = " << sin << endl;

		csa(ta, tb, cin, sin, n, m);

		}
	}
	// cpa (bit A, bit B, bit C, int Indexa, int indexb)
	//MSB-3
	ta = so[1]; tb = co[0]; cin = 0;
	cpa(ta, tb, cin, 8, 0);
	p[8] = so[8];
	//MSB-2
	ta = so[2]; tb = co[1]; cin = co[8];
	cpa(ta, tb, cin, 9, 0);
	p[9] = so[9];
	//MSB-1
	ta = so[3]; tb = co[2]; cin = co[9];
	cpa(ta, tb, cin, 10, 0);
	p[10] = so[10];

	ta = so[4]; tb = co[3]; cin = co[10];
	cpa(ta, tb, cin, 11, 0);
	p[11] = so[11];

	ta = so[5]; tb = co[4]; cin = co[11];
	cpa(ta, tb, cin, 12, 0);
	p[12] = so[12];

	ta = so[6]; tb = co[5]; cin = co[12];
	cpa(ta, tb, cin, 13, 0);
	p[13] = so[13];

	ta = so[7]; tb = co[6]; cin = co[13];
	cpa(ta, tb, cin, 14, 0);
	p[14] = so[14];
	//MSB
	ta = co[7]; tb = co[14]; cin = 0;
	cpa(ta, tb, cin, 15, 0);
	p[15] = so[15];

	//cout << "\n\nProduct = " << p << endl;
	sout.write(p);
}