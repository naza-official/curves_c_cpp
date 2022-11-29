#ifndef CCURVES_H
#define CCURVES_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define CEPS 0.0000001
#define CEPS_1 0.0001


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






void cparabola_init(CParabola *parabola, double array[3]);

double cparabola_get_a(CParabola parabola);

double cparabola_get_b(CParabola parabola);

double cparabola_get_c(CParabola parabola);

double cparabola_get_value(CParabola parabola, double x);

CPoint cparabola_get_focus(CParabola parabola);

void cparabola_input(FILE * fi, CParabola *parabola);

void cparabola_print(FILE * fh, CParabola parabola );

int cparabola_check_point(CParabola parabola, CPoint point);

double * cparabola_intersection_with_line(CParabola parabola, double k, double m);

double * cparabola_intersection_with_parabola(CParabola parabola, CParabola other);    

double cparabola_intersection_square_with_line(CParabola parabola, double k, double m);

double cparabola_intersection_square_with_parabola(CParabola parabola, CParabola other);


int cellipse_check_ellipse(CEllipse e);

CPoint cellipse_get_center(CEllipse e);

double cellipse_get_value(CEllipse e, double x, int sign);

double cellipse_newton_raphson(CEllipse e, CEllipse ellipse, double x2, int mode); 
                   
void cellipse_calc_center(CEllipse e);

double get_length(CPoint a, CPoint b); 

void cellipse_calc_center_2(CEllipse e);   

int cellipse_init_verteces(CEllipse *e, CPoint array[4]);
    
int init_focuses(CEllipse *e, CPoint f_1, CPoint f_2, double rx, double ry);    
   
CPoint * cellipse_get_focuses(CEllipse e);

CPoint * cellipse_get_vertices(CEllipse e);

double cellipse_get_rx(CEllipse e);

double cellipse_get_ry(CEllipse e);

int cellipse_is_inside(CEllipse e, CPoint a);

double cellipse_get_square(CEllipse e);

int cellipse_input(FILE *fi, CEllipse *e);

void cellipse_print(FILE * fh, CEllipse e );
  
double * cellipse_intersection_with_line(CEllipse e, double m, double c);

CPoint * cellipse_intersection_with_ellipse(CEllipse e, CEllipse ellipse);

 
void chyperbole_init(CHyperbole *hyperbole, double array[5]);

double chyperbole_newton_raphson(CHyperbole h, CHyperbole hyperbole, double x2, int mode);

double chyperbole_newton_raphson_p(CHyperbole h, CParabola hyperbole, double x2, int mode);    
    
double chyperbole_get_x0(CHyperbole h );

double chyperbole_get_y0(CHyperbole h );

double chyperbole_get_a(CHyperbole h );

double chyperbole_get_b(CHyperbole h );
   
void chyperbole_input(FILE * fi, CHyperbole *h);

void chyperbole_print(FILE * fh, CHyperbole h);

CPoint * chyperbole_get_foci(CHyperbole h);

double chyperbole_get_value(CHyperbole h, double x, int sign );
    
int chyperbole_check_point(CHyperbole h, CPoint point);

CPoint * chyperbole_intersection_p(CHyperbole h, CParabola parabola);

CPoint * chyperbole_intersection(CHyperbole h, CHyperbole parabola);


#endif