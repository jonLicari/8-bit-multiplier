#include <systemc.h>

#include "mul.h"

void make_mul() {
	sc_trace_file *tf;
	
	sc_signal<sc_bv<8> > regA, regB;
	sc_signal<sc_bv<16> > sout;
	sc_clock clk("clk", 10, SC_NS, 0.5);

	mul mult("multiplier"); // Create DUT

	mult.clk(clk);
	mult.rA(regA);
	mult.rB(regB);
	mult.sout(sout);

	tf = sc_create_vcd_trace_file("mul_trace");
	tf->set_time_unit(1, SC_NS);
	
	sc_trace(tf, clk, "clk");
	sc_trace(tf, regA, "register_a");
	sc_trace(tf, regB, "register_b");
	sc_trace(tf, sout, "sum_out");

	//Test conditions
	regA.write(10); regB.write(12);
	sc_start(10, SC_NS);
	cout << "\n\nSum Out = " << sout << endl;

	regA.write(8); regB.write(8);
	sc_start(10, SC_NS);
	cout << "\n\nSum Out = " << sout << endl;

	regA.write(128); regB.write(64);
	sc_start(10, SC_NS);
	cout << "\n\nSum Out = " << sout << endl;

	regA.write(170); regB.write(85);
	sc_start(10, SC_NS);
	cout << "\n\nSum Out = " << sout << endl;
}

int sc_main( int argc, char* argv[]) {
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	// Ignores deprecated features warning
	make_mul();

	return 0;
}