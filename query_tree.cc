// Ali Faiyaz
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.
// This file, we are creating an AVL tree using avl_tree.h. We are parsing the data and 
// making it passed through input files from txt.

#include "avl_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

namespace {
// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.

template <typename TreeType>
void QueryTree(const std::string &db_filename, TreeType &a_tree) {

	// Code for running Part2(a)
	// Parse input file @db_filename and feel tree @a_tree
	
	// Then prompt the user for exactly three strings (do a loop) and
	// provide the results of find() as described in the assignment.

	// using ifsteam to open the text file
    std::ifstream input;
	input.open(db_filename);
	if(!input.is_open()){
		return;
	}

    std::string line;
	while(getline(input, line)){
		int count = 0; // used a counter to count how many slashes where in a single line 
		for(int i = 0; i < line.length(); i++){
			if(line[i] == '/'){
				count++;
			}
			else
			{
				continue; // if it doesnt see a slash it continues to the next line 
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
				SequenceMap sequence_map(recognition_sequence, enzyme_acronym); // store it into a sequence map
				a_tree.insert(sequence_map); // insert it into the a_tree
				//cout << enzyme_acronym << " " << recognition_sequence << endl;
		}
		if (count == 4)
		{
			   // if it has 4 '/'s in it then parse it using stringstream. 
			   // when it see the first '/' store it as a enzyme acronym 
			   // when it sees the second '/' store it as a recognition sequence1
			   // when it sees the thrid '/' store it as a recognition sequence2
				std::string enzyme_acronym;
				std::string recognition_sequence1;
				std::string recognition_sequence2;
				std::stringstream ss(line);
				getline(ss, enzyme_acronym, '/');
				getline(ss, recognition_sequence1, '/');
				getline(ss, recognition_sequence2, '/');
				SequenceMap sequence_map(recognition_sequence2, enzyme_acronym); // store the second recognition sequence in the first map
				SequenceMap sequence_map1(recognition_sequence1, enzyme_acronym); // // store the first recognition sequence in the second map
				a_tree.insert(sequence_map); // insert both maps into the a_tree
				a_tree.insert(sequence_map1);
				//cout << enzyme_acronym << " " << recognition_sequence1 << " " << recognition_sequence2 << endl;
		}
	}
	// this for loop reads the file input_part2a.txt and print outs three enzyme acronym
	for(int i = 0; i < 3; i++){
		std::string finding_sequence;
		std::cin >> finding_sequence; 
		std::cout << a_tree.find(finding_sequence) << std::endl; // this find function is in avl_tree.h
	}

} 
}  // namespace

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << " <databasefilename>" << endl;
		return 0;
	}
	const std::string db_filename(argv[1]);
	
	cout << "Input filename is " << db_filename << endl;
	AvlTree<SequenceMap> a_tree;
	QueryTree(db_filename, a_tree);

	return 0;
	
}