# Huffman Coding
A C compression and decompression program based on Huffman Coding.

## Introduction

This project is to design compression and decompression programs based on Huffman Coding.
The idea of Huffman Coding is to minimize the weighted expected length of the code by means of assigning shorter codes to frequently-used characters and longer codes to seldom-used code.

## Implementation Details

The programs can compress and decompress text file consisting of 256 ASCII characters.

### Compression

1. Open input file, count and store the frequencies of different characters;
2. Construct Priority Queue and then Huffman Tree;
3. Calculate Huffman Encode Table;
4. Encode the file, store Huffman Encode Table and encoded to the output.bin.

### Decompression

1. Open file, read the table;
2. Decode the file based on the table and store it to the out.txt file.

### Compiliation

Makefile provided for compilation