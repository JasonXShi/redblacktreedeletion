/*
 *	Red Black Tree Deletion
 *	Written by Jason Shi
 *	Allows the user to create a red black tree and delete, add, and print out the tree.
 *	
 *
 */

#include "Node.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;
//declare methods
bool search(Node* root, int num);
void rotateLeft(Node *&root, Node  *pt);
void rotateRight(Node *&root, Node *pt);
void case1(Node *&root, Node *n);
void case2(Node *&root, Node *n);
void case3(Node *&root, Node *n);
void case4(Node *&root, Node *n);
void case5(Node *&root, Node *n);
void case6(Node *&root, Node *n);
void replaceNode(Node * , Node *);
void oneChildDelete(Node *&root, Node *n);
//call this function to fix the tree after every insertion
void fixTree(Node* &root, Node* &pt){
	//makes parent and grandparent of newly inserted node (helps with checking uncle and if parent is left or right)
	Node *parent_pt = NULL;
    	Node *grand_parent_pt = NULL;
    while ((pt != root) && (pt->getColor() != 2) &&
           (pt->getParent()->getColor() == 1))
    {
	    //set variables
        parent_pt = pt->getParent();
        grand_parent_pt = pt->getParent()->getParent();
        //if the parent is the left of grandparent
        if (parent_pt == grand_parent_pt->getLeft())
        {
            Node *uncle_pt = grand_parent_pt->getRight();
            //the uncle is red - just recolor some nodes, no rotation is needed
            if (uncle_pt != NULL && uncle_pt->getColor() == 1)
            {
                grand_parent_pt->setColor(1);
                parent_pt->setColor(2);
                uncle_pt->setColor(2);
                pt = grand_parent_pt;
            }
 	
            else{
          
                //  if the new node is the right of parent rotate the tree left
                if (pt == parent_pt->getRight())
                {
                    rotateLeft(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
                rotateRight(root, grand_parent_pt);
		int parentcolor = parent_pt->getColor();
		int grandcolor = grand_parent_pt->getColor();
		parent_pt->setColor(grandcolor);
		grand_parent_pt->setColor(parentcolor);
                
                pt = parent_pt;
            }
        }
 
        //the parent is right of grandparent
        else
        {
            Node *uncle_pt = grand_parent_pt->getLeft();
 
           // if the uncle is read then recolor
            if ((uncle_pt != NULL) && (uncle_pt->getColor() == 1))
            {
                grand_parent_pt->setColor(1);
                parent_pt->setColor(2);
                uncle_pt->setColor(2);
                pt = grand_parent_pt;
            }
            else {
                //the new node is left of its parent
                if (pt == parent_pt->getLeft())
                {
                    rotateRight(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->getParent();
                }
                 rotateLeft(root, grand_parent_pt);
		int parentcolor = parent_pt->getColor();
		int grandcolor = grand_parent_pt->getColor();
		parent_pt->setColor(grandcolor);
		grand_parent_pt->setColor(parentcolor);
                pt = parent_pt;
            }
        }
    }
 //set the root to be black (because the root must always be black in the end)
    root->setColor(2);

}
bool search(Node* root, int num){
    if(root!=NULL){
        if(root->getContent() == num){
            return true;
        }else if(root->getContent() > num){
            if(search(root->getLeft(),num)){
                return true;
            } 
        }else{
            if(search(root->getRight(), num)){
                return true;
            }
        }
    }
        return false;


}
//recursive function that returns the head (usually same as input)
Node* addNode(Node* head, Node* pt){
	if(head==NULL){
		//the root of the new tree is the new node to be added
		return pt;
	}else if(head->getContent()>=pt->getContent()){
                        head->setLeft(addNode(head->getLeft(), pt));
			//set parent of the new node
			head->getLeft()->setParent(head);
	}else if(head->getContent()<pt->getContent()){
			head->setRight(addNode(head->getRight(), pt));
			//set parent of the new node
			head->getRight()->setParent(head);
		}
		return head;
}

void rotateLeft(Node *&root, Node *pt)
{
	//makes a right node of the new node for easier rotation
    Node *pt_right = pt->getRight();
    pt->setRight(pt_right->getLeft());
 	//checks if the node to be set actually exist before proceding with rotation
    if (pt->getRight() != NULL){
        pt->getRight()->setParent(pt);
    }
    pt_right->setParent(pt->getParent());
    if (pt->getParent() == NULL){
        root = pt_right;
    }else if (pt == pt->getParent()->getLeft()){
        pt->getParent()->setLeft(pt_right);
}
    else{
        pt->getParent()->setRight(pt_right);
    }
    pt_right->setLeft(pt);
    pt->setParent(pt_right);
}
//same thing but just the other way
void rotateRight(Node *&root, Node *pt)
{
    Node *pt_left = pt->getLeft();
    pt->setLeft(pt_left->getRight());
    if (pt->getLeft() != NULL){
        pt->getLeft()->setParent(pt);
    }
    pt_left->setParent(pt->getParent());
 
    if (pt->getParent() == NULL){
        root = pt_left;
    }
    else if (pt == pt->getParent()->getLeft()){
        pt->getParent()->setLeft(pt_left);
    }
    else{
        pt->getParent()->setRight(pt_left);
    }
    pt_left->setRight(pt);
    pt->setParent( pt_left);
}
/*
void rotate_left(Node *&root, Node* n){
    Node* nnew = n->getRight();
    n->setRight(nn->getLeft());
    nnew->setLeft(n);
    nnew->setParent(n->getParent());
    n->setParent(nnew);
    //other stuff later

}

void rotate_right(){
    Node* nnew = n->getLeft();
    n->setLeft(nnew->getRight());
    nnew->setRight(n);
    nnew->setParent(n->getParent());
    n->setParent(nnew);
    //other stuff later

}*/
//prints the tree spacing to make things look clear
void printTree(Node* head, int space){
    if (head == NULL)
    	return;
    space += 10;
    printTree(head->getRight(), space);
    cout << '\n';
    for (int i = 10; i < space; i++)
        cout << " ";
	
    if(head->getColor()==1){
	    cout <<"\033[1;31m" << head->getContent()<< "\033[0m";
    }else{
    	cout << "\033[30;47m" << head->getContent() << "\33[0m";
    }
    printTree(head->getLeft(), space);
}
//returns the minimum node - used in deletion (not right now though, just when this was a bst)
Node* minValueNode(Node* node){
	Node* current = node;
	while(current->getLeft()!=NULL){
		current = current->getLeft();
	}
	return current;
}
//this deletion works but doesnt adjust the tree (this was for bst)
Node* deleteNode(Node* head, int number){
  	if(head->getContent()> number){
    		head->setLeft(deleteNode(head->getLeft(), number));
 	 }else if(number > head->getContent()){
    		head->setRight(deleteNode(head->getRight(), number));
	}else{
		if(head->getLeft() == NULL){
			Node* temp = head->getRight();
            if(temp->getColor()==1 || head->getColor()==1){
                temp->setColor(2);
            }
            free(head);
			return temp;
		}else if(head->getRight() == NULL){
			Node* temp = head->getLeft();
			if(temp->getColor()==1 || head->getColor()==1){
                temp->setColor(2);
            }
            free(head);
			return temp;
		}
		Node* temp = minValueNode(head->getRight());
        
        head->setContent(temp->getContent());
		head->setRight(deleteNode(head->getRight(), temp->getContent())); 
        if(temp->getColor()==1 || head->getColor()==1){
            head->setColor(2);
        }
        
	}
    return head;
}
Node* sibling(Node* n){
    Node* p = n->getParent();
    if(p==NULL){
        return NULL;
    }else if(n == p->getLeft()){
        return p->getRight();
    }else if(n == p->getRight()){
        return p->getLeft();
    }

}

void replaceNode(Node *n, Node *child){
    
	
	if(n->getParent()!=NULL){
		cout << "to be replaced parent not NULL";
		cout << n->getParent()->getContent();
		/*{
		
				  child->setParent(n->getParent());
	

    		if( n == n->getParent()->getLeft()){
	    		n->getParent()->setLeft(child);
    		}else{
			n->getParent()->setRight(child);
		}*/
	}else{
		cout << "to be replaced parent is NULL" ;	
	}
}

/*void oneChildDelete(Node *&root, Node *n){
    Node* child = NULL;
    if(n->getLeft() == NULL){
        child = n->getRight();
    }else{
        child = n->getLeft();
    }
    replaceNode(n, child);
    if(n->getColor() == 2){
        if(child->getColor() == 1){
            child->setColor(2);
        }else{
            case1(root, child);
        }
    }
    free(n);
}*/
void case1(Node *&root, Node *n){
 	cout << endl;
	cout << "case 1";
       	if(n->getParent()!=NULL){
    case2(root,n);

 }
}
void case2(Node *&root, Node *n){
    cout << "case 2";
	Node* s = sibling(n);
    if(s->getColor() == 1){
        n->getParent()->setColor(1);
        s->setColor(2);
        if( n == n->getParent()->getLeft()){
            rotateLeft(root, n->getParent());
        }else{
            rotateRight(root, n->getParent());
        }         
    }   
   case3(root, n); 
}
void case3(Node *&root, Node *n){
    cout << "case 3" << endl;
	Node* s = sibling(n);
    	if((n->getParent()->getColor()==2) && (s->getColor() == 2) && (s->getLeft()==NULL || s->getLeft()->getColor() == 2) && (s->getRight()== NULL || s->getRight()->getColor() == 2)){
        	s->setColor(1);
        	case1(root, n->getParent());
	
    }else{
       case4(root, n);
    
    }
}
void case4(Node *&root, Node *n){
	cout << "case 4" <<endl;
    Node* s = sibling(n);
	cout << n->getContent();
	cout << n->getParent();
    cout << s->getColor() << endl;
    cout << s->getLeft()<< endl;
    cout << s->getRight() <<endl;
   // if(s->getLeft()!=NULL && s->getRight()!=NULL){
	if((n->getParent()->getColor() == 1) && (s->getColor() == 2) && (s->getLeft()==NULL || s->getLeft()->getColor()==2) && (s->getRight() == NULL || s->getRight()->getColor()==2)){
		s->setColor(1);
        n->getParent()->setColor(2);
       }else{
        case5(root, n);
    
    }
    	
    
   
    
}
void case5(Node *&root, Node *n){
	cout << "case 5" <<endl;
    Node * s = sibling(n);
    if(s->getColor() == 2){
        if((n==n->getParent()->getLeft()) && (s->getRight()==NULL || s->getRight()->getColor() ==2) && (s->getLeft()!=NULL && s->getLeft()->getColor() == 1)){
            s->setColor(1);
            s->getLeft()->setColor(2);
            rotateRight(root, s);
        }else if((n == n->getParent()->getRight()) && (s->getLeft()==NULL || s->getLeft()->getColor() == 2) && (s->getRight()!=NULL && s->getRight()->getColor()==1)){
            s->setColor(1);
            s->getRight()->setColor(2);
            rotateLeft(root, s);
        
        }
        
    }   
    case6(root, n);
}

void case6(Node *&root, Node *n){
	cout << "case 6" << endl;
    Node* s = sibling(n);
    s->setColor(n->getParent()->getColor());
    n->getParent()->setColor(2);
    if(n==n->getParent()->getLeft()){
        s->getRight()->setColor(2);
        rotateLeft(root, n->getParent());
        
    
    }else{
        s->getLeft()->setColor(2);
        rotateRight(root, n->getParent());
    }
}
Node* findNode(Node* root, int num){
   	cout << "root is:" << root->getContent(); 
        if(root->getContent() == num){
            return root;
        }else if(root->getContent() > num){
            return findNode(root->getLeft(),num);
                
            
        }else{
            return findNode(root->getRight(), num);
                
            
        }
    
        return NULL;

}

void delete_node(Node *&root, int num){
	
	Node* toDelete = findNode(root, num);
	
	if(toDelete==NULL){
		return;	
	}
	if (toDelete->getLeft()!=NULL  && toDelete->getRight()!=NULL ) { // node to delete has two children
        	cout << "2 children";
		// use one or no child deletion on successor after value of successor copied into node to delete
     	 	Node* successor = toDelete->getRight(); // find successor as leftmost node of right subtree
   	   	while (successor->getLeft()!=NULL){ 
			successor = successor->getLeft();
		}
       		toDelete->setContent(successor->getContent()); // copy just the value of the successor
       		toDelete = successor; // set successor to be deleted with one or no child methods that follow
   	 }
	if (toDelete->getColor()==1) { // must have no children 
        	//delete toDelete->getRight(); 
        	cout << "color is red";
		if(toDelete->getParent()!=NULL){
		if(toDelete->getParent()->getLeft() == toDelete){
			toDelete->getParent()->setLeft(NULL);
		}else{
			toDelete->getParent()->setRight(NULL);
		}
		}else{
			//root = NULL;
		}
   	 } else if (toDelete->getLeft()!=NULL) { // black node with red left child
        	cout << "left is not null";
		 toDelete->getLeft()->setColor(2); // red child turns black and takes node to delete's position
        	replaceNode(toDelete, toDelete->getLeft());
    	} else if (toDelete->getRight()!=NULL ) { // black node with red right child
        	cout << "right is not null";
		
		toDelete->getRight()->setColor(2);
      		replaceNode(toDelete, toDelete->getRight());

    	} else { // black node with no children
        	cout << "black w no children";
		//Node* child = toDelete->getLeft();
        	//delete toDelete->getRight(); // since moving left leaf node into position this is no longer used
        	//replaceNode(toDelete, child);
        	case1(root, toDelete); // child has reduced black depth, call repair
        	if(toDelete->getParent()->getLeft() == toDelete){
			toDelete->getParent()->setLeft(NULL);
		}else{
			toDelete->getParent()->setRight(NULL);
		}
			

	
    }return;
}

int main(){
	//some unused code for bst is commented out
//get input
	/* 
	char* text = new char[400];
	cout << "Enter input as file or in console? (Type 'FILE' or 'CONSOLE')" << endl;
	cin.getline(text, 50);
	int count = 0;
	int * stor = new int[1000];
	if(strcmp(text, "FILE")==0){
		//gets filename
		cout << "Enter the filename: (Ex. 'text.txt') (Make sure to seperate the numbers just by spaces.)" << endl;
		char* filename = new char[50];
		cin.getline(filename, 50);
		ifstream inFile;
		inFile.open(filename);
		int a = 0;
		//puts all into the storage of numbers starting from 1
		while(inFile >> a){
			stor[count] = a;
			count++;
		}

	}else if(strcmp(text, "CONSOLE")==0){
		//gets input
		cout << "Enter the numbers you want to add to the tree, seperated by commas and spaces(Ex. 1, 2, 3)" << endl;
		char* input2  = new char[400];		
		cin.getline(input2, 400);
		char* token = strtok(input2, ", ");
		
		while(token != NULL){
			//changes it to int and puts it in the array starting from 1
			stor[count] = atoi(token);
			//deletes token
			token = strtok(NULL, ", ");
			count ++;
		}
		
	}
	Node* head = NULL;
	for(int i =0; i< count; i++){
		Node* pt = new Node();
		pt->setContent(stor[i]);
		head = addNode(head, pt);
		
		fixTree(head, pt);
	}	
	*/
	//makes a head so I can call the addNode function
	Node* head = NULL;
	while(1){
		cout << '\n' <<"Enter a command:" << endl;
		cout << "'ADD' to add a number." << endl;
		cout << "'PRINT' to print the tree." << endl; 
		cout << "'READ' to read in numbers from a file." << endl;
		cout << "'DELETE' to delete a number." << endl;
		cout << "'SEARCH' to search for a value." << endl;
        cout << "Or 'EXIT' to exit the program" << endl;
		char* command = new char[10];
		cin.getline(command, 10);
		int number = 0;
		if(strcmp(command, "ADD") == 0){
			//allows adding 1 number to the tree
			cout << "Enter the number you want to add: " <<endl;
			cin >> number;
			cin.get();
			//makes a new node with the number to be added
			Node* pt = new Node();
			pt->setContent(number);
			//if this is the first time (creating the tree) this function still works because a NULL pointer for head was made
			head = addNode(head, pt);
			//calls the method to fix the tree after every insertion
			fixTree(head, pt);
		}else if(strcmp(command, "PRINT") == 0){
			
            if(head == NULL){
                    cout << "There is nothing in the tree" << endl;
                    }else{
                printTree(head, 0);
            }
		}else if(strcmp(command, "DELETE") == 0){
			cout << "Enter the number you want to delete: " << endl;
			cin >> number;
			
			cin.get();
			cout <<"after getting";
			cout << "before calling";
			delete_node(head, number);
		/*	if(head->getLeft() == NULL & head->getRight() == NULL){
                head->setContent(NULL);
            }else{
                 head = deleteNode(head, number);
            }*/

		}
		else if(strcmp(command, "READ") == 0){
		
		int count = 0;
		int * stor = new int[1000];
		//gets filename
		cout << "Enter the filename: (Ex. 'text.txt') (Make sure to seperate the numbers just by commas.)" << endl;
		char* filename = new char[50];
		cin.getline(filename, 50);
		ifstream inFile;
		inFile.open(filename);
		//puts all into the storage of numbers starting from 1
		char* input2  = new char[400];		
		inFile.getline(input2, 400);
		char* token = strtok(input2, ",");
		
		while(token != NULL){
			//changes it to int and puts it in the array starting from 1
			stor[count] = atoi(token);
			//deletes token
			token = strtok(NULL, ", ");
			count ++;
		}
			//for each item in the storage call the addNode and then fixTree, one by one
		for(int i =0; i< count; i++){
			Node* pt = new Node();
			pt->setContent(stor[i]);
			head = addNode(head, pt);
			fixTree(head, pt);
		}
	
        }else if(strcmp(command, "SEARCH") == 0){
            
            cout << "Enter the value you want to search for: " << endl;
            int searchNum = 0;
            cin >> searchNum;
            cin.get();
            if(search(head, searchNum)){
                cout << "The tree contains the number."<< endl;
                
            }else{
                cout << "The tree does not contain the number."<< endl;
            }

        }
        else if(strcmp(command, "EXIT") == 0){
			exit(0);
		}
	
	}	

}
