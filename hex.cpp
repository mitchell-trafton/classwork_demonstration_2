//**************************************************
//
//  hex.cpp
//  CSCI 463 Assignment 3
//
//  Created by Mitchell Trafton (z1831076)
//
//**************************************************

#include <iostream>
#include <sstream>

#include "hex.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stringstream;
using std::hex;

string hex8(uint8_t i){
    /**
     * Returns the passed in 8-bit integer in hex form as a string.
     * 
     * conversion done using stringstream input
     * 
     * @param i an 8-bit unsigned integer to be converted
     * 
     * @return the 2-digit hex representation of the passed in integer
     *      as a string
     **************************************************************/

    //vars
    stringstream hexOut; ///< stores string to be output
    string preZero; ///< used as preceeding zero if needed

    //convert to hex
    hexOut << hex << (int)i;

    //add preceeding zero if output is less than 2 digits
    if (hexOut.str().length() < 2) preZero = "0";

    //return result
    return preZero + hexOut.str();
}

string hex32(uint32_t i){
    /**
     * Returns the passed in 32-bit integer in hex form as a string.
     * 
     * conversion done using stringstream input
     * 
     * @param i a 32-bit unsigned integer to be converted
     * 
     * @return the 8-digit hex representation of the passed in integer
     *      as a string
     **************************************************************/

    //vars
    stringstream hexOut; ///< stores string to be output
    string preZeroes = ""; ///< used as preceeding zeroes if necessary

    //convert to hex
    hexOut << hex << i;

    //add preceeding zero(es) if output is less than 8 digits
    for (size_t z = 0; z < 8 - hexOut.str().length(); ++z) 
        preZeroes += "0";

    return preZeroes + hexOut.str();
}

string hex0x32(uint32_t i){
    /**
     * Returns the passed 32-bit integer beginning with 0x in hex form
     *      as a string.
     * 
     * Actual hex conversion done using hex32
     * 
     * @param i a 32-bit unsigned integer to be converted
     * 
     * @return the 8-digit hex representation of i in 0xXXXXXXXX format
     **************************************************************/

    return "0x" + hex32(i);
}