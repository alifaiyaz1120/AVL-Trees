# Assignment 2 README.MD

Ali Faiyaz

I was successfully able to complete Assignment 2. The main purpose of this project is to understand how AVL trees are constructed and operated by using txt files as a way to pass through data to construct a tree. While most of the implementation/ code wasn't given to us, I was supposed to implement more functions and modify the ones given to complete the questions asked in this assignment.

The file "sequence_map.h" was one of the files that weren't implemented for us. In this file, we were supposed to construct the big five, which were all used as defaults, and create member functions like merge (merge one sequence map object to another), overloaded operators (less than and greater than), and a constructor (that creates a new node given recognition sequence and enzyme acronyms). In addition, I added helper functions that helped me later on in the project, which were getters that returns the recognition sequence and enzyme acronyms. I also did the extra credit for this section, which was overloaded operators "operator<< and operator>>" for sequence maps. Overall, I believe this part was probably the easiest of the entire project.

Moving on to Part 2 of the assignment. In Part 2a, we were supposed to make a parser that reads from a text file and constructs an AVL tree from there which is located in "query_tree.cc." In order to parse and read the data, I used ifsteam and streamstream. In the text file that was rebase210.txt, the text was formatted in a complex way making it hard to find the enzyme acronym and recognition sequence. An approach I took was making a counter that reads how many slashes were in a line. If it is less than 3, it continues, but read it if it's equal to 3 and 4. When it notices the first slash, it is an enzyme acronym that reads everything back to it, the second slash is the recognition sequence, and the third slash is another recognition sequence if there are four slades. To read the input_part2a.txt file, I called the find function, which I implemented in my AVL tree, as it reads the recognition sequence and returns enzyme acronyms if found. 

For Part 2b, is where I used the same parser I made in 2a to test the AVL tree. One of the questions/tests was to print the average depth and ratio of it. An approach I did was making a helper function in my AVL tree that finds the internal depth of the tree and uses the number of nodes in the trees to find both the average depth and the ratio of the average depth to the number of nodes. Question 4 was difficult for me at first. We were supposed to find the total number of strings found from the text file sequence.txt. The first approach I took was making a new function, but I realized it wasn't working and printing out the numbers it wasn't to print out. So, I modified the find function I made earlier in this assignment, where I added a pass counter; when passed, it increments, and a find counter of a number of strings was found. I made helper functions from the counters I made from that return it, successfully allowing me to answer question 4. Question 5 was also tricky, where I was supposed to find the total number successfully removed and averaged calls. I made the same approach I did in Question 4, where I made counters of removed successfully and calls removed in my remove function in my AVL tree. I struggled a lot with this question, but somehow I was able to find a way to read the sequence.txt and remove every third element in the file and increment it by using two counters. It wasn't the optimal way, but it somehow worked and got close to the expected answer. Question 6 is updating the nodes and averages from after doing Questions 4 and 5. A problem I encountered in Question 6 was the number of nodes wasn't updating. It kept printing out the exact number 565 for Question 2. A way I was able to fix it was by making a helper function in my AVL tree counting the total number of nodes, which I didn't think about earlier doing in Part 2b.

For Part 2c, I was supposed to modify the double rotations functions without calling the two single rotations. I didn't find this section hard, but fun. I successfully did this by watching Youtube videos and reading the textbook about it. But one problem I encountered was, at first, it wasn't working correctly because I implemented the height incorrectly, but I was able to fix it later. 

The input files were input_part2a.txt which tests inputs for 2a. Sequences.txt is lists of recognition sequences. Also, rebase210.txt is pair of recognition sequences and enzyme acronyms. Overall, this assignment was very tricky at first but became fun later on.


[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-c66648af7eb3fe8bc4f294546bfd86ef473780cde1dea487d3c4ff354943c9ae.svg)](https://classroom.github.com/online_ide?assignment_repo_id=8631038&assignment_repo_type=AssignmentRepo)

You will use this exact `Makefile` for your Homework 2. Failure to do so will result in *deduction* of points. Replace this file with a `README.md` for your own project. You can move these instructions to the bottom of the file if you wish.

To compile on terminal, type:

```bash
make
```

You can compile one program individually by just typing `make <Program Name>`, for example:

```bash
make query_tree
```

To delete executables and object files, type:

```bash
make clean
```
