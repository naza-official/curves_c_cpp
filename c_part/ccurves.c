#include "ccurves.h"
#define N_1 2


void cparabola_init(CParabola *parabola, double array[3]){
    for (int i = 0; i < 3; i++)
        parabola->equation[i] = array[i];
    double res = cparabola_get_a(*parabola);
    printf("%lf", res);
}


double cparabola_get_a(CParabola parabola){
    return parabola.equation[0];
}

double cparabola_get_b(CParabola parabola){
    return parabola.equation[1];
}

double cparabola_get_c(CParabola parabola){
    return parabola.equation[2];
}    

double cparabola_get_value(CParabola parabola, double x){
    return parabola.equation[0]*pow(x,2) + parabola.equation[1]*x + parabola.equation[2];
} 


CPoint cparabola_get_focus(CParabola parabola){
    CPoint res;
    res.x =(-1)* parabola.equation[1]/(2*parabola.equation[0]);
    res.y = (-1)*((pow(parabola.equation[1],2)-1)/(4*parabola.equation[0]))+parabola.equation[2];
    return res;
}



void cparabola_input(FILE *fi, CParabola *parabola){

    printf(" << CParabola >> \na = ");
    fscanf(fi, "%lf", &parabola->equation[0]);
    printf("b = ");
    fscanf(fi, "%lf", &parabola->equation[1]);
    printf("c = ");
    fscanf(fi, "%lf", &parabola->equation[2]);

}

void cparabola_print(FILE * fh, CParabola parabola ){
    fprintf(fh, "y= %lf*x^2 + %lf*x + %lf", parabola.equation[0], parabola.equation[1], parabola.equation[2]);
}

int cparabola_check_point(CParabola parabola, CPoint point){
    return point.y >= cparabola_get_value(parabola, point.x);
}

double * cparabola_intersection_with_line(CParabola parabola, double k, double m){
    
    static double res[5];      //last element is equal to number of intersection points
    double d = pow(parabola.equation[1]-k,2) - 4.0*parabola.equation[0]*(parabola.equation[2]-m);

    if (d<0){
        res[4] = 0;
        return res;
    }
    else if (d==0){
        res[4] = 1;
    }
    else res[4] = 2;
    
    res[0] = ((k-parabola.equation[1])+pow(d, 0.5))/(2.0*parabola.equation[0]);
    res[1] = res[1]*k+m;        
    
    res[2] = ((k-parabola.equation[1])-pow(d, 0.5))/(2.0*parabola.equation[0]);
    res[3] = res[2]*k+m;        
    return res;
}

double * cparabola_intersection_with_parabola(CParabola parabola, CParabola other){
    static double res[5];
    
    double d = pow(parabola.equation[1]-cparabola_get_b(other), 2) - 4.0*(parabola.equation[0]-cparabola_get_a(other))*(parabola.equation[2]-cparabola_get_c(other));
    
    
    
    if (d<0){
        res[4] = 0;
        return res;
    }
    else if (d==0){
        res[4] = 1;
    }
    else res[4] = 2;
    
    
    
           
    res[0] = ((-1.0)*(parabola.equation[1] - cparabola_get_b(other))-pow(d,0.5))/(parabola.equation[0]-cparabola_get_a(other));
    res[1] = cparabola_get_value(other, res[0]);
                      
    res[2] = ((-1.0)*(parabola.equation[1] - cparabola_get_b(other))+pow(d,0.5))/(parabola.equation[0]-cparabola_get_a(other));
    res[3] = cparabola_get_value(other, res[2]);
    return res; 
  

}    


double cparabola_intersection_square_with_line(CParabola parabola, double k, double m){
    double *points;
    points = cparabola_intersection_with_line(parabola, k, m);
    
    if (*(points+4) == 0 || *(points+4)==1) return 0;
    
    double x1 = (*points);      
    double x2 = (*(points+2));      
    
    double res = fabs((cparabola_get_c(parabola)-m)*x1 + (cparabola_get_a(parabola)*pow(x1,3))/3.0 + (cparabola_get_b(parabola) - k)*pow(x1,2)/2.0 - 
                    (cparabola_get_c(parabola)-m)*x2 + (cparabola_get_a(parabola)*pow(x2,3))/3.0 + ((cparabola_get_b(parabola) - k)*pow(x2,2))/2.0);

    return res;
}


double cparabola_intersection_square_with_parabola(CParabola parabola, CParabola other){
    double *points;
    points = cparabola_intersection_with_parabola(parabola, other);
    
    if (*(points+4) == 0 || *(points+4)==1) return 0;
    
    double x1 = (*points);      
    double x2 = (*(points+2));                
    
    double res = fabs((x1*(cparabola_get_c(parabola)-cparabola_get_c(other)) + pow(x1,2.0)/2.0*(cparabola_get_b(parabola)-cparabola_get_b(other)) + pow(x1,3.0)/3.0*(cparabola_get_a(parabola)-cparabola_get_a(other))) - 
        (x2*(cparabola_get_c(parabola)-cparabola_get_c(other)) + pow(x2,2.0)/2.0*(cparabola_get_b(parabola)-cparabola_get_b(other)) + pow(x2,3.0)/3.0*(cparabola_get_a(parabola)-cparabola_get_a(other))));
    
    return res;
}
 








int cellipse_check_ellipse(CEllipse e){
    
    if(e.center.x != (e.verteces[2].x + e.verteces[3].x)/2.0 ||
    e.center.y != (e.verteces[2].y + e.verteces[3].y)/2.0)
    {return 0;}
    
    if (e.verteces[0].y != e.verteces[1].y ||
        e.verteces[2].x != e.verteces[2].x){
        return 0;}
    return 1;
       
}




CPoint cellipse_get_center(CEllipse e){
    return e.center;
}

double cellipse_get_value(CEllipse e, double x, int sign){
    
    double A = 1.0/pow(e.rx, 2);        
    double B = 1.0/pow(e.ry, 2);         
    double C = 0.0;
    double D = (-2.0)*cellipse_get_center(e).x / pow(e.rx, 2);
    double E = (-2.0)*cellipse_get_center(e).y / pow(e.ry, 2);        
    double F = pow(cellipse_get_center(e).x, 2)/pow(e.rx, 2) +  pow(cellipse_get_center(e).y, 2)/pow(e.ry, 2) - 1;
    
    double res = ((-1.0)*(C*x+E) + sign*pow( fabs(pow(C*x+E,2) - 4*B*(A*x*x + D*x + F)), 0.5 ))/(2.0*B);
    
    // double res = (cellipse_get_ry()*pow(pow(cellipse_get_rx(),2)-pow(x,2)+2*x*cellipse_get_center().x-pow(cellipse_get_center().x,2),2))/cellipse_get_rx()+cellipse_get_center().y;
    return res;
}



double cellipse_newton_raphson(CEllipse e, CEllipse ellipse, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;
    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = (((cellipse_get_value(e, x1+CEPS, 1) - cellipse_get_value(ellipse, x1+CEPS, 1))) - (cellipse_get_value(e, x1, 1) - cellipse_get_value(ellipse, x1, 1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (cellipse_get_value(e, x1, 1)-cellipse_get_value(ellipse, x1, 1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((cellipse_get_value(e, x1+CEPS, -1)-cellipse_get_value(ellipse, x1+CEPS, 1)) - (cellipse_get_value(e, x1, -1)-cellipse_get_value(ellipse, x1, 1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (cellipse_get_value(e, x1, -1)-cellipse_get_value(ellipse, x1, 1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((cellipse_get_value(e, x1+CEPS, 1)-cellipse_get_value(ellipse, x1+CEPS, -1)) - (cellipse_get_value(e, x1, 1)-cellipse_get_value(ellipse, x1, -1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (cellipse_get_value(e, x1, 1)-cellipse_get_value(ellipse, x1, -1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((cellipse_get_value(e, x1+CEPS, -1)-cellipse_get_value(ellipse, x1+CEPS, -1)) - (cellipse_get_value(e, x1, -1)-cellipse_get_value(ellipse, x1, -1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (cellipse_get_value(e, x1, -1)-cellipse_get_value(ellipse, x1, -1))/dx;                  

        }
    
        if (count > 1000) return 0;
        count++;
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= CEPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}

 


                    
    
void cellipse_calc_center(CEllipse *e){
    e->center.x = (e->verteces[0].x + e->verteces[1].x)/2.0;
    e->center.y = (e->verteces[0].y + e->verteces[1].y)/2.0;
}


double get_length(CPoint a, CPoint b){
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}
 

void cellipse_calc_center_2(CEllipse *e){
    e->center.x = (e->focus_1.x + e->focus_2.x)/2;
    e->center.y = (e->focus_1.y + e->focus_2.y)/2;
}    


int cellipse_init_verteces(CEllipse *e, CPoint array[4]){

    for(int i = 0; i < 4; i++){
        e->verteces[i] = array[i];
    }
    
    cellipse_calc_center(e);
    
    e->rx = get_length(e->center, e->verteces[0]);
    e->ry = get_length(e->center, e->verteces[2]);
    double foci = pow(fabs(pow(e->rx,2)-pow(e->ry,2)),0.5);
    
    
    e->focus_1.x = e->center.x + foci*(e->center.x - e->verteces[0].x)/get_length(e->center, e->verteces[0]);
    
    e->focus_1.y = e->center.y + foci*(e->center.y - e->verteces[0].y)/get_length(e->center, e->verteces[0]);
    

    e->focus_2.x = e->center.x - foci*(e->center.x - e->verteces[0].x)/get_length(e->center, e->verteces[0]);
    e->focus_2.y = e->center.y - foci*(e->center.y - e->verteces[0].y)/get_length(e->center, e->verteces[0]);
    return cellipse_check_ellipse(*e);
    
}

    
int cellipse_init_focuses(CEllipse *e, CPoint f_1, CPoint f_2, double rx, double ry){
    e->focus_1 = f_1;
    e->focus_2 = f_2;
    e->rx = rx;
    e->ry = ry;
    cellipse_calc_center_2(e);
    
    e->verteces[0].x = e->center.x + e->rx*(e->center.x - e->focus_1.x)/get_length(e->center, e->focus_1);
    e->verteces[0].y = e->center.y + e->rx*(e->center.y - e->focus_1.y)/get_length(e->center, e->focus_1);
    
    e->verteces[1].x = e->center.x*2.0 - e->verteces[0].x;
    e->verteces[1].y = e->center.y*2.0 - e->verteces[0].y;
    
    e->verteces[2].x = e->center.x + e->ry*(e->center.y - e->focus_1.y)/get_length(e->center, e->focus_1);
    e->verteces[2].y = e->center.y + (-1.0)*e->ry*(e->center.x - e->focus_1.x)/get_length(e->center, e->focus_1);
    
    e->verteces[3].x = e->center.x*2.0 - e->verteces[3].x;
    e->verteces[3].y = e->center.y*2.0 - e->verteces[3].y;

    return cellipse_check_ellipse(*e);

}
    
   

CPoint * cellipse_get_focuses(CEllipse e){
    static CPoint focuses[N_1];
    focuses[0] = e.focus_1;
    focuses[1] = e.focus_2; 
    return focuses;
}

CPoint * cellipse_get_vertices(CEllipse e){
    static CPoint v[4];
    for (int i = 0; i < 4; i++){
        v[i] = e.verteces[i];
    }
    return v;
}

double cellipse_get_rx(CEllipse e){
    return e.rx;
}

double cellipse_get_ry(CEllipse e){
    return e.ry;
}    

int cellipse_is_inside(CEllipse e, CPoint a){
    if(pow((a.x-e.center.x),2)/pow(e.rx, 2) + pow((a.y-e.center.y),2)/pow(e.ry, 2) <= 1){
        return 1;
    }
    else return 0;
}


double cellipse_get_square(CEllipse e){
    return M_PI*e.rx*e.ry;
}

int cellipse_input(FILE *fi, CEllipse *e){
    int check;
    printf( "Choose a method of input: 1 -- coordinates of verteces, 0 -- foci and radiuses\n");
    fscanf(fi, "%i", &check);
    if (check){
        CPoint array[4];
        for (int i = 0; i < 4; i++){
            printf( "Vertex %i \n", i+1);
            printf( "x = ");
            fscanf(fi, "%lf", &array[i].x);
            printf( "y = ");
            fscanf(fi, "%lf", &array[i].y);
            
        }
        return cellipse_init_verteces(e, array);
    }
    else{
        CPoint focus_1, focus_2;
        double xr, yr;
        printf("Focus_1\n");
        printf("x = ");
        fscanf(fi, "%lf", &focus_1.x);
        printf("y = ");
        fscanf(fi,  "%lf", &focus_1.y);
        printf("Focus_2\n");
        printf("x = ");
        fscanf(fi, "%lf", &focus_2.x);
        printf("y = ");
        fscanf(fi,  "%lf", &focus_2.y);
        printf("XR = ");
        fscanf(fi, "%lf", &xr);
        printf("YR = ");
        fscanf(fi, "%lf", &yr);
        return cellipse_init_focuses(e, focus_1, focus_2, xr, yr);
     }
    return 0;
}

void cellipse_print(FILE * fh, CEllipse e ){
    fprintf(fh, "<< CEllipse >>" );
    fprintf(fh, "-- Center --" );
    fprintf(fh, "(%lf , %lf)", e.center.x, e.center.y);
    fprintf(fh, "-- Verteces --" );
    for (int i = 0; i < 4; i++){
        fprintf(fh, "(%lf, %lf)", e.verteces[i].x, e.verteces[i].y);
    }
    fprintf(fh, "-- Focus_1 --" );
    fprintf(fh, "(%lf, %lf)", e.focus_1.x, e.focus_1.y);
    fprintf(fh, "-- Focus_2 --" );
    fprintf(fh, "(%lf, %lf)", e.focus_2.x, e.focus_2.y);
}



   

double * cellipse_intersection_with_line(CEllipse e, double m, double c){
    
    static double res[5];                                                         
        
    double d = pow(2.0*e.rx*e.ry, 2)*(m*m*e.rx*e.rx + e.ry*e.ry + 2*m*cellipse_get_center(e).y*cellipse_get_center(e).x - 2*m*c*cellipse_get_center(e).x + 2*c*cellipse_get_center(e).y - c * c - cellipse_get_center(e).y*cellipse_get_center(e).y - m*m*cellipse_get_center(e).x*cellipse_get_center(e).x);
    double a = 2*cellipse_get_center(e).x*pow(e.ry,2) - 2*m*pow(e.rx,2)*c + 2*m*pow(e.rx,2)*cellipse_get_center(e).y;
       
    
    if (d<0) {res[4]=0; return res;}
    if (d==0) res [4]=1;
    if (d>0) res [4]=2;
        
    res[0] = (a+pow(d,0.5))/(2.0*(pow(e.ry,2)+pow(e.rx,2)*pow(m,2)));
    res[1] = m*res[0]+c;
    
    res[2] = (a-pow(d,0.5))/(2.0*(pow(e.ry,2)+pow(e.rx,2)*pow(m,2)));
    res[3] = m*res[2]+c;    
    return res;
}

CPoint * cellipse_intersection_with_ellipse(CEllipse e, CEllipse ellipse){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static CPoint res[4];
    double min_x = fmin(e.verteces[0].x, (*(cellipse_get_vertices(ellipse))).x);        
    double max_x = fmax(e.verteces[1].x, (*(cellipse_get_vertices(ellipse)+1)).x);        
    
    
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = cellipse_newton_raphson(e, ellipse, x, 1);
        eq2 = cellipse_newton_raphson(e, ellipse, x, 2);
        eq3 = cellipse_newton_raphson(e, ellipse, x, 3);
        eq4 = cellipse_newton_raphson(e, ellipse, x, 4);
        if (fabs(eq1-eq1_l)>CEPS && (eq1 < e.verteces[1].x && eq1 > e.verteces[0].x)){
            eq1_sols[i1] = eq1;
            i1++;
            eq1_l = eq1;
        }
        

        if (fabs(eq2-eq2_l)>CEPS && (eq2 < e.verteces[1].x && eq2 > e.verteces[0].x)){
            eq2_sols[i2] = eq2;
            i2++;
            eq2_l = eq2;
        }

       
        if (fabs(eq3-eq3_l)>CEPS && (eq3 < e.verteces[1].x && eq3 > e.verteces[0].x)){
            eq3_sols[i3] = eq3;
            i3++;
            eq3_l = eq3;
        }
     

        if (fabs(eq4-eq4_l)>CEPS && (eq4 < e.verteces[1].x && eq4 > e.verteces[0].x)){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
          
    }
    if (!i1 && !i2 && !i3 && !i4) return res;
            
    int i_s = 0;
    for (int i = 0; i < i1; i++) {
        CPoint r1;
        r1.x = eq1_sols[i];
        r1.y = cellipse_get_value(e, eq1_sols[i], 1);
        res[i_s] = r1; i_s++;
    }
    for (int i = 0; i < i2; i++) {
        CPoint r2;
        r2.x = eq2_sols[i];
        r2.y = cellipse_get_value(e, eq2_sols[i], 1);
        res[i_s] = r2; i_s++;
    }
    for (int i = 0; i < i3; i++) {
        CPoint r3; 
        r3.x = eq3_sols[i]; 
        r3.y = cellipse_get_value(e, eq3_sols[i], 1);
        res[i_s] = r3; i_s++;
    }
    for (int i = 0; i < i4; i++){
        CPoint r4;
        r4.x =  eq4_sols[i];
        r4.y = cellipse_get_value(e, eq4_sols[i], 1);
        res[i_s] = r4; i_s++;
    }
    return res;
}



 
void chyperbole_init(CHyperbole *hyperbole, double array[5]){
    for (int i = 0; i < 5; i++){
        hyperbole->equation[i] = array[i];
    }
} 





double chyperbole_newton_raphson(CHyperbole h, CHyperbole hyperbole, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;

    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = ((chyperbole_get_value(h, x1+CEPS, 1)-chyperbole_get_value(hyperbole, x1+CEPS, 1)) - (chyperbole_get_value(h, x1, 1)-chyperbole_get_value(hyperbole, x1, 1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, 1)-chyperbole_get_value(hyperbole, x1, 1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((chyperbole_get_value(h, x1+CEPS, -1)-chyperbole_get_value(hyperbole, x1+CEPS, 1)) - (chyperbole_get_value(h, x1, -1)-chyperbole_get_value(hyperbole, x1, 1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, -1)-chyperbole_get_value(hyperbole, x1, 1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((chyperbole_get_value(h, x1+CEPS, 1)-chyperbole_get_value(hyperbole, x1+CEPS, -1)) - (chyperbole_get_value(h, x1, 1)-chyperbole_get_value(hyperbole, x1, -1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, 1)-chyperbole_get_value(hyperbole, x1, -1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((chyperbole_get_value(h, x1+CEPS, -1)-chyperbole_get_value(hyperbole, x1+CEPS, -1)) - (chyperbole_get_value(h, x1, -1)-chyperbole_get_value(hyperbole, x1, -1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, -1)-chyperbole_get_value(hyperbole, x1, -1))/dx;                  

        }
        
        if (count > 1000) return 0;
        count++;
    
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= CEPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}




double chyperbole_newton_raphson_p(CHyperbole h, CParabola hyperbole, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;

    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = ((chyperbole_get_value(h, x1+CEPS, 1)-cparabola_get_value(hyperbole, x1+CEPS)) - (chyperbole_get_value(h, x1, 1)-cparabola_get_value(hyperbole, x1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, 1)-cparabola_get_value(hyperbole, x1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((chyperbole_get_value(h, x1+CEPS, -1)-cparabola_get_value(hyperbole, x1+CEPS)) - (chyperbole_get_value(h, x1, -1)-cparabola_get_value(hyperbole, x1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, -1)-cparabola_get_value(hyperbole, x1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((chyperbole_get_value(h, x1+CEPS, 1)-cparabola_get_value(hyperbole, x1+CEPS)) - (chyperbole_get_value(h, x1, 1)-cparabola_get_value(hyperbole, x1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, 1)-cparabola_get_value(hyperbole, x1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((chyperbole_get_value(h, x1+CEPS, -1)-cparabola_get_value(hyperbole, x1+CEPS)) - (chyperbole_get_value(h, x1, -1)-cparabola_get_value(hyperbole, x1)))/CEPS;
            if (dx == 0) return 0;
            x2 = x1 - (chyperbole_get_value(h, x1, -1)-cparabola_get_value(hyperbole, x1))/dx;                  

        }
        
        if (count > 1000) return 0;
        count++;
    
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= CEPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}
    
    
double chyperbole_get_x0(CHyperbole h ){
    return h.equation[0]; 
}

double chyperbole_get_y0(CHyperbole h ){
    return h.equation[1]; 
}

double chyperbole_get_a(CHyperbole h ){
    return h.equation[2]; 
}

double chyperbole_get_b(CHyperbole h ){
    return h.equation[3]; 
}
   
void chyperbole_input(FILE *fi, CHyperbole *h){
    double koefs[5];
    double r;
    printf( "<< Hyperbola >>\n");
    printf( "x0 = ");
    fscanf(fi, "%lf", &koefs[0]);
    printf( "y0 = ");
    fscanf(fi, "%lf", &koefs[1]);
    printf( "a = ");
    fscanf(fi, "%lf", &koefs[2]);
    printf( "b = ");
    fscanf(fi, "%lf", &koefs[3]);
    printf( "r = ");
    fscanf(fi,"%lf", &r);
    koefs[2] /= r;
    koefs[3] /= r;
    koefs[4] = r/fabs(r);
    
    chyperbole_init(h, koefs);
}

void chyperbole_print(FILE * fh, CHyperbole h){
    
     fprintf(fh, "<< Hyperbola >>" );
     fprintf(fh, "x0 = %lf " , chyperbole_get_x0(h) );
     fprintf(fh, "y0 = %lf " , chyperbole_get_y0(h) );
     fprintf(fh, "a = %lf " , chyperbole_get_a(h) );
     fprintf(fh, "b = %lf " , chyperbole_get_b(h) );
}




CPoint * chyperbole_get_foci(CHyperbole h){
    static CPoint res[2];
    
    double e = pow(1.0+(chyperbole_get_b(h)*chyperbole_get_b(h))/(chyperbole_get_a(h)*chyperbole_get_a(h)), 0.5);
    if (h.equation[4] > 0){
    res[0].x = (chyperbole_get_a(h)*e+chyperbole_get_x0(h));
    res[0].y = chyperbole_get_y0(h);
    res[1].x = ((-1)*chyperbole_get_a(h)*e+chyperbole_get_x0(h));
    res[1].y = chyperbole_get_y0(h);        
    }
    else{
    res[0].y = (chyperbole_get_a(h)*e+chyperbole_get_x0(h));
    res[0].x = chyperbole_get_y0(h);
    res[1].y = ((-1)*chyperbole_get_a(h)*e+chyperbole_get_x0(h));
    res[1].x = chyperbole_get_y0(h); 
    }
           
    return res;
}


double chyperbole_get_value(CHyperbole h, double x, int sign ){
    return chyperbole_get_y0(h) + (sign/chyperbole_get_a(h))*chyperbole_get_b(h)*pow(fabs(chyperbole_get_a(h)*chyperbole_get_a(h) - x*x + 2*x*chyperbole_get_x0(h)-chyperbole_get_x0(h)*chyperbole_get_x0(h) ) , 0.5 );
}


    
int chyperbole_check_point(CHyperbole h, CPoint point){
    
    if (pow((point.x - chyperbole_get_x0(h)),2)/pow(chyperbole_get_a(h),2) + pow((point.y - chyperbole_get_y0(h)),2)/pow(chyperbole_get_b(h),2) >= 1) return 1;
    else return 0;      
}


CPoint * chyperbole_intersection_p(CHyperbole h, CParabola parabola){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static CPoint res[4];
    double min_x = -5;        
    double max_x = 5;        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = chyperbole_newton_raphson_p(h, parabola, x, 1);
        eq2 = chyperbole_newton_raphson_p(h, parabola, x, 2);
        eq3 = chyperbole_newton_raphson_p(h, parabola, x, 3);
        eq4 = chyperbole_newton_raphson_p(h, parabola, x, 4);
        if (fabs(eq1-eq1_l)>CEPS_1 && fabs(chyperbole_get_value(h, eq1, 1) - cparabola_get_value(parabola, eq1))<0.00001){
        eq1_sols[i1] = eq1;
        i1++;
        eq1_l = eq1;
        }

        if (fabs(eq2-eq2_l)>CEPS_1 && fabs(chyperbole_get_value(h, eq2, -1) - cparabola_get_value(parabola, eq2))<0.00001){
        eq2_sols[i2] = eq2;
        i2++;
        eq2_l = eq2;
        }

        if (fabs(eq3-eq3_l )>CEPS_1 && fabs(chyperbole_get_value(h, eq3, 1) - cparabola_get_value(parabola, eq3))<0.00001){
        eq3_sols[i3] = eq3;
        i3++;
        eq3_l = eq3;
        }

        if (fabs(eq4-eq4_l)>CEPS_1 && fabs(chyperbole_get_value(h, eq4, -1) - cparabola_get_value(parabola, eq4))<0.00001){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
    }
        
    int i_s = 0;
    for (int i = 0; i < i1; i++) {

        CPoint k;
        k.x = eq1_sols[i]; 
        k.y = chyperbole_get_value(h, eq1_sols[i],1);
        res[i_s] = k;
        i_s++;}
    for (int i = 0; i < i2; i++) {
    
        CPoint k;
        k.x = eq2_sols[i]; 
        k.y = chyperbole_get_value(h, eq2_sols[i],-1);
        res[i_s] = k;
        i_s++;    }
    for (int i = 0; i < i3; i++) {
    
        CPoint k;
        k.x = eq3_sols[i]; 
        k.y = chyperbole_get_value(h, eq3_sols[i],1);
        res[i_s] = k;
        i_s++;     }
    for (int i = 0; i < i4; i++) {

        CPoint k;
        k.x = eq4_sols[i]; 
        k.y = chyperbole_get_value(h, eq4_sols[i],-1);
        res[i_s] = k;
        i_s++;     }
    return res;

}


CPoint * chyperbole_intersection(CHyperbole h, CHyperbole parabola){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static CPoint res[4];
    double min_x = -5;        
    double max_x = 5;        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = chyperbole_newton_raphson(h, parabola, x, 1);
        eq2 = chyperbole_newton_raphson(h, parabola, x, 2);
        eq3 = chyperbole_newton_raphson(h, parabola, x, 3);
        eq4 = chyperbole_newton_raphson(h, parabola, x, 4);
        if (fabs(eq1-eq1_l)>CEPS_1 && fabs(chyperbole_get_value(h, eq1, 1) - chyperbole_get_value(parabola, eq1, 1))<0.001){
        eq1_sols[i1] = eq1;
        i1++;
        eq1_l = eq1;
        }

        if (fabs(eq2-eq2_l)>CEPS_1 && fabs(chyperbole_get_value(h, eq2, -1) - chyperbole_get_value(parabola, eq2, -1))<0.001){
        eq2_sols[i2] = eq2;
        i2++;
        eq2_l = eq2;
        }

        if (fabs(eq3-eq3_l )>CEPS_1 && fabs(chyperbole_get_value(h, eq3, 1) - chyperbole_get_value(parabola, eq3, 1))<0.001){
        eq3_sols[i3] = eq3;
        i3++;
        eq3_l = eq3;
        }

        if (fabs(eq4-eq4_l)>CEPS_1 && fabs(chyperbole_get_value(h, eq4, -1) - chyperbole_get_value(parabola, eq4, -1))<0.001){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
    }





    int i_s = 0;
    for (int i = 0; i < i1; i++) {

        CPoint k;
        k.x = eq1_sols[i]; 
        k.y = chyperbole_get_value(h, eq1_sols[i], 1);
        res[i_s] = k;
        i_s++;}
    for (int i = 0; i < i2; i++) {
    
        CPoint k;
        k.x = eq2_sols[i]; 
        k.y = chyperbole_get_value(h, eq2_sols[i], -1);
        res[i_s] = k;
        i_s++;    }
    for (int i = 0; i < i3; i++) {
    
        CPoint k;
        k.x = eq3_sols[i]; 
        k.y = chyperbole_get_value(h, eq3_sols[i], 1);
        res[i_s] = k;
        i_s++;     }
    for (int i = 0; i < i4; i++) {

        CPoint k;
        k.x = eq4_sols[i]; 
        k.y = chyperbole_get_value(h, eq4_sols[i], -1);
        res[i_s] = k;
        i_s++;     }
        
    return res;

}


