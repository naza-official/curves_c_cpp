#include "ccurves.h"
#define N_1 2


void parabola_init(Parabola parabola, double array[3]){
    for (int i = 0; i < 3; i++)
        parabola.equation[i] = array[i];
}


double parabola_get_a(Parabola parabola){
    return parabola.equation[0];
}

double parabola_get_b(Parabola parabola){
    return parabola.equation[1];
}

double parabola_get_c(Parabola parabola){
    return parabola.equation[2];
}    

double parabola_get_value(Parabola parabola, double x){
    return parabola.equation[0]*pow(x,2) + parabola.equation[1]*x + parabola.equation[2];
} 


Point parabola_get_focus(Parabola parabola){
    Point res;
    res.x =(-1)* parabola.equation[1]/(2*parabola.equation[0]);
    res.y = (-1)*((pow(parabola.equation[1],2)-1)/(4*parabola.equation[0]))+parabola.equation[2];
    return res;
}



void parabola_input(FILE *fi, Parabola parabola){

    printf(" << Parabola >> \na = ");
    fscanf(fi, "%lf", &parabola.equation[0]);
    printf("b = ");
    fscanf(fi, "%lf", &parabola.equation[1]);
    printf("c = ");
    fscanf(fi, "%lf", &parabola.equation[2]);

}

void parabola_print(FILE * fh, Parabola parabola ){
    fprintf(fh, "y= %lf*x^2 + %lf*x + %lf", parabola.equation[0], parabola.equation[1], parabola.equation[2]);
}

int parabola_check_point(Parabola parabola, Point point){
    return point.y >= parabola_get_value(parabola, point.x);
}

double * parabola_intersection_with_line(Parabola parabola, double k, double m){
    
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

double * parabola_intersection_with_parabola(Parabola parabola, Parabola other){
    static double res[5];
    
    double d = pow(parabola.equation[1]-parabola_get_b(other), 2) - 4.0*(parabola.equation[0]-parabola_get_a(other))*(parabola.equation[2]-parabola_get_c(other));
    
    
    
    if (d<0){
        res[4] = 0;
        return res;
    }
    else if (d==0){
        res[4] = 1;
    }
    else res[4] = 2;
    
    
    
           
    res[0] = ((-1.0)*(parabola.equation[1] - parabola_get_b(other))-pow(d,0.5))/(parabola.equation[0]-parabola_get_a(other));
    res[1] = parabola_get_value(other, res[0]);
                      
    res[2] = ((-1.0)*(parabola.equation[1] - parabola_get_b(other))+pow(d,0.5))/(parabola.equation[0]-parabola_get_a(other));
    res[3] = parabola_get_value(other, res[2]);
    return res; 
  

}    


double parabola_intersection_square_with_line(Parabola parabola, double k, double m){
    double *points;
    points = parabola_intersection_with_line(parabola, k, m);
    
    if (*(points+4) == 0 || *(points+4)==1) return 0;
    
    double x1 = (*points);      
    double x2 = (*(points+2));      
    
    double res = fabs((parabola_get_c(parabola)-m)*x1 + (parabola_get_a(parabola)*pow(x1,3))/3.0 + (parabola_get_b(parabola) - k)*pow(x1,2)/2.0 - 
                    (parabola_get_c(parabola)-m)*x2 + (parabola_get_a(parabola)*pow(x2,3))/3.0 + ((parabola_get_b(parabola) - k)*pow(x2,2))/2.0);

    return res;
}


double parabola_intersection_square_with_parabola(Parabola parabola, Parabola other){
    double *points;
    points = parabola_intersection_with_parabola(parabola, other);
    
    if (*(points+4) == 0 || *(points+4)==1) return 0;
    
    double x1 = (*points);      
    double x2 = (*(points+2));                
    
    double res = fabs((x1*(parabola_get_c(parabola)-parabola_get_c(other)) + pow(x1,2.0)/2.0*(parabola_get_b(parabola)-parabola_get_b(other)) + pow(x1,3.0)/3.0*(parabola_get_a(parabola)-parabola_get_a(other))) - 
        (x2*(parabola_get_c(parabola)-parabola_get_c(other)) + pow(x2,2.0)/2.0*(parabola_get_b(parabola)-parabola_get_b(other)) + pow(x2,3.0)/3.0*(parabola_get_a(parabola)-parabola_get_a(other))));
    
    return res;
}
 








int ellipse_check_ellipse(Ellipse e){
    
    if(e.center.x != (e.verteces[2].x + e.verteces[3].x)/2.0 ||
    e.center.y != (e.verteces[2].y + e.verteces[3].y)/2.0)
    {return 0;}
    
    if (e.verteces[0].y != e.verteces[1].y ||
        e.verteces[2].x != e.verteces[2].x){
        return 0;}
    return 1;
       
}




Point ellipse_get_center(Ellipse e){
    return e.center;
}

double ellipse_get_value(Ellipse e, double x, int sign){
    
    double A = 1.0/pow(e.rx, 2);        
    double B = 1.0/pow(e.ry, 2);         
    double C = 0.0;
    double D = (-2.0)*ellipse_get_center(e).x / pow(e.rx, 2);
    double E = (-2.0)*ellipse_get_center(e).y / pow(e.ry, 2);        
    double F = pow(ellipse_get_center(e).x, 2)/pow(e.rx, 2) +  pow(ellipse_get_center(e).y, 2)/pow(e.ry, 2) - 1;
    
    double res = ((-1.0)*(C*x+E) + sign*pow( fabs(pow(C*x+E,2) - 4*B*(A*x*x + D*x + F)), 0.5 ))/(2.0*B);
    
    // double res = (ellipse_get_ry()*pow(pow(ellipse_get_rx(),2)-pow(x,2)+2*x*ellipse_get_center().x-pow(ellipse_get_center().x,2),2))/ellipse_get_rx()+ellipse_get_center().y;
    return res;
}



double ellipse_newton_raphson(Ellipse e, Ellipse ellipse, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;
    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = (((ellipse_get_value(e, x1+EPS, 1) - ellipse_get_value(ellipse, x1+EPS, 1))) - (ellipse_get_value(e, x1, 1) - ellipse_get_value(ellipse, x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (ellipse_get_value(e, x1, 1)-ellipse_get_value(ellipse, x1, 1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((ellipse_get_value(e, x1+EPS, -1)-ellipse_get_value(ellipse, x1+EPS, 1)) - (ellipse_get_value(e, x1, -1)-ellipse_get_value(ellipse, x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (ellipse_get_value(e, x1, -1)-ellipse_get_value(ellipse, x1, 1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((ellipse_get_value(e, x1+EPS, 1)-ellipse_get_value(ellipse, x1+EPS, -1)) - (ellipse_get_value(e, x1, 1)-ellipse_get_value(ellipse, x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (ellipse_get_value(e, x1, 1)-ellipse_get_value(ellipse, x1, -1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((ellipse_get_value(e, x1+EPS, -1)-ellipse_get_value(ellipse, x1+EPS, -1)) - (ellipse_get_value(e, x1, -1)-ellipse_get_value(ellipse, x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (ellipse_get_value(e, x1, -1)-ellipse_get_value(ellipse, x1, -1))/dx;                  

        }
    
        if (count > 1000) return 0;
        count++;
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= EPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}

 


                    
    
void ellipse_calc_center(Ellipse e){
    e.center.x = (e.verteces[0].x + e.verteces[1].x)/2.0;
    e.center.y = (e.verteces[0].y + e.verteces[1].y)/2.0;
}


double get_length(Point a, Point b){
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}
 

void ellipse_calc_center_2(Ellipse e){
    e.center.x = (e.focus_1.x + e.focus_2.x)/2;
    e.center.y = (e.focus_1.y + e.focus_2.y)/2;
}    


int ellipse_init_verteces(Ellipse e, Point array[4]){

    for(int i = 0; i < 4; i++){
        e.verteces[i] = array[i];
    }
    
    ellipse_calc_center(e);
    
    e.rx = get_length(e.center, e.verteces[0]);
    e.ry = get_length(e.center, e.verteces[2]);
    double foci = pow(fabs(pow(e.rx,2)-pow(e.ry,2)),0.5);
    
    
    e.focus_1.x = e.center.x + foci*(e.center.x - e.verteces[0].x)/get_length(e.center, e.verteces[0]);
    
    e.focus_1.y = e.center.y + foci*(e.center.y - e.verteces[0].y)/get_length(e.center, e.verteces[0]);
    

    e.focus_2.x = e.center.x - foci*(e.center.x - e.verteces[0].x)/get_length(e.center, e.verteces[0]);
    e.focus_2.y = e.center.y - foci*(e.center.y - e.verteces[0].y)/get_length(e.center, e.verteces[0]);
    return ellipse_check_ellipse(e);
    
}

    
int ellipse_init_focuses(Ellipse e, Point f_1, Point f_2, double rx, double ry){
    e.focus_1 = f_1;
    e.focus_2 = f_2;
    e.rx = rx;
    e.ry = ry;
    ellipse_calc_center_2(e);
    
    e.verteces[0].x = e.center.x + e.rx*(e.center.x - e.focus_1.x)/get_length(e.center, e.focus_1);
    e.verteces[0].y = e.center.y + e.rx*(e.center.y - e.focus_1.y)/get_length(e.center, e.focus_1);
    
    e.verteces[1].x = e.center.x*2.0 - e.verteces[0].x;
    e.verteces[1].y = e.center.y*2.0 - e.verteces[0].y;
    
    e.verteces[2].x = e.center.x + e.ry*(e.center.y - e.focus_1.y)/get_length(e.center, e.focus_1);
    e.verteces[2].y = e.center.y + (-1.0)*e.ry*(e.center.x - e.focus_1.x)/get_length(e.center, e.focus_1);
    
    e.verteces[3].x = e.center.x*2.0 - e.verteces[3].x;
    e.verteces[3].y = e.center.y*2.0 - e.verteces[3].y;
    return ellipse_check_ellipse(e);

}
    
   

Point * ellipse_get_focuses(Ellipse e){
    static Point focuses[N_1];
    focuses[0] = e.focus_1;
    focuses[1] = e.focus_2; 
    return focuses;
}

Point * ellipse_get_vertices(Ellipse e){
    static Point v[4];
    for (int i = 0; i < 4; i++){
        v[i] = e.verteces[i];
    }
    return v;
}

double ellipse_get_rx(Ellipse e){
    return e.rx;
}

double ellipse_get_ry(Ellipse e){
    return e.ry;
}    

int ellipse_is_inside(Ellipse e, Point a){
    if(pow((a.x-e.center.x),2)/pow(e.rx, 2) + pow((a.y-e.center.y),2)/pow(e.ry, 2) <= 1){
        return 1;
    }
    else return 0;
}


double ellipse_get_square(Ellipse e){
    return M_PI*e.rx*e.ry;
}

int ellipse_input(FILE *fi, Ellipse e){
    int check;
    printf( "Choose a method of input: 1 -- coordinates of verteces, 0 -- foci and radiuses\n");
    fscanf(fi, "%i", &check);
    if (check){
        Point array[4];
        for (int i = 0; i < 4; i++){
            printf( "Vertex %i \n", i+1);
            printf( "x = ");
            fscanf(fi, "%lf", &array[i].x);
            printf( "y = ");
            fscanf(fi, "%lf", &array[i].y);
            return ellipse_init_verteces(e, array);
        }
    }
    else{
        Point focus_1, focus_2;
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
        return ellipse_init_focuses(e, focus_1, focus_2, xr, yr);
     }
    return 0;
}

void ellipse_print(FILE * fh, Ellipse e ){
    fprintf(fh, "<< Ellipse >>" );
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



   

double * ellipse_intersection_with_line(Ellipse e, double m, double c){
    
    static double res[5];                                                         
        
    double d = pow(2.0*e.rx*e.ry, 2)*(m*m*e.rx*e.rx + e.ry*e.ry + 2*m*ellipse_get_center(e).y*ellipse_get_center(e).x - 2*m*c*ellipse_get_center(e).x + 2*c*ellipse_get_center(e).y - c * c - ellipse_get_center(e).y*ellipse_get_center(e).y - m*m*ellipse_get_center(e).x*ellipse_get_center(e).x);
    double a = 2*ellipse_get_center(e).x*pow(e.ry,2) - 2*m*pow(e.rx,2)*c + 2*m*pow(e.rx,2)*ellipse_get_center(e).y;
       
    
    if (d<0) {res[4]=0; return res;}
    if (d==0) res [4]=1;
    if (d>0) res [4]=2;
        
    res[0] = (a+pow(d,0.5))/(2.0*(pow(e.ry,2)+pow(e.rx,2)*pow(m,2)));
    res[1] = m*res[0]+c;
    
    res[2] = (a-pow(d,0.5))/(2.0*(pow(e.ry,2)+pow(e.rx,2)*pow(m,2)));
    res[3] = m*res[2]+c;    
    return res;
}

Point * ellipse_intersection_with_ellipse(Ellipse e, Ellipse ellipse){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static Point res[4];
    double min_x = fmin(e.verteces[0].x, (*(ellipse_get_vertices(ellipse))).x);        
    double max_x = fmax(e.verteces[1].x, (*(ellipse_get_vertices(ellipse)+1)).x);        
    
    
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = ellipse_newton_raphson(e, ellipse, x, 1);
        eq2 = ellipse_newton_raphson(e, ellipse, x, 2);
        eq3 = ellipse_newton_raphson(e, ellipse, x, 3);
        eq4 = ellipse_newton_raphson(e, ellipse, x, 4);
        if (fabs(eq1-eq1_l)>EPS && (eq1 < e.verteces[1].x && eq1 > e.verteces[0].x)){
            eq1_sols[i1] = eq1;
            i1++;
            eq1_l = eq1;
        }
        

        if (fabs(eq2-eq2_l)>EPS && (eq2 < e.verteces[1].x && eq2 > e.verteces[0].x)){
            eq2_sols[i2] = eq2;
            i2++;
            eq2_l = eq2;
        }

       
        if (fabs(eq3-eq3_l)>EPS && (eq3 < e.verteces[1].x && eq3 > e.verteces[0].x)){
            eq3_sols[i3] = eq3;
            i3++;
            eq3_l = eq3;
        }
     

        if (fabs(eq4-eq4_l)>EPS && (eq4 < e.verteces[1].x && eq4 > e.verteces[0].x)){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
          
    }
    if (!i1 && !i2 && !i3 && !i4) return res;
            
    int i_s = 0;
    for (int i = 0; i < i1; i++) {
        Point r1;
        r1.x = eq1_sols[i];
        r1.y = ellipse_get_value(e, eq1_sols[i], 1);
        res[i_s] = r1; i_s++;
    }
    for (int i = 0; i < i2; i++) {
        Point r2;
        r2.x = eq2_sols[i];
        r2.y = ellipse_get_value(e, eq2_sols[i], 1);
        res[i_s] = r2; i_s++;
    }
    for (int i = 0; i < i3; i++) {
        Point r3; 
        r3.x = eq3_sols[i]; 
        r3.y = ellipse_get_value(e, eq3_sols[i], 1);
        res[i_s] = r3; i_s++;
    }
    for (int i = 0; i < i4; i++){
        Point r4;
        r4.x =  eq4_sols[i];
        r4.y = ellipse_get_value(e, eq4_sols[i], 1);
        res[i_s] = r4; i_s++;
    }
    return res;
}



 
void hyperbole_init(Hyperbole hyperbole, double array[5]){
    for (int i = 0; i < 5; i++){
        hyperbole.equation[i] = array[i];
    }
} 





double hyperbole_newton_raphson(Hyperbole h, Hyperbole hyperbole, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;

    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = ((hyperbole_get_value(h, x1+EPS, 1)-hyperbole_get_value(hyperbole, x1+EPS, 1)) - (hyperbole_get_value(h, x1, 1)-hyperbole_get_value(hyperbole, x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, 1)-hyperbole_get_value(hyperbole, x1, 1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((hyperbole_get_value(h, x1+EPS, -1)-hyperbole_get_value(hyperbole, x1+EPS, 1)) - (hyperbole_get_value(h, x1, -1)-hyperbole_get_value(hyperbole, x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, -1)-hyperbole_get_value(hyperbole, x1, 1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((hyperbole_get_value(h, x1+EPS, 1)-hyperbole_get_value(hyperbole, x1+EPS, -1)) - (hyperbole_get_value(h, x1, 1)-hyperbole_get_value(hyperbole, x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, 1)-hyperbole_get_value(hyperbole, x1, -1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((hyperbole_get_value(h, x1+EPS, -1)-hyperbole_get_value(hyperbole, x1+EPS, -1)) - (hyperbole_get_value(h, x1, -1)-hyperbole_get_value(hyperbole, x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, -1)-hyperbole_get_value(hyperbole, x1, -1))/dx;                  

        }
        
        if (count > 1000) return 0;
        count++;
    
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= EPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}




double hyperbole_newton_raphson_p(Hyperbole h, Parabola hyperbole, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;

    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = ((hyperbole_get_value(h, x1+EPS, 1)-parabola_get_value(hyperbole, x1+EPS)) - (hyperbole_get_value(h, x1, 1)-parabola_get_value(hyperbole, x1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, 1)-parabola_get_value(hyperbole, x1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((hyperbole_get_value(h, x1+EPS, -1)-parabola_get_value(hyperbole, x1+EPS)) - (hyperbole_get_value(h, x1, -1)-parabola_get_value(hyperbole, x1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, -1)-parabola_get_value(hyperbole, x1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((hyperbole_get_value(h, x1+EPS, 1)-parabola_get_value(hyperbole, x1+EPS)) - (hyperbole_get_value(h, x1, 1)-parabola_get_value(hyperbole, x1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, 1)-parabola_get_value(hyperbole, x1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((hyperbole_get_value(h, x1+EPS, -1)-parabola_get_value(hyperbole, x1+EPS)) - (hyperbole_get_value(h, x1, -1)-parabola_get_value(hyperbole, x1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (hyperbole_get_value(h, x1, -1)-parabola_get_value(hyperbole, x1))/dx;                  

        }
        
        if (count > 1000) return 0;
        count++;
    
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= EPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}
    
    
double hyperbole_get_x0(Hyperbole h ){
    return h.equation[0]; 
}

double hyperbole_get_y0(Hyperbole h ){
    return h.equation[1]; 
}

double hyperbole_get_a(Hyperbole h ){
    return h.equation[2]; 
}

double hyperbole_get_b(Hyperbole h ){
    return h.equation[3]; 
}
   
void hyperbole_input(FILE *fi, Hyperbole h){
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
    
    hyperbole_init(h, koefs);
}

void hyperbole_print(FILE * fh, Hyperbole h){
    
     fprintf(fh, "<< Hyperbola >>" );
     fprintf(fh, "x0 = %lf " , hyperbole_get_x0(h) );
     fprintf(fh, "y0 = %lf " , hyperbole_get_y0(h) );
     fprintf(fh, "a = %lf " , hyperbole_get_a(h) );
     fprintf(fh, "b = %lf " , hyperbole_get_b(h) );
}




Point * hyperbole_get_foci(Hyperbole h){
    static Point res[2];
    
    double e = pow(1.0+(hyperbole_get_b(h)*hyperbole_get_b(h))/(hyperbole_get_a(h)*hyperbole_get_a(h)), 0.5);
    if (h.equation[4] > 0){
    res[0].x = (hyperbole_get_a(h)*e+hyperbole_get_x0(h));
    res[0].y = hyperbole_get_y0(h);
    res[1].x = ((-1)*hyperbole_get_a(h)*e+hyperbole_get_x0(h));
    res[1].y = hyperbole_get_y0(h);        
    }
    else{
    res[0].y = (hyperbole_get_a(h)*e+hyperbole_get_x0(h));
    res[0].x = hyperbole_get_y0(h);
    res[1].y = ((-1)*hyperbole_get_a(h)*e+hyperbole_get_x0(h));
    res[1].x = hyperbole_get_y0(h); 
    }
           
    return res;
}


double hyperbole_get_value(Hyperbole h, double x, int sign ){
    return hyperbole_get_y0(h) + (sign/hyperbole_get_a(h))*hyperbole_get_b(h)*pow(fabs(hyperbole_get_a(h)*hyperbole_get_a(h) - x*x + 2*x*hyperbole_get_x0(h)-hyperbole_get_x0(h)*hyperbole_get_x0(h) ) , 0.5 );
}


    
int hyperbole_check_point(Hyperbole h, Point point){
    
    if (pow((point.x - hyperbole_get_x0(h)),2)/pow(hyperbole_get_a(h),2) + pow((point.y - hyperbole_get_y0(h)),2)/pow(hyperbole_get_b(h),2) >= 1) return 1;
    else return 0;      
}


Point * hyperbole_intersection_p(Hyperbole h, Parabola parabola){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static Point res[4];
    double min_x = -5;        
    double max_x = 5;        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = hyperbole_newton_raphson_p(h, parabola, x, 1);
        eq2 = hyperbole_newton_raphson_p(h, parabola, x, 2);
        eq3 = hyperbole_newton_raphson_p(h, parabola, x, 3);
        eq4 = hyperbole_newton_raphson_p(h, parabola, x, 4);
        if (fabs(eq1-eq1_l)>EPS_1 && fabs(hyperbole_get_value(h, eq1, 1) - parabola_get_value(parabola, eq1))<0.00001){
        eq1_sols[i1] = eq1;
        i1++;
        eq1_l = eq1;
        }

        if (fabs(eq2-eq2_l)>EPS_1 && fabs(hyperbole_get_value(h, eq2, -1) - parabola_get_value(parabola, eq2))<0.00001){
        eq2_sols[i2] = eq2;
        i2++;
        eq2_l = eq2;
        }

        if (fabs(eq3-eq3_l )>EPS_1 && fabs(hyperbole_get_value(h, eq3, 1) - parabola_get_value(parabola, eq3))<0.00001){
        eq3_sols[i3] = eq3;
        i3++;
        eq3_l = eq3;
        }

        if (fabs(eq4-eq4_l)>EPS_1 && fabs(hyperbole_get_value(h, eq4, -1) - parabola_get_value(parabola, eq4))<0.00001){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
    }
        
    int i_s = 0;
    for (int i = 0; i < i1; i++) {

        Point k;
        k.x = eq1_sols[i]; 
        k.y = hyperbole_get_value(h, eq1_sols[i],1);
        res[i_s] = k;
        i_s++;}
    for (int i = 0; i < i2; i++) {
    
        Point k;
        k.x = eq2_sols[i]; 
        k.y = hyperbole_get_value(h, eq2_sols[i],-1);
        res[i_s] = k;
        i_s++;    }
    for (int i = 0; i < i3; i++) {
    
        Point k;
        k.x = eq3_sols[i]; 
        k.y = hyperbole_get_value(h, eq3_sols[i],1);
        res[i_s] = k;
        i_s++;     }
    for (int i = 0; i < i4; i++) {

        Point k;
        k.x = eq4_sols[i]; 
        k.y = hyperbole_get_value(h, eq4_sols[i],-1);
        res[i_s] = k;
        i_s++;     }
    return res;

}


Point * hyperbole_intersection(Hyperbole h, Hyperbole parabola){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static Point res[4];
    double min_x = -5;        
    double max_x = 5;        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = hyperbole_newton_raphson(h, parabola, x, 1);
        eq2 = hyperbole_newton_raphson(h, parabola, x, 2);
        eq3 = hyperbole_newton_raphson(h, parabola, x, 3);
        eq4 = hyperbole_newton_raphson(h, parabola, x, 4);
        if (fabs(eq1-eq1_l)>EPS_1 && fabs(hyperbole_get_value(h, eq1, 1) - hyperbole_get_value(parabola, eq1, 1))<0.001){
        eq1_sols[i1] = eq1;
        i1++;
        eq1_l = eq1;
        }

        if (fabs(eq2-eq2_l)>EPS_1 && fabs(hyperbole_get_value(h, eq2, -1) - hyperbole_get_value(parabola, eq2, -1))<0.001){
        eq2_sols[i2] = eq2;
        i2++;
        eq2_l = eq2;
        }

        if (fabs(eq3-eq3_l )>EPS_1 && fabs(hyperbole_get_value(h, eq3, 1) - hyperbole_get_value(parabola, eq3, 1))<0.001){
        eq3_sols[i3] = eq3;
        i3++;
        eq3_l = eq3;
        }

        if (fabs(eq4-eq4_l)>EPS_1 && fabs(hyperbole_get_value(h, eq4, -1) - hyperbole_get_value(parabola, eq4, -1))<0.001){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
    }





    int i_s = 0;
    for (int i = 0; i < i1; i++) {

        Point k;
        k.x = eq1_sols[i]; 
        k.y = hyperbole_get_value(h, eq1_sols[i], 1);
        res[i_s] = k;
        i_s++;}
    for (int i = 0; i < i2; i++) {
    
        Point k;
        k.x = eq2_sols[i]; 
        k.y = hyperbole_get_value(h, eq2_sols[i], -1);
        res[i_s] = k;
        i_s++;    }
    for (int i = 0; i < i3; i++) {
    
        Point k;
        k.x = eq3_sols[i]; 
        k.y = hyperbole_get_value(h, eq3_sols[i], 1);
        res[i_s] = k;
        i_s++;     }
    for (int i = 0; i < i4; i++) {

        Point k;
        k.x = eq4_sols[i]; 
        k.y = hyperbole_get_value(h, eq4_sols[i], -1);
        res[i_s] = k;
        i_s++;     }
        
    return res;

}


