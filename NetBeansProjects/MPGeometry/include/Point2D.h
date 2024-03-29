/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   Point2D.h
 * Author: adolfo
 *
 * Created on February 26, 2024, 12:28 PM
 */

#ifndef POINT2D_H
#define POINT2D_H
    

/**
 * @class Point2D
 * @brief To represent a point in a two-dimensional space
 */
class Point2D {
private:
    double px, py; ///< Coordinates of the point
public:
    /**
     * @brief Basic constructor
     */
    Point2D();
    /**
     * @brief Constructor with initialization parameters
     * @param x Coordinate
     * @param y Coordinate
     */
    Point2D(int x, int y);
    /**
     * @brief Initializes the X coordinate
     * @param px New value for X
     */
    void setX(int px);
    /**
     * @brief Initializes the Y coordinate
     * @param py New value for Y
     */
    void setY(int py);
    /**
     * @brief Queries the X coordinate
     * @return Value of X
     */
    int getX() const;
    /**
     * @brief Queries the Y coordinate
     * @return Value of Y
     */
    int getY() const;
    /**
     * @brief Reads the XY value from keyboard
     */
    void read();
    /**
     * @brief Prints the XY values in the screen  in the form (X,Y)
     */
    void print() const;
};



#endif /* POINT2D_H */

