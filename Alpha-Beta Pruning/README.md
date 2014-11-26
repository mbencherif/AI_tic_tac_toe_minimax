#TIC-TAC-TOE MINIMAX Alpha-Beta  
The minimax is a executable file under Linux.  
If you want to compile yourself, use the following command:  
**g++ minimax_prun.cpp -o minimax_prun**  
  
##Run the code  
Please use the following command to run the code:  
**./minimax_prun [INPUT FILE]**  
For example:  
**./minimax_prun example_input.txt**  

The optimized minimax algorithm runs much faster and even if you play 4*4 and leaves all boxed blank in the input file, the algorithm runs successfully.  


##Explanation  
In the input file, the player means which (X or O) plays next. The computer will play this player you specified in the file.  
  
The minimax tree outputed is the generated minimax tree. It's difficult to draw the tree more beautiful under command line. So...   
I've verified that the computer always play one of the most optimal strategies.  
**Utility in the minimax tree is the label of that tree indicating MIN or MAX**  
**The Input File Format must strictly follow the rule. See example input for detail.**  
**For some nodes in the tree, the utility might be -999 or 999, **these are pruned nodes.**  
  
&copy;Jeffery Zhao  
Developed Under ArchLinux  
Nov 25, 2014  