#include "curves.h"


// Parabola methods


void Parabola::init(double array[3]){
    for (int i = 0; i < 3; i++)
        this->equation[i] = array[i];
}


double Parabola::get_a(){
    return this->equation[0];
}

double Parabola::get_b(){
    return this->equation[1];
}

double Parabola::get_c(){
    return this->equation[2];
}    

double Parabola::get_value(double x){
    return this->equation[0]*pow(x,2) + this->equation[1]*x + this->equation[2];
} 

Point Parabola::get_focus(){
    struct Point res;
    res.x =(-1)* this->equation[1]/(2*this->equation[0]);
    res.y = (-1)*((pow(this->equation[1],2)-1)/(4*this->equation[0]))+this->equation[2];
    return res;
}



void Parabola::input(istream& inp){
    cout << " << Parabola >> " << endl;
    cout << "a = ";
    inp >> this->equation[0];
    cout << "b = ";
    inp >> this->equation[1];
    cout << "c = ";
    inp >> this->equation[2];
}

void Parabola::print(ostream& out ){
    out << "y=" << this->equation[0] << "*x^2 + " << this->equation[1] << "*x + " << this->equation[2] << endl;
}

int Parabola::check_point(Point point){
    return point.y >= get_value(point.x);
}

Point * Parabola::intersection(double k, double m){
    
    static Point res[2];
    double d = pow(this->equation[1]-k,2) - 4.0*this->equation[0]*(this->equation[2]-m);

    if (d<0)
        throw logic_error("There are not intersection points.");
    else {
        res[0].x = ((k-this->equation[1])+pow(d, 0.5))/(2.0*this->equation[0]);
        res[0].y = res[0].x*k+m;        
        
        res[1].x = ((k-this->equation[1])-pow(d, 0.5))/(2.0*this->equation[0]);
        res[1].y = res[1].x*k+m;        
        return res;
    }
}

Point * Parabola::intersection(Parabola other){
    static Point res[2];
    
    double d = pow(this->equation[1]-other.get_b(), 2) - 4.0*(this->equation[0]-other.get_a())*(this->equation[2]-other.get_c());
            
    if (d<0)
        throw logic_error("There are  not intersection points.");
    else {
           
        res[0].x = ((-1.0)*(this->equation[1] - other.get_b())-pow(d,0.5))/(this->equation[0]-other.get_a());
        res[0].y = other.get_value(res[0].x);
                          
        res[1].x = ((-1.0)*(this->equation[1] - other.get_b())+pow(d,0.5))/(this->equation[0]-other.get_a());
        res[1].y = other.get_value(res[0].x);
        return res; 
      
    }
}    

double Parabola::intersection_square(double k, double m){
    Point *points;
    points = intersection(k, m);
    double x1 = (*points).x;      
    double x2 = (*(points+1)).x;      
    
    double res = abs((get_c()-m)*x1 + (get_a()*pow(x1,3))/3.0 + (get_b() - k)*pow(x1,2)/2.0 - 
                    (get_c()-m)*x2 + (get_a()*pow(x2,3))/3.0 + ((get_b() - k)*pow(x2,2))/2.0);

    return res;
}


double Parabola::intersection_square(Parabola other){

    Point *points;
    points = intersection(other);
    double x1 = (*points).x;      
    double x2 = (*(points+1)).x;        
    
    double res = abs((x1*(get_c()-other.get_c()) + pow(x1,2.0)/2.0*(get_b()-other.get_b()) + pow(x1,3.0)/3.0*(get_a()-other.get_a())) - 
        (x2*(get_c()-other.get_c()) + pow(x2,2.0)/2.0*(get_b()-other.get_b()) + pow(x2,3.0)/3.0*(get_a()-other.get_a())));
    
    return res;
}
 


// Ellipse methods


void Ellipse::check_ellipse(){
    
    if(this->center.x != (this->verteces[2].x + this->verteces[3].x)/2.0 ||
    this->center.y != (this->verteces[2].y + this->verteces[3].y)/2.0)
    {throw logic_error("The figure is not an ellipse");}
    
    if (this->verteces[0].y != this->verteces[1].y ||
        this->verteces[2].x != this->verteces[2].x){
        throw logic_error("We suppose that ellipses have their axises parallel to OX/OY axis");}
}



double Ellipse::newton_raphson(Ellipse ellipse, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;
    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = (((get_value(x1+EPS, 1) - ellipse.get_value(x1+EPS, 1))) - (get_value(x1, 1) - ellipse.get_value(x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, 1)-ellipse.get_value(x1, 1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((get_value(x1+EPS, -1)-ellipse.get_value(x1+EPS, 1)) - (get_value(x1, -1)-ellipse.get_value(x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, -1)-ellipse.get_value(x1, 1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((get_value(x1+EPS, 1)-ellipse.get_value(x1+EPS, -1)) - (get_value(x1, 1)-ellipse.get_value(x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, 1)-ellipse.get_value(x1, -1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((get_value(x1+EPS, -1)-ellipse.get_value(x1+EPS, -1)) - (get_value(x1, -1)-ellipse.get_value(x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, -1)-ellipse.get_value(x1, -1))/dx;                  

        }
    
        if (count > 1000) return 0;
        count++;
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= EPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}

                    
    
void Ellipse::calc_center(){
    this->center.x = (this->verteces[0].x + this->verteces[1].x)/2.0;
    this->center.y = (this->verteces[0].y + this->verteces[1].y)/2.0;

}


double Ellipse::get_length(Point a, Point b){
    return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}
 

void Ellipse::calc_center_2(){
    this->center.x = (this->focus_1.x + this->focus_2.x)/2;
    this->center.y = (this->focus_1.y + this->focus_2.y)/2;
}    


void Ellipse::init(Point array[4]){

    for(int i = 0; i < 4; i++){
        this->verteces[i] = array[i];
    }
    
    calc_center();
    
    this->rx = get_length(this->center, this->verteces[0]);
    this->ry = get_length(this->center, this->verteces[2]);
    double foci = pow(fabs(pow(this->rx,2)-pow(this->ry,2)),0.5);
    
    
    this->focus_1 = {this->center.x + foci*(this->center.x - this->verteces[0].x)/get_length(this->center, this->verteces[0]),
                     this->center.y + foci*(this->center.y - this->verteces[0].y)/get_length(this->center, this->verteces[0])};
    

    this->focus_2 = {this->center.x - foci*(this->center.x - this->verteces[0].x)/get_length(this->center, this->verteces[0]),
                     this->center.y - foci*(this->center.y - this->verteces[0].y)/get_length(this->center, this->verteces[0])};
    
    check_ellipse();
    
}

    
void Ellipse::init(Point f_1, Point f_2, double rx, double ry){
    this->focus_1 = f_1;
    this->focus_2 = f_2;
    this->rx = rx;
    this->ry = ry;
    calc_center_2();
    
    this->verteces[0] = {this->center.x + this->rx*(this->center.x - this->focus_1.x)/get_length(this->center, this->focus_1),
                         this->center.y + this->rx*(this->center.y - this->focus_1.y)/get_length(this->center, this->focus_1)};
    
    this->verteces[1] = {this->center.x*2.0 - this->verteces[0].x, this->center.y*2.0 - this->verteces[0].y};
    
    this->verteces[2] = {this->center.x + this->ry*(this->center.y - this->focus_1.y)/get_length(this->center, this->focus_1),
                         this->center.y + (-1.0)*this->ry*(this->center.x - this->focus_1.x)/get_length(this->center, this->focus_1)};
    
    this->verteces[3] = {this->center.x*2.0 - this->verteces[2].x, this->center.y*2.0 - this->verteces[2].y};
    check_ellipse();
}
    
   
Point Ellipse::get_center(){
    return this->center;
}

Point * Ellipse::get_focuses(){
    static Point focuses[2] = {this->focus_1, this->focus_2}; 
    return focuses;
}

Point * Ellipse::get_vertices(){
    return this->verteces;
}

double Ellipse::get_rx(){
    return this->rx;
}

double Ellipse::get_ry(){
    return this->ry;
}    

int Ellipse::is_inside(Point a){
    if(pow((a.x-this->center.x),2)/pow(this->rx, 2) + pow((a.y-this->center.y),2)/pow(this->ry, 2) <= 1){
        return 1;
    }
    else return 0;
}


double Ellipse::get_square(){
    return M_PI*this->rx*this->ry;
}

void Ellipse::input(istream& inp){
    int check;
    cout << "Choose a method of input: 1 -- coordinates of verteces, 0 -- foci and radiuses" << endl;
    inp >> check;
    if (check){
        Point array[4];
        for (int i = 0; i < 4; i++){
            cout << "Vertex " << i+1 << endl;
            cout << "x = ";
            inp >> array[i].x;
            cout << "y = ";
            inp >> array[i].y;
        }
        init(array);
    }
    else{
        Point focus_1, focus_2;
        double xr, yr;
        cout << "Focus_1" << endl;
        cout << "x = ";
        inp >> focus_1.x;
        cout << "y = ";
        inp >> focus_1.y;
        cout << "Focus_2"<< endl;
        cout << "x = ";
        inp >> focus_2.x;
        cout << "y = ";
        inp >> focus_2.y;
        cout << "XR = ";
        inp >> xr;
        cout << "YR = ";
        inp >> yr;
        init(focus_1, focus_2, xr, yr);
     }
}

void Ellipse::print(ostream& out ){
    out << "<< Ellipse >>" << endl;
    out << "-- Center --" << endl;
    out << "(" << this->center.x << "," << this->center.y << ")" << endl;
    out << "-- Verteces --" << endl;
    for (int i = 0; i < 4; i++){
        out << "(" << this->verteces[i].x << "," << this->verteces[i].y << ")" << endl;
    }
    out << "-- Focus_1 --" << endl;
    out << "(" << this->focus_1.x << "," << this->focus_1.y << ")" << endl;
    out << "-- Focus_2 --" << endl;
    out << "(" << this->focus_2.x << "," << this->focus_2.y << ")" << endl;
}



double Ellipse::get_value(double x, int sign){
    
    double A = 1.0/pow(this->rx, 2);        
    double B = 1.0/pow(this->ry, 2);         
    double C = 0.0;
    double D = (-2.0)*get_center().x / pow(this->rx, 2);
    double E = (-2.0)*get_center().y / pow(this->ry, 2);        
    double F = pow(get_center().x, 2)/pow(this->rx, 2) +  pow(get_center().y, 2)/pow(this->ry, 2) - 1;
    
    double res = ((-1.0)*(C*x+E) + sign*pow( fabs(pow(C*x+E,2) - 4*B*(A*x*x + D*x + F)), 0.5 ))/(2.0*B);
    
    // double res = (get_ry()*pow(pow(get_rx(),2)-pow(x,2)+2*x*get_center().x-pow(get_center().x,2),2))/get_rx()+get_center().y;
    return res;
}
   

Point * Ellipse::intersection(double m, double c){
    
    static Point res[2];                                                         
    double d = pow(2.0*this->rx*this->ry, 2)*(m*m*this->rx*this->rx + this->ry*this->ry + 2*m*get_center().y*get_center().x - 2*m*c*get_center().x + 2*c*get_center().y - c * c - get_center().y*get_center().y - m*m*get_center().x*get_center().x);
    double a = 2*get_center().x*pow(this->ry,2) - 2*m*pow(this->rx,2)*c + 2*m*pow(this->rx,2)*get_center().y;
         
    if (d<0) throw logic_error("There are not intersection points.");
            
    res[0].x = (a+pow(d,0.5))/(2.0*(pow(this->ry,2)+pow(this->rx,2)*pow(m,2)));
    res[0].y = m*res[0].x+c;
    
    res[1].x = (a-pow(d,0.5))/(2.0*(pow(this->ry,2)+pow(this->rx,2)*pow(m,2)));
    res[1].y = m*res[1].x+c;
    return res;
}

Point * Ellipse::intersection(Ellipse ellipse){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static Point res[4];
    double min_x = fmin(this->verteces[0].x, (*(ellipse.get_vertices())).x);        
    double max_x = fmax(this->verteces[1].x, (*(ellipse.get_vertices()+1)).x);        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = newton_raphson(ellipse, x, 1);
        eq2 = newton_raphson(ellipse, x, 2);
        eq3 = newton_raphson(ellipse, x, 3);
        eq4 = newton_raphson(ellipse, x, 4);
        if (fabs(eq1-eq1_l)>EPS && (eq1 < this->verteces[1].x && eq1 > this->verteces[0].x)){
            eq1_sols[i1] = eq1;
            i1++;
            eq1_l = eq1;
        }
        

        if (fabs(eq2-eq2_l)>EPS && (eq2 < this->verteces[1].x && eq2 > this->verteces[0].x)){
            eq2_sols[i2] = eq2;
            i2++;
            eq2_l = eq2;
        }

       
        if (fabs(eq3-eq3_l)>EPS && (eq3 < this->verteces[1].x && eq3 > this->verteces[0].x)){
            eq3_sols[i3] = eq3;
            i3++;
            eq3_l = eq3;
        }
     

        if (fabs(eq4-eq4_l)>EPS && (eq4 < this->verteces[1].x && eq4 > this->verteces[0].x)){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
          
    }
    
    if (!i1 && !i2 && !i3 && !i4) throw logic_error("There are not intersection points.");
        
    int i_s = 0;
    for (int i = 0; i < i1; i++) {res[i_s] = Point{eq1_sols[i], get_value(eq1_sols[i])}; i_s++;}
    for (int i = 0; i < i2; i++) {res[i_s] = Point{eq2_sols[i], get_value(eq2_sols[i])}; i_s++;}
    for (int i = 0; i < i3; i++) {res[i_s] = Point{eq3_sols[i], get_value(eq3_sols[i])}; i_s++;}
    for (int i = 0; i < i4; i++) {res[i_s] = Point{eq4_sols[i], get_value(eq4_sols[i])}; i_s++;}
    return res;
}
  

  





void Hyperbole::init(double array[5]){
    for (int i = 0; i < 5; i++){
        this->equation[i] = array[i];
    }
} 


double Hyperbole::newton_raphson(Hyperbole hyperbole, double x2, int mode) 
{ 
    double x1, dx;
    int count = 0;

    do
    { 
        x1=x2;
        
        if (mode == 1){
            dx = ((get_value(x1+EPS, 1)-hyperbole.get_value(x1+EPS, 1)) - (get_value(x1, 1)-hyperbole.get_value(x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, 1)-hyperbole.get_value(x1, 1))/dx; 
        }
        else if (mode == 2){
            
            dx = ((get_value(x1+EPS, -1)-hyperbole.get_value(x1+EPS, 1)) - (get_value(x1, -1)-hyperbole.get_value(x1, 1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, -1)-hyperbole.get_value(x1, 1))/dx;
        }
        else if (mode == 3){
                            
            dx = ((get_value(x1+EPS, 1)-hyperbole.get_value(x1+EPS, -1)) - (get_value(x1, 1)-hyperbole.get_value(x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, 1)-hyperbole.get_value(x1, -1))/dx;                 
            
        }
        else if (mode == 4){

            dx = ((get_value(x1+EPS, -1)-hyperbole.get_value(x1+EPS, -1)) - (get_value(x1, -1)-hyperbole.get_value(x1, -1)))/EPS;
            if (dx == 0) return 0;
            x2 = x1 - (get_value(x1, -1)-hyperbole.get_value(x1, -1))/dx;                  

        }
        
        if (count > 1000) return 0;
        count++;
    
  
        /* Xi+1 = Xi - f(x) / f'(x) */
        // x2 = x1 - func(x1)/derivative(func, x1); 
    
    }while(fabs(x2-x1) >= EPS);
    /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
    return x2;
}


double Hyperbole::newton_raphson(Parabola parabola, double x2, int mode) 
    { 
        double x1, dx;
        int count = 0;

        do
        { 
            x1=x2;
        
            if (mode == 1){
                dx = ((get_value(x1+EPS, 1)-parabola.get_value(x1+EPS)) - (get_value(x1, 1)-parabola.get_value(x1)))/EPS;
                if (dx == 0) return 0;
                x2 = x1 - (get_value(x1, 1)-parabola.get_value(x1))/dx; 
            }
            else if (mode == 2){
            
                dx = ((get_value(x1+EPS, -1)-parabola.get_value(x1+EPS)) - (get_value(x1, -1)-parabola.get_value(x1)))/EPS;
                if (dx == 0) return 0;
                x2 = x1 - (get_value(x1, -1)-parabola.get_value(x1))/dx;
            }
            else if (mode == 3){
                dx = ((get_value(x1+EPS, 1)-parabola.get_value(x1+EPS)) - (get_value(x1, 1)-parabola.get_value(x1)))/EPS;
                if (dx == 0) return 0;
                x2 = x1 - (get_value(x1, 1)-parabola.get_value(x1))/dx;                 
            
            }
            else if (mode == 4){
                dx = ((get_value(x1+EPS, -1)-parabola.get_value(x1+EPS)) - (get_value(x1, -1)-parabola.get_value(x1)))/EPS;
                if (dx == 0) return 0;
                x2 = x1 - (get_value(x1, -1)-parabola.get_value(x1))/dx;                  

            }
            
            if (count > 1000) return 0;
            count++;
  
            /* Xi+1 = Xi - f(x) / f'(x) */
            // x2 = x1 - func(x1)/derivative(func, x1); 
    
        }while(fabs(x2-x1) >= EPS);
        /* Stop the loop when |Xi+1 - Xi| becomes less than the desired accuracy(e) */
   
        return x2;
    }

    
    
double Hyperbole::get_x0(){
    return this->equation[0]; 
}

double Hyperbole::get_y0(){
    return this->equation[1]; 
}

double Hyperbole::get_a(){
    return this->equation[2]; 
}

double Hyperbole::get_b(){
    return this->equation[3]; 
}
   
void Hyperbole::input(istream& inp ){
    double koefs[5];
    double r;
    cout << "<< Hyperbola >>" << endl;
    cout << "x0 = ";
    inp >> koefs[0];
    cout << "y0 = ";
    inp >> koefs[1];
    cout << "a = ";
    inp >> koefs[2];
    cout << "b = ";
    inp >> koefs[3];
    cout << "r = ";
    inp >> r;
    koefs[2] /= fabs(r);
    koefs[3] /= fabs(r);
    koefs[4]  = r/fabs(r);    
    
    init(koefs);
}

void Hyperbole::print(ostream& out){
    
    cout << "<< Hyperbola >>" << endl;
    cout << "x0 = " << get_x0() << endl;
    cout << "y0 = " << get_y0() << endl;
    cout << "a = " << get_a() << endl;
    cout << "b = " << get_b() << endl;
}


Point * Hyperbole::get_foci(){
    static Point res[2];
    
    double e = pow(1.0+(get_b()*get_b())/(get_a()*get_a()), 0.5);
    if (this->equation[4] > 0){
    res[0].x = (get_a()*e+get_x0());
    res[0].y = get_y0();
    res[1].x = ((-1)*get_a()*e+get_x0());
    res[1].y = get_y0();        
    }
    else{
    res[0].y = (get_a()*e+get_x0());
    res[0].x = get_y0();
    res[1].y = ((-1)*get_a()*e+get_x0());
    res[1].x = get_y0(); 
    }
           
    return res;
}

    
bool Hyperbole::check_point(Point point){
    
    return pow((point.x - get_x0()),2)/pow(get_a(),2) + pow((point.y - get_y0()),2)/pow(get_b(),2) >= this->equation[4];       
}


double Hyperbole::get_value(double x, int sign ){
    return get_y0() + (sign/get_a())*get_b()*pow(fabs(get_a()*get_a() - x*x + 2*x*get_x0()-get_x0()*get_x0() ) , 0.5 );
}

 

Point * Hyperbole::intersection(Parabola parabola){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static Point res[4];
    double min_x = -5;        
    double max_x = 5;        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = newton_raphson(parabola, x, 1);
        eq2 = newton_raphson(parabola, x, 2);
        eq3 = newton_raphson(parabola, x, 3);
        eq4 = newton_raphson(parabola, x, 4);
        if (abs(eq1-eq1_l)>EPS_1 && fabs(get_value(eq1) - parabola.get_value(eq1))<0.00001){
        eq1_sols[i1] = eq1;
        i1++;
        eq1_l = eq1;
        }

        if (abs(eq2-eq2_l)>EPS_1 && fabs(get_value(eq2) - parabola.get_value(eq2))<0.00001){
        eq2_sols[i2] = eq2;
        i2++;
        eq2_l = eq2;
        }

        if (abs(eq3-eq3_l )>EPS_1 && fabs(get_value(eq3) - parabola.get_value(eq3))<0.00001){
        eq3_sols[i3] = eq3;
        i3++;
        eq3_l = eq3;
        }

        if (abs(eq4-eq4_l)>EPS_1 && fabs(get_value(eq4) - parabola.get_value(eq4))<0.00001){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
    }
        
    int i_s = 0;
    for (int i = 0; i < i1; i++) {res[i_s] = Point{eq1_sols[i], get_value(eq1_sols[i])}; i_s++;}
    for (int i = 0; i < i2; i++) {res[i_s] = Point{eq2_sols[i], get_value(eq2_sols[i])}; i_s++;}
    for (int i = 0; i < i3; i++) {res[i_s] = Point{eq3_sols[i], get_value(eq3_sols[i])}; i_s++;}
    for (int i = 0; i < i4; i++) {res[i_s] = Point{eq4_sols[i], get_value(eq4_sols[i])}; i_s++;}
    return res;

}


Point * Hyperbole::intersection(Hyperbole parabola){
    double eq1, eq2, eq3, eq4, eq1_l = 0, eq2_l = 0, eq3_l = 0, eq4_l = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0;
    double eq1_sols[2], eq2_sols[2],eq3_sols[2],eq4_sols[2];
    static Point res[4];
    double min_x = -5;        
    double max_x = 5;        
    
    for (float x = min_x; x <= max_x; x += 0.5){
        eq1 = newton_raphson(parabola, x, 1);
        eq2 = newton_raphson(parabola, x, 2);
        eq3 = newton_raphson(parabola, x, 3);
        eq4 = newton_raphson(parabola, x, 4);
        if (abs(eq1-eq1_l)>EPS_1 && fabs(get_value(eq1) - parabola.get_value(eq1))<0.001){
        eq1_sols[i1] = eq1;
        i1++;
        eq1_l = eq1;
        }

        if (abs(eq2-eq2_l)>EPS_1 && fabs(get_value(eq2) - parabola.get_value(eq2))<0.001){
        eq2_sols[i2] = eq2;
        i2++;
        eq2_l = eq2;
        }

        if (abs(eq3-eq3_l )>EPS_1 && fabs(get_value(eq3) - parabola.get_value(eq3))<0.001){
        eq3_sols[i3] = eq3;
        i3++;
        eq3_l = eq3;
        }

        if (abs(eq4-eq4_l)>EPS_1 && fabs(get_value(eq4) - parabola.get_value(eq4))<0.001){
            eq4_sols[i4] = eq4;
            i4++;
            eq4_l = eq4;
        }
    }
        
    int i_s = 0;
    for (int i = 0; i < i1; i++) {res[i_s] = Point{eq1_sols[i], get_value(eq1_sols[i])}; i_s++;}
    for (int i = 0; i < i2; i++) {res[i_s] = Point{eq2_sols[i], get_value(eq2_sols[i])}; i_s++;}
    for (int i = 0; i < i3; i++) {res[i_s] = Point{eq3_sols[i], get_value(eq3_sols[i])}; i_s++;}
    for (int i = 0; i < i4; i++) {res[i_s] = Point{eq4_sols[i], get_value(eq4_sols[i])}; i_s++;}
    return res;

}








