//**************************************************
//
//  hex.h
//  CSCI 463 Assignment 3
//
//  Created by Mitchell Trafton (z1831076)
//
//**************************************************

#ifndef hex_H
#define hex_H

#include <string>
#include <stdint.h>

/**
 * Returns the passed in 8-bit integer in hex form as a string.
 * 
 * conversion done using stringstream input
 * 
 * @param i an 8-bit integer to be converted
 * 
 * @return the 2-digit hex representation of the passed in integer
 *      as a string
 * *************************************************************/
std::string hex8(uint8_t i);

/**
 * Returns the passed in 32-bit integer in hex form as a string.
 * 
 * conversion done using stringstream input
 * 
 * @param i a 32-bit integer to be converted
 * 
 * @return the 8-digit hex representation of the passed in integer
 *      as a string
 * *************************************************************/
std::string hex32(uint32_t i);

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
std::string hex0x32(uint32_t i);

#endif