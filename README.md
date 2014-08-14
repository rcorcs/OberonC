
# Oberon-0 Compiler

An educational compiler for a subset of Oberon version 1.0

## Quickstart

#### Windows

oberonc.exe is the compiler executable.
It generates an assembly file compiled from the source code.

After oberonc has generated the assembly file, you execute
the GNU Assembler (GAS, as) to generate the object file and then
execute the GNU Linker ( ld ) to create the executable file of 
your program.

Files:
bin/oberonc.exe
bin/gas/as.exe
bin/gas/ld.exe

The batches intend to simplify these steps.

Once you've created the assembly file, you can
just execute the assemble.cmd and type the 
name of the assembly file, without the extension (.s) .

The build.cmd do all the steps. It means that you
can just execute the build.cmd and type the name
of the source file, without the extension (.obe),
and it will call the compiler, the assembler and
the linker.

#### Linux

oberonc is the compiler executable.
It generates an assembly file compiled from the source code.

After oberonc has generated the assembly file, you can execute the GNU C Compiler (gcc) to generate the executable file of your program.

The build.sh do all the steps. It means that you can just execute the bash.sh passing the path of your source file as an argument, then it will call the Oberon-0 compiler and the GNU C Compiler (gcc) generating the executable in the same folder of you source file.

## TODO

Finish support to x64 architecture.

Finish support to MIPS architecture.

Code optimisation.


### Building Dependencies

* [gcc](https://gcc.gnu.org/)
* [bison](http://www.gnu.org/software/bison/) 
* [flex](http://flex.sourceforge.net/)

