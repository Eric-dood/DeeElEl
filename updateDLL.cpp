//COMSC-210 | Lab 22 | Eric-Giulio Hedes
#include <iostream>
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
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next; // Deleting the head

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev; // Deleting the tail

        delete temp;
    }

    //Define delete_pos()
    void delete_pos(int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* temp = head;

        if (!head) return; //Empty list
        
        if (head == tail) {
            head = tail = nullptr;
            return;
        }

        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not deleted.\n";
            delete temp;
            return;
        }
        
        if (temp->prev) temp->prev->next = temp->next;
        else head = temp->next; // Deleting the head

        if (temp->next) temp->next->prev = temp->prev;
        else tail = temp->prev; // Deleting the tail

        delete temp;
    }

    //Define pop_front()
    void pop_front() {
        if (!head) return; // Empty list
        Node* temp = head;
        if (head == tail)
            head = tail = nullptr;
        else {
            head = temp->next;
            temp->prev = nullptr;
        }
        delete temp;
    }

    //Define pop_back()
    void pop_back() {
        if (!tail) return; // Empty list
        Node* temp = tail;
        if (tail == head)
            tail = head = nullptr;
        else
        {
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
        if (!current) return;
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
        if (!current) return;
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
int main() {
    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();

    cout << "List backward: ";
    list.print_reverse();

    cout << "Inserting node 45 at position 6: ";
    list.insert_after(46, 6);
    list.print();

    cout << "Deleting value 45: ";
    list.delete_val(45);
    list.print();

    cout << "Inserting node 122 at tail: ";
    list.push_back(122);
    list.print();

    cout << "Inserting node 253 at head: ";
    list.push_front(253);
    list.print();

    cout << "Deleting at position 4: ";
    list.delete_pos(4);
    list.print();
    
    cout << "Deleting the head: ";
    list.pop_front();
    list.print();

    cout << "Deleting the tail: ";
    list.pop_back();
    list.print();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
