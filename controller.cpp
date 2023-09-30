#include <systemc.h>

SC_MODULE(controller)
{
        sc_in<sc_uint<4>> instruction;
        sc_out<bool> halt_signal;
        sc_out<bool> add_signal;

        void p1()
        {
                if (instruction.read() == 0xF)
                { // HALT
                        halt_signal.write(true);
                        add_signal.write(false);
                }
                else if (instruction.read() == 0x1)
                { // ADD
                        halt_signal.write(false);
                        add_signal.write(true);
                }
                else
                {
                        halt_signal.write(false);
                        add_signal.write(false);
                }
        }

        SC_CTOR(controller)
        {
                SC_METHOD(p1);
                sensitive << instruction;
        }
};
