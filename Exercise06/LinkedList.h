#ifndef ITERATORS_LINKED_LIST_H_
#define ITERATORS_LINKED_LIST_H_

#include <iostream>

class LinkedList {

  // Nested private class - only used to save the elements of the list
  struct Node {
	int data_;
	Node* next_;
	Node(int data, Node *next) : data_(data), next_(next) {}
  };

public:
    LinkedList() : head_(nullptr) {}

    void push(int data) {
        head_ = new Node(data, head_);
    }

    void erase(int data) {
      Node *cur_node = head_;
      
      // handle head node
      if(head_->data_ == data) {
          head_ = cur_node->next_;
          delete cur_node;
          return;
      }
      
      Node* last_node = nullptr;
      while (cur_node) {
        // node to delete
        if (cur_node->data_ == data && last_node) {
            last_node->next_ = cur_node->next_;
            delete cur_node;
            break;
        }
        last_node = cur_node;
        cur_node = cur_node->next_;
      }
    }

    ~LinkedList() {
      Node *cur_node = head_, *next_node;
      while (cur_node) {
        next_node = cur_node->next_;
        delete cur_node;
        cur_node = next_node;
      }
    }
    

  /* Iterator class */
  class Iterator {
  private:


  public:
    /* ITERATOR TRAITS - must be defined (and public) in the iterator, for it to work with all STL algorithms.
     * Comment this out and attempt to call std::find with this iterator to watch the runtime error
     * you will get if you don't define iterator traits */
    typedef int value_type;
    typedef int& reference;
    typedef int* pointer;
    typedef ptrdiff_t difference_type; // irrelevant here, as we have no difference - but still required
    typedef std::forward_iterator_tag iterator_category;

      Iterator(Node* node) : _node(node)  {}

      Iterator& operator++() {
            _node = _node->next_;
            return *this;
      }

      Iterator operator++(int) {
            auto tmp = *this;
            ++*this;
            return tmp;
      }

      bool operator==(const Iterator& rhs) const {
          return _node == rhs._node;

      }

      bool operator!=(const Iterator& rhs) const {
          return !(*this == rhs);

      }

      reference operator*() const {
            return _node->data_;
      }

      pointer operator->() const {
            return &(_node->data_);
            // or: return &(**this);
      }

  private:
      Node* _node;
  };


private:
  Node *head_; // head of the linked list

public:





  /* Iterator functions section - begin, end, etc
     begin will return an iterator or a const_iterator depending on the const-qualification of the object it is called on.
     cbegin will always return a const_iterator */

};

#endif //ITERATORS__LINKED_LIST_H_
