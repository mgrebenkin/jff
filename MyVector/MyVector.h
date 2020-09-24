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
    m_blocks_amount(0){
        //resize();
    }
    MyVector(std::size_t count):
    m_data(nullptr){
        m_size = count;
        resize();

    }//                                                    |1 1 1 1 1 | o o o o o| o o o o o |
    ~MyVector(){
        delete[] m_data;
    }
    T& operator[](std::size_t pos){
        return m_data[pos];
    }
    std::size_t get_size(){return m_size;}
    void pop_back(){
        if(m_size > 0){
            m_size--;
            resize();
        }
    }
    void push_back(const T& elem){
        m_size++;
        resize();
        m_data[m_size-1] = elem;
    }
    void printout(){
        if(m_size>0){
            std::cout<<"|";
            for(int i = 0; i<m_size; i++){
                std::cout<<m_data[i]<<"|";
            }
        }else std::cout<<"Empty";
        std::cout<<std::endl;
    }
    MyVector& operator=(MyVector& other){
        this->m_size = other.m_size;
        resize();
        memcpy(this->m_data, other.m_data, sizeof(T)*other.m_size);
        return *this;
    }
    MyVector& operator=(MyVector&& other){
        if (this->m_data != nullptr) delete[] this->m_data;
        this->m_data = other.m_data;
        this->m_size = other.m_size;
        this->m_blocks_amount = other.m_blocks_amount;
        other.m_data = nullptr;
        other.m_size() = 0;
        other.m_blocks_amount = 0;
        return *this;
    }
    void append(MyVector& other){
        this->m_size+=other.m_size;
        resize();
        
    }
private:
    T* m_data;
    std::size_t m_size;
    std::size_t m_blocks_amount;
    bool resize(){
        if((m_blocks_amount*_BLOCK_SIZE>=m_size)&&
           (m_blocks_amount*_BLOCK_SIZE<m_size+_BLOCK_SIZE)){
            //DBMSG("Resize Check: did nothing");
            return false;
        }else{
            //DBMSG("Did resize from: "); DBMSG(m_blocks_amount);
            m_blocks_amount = (m_size/_BLOCK_SIZE) + (m_size%_BLOCK_SIZE?1:0);
            T* old_mem = m_data;
            m_data = new T[m_blocks_amount*_BLOCK_SIZE];
            if(old_mem != nullptr){
                memcpy(m_data, old_mem, sizeof(T)*m_size);
                delete[] old_mem;
            }
            //DBMSG("To"); DBMSG(m_blocks_amount);
            return true;
        }
    }
    
};


#endif /* MyVector_h */
