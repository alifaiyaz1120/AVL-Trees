// Ali Faiyaz
// Main file for Part2(c) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.
// This file, we are answering the questions in the assignment of finding numbers of nodes, average depth, successfull queries, successful removes, and etc.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.
template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {

	// From Question 2
	int node_count = 0; // used to count the number of nodes in the tree (counter)

	// Code for running Part2(b)
    std::ifstream input;
	input.open(db_filename);
	if(!input.is_open()){
		return;
	}
	
	// this is the same code in query_tree for the parser
    std::string line;
	while(getline(input, line)){
		int count = 0;
		for(int i = 0; i < line.length(); i++){
			if(line[i] == '/'){
				count++;
			}
			else
			{
				continue;
			}
		}	
		if(count == 3){
			// if it has 3 '/'s in it then parse it using stringstream. 
			// when it see the first '/' store it as a enzyme acronym 
			// when it sees the second '/' store it as a recognition sequence
				std::string enzyme_acronym;
				std::string recognition_sequence;
				std::stringstream ss(line);
				getline(ss, enzyme_acronym, '/');
				getline(ss, recognition_sequence, '/');
				SequenceMap sequence_map(recognition_sequence, enzyme_acronym);
				if (!a_tree.contains(sequence_map)) {
					node_count++; // if the tree does not contain the sequence map then increment the node count
				}
				a_tree.insert(sequence_map);
		}
		
		if (count == 4)
		{
			    // if it has 4 '/'s in it then parse it using stringstream. 
				// when it see the first '/' store it as a enzyme acronym 
				// when it sees the second '/' store it as a recognition sequence1
				// when it sees the third '/' store it as a recognition sequence2
				std::string enzyme_acronym;
				std::string recognition_sequence1;
				std::string recognition_sequence2;
				std::stringstream ss(line);
				getline(ss, enzyme_acronym, '/');
				getline(ss, recognition_sequence1, '/');
				getline(ss, recognition_sequence2, '/');
				SequenceMap sequence_map(recognition_sequence2, enzyme_acronym);
				SequenceMap sequence_map1(recognition_sequence1, enzyme_acronym);
				if (!a_tree.contains(sequence_map)) { // if the tree does not contain the sequence map then increment the node count
					node_count++; 
				}
				a_tree.insert(sequence_map);
				if (!a_tree.contains(sequence_map1)) { 
					node_count++;
				}
				a_tree.insert(sequence_map1);
		}

	}
	
	// Question 2
	cout << "2: " << node_count << endl; // Prints the number of nodes in your tree 

	// Question 3
	float depth_sum = 0; // counter for depth sum
	float depth_ratio = 0; // counter for depth ratio

	depth_sum = (float)a_tree.internal()/(float)node_count; // average sum = internal nodes / total nodes
	cout << "3a: " << depth_sum << endl;
	depth_ratio = depth_sum/(float)(node_count); // calculates the ratio of the sum of the depths of the nodes in the tree to the number of nodes in the tree
	cout << "3b: " << depth_ratio << endl;

	// Question 4
	std::ifstream input2;
	input2.open(seq_filename);
	if(!input2.is_open()){
		return;
	}	
	int counter = 0; 
	while(input2){ 
		std::string finding_sequence;
		input2 >> finding_sequence; 
		if(!input2){ 
			break;
		}
		a_tree.find(finding_sequence); // searches for nodes 
		counter++;
	}

	std::cout << "4a: " << a_tree.getPassCounter() << std::endl; // Prints the total number of successful queries (number of strings found).
	std::cout << "4b: " << (float)a_tree.getFindCounter()/(float)counter << std::endl; // Prints the average number of recursive calls. 

	// Question 5
	// removes every other sequence in sequences.txt from the tree 
	// counts the total number of recursion calls for all executions of remove().
	std::ifstream input3;
	input3.open(seq_filename);
	if(!input3.is_open()){
		return;
	}
	int counter1 = 0;
	int counter2 = 0;
	while(input3){ 
		std::string finding_sequence;
		input3 >> finding_sequence; 
		if(!input3){ 
			counter2++;
			break;
		}
		if(counter1 % 2== 0){
			a_tree.remove(finding_sequence); // removes every third element in sequences.txt
			counter2++;
		}
		counter1++;
	}
	std::cout << "5a: " << a_tree.getSuccessRemove() << std::endl; // prints out the total number of successful removes
	//std::cout << (float)a_tree.getRemoveCalls() << std::endl;
	//std::cout << counter2 << std::endl;
	std::cout << "5b: " << (float)a_tree.getRemoveCalls()/(float)counter2 << std::endl; // prints out the average number of recursive calls 

	// Question 6
	// Redoing steps from question 2 and 3
	std:: cout << "6a: " << a_tree.nodeCount() << std::endl; // re-calculating the number of nodes in the tree
	float depth_sum2 = 0;
	float depth_ratio2 = 0;
	depth_sum2 = (float)a_tree.internal()/a_tree.nodeCount();
	cout << "6b: " << depth_sum2 << endl;
	depth_ratio2 = depth_sum2/a_tree.nodeCount();
	cout << "6c: " << depth_ratio2 << endl;
	}

}  // namespace

int main(int argc, char **argv) {
	if (argc != 3) {
		cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename>" << endl;
		return 0;
	}
	const string db_filename(argv[1]);
	const string seq_filename(argv[2]);

	cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;

	AvlTree<SequenceMap> a_tree;
	TestTree(db_filename, seq_filename, a_tree);

	return 0;
}
