# ZlibLibraryC++

This code displays the compression and decompression capabilities of the zlib library. _**main.cpp**_ is the file that contains the code, the rest are supporting files from CodeBlocks.

I have used CobeBlocks IDE to run this code. 
Refer the following links if you need to download and set-up the library:
1. [Video link](https://youtu.be/VHcNuBk7-sU) to download and install library and set it up in CodeBlocks
2. [Video link](https://youtu.be/JO_F-Rpb9qQ) to solve reference error

The code is to be run as is, most instructions are clearly written in it. Note that you must have a .txt file already made if you wish to compress the words in a file. Also note that a file itself cannot be compressed using this code.

Limitations of the code:
1. If a small input is compressed, it is likely that the compressed string will be larger that the input string.
2. If the file you try to decompress is too big, you will encounter an error. The decompression works only for relatively small files
