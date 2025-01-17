#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;


// Function to get the top N frequent words from a word count map

vector<pair<string,double>>topFrequentWords(const unordered_map<string,double>& wordCount,int topN = 100){
    vector<pair<string,double>>wordFreq(wordCount.begin(),wordCount.end());

    // Sort the words frequency vector in descending order

    sort(wordFreq.begin(),wordFreq.end(),[](const pair<string, double>& a,const pair<string,double>& b){
        return a.second>b.second;
    });

    // Get the top N frequent words

    if (wordFreq.size() > topN){
        wordFreq.resize(topN);
    }

    return wordFreq;
}


// Function to get the totalWords in a file

int totalWords(const string& file){
    ifstream Book(file);
    if (!Book.is_open()){
        cout <<"Error opening file: "<<file<< endl;
        return 0;
    }

    unordered_set<string> stopWords = {"A", "AN", "THE", "AND", "OF", "IN"};

    string word;
    int total = 0;

    while (Book>>word){

        // Convert word to uppercase
        
        transform(word.begin(),word.end(),word.begin(),::toupper);

        // Remove punctuation

        word.erase(remove_if(word.begin(),word.end(),::ispunct),word.end());

        // Check if word is a stop word

        if (stopWords.find(word)==stopWords.end()){
            total++;
        }
    }

    Book.close();
    return total;
}


// Function to count the words in a file

void countWords(const string& file,unordered_map<string,double>& wordCount,int& totalWords){
    unordered_set<string> stopWords = {"A", "AN", "THE", "AND", "OF", "IN"};
    string word;
    totalWords = 0;

    ifstream Book(file);
    if (!Book.is_open()){
        cout <<"Error opening file: "<<file<< endl;
        return;
    }

    while (Book >> word){

        // Convert word to uppercase

        transform(word.begin(),word.end(),word.begin(),::toupper);

        // Remove punctuation

        word.erase(remove_if(word.begin(),word.end(),::ispunct),word.end());

        // Check if word is a stop word

        if (stopWords.find(word)==stopWords.end()){
            wordCount[word]++;
            totalWords++;
        }
    }

    Book.close();
}

double calculateSimilarityIndex(const unordered_map<string,double>& wordCount1,int totalWords1,const unordered_map<string,double>& wordCount2,int totalWords2) {
    double similarityIndex=0.0;

    for (const auto& wc : wordCount1){
        if (wordCount2.find(wc.first)!=wordCount2.end()){
            double normalizedFreq1=wc.second/totalWords1;
            double normalizedFreq2=wordCount2.at(wc.first)/totalWords2;
            similarityIndex+=normalizedFreq1+normalizedFreq2;
        }
    }

    return similarityIndex;
}


//Function to report top ten similar pairs

void reportTopTenSimilarPairs(const vector<vector<double>>& similarityMatrix,const vector<string>& files){
    vector<pair<string,string>>similarPairs;
    for (int i=0;i<files.size();i++){
        for (int j=i+1;j<files.size();j++){
            similarPairs.push_back({files[i],files[j]});
        }
    }

    sort(similarPairs.begin(),similarPairs.end(),[&](const pair<string,string>& a,const pair<string,string>& b){
        return similarityMatrix[distance(files.begin(),find(files.begin(),files.end(),a.first))][distance(files.begin(),find(files.begin(),files.end(),a.second))]>
        similarityMatrix[distance(files.begin(),find(files.begin(),files.end(),b.first))][distance(files.begin(),find(files.begin(),files.end(),b.second))];
    });
    
    cout<<"                           Top 10 Similar Pairs"<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    cout<<"|            Book 1               |            Book 2                 | Similarity Index |"<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    for (int i=0;i<10;i++){           
        cout<<similarPairs[i].first<<"  |  "<<similarPairs[i].second<<" | "<<similarityMatrix[distance(files.begin(),find(files.begin(),
        files.end(),similarPairs[i].first))][distance(files.begin(),find(files.begin(),files.end(),similarPairs[i].second))]<<endl;
    }
    cout<<"------------------------------------------------------------------------------------------"<<endl;
}

int main(){
    // List of all files

    vector<string> files ={
        "Cats by Moncrif.txt","Foxes Book of Martyrs Part 1.txt","Foxes Book of Martyrs Part 2.txt","Foxes Book of Martyrs Part 3.txt",
        "Foxes Book of Martyrs Part 4.txt","Foxes Book of Martyrs Part 5.txt","Foxes Book of Martyrs Part 6.txt",
        "Gerards Herbal Vol. 1.txt","Gerards Herbal Vol. 2.txt","Gerard's Herbal Vol. 3.txt","Gerards Herbal Vol.4.txt",
        "Gil Blas.txt","Gossip in a Library.txt","Hudibras.txt","King of the Beggars.txt","Knocknagow.txt",
        "Les Chats par Moncrif.txt","Lives and Anecdotes of Misers.txt","Love and Madness - Herbert Croft.txt",
        "Memoirs of Laetitia Pilkington V 1.txt","Memoirs of Laetitia Pilkington V 2.txt","Memoirs of Laetitia Pilkington V 3.txt",
        "Memoirs of Mrs Margaret Leeson - Peg Plunkett.txt","Monro his Expedition.txt","Mrs Beetons Book of Household Management.txt",
        "Out of the Hurly-Burly.txt", "Percys Reliques.txt","Pompey The Little.txt","Radical Pamphlets from the English Civil War.txt",
        "Scepsis Scientifica.txt","The Anatomy of Melancholy Part 1.txt","The Anatomy of Melancholy Part 2.txt",
        "The Anatomy of Melancholy Part 3.txt","The Complete Cony-catching.txt","The Consolation of Philosophy.txt",
        "The Covent Garden Calendar.txt","The Devil on Two Sticks.txt","The Diary of a Lover of Literature.txt",
        "The History Of Ireland - Geoffrey Keating.txt","The History of the Human Heart.txt","The Ingoldsby Legends.txt",
        "The Life of Beau Nash.txt","The Life of John Buncle by Thomas Amory.txt","The Life of King Richard III.txt",
        "The Life of Pico della Mirandola.txt","The Martyrdom of Man.txt","The Masterpiece of Aristotle.txt",
        "The Memoirs of Count Boruwlaski.txt","The Metamorphosis of Ajax.txt","The Newgate Calendar - Supplement 3.txt",
        "The Newgate Calendar Supplement 2.txt","The Newgate Calendar Supplement.txt","The Newgate Calendar V 1.txt",
        "The Newgate Calendar V 2.txt","The Newgate Calendar V 3.txt","The Newgate Calendar V 4.txt",
        "The Newgate Calendar V 5.txt","The Newgate Calendar V 6.txt","The Poems of Ossian.txt",
        "The Poetical Works of John Skelton.txt","The Protestant Reformation.txt","The Real Story of John Carteret Pilkington.txt",
        "The Rowley Poems.txt","The SIlver Fox.txt"
    };

    // Calculate word counts and total words for each file

    vector<unordered_map<string,double>> wordCounts(files.size());
    vector<int>totalWordsVec(files.size(),0);

    for (int i=0;i<files.size();i++){
        countWords(files[i],wordCounts[i],totalWordsVec[i]);
    }

    // Calculate similarity matrix
    
    vector<vector<double>>similarityMatrix(files.size(),vector<double>(files.size(),0.0));

    for (int i=0;i<files.size();i++){
        for (int j=i+1;j<files.size();j++){
            similarityMatrix[i][j]=calculateSimilarityIndex(wordCounts[i],totalWordsVec[i],wordCounts[j],totalWordsVec[j]);
            similarityMatrix[j][i]=similarityMatrix[i][j];
        }
    }

    // Report top ten similar pairs

    reportTopTenSimilarPairs(similarityMatrix,files);

    return 0;
}
