/*
 * Metodología de la Programación: Kmer0
 * Curso 2023/2024
 */

/**
 * @file:   main.cpp
 * @author  Adolfo Martínez Olmedo 
 * Created on 05 March 2024, 15:00
 */

#include <iostream>
#include <string>

#include "Kmer.h"


/**
 * This program first reads from the standard input an integer k (length of Kmer)
 * and a string with a genetic sequence. Then, it obtains from the genetic 
 * sequence, the list of kmers (of length k) and saves them in the array kmers. 
 * Then, the kmers are normalized. After that, the complementary kmers, 
 * converted to lowercase, are saved in the array complementaryKmers. Finally 
 * the kmers in the arrays kmers and complementaryKmers are shown in the 
 * standard output.
 * See the next example:
 * 
 * Running example:
 * > kmer0 < data/easyDNA5_missing.k0in
6
GCGCC<-->cgcgg
CGCCC<-->gcggg
GCCC_<-->cggg_
CCC_G<-->ggg_c
CC_G_<-->gg_c_
C_G_G<-->g_c_c
 */

/**
 * @brief Main function
 * @return Always 0
 */
int main(int argc, char* argv[]) {
    
    int k; 
    std::string genetic_sequence;

    // This string contains the list of nucleotides that are considered as
    // valid within a genetic sequence. The rest of characters are considered as
    // unknown nucleotides 
    const std::string VALID_NUCLEOTIDES = "ACGT";
    
    // This string contains the list of complementary nucleotides for each
    // nucleotide in validNucleotides
    const std::string COMPLEMENTARY_NUCLEOTIDES = "TGCA";

    // This is a constant with the dimension of the array kmers
    const int DIM_ARRAY_KMERS = 100;
    
    // This is the array where the kmers of the input genetic sequence will be
    // saved
    Kmer kmers[DIM_ARRAY_KMERS];
    
    // This is the array where the complementary kmers will be
    // saved
    Kmer complementaryKmers[DIM_ARRAY_KMERS];
    
    // Read K (integer) and a string with the input nucleotides list
    
    std::cin >> k >> genetic_sequence;
    
    int sequence_size = genetic_sequence.size(); // To avoid comparing signed a
                                                 // and unsigned ints.
    int kmers_used = 0;
    
    // We make sure we won't accept a sequence longer than the dimension of our
    // array.
    
    if (sequence_size > DIM_ARRAY_KMERS && k < sequence_size)
        sequence_size = DIM_ARRAY_KMERS + k - 1;
    
    // Obtain the kmers: find the kmers in 
    // the input string and put them in an array of Kmers
    
    // First we will run through the whole string.
    
    
    for (int i = 0; i < (sequence_size - k + 1); i++) {
    
        // We create a k sized implicit string which will be used to contain the
        // nucleotides to initialize the Kmer.        
        
        std::string k_nucleotides;
        
        // Move from the position we're at in the string until we cover "k" 
        // places, that will be our kmer.
        
        k_nucleotides = genetic_sequence.substr(i,k);
        
        // Now that we have all the nucleotides we need in the string we create
        // the k sized Kmer.
        
        Kmer new_Kmer (k_nucleotides);
        
        // After having created the kmer, we add it to the array.
        
        kmers[kmers_used] = new_Kmer;
        
        // We normalize it.
        
        kmers[kmers_used].normalize(VALID_NUCLEOTIDES);
        
        kmers_used ++;
        
        // Obtain the complementary kmers and turn them into lowercase
        
        // First let's create the implicit kmer which will eventually become
        // our complementary.
        
        Kmer complementary_kmer(k);
        
        // Make it complementary by using the method in the class.
        
        complementary_kmer = kmers[i].complementary(VALID_NUCLEOTIDES, 
                                                    COMPLEMENTARY_NUCLEOTIDES);
        
        // Make it lowercase
        
        ToLower(complementary_kmer);
        
        // Add it to the array
        
        complementaryKmers[i] = complementary_kmer;
        
    }   

    // Show the list of used kmers and complementary kmers as in the example
    
    std::cout << kmers_used << std::endl;
    
    for(int i = 0; i < kmers_used; i++) {
        std::string output;
        output = kmers[i].toString() + "<-->" + 
                                     complementaryKmers[i].toString();
        std::cout << output << std::endl;
    }
    
    return (0);
}
