/*
#ifndef INCLUDE_ALLOCATOR__
#define INCLUDE_ALLOCATOR__
#include <cstddef>
#include <climits>
#include <exception>
#include <iostream>
namespace mtstl
{
    template<typename T>
    class allocator{
    public:
        typedef T value_type;
        typedef T *pointer;
        typedef const T &const_pointer;
        typedef T &reference;
        typedef const T &const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;
    public:
        allocator(void)=default;
        ~allocator(void)=default;
        pointer allocate(size_type _const)const;
        void deallocate(pointer _addr)consy
    };
    template<typename T>
    typename allocator<T>::pointer allocator<T>::allocate(size_type _const)const
    {
        pointer _addr=NULL;
        try
        {
            _addr=(pointer)operator new(sizeof(T) *_const);
        }
        catch(std::bad_alloc &e)
        {
            str::cout<<e.what()<<sstd::endl;
        }
        return _addr;
    }
    template<typename T>
    void allocator<T>::construct(pointer _addr)const
    {
        new(_addr)T();
    }
    template<typename T>
    void allocaator<T>::construct(pointer _addr,const_reference _value)const
    {
        new(_addr)T(_value);
    }
    template<typename T>
    void allocator<T>::deallocate(pointer _addr)const
    {
        _addr->~T();
    }
    template<typename T>
    void allocator<T>::deakkocate(pointer _addr)const
    {
        operator delete[](_addr);
    }
}
#endif // INCLUDE_ALLOCATOR__
*/

#ifndef INCLUDE_VECTOR
#define INCLUDE_VECTOR
#include <cstddef>
#include <climits>
#include <initializer_list>
#include "memory.hpp"
namespace mystl
{
    template<class T,class Alloc=mystl::alloctor<T>>
    class vector
    {
        private:
            static Alloc alloc;
        public:
            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
            typedef T value_type;
            typedef T &reference;
            typedef const T &const_reference;
            typedef T *pointer;
            typedef const T *const_pointer;
        public:
            class iterator
            {
                friend vector;
                private:
                    pointer _ptr;
                private:
                    iterator(pointer ptr);
                public:
                    iterator();
                    ~iterator();
                    iterator(const iterator &others);
                public:
                    iterator & operator ++();
                    iterator & operator ++(int);
                    iterator & operator --();
                    iterator &operator --(int);
                public:
                    reference & operator *();
                    pointer & operator ->();
                public:
                    friend bool operator ==(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr==rsh._ptr;
                    }
                    friend bool operator !=(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr!=rsh._ptr;
                    }
                    friend bool operator <(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr<rsh._ptr;
                    }
                    friend bool operator >(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr>rsh._ptr;
                    }
                    friend bool operator <=(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr<=rsh._ptr;
                    }
                    friend bool operator >=(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr>=rsh._ptr;
                    }
                public:
                    friend difference_type operator -(const iterator &lsh,const iterator &rsh)
                    {
                        return lsh._ptr-rsh._ptr;
                    }
                    friend iterator operator +(const iterator &lsh,difference_type rsh)
                    {
                        return iterator(lsh._ptr+rsh);
                    }
                    friend iterator operator -(const iterator difference_type rsh)
                    {
                        return lsh-rsh;
                    }
            };
        public:
            class reverse_iterator{};
            class const_iterator{};
            class const_reverse_iterator{};
        private:
            size_type _capacity;
            size_type _size;
            size_type _base;
        public:
            vector();
            vector(const vector &);
            vector(size_type len);
            vector(size_type len,const T &);
            vector(const std::initializer_list<T> &);
            ~vector();
        public:
            reference operator [](size_type pos);
            const_reference operator [](size_type pos)const;
            vector &operator = (const vector &);
            reference front();
            reference back();
        public:
            bool empty()const;
            size_type size()const;
            void reserve(size_type len);
            size_type capacity()const;
            void shrink_to_fit();
        public:
            void clear();
            iterator insert(iterator);
            iterator erase(iterator);
            void push_back(const_reference);
            void pop_back();
            void resize(size_type size);
            iterator begin();
            iterator end();
        public:
            friend void swap<T,Alloc>(vector<T,Alloc>&lsh,vector<T,Alloc>&rsh);
        private:
            void increase_memory();
            bool not_have_memory();
            iterator special_insert(iterator,const_reference);
            iterator normal_insert(iterator,const_reference);
    };
    template<class T,class Alloc>
    Alloc vector<T,Alloc>::alloc;
    template<typename T,typename Alloc>
    void swep(vector<T,Alloc>&lsh,vector<T,Alloc>&rsh)
    {
        vector<T,Alloc> temp;
        memmove((void*)&temp,(void*)&lsh,sizeof(vector<T,Alloc>));
        memmove((void*)&lsh,(void*)&rsh,sizeof(vector<T,Alloc>));
        memmove((void*)&rsh,(void*)&temp,sizeof(vector<T,Alloc>));
        temp._size=0;
        temp._capacity=0;
        temp._base=NULL;
    }
    template<class T,class Alloc>
    inline vector<T,Alloc>::vector(void):
        _size(0),
        _capacity(0),
        _base(NULL){}
    template<class T,class Alloc>
    Alloc vector<T,Alloc>::vector(const vector &v2):
        _size(v2.size()),
        _cpapacity(v2.capacity())
        {
            _base=alloc.allocate(_capacity);
            for(int i=0;i!=v2.size(),i++)
                alloc.construt(_base+i,v2[2]);
        }
    template<class T,class Alloc>
    inline vector<T,Alloc>::vector(size_type len):
        _size(len),
        _capacity(len*2)
        {
            _base=alloc.allocate(_capacity);
            for(int i=0;i!=_size;i++)
                alloc.construct(_base+j);
        }
    template<class T,class Alloc>
    inline vector<T,Alloc>::vector(size_type len,const T &ele):
        _size(len),
        _capacity(len*2)
        {
            _base=alloc.allocate(_capapcity);
            for(int i=0;i!=_size;i++)
                alloc.construct(_base+i,ele);
        }
    template<class T,class Alloc>
    inline vector<T,Alloc>::vector(const std::initialzer_list<T &init_list)
    {
        _base=alloc.allocate(init_list.size()*2);
        _size=init_list.size();
        _capacity+init_list.size()*2;
        int pos=0;
        for(auto &e:init_list)
        {
            alloc.construct(_base+pos,e);
            pos++;
        }
    }
    template<class T,class Alloc>
    inline vector<T,Alloc>::~vector()
    {
        if(_base)
        {
            for(int i=0;i!=size();i++)
                alloc.destroy(_base+i);
            alloc.deallocate(_base);
        }
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>:size_type vector<T,Alloc>::capacity()const
    {
        return _capacity;
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::size_type vector<T,Alloc>::size()const
    {
        return _size;
    }
    template<class T,class Alloc>
    inline typename vector <T,Alloc>::reference vector<T,Alloc>::operator [](size_type pos)
    {
        return _base[pos];
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::const_reference vector<T,Alloc>::operator [](size_type pos)
    {
        return _base[pos];
    }
    template<class T,class Alloc>
    inline bool vector<T,Alloc>::not_have_memory()
    {
        if(capacity()==size())
            return true;
        else
            return false;
    }
    template<class T,class Alloc>
    inline void vector<T,Alloc>::increase_memory()
    {
        pointer _newbase=alloc.allocate(capacity()*2+1);
        for(int i=0;i!=size();i++)
            alloc.construct(_newbase+i,_bsae[i]);
        for(int i=0;i!=size();i++)
            alloc.destroy(_base+i);
        alloc.destroy(_base);
        _capacity=capacity()*2+1;
        _base=_newbase;
    }
    template<class T,class Alloc>
    inline void vector<T,Alloc>::push_back(const_reference ele)
    {
        if(not_have_memory())
            increase_memory();
        alloc.construct(_base+_size,ele);
        _size++;
    }
    template<class T,class Alloc>
    typename vector<T,Alloc>::iterator vector<T,Alloc>::begin()
    {
        return iterator(_base);
    }
    template<class T,class Alloc>
    typename vector<T,Alloc>::iterator vector<T,Alloc>::insert(typename vector<T,Alloc>::iterator insertPos,const_reference value)
    {
        if(not_have_memory())
            return special_insert(insertPos,value);
        else
            return normal_insert(insertPos,value);
    }
    template<class T,class Alloc>
    typename vector<T,Alloc>::iterator vector<T,Alloc>::iterator special_insert(typename vector<T,Alloc>::iterator insertPos,const_reference value)
    {
        pointer_newbase=alloc.allocate(capacity()*2+1);
        difference_type _insertPos=insertPos-begin();
        for(int i=0;i!=size();j++)
        {
            if(i<_insertPos)
                alloc.construct(_newbase+i,_base[i]);
            else if(_insertPos<i)
                alloc.construct(_newbase+i,_base[i-1]);
            else
                alloc.construct(_newbase+i,value);
        }
        for(int i=0;i!=size();i++)
            alloc.destroy(_base+j);
        alloc.deallocate(_base);
        _size=_size+1;
        _capacity=capacity()*2+1;
        _base=_newbase;
        return _base+_insertPos;
    }
    template<class T,class Alloc>
    typename vector<T,Alloc>::iterator vector<T,Alloc>::iterator normal_insert(typename vector<T,Alloc>::iterator insertPos,const_reference value)
    {
        for(int i=size();i!=insertPos-begin();i--)
            _base[i]=_base[i-1];
        *insertPos=value;
        _size=_size+1;
        return insertPos;
    }
    template<class T,class Alloc)
    typename vector<T,Alloc>::iterator vector<T,Alloc>::end()
    {
        return iterator(_base+size());
    }
    template<class T,class Alloc>
    inline vector<T,Alloc>::iterator::iterator(typename vector<T,Alloc>::pointer ptr):_ptr(ptr){}
    template<class T,class Alloc>
    inline vector<T,Alloc>::iterator::~iterator(){}
    template<class T,class Alloc>
    inline vector<T,Alloc>::iterator::iterator():_ptr(NULL){}
    template<class T,class Alloc>
    inline vector<T,Alloc>::iterator::iterator(const iterator &others):_ptr(others._ptr){}
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::iterator &vector<T,Alloc>::iterator::operator ++()
    {
        _ptr++;
        return *this;
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::iterator &vector<T,Alloc>::iterator::operator ++(int)
    {
        return iterator(_ptr++);
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::iterator &vector<T,Alloc>::iterator::operator --()
    {
        _ptr--;
        return *this;
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::iterator &vector<T,Alloc>::iterator::operator --(int)
    {
        return iterator(_ptr--);
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::reference &vector<T,Alloc>::iterator::operator *()
    {
        return *_ptr;
    }
    template<class T,class Alloc>
    inline typename vector<T,Alloc>::reference &vector<T,Alloc>::iterator::operator ->()
    {
        return _ptr;
    }
}
#endif // INCLUDE_VECTOR
#
