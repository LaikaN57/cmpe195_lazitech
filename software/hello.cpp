#include<iostream>
#include<string>
#include<algorithm>
#include <fstream>
#include <sstream>
#include<vector>
#include<cstring>
using namespace std;

string noPunct(string removeW);

string lowerCase(string word);


void wordSum(vector<string>& addUp);


int main() {
	ifstream fin;
	 string current_word, next_word, final_word;
	  vector<string> wordList;
		fin.open("test.txt");
		if (fin.fail()) {
			cout << "Unable to open file" << endl;
		}
		 while(fin >> current_word){ //enters word or phrase into loop
			 if(current_word == "stream"){
				 cout << "Stream Found!!" << endl;
				 do{
					 fin >> next_word;
					 wordList.push_back(next_word);
				 }while(next_word != "endstream");
		    //next_word = lowerCase(next_word);//takes the string of words to be lowercased
		    //final_word =  noPunct(next_word); //has punctuations removed
		    //wordList.push_back(next_word);// adds word into vector
		   }
		 }
		     wordSum(wordList); //increments to word

		return 0;
		}

///////////////////////////////////////////
string noPunct(string removeW) {
	int size = removeW.size();
	int character =  removeW[size-1];
	if(ispunct(character)){
		removeW = removeW.substr(0, removeW.size()-1);
	}
	return removeW;
 }

string lowerCase(string phrase){
  int i = 0;
  char s;

  while(phrase[i]){
    s = phrase[i];
    phrase[i] = tolower(s);
    i++;
  }
  return phrase;
}


void wordSum(vector<string>& addUp){
  /* for(int i=0; i < addUp.size(); i++){
    addUp[i] = i + 1;
    } */
   int count = 1;
  for(int i = 0; i < addUp.size(); i++){
    if (addUp[0] != addUp[i]) {
      cout << addUp[0] << " " << count << endl;
      count = 0;
      addUp[0] = addUp[i];
     }
 count++;
  }
   cout << addUp[0] << " " << count << endl;
}




