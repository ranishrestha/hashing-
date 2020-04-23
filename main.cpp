#include <iostream>
#include<fstream>
using namespace std;

class HTreeNode
{
    public:
    string data;
    int count;
    HTreeNode *next;
   
   public:HTreeNode(string data1, int count1, HTreeNode *next1)
    {
        data = data1;
        count = count1;
        next = next1;
    }
    void printNode (HTreeNode* node, ofstream &outFile)
    {
        outFile << "( " <<node->data <<", " << node->count <<", "<< node->next->data <<")->" << endl;  
    }
};

 class HashTable
{
    private:
    int BucketSize;
   
    HTreeNode* HashTableAry[29];

    public:HashTable()
    {
     BucketSize = 29;
       
        
    }

    public: void createHashAry()
    {
        
        for (int i = 0; i < BucketSize; i++)
        { 
            HTreeNode *newNode = new HTreeNode ("dummy",0,NULL);
            HashTableAry[i]=newNode;
        }
        


    }

    int doIt (string x)
    {
        unsigned int val = 1;
        for (int i =0; i< x.length(); i++)
        {
            val = val*32 + (int)x[i];
        }
        return val%BucketSize;
        
    }

    HTreeNode* findSpot (HTreeNode *listHead, HTreeNode *newNode)
   {
       HTreeNode *spot = listHead;
       while(spot->next!= NULL && spot->next->data.compare(newNode -> data)<0)
       spot = spot->next;
       if(spot->next != nullptr && spot->next->data == newNode->data)
       {
           spot->next->count++;
           spot = NULL;
       }
       return spot;
 
   }

   void listInsert(HTreeNode* listHead1, HTreeNode* newNode1)
   {
       HTreeNode* spot1 = findSpot(listHead1, newNode1);
        if(spot1!=NULL)
        {
            newNode1->next = spot1->next;
            spot1->next = newNode1;
        }
           
       
       
   }

    void printList (int index, ofstream &outFile)
    {
        outFile << "HashTableAry[" << index << "]->";
        HTreeNode* printSpot = HashTableAry[index];
        while (printSpot->next !=NULL)
        {
            printSpot->printNode(printSpot, outFile);
            printSpot = printSpot->next;
        }
        
    }
    void printHashTable(ofstream &outFile1)
    {
        int index = 0;
        while (index < BucketSize)
        {
            printList(index,outFile1);
            index++;
        }

    }

    void storeDataIntoHashTable(ifstream &infile, ofstream &outFile2)
    {
        string data;
        while(infile >> data)
        {
            HTreeNode* newNode = new HTreeNode (data,1,NULL);
            int index = doIt(data);
            HTreeNode* listHead = this->HashTableAry[index];
            listInsert(listHead,newNode);
            printList(index,outFile2);//debug
         }  
           

    }
};

    int main(int argc, char* argv[])
    {
       
        ifstream inFile;
        inFile.open(argv[1]);
        ofstream outFile1;
        outFile1.open(argv[2]);
        ofstream outFile2;
        outFile2.open(argv[3]);
        HashTable *myTable = new HashTable();
        myTable->createHashAry();
        myTable ->storeDataIntoHashTable(inFile,outFile2);
        myTable->printHashTable(outFile1);
        inFile.close();
        outFile1.close();
        outFile2.close();
    }

    
