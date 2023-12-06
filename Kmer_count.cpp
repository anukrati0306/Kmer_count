#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <chrono> 
#include <algorithm>
#include <cctype>

using namespace std;
unordered_map<string, int> countKmers(const string& seq, int k) {
   unordered_map<string, int> kmerCount;
    string upperSeq = seq;
    transform(upperSeq.begin(), upperSeq.end(), upperSeq.begin(), ::toupper);
    //transform(seq.begin(), seq.end(), seq.begin(), ::toupper);
    for (int i = 0; i <= upperSeq.length() - k; ++i) {
        string kmer = upperSeq.substr(i, k);
        kmerCount[kmer]++;
    }

    return kmerCount;
}

string MostFrequentKmer(const unordered_map<string, int>& kmerCount) {
    string frequentKmer;
    int max_count = 0;

    for  (const auto& entry : kmerCount) {
        if (entry.second > max_count) {
            frequentKmer = entry.first;
            max_count = entry.second ;
        }
    }

    return frequentKmer;
}


int main() {
    ifstream file("/home/ccmb/imperfect_repeats/human_ref/T2T_humanref/T2T_chr1.fa");
    if (!file.is_open()) {
        cerr << "not open" << endl;
        return 1;
    }
    string line;
    string seq = "";
    while (getline(file, line)) {
        //to skip the line with >
        if (line[0] == '>')
        continue;

        seq += line;
    }

    file.close();

    int seq_len = seq.length(); 
    int k = 10;  
    auto start = chrono::high_resolution_clock::now();

    unordered_map<string, int> kmerCount = countKmers(seq, k);

    
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "For K-mer size = " << k << "\n";
    for (const auto& entry : kmerCount) {
        //cout << entry.first << ":" << entry.second << "\n";

    }
    
    string frequentKmer = MostFrequentKmer(kmerCount);
    cout << "Most frequent K-mer :" << frequentKmer << "(count: " << kmerCount[frequentKmer] << ") \n"; 

    
    cout << "For DNA seq of length : " << seq_len << " And K-mer of Size :" << "\t" << k << "\t" << "Time taken: " << duration.count() << " microseconds\n";

    return 0;
}
