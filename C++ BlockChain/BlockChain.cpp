#include<bits/stdc++.h>

using namespace std;

//we need some some trasection
struct TransactionData{
    double amount;
    string senderKey;
    string receiverKey;
    time_t timestamp;

    TransactionData(){};

    TransactionData(double amt, string sender, string receiver, time_t time){
        amount = amt;
        senderKey = sender;
        receiverKey = receiver;
        timestamp = time;
    }
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

        // getting index
        int getIndex();

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

int Block :: getIndex(){
    return index;
}

bool Block :: validateHash(){
    return genrateHash() == blockHash;
}


class Blockchain{
    private:
        Block createGensisBlock();
        vector<Block> chain;

    public:
        //public chain
        vector<Block> getChain();
        //Constructer
        Blockchain();

        //Public Function
        void addBlock(TransactionData data);
        bool isChainValid();

        //contrived Example for Demo only
        Block *getLetestBlock();

        void printChain();
};

// Blockchain Consturcter
Blockchain :: Blockchain () {
    Block gensis = createGensisBlock();
    chain.push_back(gensis);
}

Block Blockchain :: createGensisBlock(){
    time_t current;
    TransactionData d(0,"None", "None", time(&current));

    Block gensis(0, d, 0);
    return gensis;
}

// only for demo
Block *Blockchain :: getLetestBlock(){
    return &chain.back();
}

void Blockchain :: addBlock(TransactionData d){
    int index = (int)chain.size();
    size_t previousHash = (int)chain.size() > 0 ? getLetestBlock()->getHash() : 0;
    Block newBlock(index, d, previousHash);
    chain.push_back(newBlock);
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

void Blockchain :: printChain(){
    vector<Block> :: iterator it;
    
    for(it = chain.begin() ; it != chain.end() ; ++it){
        Block currentBlock = *it;
        printf("\n\t\t|\t|\n================= BLOCK ======================");
        printf("\nIndex : %d",currentBlock.getIndex());
        printf("\nAmount: %f",currentBlock.data.amount);
        printf("\nSenderKey: %s",currentBlock.data.senderKey.c_str());
        printf("\nReceiverKey: %s",currentBlock.data.receiverKey.c_str());
        printf("\nTimestamp: %ld",currentBlock.data.timestamp);
        printf("\nHash: %zu",currentBlock.getHash());
        printf("\nPrevious hash: %zu",currentBlock.getPreviousHash());
        printf("\nIs Block Valid: %d",currentBlock.validateHash());
        printf("\n\n================= CHAIN ======================\n\t\t|\t|\n");
    }
}


int main(void){
    // Start a Block-Chain
    Blockchain Indicoin;

    // Data for first added block
    // TransactionData data1;
    // time_t data1Time;
    // data1.amount = 1.5;
    // data1.receiverKey = "Arjun";
    // data1.senderKey = "Rahul";
    // data1.timestamp = time(&data1Time);

    // Indicoin.addBlock(data1);

    // time_t data2Time;
    // TransactionData data2(2.5, "Rahul", "Arjun", time(&data2Time));
    // Indicoin.addBlock(data2);

    // time_t data3Time;
    // TransactionData data3(4.5, "Virat", "Arjun", time(&data2Time));
    // Indicoin.addBlock(data3);

    // Indicoin.printChain();

    while(1){
        system("clear");
        cout<<"\tWELCOME IN BLOCK-CHAIN TECHNOLOGY\t"<<endl;
        cout<<"01. FOR INSERTING DATA"<<endl;
        cout<<"02. FOR PRINTING CHAIN"<<endl;
        int n;
        cin >> n;
        system("clear");
        
        switch(n){
            case 1 :{
                cout<<"======== Entring data in Block ========="<<endl;
                string sender;
                cout << "Enter Sender Name: ";
                cin >> sender;

                string receiver;
                cout << "Enter Receiver Name: ";
                cin >> receiver;

                double amount;
                cout << "Enter Amount: $ ";
                cin >> amount;

                time_t dateTime;
                TransactionData data(amount, sender, receiver, time(&dateTime));
                Indicoin.addBlock(data);
            }
            break;
            

            case 2 :{
                cout<<"======== These are all block data of BLOCK - CHAIN ========"<<endl;
                Indicoin.printChain();
                    }
            break;

            default:
                continue;
            break;
        }

        cout<< endl << "Do you want to continue (Y/N)" << endl;
        if(getchar() == 'N' || getchar() == 'n'){
            system("clear");
            break;
        }
    }
    return 0;
}
