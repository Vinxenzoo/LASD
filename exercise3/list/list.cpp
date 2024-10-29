//Vincenzo Capasso N86004259

#include "list.hpp"
#include <cassert>

namespace lasd 
{
    //costruttori specifici
    //più esatto fare il move
    template<typename Data>
    List<Data> :: Node :: Node (Data && d) noexcept
    {
        std::swap(elem, d);
    }

    
    template<typename Data>
    List<Data> :: Node :: Node (Node && n) noexcept
    {
        std::swap(elem, n.elem);
        std::swap (next, n.next);
    }


    template<typename Data>
    List<Data> :: Node :: ~Node () 
    {
        delete next;
    }


/* ************************************************************************** */

//operatori di comparazione nodo

    template<typename Data>
    bool List<Data> :: Node :: operator==(const Node & n) const noexcept 
    {
        return (elem == n.elem) && (next == nullptr && n.next == nullptr) || (next != nullptr && n.next != nullptr);
    }

    template<typename Data>
    bool List<Data> :: Node :: operator!=(const Node & n) const noexcept 
    {
        return !(*this == n);
    }

/* ************************************************************************** */


    template<typename Data>
    typename List<Data> :: Node *  List<Data> :: Node :: Clone(Node * t)
    {
       if(next == nullptr)
       {
        return t;
       }
       else
       {
         Node * nod = new Node(elem);
         nod->next = next -> Clone(t);
         return nod;
       }
    }

/* ************************************************************************** */

    //implementazioni costruttori specifici di lista
    template<typename Data>
    List<Data> :: List(const TraversableContainer<Data> & c)
    {
        c.Traverse(
            [this] (const Data& d) {
                InsertAtBack(d);
            }
        );
    }

    template<typename Data>
    List<Data> :: List(MappableContainer<Data> && m)
    {
        std::cout<<"\n sono nel mappable di list. \n\n";
        m.Map(
            [this] (Data & d) {
                std::cout<<"\n sono nella. \n\n";
                InsertAtBack(std::move(d));
            }
        );
    }

/* ************************************************************************** */
    
    // costruttore di copia e move 
    template<typename Data>
    List<Data> :: List (const List<Data> & ls)

    {
        
        if(ls.tail != nullptr)
        {
            tail = new Node(*ls.tail);
            head = ls.head->Clone(tail);
            size = ls.size;
        }
        
    
    }

    template<typename Data>
    List<Data> :: List( List<Data> && ls) 
    {
        std::cout<<"\n\n sono nel move di lista: \n";
        std::swap (size, ls.size);
        std::swap (head, ls.head);
        std::swap (tail, ls.tail);
    
       
    }



/* ************************************************************************** */
    

    //Distruttore
    template <typename Data>
    List<Data> :: ~List()
    { 
        delete head;
        head = tail = nullptr;
        size =0;
    }


/* ****************************Copy assignement********************************************** */


   template< typename Data>
   List<Data> & List<Data> :: operator = (const List<Data> & ls)
   {
    /*
      if( size <= ls.size) 
      {
        if(tail != nullptr)
        {
            List<Data> *tls = new List(tls);
            std:: swap(*tls, *this);
            delete tls;
        }
        else
        {
            Node *o = ls.head;
            for (Node * n = head; n != nullptr; n = n-> next)
            {
                n->elem = o-> elem;
            }
            if (o != nullptr)
            {
                Node * newtail = new Node (*ls.tail);
                tail->next = o-> Clone(newtail);
                tail = newtail;
            }
        }

      }
      else
      {
        if(ls.tail == nullptr)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node * n = head;
        }
      }
      */
  
  Node * i = head;
  Node * src = ls.head;
  while( i != nullptr && src != nullptr)
  {
    i->elem = src->elem;
    i =i->next;
    src = src->next;
  }

  while (src == nullptr &&(size - ls.Size()) != 0) RemoveFromFront();
  while (src != nullptr && (size - ls.Size()) != 0) { InsertAtBack(src->elem); src = src->next;}
    return *this;
    }

   

   template< typename Data>
   List<Data> & List<Data> :: operator = (List<Data> && ls) noexcept
   {
      std:: swap (size, ls.size);
      std::swap(head, ls.head);
      std::swap (tail, ls.tail);
      return *this;
   }


   /* ************************************************************************** */
    
    
    template <typename Data>
    inline bool List<Data> :: operator ==(const List<Data> & ls) const noexcept
    {
        if(size != ls.size)
        {
            return false;
        }
        Node *at= head;
        Node *src = ls.head;

        while( at != nullptr && src != nullptr)
        {
            if(at->elem != src->elem)
            {
                return false;
            }

            at = at->next;
            src = src->next;
        }

        //assert (at == nullptr && src == nullptr);
        return true;
    }
   

    template <typename Data>
    inline bool List<Data> :: operator !=(const List<Data> & ls) const noexcept
    {
        return !(*this== ls);
    }
     
   /* ************************************************************************** */


   template<typename Data>
   void  List<Data>::InsertAtFront(const Data & d)
   {
     Node * begin = new Node(d);
     begin->next = head;
     head = begin;
     if(tail == nullptr)
     {
        tail = head;
     }

     ++size;
   }

   template<typename Data>
   void  List<Data>::InsertAtFront( Data && d)
   {
     Node * begin = new Node(std::move(d));
     begin->next = head;
     head = begin;
     if(tail == nullptr)
     {
        tail = head;
     }

     ++size;
   }

   template<typename Data>
   void List<Data> :: RemoveFromFront()
   {
      if(head != nullptr)
      {
        Node * f = head;
        if(tail == head)
         {
            tail = head = nullptr;
         }
         else
         {
            head = head->next;
         }

         --size;
         f->next = nullptr;
         delete f;
      }
      else
      {
        throw std::length_error(" si sta provando ad accedere ad una lista vuota");
      }
      
   }

   template<typename Data>
   Data List<Data> :: FrontNRemove()
   {
      if(head != nullptr)
      {
        Node * f = head;
        if(tail == head)
        {
           tail = head = nullptr;
        }
        else
        {
            head = head->next;
        }
        --size; 
        f->next =nullptr;
        Data d(std::move(f->elem));
        delete f;
        return d;
      }
      else
      {
        throw std::length_error(" stai provando ad accedere ad una lista vuota. ");
      }
   }

   template <typename Data>
   void List<Data> :: InsertAtBack(const Data & d)
   {
     Node * finel = new Node(d);
     if(tail ==nullptr)
     {
        head = finel;
     }
     else
     {
        tail->next = finel;
     }

     tail = finel;
     ++size;
   }

    template <typename Data>
   void List<Data> :: InsertAtBack( Data && d)
   {
     Node * finel = new Node(std::move(d));
     if(tail ==nullptr)
     {
        head = finel;
     }
     else
     {
        tail->next = finel;
     }

     tail = finel;
     ++size;
   }



   /* ************************************************************************** */

   template<typename Data>
   void List<Data>:: Clear()
   {
     delete head;
     head = tail = nullptr;
     size = 0;
   }

  /* ************************************************************************** */

   template< typename Data>
   bool List<Data> ::Insert(const Data & dato_da_v)
   {
    
      for (Node * c= head; c != nullptr; c= c->next)
      {
         if(c->elem == dato_da_v)
         {
            return false;
         }
      }
      InsertAtBack(dato_da_v);
      return true;
      


   }

     template< typename Data>
   bool List<Data> ::Insert( Data && dato_da_v)
   {
    
      for (Node * c= head; c != nullptr; c= c->next)
      {
         if(c->elem == dato_da_v)
         {
            return false;
         }
      }
      InsertAtBack(std::move(dato_da_v));
      return true;
      

   }

   template< typename Data>
   bool List<Data> ::Remove(const Data & dato_da_v)
   {
      if(!size)
      {
        return false;
      }

      if(head->elem == dato_da_v)
      {
        RemoveFromFront();
        return true;
      }

      Node *t {head->next}, *s{head};

      while( t!= nullptr)
      {
        if(t->elem == dato_da_v)
        {
          s->next = t->next;
          t->next ? t->next = nullptr : tail = s;
          delete t;
          --size;
          return true;
        }

        s=t;
        t= t->next;
        
      }
      return false;

   } 
   

     /* ************************************************************************** */

     template< typename Data>
     const Data & List<Data> :: operator[](const ulong i) const
     {
        if( i < size)
        {
            Node *c = head;
            for (ulong in =0; in < i; ++in, c = c->next){}
            
                 return c->elem;
            
        }
        else
        {
            throw std::out_of_range(" l'indice che hai messo è troppo grande ");
        }
     }

     template< typename Data>
      Data & List<Data> :: operator[](const ulong i)
     {
        if( i < size)
        {
            Node *c = head;
            for (ulong in =0; in < i; ++in, c = c->next){}
            
                 return c->elem;
            
        }
        else
        {
            throw std::out_of_range(" l'indice che hai messo è troppo grande ");
        }
     }

     template <typename Data>
     const Data & List<Data> :: Front () const
     {
        if(head != nullptr)
        {
            return head->elem;
        }
        else
        {
            throw std::length_error( "accesso ad una lista vuota ");
        }
     }

      template <typename Data>
      Data & List<Data> :: Front () 
     {
        if(head != nullptr)
        {
            return head->elem;
        }
        else
        {
            throw std::length_error( "accesso ad una lista vuota ");
        }
     }

      template <typename Data>
     const Data & List<Data> :: Back () const
     {
        if(tail != nullptr)
        {
            return tail->elem;
        }
        else
        {
            throw std::length_error( "accesso ad una lista vuota ");
        }
     }
    
      template <typename Data>
      Data & List<Data> :: Back () 
     {
        if(tail != nullptr)
        {
            return tail->elem;
        }
        else
        {
            throw std::length_error( "accesso ad una lista vuota ");
        }
     }


/* ************************************************************************** */

//override delle funzioni traverse che chiamano quelle ausiliarie

template <typename Data>
 void List<Data> :: Traverse(TraverseFun fun) const 
{
    PreOrderTraverse(fun);
}

template <typename Data>
inline void List<Data> :: PreOrderTraverse(TraverseFun fun) const 
{
    PreOrderTraverse(fun, head);
}

template <typename Data>
inline void List<Data> :: PostOrderTraverse(TraverseFun fun) const 
{
    PostOrderTraverse(fun, head);
}

/* ************************************************************************** */


//override delle funzioni map  che chiamano quelle ausiliarie
template <typename Data>
 void List<Data> :: Map(MapFun fun) 
{
    PreOrderMap(fun);
}

template <typename Data>
 void List<Data> :: PreOrderMap(MapFun fun) 
{
    PreOrderMap(fun, head);
}

template <typename Data>
 void List<Data> :: PostOrderMap(MapFun fun) 
{
    PostOrderMap(fun, head);
}

/* ************************************************************************** */

//funzioni ausiliarie per attraversamento lista (overloading)

template <typename Data>
inline void List<Data> :: PreOrderTraverse(TraverseFun fun,const Node * c) const 
{
    /*
    for(; c !=nullptr; c = c->next)
    {
        fun(c->elem);
    }
   */
    
   /*
    if(c != nullptr)
    {
       
       fun(c->elem);
        PreOrderTraverse(fun, c->next);
       
    }
    */

    if(!c)
    return;

    fun(c->elem);
    PreOrderTraverse(fun, c->next);
}

template <typename Data>
inline void List<Data> :: PostOrderTraverse(TraverseFun fun ,const Node * c) const 
{
     if(c != nullptr)
    {
        PostOrderTraverse(fun, c->next);
        fun(c->elem);
    }
}


/* ************************************************************************** */


//funzioni ausiliarie per Mappatura lista (overloading)
template <typename Data>
 void List<Data> :: PreOrderMap(MapFun fun, Node * c) 
{
    for(; c !=nullptr; c = c->next)
    {
        fun(c->elem);
    }
}

template <typename Data>
 void List<Data> :: PostOrderMap(MapFun fun, Node * c) 
{
    if(c != nullptr)
    {
        PostOrderMap(fun, c->next);
        fun(c->elem);
    }
}
}
