// 22f_aoc2022_HillClimbingAlgorithm.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

string abc = "abcdefghijklmnopqrstuvwxyz";

int magassag(char c) {
	for (size_t i = 0; i < abc.size(); i++){
		if (c==abc[i]){
			return i;
		}
	}
	return -1;
}

vector<string> beolvas(string fajlnev) {
    ifstream file(fajlnev);

    vector<string> eredmeny;

    string sor;
    while (getline(file, sor)) {
        eredmeny.push_back(sor);
    }

    return eredmeny;
}

vector<vector<int>> szomszedai(int i, int j, vector<string> map) {

}

int main(){
    
}
