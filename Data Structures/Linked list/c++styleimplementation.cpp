#include<cstdio>
#include<iostream>
class Node
{
	private:
		int key;
		Node *next;
	public:
		Node();
		Node(int);
		int get_key();
		Node* get_node();
		void set_next(Node *);
		~Node();
		friend class LinkedList;
};
class LinkedList
{
	private:
		Node *head;
	public:
		LinkedList();
		void insert_at_beginning(int);
		void insert_at_end(int);
		void display_linked_list();
		~LinkedList();
};
//friend Node LinkedList;
Node::Node()
{
	//an empty contructor
}
Node::Node(int key)
{
	this->key=key;
	this->next=NULL;
}
int Node::get_key()
{
	return this->key;
}
Node* Node::get_node()
{
	//Now, this is a pointer
	//could we return this?
	return this;
}
void Node::set_next(Node *to_be_next)
{
	this->next=to_be_next;
}
Node::~Node()
{
	//free next;
	delete next;
	//otherwise, the memory will remain allocated in case of a big program
	//and we cannot reuse the heap memory
}
LinkedList::LinkedList()
{
	head=NULL;
}
void LinkedList::insert_at_beginning(int data)
{
	//now, since, LinkedList is a friend class of Node we can access the private members directly
	Node *curr=new Node();
	//allocate memory for pointer to a class dynamically
	curr->key=data;
	curr->next=NULL;
	//since, LinkedList is a friend class
	if(head==NULL)
	{
		head=curr;
		return;
	}
	curr->next=head;
	head=curr;
	//implmentation of singly linked list
}
void LinkedList::insert_at_end(int data)
{
	Node *curr=new Node();
	//now, sincce, LinkedList is a friend class of Node 
	//we can access the private members directly
	curr->key=data;
	curr->next=NULL;
	if(head==NULL)
	{
		head=curr;
		return;
	}
	Node *index_node=head;
	for(;index_node->next!=NULL;index_node=index_node->next)
	{
	}
	index_node->next=curr;
	//this is done	
}	
void LinkedList::display_linked_list()
{
	printf("The linkedlist is: ");
	Node *index_node=head;
	for(;index_node!=NULL;index_node=index_node->next)
	{
		if(index_node==head)
		{
			printf("%d",index_node->key);
		}
		else
		{
			printf(" %d",index_node->key);
		}
	}
}
LinkedList::~LinkedList()
{
	//free head;
	delete head;
	//generally memory allocated by new will be freed by delete function
}
int main()
{
	LinkedList curr_list;
	//default constructor will be invoked
	curr_list.insert_at_end(2);
	curr_list.insert_at_beginning(1);
	curr_list.insert_at_end(3);
	curr_list.display_linked_list();
	return 0;
	//now, curr_list goes out of scope
	//so, destructor will be invoked
}
