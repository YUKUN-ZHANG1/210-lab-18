// COMSC-210 | Lab 18: Movie Reviews | Yukun Zhang
// IDE used: Visual Studio Code

#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct ReviewNode {
    float rating;
    string comment;
    ReviewNode *next;
};

// Function to output all reviews
void outputReviews(ReviewNode *head){
    if(!head){
        cout<<"No reviews available.\n";
        return;
    }
    ReviewNode *current = head;
    int count = 1;
    float totalRating = 0;
    while(current){
        cout<<"> Review #" << count++ << ": " << current->rating << ": " << current->comment << endl;
        totalRating += current->rating;
        current = current->next;
    }
    float average = totalRating / (count - 1);
    cout<<"> Average: "<<average<<endl;
}

// Function to add a node at the head of the linked list
void addAtHead(ReviewNode *&head, float rating, const string &comment){
    ReviewNode *newNode = new ReviewNode{rating, comment, nullptr};
    newNode->next = head;
    head = newNode;
}

// Function to add a node at the tail of the linked list
void addAtTail(ReviewNode *&head, float rating, const string &comment){
    ReviewNode *newNode = new ReviewNode{rating, comment, nullptr};
    if(!head){
        head = newNode;
    }else{
        ReviewNode *current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to get the user's choice of linked list method (head or tail)
int getLinkedListChoice(){
    int choice;
    do{
        cout<<"Which linked list method should we use?\n";
        cout<<"    [1] New nodes are added at the head of the linked list\n";
        cout<<"    [2] New nodes are added at the tail of the linked list\n";
        cout<<"Choice: ";
        cin>>choice;
        if(cin.fail()||(choice != 1 && choice != 2)){
            cout<<"Invalid input. Please enter 1 or 2.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            break;
        }
    }while(true);
    return choice;
}

// Function to get the user's input for a review (rating and comment)
void getReviewInput(float &rating, string &comment){
    do{
        cout<<"Enter review rating 0-5: ";
        cin>>rating;
        if(cin.fail()||rating < 0||rating > 5){
            cout<<"Invalid input. Please enter a rating between 0 and 5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }else{
            break;
        }
    }while(true);
    cin.ignore();
    cout<<"Enter review comments: ";
    getline(cin, comment);
}

// Function to ask if the user wants to enter another review
bool askForAnotherReview(){
    char addMore;
    do{
        cout<<"Enter another review? Y/N: ";
        cin>>addMore;
        cin.ignore();
        if(tolower(addMore) == 'y'||tolower(addMore) == 'n'){
            break;
        }else{
            cout<<"Invalid input. Please enter 'Y' or 'N'.\n";
        }
    }while(true);
    return tolower(addMore) == 'y';
}

int main(){
    ReviewNode *head = nullptr;
    int choice = getLinkedListChoice();

    do{
        float rating;
        string comment;
        getReviewInput(rating, comment);
        // Add the review to the list
        if(choice == 1){
            addAtHead(head, rating, comment);
        }else{
            addAtTail(head, rating, comment);
        }

    }while(askForAnotherReview());
    cout<<"Outputting all reviews:\n";
    outputReviews(head);
    // Clean up the memory (delete linked list)
    ReviewNode *current = head;
    while(current){
        ReviewNode *next = current->next;
        delete current;
        current = next;
    }

    return 0;
}
