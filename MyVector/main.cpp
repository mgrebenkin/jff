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
    Vector3 x1(1,1,1, "Ones"), x2(2,2,2, "Twos"), x5(3,3,3, "Threes");
    Vector3 x3(x1);
    Vector3 x4(x2);
    MyVector<Vector3> c(3);
    MyVector<Vector3> d;
    c.push_back(x1); c.push_back(x2);c.push_back(Vector3(5,5,5, "Fives"));
    d = c;
    c.append(d);
    c.EmplaceBack(6,6,6, "Sixes");
    c.EmplaceBack();
    print_vector(c);
    
    return 0;
}
