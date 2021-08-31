//**************************************************
//
//  main.cpp
//  CSCI 463 Assignment 4
//
//  Created by Mitchell Trafton (z1831076)
//
//**************************************************

#include <iostream>
#include <unistd.h>

#include "hex.h"
#include "memory.h"
#include "rv32i.h"

using std::cout;
using std::cin;
using std::endl;

/**
 * Print a usage message and abort the program.
 *************************************************************/
void usage(){
    std::cerr << "Usage: rv32i [-m hex-mem-size] infile" << endl;
    std::cerr << "    -m specify memory size (default = 0x10000)" << endl;
    exit(1);
}


/**
 * Read a file of RV32I instructions and execute them.
 **********************************************************/
int main(int argc, char **argv){
    uint32_t memory_limit = 0x10000; //default memory size = 64k
    int opt;

    while ((opt = getopt(argc, argv, "m:")) != -1){
        switch (opt){
            case 'm':
                memory_limit = std::stoul(optarg, nullptr, 16);
                break;
            default: /* '?' */
                usage();
        }
    }

    if (optind >= argc) usage(); //missing filename

    memory mem(memory_limit);

    if  (!mem.load_file(argv[optind])) usage();

    rv32i sim(&mem);
    sim.disam();
    mem.dump();

    return 0;
}