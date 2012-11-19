//Binary Search Tree Program
//Group 13
//Sam Reed, Craig Ashworth, Thomas Biddle

/*
  This program implements a class Person which stores instances of the first and
  last name of each person along with their phone number.  It also implements a class
  Book which is where the binary search tree is created that contains the people in the
  phone book.  The program implements a UserInterface where the user can add a person into
  the phone book, delete a person in the phone book, find a person in the phone book, change
  a number of a person in the phone book, display the people in the phone book and quit when
  finished.  It will save the phone book into a text file.

*/

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
// create class BinarySearchTree
class BinarySearchTree
{
    private:
        struct bookNode
        {
           bookNode* left;
           bookNode* right;
           string info;
           string lastname;
           string firstname;
           string number;
           void printnumber();

        };
        bookNode* root;

    public:
        BinarySearchTree()
        {
           root = NULL;
        }

        bool isEmpty() const { return root==NULL; }
        void print_inorder();
        void inorder(bookNode*);
        void add(string, string,  string);
        void remove(string);
        void find(string);
        void change(string);
        void saveToText();
        string traverseTree(bookNode*);
};
// end BinarySearchTree


/*
  Function:
            The add function will allow the user to add both a first and last name along with a
            phone number.  The user can do this mulitple times as the program will continue to
            return to the UserInterface.

  Parameters:
              string x - refers to the first name of the person in the phone book
              string y - refers to the last name of the person in the phone book
              string z - refers to the phone number of the person in the phone book

  Output:
          The first and last name the user entered is stored in the phone book.
*/
// Smaller elements go left
// larger elements go right
void BinarySearchTree::add(string x, string y, string z)
{
    string space = ", ";
    string dash = " - ";
    bookNode* t = new bookNode;
    bookNode* parent;
    t->info = x + space + y + dash + z;
    t->left = NULL;
    t->right = NULL;
    t->firstname = y;
    parent = NULL;
    t->lastname = x;
    t->number = z;

    // is this a new tree?
    if(isEmpty()) root = t;
    else
    {
        //Note: ALL addions are as leaf nodes
        bookNode* curr;
        curr = root;
        // Find the Node's parent
        while(curr)
        {
            parent = curr;
            if(t->info > curr->info) curr = curr->right;
            else curr = curr->left;
        }

        if(t->info < parent->info)
           parent->left = t;
        else
           parent->right = t;
    }
}
/*
  Function:
            The remove function will allow the user to remove one of the people in the
            phone book.  The user can do this multiple times as the program will continue
            to return to the UserInterface.

  Parameters:
             string d - refers to the last name of the person in the phone book the user would
             like to remove

  Output:
         return - The name the user entered is removed.
*/

void BinarySearchTree::remove(string d){

//Bootstrap condition
    bool found = false;
    if(isEmpty())
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }

    //Locate the element

    bookNode* curr;
    bookNode* parent;
    curr = root;

    while(curr != NULL)
    {
         if(curr->lastname == d)
         {
            found = true;
            break;
         }
         else
         {
             parent = curr;
             if(d>curr->lastname) curr = curr->right;
             else curr = curr->left;
         }
    }
        if(!found){
                cout<<" Cannot find any info! "<<endl;
                return;
        }

    if((curr->left == NULL && curr->right != NULL)|| (curr->left != NULL&& curr->right == NULL)){
                if(curr->left == NULL && curr->right != NULL) {
                        if(curr == root){
                                root = curr->right;
                                delete curr;
                                return;
                        }
                        if(parent->left == curr)        {
                                parent->left = curr->right;
                                delete curr;
                        }
                        else {
                                parent->right = curr->right;
                                delete curr;
                        }
                }
                else {
                        if(curr == root){
                                root = curr->left;
                                delete curr;
                                return;
                        }
                        if(parent->left == curr){
                                parent->left = curr->left;
                                delete curr;
                        }
                        else{
                                parent->right = curr->left;
                                delete curr;
                        }
                }
                return;
        }

        if( curr->left == NULL && curr->right == NULL){
                if(curr == root){
                        root = NULL;
                        return;
                }
                if(parent->left == curr)
                        parent->left = NULL;
                else
                        parent->right = NULL;
                delete curr;
                return;
        }
        if (curr->left != NULL && curr->right != NULL){
                bookNode* chkr;
                chkr = curr->right;
                if((chkr->left == NULL) && (chkr->right == NULL))       {
                        curr = chkr;
                        delete chkr;
                        curr->right = NULL;
                }
                else {

                        if((curr->right)->left != NULL){
                                bookNode* lcurr;
                                bookNode* lcurrp;
                                lcurrp = curr->right;
                                lcurr = (curr->right)->left;
                                while(lcurr->left != NULL){
                                        lcurrp = lcurr;
                                        lcurr = lcurr->left;
                                }
                                curr->info = lcurr->info;
                                delete lcurr;
                                lcurrp->left = NULL;
                        }
                        else    {
                                bookNode* tmp;
                                tmp = curr->right;
                                curr->info = tmp->info;
                                curr->right = tmp->right;
                                delete tmp;
                        }
                }
                return;
        }

}
/*
  Function:
            The print_inorder function prints the people in the phone book alphabetically
            according to the last name.

  Parameters:
             There are no parameters.

  Output:
         inorder is called to check to see the alphabetic order of the phone book of last
         names and then first names if last names are the same.
*/
void BinarySearchTree::print_inorder()
{
  inorder(root);
}
/*
  Function:
           The inorder function is used to list the people in the book alphabetically testing
           the last names and then the first names if last names are the same.

  Paramters:
             bookNode* p - refers to a pointer pointing the nodes in the BinarySearchTree

  Output:
         Stores the people in the phonebook alphabetically according to their last name
*/
void BinarySearchTree::inorder(bookNode* p)
{
    if(p != NULL)
    {
        if(p->left) inorder(p->left);
        //cout<<" "<<p->info<<" " << endl;
        cout<<" "<< p->lastname << ", "<< p->firstname << " - " << p->number<<" " << endl;
        if(p->right) inorder(p->right);
    }
    else return;
}
/*
  Function:
            The find function locates a person in the phone book according to the last name
            the user entered.

  Parameters:
              string l - refers to the last name of the person in the phone book

  Output:
         return: says the Tree has no nodes, empty tree.

         In the while loop if the name is found it will locate the last name and the phone
         number corresponding to the name and print it out.

         return: says Can't find any info! if the name is not found
*/

void BinarySearchTree::find(string l){

        bool found = false;
        if(isEmpty()) {
                cout<<" Tree has no nodes, empty tree. "<<endl;
                return;
        }

        bookNode* curr;
        bookNode* parent;
        curr = root;

        while(curr != NULL)     {
                if(curr->lastname == l )        {
                        found = true;
                        curr->printnumber();
                        break;
                }
                else    {
                        parent = curr;

                        if(l > curr->info)
                                curr = curr->right;
                        else curr = curr->left;
                }
        }
        if(!found)
        {
                cout<<" Can't find any info! "<<endl;
                return;
        }
}

/*
  Function:
            The printnumber function will display the last name of the person in
            the phone book along with the phone number.

  Paramters:
            There are no parameters.

  Output:
         cout: it will print the last name of the person in the phone book along with their
               phone number.
*/
void BinarySearchTree::bookNode::printnumber(){
        cout<< endl << lastname << "'s phone number is " << number << endl;
}
/*
  Function:
            The change function will allow the user to be able to go in the phone book and change
            an already existing person's phone number.  It will locate the old number and set it
            to equal the new number the user enters.

  Parameters:
             string c - refers to the last name of the person in the phone book
             string d - refers to the first name of the person in the phone book

  Output:
         return: it will return Tree has no nodes, empty tree if the name is not found

         The while loop will locate the first and last name of the person the user wants to change
         and set the old number to equal the new number.

         return: it will return Can't fina any info! if if the name is not found.
*/

void BinarySearchTree::change(string c){

    bool found = false;
        if(isEmpty()) {
                cout<<" Tree has no nodes, empty tree. "<<endl;
                return;
     }

     bookNode* curr;
         bookNode* parent;
         curr = root;

         while(curr != NULL)     {
                if(curr->lastname == c )        {
                        found = true;
                            string newnum;
        cout << "Please enter the new phone number: " << endl;
        cin >> newnum;
        curr->number = newnum;
    break;
                }
                else    {
                        parent = curr;

                        if(c > curr->info)
                                curr = curr->right;
                        else curr = curr->left;
                }
        }
        if(!found)
        {
                cout<<" Can't find any info! "<<endl;
                return;
        }


}


string BinarySearchTree::traverseTree(bookNode* curr) {
         if(curr != NULL)
         {
          if(curr->left) traverseTree(curr->left);
             string writeToFile = (curr->lastname + ":" + curr->firstname + ":" + curr->number);
             return writeToFile;
          if(curr->right) traverseTree(curr->right);

         }
         else return NULL;
}


/*
// Doesn't work fully
void BinarySearchTree::saveToText() {
fstream myStream;
myStream.open("myfile43.txt",ios::out);

        if(isEmpty()) {
                cout<<" Tree has no nodes, empty tree. "<<endl;
                return;
     }

     bookNode* curr;
         bookNode* parent;
         curr = root;
         string newnum;

         string writeToFile2 = traverseTree(root);
         //if (writeToFile2 != NULL) {
          myStream << writeToFile2;
   //}
  // else continue;

    myStream.close();
    return;
}
*/

// Create class UserInterface
class UserInterface {
public:
        void displayUI();

};
/*
  Function:
           The UserInterface function will create a menu for the user to easily access each
           of the functions to add a person to the phone book, print the phone book, find a
           person in the phone book, change a person's number in the phone book, delete a person
           from the phone book and exit the program when done. The switch cases hide the menu and
           allows the user to only enter the choice they selected from the menu.  When done, the menu
           comes back and they can repeat and/or choose another option.
*/
void UserInterface::displayUI()
{

    BinarySearchTree b;
    int ch;
    string last, first, number;
    int keepOpen = 0;
        while (keepOpen == 0)
    {
       cout<<endl<<endl;
       cout<<" Binary Search Tree Operations "<<endl;
       cout<<" ----------------------------- "<<endl;
       cout<<" 1. Addition/Creation "<<endl;
       cout<<" 2. Print Phone Book "<<endl;
       cout<<" 3. Find "<<endl;
       cout<<" 4. Change "<<endl;
       cout<<" 5. Delete "<<endl;
       cout<<" 6. Exit "<<endl;
       cout<< endl << " Enter your choice : ";
       cin>>ch;
       while (1 <= ch >= 6) {
       cin>>ch;
       }
       switch(ch)
       {
           case 1 : cout<<"PLease enter the last name: ";
                    cin>>last;
                    cout<<"PLease enter the first name: ";
                    cin>>first;
                    cout<<"PLease enter the phone number: ";
                    cin>>number;
                    b.add(last, first, number);
                    break;
           case 2 : cout<<endl;
                    cout<<" Phone Book "<<endl;
                    cout<<" -------------------"<<endl;
                    b.print_inorder();
                    break;
           case 3 : cout<< "Please enter the last name to be found: " << endl;
                    cin >> last;
                    b.find(last);
                    cout<<" -------------------"<<endl;
                    break;
           case 4 : cout<<endl;
                    cout<<"Please enter the name that you want to change: "<<endl;
                    cin >> last;
                    b.change(last);
                    break;
           case 5 : cout<<"PLease enter the last name of the person to be removed : ";
                    cin>>last;
                    b.remove(last);
                    break;
           case 6 :
                    keepOpen = 1;
                    // Save to file.
                       break;

       }
    }
}
// the main calls the UserInterface
int main() {

    UserInterface ui;
        ui.displayUI();

        return 0;

}
