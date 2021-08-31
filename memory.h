//**************************************************
//
//  memory.h
//  CSCI 463 Assignment 3
//
//  Created by Mitchell Trafton (z1831076)
//
//**************************************************

#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class memory{
public:
    /**
     * Initializes the size member variable and *mem array.
     * 
     * size is set to the value of siz.
     * The *mem array is allocated with siz bytes, each having a value
     *      of 0xa5.
     * 
     * @param siz Size to initialize size and *mem with.
     ********************************************************/
    memory(uint32_t siz);  
    /**
     * Free all memory present in simulated memory.
     *************************************************/
    ~memory();

    /**
     * Returns true if the given address is in simulated memory.
     * If false, prints warning and returns false
     * 
     * @param i Address to check for in simulated memory.
     * 
     * @return True if value is in simulated memory. 
     *          False if otherwise.
     *********************************************************/
    bool check_address(uint32_t i) const;
    /**
     * @return Size of simulated memory
     *********************************************/
    uint32_t get_size() const;

    /**
     * Returns the  8-bit value at the given address if it exists.
     * 
     * Calls get_size() to check if value exists.
     * 
     * @param addr Address to check for value.
     * 
     * @return The value at addr if it exists.
     *          0 if the address is not in range.
     ********************************************************/
    uint8_t get8(uint32_t addr) const;
    /**
     * Retrieves the 16-bit value at the given address.
     * 
     * Value is retrieved in little-endian order and
     *      is accomplished by calling get8() twice.
     * 
     * @param addr Address to check for value.
     * 
     * @return The 16-bit value at addr.
     *******************************************************/
    uint16_t get16(uint32_t addr) const;
    /**
     * Retrieves the 32-bit value at the given address.
     * 
     * Value is retrieved in little-endian order and
     *      is accomplished by calling get16() twice.
     * 
     * @param addr Address to check for value.
     * 
     * @return The 32-bit value at addr.
     *******************************************************/
    uint32_t get32(uint32_t addr) const;

    /**
     * Places the given 8-bit value into the given address in 
     *      simulated memory.
     * 
     * Address is validated with check_address().
     * Value is discarded if address is out of range.
     * 
     * @param addr Address to store value in.
     * @param val  8-bit value to store in address.
     ******************************************************/
    void set8(uint32_t addr, uint8_t val);
    /**
     * Places the given 16-bit value into the given address in 
     *      simulated memory.
     * 
     * Process is done by calling set8() twice with fragments
     *      of val.
     * Value is placed in little-endian order
     * 
     * @param addr Address to store value in.
     * @param val  16-bit value to store in address.
     * 
     * @warning Entire value might not be placed in memory if there
     *           are insufficient bytes availible at addr.
     ******************************************************/
    void set16(uint32_t addr, uint16_t val);
    /**
     * Places the given 32-bit value into the given address in 
     *      simulated memory.
     * 
     * Process is done by calling set16() twice with fragments
     *      of val.
     * Value is placed in little-endian order
     * 
     * @param addr Address to store value in.
     * @param val  16-bit value to store in address.
     * 
     * @warning Entire value might not be placed in memory if there
     *           are insufficient bytes availible at addr.
     ******************************************************/
    void set32(uint32_t addr, uint32_t val);

    /**
     * Dump the entire contents of simulated memory.
     * 
     * Each dump line displays 16 bits of data. 
     * Dump lines will follow the following format: 
     * [32-bit line address]: [individual bits] *[ASCII representation]* 
     * Example: 
     * 00000010: 68 65 6c 6c 0a a5 a5  a5 a5 a5 a5 a5 a5 a5 a5 *hello...........*
     *****************************************************/
    void dump() const;

    /**
     * Open passed in file and load it into simulated memory. 
     * 
     * Will print an appropriate message if file is too big or 
     *      can't be opened
     * 
     * @param fname Name of file to open.
     * 
     * @return True if file can be opened and is not too large. 
     *          False if else.
     ****************************************************/
    bool load_file(const std::string &fname);

private:
    uint8_t *mem;   ///< simulated memory
    uint32_t size;  ///< size in bytes of simulated memory
};

#endif