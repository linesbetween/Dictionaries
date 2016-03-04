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
		else if (choice1 == 0){
			cout << "Presh Enter to try again.\n";
			_getch();
			continue;
		}
		else {
			cout << "Please enter integer between 1~11 \n";
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
		if (cin.fail()){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Please enter an integer\n";
			return 0;
		}
	
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
		cin >> choice2; cin.ignore(100, '\n');
		if (cin.fail()){
			cin.clear();
			cin.ignore(100, '\n');
			cout << "Please enter an integer \n";
			continue;
		}
		
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



void displayDictPart(int dictType, char wordType[]){
	cout << "you selected dictionary " << dictType << "word type: " << wordType;
	_getch();
}

void displaySample(vector<Entry> dict){
	
	vector<Entry> temp; //to hold certain type of words

	for (Entry entry:dict){// walk through dict vector
		if (strcmp(entry.getType().c_str(), "noun") == 0){ //if type = noun
			//write to temp vector
			temp.emplace_back(entry);
			cout << left;
			cout << "Found: " << setw(4) << entry.getPrefix() << " " << setw(20) << entry.getWord()
				<< " " << setw(20) << entry.getType() << " " << setw(20) << entry.getMeaning() << endl;
		}
	}


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

	cout << "searching for " << word << endl;

	//linear search
	bool found = false;
	for(Entry entry :dict){
		if (strcmp(entry.getWord().c_str(), word.c_str()) == 0 /*entry.getWord().compare(word)==0*/){
			cout << word << " meaing is: " << entry.getMeaning() << " \n.";
			found = true;
		}
		continue;
	}

	if (found == false)
		cout << word << " not found.\n";
	cout << "Press Enter to go back \n";
		_getch();
	
	
}