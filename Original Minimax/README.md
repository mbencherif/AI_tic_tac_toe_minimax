#TIC-TAC-TOE MINIMAX  
The minimax is a executable file under Linux.  
If you want to compile yourself, use the following command:  
**g++ minimax.cpp -o minimax**  
  
##Run the code  
Please use the following command to run the code:  
**./minimax [INPUT FILE]**  
For example:  
**./minimax example_input.txt**  

**For this original minimax program, you'd better not leave too many blanks in the input file.**
Or the program will long a lot of time and maybe run out of memory.

##Explanation  
In the input file, the player means which (X or O) plays next. The computer will play this player you specified in the file.  
  
The minimax tree outputed is the generated minimax tree. It's difficult to draw the tree more beautiful under command line. So...   
I've verified that the computer always play one of the most optimal strategies.  
**Utility in the minimax tree is the label of that tree indicating MIN or MAX**  
**The Input File Format must strictly follow the rule. See example input for detail.**  
  
&copy;Jeffery Zhao  
Developed Under ArchLinux  
Nov 25, 2014  