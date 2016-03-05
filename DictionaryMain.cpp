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

vector<Entry> temp, dictGeEn, dictFrEn, dictLaEn, dictHeEn;

int main(){

	int choice1, choice2;
	char type[TYPE_SIZE], all[] = {'a','l', 'l'};
	char key[PRE_SIZE + WORD_SIZE];
	int dictCode;
	ifstream dictBin, dictBin1, dictBin2, dictBin3, dictBin4;
	bool isConverted = false, isLoaded = false;

	for (;;){
		choice1 = menu1();

		// choice 1 load
		if (choice1 == 1){ 
			dictBin.open("dic1.dat");
			dictBin1.open("dictGeEn.dat");
			dictBin2.open("dictFrEn.dat");
			dictBin3.open("dictLaEn.dat");
			dictBin4.open("dictHeEn.dat");

			if (dictBin.fail() || dictBin1.fail() || dictBin2.fail() || dictBin3.fail() || dictBin4.fail()){
				cout << "Convert txt to binary... \n";
				txt2Bin("dic1.txt", "dic1.dat");
				txt2Bin("dictGeEn.txt", "dictGeEn.dat");
				txt2Bin("dictFrEn.txt", "dictFrEn.dat");
				txt2Bin("dictLaEn.txt", "dictLaEn.dat");
				txt2Bin("dictHeEn.txt", "dictHeEn.dat");
			}
			else{
				cout << "Txt already converted to Binary.\n";
				isConverted = true;

				if (!isLoaded){
					loadDictionary("dic1.dat", temp);
					std::sort(temp.begin(), temp.end(), sortByWord);
					loadDictionary("dictGeEn.dat", dictGeEn);
					std::sort(dictGeEn.begin(), dictGeEn.end(), sortByWord);
					loadDictionary("dictFrEn.dat", dictFrEn);
					std::sort(dictFrEn.begin(), dictFrEn.end(), sortByWord);
					loadDictionary("dictLaEn.dat", dictLaEn);
					std::sort(dictLaEn.begin(), dictLaEn.end(), sortByWord);
					loadDictionary("dictHeEn.dat", dictHeEn);
					std::sort(dictHeEn.begin(), dictHeEn.end(), sortByWord);

					isLoaded = true;
				}

				else
					cout << "Dictionaries are already loaded. \n";
			}
			dictBin.close();
			dictBin1.close();
			dictBin2.close();
			dictBin3.close();
			dictBin4.close();
			
			//break, back to main menu
			cout << "Press Enter to return to main menu \n";
			_getch();
			continue;

		}//End of choice 1


		// choice 10 search
		else if (choice1 == 10){
			if (isLoaded){
				cout << "Please enter a word for search \n";
				string key1;
				string key2 = "\0";
				cin >> key1;
				getline(cin, key2);
				cout << "key1:" << key1 << ", key2:" << key2 << endl;
				if (key2 == "\0") key2 = key1;
				else key2.erase(0, 1);
				searchWord(key2, temp);
			}
			else {
				cout << "Please select 1 to load dictionary first! \n";
				cout << "Press Enter to go back \n";
				_getch();
				continue;
			}
		}// End of choice 10 search

		//choice 11 exit
		else if (choice1 == 11){ //quit
			system("cls");
			cout << "See you next time \n";
			exit(0);
		}//End of choice 11 exit


		//choice 2- 9 display
		else if (choice1 >= 2 && choice1 <= 9){ 

			if (isLoaded){
				choice2 = menu2(choice1);
				//choice2 = 8, return to main
				if (choice2 == 8){
					continue;
				}

				//choice1 = 2-9 choose dictionary
				switch (choice1){
				case 2: dictCode = 1; break;
				case 3: dictCode = 2; break;
				case 4: dictCode = 3; break;
				case 5: dictCode = 4; break;
				case 6: dictCode = 5; break;
				case 7: dictCode = 6; break;
				case 8: dictCode = 7; break;
				case 9: dictCode = 8; break;
				default: cout << "Wrong dictionary picked \n"; continue;
				}

				//choice2= 1-7 choose part or all
				switch (choice2)
				{
				case 1: displaySample(temp);/*displayDictPart(dictCode, "noun");*/ break;
				case 2: displayDictPart(dictCode, "verb"); break;
				case 3: displayDictPart(dictCode, "preposition"); break;
				case 4: displayDictPart(dictCode, "adjective"); break;
				case 5: displayDictPart(dictCode, "adverb"); break;
				case 6: displayDictPart(dictCode, "cardinal number"); break;
				case 7: displayDictAll(temp); break; //TEST
				default: cout << "Please select the correct type of word \n"; continue;
				}
			}
			else {
				cout << "Please select 1 in main menu to load dictionary first! \n";
				cout << "Press Enter to go back \n";
				_getch();
				continue;
			} // End of if(isLoaded)

			}// End of choice 2-9 display


		    //choice1 is NOT an integer
			else if (choice1 == 0){
				cout << "Presh Enter to try again.\n";
				_getch();
				continue;
			}

			//choice1 is NOT within range
			else {
				cout << "Please enter integer between 1~11 \n";
				cout << "Presh Enter to try again.\n";
				_getch();
				continue;
			}

	}// End of for
	
}// End of main()



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

bool sortByMeaning(const Entry &lhs, const Entry &rhs) {

	string wordL = lhs.getMeaning();
	string wordR = rhs.getMeaning();

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
	vector<Entry> *currentDict = &dictGeEn;

	switch (dictCode){
	case 1:;
	case 5: currentDict = &dictGeEn; break;
	case 2:;
	case 6: currentDict = &dictFrEn; break;
	case 3:;
	case 7: currentDict = &dictLaEn; break;
	case 4:;
	case 8: currentDict = &dictHeEn; break;
	}


	for (Entry entry : *currentDict){
		if (entry.getPrefix().empty()){
			cout << setw(25) << entry.getWord() << " " << setw(20) << entry.getType() << " "
				<< setw(20) << entry.getMeaning() << endl;
		}
		else{
			cout << setw(4) << entry.getPrefix() << " " << setw(20) << entry.getWord() << " "
				<< setw(20) << entry.getType() << " " << setw(20) << entry.getMeaning() << endl;
		}
	}
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