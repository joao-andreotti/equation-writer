# 📖 EquationWriter 

EquationWriter is a simple header only library that facilitate the process of writing linear systems of equations in C++. 

The syntax is meant to imitate how equations are writen in normal math notation:

```c++
Context c;
Variable x = c.CreateVariable("x");
Variable y = c.CreateVariable("y");
Variable z = c.CreateVariable("z");

Equation eq1 = 2 * x + 3 * y == 4.0;
Equation eq2 = 3 * x  == 5 - 4 * y - 10 + x;
Equation eq3 = 1 + z - 4 * x + 5 * y + 2 == 6;

LinearSystem system;
system.AddEquation(eq1);
system.AddEquation(eq2);
system.AddEquation(eq3);
```

The code above creates three equations and adds them to a system.

The system can then be used to fill the left and right hand sides of the equation into a generic matrix type (for instance Eigen's matrix types). The only requirement is that the matrix type must implement indexing through parenthesis (e.g. `m(1,2)` gets the element at the first row and second column of `m`).

```c++
auto system_size = system.GetMatrixDimension(c);
Eigen::MatrixXd m(system_size.first, system_size.second);
Eigen::VectorXd rhs(system_size.first);

system.FillMatrix(m);
system.FillRightSide(rhs);
```