#ifndef CCURVES_H
#define CCURVES_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define EPS 0.0000001
#define EPS_1 0.0001


struct CPoint {
    double x, y;
};

typedef struct CPoint CPoint;


struct CEllipse{
    CPoint verteces[4];
    CPoint focus_1;
    CPoint focus_2;
    double rx, 
           ry;
    CPoint center;
};


typedef struct CEllipse CEllipse;


struct CParabola {
  
    double equation[3];
      
};

typedef struct CParabola CParabola;

struct CHyperbole{

    double equation[5];           // x_center, y_center, a, b, r

};

typedef struct CHyperbole CHyperbole;






void parabola_init(CParabola parabola, double array[3]);

double parabola_get_a(CParabola parabola);

double parabola_get_b(CParabola parabola);

double parabola_get_c(CParabola parabola);

double parabola_get_value(CParabola parabola, double x);

CPoint parabola_get_focus(CParabola parabola);

void parabola_input(FILE * fi, CParabola parabola);

void parabola_print(FILE * fh, CParabola parabola );

int parabola_check_point(CParabola parabola, CPoint point);

double * parabola_intersection_with_line(CParabola parabola, double k, double m);

double * parabola_intersection_with_parabola(CParabola parabola, CParabola other);    

double parabola_intersection_square_with_line(CParabola parabola, double k, double m);

double parabola_intersection_square_with_parabola(CParabola parabola, CParabola other);

int ellipse_check_ellipse(CEllipse e);

CPoint ellipse_get_center(CEllipse e);

double ellipse_get_value(CEllipse e, double x, int sign);

double ellipse_newton_raphson(CEllipse e, CEllipse ellipse, double x2, int mode); 
                   
void ellipse_calc_center(CEllipse e);

double get_length(CPoint a, CPoint b); 

void ellipse_calc_center_2(CEllipse e);   

int ellipse_init_verteces(CEllipse e, CPoint array[4]);
    
int init_focuses(CEllipse e, CPoint f_1, CPoint f_2, double rx, double ry);    
   
CPoint * ellipse_get_focuses(CEllipse e);

CPoint * ellipse_get_vertices(CEllipse e);

double ellipse_get_rx(CEllipse e);

double ellipse_get_ry(CEllipse e);

int ellipse_is_inside(CEllipse e, CPoint a);

double ellipse_get_square(CEllipse e);

int ellipse_input(FILE *fi, CEllipse e);

void ellipse_print(FILE * fh, CEllipse e );
  
double * ellipse_intersection_with_line(CEllipse e, double m, double c);

CPoint * ellipse_intersection_with_ellipse(CEllipse e, CEllipse ellipse);
 
void hyperbole_init(CHyperbole hyperbole, double array[5]);

double hyperbole_newton_raphson(CHyperbole h, CHyperbole hyperbole, double x2, int mode);

double hyperbole_newton_raphson_p(CHyperbole h, CParabola hyperbole, double x2, int mode);    
    
double hyperbole_get_x0(CHyperbole h );

double hyperbole_get_y0(CHyperbole h );

double hyperbole_get_a(CHyperbole h );

double hyperbole_get_b(CHyperbole h );
   
void hyperbole_input(FILE * fi, CHyperbole h);

void hyperbole_print(FILE * fh, CHyperbole h);

CPoint * hyperbole_get_foci(CHyperbole h);

double hyperbole_get_value(CHyperbole h, double x, int sign );
    
int hyperbole_check_point(CHyperbole h, CPoint point);

CPoint * hyperbole_intersection_p(CHyperbole h, CParabola parabola);

CPoint * hyperbole_intersection(CHyperbole h, CHyperbole parabola);


#endif