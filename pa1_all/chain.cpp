#include "chain.h"
#include "chain_given.cpp"

using namespace std;

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain(){ 
  clear();
}

/**
 * Inserts a new node in position one of the Chain,
 * after the sentinel node.
 * This function **SHOULD** create a new Node.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertFront(const Block & ndata){
  Node* insf= new Node(ndata);

  head_->next->prev = insf;
  
  insf->next = head_->next;
  head_->next = insf;
  insf->prev = head_;

  length_= length_ + 1;
/* your code here! */
}

/**
 * Inserts a new node at the back of the Chain,
 * but before the tail sentinel node.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block & ndata){
  Node* insb= new Node(ndata);
  tail_->prev->next= insb;
  insb->prev = tail_->prev;
  tail_->prev= insb;
  insb->next = tail_;
  length_+= 1;
   /* your code here! */
}

/**
 * Modifies the Chain by moving a contiguous subset of Nodes to
 * the end of the chain. The subset of len nodes from (and
 * including) startPos are moved so that they
 * occupy the last len positions of the
 * chain (maintaining the sentinel at the end). Their order is
 * not changed in the move.
 */
void Chain::moveToBack(int startPos, int len){
  if(startPos+len > size()) return;
  if(startPos <1 || len <1) return;
  if(head_ == NULL) return;

  Node* startp = walk(head_, startPos-1);
  Node* start = walk(startp, 1);
  Node* end = walk(startp, len);
  Node* endn = walk(end,1);

 
 
  startp->next = endn;
  endn->prev=startp;

  Node* tailp = tail_->prev;
  tailp->next = start;
  start->prev = tailp;

  tail_->prev= end;
  end->next = tail_;
  
   /* your code here! */
}

/**
 * Rotates the current Chain by k nodes: removes the first
 * k nodes from the Chain and attaches them, in order, at
 * the end of the chain (maintaining the sentinel at the end).
 */
void Chain::rotate(int k){
  moveToBack(1, k);
   /* your code here! */
}

/**
 * Modifies the current chain by swapping the Node at pos1
 * with the Node at pos2. the positions are 1-based.
 */
void Chain::swap(int pos1, int pos2){
  if(pos1 <1 || pos2 <1) return;
  Node* pos1nd = walk(head_, pos1);
  Node* pos2nd = walk(head_, pos2);

  Node* pos1prev = pos1nd->prev;
  Node* pos1next = pos1nd->next;
  
  Node* pos2prev = pos2nd->prev;
  Node* pos2next = pos2nd->next;

  Node* copypos1 = new Node(pos1nd->data);
  Node* copypos2 = new Node(pos2nd->data);

 
  pos1prev->next = copypos2;
  copypos2->prev = pos1prev;
  copypos2->next = pos1next;
  pos1next->prev = copypos2;

  pos1nd->prev = NULL;
  pos1nd->next = NULL;
  delete pos1nd;

  pos2prev->next = copypos1;
  copypos1->prev = pos2prev;
  copypos1->next = pos2next;
  pos2next->prev =  copypos1;

  pos2nd->prev=NULL;
  pos2nd->next=NULL;
  delete pos2nd;
}
 

/*
 *Modifies both the current and input chains by trading
 * nodes in even positions between the chains. Length
 * of each chain should stay the same. If the block dimensions
 * are NOT the same, the funtion has no effect and a simple
 * error message is output: cout << "Block sizes differ." << endl;
 */

void Chain::twist(Chain & other){

   if(other.empty()|| empty()) return;

   if(width_ != other.width_|| height_ != other.height_){
     cout << "Block sizes differ. " << endl; 
   }

  if(size() == other.size()){
   for(int i = 2; i <= length_; i=i+2){
     Node* even = walk(head_, i);
     Node* evenprev = even->prev;
     Node* evennext = even->next;
     Node* eveno= other.walk(other.head_, i);
     Node* evenoprev = eveno->prev;
     Node* evenonext = eveno->next;

     evenprev->next = eveno;
      evennext->prev = eveno;
      eveno->prev = evenprev;
      eveno->next = evennext;

      evenoprev->next = even;
      evenonext->prev = even;
      even->prev =evenoprev;
      even->next = evenonext;}
    }else{
   
    /* these two chains have different length */
   int leng;
   if(size() < other.size()){
     leng = length_;
   }else{
     leng = other.length_;
   }

   for(int i = 2; i <= leng; i=i+2){
    Node* even = walk(head_, i);
     Node* evenprev = even->prev;
     Node* evennext = even->next;
     Node* eveno= other.walk(other.head_, i);
     Node* evenoprev = eveno->prev;
     Node* evenonext = eveno->next;

     evenprev->next = eveno;
      evennext->prev = eveno;
      eveno->prev = evenprev;
      eveno->next = evennext;

      evenoprev->next = even;
      evenonext->prev = even;
      even->prev =evenoprev;
      even->next = evenonext;
    }
  }
  
   /* Your code here. */
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear() {
  Node* curr = head_;
  while(curr->next != NULL){
  Node* temp = curr;
  curr =  curr->next;
  delete temp; 
  head_ = curr;
  curr->prev = NULL;
  }
  head_ = NULL;
  tail_ = NULL;
  delete curr;
  delete head_;
  delete tail_;
   /*your code here*/
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const& other) {
   head_ = new Node(Block());
   tail_ = new Node(Block());
   head_->next = tail_;
   tail_->prev = head_;
   width_ = other.width_;
   height_=other.height_;

   if(other.empty()){
    return;
   }
  

   Node* curr = other.head_;
   Node* first = curr->next;
   Node* end  = other.tail_;
 
   while(first != end){
   Block b = first->data;
   insertBack(b);
   first = first->next;
   }
   length_ = other.length_;
   /* your code here! */
}
