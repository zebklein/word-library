/*
--DISCLAIMER--
This content is the property of David Z Kleinsorge and affiliated parites.
Those who are permitted to access these documents shall respect and preserve the privacy, confidentiality, and security of the project.
*/ /*
This program generates all ceasar cipher combinations of a given string with some custom filtering on certain character combinations.
This filtering is meant to narrow the output so as to increase the likelyhood of generating "sensible" names in the English language.
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;


string toLower(string s) {
    for (int i = 0; i < s.size(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}
vector<int> constructIntArr(string s) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<int> nameArr;
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (s[i] == alphabet[j]) {
                nameArr.push_back(j);
                break;
            }
        }
    }
    return nameArr;
}

void printIntVector(vector<int> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}
/*void printCharVector(vector<char> v) {
    for (int i = 0; i < v.size(); ++i) {
        cout << v[i];
    }
}*/

vector<int> incrementVector(vector<int> v) {
    for (int i = 0; i < v.size(); ++i) {
        if (++v[i] == 26) v[i] = 0;
    }
    return v;
}

vector<char> intArrToCharArr(vector<int> v) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    vector<char> s;
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
            if (v[i] == j) {
                s.push_back(alphabet[j]);
                break;
            }
        }
    }
    return s;
}

string intArrToString(vector<char> v) {
    string s(v.begin(), v.end());
    return s;
}

bool checkForObscureLetter(string s) {
    string obscure = "qvzxj";
    for (int i = 0; i < s.size(); ++i) {
        for (int j = 0; j < obscure.size(); ++j) {
            if (s[i] == obscure[j]) return true;
        }
    }
    return false;
}

bool isVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y') return true;
    else return false;
}
bool isTrueVowel(char c) {
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
    else return false;
}
bool hasBadDouble(string s) {
    for (int i = 0; i < s.size() - 1; ++i) {
        if (s[i] == 'k' && s[i + 1] == 'k') return true;
        if (s[i] == 'k' && s[i + 1] == 'b') return true;
        if (s[i] == 'k' && s[i + 1] == 'p') return true;
        if (s[i] == 'b' && s[i + 1] == 'p') return true;
        if (s[i] == 'b' && s[i + 1] == 'k') return true;
        if (s[i] == 'p' && s[i + 1] == 'k') return true;
        if (s[i] == 'p' && s[i + 1] == 'b') return true;

        if (!isVowel(s[i]) || s[i] == 'o') continue;
        if (s[i] == s[i+1]) return true;
        if (s[i] == 'a' && s[i + 1] == 'o') return true;
        if (s[i] == 'a' && s[i + 1] == 'u') return true;
        if (s[i] == 'a' && s[i + 1] == 'e') return true;
        if (s[i] == 'y' && s[i + 1] == 'a') return true;
        if (s[i] == 'y' && s[i + 1] == 'u') return true;
        if (s[i] == 'y' && s[i + 1] == 'i') return true;
        if (s[i] == 'u' && s[i + 1] == 'i') return true;
        if (s[i] == 'u' && s[i + 1] == 'a') return true;
        if (s[i] == 'u' && s[i + 1] == 'o') return true;
        if (s[i] == 'e' && s[i + 1] == 'o') return true;
        if (s[i] == 'e' && s[i + 1] == 'u') return true;
        if (s[i] == 'k' && s[i + 1] == 'k') return true;
        if (s[i] == 'b' && s[i + 1] == 'k') return true;
        if (s[i] == 'k' && s[i + 1] == 'b') return true;
    }
    return false;
}
bool hasTriple(string s) {
    for (int i = 0; i < s.size() - 2; ++i) {
        if (s[i] == s[i + 1] && s[i] == s[i + 2]) return true;
        if (isVowel(s[i]) && isVowel(s[i + 1]) && isVowel(s[i + 2])) return true;
    }
    return false;
}
bool hasVowel(string s) {
    bool found = false;
    for (int i = 0; i < s.size(); ++i) {
        if (isTrueVowel(s[i])) found = true;
    }
    return found;
}
bool ruleViolation(string s) {
    if (isVowel(s[0])) return true;
    if (s[0] == s[1]) return true;
    if (isVowel(s[0]) && isVowel(s[1])) return true;
    if (!isVowel(s[0]) && !isVowel(s[1])) return true;
    if (hasBadDouble(s) || hasTriple(s)) return true;
    if (isTrueVowel(s[s.size() - 1])) return true;
    if (!hasVowel(s)) return true;
    return false;
}

void printAnagrams(string s) {
    sort(s.begin(), s.end());
    do
        if (!ruleViolation(s)) cout << s << endl;
    while (next_permutation(s.begin(), s.end()));
}

int main() {
    string name = "Anderson";
    
    vector<int> nameArr;
    name = toLower(name);
    nameArr = constructIntArr(name);

    for (int i = 0; i < 25; ++i) {
        nameArr = incrementVector(nameArr);
        string name = intArrToString(intArrToCharArr(nameArr));
        if (!checkForObscureLetter(name)) {
            cout << "Anagrams for " << name << " (caesar sipher +" << i+1 << "): " << endl;
            printAnagrams(name);
            cout << endl << endl;
        }
        
    }

    return 0;
}