/**  @file curves.h
*    @brief Classes prototypes for the half year project.
*    
*    This contains patterns of classes which represent conic sections.
*    
*    Conpleting date: 18.11.2022
*    
*
*    @author Mandrenko Olexander
*    @bug No known bugs.
*/




#ifndef CURVES_H
#define CURVES_H

///include files go here

#include <iostream>
#include <fstream>
#include <ostream> 
#include <math.h>
#include <cmath>
#include <stdexcept>

#define EPS 0.0000001
#define EPS_1 0.01

using namespace std;


/// Struct Point(just for convenience) declaration goes here
struct Point {
    double x, y;
};


/// Class Ellipse declaration goes here
class Ellipse {

private:
    Point verteces[4];
    Point focus_1;
    Point focus_2;
    double rx, 
           ry;
    Point center;
    
    double newton_raphson(Ellipse ellipse, double x2, int mode);
    /**  @brief numerical method for finding intersection points of two ellipses
    *    
    *    Algorithm is modified by the author for the current task
    *    It contain also numerical method to find derivative.
    *    This method solves all 4 possible equations to find ellipses intersection
    *    
    *
    *    @param ellipse another ellipse 
    *    @param x2 start point of algorithm
    *    @param mode switcher between different equations of ellipses
    *    @return The pointer to the first element of list of 4 Points.
    */
        
    void calc_center();
    /** @brief find coordinates of the center if verteces is given
    */
    
    double get_length(Point a, Point b);
    
    void calc_center_2();    
    /** @brief find coordinates of the center if focuses is given
    */
    
    void check_ellipse();
    /** @brief check whether input figure is exactly ellipse and whether 
    *   @throw axises of ellipse is parallel to Ox/Oy -- if not raise logic_error
    */

    void init(Point array[4]);
   
    void init(Point f_1, Point f_2, double rx, double ry);
    
public:
    
    Ellipse() {};
    Ellipse(Point array[4]) { init(array); }
    Ellipse(Point f_1, Point f_2, double rx, double ry){ init(f_1, f_2, rx, ry); }
    
    
    Point get_center();
    /** @brief get coordinates of the center of the ellipse
    */
    
    Point * get_focuses();
    /** @brief get coordinates of foci(2) of the ellipse
    */
    
    
    Point * get_vertices();
    /** @brief get coordinates of all verteces of the ellipse
    */
    
    double get_rx();
    /** @brief get Ox axis radius of the ellipse
    */
    
    double get_ry();    
    /** @brief get Oy axis radius of the ellipse
    */
    
    int is_inside(Point a);
    /**  @brief check whether Point lays inside the ellipse
    *    
    *    @param point for checking
    *    @return 1 -- if it lays inside | unless -- 0
    */
    
   
    double get_square();
    /** @brief get square of the ellipse
    */
    
    void input(istream& inp = cin);
    /** @brief method to set up an ellipse
    *
    *    There are two ways of setting up an ellipse:
    *      1. with coordinates of all verteces
    *      2. with coordinates of foci and lengths of rasiuses
    *    It is possible to load data from a file but 
    *    you should set up ifstream before and make txt file like that:
    *    
    *    /way of setting up
    *    /consecutively in a new line one number depending on the input method
    *    @param inp input stream (cin by default)
    */
    
    void print(ostream& out = cout);
    /** @brief print ellipse to the output stream
    *
    *    @param out output stream(cout by default)
    */

    double get_value(double x, int sign = 1);
    /**  @brief get value of an ellipse func
    *
    *    As for every x in ellipse there are 2 y,
    *    there is sign parameter in the method
    *
    *    @param x f(x)
    *    @param sign f(x) = +- y
    *    @return value of function f(x)
    */

    Point * intersection(double m, double c);
    /** @brief intersection with the line y = mx+c
    *
    *    Intersection points found analytically
    *    @throw If there are not intersection points throw logic_error
    *
    *    @param m angle koeficient of the line
    *    @param c movement of the line 
    *    @return pointer to Point array with two elements
    */
    
    Point * intersection(Ellipse ellipse);
    /** @brief intersection with another ellipse
    *
    *    Intersection points found numerically
    *    @throw If there are not intersection points throw logic_error
    *
    *    @param ellipse another ellipse object
    *    @return pointer to Point array with 4 elements
    */
};




class Parabola{

private:
    double equation[3];
    
    
    void init(double array[3]);
        
public:
    
    
    Parabola() {}
    Parabola(double array[3]) { init(array); }
    
    double get_a();
    
    double get_b();

    double get_c();    

    double get_value(double x); 

    Point get_focus();
    /** @brief calculating focus point of parabola
    */
    
    void input(istream& inp = cin);
    
    void print(ostream& out = cout);
    
    int check_point(Point point);
    /**  @brief check whether Point lays inside the parabola
    *    
    *    @param point for checking
    *    @return 1 -- if it lays inside | unless -- 0
    */
    
    Point * intersection(double k, double m);
    /** @brief intersection with the line y = mx+c
    *
    *    Intersection points found analytically
    *    @throw If there are not intersection points throw logic_error
    *
    *    @param m angle koeficient of the line
    *    @param c movement of the line 
    *    @return pointer to Point array with two elements
    */
    
    Point * intersection(Parabola other);    
    /** @brief intersection with another parabola
    *
    *    Intersection points found analytically
    *    @throw If there are not intersection points throw logic_error
    *
    *    @param other parabola object for checking intersection 
    *    @return pointer to Point array with two elements
    */
        
    double intersection_square(double k, double m);
    /** @brief square of intersection with line y = kx+m
    *
    *    Intersection points and square found analytically
    *    @throw If there are not intersection points throw logic_error
    *
    *    @param other parabola object for checking intersection 
    *    @return double value of square
    */
    
    double intersection_square(Parabola other);    
    /** @brief square of intersection with another parabola
    *
    *    Intersection points and square found analytically
    *    @throw If there are not intersection points throw logic_error
    *
    *    @param other parabola object for checking intersection 
    *    @return double value of square
    */    

};





class Hyperbole {
    
private:
    
    double equation[5];           // x_center, y_center, a, b
    
    void init(double array[5]);

    
    double newton_raphson(Hyperbole hyperbole, double x2, int mode);
    /**  @brief numerical method for finding intersection points of parabola and hyperbole
ellipses    *    
    *    Algorithm is modified by the author for the current task
    *    It contain also numerical method to find derivative.
    *    This method solves all 4 possible equations to find ellipses intersection
    *    
    *
    *    @param hyperbole with which intersects 
    *    @param x2 start point of algorithm
    *    @param mode switcher between different equations of ellipses
    *    @return The pointer to the first element of list of 4 Points.
    */


    double newton_raphson(Parabola parabola, double x2, int mode);
            

public: 
    Hyperbole(){}
    Hyperbole(double array[5]){init(array);}
    
    double get_x0();

    double get_y0();
    
    double get_a();

    double get_b();
   
    void input(istream& inp = cin);
    
    void print(ostream& out = cout);
    
    
    Point * get_foci();
    
        
    bool check_point(Point point);
    /**  @brief check whether Point lays inside the hyperbola
    *    
    *    @param point for checking
    *    @return 1 -- if it lays inside | unless -- 0
    */
    
    double get_value(double x, int sign = 1);
    
    
    Point * intersection(Hyperbole hyperbole);
    /** same as for previous sections 
    */ 
    
    Point * intersection(Parabola parabola);
};


#endif
