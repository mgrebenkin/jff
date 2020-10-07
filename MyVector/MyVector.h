//
//  MyVector.h
//  MyVector
//
//  Created by Михаил Гребенкин on 20.09.2020.
//  Copyright © 2020 Michael Grebenkin. All rights reserved.
//

#ifndef MyVector_h
#define MyVector_h

#define _BLOCK_SIZE 5
#define DBMSG(DBSTRING) (std::cout<<"|DBG: "<<(DBSTRING)<<"|\n")

template<typename T>
class MyVector{
public:
    MyVector():
    m_data(nullptr),
    m_size(0),
    m_blocks_amount(0),
    m_capacity(0){
    }
    MyVector(std::size_t count):
    m_data(nullptr), m_size(0), m_capacity(0), m_blocks_amount(0){
        allocate(blocks_in_size(count));
    }
    
    MyVector(const MyVector& other):
    m_data(nullptr), m_size(other.m_size), m_blocks_amount(0), m_capacity(0){
        allocate(other.m_blocks_amount);
        for(size_t i = 0; i < other.size(); i++){
            m_data[i] = other.m_data[i];
        }
    }
    
    MyVector(MyVector&& other):
    m_data(other.m_data), m_blocks_amount(other.m_blocks_amount), m_capacity(other.m_capacity){
        other.m_data = nullptr;
        other.m_blocks_amount = 0;
        other.m_capacity = 0;
        other.m_size = 0;
    }
    ~MyVector(){
        Clear();
        ::operator delete(m_data, m_capacity*sizeof(T));
    }
    void Clear(){
        for (int i = 0; i< m_size; i++){
            m_data[i].~T();
        }
        m_size = 0;
    }
    T& operator[](std::size_t pos){
        return m_data[pos];
    }
    T& operator[](std::size_t pos) const{
        return m_data[pos];
    }
    
    std::size_t get_size() const {return m_size;}
    
    T& pop_back(){
        if(m_size > 0){
            m_size--;
            return m_data[m_size];
            
        }
    }
    void push_back(const T& elem){
        if(m_size>=m_capacity) allocate(1);
        m_data[m_size] = elem;
        m_size++;
        DBMSG("Copy pushed");
    }
    void push_back(T&& elem){
        if(m_size>=m_capacity) allocate(1);
        m_data[m_size] = std::move(elem);
        m_size++;
        DBMSG("Move pushed");
    }
    
    template<typename... Args>
    T& EmplaceBack(Args&&... args){
        if(m_size == m_capacity) allocate(1);
        new(&m_data[m_size]) T(std::forward<Args>(args)...);
        m_size++;
        return m_data[m_size-1];
    }
    MyVector& operator=(const MyVector& other){
        Clear();
        if(m_capacity<other.m_size) allocate(blocks_in_size(other.m_size - m_capacity));
        for(size_t i = 0; i<other.m_size; i++)
            m_data[i] = other.m_data[i];
        m_size = other.m_size;
        DBMSG("Copy = operator ");
        return *this;
    }
    MyVector& operator=(MyVector&& other){
        Clear();
        allocate(-m_blocks_amount);
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_blocks_amount = other.m_blocks_amount;
        other.m_size = 0;
        other.m_blocks_amount = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
        DBMSG("Move = operator");
        return *this;
    }
    MyVector<T>& append(const MyVector& other){
        if(m_size+other.m_size>m_capacity)
            allocate(blocks_in_size(m_size + other.m_size - m_capacity));
        for(size_t i = 0; i<other.m_size; i++) m_data[m_size+i] = other.m_data[i];
        this->m_size+=other.m_size;
        return *this;
    }
private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_blocks_amount;
    std::size_t m_capacity;
    void allocate(long long blocks){
        if(m_blocks_amount + blocks<=0){
            ::operator delete(m_data, m_capacity*sizeof(T));
            m_blocks_amount = 0;
            m_size = 0;
            m_capacity = 0;
            return;
        } else {
            m_blocks_amount +=blocks;
            size_t prev_capacity = m_capacity;
            m_capacity = m_blocks_amount*_BLOCK_SIZE;
            T* new_data = (T*)::operator new(m_capacity*sizeof(T));
            m_size = m_size<=m_capacity?m_size:m_capacity;
            for(size_t i = 0; i<m_size; i++)
                new_data[i] = std::move(m_data[i]);
            if(m_data != nullptr){
                ::operator delete(m_data, prev_capacity*sizeof(T));
            }
            m_data = new_data;
            return;
        }
        
        
    }
    static size_t blocks_in_size(size_t size){
        return size/_BLOCK_SIZE + size%_BLOCK_SIZE?1:0;
    }
};


#endif /* MyVector_h */
