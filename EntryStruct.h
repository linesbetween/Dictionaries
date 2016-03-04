#ifndef ENTRYSTRUCT_H
#define ENTRYSTRUCT_H

const int PRE_SIZE = 5, WORD_SIZE = 20, MEANING_SIZE = 20, TYPE_SIZE = 20;

struct EntryStruct{

	char prefix[PRE_SIZE];
	char word[WORD_SIZE];
	char meaning[MEANING_SIZE];
	char type[TYPE_SIZE];
};

#endif