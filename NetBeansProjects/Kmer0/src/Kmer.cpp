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
        std::string temporary_kmer(k,MISSING_NUCLEOTIDE); // Use the string constructor
        _text = temporary_kmer;                          
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
    
    return (_text.at(index)); // Returns a constant reference to  
                              // the character in a given position.
}

char& Kmer::at(int index) 
{
    
    if (index < 0 || index >= getK()){ // Precondition violation
        throw std::out_of_range(       // composed string
            std::string("char& Kmer::at(int index) const: ") +
                        "invalid position " + std::to_string(index));
    }
    
    return (_text.at(index)); // Returns a reference to the character  
                              //  in a given position. 
}

void Kmer::normalize(const std::string& validNucleotides)
{
    // This method performs its function in two steps, first it converts 
    // the characters to uppercase then it replaces any invalid character.
    
    // 1. Converting:
    int size = _text.size(); // In order to prevent signed problems
    
    Kmer auxiliary_kmer(_text); // We create a "helper" kmer which we will work on, then
                                // assign it's text to the one in the class.
    
    ToUpper(auxiliary_kmer);    // Efficiently make use of the function.
    
    // 2. Formatting:
    
    
    for (int i = 0; i < size; i++) { 
        // We check if the character we're looking at matches any of the 
        // valid ones, if it doesn't we switch it with our constant 
        // MISSING_NUCLEOTIDE character
        // We can efficiently make use of our function.
        
        if (!IsValidNucleotide(auxiliary_kmer.at(i),validNucleotides)){
            auxiliary_kmer.at(i) = MISSING_NUCLEOTIDE;
        }
             
        // If it matches one of the valid ones we simply move on to study
        // the next character.
            
    }
    
    // We assign the value of the auxiliary to the one in the class.
    
    _text = auxiliary_kmer._text;
    
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
    
    int text_size = _text.size();             // In order to prevent signed problems
    Kmer complementary_kmer(_text);       // We create the object we're gonna return

    // We will use two for loops, one to run through our Kmer and another one 
    // to, for each individual character, convert it into its complementary.
    
    for (int i = 0; i < text_size; i++) {
        // We move through our Kmer 
        
        // For each character in our Kmer, we find the position of the corresponding
        // nucleotide
        int pos_nucleotide = nucleotides.find(complementary_kmer.at(i));
        
        if (pos_nucleotide != -1){
            // If the position is valid (which means that this nucleotide belongs
            // to the valid ones, we replace it with the complementary nu
            
            complementary_kmer.at(i) = complementaryNucleotides.at(pos_nucleotide);
            
        }
        
    } // for

    return (complementary_kmer);
    
}

bool IsValidNucleotide(char nucleotide, const std::string& validNucleotides)
{
    bool value = false; // First initialize the value as false to save computing time.
    
    int position;
    
    position = validNucleotides.find(nucleotide);
    
    // This method in the string class will return the position of the nucleotide
    // if it belongs in the valid ones, if it doesn't belong there it will return "-1"
    // hence, if it is not -1 the nucleotide does belong within the valid ones.
    
    if (position != -1)
        value = true;
        
    
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


