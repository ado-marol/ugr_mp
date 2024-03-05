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

char& Kmer::at(int index) 
{
    
    if (index < 0 || index >= getK()){ // Precondition violation
        throw std::out_of_range(       // composed string
            std::string("char& Kmer::at(int index) const: ") +
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
    int size = _text.size(); // In order to prevent signed problems
    
    for (int i = 0; i < size; i ++) {
        _text.at(i) = std::toupper(_text.at(i));
    }
    
    // 2. Formatting:
    
    
    for (int i = 0; i < size; i++) {
        // First we run through the string
        
        
        // Then we check if the character we're looking at matches any of the 
        // valid ones, if it doesn't we switch it with our constant 
        // MISSING_NUCLEOTIDE character
        // We can efficiently make use of our function.
        
        if (!IsValidNucleotide(_text.at(i),validNucleotides)){
            _text.at(i) = MISSING_NUCLEOTIDE;
        }
             
        // If it matches one of the valid ones we simply move on to study
        // the next character.
            
    }
    
}

Kmer Kmer::complementary(const std::string& nucleotides, 
         const std::string& complementaryNucleotides) const
{
    if (nucleotides.size() != complementaryNucleotides.size()){ // Different sizes
        throw std::invalid_argument( // composed string
            std::string("Kmer Kmer::complementary(const std::string& nucleotides,") +
                        "const std::string& complementaryNucleotides) const:" +
                        " nucleotides and complementary nucleotides cannot be" +
                        " differently sized");
    }
    else {
        int text_size = _text.size();             // In order to prevent signed problems
        int nucleotide_size = nucleotides.size(); // In order to prevent signed problems
        Kmer complementary_kmer(text_size);       // We create the object we're gonna return
        complementary_kmer._text = _text;

        // We will use two for loops, one to run through our Kmer and another one 
        // to, for each individual character, convert it into its complementary.
    
        for (int i = 0; i < text_size; i++) {
            // We move through our Kmer 
            
            bool complemented = false;
            int pos = 0;
            
            while (pos < nucleotide_size && !complemented) {
                
                // We check which Nucleotide in specific we're studying in our Kmer.
                // Depending on which one it is we match it with the corresponding
                // complementary nucleotide. If it doesn't match any of the valid 
                // ones, then we will do nothing and it will stay the same.
                // As soon as we have interchanged them, the process is done 
                // and we exit the while loops
                
                if (complementary_kmer.at(i) == nucleotides.at(pos)){
                    complementary_kmer._text.at(i) = complementaryNucleotides.at(pos); 
                    complemented = true;
                }
                else pos ++;
            }

        }

        return (complementary_kmer);
    }
    
}

bool IsValidNucleotide(char nucleotide, const std::string& validNucleotides)
{
    bool value = false; // First initialize the value as false to go in the loop
    
    int size = validNucleotides.size(); // In order to avoid signed/unsigned integers
    
    // We will use a while loop in order to minimize the amount of comparisons
    // so we can exit it if we find the nucleotide to be valid.
    
    int pos = 0;
    
    while (pos < size && !value) {
        
        if (nucleotide == validNucleotides.at(pos)) value = true; // if it belongs to the valid ones, we're done.
        
        else pos ++; // if it doesn't, we move to the next valid nucleotide.
    }
    
    return (value);
}

void ToLower(Kmer& kmer)
{
    int size = kmer.size(); // To prevent problems with signed/unsigned ints
    
    for (int i = 0; i < size; i++) { // We run through our Kmer, converting to 
                                     // lowercase any letter which isn't already
        
        kmer.at(i) = std::tolower(kmer.at(i));
    }
    
}

void ToUpper(Kmer& kmer)
{
    int size = kmer.size(); // To prevent problems with signed/unsigned ints
    
    for (int i = 0; i < size; i++) { // We run through our Kmer, converting 
                                     // to uppercase any letter which isn't
                                     // already
        
        kmer.at(i) = std::toupper(kmer.at(i));
    }
    
}


