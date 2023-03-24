#include<bits/stdc++.h>

using namespace std;

//we need some some trasection
struct TransactionData{
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;
};

//block class
class Block{
    private:
        int index;
        size_t blockHash;
        size_t previousHash;
        size_t genrateHash();

    public:
        Block(int idx, TransactionData d, size_t prevHash);

        // get original Hash
        size_t getHash();

        // get previos Hash
        size_t getPreviousHash();

        // TransactionData data
        TransactionData data;

        // validate Hash
        bool validateHash();
};

//constructer with params
Block :: Block(int idx, TransactionData d, size_t prevHash){
    index = idx;
    data = d;
    previousHash = prevHash;
    blockHash = genrateHash();
}

//private function
size_t Block :: genrateHash(){
    hash<string> hash1;
    hash<size_t> hash2;
    hash<size_t> finalhash;
    string toHash = to_string(data.amount) + data.receiverKey + data.senderKey + to_string(data.timestamp);

    return finalhash(hash1(toHash) + hash2(previousHash));
}

// public function
size_t Block :: getHash(){
    return blockHash;
}

size_t Block :: getPreviousHash(){
    return previousHash;
}

bool Block :: validateHash(){
    return genrateHash() == blockHash;
}


class Blockchain{
    private:
        Block createGensisBlock();

    public:
        //public chain
        vector<Block> chain;

        //Constructer
        Blockchain();

        //Public Function
        void addBlock(TransactionData data);
        bool isChainValid();

        //contrived Example for Demo only
        Block *getLetestBlock();
};

// Blockchain Consturcter
Blockchain :: Blockchain () {
    Block gensis = createGensisBlock();
    chain.push_back(gensis);
}

Block Blockchain :: createGensisBlock(){
    time_t current;
    TransactionData d;
    d.amount = 0;
    d.receiverKey = "none";
    d.senderKey = "none";
    d.timestamp = time(&current);

    hash<int> hash1;
    Block gensis(0, d, hash1(0));
    return gensis;
}

// only for demo
Block *Blockchain :: getLetestBlock(){
    return &chain.back();
}

void Blockchain :: addBlock(TransactionData d){
    int index = (int)chain.size()-1;
    Block newBlock(index, d, getLetestBlock()->getHash());
}

bool Blockchain :: isChainValid(){
    vector<Block> :: iterator it;
    int chainLen = (int)chain.size();

    for(it = chain.begin() ; it != chain.end() ; ++it){
        Block currentBlock = *it;
        if(!currentBlock.validateHash()){
            // Invalid 
            return false;
        }
        if(chainLen > 1){
            Block previousBlock = *(it-1);
            if(currentBlock.getPreviousHash() != previousBlock.getHash()){
                // Invalid
                return false;
            }
        }
    }
    return true;
}


int main(void){
    // Start a Block-Chain
    Blockchain Indicoin;

    // Data for first added block
    TransactionData data1;
    time_t data1Time;
    data1.amount = 1.5;
    data1.receiverKey = "Arjun";
    data1.senderKey = "Rahul";
    data1.timestamp = time(&data1Time);

    Indicoin.addBlock(data1);

    cout << "Is chain is Valid" << endl
         << Indicoin.isChainValid() << endl;
}