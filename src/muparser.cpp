#include <iostream>
#include <muParser.h>

// g++ muparser.cpp -o muparser -lmuparser

/// main program
int main_muparser(int argc, char* argv[])
{
  using namespace mu;

  try
  {
    std::string formula = "exp(-0.0565/sqrt(e0))*(1.-exp(-3.284/sqrt(e0)))";
    double e0 = 3.27;

	mu::Parser p;
	p.DefineVar("e0", &e0);
	p.SetExpr(formula);
	double eff0 =  p.Eval();
	std::cout << eff0 << std::endl;
  }
  catch (Parser::exception_type &e)
  {
    std::cout << e.GetMsg() << std::endl;
  }
  return 0;
}
