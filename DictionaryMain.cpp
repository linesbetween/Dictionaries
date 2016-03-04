// Display menu of multi language dictionary
// Print content or search. 
// DictionaryMain.cpp
// Hanfei Xu

#include <iostream>
using std::cout;
using std::cin;

#include <algorithm>
#include <cstdlib>
#include <conio.h>
#include <cstring>
#include <iomanip>
#include <ctype.h>

#include "Txt2Bin.h"
#include "LoadDictionary.h"

int menu1();
int menu2(int);
bool sortByWord(const Entry &lhs, const Entry &rhs);
void displayDictPart(int dictCode, char wordType[TYPE_SIZE]);
void displaySample(vector<Entry> dict); // display German to English noun;
void displayDictAll(int dictCode); //
void displayDictAll(vector<Entry> dict);
void searchWord(string, vector<Entry>);// search in one dictionary


int main(){

	vector<Entry> temp, dictGeEn, dictFrEn, dictLaEn, dictHeEn;

	int choice1, choice2;
	char type[TYPE_SIZE], all[] = {'a','l', 'l'};
	char key[PRE_SIZE + WORD_SIZE];
	int dictCode;
	ifstream dictBin;
	bool isConverted = false, isLoaded = false;

	for (;;){
		choice1 = menu1();
		if (choice1 == 1){
			dictBin.open("dic1.dat");
			if (dictBin.fail()){
				cout << "Convert txt to binary... \n";
				isConverted = txt2Bin("dic1.txt", "dic1.dat");
			}
			else{
				cout << "Txt already converted to Binary.\n";
				isConverted = true;

				if (!isLoaded){
					loadDictionary("dic1.dat", temp);
					std::sort(temp.begin(), temp.end(), sortByWord);
					isLoaded = true;
				}
				else
					cout << "Dictionary is already loaded. \n";			
			}
			dictBin.close();
			/*

			//load dictionaries, check file exis 
			if (txt2Bin("dictGeEn.txt", "dictGeEn.dat"))
				loadDictionary("dictGeEn.dat", dictGeEn);
			if (txt2Bin("dictFrEn.txt", "dicFrEn.dat"))
				loadDictionary("dicFrEn.dat", dictFrEn);
			if (txt2Bin("dictLaEn.txt", "dicLaEn.dat"))
				loadDictionary("dicLaEn.dat", dictLaEn);
			if (txt2Bin("dicHeEn.txt", "dicHeEn.dat"))
				loadDictionary("dictHeEn.dat", dictHeEn);
				*/
			//break, back to main menu
			cout << "Press Enter to return to main menu \n";
			_getch();
			continue;
		}
		else if (choice1 == 10){//search
			cout << "Please enter a word for search \n";
			string key1;
			string key2 = "\0";
			cin >> key1;
			getline(cin,key2);
			cout << "key1:" << key1 << ", key2:" << key2<<endl;
			if (key2 == "\0") key2 = key1;
			else key2.erase(0, 1);
			searchWord(key2, temp);
		}
		else if (choice1 == 11){ //quit
			system("cls");
			cout << "See you next time \n";
			exit(0);
		}
		else if (choice1 >=2 && choice1 <=9){ // if choice1 == 2~9
			/*
			//TEST
			string key1, key2;
			char keyChar[20];
			cout << "Please enter a word for search \n";
			cin >> key1;
			cin >> key2;
			if (key2 == "") key2 = key1;
			strcpy_s(keyChar, key2.c_str());
			searchWord(keyChar, temp);
			
			//cin.getline(key, PRE_SIZE+WORD_SIZE, '\n');
			//searchWord(key, temp);

			displaySample(temp);
			//END TEST
			*/
			choice2 = menu2(choice1);
			if (choice2 == 8 ){
				continue;
			}

			switch (choice1){
			case 2 : dictCode = 1; break;
			case 3 : dictCode = 2; break;
			case 4 : dictCode = 3; break;
			case 5 : dictCode = 4; break;
			case 6 : dictCode = 5; break;
			case 7 : dictCode = 6; break;
			case 8 : dictCode = 7; break;
			case 9 : dictCode = 8; break;
			default: cout << "Wrong dictionary picked \n"; continue;
			}

			switch (choice2)
			{
			case 1 : displaySample(temp);/*displayDictPart(dictCode, "noun");*/ break;
			case 2 : displayDictPart(dictCode, "verb"); break;
			case 3 : displayDictPart(dictCode, "preposition"); break;
			case 4 : displayDictPart(dictCode, "adjective"); break;
			case 5 : displayDictPart(dictCode, "adverb"); break;
			case 6 : displayDictPart(dictCode, "cardinal number"); break;
			case 7 : displayDictAll(temp); break; //TEST
			default: cout << "Please select the correct type of word \n"; continue;
			}
		}
		else {
			cout << "Please entner integer between 1 to 11 \n";
			cout << "Presh Enter to try again.\n";
			_getch();
			continue;
		}
	}

	_getch();
	return 0;
}



int menu1(){
	int choice1 = 0;

		system("cls");
		cout << "***Dictionary*** \n";
		cout << "(1) Create the word list \n";
		cout << "(2) German to English \n";
		cout << "(3) French to English \n";
		cout << "(4) Latin to English \n";
		cout << "(5) Hebrew to English \n";
		cout << "(6) English to German \n";
		cout << "(7) English to French \n";
		cout << "(8) English to Latin \n";
		cout << "(9) English to Hebrew \n";
		cout << "(10) Search for a word in one language and return in another language \n";
		cout << "(11) Quit \n\n";
		cout << "Please enter your choice: ";
		
		cin >> choice1; cin.ignore(100, '\n');
		//TODO check digit input (letter will crash program)
		/*
		if (choice1 < 1 || choice1 > 11){
			cout << "Please entner integer between 1 to 11 \n";
			_getch();

		}
		*/
		//retunr 1 - 9 and discard sndDigit
		 return choice1;
	
}

int menu2(int choice1){
	int choice2;
	switch (choice1){
	case 2 : cout << "German to English \n"; break;
	case 3 : cout << "French to English \n"; break;
	case 4 : cout << "Latin to English \n"; break;
	case 5 : cout << "Hebrew to English \n"; break;
	case 6 : cout << "English to German \n"; break;
	case 7 : cout << "English to French \n"; break;
	case 8 : cout << "English to Latin \n"; break;
	case 9 : cout << "English to Hebrew \n"; break;
	default: cout << "No such choice"; return '\0';
	}

	while (true){
		cout << "(1) nouns \n";
		cout << "(2) verbs \n";
		cout << "(3) prepositions \n";
		cout << "(4) adjectives \n";
		cout << "(5) adverbs \n";
		cout << "(6) cardinal numbers \n";
		cout << "(7) all \n";
		cout << "(8) return to level 1 menu \n";
		cin>>choice2;
		cin.ignore(100, '\n');
		if (choice2< 1 || choice2 > 8){
			cout << "Please enter integer between 1 to 8\n";
			continue;
		}
		else return choice2;
	};

}


bool sortByWord( const Entry &lhs, const Entry &rhs) {
	
	string wordL = lhs.getWord();
	string wordR = rhs.getWord();

	wordL.at(0) = tolower(lhs.getWord().at(0));
	wordR.at(0) = tolower(rhs.getWord().at(0));

	if (strcmp(wordL.c_str(), wordR.c_str()) < 0)
		return true;
	else
		return false;
}


vector<Entry> bubbleSort(const vector<Entry> &dict){
	
	vector<Entry> sortedDict(dict.size());
	copy(dict.begin(), dict.end(), sortedDict.begin());
	for (Entry entry: sortedDict)
	{
		for (auto iter = dict.begin(); iter < dict.end(); ++iter)
		{
			if (strcmp(iter->getWord().c_str(),(iter+1)->getWord().c_str())>0)
			{
				char temp[WORD_SIZE];
				strcpy_s(temp, (iter + 1)->getWord().c_str());
				for (int i = 0; i < WORD_SIZE; ++i){
					(iter + 1)->getWord().at(i) = iter->getWord().at(i);
					iter->getWord().at(i) = temp[i];
				}
				//strncpy_s((iter + 1)->getEntry().word, iter->getEntry().word, WORD_SIZE);
				//strncpy_s(iter->getEntry().word,temp, WORD_SIZE);
				//copy(iter->getEntry().word[0], iter->getEntry().word[WORD_SIZE], (iter + 1)->getEntry().word[0]);
				//copy(temp[0], temp[WORD_SIZE], iter ->getEntry().word[0]);
			}
			++iter;
		}
	}
	
	return sortedDict;
}


void displayDictPart(int dictType, char wordType[]){
	cout << "you selected dictionary " << dictType << "word type: " << wordType;
	_getch();
}

void displaySample(vector<Entry> dict){
	
	vector<Entry> temp; //to hold certain type of words

	/*
	for (auto iter = std::cbegin(dict); iter != std::cend(dict); ++iter){// walk through dict vector
		if (strcmp(iter->getEntry().type, "noun") == 0){ //if type = noun
			//write to temp vector
			temp.emplace_back(*iter);
			cout << "push to vector" << iter->getEntry().prefix << " " << iter->getEntry().word << " " << iter->getEntry().type
				<< " " << iter->getEntry().prefix << " " << iter->getEntry().meaning << endl;
		}
		else
			continue;
	}
	*/

	for (Entry entry:dict){// walk through dict vector
		if (strcmp(entry.getType().c_str(), "noun") == 0){ //if type = noun
			//write to temp vector
			temp.emplace_back(entry);
			cout << left;
			cout << "Found: " << setw(4) << entry.getPrefix() << " " << setw(20) << entry.getWord()
				<< " " << setw(20) << entry.getType() << " " << setw(20) << entry.getMeaning() << endl;
		}
	}


	//std::sort(temp.begin(), temp.end(), sortByWord);	

	for (Entry entry : temp){
		if (entry.getPrefix().empty()){
			cout << setw(25) << entry.getWord() << " " << setw(20) << entry.getType() << " "
				<< setw(20) << entry.getMeaning() << endl;
		}
		else{
			cout << setw(4) << entry.getPrefix() << " " << setw(20) << entry.getWord() << " " 
				<< setw(20) << entry.getType() << " "<< setw(20) << entry.getMeaning() << endl;
		}
	}

	cout << "\n\n Please press enter to return";
	_getch();
}

void displayDictAll(int dictCode){
	cout << "you are printing the whole dictionary of No." << dictCode;
	_getch();
}

void displayDictAll(vector<Entry> dict){
	//std::sort(dict.begin(), dict.end(), sortByWord);
	for (Entry entry : dict){
		if (entry.getPrefix().empty()){
			cout << setw(25) << entry.getWord() << " " << setw(20) << entry.getType() << " "
				<< setw(20) << entry.getMeaning() << endl;
		}
		else{
			cout << setw(4) << entry.getPrefix() << " " << setw(20) << entry.getWord() << " "
				<< setw(20) << entry.getType() << " "<< setw(20) << entry.getMeaning() << endl;
		}
	}

	cout << "Press Enter to return to main menu \n";
	_getch();
}

void searchWord(string word, vector<Entry> dict){

	/*
	for (int i = 0; i < PRE_SIZE + WORD_SIZE; ++i){
		if (key[i] == ' '){ // if there is prefix
			for (int k=0; k < PRE_SIZE + WORD_SIZE - i; ++k){ // delete prefix and move up the rest
				key[k] = key[k + i + 1];
			}
			break;
		}

		key[PRE_SIZE-1] = '\0'; //delete the reserved length for prefix.
	}
	*/

	cout << "searching for " << word << endl;
	/*
	char* prefix; char* word = ""; // Can't assign char* a, b;
	prefix = strtok_s(key, " ",&word);
	cout << "prefix is: " << prefix << " word is: " << word;

	if (word == ""){ // if prefix is null,  
		word = prefix;
		prefix = "";
	}

	
	*/
	//linear search
	bool found = false;
	//auto iter = dict.begin();
	//_Vector_iterator<_Vector_val<_Simple_types<Entry>>> iter = dict.begin(); //auto
	for(Entry entry :dict){
		if (strcmp(entry.getWord().c_str(), word.c_str()) == 0){
			cout << word << " meaing is: " << entry.getMeaning() << " \n.";
			found = true;
		}
		continue;
	}

	if (found == false)
		cout << word << " not found.\n";
	
	//std::sort(dict.begin(), dict.end(),sortByWord);
	//cout << "sorted \n";

	//binary search
	auto begin = dict.begin();
	auto end = dict.end()-1;
	auto mid = dict.begin();
	auto loc = dict.begin();
	bool flag = false;

	while (begin < end && flag == false)
	{
		cout << "searching...\n";
		mid = begin + (end - begin) / 2;// / size of (*begin)?
		cout << "begin before: " << begin->getWord() << endl;
		cout << "mid before: " << mid->getWord() << endl;
		cout << "end before: " << end->getWord() << endl;		
		if (strcmp(word.c_str(), mid->getWord().c_str()) == 0)
		{
			loc = mid;
			flag = true;
		}
		else if (strcmp(word.c_str(), mid->getWord().c_str())<0)
			end = mid - 1;
		else
			begin = mid + 1; //when key is > array[midpoint]

		cout << "begin after: " << begin->getWord() << endl;
		cout << "mid after: " << mid->getWord() << endl;
		cout << "end after: " << end->getWord() << endl;
	}

	if (flag == true){
		cout << word << " meaing is: " << loc->getMeaning() << " \n.";
		_getch();
	}
	else{
		cout << word << " not found. \n";
		_getch();
	}

}