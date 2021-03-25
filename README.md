# Text_Turing_Machine
A working simulation of a single-tape, two-way, infinite-sized deterministic Turing machine. 

First input is a file name containing the state rules you want the Turing Machine to implement.
The state rules can contain multiple lines: Each line is either blank; a comment, indicated by 
the “//” characters; or a 5-tuple rule consisting of: currentState, currentTapeSymbol, newState, 
newTapeSymbol, direction to read next symbol. (instructions can be followed comments on the same 
line, also indicated by “//”. 
States are indicated by either an integer (0 represents the start state q0, where the Turing Machine
will always begin automatically) or the letter f, for Final state. 
Example: the line 0 1 2 X R translates to:
0  //if currently in state q0 
1  //and the current symbol being read is a 1
2  //then switch to state q2
X  //replace the current symbol on the tape with an 'X'
R  //read the symbol to the right of the current one

 After initializing the virtual Turing Machine with the given state rules, you are asked for an input word.
 The program will then determine if the word is accepted by the rules, and output the state of the tape 
 at each process before settling on a final indication of accepted or not.
 
 You can enter as many words as you'd like on the initialized Turing Machine until the program is exited manually.

(includes 2 test files to demonstrate implementation and proper rule syntax)
