#pragma once

template <typename dataclass> 
class nodeClass {
public:
    dataclass data;
    nodeClass<dataclass>* next = nullptr;// point to the next node
    nodeClass<dataclass>* previous = nullptr;// point to the previous node
};


template <typename dataclass>

class linkClass{
    public:
        nodeClass<dataclass>* last = nullptr;// points to the last node
        nodeClass<dataclass>* first = nullptr;// points to the first node

        // CRUD
        void addTofirst(dataclass data);// create some node at first
        void addToEnd(dataclass data);// create some node at first
        nodeClass<dataclass>* get(int index);// read a node
        void updNode(int index, dataclass data);// update a node
        void delNode(int index);// delete a node
        void purgeAll(); // delete all nodes

        dataclass operator[](int index) {
            return get(index)->data;
        };
};

template <typename dataclass>
void linkClass<dataclass>::addTofirst (dataclass data) {
    nodeClass<dataclass>* z = new (nodeClass<dataclass>);
    z->data = data;
    if (first != nullptr) {
        first->next = z;
        z -> next = first;
    }
    else {
        z -> previous = NULL;
        last = z;
    }
    first = z;
};

template <typename dataclass>
void linkClass<dataclass>::addToEnd(dataclass data) {
    nodeClass<dataclass>* z = new (nodeClass<dataclass>);
    if (first != nullptr) {
        last->next = z;
        z->previous = last;
    }
    else {
        z->previous = nullptr;
        first = z;
    }
    last = z;
    z->data = data;
};

template <typename dataclass>
nodeClass<dataclass>* linkClass<dataclass>::get(int index) {
    if (first != nullptr) {
        if (index == 0) return first;
        else {
            nodeClass<dataclass>* current = first;
            while (current != nullptr && index > 0) {
                index -= 1;
                current = current->next;
            }
            return current;
        };
    }
    else return nullptr;
};

template <typename dataclass>
void linkClass<dataclass>::updNode(int index, dataclass data) {
    nodeClass<dataclass>* find = get(index);
    if (find != nullptr) {
        find->data = data;
        cout << "\n Update Succesfull \n";
    }
};

template <typename dataclass>
void linkClass<dataclass>::delNode(int index) {
    nodeClass<dataclass>* find = get(index);
    if (find != nullptr) {
        find->next->previous = find->previous;
        find->previous->next = find->next;
        delete find;
        cout << "\n Delete Succesfull \n";
    }
};
template <typename dataclass>
void linkClass<dataclass>::purgeAll() {
    nodeClass<dataclass>* current = first;
    nodeClass<dataclass>* temp;
    while (current != nullptr) {
        temp = current->next;
        delete current;
        current = temp;
    }
    cout << "\n Purge Succesfull \n";
};