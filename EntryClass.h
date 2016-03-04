#ifndef ENTRYCLASS_H
#define ENTRYCLASS_H
#include "EntryStruct.h";
//#include <cstring>
#include <string>

class Entry{
private:
	//EntryStruct data;
	string prefix, word, meaning, type;

public:

	Entry(){ ; }

	Entry(EntryStruct en){
		prefix = string(en.prefix);
		word = string(en.word);
		meaning = string(en.meaning);
		type = string(en.type);
	}


	string getPrefix() const { return prefix; }
	string getWord() const { return word; }
	string getMeaning() const { return meaning; }
	string getType() const{ return type; }
	/*
	Entry(EntryStruct en){

		strncpy_s(data.meaning, en.meaning, MEANING_SIZE);
		//data.meaning[MEANING_SIZE - 1] = '\0';
		strncpy_s(data.prefix, en.prefix, PRE_SIZE);
		//data.prefix[PRE_SIZE - 1] = '\0';
		strncpy_s(data.type, en.type, TYPE_SIZE);
		//data.type[TYPE_SIZE - 1] = '\0';
		strncpy_s(data.word, en.word, WORD_SIZE);
		//data.word[WORD_SIZE - 1] = '\0';
		
	}


	EntryStruct getEntry() const{
		return data;
	}
	
	*/

	// Less-than operator
	bool operator< (const Entry& en) const
	{
		int result{ strcmp(word.c_str(), en.getWord().c_str()) };
		return (result < 0 );
	}


};

#endif