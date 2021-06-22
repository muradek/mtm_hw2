//
// Created by Admin on 22/06/2021.
//

#ifndef SORTEDLIST_SORTEDLIST_H
#define SORTEDLIST_SORTEDLIST_H
#include <iostream>
#include <stdexcept>
using std::ostream;
using namespace std;

namespace mtm {

    template<class T>
    class GenericNode {
        T* Data;
        GenericNode *next;

    public:
        GenericNode();
        ~GenericNode()=default;
        GenericNode(T* value, GenericNode *next);
        GenericNode &operator=(GenericNode<T> node);
        T* getData();
        GenericNode *getNext();
        void setNext(GenericNode<T> *node);
    };

    template<class T>
    T* GenericNode<T>::getData() {
        return this->Data;
    }
    //assignment operator for the nodes;
    template<class T>
    GenericNode<T> &GenericNode<T>::operator=(GenericNode<T> node) {
        Data=node.Data;
    }

    template<class T>
    GenericNode<T> *GenericNode<T>::getNext() {
        return this->next;
    }

    template<class T>
    void GenericNode<T>::setNext(GenericNode *node) {
        this->next = node;
    }

    template<class T>
    GenericNode<T>::GenericNode(T* value, GenericNode *next): Data(value), next(next) {}

    template<class T>
    class SortedList {
        GenericNode<T> *first_node;
        int num_of_nodes;

    public:
        SortedList();
        ~SortedList();
        SortedList &operator=(const SortedList &);
        SortedList(const SortedList &);
        void DeleteNode(GenericNode<T> *node);
        class const_iterator
        {
            GenericNode<T> *node;
            const_iterator(GenericNode<T>* ourList, int index);
            GenericNode<T>* getNode();
        public:
            const_iterator()=delete;
            ~const_iterator()=default;
            explicit const_iterator(GenericNode<T> *node);
            const T &operator*() const;
            const_iterator &operator++();
            const_iterator operator++(int);
            bool operator==(const const_iterator &it) const;
            bool operator!=(const const_iterator &it) const;
            const_iterator(const const_iterator &) = default;
            const_iterator &operator=(const const_iterator &) = default;
            friend SortedList<T>;

        };



        void insert(T Data);

        void remove(const_iterator element);

        int length();

        const_iterator begin();

        const_iterator end();

        template<class function>
        SortedList<T> apply(function applied);

        template<class function>
        SortedList<T> filter(function predict);

        friend const_iterator;
    };

    template<class T>
    SortedList<T>::SortedList():first_node(nullptr), num_of_nodes(0) {}

    template<class T>
    void SortedList<T>::DeleteNode(GenericNode<T> *node) {
        if(node!= nullptr){
            delete node->getData();
            delete(node);
        }
    }

    template<class T>
    SortedList<T>::~SortedList() {
        GenericNode<T> *node_to_delete;
        while(first_node!= nullptr){
            node_to_delete=first_node;
            first_node=first_node->getNext();
            DeleteNode(node_to_delete);
        }
    }
    template<class T>
    SortedList<T>::SortedList(const SortedList &other):first_node(nullptr), num_of_nodes(0){
        *this=other;
    }
    // assignment operator, we clear the current list, then we insert other list elements in the current list
    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &other) {
        if(&other==this)
        {
            return *this;
        }
        GenericNode<T> *node_to_delete;
        while(first_node!= nullptr){
            node_to_delete=first_node;
            first_node=first_node->getNext();
            DeleteNode(node_to_delete);
        }
        num_of_nodes=0;
        GenericNode<T> *other_iterator=other.first_node;
        while(other_iterator!= nullptr)
        {
            insert(*(other_iterator->getData()));
            other_iterator=other_iterator->getNext();
        }
        return *this;
    }


    template<class T>
    void SortedList<T>::insert(T Data) {
        T* newData = new T(Data);
        GenericNode<T> *newNode = new GenericNode<T>(newData, nullptr);
        if (num_of_nodes==0) { // if the list is empty
            first_node = newNode;
            num_of_nodes++;
            return;
        }
        if((*(newNode->getData()) < *(first_node->getData()))) // if we want to insert to the head
        {
            newNode->setNext(first_node);
            first_node=newNode;
            num_of_nodes++;
            return;
        }
        GenericNode<T>  *current=first_node;
        while(  (current->getNext() != nullptr))// if we want to insert in the the middle of the list
        {
            if(*(newNode->getData()) < *(current->getNext()->getData()))
            {
                newNode->setNext(current->getNext());
                current->setNext(newNode);
                num_of_nodes++;
                return;
            }
            current=current->getNext();
        }
        current->setNext(newNode); // we insert in the tail of the list
        num_of_nodes++;
    }

    template<class T>
    void SortedList<T>::remove(SortedList::const_iterator element) {
        if(num_of_nodes==0)
        {
            throw std::out_of_range("out of range");
        }
        num_of_nodes--;
        if(element.getNode() == first_node)
        {
            first_node=first_node->getNext();
            DeleteNode(element.getNode());
            return;
        }
        GenericNode<T>* current_node=first_node;
        while(current_node->getNext() != element.getNode())
        {
            current_node=current_node->getNext();
        }
        current_node->setNext(element.getNode()->getNext());
        DeleteNode(element.getNode());
    }

    template<class T>
    template<class Function>
    SortedList<T> SortedList<T>::apply(Function function) {
        SortedList<T> new_sorted_list;
        for (auto it = this->begin(); !(it == this->end()); ++it) {
            T new_value =  function(*it);
            new_sorted_list.insert(new_value);
        }
        return new_sorted_list;
    }

    template<class T>
    template<class function>
    SortedList<T> SortedList<T>::filter(function predict) {
        SortedList<T> new_sorted_list;
        for (auto it = this->begin(); it != this->end(); ++it) {
            if (predict(*it)) {
                new_sorted_list.insert(*it);
            }
        }
        return new_sorted_list;
    }

    template<class T>
    int SortedList<T>::length() {
        return num_of_nodes;
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator(GenericNode<T> *node) : node(node) {};

    template<class T>
    const T& SortedList<T>::const_iterator::operator*() const {
        if (!node) {
            throw std::out_of_range("out of range");
        }
        return *(node->getData());
    }

    template<class T>
    typename SortedList<T>::const_iterator &SortedList<T>::const_iterator::operator++() {
        if (!node) {
            throw std::out_of_range("out of range");
        }
        node = node->getNext();
        return *this;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int) {
        if (node== nullptr) {
            throw std::out_of_range("out of range");
        }
        const_iterator result = *this;
        ++*this;
        return result;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const SortedList<T>::const_iterator &it) const {
        if (node == nullptr && it.node == nullptr) {
            return true;
        }
        if (node == nullptr || it.node == nullptr) {
            return false;
        }
        if (node == it.node) {
            return true;
        }
        return false;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator!=(const SortedList<T>::const_iterator &it) const {
        return !(*this==it);
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() {
        return const_iterator(first_node);
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator(GenericNode<T> *ourList, int index) {
        while(index){
            index--;
            if(!ourList)
            {
                return;
            }
            ourList=ourList->getNext();
        }
        this->node=ourList;
    }

    template<class T>
    GenericNode<T> *SortedList<T>::const_iterator::getNode() {
        if(!node){
            return nullptr;
        }
        return node;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() {
        return const_iterator(first_node, num_of_nodes);
    }
}
#endif //SORTEDLIST_SORTEDLIST_H
