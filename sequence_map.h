// Ali Faiyaz
// Part 1 for Assignment 2
// Implementation of the SequenceMap class, and the big five.

#ifndef SEQUENCE_MAP
#define SEQUENCE_MAP

#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <sstream>

class SequenceMap {
public:
    // Default big five
    // Default Copy Constructor
    SequenceMap(const SequenceMap &rhs) = default;
    // Default Move Constructor
    SequenceMap(SequenceMap &&rhs) = default;
    // Default Copy Assignment Operator
    SequenceMap &operator=(const SequenceMap &rhs) = default;
    // Default Move Assignment Operator
    SequenceMap &operator=(SequenceMap &&rhs) = default;
    // Default Destructor
    ~SequenceMap() = default;

    // A constructor that constructs a SequenceMap from two strings
    SequenceMap(const std::string &a_rec_seq, const std::string &an_enz_acro){
        enzyme_acronyms_.push_back(an_enz_acro);
        recognition_sequence_ = a_rec_seq;
    }

    // Greather than operator that compares two SequenceMap objects
    bool operator<(const SequenceMap &rhs) const {
        return recognition_sequence_ < rhs.recognition_sequence_;
    }

    // Less than operator that compares two SequenceMap objects
    bool operator>(const SequenceMap &rhs) const {
        return recognition_sequence_ > rhs.recognition_sequence_;
    }

    // Overloaded operators operator<< and operator>> for SequenceMaps.
    // This is for Extra Credit 1 
    friend std::ostream &operator<<(std::ostream &out, const SequenceMap &outside_map)
    {
        for (signed int i = 0; i < outside_map.enzyme_acronyms_.size(); i++){
            out << outside_map.enzyme_acronyms_[i];
            if (i != outside_map.enzyme_acronyms_.size() - 1)
            {
                out << " ";
            }
        }
        return out;
    }
    friend std::istream &operator>>(std::istream &in, SequenceMap &outside_map)
    {
        std::string enz_acro;
        in >> outside_map.recognition_sequence_; 
        in >> enz_acro;
        outside_map.enzyme_acronyms_.push_back(enz_acro);
        return in;
    }
    // merge function
    void Merge(const SequenceMap &other_sequence) {
        for (int i = 0; i < other_sequence.enzyme_acronyms_.size(); i++) {
            enzyme_acronyms_.push_back(other_sequence.enzyme_acronyms_[i]);
        }
    }
    // getter that returns the recognition sequence
    std::string getRecSequence() const{
        return recognition_sequence_;
    }
    // getter that returns enzyme acronyms
    std::string getEnzymeAcro() const{   
        std::string res = "";
        for(int i = 0; i < enzyme_acronyms_.size(); i++){
            res += enzyme_acronyms_[i];
            if(i != enzyme_acronyms_.size()-1){
                res+= " ";
            }
        }
        return res;
    }
    private:
        std::string recognition_sequence_ ;
        std::vector<std::string> enzyme_acronyms_;

};

#endif 