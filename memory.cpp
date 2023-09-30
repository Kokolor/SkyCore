#include <systemc.h>

SC_MODULE(memory)
{
        sc_in<sc_uint<4>> address;
        sc_in<sc_uint<4>> data_in;
        sc_out<sc_uint<4>> data_out;
        sc_in<bool> read_enable, write_enable;

        sc_uint<4> mem[16];

        void p1()
        {
                if (write_enable.read())
                {
                        mem[address.read()] = data_in.read();
                }
                if (read_enable.read())
                {
                        data_out.write(mem[address.read()]);
                }
        }

        SC_CTOR(memory)
        {
                SC_METHOD(p1);
                sensitive << address << read_enable << write_enable;
        }
};
