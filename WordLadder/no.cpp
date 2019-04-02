#include "WordLadder.h"
#include <fstream>

using namespace std;

// list<string> dict;        //list of possible words in ladder


/* Passes in the name of a file that contains a dictionary of 5-letter words.
   Fills the list (dict) with the words within this file. 
   If the file does not open for any reason or if any word within the file
   does not have exactly 5 characters, this function should output an
   error message and return.
*/
WordLadder::WordLadder(const string & filename){
	string word;

	ifstream inFS;
	inFS.open(filename.c_str());

	if(!inFS.is_open()){
		cout << "Error opening " << filename << "." << endl;
		return;
	}

	while(inFS >> word){
		if(word.size() != 5){
			cout << "Error, " << word << " is not exactly 5 characters." << endl;
			return;
		}
		dict.push_back(word);
	}

	inFS.close();
}

/* Passes in two 5-letter words and the name of an output file.
   Outputs to this file a word ladder that starts from the first word passed in
   and ends with the second word passed in.
   If either word passed in does not exist in the dictionary (dict),
   this function should output an error message and return.
   Otherwise, this function outputs to the file the word ladder it finds or outputs
   to the file, the message, "No Word Ladder Found!!"
*/
// void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile ){
// 	if(inDictionary(start) && inDictionary(end)){

// 		stack<string> firstLadder;
// 		firstLadder.push(start);

// 		queue<stack<string> > ladder;
// 		ladder.push(firstLadder);

// 		// find words that are off by one from the start
// 			// change each letter in the start word to a - z 
// 				// loop through dictionary
// 					// if new word is in dictionary
// 						// create new stack from first stack
// 						// push new word
// 						// if new word = end
// 							// return
// 						// else
// 							//	enqueue stack into queue
// 							// remove new word from dictionary
// 				// dequeue front stack
// 		while(!ladder.empty()){
// 			string word = ladder.front().top();

// 			for(string::iterator i = word.begin(); i != word.end(); i++){
// 				for(char change = 'a'; change <= 'z'; change++){
// 					word = ladder.front().top();
// 					*i = change;
// 					if(inDictionary(word)){
// 						stack<string> newLadder = ladder.front();
// 						newLadder.push(word);
// 						// cout << word << endl;
// 						if(word == end){
// 							// cout << "done" << endl;
// 							// ladder.front().push(end);
// 							return fillOutput(outputFile, newladder);
// 						} else {
// 							ladder.push(newLadder);
// 							dict.remove(word);
// 						}
// 					}
// 				}
// 			}
// 			ladder.pop();
// 		}
		
// 		ofstream outFS(outputFile.c_str(), ofstream::trunc);
// 		if(outFS.is_open()){
// 			outFS << "No Word Ladder Found!!";

// 			outFS.close();
// 		} else{
// 			cout << "Error opening " << outputFile << endl;
// 		}
// 	} else{
// 		cout << "Word not in dictionary." << endl;
// 		return;
// 	}
// }

void WordLadder::fillOutput(const string& outputFile, stack<string> ladder){
	ofstream outFS(outputFile.c_str(), ofstream::trunc);
	if(outFS.is_open()){
		stack<string> rev;
		for(stack<string> fill = ladder; !fill.empty(); fill.pop()){
			rev.push(fill.top());
		}
		outFS << rev.top();
		rev.pop();
		for(stack<string> fill = rev; !fill.empty(); fill.pop()){
			outFS << " " << fill.top();
		}
		outFS.close();
	} else{
		cout << "Error opening " << outputFile << endl;
		return;
	}
}

bool WordLadder::inDictionary(const string& word){
	for(list<string>::iterator it = dict.begin(); it != dict.end(); ++it){
		if(word == *it){
			return true;
		}
	}
	// cout << word << " not in dictionary." << endl;
	return false;
}
// create a Stack containing just the first word in the ladder
// enqueue this Stack on to a Queue of Stacks
// while this Queue of Stacks is not empty
// 		get the word on top of the front Stack of this Queue
// 		for each word in the dictionary
// 			if the word is off by just one letter from the top word
// 				create a new Stack that is a copy of the front Stack and push on this off-by-one word found
// 				if this off-by-one word is the end word of the ladder, this new Stack contains the entire word ladder. You are done!
// 				otherwise, enqueue this new Stack and remove this word from the dictionary
// 		dequeue this front stack
// if the Queue is empty and you didn't find the word ladder, a word ladder does not exist for these 2 words


void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile ){
	ofstream outFS(outputFile.c_str(), ofstream::trunc);

	if(!inDictionary(start) || !inDictionary(end)){
		outFS << "word not in dictionary.";
		return;
	}
	
	stack<string> ladder;
	ladder.push(start);
	queue<stack<string> > wordLadder;
	wordLadder.push(ladder);
	dict.remove(start);
	
	if(start == end){
		return fillOutput(outputFile, ladder);
	}
		stack<string> newLadder = wordLadder.front();
		string word = wordLadder.front().top();
	
	while(!wordLadder.empty()){
		// for(unsigned i = 0; i < word.size(); ++i){
		// 	word = wordLadder.front().top();
		// 	for(char change = 'a'; change <= 'z'; ++change){
		// 		word = word.replace(i, 1, 1, change);
		// 		cout << word << endl;
		word = wordLadder.front().top();
		for(list<string>::iterator it = dict.begin(); it != dict.end(); ++it){
			if(hasFour(word, *it)){
				newLadder = wordLadder.front();
				newLadder.push(*it);
				wordLadder.push(newLadder);
				if(*it == end){
					return fillOutput(outputFile, newLadder);
				}
					dict.remove(*it);
					--it;
			}
		}
		wordLadder.pop();
	}
		if(outFS.is_open()){
			outFS << "No Word Ladder Found!!";
			outFS.close();
		} else{
			cout << "Error opening " << outputFile << endl;
		}
}

bool WordLadder::hasFour(const string word, const string fuck){
	int count = 0;
	for(unsigned i = 0; i < word.size(); i++){
		if(word.at(i) == fuck.at(i)){
			++count;
		}
	}
	if(count == 4){
		return true;
	} 
	return false;
}
	

/* Passes in two 5-letter words and the name of an output file.
   Outputs to this file a word ladder that starts from the first word passed in
   and ends with the second word passed in.
   If either word passed in does not exist in the dictionary (dict),
   this function should output an error message and return.
   Otherwise, this function outputs to the file the word ladder it finds or outputs
   to the file, the message, "No Word Ladder Found!!"
*/