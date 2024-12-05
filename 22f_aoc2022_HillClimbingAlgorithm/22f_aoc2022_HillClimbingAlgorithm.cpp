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
    if (c=='S')
    {
        return magassag('a');
    }
    if (c=='E')
    {
        return magassag('z');
    }
    for (size_t i = 0; i < abc.size(); i++) {
        if (c == abc[i]) {
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

vector<vector<int>> szomszedai(int i, int j, vector<string> m) {
    vector<vector<int>> result;

    // felette: ( i-1 ; j   )
    if (0 < i && magassag(m[i - 1][j]) - magassag(m[i][j]) <= 1 )
    {
        result.push_back({ i-1, j });
    }
    // jobbra:  ( i   ; j+1 )
    if (j < m[0].size() - 1 && magassag(m[i][j+1]) - magassag(m[i][j]) <= 1)
    {
        result.push_back({ i, j+1 });
    }

    // alatta:  ( i+1 ; j   )
    if (i < m.size() - 1 && magassag(m[i + 1][j]) - magassag(m[i][j]) <= 1)
    {
        result.push_back({ i+1, j });
    }

    // balra:  ( i   ; j-1 )

    if (0 < j && magassag(m[i][j-1]) - magassag(m[i][j]) <= 1)
    {
        result.push_back({ i, j-1 });
    }

    return result;
}

vector<vector<int>> mo_keszitese(vector<vector<vector<int>>>& honnan, vector<int> end) {
    vector<vector<int>> result({ end });
    vector<int> szampar = end;

    while (honnan[szampar[0]][szampar[1]][0] != -1)
    {
        szampar = honnan[szampar[0]][szampar[1]];
        result.push_back(szampar);
    }

    return result;
}



vector<vector<int>> legrovidebb_ut(vector<string>m, vector<int> start, vector<int> end)
{
    int feher = 0;  // nem is jártunk ott
    int kek = 1;    // már felvettük a tennivalók közé
    int zold = 2;   // fel is dolgoztuk már

    vector<vector<int>> szin(m.size(),vector<int>(m[0].size(),feher)); // eleinte minden fehér

    queue<vector<int>> tennivalok;
    tennivalok.push(start); // merthogy innen indul a keresés!

    vector<vector<vector<int>>> honnan(m.size(), vector<vector<int>>(m[0].size(), {-1,-1}));  // ---------------> a piros táblázat kitöltése -1-esekkel!

    while (!tennivalok.empty())
    {
        // Soron következõ elem KIVÉTELE
        vector<int> tennivalo = tennivalok.front();
        tennivalok.pop();

        int i = tennivalo[0];
        int j = tennivalo[1];

        // Soron következõ elem FELDOLGOZÁSA

        szin[i][j] = zold;
        if (tennivalo == end)
        {
            return mo_keszitese(honnan, end);
        }

        // Szomszédok kezelése

        for (vector<int>& szomszed : szomszedai(i, j, m))
        {
            int k = szomszed[0];
            int l = szomszed[1];
            if (szin[k][l] == feher)
            {
                tennivalok.push(szomszed);
                szin[k][l] = kek;
                honnan[k][l] = tennivalo; // ---------------> a piros táblázat kitöltése!
            }
        }
    }
    return { { -1 } };
}

vector<int> helye(char betu, vector<string> m){
    for (int i = 0; i < m.size(); i++)
    {
        for (int j = 0; j < m[0].size(); j++)
        {
            if (m[i][j] == betu)
            {
                return { i,j };
            }
        }
    }
    return{ -1,-1 };
}


int main(){
    /** /
    vector<string> m = beolvas("test.txt");
    /*/
    vector<string> m = beolvas("input.txt");
    /**/

    vector<vector<int>> mo = legrovidebb_ut(m, helye('S',m ), helye('E',m ));
    
    cout << mo.size()-1 << "lépés, mégpedig:";

    for (auto& par : mo)
    {
        cout << "(" << par[0] << " ; " << par[1] << ")\n";
    }


}


