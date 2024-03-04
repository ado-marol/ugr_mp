/*
 * Metodología de la Programación: Kmer0
 * Curso 2023/2024
 */

/** 
 * @file Kmer.cpp
 * @author Adolfo Martínez Olmedo <adolfomarol@correo.ugr.es>
 * 
 * Last modified on 7 October 2024, 13:42
 */

#include <iostream>
#include "Kmer.h"

/////////////////////////////////////////////////////////////////

Kmer::Kmer(int k /* =1 */) 
{
    
    if (k <= 0){    // Precondition violation.
        throw std::invalid_argument(
            std::string("Kmer(k): Number of nucleotides in a given") +
                        " Kmer cannot be less than or equal to zero");
    } // Throws error message when precondition is violated
    
    else{ // k > 0
        for(int i = 0; i < k; i++) { 
            _text += MISSING_NUCLEOTIDE; 
        } // Fills a "k" sized Kmer with the default character '_'
    }
    
}

/////////////////////////////////////////////////////////////////
// TRIVIAL METHODS:
/////////////////////////////////////////////////////////////////


Kmer::Kmer(const std::string&text) 
{
    
    if (text.size()==0){    // text is empty
        throw std::invalid_argument( // composed string
            std::string("Kmer(const std::string&text): ") +
                        "text is an empty string");
    }
    _text = text; // if the text is not empty, create a Kmer with it.
}

int Kmer::getK() const
{
    return(_text.size()); // Returns the size of the string that is 
                          // representing the Kmer.
} 

// "Size" and "K" of a specific Kmer are two ways of saying the same thing.

int Kmer::size() const
{
    return(_text.size()); // Returns the size of the string which is 
                          // representing the Kmer.
}

std::string Kmer::toString() const
{
    return(_text); // Simply returns the string as it's 
                   // already representing a Kmer.
}

/////////////////////////////////////////////////////////////////

const char& Kmer::at(int index) const 
{
    
    if (index < 0 || index >= getK()){ // Precondition violation
        throw std::out_of_range(       // composed string
            std::string("const char& Kmer::at(int index) const: ") +
                        "invalid position " + std::to_string(index));
    }
    else{
        return (_text.at(index)); // Returns a constant reference to  
                                  // the character in a given position.
    }   
}

char& Kmer::at(int index) const 
{
    
    if (index < 0 || index >= getK()){ // Precondition violation
        throw std::out_of_range(       // composed string
            std::string("const char& Kmer::at(int index) const: ") +
                        "invalid position " + std::to_string(index));
    }
    else{
        return (_text.at(index)); // Returns a reference to the character  
                                  //  in a given position.
    }   
}

void Kmer::normalize(const std::string& validNucleotides)
{
    // This method performs its function in two steps, first it converts 
    // the characters to uppercase then it replaces any invalid character.
    
    // 1. Converting:
    
    ToUpper(_text);
    
    // As a reference is used in the function's parameters, it will modify
    // the string converting it to uppercase.
    
    // 2. Formatting:
    
    
    for (int i = 0; i < _text.size(); i++){
        // First we run through the string
        
        
        // Then we check if the character we're looking matches any of the 
        // valid ones, if it doesn't we change it for our constant 
        // MISSING_NUCLEOTIDE character
        if (_text.at(i) != validNucleotides.at(0) && 
            _text.at(i) != validNucleotides.at(1) &&
            _text.at(i) != validNucleotides.at(2) &&
            _text.at(i) != validNucleotides.at(3) &&){
            
            _text.at(i) = MISSING_NUCLEOTIDE;
        }
        
        // If it matches one of the valid ones we simply move on to study
        // the next character.
            
    }
    
}

Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const
{
    
    
    
}


