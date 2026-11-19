#include <bits/stdc++.h>
using namespace std;

class Node{
    public : 

        vector< Node* > ptr ;
        int cnt = 0;
        int we = 0;
        int pre = 0;

        Node():ptr(26 , nullptr){}

        Node* createNode(char c){
            Node* newNode;

            try{
                newNode = new Node();
            }catch(...){
                cout<<"OverFlow Ocuured\n";
                exit(1);
            }
            
            return newNode;
        }

        Node* nextChar(char c){
            if(ptr[c-'a'] == nullptr){
                ptr[c-'a'] = createNode(c);
                ++cnt;
            }
            return ptr[c-'a'];
        }      

        void incWordEnd(){
            we += 1;
        }

        bool hasNextChar(char c){
            return ptr[c-'a'] != nullptr;
        }

        void updatePtr(char c , Node* newPtr){
            ptr[c-'a'] = newPtr;
            if(newPtr == nullptr){
                --cnt;
            }
        }
        void decWordEnd(){
            we -= 1;
        }

        bool isItEmpty(){
            return (cnt == 0) && (we == 0);
        }
        void incPreWord(){
            pre += 1;
        }
        void decPreWord(){
            pre -= 1;
        }
};

class Trie{
    Node* root;

    public :
        Trie(){
            try{
                root = new Node();
                root->incWordEnd();
            }catch(...){
                exit(1);
            }
        }
        
        void insert(string word){
            Node* ptr = root;

            for(char &c : word){
                ptr = ptr->nextChar(c);
                ptr->incPreWord();
            }

            ptr->incWordEnd();
        }

        bool search(string word){
            Node* ptr = root;

            for(char &c : word){
                if(!ptr->hasNextChar(c)){
                    return false;
                }

                ptr = ptr->nextChar(c);
            }

            return ptr->we > 0;
        }
        Node* deleteWord(string s){
            if(!search(s)) return root;

            root->updatePtr(s[0] , deletion(s , 1 , root->nextChar(s[0])) ) ;
            return root;
        }

        Node* deletion(string s , int idx  , Node* ptr ){
            if(s.size() == 0) return root;
            
            ptr->decPreWord();
            if(s.size() == idx){
                ptr->decWordEnd();

                if ( ptr->isItEmpty() ) {
                    delete ptr;
                    ptr = nullptr;
                }

                return ptr;
            }

            if(ptr->hasNextChar(s[idx])){

                ptr->updatePtr( s[idx] , deletion( s , idx + 1 , ptr->nextChar( s[idx] )) );

                if(ptr->isItEmpty()){
                    delete ptr;
                    ptr = nullptr;
                }
            }

            return ptr;
        }

        bool startsWith(string word){
            Node* ptr = root;

            for(char &c : word){
                if(! ptr->hasNextChar(c) ) return false;
                ptr = ptr->nextChar(c);
            }

            return 1;
        }
};
