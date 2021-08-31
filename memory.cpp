//**************************************************
//
//  memory.cpp
//  CSCI 463 Assignment 3
//
//  Created by Mitchell Trafton (z1831076)
//
//**************************************************

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>

#include "memory.h"

using std::string;
using std::cout;
using std::hex;
using std::stringstream;
using std::stoi;



memory::memory(uint32_t siz){
    /**
     * Initializes the size member variable and *mem array.
     * 
     * size is set to the value of siz.
     * The *mem array is allocated with siz bytes, each having a value
     *      of 0xa5.
     * 
     * @param siz Size to initialize size and *mem with.
     ********************************************************/
    //round siz to next multiple of 16
    siz = (siz+15)&0xfffffff0;
    //initialize size var
    size = siz;

    //allocate space to *mem
    mem = new uint8_t[siz];
    //fill *mem array
    std::fill_n(mem,siz,0xa5);
}

memory::~memory(){
    /**
     * Free all memory present in simulated memory.
     *************************************************/

    mem = NULL;
}

bool memory::check_address(uint32_t i) const{
    /**
     * Returns true if the given address is in simulated memory.
     * If false, prints warning and returns false
     * 
     * @param i Address to check for in simulated memory.
     * 
     * @return True if address is in simulated memory. 
     *          False if otherwise.
     *********************************************************/

    //if address is greater than memory size, print warning
    //and return false
    if (i >= size){
        cout << "WARNING: Address out of range: ";
        cout << std::setfill('0') << std::setw(8);
        cout << "0x" << hex << i << "\n";
        return false;
    }
    //return true if address is in range
    else return true;
}

uint32_t memory::get_size() const{
    /**
     * @return Size of simulated memory
     *********************************************/
    return size;
}

uint8_t memory::get8(uint32_t addr) const{
    /**
     * Returns the 8-bit value at the given address if it exists.
     * 
     * Calls get_size() to check if value exists.
     * 
     * @param addr Address to check for value.
     * 
     * @return The value at addr if it exists.
     *          0 if the address is not in range.
     ********************************************************/

    //if address exists, return value at address
    if (check_address(addr)) return mem[addr];
    //if address doesn't exist, return 0
    else return 0;
}

uint16_t memory::get16(uint32_t addr) const{
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

    //vars
    uint16_t out16; ///< used as 16-bit output
    uint8_t first8; ///< first 8-bit value of 16-bit output
    uint8_t second8; ///< second 8-bit value of 16-bit output

    //collect 8-bit fragments
    first8 = get8(addr + 1);
    second8 = get8(addr);

    //format output
    out16 = first8;
    out16 *= 0x100;
    out16 += second8;

    //if address was valid, return 16-bit value
    return out16;
}

uint32_t memory::get32(uint32_t addr) const{
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

    //vars
    uint32_t out32; ///< used as 32-bit output
    uint16_t first16; ///< first 16-bit value of 32-bit output
    uint16_t second16; ///< second 16-bit value of 32-bit output

    //collect 8-bit fragments
    first16 = get16(addr + 2);
    second16 = get16(addr);

    //format output
    out32 = first16;
    out32 *= 0x10000;
    out32 += second16;

    //if address was valid, return 16-bit value
    return out32;
}

void memory::set8(uint32_t addr, uint8_t val){
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

    //validate address, terminating function if invalid
    if (!check_address(addr)) return;

    //place value into memory address
    mem[addr] = val;
}

void memory::set16(uint32_t addr, uint16_t val){
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

    //vars
    uint8_t first8 = val >> 8; ///< first 8 bytes of value
    uint8_t second8 = val; ///< second 8 bytes of value

    //insert value in 8-byte segments
    set8(addr, second8);
    set8(addr+1, first8);
}

void memory::set32(uint32_t addr, uint32_t val){
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

    //vars
    uint16_t first16 = val >> 16; ///< first 8 bytes of value
    uint16_t second16 = val; ///< second 8 bytes of value

    //insert value in 8-byte segments
    set16(addr, second16);
    set16(addr+2, first16);
}

void memory::dump() const{
    /**
     * Dump the entire contents of simulated memory.
     * 
     * Each dump line displays 16 bits of data. 
     * Dump lines will follow the following format: 
     * [32-bit line address]: [individual bits] *[ASCII representation]* 
     * Example: 
     * 00000010: 68 65 6c 6c 0a a5 a5  a5 a5 a5 a5 a5 a5 a5 a5 *hello...........*
     *****************************************************/

    //vars
    uint32_t currentBitAddr = 0; ///< address of current bit being read
    uint8_t currentBit; ///< current bit being worked with
    string indivBits; ///< individual bits in current line
    stringstream ASCIIrep; ///< ASCII representation for current line

    //print lines
    for (uint32_t line = 0; line < (size / 16); ++line){
        //prep ASCIIrep
        ASCIIrep.str("");
        ASCIIrep << "*";
        //print line address
        cout << std::setw(8) << std::setfill('0') << hex << line;
        cout << ": ";

        for (size_t bit = 0; bit < 16; ++bit){//print individual bits
            //get individual bit
            currentBit = get8(currentBitAddr);
            //print individual bit
            cout << std::setw(2) << std::setfill('0');
            cout << hex << (int)currentBit << " ";
            //add ASCII representation
            ASCIIrep << (isprint(currentBit) ? (char)currentBit : '.');
            //increment address
            currentBitAddr++;

            if (bit == 8) cout << " ";
        }

        //close ASCIIrep and print it
        ASCIIrep << "*";
        cout << " " << ASCIIrep.str() << std::endl;
    }
}

bool memory::load_file(const string &fname){
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
    
    //open file
    std::ifstream infile(fname, std::ios::in|std::ios::binary);

    if (!infile){//file can't be opened or doesn't exist
        std::cerr << "Can't open file '" << fname << "' for reading.\n";
        return false;
    }

    //check file length
    //if file length greater than size of simulated memory, display error message and return false
    infile.seekg(0,infile.end);
    if (infile.tellg() > size){
        std::cerr << "File is too big.\n";
        infile.close();
        return false;
    }
    infile.seekg(0,infile.beg);

    //write to memory
    for (size_t i = 0; i < size; ++i){
        infile >> std::noskipws >> mem[i];

        if (infile.eof()) break;
    }

    //close file
    infile.close();

    return true;
}