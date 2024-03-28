#include <bits/stdc++.h>
using namespace std;
//先找有沒有完全的substr
bool isLonger(const string &a, string &b)
{
    return a.size() > b.size();
}
void lps_func(string txt, vector<int> &Lps)
{
    Lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < txt.length())
    {
        if (txt[i] == txt[len])
        {
            len++;
            Lps[i] = len;
            i++;
            continue;
        }
        else
        {
            if (len == 0)
            {
                Lps[i] = 0;
                i++;
                continue;
            }
            else
            {
                len = Lps[len - 1];
                continue;
            }
        }
    }
}
bool KMP(string &pattern, string &text)
{
    int txtLen = text.length();
    int patLen = pattern.length();
    vector<int> Lps(patLen);

    lps_func(pattern, Lps);

    int i = 0, j = 0;
    while (i < txtLen)
    {
        if (pattern[j] == text[i])
        {
            i++;
            j++;
        }
        if (j == patLen)
        {
            return true;
        }
        else if (i < txtLen && pattern[j] != text[i])
        {
            if (j == 0)
                i++;
            else
                j = Lps[j - 1];
        }
    }
    return false;
}
int stringCompare(string &a, string &b)
{
    string l = b + '#' + a;
    vector<int> table(l.size(), 0);
    for (int i = 1; i < l.size(); ++i)
    {
        int j = table[i - 1];
        while (j > 0 && l[i] != l[j])
            j = table[j - 1];
        table[i] = (j += l[i] == l[j]);
    }
    return table[l.size()-1];
}
int main()
{
    int n;
    cin >> n;
    vector<string> inputList(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> inputList[i];
    //按長度大到小sort
    sort(inputList.begin() + 1, inputList.end(), isLonger);
    for (int i = 1; i <= n; ++i)
    {
        if (inputList[i] == "#")
            continue;        
        for (int j = i + 1; j <= n; ++j)
        {
            if (KMP(inputList[j], inputList[i])) // to be optimized
                inputList[j] = "#";
        }
    }
    sort(inputList.begin() + 1, inputList.end()); // # is prior
    int index = 1;
    while (inputList[index] == "#")
        index++;
    while (index < n)
    {
        int maxLen = 0;
        int len = 0;
        int head = 0, tail = 0;
        for (int i = index; i < n; ++i)
        {
            for (int j = i + 1; j <= n; ++j)
            {
                len = stringCompare(inputList[i], inputList[j]);
                if (len > maxLen)
                {
                    maxLen = len;
                    head = i;
                    tail = j;
                }
                len = stringCompare(inputList[j], inputList[i]);
                if (len > maxLen)
                {
                    maxLen = len;
                    head = j;
                    tail = i;
                }
            }
        }
        if (head == 0 && tail == 0)
        {
            // concate by dic_order and output
            string output = "";
            for (int i = index; i <= n; ++i)
            {
                output += inputList[i];
            }
            cout << output << '\n';
            break;
        }
        else
        {
            string temp = inputList[head].substr(0, inputList[head].size() - maxLen) + inputList[tail];
            inputList[head] = temp;
            inputList[tail] = "#";
            sort(inputList.begin() + 1, inputList.end());
            ++index;
        }
    }
    if (index == n)
        cout << inputList[index] << '\n';
    return 0;
}