/*
 * Metodología de la Programación: Kmer1
 * Curso 2023/2024
 */

/** 
 * @file Kmer.cpp
 * @author Adolfo Martínez Olmedo <adolfomarol@correo.ugr.es>
 *
 * Created on 12 March 2024, 19:00
 */

#include <iostream>
#include "KmerFreq.h"

/////////////////////////////////////////////////////////////////

KmerFreq::KmerFreq(): _frequency(0)
{ 
    _kmer = Kmer();
}

/////////////////////////////////////////////////////////////////
// TRIVIAL METHODS:
/////////////////////////////////////////////////////////////////

const Kmer& KmerFreq::getKmer()
{
    return (_kmer); 
}

int KmerFreq::getFrequency()
{
    return (_frequency);
}

/////////////////////////////////////////////////////////////////

void KmerFreq::setKmer(const Kmer& kmer)
{
    _kmer = kmer;
}

void KmerFreq::setFrequency(int frequency)
{
    if (frequency < 0){ // Precondition violation
        throw std::out_of_range(
            std::string("void KmerFreq::setFrequency(int frequency): Frequency") +
                        "  cannot be negative");
    }
    _frequency = frequency;
}

std::string KmerFreq::toString() const
{
    std::string Kmer_and_freq;
    
    Kmer_and_freq = _kmer.toString() + ' ' + std::to_string(_frequency);
    
    return (Kmer_and_freq);
}
