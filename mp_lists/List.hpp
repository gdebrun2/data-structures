/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_=0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * temp = head_;
  if(temp==NULL)
  {
    return;
  }
  ListNode * temp2;
  while(temp!=NULL)
  {
    temp2=temp->next;
    delete temp;
    temp = temp2;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ ->prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_=newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  if (head_ == NULL) {
    head_ = newNode;
  }
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }

  tail_=newNode;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  if(start==NULL)
  {
    return NULL;
  }
  if(splitPoint<1)
  {
    return start;
  }
  if(length_<splitPoint)
  {
    return NULL;
  }
  ListNode * curr = start;

  for (int i = 0; i < splitPoint-1 && curr != NULL; i++) {
    if(curr->next!=NULL)
      curr = curr->next;
  }

  if (curr != NULL) {
      curr=curr->next;
      curr->prev->next = NULL;
      tail_=curr->prev;
      curr->prev = NULL;
      return curr;
  }

  return NULL;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  std::vector<ListNode*> nodes;
  ListNode *node = head_;
  for (int i = 0; i < length_; i++) {
    
    nodes.push_back(node);
    node = node->next;
    
  }
  ListNode *tmp;
  std::vector<ListNode*> reinsert;
  int j = 0;
  for (unsigned i = 0; i < nodes.size(); i++) {
    if (i % 3 == 0) {
      reinsert.push_back(nodes[i]);
      nodes[i] = nullptr;
    }
  }
  for (unsigned i = 0; i < nodes.size(); i++) {
    if (nodes[i] == nullptr) {
      nodes.erase(nodes.begin()+i);
    }
  }
  for (unsigned i = 0; i < nodes.size() + reinsert.size(); i++) {
    if (i % 3 == 2) {
      nodes.insert(nodes.begin()+i, reinsert[j]);
      j++;
    }
  }
  for (unsigned i = 0; i < nodes.size() - 1; i++) {

    std::cout << nodes[i]->data << std::endl;
    if (i == 0) {
      nodes[i]->prev = nullptr;
      head_ = nodes[i];
      nodes[i]-> next = nodes[i + 1];
    }
    else if (i == nodes.size() - 2) {
      nodes[i]->next = nodes[i + 1];
      nodes[i + 1]->prev = nodes[i];
      tail_ = nodes[i + 1];
      nodes[i + 1]->next = nullptr;
    }
    else if (i != 0 && i < nodes.size() - 2) {
      nodes[i]->prev = nodes[i - 1];
      nodes[i]->next = nodes[i + 1];
    }
    /**if (i == 0) {
      ListNode *index0 = nodes[0];
      ListNode *index1 = nodes[1];
      ListNode *index3 = nodes[3];
      ListNode *index2 = nodes[2];
      ListNode *index4 = nodes[4];
      ListNode *index5 = nodes[5];
      nodes[0]->prev = index2;
      nodes[0]->next = index4;
      nodes[1]->prev = nullptr;
      nodes[2]->next = index0;
      nodes[3]->prev = index5;
      nodes[3]->next = nullptr;
      nodes[4]->prev = index0;
      nodes[5]->next = index3;
      head_ = nodes[1];
      tail_ = nodes[3]; */
  }

}



/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode * tempstart = startPoint;
  ListNode * startPrev = startPoint;
  ListNode * endNext = endPoint->next;
  if(startPoint == endPoint)
  {
    return;
  }
  while (tempstart != endNext)
  {
      startPrev = tempstart->prev;
      tempstart->prev = tempstart->next;
      tempstart->next = startPrev;
      tempstart = tempstart->prev;
  }
  startPrev = endPoint->prev;
  ListNode * temp22 = startPoint->next;
  if(temp22!=NULL)
  {
    endPoint->prev = startPoint->next;
    startPoint->next->next = endPoint;
  }
  else
  {
    endPoint->prev = NULL;//NULL;
  }
  if(startPrev!=NULL)
  {
    startPoint->next = startPrev;
    startPrev->prev = startPoint;
  }
  else
  {
    startPoint->next = nullptr;
  }
  tempstart = startPoint;
  startPoint = endPoint;
  endPoint = tempstart;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  int c= n;
  if(n <= 1)
  {
    return;
  }
  if(length_<=1)
  {
    return;
  }
  if(n>=length_)
  {
    reverse();
  }
  ListNode * temp1 = head_;
  ListNode * temp2 = head_;
  ListNode * temp3 = nullptr;
  while(temp1 != NULL)
    {
       if (c==0)
       {
           if (temp2 == head_)
               head_ = temp3;
            reverse(temp2,temp3);
            c = n;
            temp2 = temp1;
            temp3 = temp1;
       }
       if (temp1->next == NULL)
       {
            reverse(temp2,temp1);
       }
       temp3= temp1;
       temp1 = temp1->next;
       c=c-1;
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
 template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode * temp1 = NULL;

  ListNode * fv = first;

  ListNode * tempf = first;
  ListNode * temps = second;
  if(first->data < second->data)
  {
        fv = tempf;
        tempf = tempf->next;
  }
  else
  {
        fv = temps;
        temps = temps->next;
  }

  temp1 = fv;

  while(temps != NULL && tempf != NULL)
  {

      if(tempf == NULL && temps== NULL)
      {
        break;
      }

      else if(tempf == NULL ||
              (temps->data < tempf->data && temps != NULL) )
      {
        temp1->next = temps;
        temp1->next->prev = temp1;
        temps = temps->next;
        temp1 = temp1->next;
      }
      else
      {
        temp1->next = tempf;
        temp1->next->prev = temp1;
        tempf = tempf->next;
        temp1 = temp1->next;
      }
  }

  if(temps == NULL)
  {
    temp1->next = tempf;
    tempf->prev = temp1;
  }
  else
  {//std::cout<<"n-null";
  }
  if(tempf == NULL)
  {
    temp1->next = temps;
    temps->prev = temp1;
  }
  return fv;
}


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1){
	return start;
  }
  else {
	int currLength = chainLength/2;
	ListNode * temp;
	temp = split(start, currLength);
	ListNode * begin = mergesort(start, currLength);
	ListNode * end = mergesort(temp, chainLength - currLength);
	return merge(begin, end);
  }
}
