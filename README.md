# AVL Tree 

This repository contains the implementation for an AVL Tree.

## Part 1: SequenceMap Class (sequence_map.h)

### Description
The `sequence_map.h` file contains the implementation of the `SequenceMap` class with the specified functionalities.

### Class Members
- `string recognition_sequence_;`
- `vector<string> enzyme_acronyms_;`

### Additional Functions
- Constructor: `SequenceMap(const string &a_rec_seq, const string &an_enz_acro)`
- Overloaded Operators: `bool operator<(const SequenceMap &rhs) const` and `bool operator>(const SequenceMap &rhs) const`
- Overloaded Operators `operator<<` and `operator>>`
- Member Function: `void Merge(const SequenceMap &other_sequence)`

## Part 2: AVL Tree Programs

### Description
This section includes programs for constructing and testing AVL trees based on a provided database file (`rebase210.txt`) and query file (`sequences.txt`).

### Input Files
There is two text files: `rebase210.txt` and `sequences.txt`. The `rebase210.txt` file contains the name of a restriction enzyme and possible DNA sites the enzyme may cut in the following format:

- enzyme_acronym/recognition_sequence/.../recognition_sequence//

For instance the first few lines of rebase210.txt are:

```bash

AanI/TTA'TAA// AarI/CACCTGCNNNN'NNNN/'NNNNNNNNGCAGGTG// AasI/GACNNNN'NNGTC//
AatII/GACGT'C//
AbsI/CC'TCGAGG//
AccI/GT'MKAC//
AccII/CG'CG//
AccIII/T'CCGGA//
Acc16I/TGC'GCA// Acc36I/ACCTGCNNNN'NNNN/'NNNNNNNNGCAGGT//
...

```

## Part 2A: Query Tree Program (query_tree.cc)

### Description
The `query_tree.cc` program reads the `rebase210.txt` database file, constructs an AVL tree of `SequenceMap` objects, and allows users to query the tree using recognition sequences.

### How to Run
```bash
./query_tree rebase210.txt

```

## Part 2B: Test Tree Program (test_tree.cc)

### Description
- The test_tree.cc program performs various tests on the AVL tree, including insertion, statistics calculation, searching, and removal.

### How to Run
```bash
./test_tree rebase210.txt sequences.txt
```

## Part 2C: Modified AVL Tree Implementation (avl_tree_p2c.h)

### Description
- The avl_tree_p2c.h file contains a modified AVL Tree implementation that directly implements double rotations instead of calling two single rotations.

```bash
./test_tree_mod rebase210.txt sequences.txt
```

## Makefile 

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
