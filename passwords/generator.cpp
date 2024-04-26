/*
--DISCLAIMER--
This content is the property of David Z Kleinsorge and affiliated parites.
Those who are permitted to access these documents shall respect and preserve the privacy, confidentiality, and security of the project.
The content provided herein is for educational purposes only. It is not intended to encourage or promote any illegal activities. 
Users are reminded to use this information responsibly and in accordance with applicable laws and regulations. 
The provider does not endorse or condone any illegal behavior. Users are solely responsible for their actions and compliance with the law.
*/ /*
This program takes as input a text document containing strings divided into three sets: pre, body and post. When combined, a string from each set should form a "common" password e.g. 'mycool'+'password'+'1998'
The output is all permutations of these three parts, with some custom character exclusion, inclusion, and swapping.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Recursively move through the string s, making special chracter replacements as it goes,
// and adds the final products to the body vector
void pushBodyRecursive(vector<string>& body, string s, int i);

// Push original string s to vector post, as well as variants
void pushPostVariations(vector<string>& post, string s);

// Add ! and ? to all strings in vector v
void appendPunctuation(vector<string>& v);


int main(int argc, char* argv[]) {
    if (argc < 3) { throw "Too few args"; }
    
    ifstream fin(argv[1]);
    if (!fin.is_open()) { throw "File failed to open\n"; }
    string header;
    string word;
    vector<string> pre = { "" };
    vector<string> body = { "" };
    vector<string> post = { "" };
    while (!fin.eof()) {
        fin >> word;
        if (word[0] == '-')   {
            header = word.substr(1);
            continue;
        }
        if (header == "pre") {
            pre.push_back(word);
        }
        else if (header == "body") {
            pushBodyRecursive(body, word, 0);
        }
        else if (header == "post") {
            pushPostVariations(post, word);
        }
        else { throw "Unrecognized header\n"; }
    }
    fin.close();
    appendPunctuation(post);

    cout << "Writing to " << argv[2] << " . . .\n";
    ofstream fout(argv[2]);
    if (!fout.is_open()) { throw "File failed to open\n"; }
    int count = 0;
    string finalWord;
    for (int i = 0; i < pre.size(); ++i) {
        for (int j = 0; j < body.size(); ++j) {
            for (int k = 0; k < post.size(); ++k) {
                finalWord = pre[i] + body[j] + post[k];
                if (finalWord.length() < 5) continue;
                fout << pre[i] + body[j] + post[k] << endl;
                //cout << pre[i] + body[j] + post[k] << endl;
                ++count;
            }
        }
    }
    
    cout << endl << count << " strings generated\n";
    fout.close();
    return 0;
}

void pushBodyRecursive(vector<string>& body, string s, int i) {
    if (i == s.length()) {
        body.push_back(s);
        return;
    }
    string o = s; 
    if (i == 0) { // replace first char with upper case
        s[0] -= 32;
        pushBodyRecursive(body, s, i+1);
    }
    if (s[i] == 'o') { // replace o with 0
        s[i] = '0';
        pushBodyRecursive(body, s, i + 1);
    }
    else if (s[i] == 'i' || s[i] == 'l') { // replace i or l with 1
        s[i] = '1';
        pushBodyRecursive(body, s, i + 1);
    }
    else if (s[i] == 's') { // replace s with 3 and 5
        s[i] = '3';
        pushBodyRecursive(body, s, i + 1);
        s[i] = '5';
        pushBodyRecursive(body, s, i + 1);
    }
    pushBodyRecursive(body, o, i + 1); // do nothing and continue
}

void pushPostVariations(vector<string>& post, string s) {
    post.push_back(s);
    // if postfix is length 4 and begins in 1 or 2, add the last two digits to post as well
    if (s.length() == 4 && (s[0] == '1' || s[1] == '2')) {
        post.push_back(s.substr(2));
    }
    // if length 2, swap numbers
    if (s.length() == 2 && s[0] != s[1]) {
        string r = s;
        std::reverse(r.begin(), r.end());
        post.push_back(r);
    }
}

void appendPunctuation(vector<string>& v) {
    for (int i = 0; i < v.size(); ++i) {
        v.push_back(v[i] + '!');
        v.push_back(v[i] + '?');
    }
}