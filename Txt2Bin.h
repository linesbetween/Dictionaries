// Convert txt file into binary file.
// By reading txt file into structure and write structure to binary file
// Txt2Bin.h
// Hanfei Xu

#ifndef TXT2BIN_H
#define TXT2BIN_H

#include "EntryStruct.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

bool txt2Bin (string inName, string outName){

	char prefix[PRE_SIZE] = {'\0'};
	char word[WORD_SIZE];
	char meaning[MEANING_SIZE];
	char type[TYPE_SIZE];
	char end;
	EntryStruct entryStruct;

	ifstream inFile(inName, ios::in);
	if (!inFile){
		cout << "no input file. \n";
		return false;
	}

	ofstream outFile(outName, ios::out | ios::binary);

	while (!inFile.eof()){
		
		inFile.getline(prefix, PRE_SIZE,'$');
		inFile.getline(word, WORD_SIZE, '$');
		inFile.getline(meaning, MEANING_SIZE, '$');
		inFile.getline(type, TYPE_SIZE, '$');
		inFile.ignore(1000, '\n');

		if (prefix[0] == '\0')
			entryStruct.prefix[0] = '\0';
		else
			strncpy_s(entryStruct.prefix, prefix, PRE_SIZE);
		//entryStruct.prefix[PRE_SIZE -1] = '\0';
		strncpy_s(entryStruct.word, word, WORD_SIZE);
		//entryStruct.word[WORD_SIZE -1] = '\0';
		strncpy_s(entryStruct.meaning, meaning, MEANING_SIZE);
		//entryStruct.meaning[MEANING_SIZE -1] = '\0';
		strncpy_s(entryStruct.type, type, TYPE_SIZE);
		//entryStruct.type[TYPE_SIZE -1 ] = '\0';

		outFile.write(reinterpret_cast<char *> (&entryStruct), sizeof(entryStruct));

		cout << "one entry written into bin\n";
	}

	inFile.close();
	outFile.close();

	return true;
}

#endif