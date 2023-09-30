#include <systemc.h>

SC_MODULE(registers)
{
        sc_in<sc_uint<4>> data_in;
        sc_out<sc_uint<4>> data_out;
        sc_in<bool> clk, write_enable;

        sc_uint<4> reg;

        void p1()
        {
                if (write_enable.read())
                {
                        reg = data_in.read();
                }
                data_out.write(reg);
        }

        SC_CTOR(registers)
        {
                SC_METHOD(p1);
                sensitive << clk.pos();
        }
};
