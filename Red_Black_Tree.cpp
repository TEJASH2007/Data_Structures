#include <bits/stdc++.h>
using namespace std;

const int OVERFLOW_EXIT = 2 ;

#define debug(...) 1
// #define debug(...) cout << __VA_ARGS__ << endl

struct Node{
    int data ;
    Node* left = nullptr;
    Node* right = nullptr;
    int color = 0;        //  0 means red , 1 = black , 2 = double black
};

Node* createNode(int data){
    Node* newNode = new Node{data};
    if(newNode == nullptr) exit(OVERFLOW_EXIT);
    return newNode;
}

int color(Node* ptr){
    if(ptr == nullptr) return 1;
    return ptr->color;
}

Node* leftRotate(Node* G){
    Node* p = G->right;
    Node* T = p->left;

    p->left = G;
    G->right = T;

    swap(p->color , G->color);
    return p;
}

Node* rightRotate(Node* G){
    Node* p = G->left;
    Node* T = p->right;

    p->right = G;
    G->left = T;

    swap(p->color , G->color);
    return p;
}

class RBTree{
    public : 
        Node* root = nullptr;
        Node* NIL = new Node{-1};
        

        RBTree(){
            NIL->color = 2;
        }

        Node* insert(int data , Node* ptr = nullptr){

            if(ptr == nullptr){
                if(root){
                    root = insert(data , root);
                    root->color = 1;
                    return root;
                }
                root = createNode(data);
                root->color = 1;
                return root;
            }

            if(ptr->data == data) return ptr;

            if(ptr->data < data){
                if(ptr->right){
                    ptr->right = insert(data , ptr->right);
                }else{
                    ptr->right = createNode(data);
                    return ptr;
                }
            }else{
                if(ptr->left){
                    ptr->left = insert(data , ptr->left);
                }else{
                    ptr->left = createNode(data);
                    return ptr;
                }
            }
            
            // LL
            if(ptr->left && color(ptr->left)==0 && color(ptr->left->left) == 0){
                debug("LL");
                if(color(ptr->right) == 0){
                    ptr->right->color = 1;
                    ptr->left->color = 1;
                    ptr->color = 0;
                    return ptr;
                }

                ptr = rightRotate(ptr);
                return ptr;
            }
            
            
            if(ptr->left && color(ptr->left)==0 && color(ptr->left->right) == 0){

                if(color(ptr->right) == 0){
                    ptr->right->color = 1;
                    ptr->left->color = 1;
                    ptr->color = 0;
                    return ptr;
                }
                
                ptr->left = leftRotate(ptr->left);
                ptr = rightRotate(ptr);
                return ptr;
            }

            // RR
            if(ptr->right && color(ptr->right)==0 && color(ptr->right->right) == 0){
                
                if(color(ptr->left) == 0){
                    ptr->right->color = 1;
                    ptr->left->color = 1;
                    ptr->color = 0;
                    return ptr;
                }

                ptr = leftRotate(ptr);
                return ptr;
            }

            // RL
            if(ptr->right && color(ptr->right)==0 && color(ptr->right->left) == 0){

                if(color(ptr->left) == 0){
                    ptr->right->color = 1;
                    ptr->left->color = 1;
                    ptr->color = 0;
                    return ptr;
                }


                ptr->right = rightRotate(ptr->right);
                ptr = leftRotate(ptr);
                return ptr;
            }

            return ptr;
        }

        void inorderTraversal(){
            
            stack<Node*> stk;
            stk.push(root);

            while(!stk.empty()){
                Node* ptr = stk.top();
                if(ptr != nullptr){
                    stk.push(ptr->left);
                }else{
                    stk.pop();
                    if(stk.empty()) break;
                    ptr = stk.top();
                    stk.pop();
                    cout<<ptr->data<<" "<<ptr->color<<endl;

                    stk.push(ptr->right);
                }
            }
        }
        
        Node* deleteNode(int key ){
            Node* ptr = root;
            Node* preptr = nullptr;
            
            while(ptr && ptr->data != key){

                preptr = ptr;
                if(key < ptr->data) ptr = ptr->left;
                else ptr = ptr->right; 

            }

            if(!ptr){
                cout<<"  Key not found ! "<<endl;
                return root;
            }
            
            if(ptr->left && ptr->right){
                Node* succ = ptr->right;
                Node* succParent = ptr;
                
                while(succ->left){
                    succParent = succ;
                    succ = succ->left;
                }

                ptr->data = succ->data;
                ptr = succ;
                preptr = succParent;

            }

            Node* child = nullptr;

            if(ptr->left){
                child = ptr->left;
            }else if(ptr->right || ptr->color == 0){
                child = ptr->right;
            }else {
                child = NIL;
            }


            if(!preptr){

                root = child;
                preptr = root;
                
            }else{
                if(preptr->left == ptr){
                    preptr->left = child;
                }else{
                    preptr->right = child;
                }
        
            }
            
            // simple case : 
            bool ok = 0;

            if(color(child) == 0){
                child->color = 1;
                ok = 1;
            }
            else if(color(ptr) == 0){
                ok = 1;
            }

            delete ptr;

            if(ok == 0) {
                bool got = 0;
                root = validate(preptr , root , got);
            }
            
            return root;
        }

        Node* validate(Node* tar , Node* ptr , bool &got){
            
            if(ptr != tar && got == 0){
                if(ptr->data < tar->data) ptr->right = validate(tar , ptr->right , got);
                else ptr->left = validate(tar , ptr->left , got);
            }else {
                got = 1;
            }

            if(color(ptr->left) == 2){
                if(color(ptr->right) == 0){
                    
                    debug("right_RED_sibling");
                    ptr = leftRotate(ptr);

                    ptr->left = validate(tar , ptr->left , got);
                    return ptr;
                }

                if(color(ptr->right->left)==1 && color(ptr->right->right)==1){// RR

                    debug("right_BB_child");
                    if(ptr->left == NIL){
                        ptr->left = nullptr;   
                    }else ptr->left->color = 1;

                    ptr->right->color = 0;
                    ptr->color += 1;

                    return ptr;

                }else if(color(ptr->right->right) == 0){   // RR 
                    debug("RR");
                    ptr = leftRotate(ptr);
                    if(ptr->left->left == NIL) ptr->left->left = nullptr;
                    else ptr->left->left->color = 1;

                    ptr->right->color = 1;
                }else{                                     // RL
                    debug("RL");
                    ptr->right = rightRotate(ptr->right);
                    ptr = leftRotate(ptr);
                    if(ptr->left->left == NIL) ptr->left->left = nullptr;
                    else ptr->left->left->color = 1;
                    ptr->right->color = 1;
                }

            }else if(color(ptr->right) == 2){
                
                if(color(ptr->left) == 0){
                    debug("Left_RED_sibling");
                    ptr = rightRotate(ptr);
                    ptr->right = validate(tar , ptr->right , got);
                    return ptr;
                }

                if(color(ptr->left->left)==1 && color(ptr->left->right)==1){
                    debug("left_BB_child");
                    if(ptr->right == NIL){
                        ptr->right = nullptr;   
                    }else ptr->right->color = 1;

                    ptr->left->color = 0;
                    ptr->color += 1;

                    return ptr;

                }else if(color(ptr->left->left) == 0){   // LL
                    debug("LL");
                    ptr = rightRotate(ptr);

                    if(ptr->right->right == NIL) ptr->right->right = nullptr;
                    else ptr->right->right->color = 1;

                    ptr->left->color = 1;
                }else{                                     // LR
                    ptr->left = leftRotate(ptr->left);
                    ptr = rightRotate(ptr);

                    if(ptr->right->right == NIL) ptr->right->right = nullptr;
                    else ptr->right->right->color = 1;

                    ptr->left->color = 1;
                    
                }

            }

            return ptr;
        }
        void printTree(Node* ptr) {
            if (ptr == nullptr) return;

            cout << "Node: " << ptr->data
                << " (" << (ptr->color == 0 ? "RED" : "BLACK") << ")";

            cout << " | Left: ";

            if (ptr->left) {
                cout << ptr->left->data << " ("
                    << (ptr->left->color == 0 ? "RED" : "BLACK") << ")";
            } else {
                cout << "NULL (BLACK)";
            }

            cout << " | Right: ";

            if (ptr->right) {
                cout << ptr->right->data << " ("
                    << (ptr->right->color == 0 ? "RED" : "BLACK") << ")";
            } else {
                cout << "NULL (BLACK)";
            }

            cout << '\n';

            printTree(ptr->left);
            printTree(ptr->right);
        }
};



int main() 
{
    vector<int> arr = {
        10, 5, 15, 1, 7, 12, 18,
        0, 2, 6, 8, 11, 13, 17, 20,
        4, 3, 9, 14, 16, 19
    };

    RBTree tree;
    for(auto &x : arr){

        tree.insert(x);
        
    }
    tree.printTree(tree.root);

    vector<int> del = {
        0, 15, 5, 20, 10, 7, 12,
        1, 18, 3, 13, 6, 17, 2, 11,
        8, 14, 16, 19, 4, 9
    };

    for(auto &x  : del){
        tree.deleteNode(x);
    }
    return 0;
}
