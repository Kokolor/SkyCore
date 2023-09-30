#include <systemc.h>

SC_MODULE(alu)
{
  sc_in<sc_uint<4>> a, b;
  sc_in<sc_uint<3>> op;
  sc_out<sc_uint<4>> result;

  void p1()
  {
    switch (op.read())
    {
    case 0:
      result.write(a.read() + b.read());
      break;
    case 1:
      result.write(a.read() - b.read());
      break;
    case 2:
      result.write(a.read() & b.read());
      break;
    case 3:
      result.write(a.read() | b.read());
      break;
    case 4:
      result.write(a.read() ^ b.read());
      break;
    case 5:
      result.write(~a.read());
      break;
    default:
      result.write(0);
      break;
    }
  }

  SC_CTOR(alu)
  {
    SC_METHOD(p1);
    sensitive << a << b << op;
  }
};
