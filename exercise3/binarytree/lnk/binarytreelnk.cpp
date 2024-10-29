//Vincenzo Capasso N86004259

#include "binarytreelnk.hpp"

namespace lasd 
{

/* ************************************************************************** */

//Element
template <typename Data>
const Data & BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept {
    return info;
}

//Element (mutable)
template <typename Data>
Data & BinaryTreeLnk<Data>::NodeLnk::Element() noexcept {
    return info;
}

//isLeaf 
template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept {

    return !(HasLeftChild() || HasLeftChild());
}

//HasRightChild
template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
    return (right != nullptr);
}

//HasLeftChild
template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
    return (left != nullptr);
}



//Move & copy constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk && lnk_no) noexcept {
    std::swap(info, lnk_no.info);
    std::swap(left, lnk_no.left);
    std::swap(right,lnk_no.right);
};

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk & lnk_no) {

    info = lnk_no.info;

    if(lnk_no.HasLeftChild()) {left = new NodeLnk(*lnk_no.left);}
    if(lnk_no.HasRightChild()) {right = new NodeLnk(*lnk_no.right);}
}


//Copy assignment
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk & lnk_no) {

    info = lnk_no.info; 

    if(!(lnk_no.HasLeftChild())) 
    {
        delete left; left = nullptr;
    } 
    else 
    {
        delete left; left = new NodeLnk(*lnk_no.left);
    }

    if(!(lnk_no.HasRightChild())) 
    {
        delete right; right = nullptr;
    } 
    else 
    {
        delete right; right = new NodeLnk(*lnk_no.right);
    }

    return *this;
}

//Move assignment
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& lnk_no) noexcept {
    std::swap(info, lnk_no.info);
    std::swap(left, lnk_no.left);
    std::swap(right, lnk_no.right);
    return *this;
}

//left node
template <typename Data>
const BinaryTreeLnk<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const 
{
    if(left == nullptr)
    {
        throw std::out_of_range("il figlio sinistro non esiste"); 
    } 
    else 
    {
        return *left;
    }
}


template <typename Data>
BinaryTreeLnk<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::LeftChild() 
{
    if(left == nullptr)
    {
        throw std::out_of_range("il figlio sinistro non esiste"); 
    } 
    else 
    {
        return *left;
    }
}

//Rightchild node 
template <typename Data>
const BinaryTreeLnk<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const
{
    if(right == nullptr) 
    {
        throw std::out_of_range("il figlio destro non esiste");
    } 
    else 
    {
        return *right;
    }
}


template <typename Data>
BinaryTreeLnk<Data>::MutableNode & BinaryTreeLnk<Data>::NodeLnk::RightChild()  
{
    if(right == nullptr) 
    {
        throw std::out_of_range("il figlio destro non esiste");
    } 
    else 
    {
        return *right;
    }
}

//Binary function lnk node

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> & trav_con) {

    size = trav_con.Size();
    QueueVec<NodeLnk**> q;
    q.Enqueue(&root);

    trav_con.Traverse([&q](const Data& dat_i) {
        NodeLnk* &tempor = *q.HeadNDequeue();

        tempor = new NodeLnk(dat_i);

        q.Enqueue(&tempor->left);
        q.Enqueue(&tempor->right);
    });
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> && map_con) {

    size = map_con.Size();
    QueueVec<NodeLnk**> q;

    q.Enqueue(&root);

    map_con.Map([&q](const Data& dat_i) {
        NodeLnk*& tempor = *q.HeadNDequeue();
        tempor = new NodeLnk(std::move(dat_i));
        q.Enqueue(&tempor->left);
        q.Enqueue(&tempor->right);
    });
}

//Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& alber_lnk) noexcept {

    std::swap(size, alber_lnk.size);
    std::swap(root, alber_lnk.root);
}

//Copy assignment
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& alber_lnk)
{

  if(alber_lnk.Size() <= 0)
  {
    Clear();
  } 
  else 
  {
    BinaryTreeLnk<Data>* tempor = new BinaryTreeLnk<Data>(alber_lnk);
    std::swap(*this, *tempor);
    delete tempor; 
  }

  return *this;
}

//Move assignment
template<typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& alber_lnk) noexcept
{
  std::swap(root, alber_lnk.root);
  std::swap(size, alber_lnk.size);
  return *this;
}


//Root
template <typename Data>
const typename BinaryTree<Data>::Node & BinaryTreeLnk<Data>::Root() const 
{
    if(root == nullptr) 
    {
        throw std::length_error("l'albero e' vuoto!");
    } 
    else 
    {
        return *root;
    }
}

//Root mutable 
template <typename Data>
typename MutableBinaryTree<Data>::MutableNode & BinaryTreeLnk<Data>::Root() 
{
    if(root == nullptr) 
    {
        throw std::length_error("l'albero e' vuoto!");
    } 
    else 
    {
        return *root;
    }
}

/*
//Root mutable 
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root_lnk() 
{
    if(root == nullptr) 
    {
        throw std::length_error("l'albero e' vuoto!");
    } 
    else 
    {
        return *root;
    }
}
*/

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::alb_same(NodeLnk* lnk_no)
{
    NodeLnk* tempor = new NodeLnk();
    tempor->info = lnk_no->Element();
    if(lnk_no->HasLeftChild())
      tempor -> left = alb_same (lnk_no -> left);
    else
      tempor->left = nullptr;

    if(lnk_no->HasRightChild())
      tempor -> right = alb_same (lnk_no-> right);
    else
      tempor->right = nullptr;

    return tempor;
}



}