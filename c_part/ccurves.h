#ifndef CCURVES_H
#define CCURVES_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPS 0.0000001
#define EPS_1 0.0001


struct Point {
    double x, y;
};

typedef struct Point Point;


struct Ellipse{
    Point verteces[4];
    Point focus_1;
    Point focus_2;
    double rx, 
           ry;
    Point center;
};


typedef struct Ellipse Ellipse;


struct Parabola {
  
    double equation[3];
      
};

typedef struct Parabola Parabola;

struct Hyperbole{

    double equation[5];           // x_center, y_center, a, b, r

};

typedef struct Hyperbole Hyperbole;






void parabola_init(Parabola parabola, double array[3]);

double parabola_get_a(Parabola parabola);

double parabola_get_b(Parabola parabola);

double parabola_get_c(Parabola parabola);

double parabola_get_value(Parabola parabola, double x);

Point parabola_get_focus(Parabola parabola);

void parabola_input(FILE * fi, Parabola parabola);

void parabola_print(FILE * fh, Parabola parabola );

int parabola_check_point(Parabola parabola, Point point);

double * parabola_intersection_with_line(Parabola parabola, double k, double m);

double * parabola_intersection_with_parabola(Parabola parabola, Parabola other);    

double parabola_intersection_square_with_line(Parabola parabola, double k, double m);

double parabola_intersection_square_with_parabola(Parabola parabola, Parabola other);

int ellipse_check_ellipse(Ellipse e);

Point ellipse_get_center(Ellipse e);

double ellipse_get_value(Ellipse e, double x, int sign);

double ellipse_newton_raphson(Ellipse e, Ellipse ellipse, double x2, int mode); 
                   
void ellipse_calc_center(Ellipse e);

double get_length(Point a, Point b); 

void ellipse_calc_center_2(Ellipse e);   

int ellipse_init_verteces(Ellipse e, Point array[4]);
    
int init_focuses(Ellipse e, Point f_1, Point f_2, double rx, double ry);    
   
Point * ellipse_get_focuses(Ellipse e);

Point * ellipse_get_vertices(Ellipse e);

double ellipse_get_rx(Ellipse e);

double ellipse_get_ry(Ellipse e);

int ellipse_is_inside(Ellipse e, Point a);

double ellipse_get_square(Ellipse e);

int ellipse_input(FILE *fi, Ellipse e);

void ellipse_print(FILE * fh, Ellipse e );
  
double * ellipse_intersection_with_line(Ellipse e, double m, double c);

Point * ellipse_intersection_with_ellipse(Ellipse e, Ellipse ellipse);
 
void hyperbole_init(Hyperbole hyperbole, double array[5]);

double hyperbole_newton_raphson(Hyperbole h, Hyperbole hyperbole, double x2, int mode);

double hyperbole_newton_raphson_p(Hyperbole h, Parabola hyperbole, double x2, int mode);    
    
double hyperbole_get_x0(Hyperbole h );

double hyperbole_get_y0(Hyperbole h );

double hyperbole_get_a(Hyperbole h );

double hyperbole_get_b(Hyperbole h );
   
void hyperbole_input(FILE * fi, Hyperbole h);

void hyperbole_print(FILE * fh, Hyperbole h);

Point * hyperbole_get_foci(Hyperbole h);

double hyperbole_get_value(Hyperbole h, double x, int sign );
    
int hyperbole_check_point(Hyperbole h, Point point);

Point * hyperbole_intersection_p(Hyperbole h, Parabola parabola);

Point * hyperbole_intersection(Hyperbole h, Hyperbole parabola);


#endif