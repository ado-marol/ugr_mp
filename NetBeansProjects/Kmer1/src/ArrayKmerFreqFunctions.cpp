/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file ArrayKmerFreqFunctions.cpp
 * @author Adolfo Martínez Olmedo <adolfomarol@correo.ugr.es>
 * 
 * Created on 14 March 2024, 05:00
 */

#include <iostream>
#include "ArrayKmerFreqFunctions.h"



void ReadArrayKmerFreq(KmerFreq array[], int dim, int& nElements)
{  
    if (nElements > dim)
        nElements = dim;
    
    if (nElements < 0)
        nElements = 0;
    
    for (int i = 0; i < nElements; i++) {
        // We create a variable to store the text that will eventually become the
        // kmer.
        
        std::string kmer_text;
        
        // We also create one that will be the frequency.
        
        int frequency;
        
        // We read the text in the kmer and create a kmer object using it.
        
        std::cin >> kmer_text;
        Kmer a_kmer(kmer_text);
        
        // We read the frequency.
        
        std::cin >> frequency;
        
        // Once we have the kmer and its frequency we create a KmerFreq object
        // and assign the kmer and frequency values we've read.
        
        KmerFreq kmer_and_freq;
        
        kmer_and_freq.setKmer(a_kmer);
        
        kmer_and_freq.setFrequency(frequency);
        
        // Once we have the object created, we add it to the array and repeat.
        
        array[i] = kmer_and_freq;
    }
    
}

void PrintArrayKmerFreq(KmerFreq array[], int nElements)
{
    // First print the number of kmers.
    
    if (nElements > 0)
        std::cout << nElements << std::endl;
    
    // Afterwards, go through the array printing the kmer, a space and the 
    // frequency right after.
    
    for (int i = 0; i < nElements; i++) {
        
        std::cout << array[i].getKmer().toString() << " " 
                  << array[i].getFrequency() << std::endl;
    }
    
}

void SwapElementsArrayKmerFreq(KmerFreq array[], int nElements, int first,
                int second)
{
    if (first > nElements || second > nElements){    // Precondition violation.
        throw std::out_of_range(
            std::string("ArrayKmerFreqFunctions(KmerFreq array[], int nElements, int first, int second): ") +
                        " The position 'first' or 'last' cannot be bigger than the size of the array");
        
    } // Throws error message when precondition is violated
    
    KmerFreq temp; // Create an object to temporary store a value in order to swap
    
    temp = array[first];
    
    array[first] = array[second];
    
    array[second] = temp;
}

int FindKmerInArrayKmerFreq(KmerFreq array[], Kmer kmer,
        int initialPos, int finalPos)
{
    int pos_to_find = -1; // If not found, this will be its value.
    
    // We go through the array between the positions specified and try to find 
    // the kmer in question, if we do we log its position and break the search.
    
    for (int i = initialPos; i <= finalPos; i++) {
        
        if (array[i].getKmer().toString() == kmer.toString()){
            
            pos_to_find = i;
            
            break; // Stop the search
        }
    }
    
    return (pos_to_find);
}


int Partition(KmerFreq array[], int low, int high, int nElements) 
{
    int pivot = array[high].getFrequency(); // Choose the element most on the right as the pivot.
    int i = low - 1;                        // Index of the smaller element
    
    for (int j = low; j <= high - 1; j++) { // We go through our partition
        
        // If the frequency at the smaller element is larger than the pivot,
        // we will swap them.
        if (array[j].getFrequency() >= pivot) {
            i++;
            SwapElementsArrayKmerFreq(array, nElements, i, j);
        }
    }
    
    SwapElementsArrayKmerFreq(array,nElements, i + 1, high);
    return (i + 1); // Return the pivot index
}

void QuickSort(KmerFreq array[], int low, int high, int nElements) 
{
    if (low < high) {
        int pivotIndex = Partition(array, low, high, nElements); // We get the pivot using
                                                                 // our partition function

        // Recursively sort the left and right subarrays
        QuickSort(array, low, pivotIndex - 1, nElements);
        QuickSort(array, pivotIndex + 1, high, nElements);
    }
}


void SortArrayKmerFreq(KmerFreq array[], int nElements)
{
    
    // Firstly we must make sure that the array is not already sorted.
    
    bool its_sorted = true;
    
    for (int i = 1; i < nElements; i++) {
        
        if ((array[i - 1].getFrequency()) < array[i].getFrequency()){
            its_sorted = false;
            break;
        }
    }
    
    // We will use quick sort as it is infinitely faster than insertion or 
    // Selection sort.
    
    // Call our quicksort function if it is not sorted already
    if (!its_sorted){
        
        QuickSort(array, 0, nElements - 1, nElements);
    
        // And that's it, the quicksort function takes care of sorting the array.
    
        // However, we must make sure of one last thing. If two kmers have the same
        // exact frequency, the one with the first character in alphabetical 
        // order will be first, let's go through the array and make sure of it.
        
        // For this purpose we use two for loops, where the first one goes through
        // the array, and for each element of the array the second loop
        // studies if there are any KmerFreq objects with the same frequency but 
        // which should go earlier in alphabetical order, if it finds one, 
        // it swaps them in the array, doing this for *every* element in the array
        // will ensure that it ends up properly sorted. 
        // (these 10 lines of code took me literally 4 hours of Saturday 
        //  afternoon omg, who knew you can use ">" between strings).
        
        for (int i = 0; i < nElements; i++) {
            
            for (int j = i + 1; j < nElements ; j++) {
                
                if ((array[i].getFrequency() == array[j].getFrequency()) &&
                    (array[i].getKmer().toString() > array[j].getKmer().toString())){   
                    
                    SwapElementsArrayKmerFreq(array, nElements, i,j);
                }
            }
        }
    
   
    }
}

void NormalizeArrayKmerFreq(KmerFreq array[], int& nElements, 
        std::string validNucleotides)
{ 
    
    // Loop to traverse and normalize each one of the kmers in array
          // Normalize kmer i
    for (int i = 0; i < nElements; i ++) {
        
        // First create an implicit Kmer.
        
        Kmer normalized (array[i].getKmer());
        
        // Then normalize it.
        
        normalized.normalize(validNucleotides);
        
        // Afterwards, we replace the corresponding kmer in the array with it.
        
        array[i].setKmer(normalized);
    }
    
    // Loop to traverse the kmers in array from position 1 to position nElements-1
          // index = Position of array[i].getKmer() in the subarray that begins
          //         at position 0 and ends at position i-1
          // If array[i].getKmer() was found in the the subarray from 0 to i-1 
               // Accumulate the frequencies of the kmers at positions 
               //    index and i in the kmer at position index
               // Delete from the array, the kmer at position i 
    
    int index;
    bool found = true;
    
    for (int i = 1; i < nElements; i++) {
        
        for (int j = 0; j < i; j ++) {
            
            if (array[j].getKmer().toString() == array[i].getKmer().toString()){  
                // If so, we have a match.
                
                
                // If we indeed find it has already been found before, we 
                // mark the position using index, and promptly exit the loop.
                index = j;
                found = true;
                break;
            }
            
            else found = false; // We use this bool to prevent unintended changes.
            
        }
        
        if (found){  // If this exact kmer has been found before.
            
            // first of all copy the frequencies to the one at pos = index.
            
            array[index].setFrequency(array[index].getFrequency() + array[i].getFrequency());
            
            // Secondly, "delete" the second appearance from the array            
            
            DeletePosArrayKmerFreq(array, nElements, i);
            i = i - 1; // We have to do this in order to compensate for the 
                       // fact that we have moved the elements of the array
                       // back one place, this way we do this specific for 
                       // instruction once more, because the element at pos "i"
                       // is not the same as it was.
            }
        }
    
    
}

void DeletePosArrayKmerFreq(KmerFreq array[], int& nElements, int pos)
{
    if (pos < 0 || pos > nElements){    // Precondition violation.
        throw std::out_of_range(
            std::string("ArrayKmerFreqFunctions(KmerFreq array[], int nElements, int pos") +
                        " The position 'pos' must be in range of 0 and nElements");
        
    } // Throws error message when precondition is violated
    
    // We move all the elements to the right of pos one spot to the left, 
    // effectively "deleting" the element at pos.
    for (int i = pos; i < nElements; i ++) {
        
        if (i != nElements - 1)
            array[i] = array[i + 1]; // Replace the element at i with the one 
                                    // on it's right.
    }
    nElements --;
    
}

void ZipArrayKmerFreq(KmerFreq array[], int& nElements, 
        bool deleteMissing /* =false */, int lowerBound /* =0 */)
{
    // First of all, if deleteMissing = true, let's delete all the ones
    // that contain an unknown nucleotide.
    

    if (deleteMissing == true) {
        
        int pos_missing_nucleotide;
        
        for (int i = 0; i < nElements; i++) {
            
            pos_missing_nucleotide = array[i].getKmer().toString().find('_');
            
            if (pos_missing_nucleotide != -1){
                DeletePosArrayKmerFreq(array, nElements, i);
                i = i - 1; // We have to do this in order to compensate for the 
                           // fact that we have moved the elements of the array
                           // back one place, this way we do this specific for 
                           // instruction once more, because the element at pos "i"
                           // is not the same as it was.
            }
        }
    }
    
    
    for (int i = 0; i < nElements; i++) {
        
        if (array[i].getFrequency() <= lowerBound){
            DeletePosArrayKmerFreq(array,nElements,i);
        }
    }
    
}

