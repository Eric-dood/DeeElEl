//COMSC-210 | Lab 22 | Eric-Giulio Hedes
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

//Global constants
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

//Start of the DoublyLinkedList class
class DoublyLinkedList {
//Private values & functions
private:
    //This will be used for searching nodes through a linked list
    struct Node {
        //'data' will be used for values
        int data;
        //Set up prev & next
        Node* prev;
        Node* next;
        //Also set up a constructor for the node
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    //Set up head & tail nodes
    Node* head;
    Node* tail;

//Public functions
public:
    //Constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    //Define push_back()
    void push_back(int value) {
        //Set up a newNode that will be used for inserting in the tail node
        Node* newNode = new Node(value);
        if (!tail)  //If there's no tail, set both the head & tail as the newNode
            head = tail = newNode;
        else { //Otherwise insert the new value & set it as the tail
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    //Define push_front()
    void push_front(int value) {
        //Set up a newNode that will be used for inserting in the head node
        Node* newNode = new Node(value);
        if (!head)  //If there's no head, set both the head & tail as the newNode
            head = tail = newNode;
        else { //Otherwise insert the new value & set it as the head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    //Define insert_after()
    void insert_after(int value, int position) {
        //If the position is lower than 0, print out a error message & exit the function
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        //Define newNode
        Node* newNode = new Node(value);
        //If the head doesn't exist, set up newNode as the head & tail
        if (!head) {
            head = tail = newNode;
            //Also return
            return;
        }

        //Set up a temporary node called temp, which'll start from the head
        Node* temp = head;
        //Loop through the linked list until a certain position is found
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        //If the selected position is beyond the list size, print out an error message & exit
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode; //Delete the newNode for memory safety
            return;
        }

        //Set newNode's next variable equal to temp's next variable
        newNode->next = temp->next;
        //Set newNode's previous variable as the temp variable
        newNode->prev = temp;

        //If the temp->next value exceeded the list, set the prev value of temp->next as the newNode
        if (temp->next) temp->next->prev = newNode;
        else tail = newNode; //Otherwise insert it at the end

        //Set up temp->next as the newNode
        temp->next = newNode;
    }

    //Define delete_val()
    void delete_val(int value) {
        //If the list is empty, return
        if (!head) return;

        //Set up a temporary Node starting from the head
        Node* temp = head;
        //Loop through the entire list until a certain value is found
        while (temp && temp->data != value)
            temp = temp->next;

        //If the value isn't found, return
        if (!temp)
        {
            cout << "Value " << value << " not found." << endl;
            return;
        }

        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next; //Deleting the head

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev; //Deleting the tail

        //Delete the temp node for memory safety
        delete temp;
    }

    //Define delete_pos()
    void delete_pos(int position) {
        //If the position is lower than 0, prompt an error message and exit
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        //Set up a temporary node starting from the head
        Node* temp = head;

        //If the list is empty, return
        if (!head) return;
        
        //If the head is equal to the tail, set both as nullptr
        if (head == tail) {
            head = tail = nullptr;
            return;
        }

        //Search through the entire list until at a certain position
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        //If the position exceeded list size, print out an error message & exit the function
        if (!temp) {
            cout << "Position exceeds list size. Node not deleted.\n";
            //Delete temp for memory safety
            delete temp;
            return;
        }
        
        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next; // Deleting the head

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev; // Deleting the tail

        //Delete temp for memory safety
        delete temp;
    }

    //Define pop_front()
    void pop_front() {
        //If the list is empty, exit the function
        if (!head) return;
        //Set up temp as the head
        Node* temp = head;
        //If the head is equal to the tail, set both as nullptr
        if (head == tail)
            head = tail = nullptr;
        else { //Otherwise delete the head as usual
            head = temp->next;
            temp->prev = nullptr;
        }
        delete temp;
    }

    //Define pop_back()
    void pop_back() {
        //If the list is empty, exit the function
        if (!tail) return;
        //Set up temp as the tail
        Node* temp = tail;
        //If the head is equal to the tail, set both as nullptr
        if (tail == head)
            tail = head = nullptr;
        else { //Otherwise delete the tail as usual
            tail = temp->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    //Define print()
    void print() {
        //Set the current node as the head
        Node* current = head;
        //If it doesn't exist, return
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        //Loop through the current node list
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    //Define print_reverse()
    void print_reverse() {
        //Set the current node as the tail
        Node* current = tail;
        //If it doesn't exist, return
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        //Loop through the current node list
        while (current) {
            cout << current->data << " "; //Print out the data
            current = current->prev; //Go to the previous element
        }
        //Leave in extra space
        cout << endl;
    }

    //Destructor
    ~DoublyLinkedList() {
        //This deletes the entire list.
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main()
{
    //Random seed generator
    srand(time(0));
    //Set up the DoublyLinkedList object
    DoublyLinkedList list;
    //Set up a randomized size
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    //Do a randomized list
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    
    //Print the list
    cout << "List forward: ";
    list.print();

    //Reverse print the list
    cout << "List backward: ";
    list.print_reverse();

    //Insert node 45 at position 6 in the list by using insert_after()
    cout << "Inserting node 46 at position 6: ";
    list.insert_after(46, 6);
    list.print();

    //Delete node 45 at the list by using delete_val()
    cout << "Deleting value 45: ";
    list.delete_val(45);
    list.print();

    //Insert node 122 at the tail by using push_back()
    cout << "Inserting node 122 at tail: ";
    list.push_back(122);
    list.print();

    //Insert node 253 at the head by using push_front()
    cout << "Inserting node 253 at head: ";
    list.push_front(253);
    list.print();

    //Delete position 4 by using delete_pos()
    cout << "Deleting at position 4: ";
    list.delete_pos(4);
    list.print();
    
    //Use pop_front() to delete the head
    cout << "Deleting the head: ";
    list.pop_front();
    list.print();

    //Use pop_back() to delete the tail
    cout << "Deleting the tail: ";
    list.pop_back();
    list.print();

    //Use the destructor to delete the entire list
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
