/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.cc to edit this template
 */

#include <iostream>
#include"Point2D.h"

using namespace std;

    Point2D::Point2D() {
        px = py = 0;
    }
    
    Point2D::Point2D(int x, int y) {
        px = x;
        py = y;
    }
    
    void Point2D::setX(int px) {
        this->px = px;
    }
    
    void Point2D::setY(int py) {
        this->py = py;
    }
    
    int Point2D::getX() const {
        return px;
    }

    int Point2D::getY() const {
        return py;
    }
    
    void Point2D::read() {
        cin >> px >> py;
    }
    
    void Point2D::print() const {
        cout << "("<<px << "," << py<<")";
    }