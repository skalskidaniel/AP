#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'crosswordPuzzle' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 *  1. STRING_ARRAY crossword
 *  2. STRING words
 */

bool canPlaceHorizontal(int x, int y, const vector<string> &crossword, const string &word)
{
    int n = crossword[0].size();
    if (y + word.size() > n)
        return false; // Out of bounds

    for (int i = 0; i < word.size(); ++i)
    {
        if (crossword[x][y + i] != '-' && crossword[x][y + i] != word[i])
        {
            return false; // Conflict
        }
    }
    return true;
}

bool canPlaceVertical(int x, int y, const vector<string> &crossword, const string &word)
{
    int n = crossword.size();
    if (x + word.size() > n)
        return false; // Out of bounds

    for (int i = 0; i < word.size(); ++i)
    {
        if (crossword[x + i][y] != '-' && crossword[x + i][y] != word[i])
        {
            return false; // Conflict
        }
    }
    return true;
}

vector<string> placeHorizontal(int x, int y, const vector<string> &crossword, const string &word)
{
    vector<string> result = crossword;
    for (int i = 0; i < word.size(); ++i)
    {
        result[x][y + i] = word[i];
    }
    return result;
}

vector<string> placeVertical(int x, int y, const vector<string> &crossword, const string &word)
{
    vector<string> result = crossword;
    for (int i = 0; i < word.size(); ++i)
    {
        result[x + i][y] = word[i];
    }
    return result;
}

bool solve(vector<string> &crossword, const vector<string> &words, int wordIndex)
{
    if (wordIndex == words.size())
        return true; // All words are placed

    string word = words[wordIndex];
    int n = crossword.size();

    // Try placing horizontally
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - word.size() + 1; ++j)
        {
            if (canPlaceHorizontal(i, j, crossword, word))
            {
                vector<string> temp = placeHorizontal(i, j, crossword, word);
                if (solve(temp, words, wordIndex + 1))
                {
                    crossword = temp; // Update crossword
                    return true;
                }
            }
        }
    }

    // Try placing vertically
    for (int i = 0; i < n - word.size() + 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (canPlaceVertical(i, j, crossword, word))
            {
                vector<string> temp = placeVertical(i, j, crossword, word);
                if (solve(temp, words, wordIndex + 1))
                {
                    crossword = temp; // Update crossword
                    return true;
                }
            }
        }
    }

    return false; // Unable to place current word
}

vector<string> crosswordPuzzle(vector<string> crossword, const string &words)
{
    istringstream iss(words);
    string current_word;
    vector<string> wordsList;
    while (getline(iss, current_word, ';'))
    {
        wordsList.push_back(current_word);
    }

    if (solve(crossword, wordsList, 0))
    {
        return crossword; // If puzzle is solved, return the filled crossword
    }
    else
    {
        cerr << "Error: Unable to fill the crossword puzzle" << endl;
        return {}; // Otherwise, return an empty crossword
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    vector<string> crossword(10);

    for (int i = 0; i < 10; i++)
    {
        string crossword_item;
        getline(cin, crossword_item);

        crossword[i] = crossword_item;
    }

    string words;
    getline(cin, words);

    vector<string> result = crosswordPuzzle(crossword, words);

    for (size_t i = 0; i < result.size(); i++)
    {
        fout << result[i];

        if (i != result.size() - 1)
        {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str)
{
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str)
{
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end());

    return s;
}
