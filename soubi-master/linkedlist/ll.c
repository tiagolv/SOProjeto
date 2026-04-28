#include <iostream>
#include <cstdlib>


class Node
{
public:
    Node* next;
    int data;
};

using namespace std;

class LinkedList
{
public:
    int length;
    Node* head;

    LinkedList();
    ~LinkedList();
    void add(int data);
	void remove();
    void print();
};

LinkedList::LinkedList(){
    this->length = 0;
    this->head = NULL;
}

LinkedList::~LinkedList(){
	
	if (this->head == NULL) return;
	 
	Node* head = this->head;
    while(head){
		Node *tmp=head;
        head = tmp->next;
		free(tmp);
    }
	
    std::cout << "LIST DELETED";
}

void LinkedList::add(int data){
    Node* node = new Node();
    node->data = data;
    node->next = this->head;
    this->head = node;
    this->length++;
}
/* remover o inicio da lista */

void LinkedList::remove(){
    if (this->head == NULL) return;
	//if this->length == 0 retunr
	
    Node* node = this->head->next;
	free(head);
	this->head = node;
	
	this->length --;
}

void LinkedList::print(){
    Node* head = this->head;
    int i = 1;
    while(head){
        std::cout << i << ": " << head->data << std::endl;
        head = head->next;
        i++;
    }
}

int main(int argc, char const *argv[])
{
    LinkedList* list = new LinkedList();
	

	cout << "Press Enter";
	cin.get();
	
    for (int i = 0; i < 1000000; ++i)
    {
        list->add(rand() % 100);
    }
    //list->print();
    std::cout << "List Length: " << list->length << std::endl;
	
	list->remove();
	list->remove();
    
	cout << "Press Enter";	
    cin.get();
	
	//list->print();
    std::cout << "List Length: " << list->length << std::endl;
	
    delete list;
	
	cout << "Press Enter";
	cin.get();
	
	list = new LinkedList();
    for (int i = 0; i < 1000000; ++i)
    {
        list->add(rand() % 100);
    }
    //list->print();
    std::cout << "List Length: " << list->length << std::endl;
	
	cout << "Press Enter";
	cin.get();
	
	
    return 0;
}