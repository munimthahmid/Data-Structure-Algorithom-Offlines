#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
vector<bool> isPrime(N + 1, true);
string keyGenerator()
{
    string s = "abcdefghijklmnopqrstuvwxyz";
    int size = std::rand() % (10 - 5 + 1) + 5;
    string key;
    for (int i = 0; i < size; i++)
    {
        int index = std::rand() % (s.size() - 1 - 0 + 1) + 0;
        key.push_back(s[index]);
    }
    return key;
}
void sieve()
{
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= N; i++)
    {
        if (isPrime[i])
        {
            for (int j = 2 * i; j <= N; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}
int nearestPrime(int n)
{
    int prime = -1;
    while (true)
    {
        if (isPrime[n])
        {
            prime = n;
            break;
        }
        else
            n++;
    }
}
class node
{
public:
    string key;
    int val;
    node *next;
};

int Hash1(string str, int M)
{
    unsigned long hash = 5381;
    for (char c : str)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % M;
}
int Hash2(string str, int M)
{
    unsigned long long hash = 14695981039346656037UL;
    for (char c : str)
    {
        hash ^= c;
        hash *= 1099511628211UL;
    }
    return hash % M;
}
int auxHash(string s, int M)
{
    int hash = 7, prime = 19;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash * prime + s[i]) % M;
    }
    return hash % M == 0 ? 1 : hash % M;
}

class Separate_Chaining
{
public:
    int tableSize;
    vector<node *> hashTable;
    int N;
    int M;
    int collissionCount = 0;
    int probeCount = 0;
    function<int(string, int)> hashFunction;

    Separate_Chaining(int N, function<int(string, int)> f)
    {
        M = nearestPrime(N);
        hashTable.resize(M);
        for (int i = 0; i < M; i++)
        {
            hashTable[i] = NULL;
        }
        hashFunction = f;
    }
    node *createNode(string key, int val)
    {
        node *ptr = new node;
        ptr->val = val;
        ptr->next = NULL;
        ptr->key = key;
        return ptr;
    }

    bool insert(string s)
    {
        int index = hashFunction(s, M);
        node *cur = hashTable[index];
        if (cur == NULL)
        {
            node *newnode = createNode(s, index);
            hashTable[index] = newnode;
            return true;
        }
        while (cur->next != NULL)
        {
            if (cur->key == s)
                return false;

            cur = cur->next;
        }
        node *newnode = createNode(s, index);
        cur->next = newnode;
        if (hashTable[index] != NULL)
            collissionCount++;
    }
    int find(string s)
    {
        int index = hashFunction(s, M);
        node *cur = hashTable[index];
        int prbcnt = 0;
        while (cur != NULL)
        {
            prbcnt++;
            if (cur->key == s)
            {
                probeCount += prbcnt;
                return cur->val;
            }

            cur = cur->next;
        }
        return -1; // If not found
    }
    int erase(string s)
    {
        int index = hashFunction(s, M);
        node *cur = hashTable[index];
        node *prev = NULL;
        node *next = cur->next;
        while (cur != NULL)
        {
            if (cur->key == s)
            {
                int val = cur->val;
                if (prev == NULL)
                    hashTable[index] = cur->next;
                else
                {
                    prev->next = cur->next;
                    delete cur;
                }
                return val;
            }
            prev = cur;
            cur = cur->next;
        }
        return -1; // no value found
    }
};
class Double_Hashing
{
public:
    int N, M;
    vector<node *> hashTable;
    vector<bool> isDeleted;
    function<int(string, int)> hashFunction;
    int collissionCount = 0;
    int probeCount = 0;
    Double_Hashing(int N, function<int(string, int)> f)
    {
        M = nearestPrime(N);
        hashTable.resize(M);
        isDeleted.resize(M, false);
        for (int i = 0; i < M; i++)
        {
            hashTable[i] = NULL;
        }
        hashFunction = f;
    }
    node *createNode(string key, int val)
    {
        node *ptr = new node;
        ptr->val = val;
        ptr->next = NULL;
        ptr->key = key;
        return ptr;
    }
    bool insert(string key)
    {
        int index1 = hashFunction(key, M);
        int index2 = auxHash(key, M);

        if (hashTable[index1] == NULL)
        {
            node *ptr = createNode(key, index1);
            hashTable[index1] = ptr;
            return true;
        }
        else
        {
            for (int i = 1; i < M; i++)
            {
                int index = (index1 + i * index2) % M;
                if (hashTable[index] == NULL)
                {
                    node *ptr = createNode(key, index);
                    hashTable[index] = ptr;
                    collissionCount += i; // Increase collision count by the number of probes
                    return true;
                }
            }
            return false; // No empty slot found
        }
    }

    bool erase(string key)
    {
        int index1 = hashFunction(key, M);
        int index2 = auxHash(key, M);
        for (int i = 0; i < M; i++)
        {
            int index = (index1 + i * index2) % M;
            if (hashTable[index] == NULL)
                return false;
            else if (hashTable[index]->key == key)
            {
                isDeleted[index] = true;
                return true;
            }
        }
        return false;
    }
    int find(string key)
    {
        int index1 = hashFunction(key, M);
        int index2 = auxHash(key, M);
        int prbcnt = 0;
        for (int i = 0; i < M; i++)
        {

            int index = (index1 + i * index2) % M;
            if (isDeleted[index])
                continue;
            if (hashTable[index]->key == key)
            {
                prbcnt++;
                probeCount += prbcnt;
                return index;
            }
            prbcnt++;
        }

        return -1;
    }
};
class Custom_Hashing
{
public:
    int N, M;
    vector<node *> hashTable;
    vector<bool> isDeleted;
    function<int(string, int)> hashFunction;
    int collissionCount = 0;
    int probeCount = 0;
    int C1 = 5;
    int C2 = 10;
    Custom_Hashing(int N, function<int(string, int)> f)
    {
        M = nearestPrime(N);
        hashTable.resize(M);
        isDeleted.resize(M, false);
        for (int i = 0; i < M; i++)
        {
            hashTable[i] = NULL;
        }
        hashFunction = f;
    }
    node *createNode(string key, int val)
    {
        node *ptr = new node;
        ptr->val = val;
        ptr->next = NULL;
        ptr->key = key;
        return ptr;
    }
    bool insert(string key)
    {
        int index1 = hashFunction(key, M);
        int index2 = auxHash(key, M);

        if (hashTable[index1] == NULL)
        {
            node *ptr = createNode(key, index1);
            hashTable[index1] = ptr;
            return true;
        }
        else
        {
            for (int i = 1; i < M; i++)
            {
                int index = (index1 + C1 * i * index2 + C2 * i * i) % M;
                if (hashTable[index] == NULL)
                {
                    node *ptr = createNode(key, index);
                    hashTable[index] = ptr;
                    collissionCount += i; // Increase collision count by the number of probes
                    return true;
                }
            }
            return false; // No empty slot found
        }
    }

    bool erase(string key)
    {
        int index1 = hashFunction(key, M);
        int index2 = auxHash(key, M);
        for (int i = 0; i < M; i++)
        {
            int index = (index1 + C1 * i * index2 + C2 * i * i) % M;
            if (hashTable[index] == NULL)
                return false;
            else if (hashTable[index]->key == key)
            {
                isDeleted[index] = true;
                return true;
            }
        }
        return false;
    }
    int find(string key)
    {
        int index1 = hashFunction(key, M);
        int index2 = auxHash(key, M);
        int prbcnt = 0;
        for (int i = 0; i < M; i++)
        {

            int index = (index1 + C1 * i * index2 + C2 * i * i) % M;
            if (isDeleted[index])
                continue;
            if (hashTable[index]->key == key)
            {
                prbcnt++;
                probeCount += prbcnt;

                return index;
            }
            prbcnt++;
        }

        return -1;
    }
};
int main()
{
    sieve();
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    vector<string> words;
    for (int i = 0; i < 10000; i++)
    {
        string s = keyGenerator();
        words.push_back(s);
    }
    vector<string> keysToSearch;
    for (int i = 0; i < 1000; i++)
    {
        int index = std::rand() % (words.size() - 1 - 0 + 1) + 0;
        keysToSearch.push_back(words[index]);
    }
    vector<int> tableSize = {5000, 10000, 20000};
    for (int i = 0; i < tableSize.size(); i++)
    {
        Separate_Chaining hash1(tableSize[i], Hash1);
        Separate_Chaining hash2(tableSize[i], Hash2);
        Double_Hashing dhash1(tableSize[i], Hash1);
        Double_Hashing dhash2(tableSize[i], Hash2);
        Custom_Hashing chash1(tableSize[i], Hash1);
        Custom_Hashing chash2(tableSize[i], Hash2);

        for (int i = 0; i < words.size(); i++)
        {
            hash1.insert(words[i]);
            hash2.insert(words[i]);
            dhash1.insert(words[i]);
            dhash2.insert(words[i]);
            chash1.insert(words[i]);
            chash2.insert(words[i]);
        }
        for (int i = 0; i < keysToSearch.size(); i++)
        {
            hash1.find(keysToSearch[i]);
            hash2.find(keysToSearch[i]);
            dhash1.find(keysToSearch[i]);
            dhash2.find(keysToSearch[i]);
            chash1.find(keysToSearch[i]);
            chash2.find(keysToSearch[i]);
        }
        cout << "For table size: " << hash1.M << endl;
        cout << "Separate Chaining: " << endl;
        cout << "Hash 1 : "
             << "Collission Count: " << hash1.collissionCount << " "
             << "Average Probe:" << hash1.probeCount / 1000.0 << endl;
        cout << "Hash 2 "
             << "Collission Count: " << hash2.collissionCount << " "
             << "Average Probe: " << hash2.probeCount / 1000.0 << endl;
        cout << "Double Hashing: " << endl;
        cout << "Hash 1: "
             << "Collission Count: " << dhash1.collissionCount << " "
             << "Average Probe: " << dhash1.probeCount / 1000.0 << endl;
        cout << "Hash 2: "
             << "Collission Count: " << dhash2.collissionCount << " "
             << "Average Probe: " << dhash2.probeCount / 1000.0 << endl;
        cout << "Custom Probing: " << endl;
        cout << "Hash 1 :"
             << "Collission Count: " << chash1.collissionCount << " "
             << "Average Probe: " << chash1.probeCount / 1000.0 << endl;
        cout << "Hash 2: "
             << "Collission Count: " << chash2.collissionCount << " "
             << "Average Probe:" << chash2.probeCount / 1000.0 << endl;
    }
}