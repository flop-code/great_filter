# The Great Filter
The Great Filter is a tool designed to easily and quickly filter and merge huge amounts of data,
that can be represented as a set of unique strings.

The project was first created to filter out big password leaks like `rockyou.txt`
and merge them into one base (_of course for educational purposes only_).

## Requirements
- GNU Make to build the project, but alternatively,
you can just paste the command from the Makefile into your terminal.

## Usage
1. clone the repository;
2. cd into it;
3. run `make` to build the project;
4. run `./tgf [input_file] ...` to filter and merge the files together.

## Perfomance
According to the tests, it takes <20 seconds and <1GB of RAM to process 1GB file, where each line is unique.

**The less unique the lines (or rather their prefixes), the less memory and time are required to process them.**

## How does it work?
First of all, the program can't just read the whole input file into the RAM,
instead, it reads it using fixed-sized chunks and then splits that chunk into lines, filters them,
and saves them into a Trie data structure.
After reading the whole list of input files, the program starts to write a list of lines
into a separate output file called `output.txt`, using the same chunks approach.

Using this approach, same line prefixes won't be stored in memory multiple times,
and you can avoid duplicating entries.

Also, due to using the Trie data structure, the order of input lines is not preserved.
In the output file, lines with the same prefix will be written near each other.

## ToDo
- [x] Min/max character number filter;
- [ ] Non-readable character filter;
