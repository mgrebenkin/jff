//
//  main.cpp
//  MyVector
//
//  Created by Михаил Гребенкин on 20.09.2020.
//  Copyright © 2020 Michael Grebenkin. All rights reserved.
//

#include <iostream>
#include "MyVector.h"
struct Vector3{
    float x;
    float y;
    float z;
    std::string name;
    Vector3():x(0), y(0), z(0), name("No name"){
        std::cout<<"Vector3 Constructed no args\n";
    }
    Vector3(float ax, float ay, float az):
    name("No name"){
        x = ax;
        y = ay;
        z = az;
        std::cout<<"Vector3 Constructed with args but no name\n";
    }
    Vector3(float ax, float ay, float az, std::string aname){
        x = ax;
        y = ay;
        z = az;
        name = aname;
        std::cout<<"Vector3 Constructed with args\n";
    }
    
    Vector3(const Vector3& other):
    x(other.x), y(other.y), z(other.z), name(other.name){
        std::cout<<"Vector3 Copied\n";
    }
    Vector3(Vector3&& other):
    x(other.x), y(other.y), z(other.z){
        name = std::move(other.name);
        std::cout<<"Vector3 Moved\n";
    }
    Vector3& operator=(const Vector3& other ){
        x = other.x;
        y = other.y;
        z = other.z;
        name = other.name;
        std::cout<<"Vector3 Copy = operator\n";
        return *this;
    }
    Vector3& operator=(Vector3&& other){
        x = other.x;
        y = other.y;
        z = other.z;
        name = std::move(other.name);
        std::cout<<"Vector3 Move = operator\n";
        return *this;
    }
    void print(){
        std::cout<<"Vector3 name:"<<name<<std::endl;
        std::cout<<":"<<x<<":"<<y<<":"<<z<<":"<<std::endl;
        std::cout<<"---------------"<<std::endl;
    }
};

void print_vector(const MyVector<Vector3>& v){
    for(std::size_t i = 0; i<v.get_size(); i++)
        v[i].print();
    std::cout<<"~~~~~~~~~~~~~~~~~~~"<<std::endl;
}

int main(int argc, const char * argv[]) {
    MyVector<int> vector;
    vector.EmplaceBack(1);
    vector.EmplaceBack(2);
    vector.EmplaceBack(3);
    vector.EmplaceBack(4);
    vector.EmplaceBack(5);
    
    for(auto element:vector){
        std::cout << element<<"   ";
    }
    std::cout << std::endl;
    
    for(MyVector<int>::Iterator it = vector.begin(); it != vector.end(); ++it){
        std::cout << *it << "   ";
    }
    std::cout << std::endl;
    MyVector<int>::Iterator it;
    for(int i = 0; i < vector.get_size(); i++){
        it = vector.begin();
        it+=i;
        std::cout << *it << "   ";
    }
    std::cout<<std::endl;
    
    for(int i = 0; i < vector.get_size(); i++){
        std::cout << *(vector.begin()+i) << "   ";
    }
    std::cout << std::endl;
    
    MyVector<int>::Iterator it1 = vector.begin();
    MyVector<int>::Iterator it2 = vector.end()-1;
    std::cout << it2 - it1 << std::endl;
    
    
    
    
    return 0;
}
