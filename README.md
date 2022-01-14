# Ayanami

Implimentation of a market making strategy on the FTX cryptocurrency exchange as described in the 2008 paper by Marco Avellaneda and Sasha Stoikov [High-frequency trading in a limit order book](https://www.math.nyu.edu/~avellane/HighFrequencyTrading.pdf).

## Purpose and Design

The purpose of this project is to serve as a learning tool for C++ and to generate a codebase I can draw on as a portfolio of sorts and to document my progess.

The code follows a procedural style described by [Brian Will](https://www.youtube.com/watch?v=0iyB0_qPvWk) that I liked the sound of after having started learning java and encountering some of the issues he mentions in his videos:

The code is written in **modules**. Modules come in two basic kinds. Namely, **state** modules, and **logic** modules.

### Logic Modules ...
- ... contain no internal state.
- ... do not reach out for external state.
- ... consists only of functions that only touch stateful things that are explicitly passed to them.
- ... are not responsible for managing state. The responsibility of side effects belongs to the callers of logic module code.
- ... are responsible for generating and mutating data only as it says it will in its documentation.
- ... do not call state module code.

### State Modules ...
- ... each protect their own private state.
- ... are encapsulated and should only be interacted with via a public interface.
- ... are not objects.
- ... are not an instance of a datatype. In almost all cases, state modules are singletons and are unapologetic about it.

Both state and logic modules may make use of private functions to either hide implementation from a public interface or to minimize the exposure of state.

Datatypes do not belong to either kind of module and are defined in whichever module where it is most predominantly used or if encapsulation requires it.

As much as possible, state code is moved into logic modules.

## Contributions
I am open to contrubutions however unlikely they are.
