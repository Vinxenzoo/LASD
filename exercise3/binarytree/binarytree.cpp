//Vincenzo Capasso N86004259

#include "binarytree.hpp"

namespace lasd 
{

/* ************************************************************************** */

//operatori di comparazione

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node & nodo_comp) const noexcept 
{
bool cond = true;

  if(Element() == nodo_comp.Element())
  {
    if(HasLeftChild() && nodo_comp.HasLeftChild())
    {
      cond = (LeftChild() == nodo_comp.LeftChild());
    }
    else if (HasLeftChild() || nodo_comp.HasLeftChild())
    {
      cond = false;
    }
    if(cond)
    {
      if(HasRightChild() && nodo_comp.HasRightChild())
      {
        cond = RightChild() == nodo_comp.RightChild();
      }
      else if(HasRightChild() || nodo_comp.HasRightChild())
      {
        cond = false;
      }
    }
  }
  else
    cond = false;
  return cond;
}

//Binary tree

//PreOrderTraverse 
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun, const Node* altro_nodo) const 
{
    if (altro_nodo == nullptr) {return;}

    fun(altro_nodo->Element());
    if (altro_nodo->HasLeftChild()) { PreOrderTraverse(fun, &(altro_nodo->LeftChild()));}
    if (altro_nodo->HasRightChild()) {PreOrderTraverse(fun, &(altro_nodo->RightChild()));}
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun, const Node* altro_nodo) const 
{
    if (altro_nodo == nullptr) {return;}

    if (altro_nodo->HasLeftChild()) { PostOrderTraverse(fun, &(altro_nodo->LeftChild()));}
    if (altro_nodo->HasRightChild()) { PostOrderTraverse(fun, &(altro_nodo->RightChild()));}
    fun(altro_nodo->Element());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun, const Node* altro_nodo) const 
{
    if(altro_nodo == nullptr) {return;}

    if (altro_nodo->HasLeftChild()) { InOrderTraverse(fun, &(altro_nodo->LeftChild()));}
    fun(altro_nodo->Element());
    if (altro_nodo->HasRightChild()) { InOrderTraverse(fun, &(altro_nodo->RightChild()));}

}

template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun, const Node* altro_nodo) const 
{
    if(altro_nodo == nullptr) { return;}

    lasd::QueueVec<const Node *> queue;
    queue.Enqueue(altro_nodo);

    while(!queue.Empty()) 
    {
        fun(queue.Head()->Element());
        if(queue.Head()->HasLeftChild()) {queue.Enqueue(&(queue.Head()->LeftChild()));}
        if(queue.Head()->HasRightChild()) {queue.Enqueue(&(queue.Head()->RightChild()));}
        queue.Dequeue();
    }
}

//MutableBinarytree

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun, MutableNode * altro_nodo) 
{
    if (altro_nodo == nullptr) { return;}

    fun(altro_nodo->Element());
    if (altro_nodo->HasLeftChild()) { PreOrderMap(fun, &(altro_nodo->LeftChild()));}
    if (altro_nodo->HasRightChild()) { PreOrderMap(fun, &(altro_nodo->RightChild()));}

}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun, MutableNode * altro_nodo) 
{
    if (altro_nodo == nullptr) {return;}

    if (altro_nodo->HasLeftChild()) { PostOrderMap(fun, &(altro_nodo->LeftChild()));}
    if (altro_nodo->HasRightChild()) { PostOrderMap(fun, &(altro_nodo->RightChild()));}
    fun(altro_nodo->Element());

}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun, MutableNode * altro_nodo) 
{
    if (altro_nodo == nullptr) {return;}

    if (altro_nodo->HasLeftChild()) { InOrderMap(fun, &(altro_nodo->LeftChild()));}
    fun(altro_nodo->Element());
    if (altro_nodo->HasRightChild()) { InOrderMap(fun, &(altro_nodo->RightChild()));}
}

template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun, MutableNode* altro_nodo) 
{
    if(altro_nodo == nullptr) {return;}
    lasd::QueueVec<MutableNode *> queue;
    queue.Enqueue(altro_nodo);

    while(!queue.Empty()) 
    {
        fun(queue.Head()->Element());

        if(queue.Head()->HasLeftChild()) { queue.Enqueue(&(queue.Head()->LeftChild()));}
        if(queue.Head()->HasRightChild()) { queue.Enqueue(&(queue.Head()->RightChild()));}
        queue.Dequeue();
    }
}

//BTPreorder iterator function and operator

template <typename Data>
BTPreOrderIterator<Data> & BTPreOrderIterator<Data>::operator++() 
{
  if(!Terminated())
  {
    if (curr->HasLeftChild())
    {
      if(curr->HasRightChild())
      {
        stk.Push(&curr->RightChild());
      }
      curr = &curr->LeftChild();
    }
    else
    {
        if(curr->HasRightChild())
        {
          curr = &curr->RightChild();
        }
        else
        {
          if(stk.Empty())
          {
            curr = nullptr;
          }
          else
          {
            curr = stk.TopNPop();
          }
        }
      }
    }
    else
    {
      curr = nullptr;
      throw std::out_of_range("Iteratore terminato!");
    }
  return *this;
}


template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator++() 
{
{
  if(!Terminated())
  {
    if (!stk.Empty())
    {
        //ricordarsi che il post order it parte dal nodo piu a sinistra però possono esserci anche nodi destri all'interno del cammino per il nodo più a sinistra
      if(stk.Top()->HasRightChild())
      {
        if (&stk.Top()->RightChild() != curr)
        {
          curr = &stk.Top()->RightChild();
          while (curr->HasLeftChild() || curr->HasRightChild())
          {
            if (curr->HasLeftChild())
            {
              stk.Push(curr);
              curr = &curr->LeftChild();
            }
            else
            {
              stk.Push(curr);
              curr = &curr->RightChild();
            }
          }
        }
        else
        {
          curr = stk.TopNPop();
        }
      }
      else
      {
        curr = stk.TopNPop();
      }
    }
    else
    {
      curr = nullptr;
    }
  }
  else
  {
    throw std::out_of_range("Iteratore terminato!");
  }
  return *this;
}
}

template <typename Data>
void BTPostOrderIterator<Data>::piu_a_sinistra() 
{
    while (curr!=nullptr) 
    {
        if (curr->HasLeftChild()) 
        {
            stk.Push(curr);
            curr = &(curr->LeftChild());
        }
        else 
        { if (curr->HasRightChild()) 
        {
            stk.Push(curr);
            curr = &(curr->RightChild());
        }
        else 
        {
            break; 
        }
    }
}
}


//In Order Iterator

template <typename Data>
void BTInOrderIterator<Data>::piu_a_sinistra_n() 
{
    if(curr == nullptr) { return;}
    while(curr->HasLeftChild()) { stk.Push(curr);  curr = &curr->LeftChild(); }
}



template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator++() 
{
    if(Terminated()) { throw std::out_of_range("Iterator Terminated!");}
    if(curr->HasRightChild()) 
    {
        curr = &(curr->RightChild());
        piu_a_sinistra_n();
    } 
    else 
    {
        if(stk.Empty())
        {
            curr = nullptr;
        } 
        else 
        {
            curr = stk.TopNPop();
        }

    }
    return *this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator++() 
{
if(!Terminated())
  {
    if(curr->HasLeftChild())
      queue.Enqueue(&curr->LeftChild());

    if(curr->HasRightChild())
      queue.Enqueue(&curr->RightChild());

    if(queue.Empty())
      curr = nullptr;
    else
      curr = queue.HeadNDequeue();

  }
  else
    throw std::out_of_range("Iteratore terminato!");

  return *this;
}



};

