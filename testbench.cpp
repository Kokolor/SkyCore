#include "alu.cpp"
#include "registers.cpp"
#include "memory.cpp"
#include "controller.cpp"

int sc_main(int argc, char *argv[])
{
        sc_signal<sc_uint<4>> a, b, result, data_in, data_out;
        sc_signal<sc_uint<3>> op;
        sc_signal<sc_uint<4>> address, data_mem_in, data_mem_out;
        sc_signal<bool> read_enable, write_enable;
        sc_signal<bool> clk;
        sc_signal<sc_uint<4>> instruction;

        sc_signal<bool> halt_signal;
        sc_signal<bool> add_signal;

        alu alu1("ALU");
        alu1.a(a);
        alu1.b(b);
        alu1.op(op);
        alu1.result(result);

        registers reg1("Registers");
        reg1.data_in(data_in);
        reg1.data_out(data_out);
        reg1.clk(clk);
        reg1.write_enable(write_enable);

        memory mem1("Memory");
        mem1.address(address);
        mem1.data_in(data_mem_in);
        mem1.data_out(data_mem_out);
        mem1.read_enable(read_enable);
        mem1.write_enable(write_enable);

        controller ctrl1("Controller");
        ctrl1.instruction(instruction);
        ctrl1.halt_signal(halt_signal);
        ctrl1.add_signal(add_signal);

        a = 1;
        b = 2;
        data_in = 3;
        write_enable = true;
        address = 0;
        data_mem_in = 4;
        read_enable = false;
        instruction = 0;

        FILE *program = fopen("program.bin", "rb");
        if (!program)
        {
                printf("Error opening program.bin.\n");
                return 1;
        }

        unsigned char opcode;
        int addr = 0;
        while (fread(&opcode, 1, 1, program) == 1)
        {
                address = addr;
                data_mem_in = opcode;
                write_enable = true;
                sc_start(1, SC_NS);
                addr++;
        }
        fclose(program);

        address = 0;
        read_enable = false;
        write_enable = false;

        while (true)
        {
                read_enable = true;
                sc_start(1, SC_NS);
                read_enable = false;

                instruction = data_mem_out.read();

                sc_start(1, SC_NS);

                if (add_signal.read())
                {
                        op = 0;
                        cout << "ADD instruction received. Result: " << result.read() << endl;
                }

                if (halt_signal.read())
                {
                        cout << "HLT instruction received. Halting simulation." << endl;
                        break;
                }

                address = address.read() + 1;
        }

        return 0;
}
