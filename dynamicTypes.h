#pragma once

//linked list

template <typename dataclass>

class linkList {
private: 
    int partition(int low = 0, int high = 0);
public:
    class nodeClass {// node general structure
    public:
        dataclass data;
        nodeClass* next = nullptr;// point to the next node
        nodeClass* previous = nullptr;// point to the previous node
    };

    nodeClass* last = nullptr;// points to the last node
    nodeClass* first = nullptr;// points to the first node

    // CRUD
    void addTofirst(dataclass data);// create some node at first
    void addToEnd(dataclass data);// create some node at first

    nodeClass* get(int index) {// read a node
        if (first != nullptr) {
            if (index == 0) return first;
            else {
                nodeClass* current = first;
                while (current != nullptr && index > 0) {
                    index -= 1;
                    current = current->next;
                }
                return current;
            };
        }
        else return nullptr;
    };
    int getSize();// get the size of the list

    void updNode(int index, dataclass data);// update a node
    void swap(int from, int  to);// swap two nodes 
    void quickSort(int low = 0, int high = 0); // sort data (needs overload operators)
    void delNode(int index);// delete a node
    void purgeAll(); // delete all nodes

    nodeClass* operator[](int index) {
        return get(index);
    };
    

};

    template <typename dataclass>
    void linkList<dataclass>::addTofirst (dataclass data) {
        nodeClass* z = new (nodeClass);
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
    void linkList<dataclass>::addToEnd(dataclass data) {
        nodeClass* z = new (nodeClass);
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
    void linkList<dataclass>::updNode(int index, dataclass data) {
        nodeClass* find = get(index);
        if (find != nullptr) {
            find->data = data;
            //cout << "\n Update Succesfull \n";
        }
    };

    template <typename dataclass>
    void linkList<dataclass>::swap(int from, int to) {
        nodeClass* node1 = get(from);
        nodeClass* node2 = get(to);
        dataclass temp = node1->data;
        node1->data = node2->data;
        node2->data = temp;
    };

    template <typename dataclass>
    int linkList<dataclass>::partition(int low, int high) {
        dataclass pivot = get(low)->data;
        int count = 0;
        int i = low + 1;
        int j = high;
        while (i <= high) {
            if (get(i)->data >= pivot) count += 1;
            i += 1;
        }
        int pivotIndex = low + count;
        swap(pivotIndex, low);
        i = low;
        while (i < pivotIndex && j > pivotIndex) {

            while (get(i)->data >= pivot) {
                i++;
            }

            while (get(j)->data < pivot) {
                j--;
            }

            if (i < pivotIndex && j > pivotIndex) {
                swap(i++, j--);
            }
        }

        return pivotIndex;
    };

    template <typename dataclass>
    void linkList<dataclass>::quickSort(int low, int high) {
        if (low >= high) return;
        int p = partition(low, high);
        quickSort(low, p - 1);
        quickSort(p + 1, high);
    };

    template <typename dataclass>
    void linkList<dataclass>::delNode(int index) {
        nodeClass* find = get(index);
        if (find != nullptr) {
            if (find == first) first = find->next;
            if (find == last) last = find->previous;
            if (find->next != nullptr) find->next->previous = find->previous;
            if(find->previous != nullptr) find->previous->next = find->next;
            delete find;
            //cout << "\n Delete Succesfull \n";
        }
    };
    template <typename dataclass>
    int linkList<dataclass>::getSize() {
        int size = 0;
        nodeClass* current = first;
        while (current != nullptr) {
            size += 1;
            current = current->next;
        }
        return size;
    };
    template <typename dataclass>
    void linkList<dataclass>::purgeAll() {
        nodeClass* current = first;
        nodeClass* temp;
        while (current != nullptr) {
            temp = current->next;
            delete current;
            current = temp;
        }
        first = nullptr;
        last = nullptr;
        //cout << "\n Purge Succesfull \n";
    };

//end of linked list


//Binary Trees

template <typename dataclass>
class treeClass {
public:
    class nodeClass {// node general structure
    public:
        int id = nullptr;
        bool isRoot = false;
        bool isParent = false;
        bool isLeaf = true;
        bool isNode = false;
        dataclass data;
        nodeClass* left = nullptr;// point to the next node
        nodeClass* father = nullptr;// point to the father node
        nodeClass* right = nullptr;// point to the previous node
    };
    nodeClass* root = nullptr;// points to the last node

    // CRUD
    void addToTree(dataclass from, int index);// create a new node on the tree
    
    dataclass get(nodeClass from, linkList<dataclass>& data);// read a node
    
    nodeClass* search(nodeClass* from, int index, int dir)// search a node of the tree, starting from some point
    {
        nodeClass* cursor = from;
        if (cursor != nullptr) {
            if (cursor->data != index) {
                if (cursor->data > index) {
                    if (cursor->left != nullptr)
                        cursor = search(cursor->left, index);
                    else
                        dir = 1;

                }
                if (cursor->data < index) {
                    if (cursor->right != nullptr)
                        cursor = search(cursor->right, index);
                    else
                        dir = 2;

                }
                if (cursor->data == index) {
                    dir = 3;
                }
            }
        }
        else dir = 0;
        return cursor;
    };
    void purgeAll(); // delete all nodes
    

    dataclass operator[](int param) {
        return get(param)->data;
    };
};

template <typename dataclass>
void treeClass<dataclass>::addToTree(dataclass data, int id) {
    int dir = 0;
    nodeClass* father = search(root,id, dir);
    nodeClass* z = new (nodeClass);
    z->data = data;
    if (root != nullptr) {
        z->father = father;
        switch(dir) 
        {
        case 1:
            father->left = z;
            break;
        case 2:
            father->right = z;
            break;
        }
        father->isParent = true;
        father->isLeaf = false;
    }
    else {
        root = z;
    }
};

template <typename dataclass>
dataclass treeClass<dataclass>::get(treeClass::nodeClass from, linkList<dataclass>& data)// read a node
{
    nodeClass* cursor = from;
    if (cursor != nullptr) {
        if (cursor->left != nullptr) {
            data.addToFirst(get(cursor->left));// la izquierda del arbol
        }
        data.addToEnd(cursor->data);
        if (cursor->left != nullptr) {
            data.addToEnd(get(cursor->right));// la izquierda del arbol
        }
    }
    else return nullptr;
};

template <typename dataclass>
void treeClass<dataclass>::purgeAll() {
    nodeClass* current = root;
    nodeClass* temp;
    while (current != nullptr) {
        temp = current->next;
        delete current;
        current = temp;
    }
    //cout << "\n Purge Succesfull \n";
};

// end of Binary trees

// graphs

template <typename dataclass>
class graphsClass {
public:
    class nodeClass {// node general structure
        class pathClass {
            int weight = 1;
            nodeClass* destination = nullptr;
            nodeClass* startpoint = nullptr;

        };
        dataclass data;
        linkList<pathClass*> paths;
        //CRUD
        void addPath(nodeClass to); // create a path between two nodes
        pathClass* searchPath(nodeClass to) {// search a path between two nodes
            int  i = 0;
            while (paths[i] != nullptr) {
                if (paths[i]->destination == to) {
                    return paths[i];
                }
                i++;
            }
            return nullptr;
        };
        void deletePath(nodeClass to);// delete a node of the tree, starting from some point

        /* void operator delete() {
            paths.purgeAll();
        };// delete a node */
    };

    linkList<nodeClass*> nodes;
    
    // CRUD
    void addNode(dataclass data);// create a new node on the graph
    nodeClass* searchNode(dataclass index) {// search a node of the graph
        int  i = 0;
        while (nodes[i] != nullptr) {
            if (nodes[i]->data == index) {
                return nodes[i];
            }
            i++;
        }
        return nullptr;
    };

    linkList<nodeClass> searchPath(dataclass to) {// search a path between two nodes
        
    };

    void purgeAll(); // delete all nodes
    dataclass get(int index=0);// read all nodes or just one
    
};

template <typename dataclass>
void graphsClass<dataclass>::addNode(dataclass data) {
    nodeClass* temp = new (nodeClass);
    temp->data = data;
    nodes.addToEnd(temp);
};



template <typename dataclass>
void graphsClass<dataclass>::nodeClass::addPath(nodeClass to) {
    pathClass* temp = new(pathClass);
    temp->startpoint = this;
    temp->destination = to;
    paths.addToEnd(temp);
};
