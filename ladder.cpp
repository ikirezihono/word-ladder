

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <set>
using namespace std;

const int ALPHA_LENGTH = 26;

void findWord(string &word1, string &word2);
void DisplayWordLadder(string word1, string word2);

int main() {
    
  string word1, word2;
  findWord(word1, word2); 
  DisplayWordLadder(word1, word2);
    
  return 0;
}

void findWord(string &word1, string &word2) {
  while (true) {
    cout << "Please enter a word: ";
    cin>>word1;
    
    cout << "Please enter another word of the same length: ";
    cin>>word2;
    
    if (word1.length() == word2.length()) {
      break;
    }
    cout << "Please enter two words with the same length." << endl;
  }
}

void DisplayWordLadder(string word1, string word2){
    
    // creates an empty queue of stacks
    queue<stack<string> > myQueue;
    
    //Create a stack which will contain a final word ladder
    stack<string> wordladder;
    
    // creates and adds a stack containing word1 to the queue
    stack<string> myStack;
    myStack.push(word1);
    myQueue.push(myStack);
    
    // creates two sets: one for the dictionary and one for the tested words
    string token;
    ifstream dictionary("EnglishWords.dat");
    set<string> myDictionary;
    set<string> testedWords;
    
    if(dictionary.is_open()) {
      
	      while (dictionary >> token) {
	    	myDictionary.insert(token);
	      }
	      
	      // while the queue is not empty:
	      while (!(myQueue.empty())) {
	        
	        // dequeue the partial-ladder stack from the front of the queue.
			stack<string> ladder = myQueue.front();
			myQueue.pop();
			string word = ladder.top();
		        
			// if the word on top of the stack is the destination word:
			if (word == word2) {
			
			  cout << "The ladder from " << word1 << " to " << word2 << " is \n";
			 
			  while(!ladder.empty()){
			  	wordladder.push(ladder.top());
			  	ladder.pop();
			  }
			  while(!wordladder.empty()){
			  	cout<<wordladder.top()<<" --> ";
			  	wordladder.pop();
			  }
		} 
		else {
			  // for each valid English word that 
			  string test;
			  for (int i = 0; i < word.size(); i++) {
			    for (char j = 'a'; j <= 'z'; j++) {
			    test = word.substr(0, i) + j + word.substr(i + 1);
		            
			    // if that word is an english word
			    if (myDictionary.count(test)) {
			      
			      // if that neighbor word has not already been used in a ladder before:
			      if (!testedWords.count(test)) {
				
						// create a copy of the current ladder stack.
						stack<string> copy = ladder;
				                
						// put the neighbor word on top of the copy stack.
						copy.push(test);
				                
						// add the copy stack to the end of the queue.
						myQueue.push(copy);
			      }
			    }
		            
			    // Add test to tested words because it is already used.
			    testedWords.insert(test);
			}
		}
	      }
	    }
    } else {
      cerr << "Sorry, Dictionary could not be opened" << endl;
    }
    
    
}
