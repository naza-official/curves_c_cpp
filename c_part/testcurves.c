#include "ccurves.h"
#include <stdio.h>




Ellipse test_create_ellipse_console(){
    Ellipse ellipse;
    int t = ellipse_input(ellipse);
    printf("\n");
    ellipse_print(ellipse);
    if (t) printf("Test complited!\n");
    else  printf("Test failed!\n");
    return ellipse; 
}


void test_check_point_ellipse_console(Ellipse ellipse){
    Point x;
    printf("Is inside point test\n");
    printf("Enter point \n");
    printf("x = ");
    scanf("%lf", &x.x);
    printf("y = ");
    scanf("%lf", &x.y);
    printf("Point: x = %lf y = %lf\n", x.x, x.y);
    int res = ellipse_is_inside(ellipse, x);
    
    printf("Test complited!\n");
    printf("Result: %i \n", res); 
} 



void test_square_ellipse_console(Ellipse ellipse){
    printf("Square of ellipse\n");
    double res = ellipse_get_square(ellipse);
    if (res >= 0) printf("Test complited!\n");
    else printf("Test failed!\n");
    printf("Result: %lf\n", res); 
}


void test_get_value_ellipse(Ellipse ellipse  ){
    double res, x;
    printf("Value in the point!\n");
    scanf("%lf", &x);
    
    res = ellipse_get_value(ellipse, x, 1);
    if (fabs(res) == fabs(ellipse_get_value(ellipse, x, -1))){
        printf("Test completed!\n");
    }
    else printf("Test failed!\n");
    
    printf("Result: %lf\n", res);
    
}


void test_intersection_ellipse_with_ellipse(Ellipse ellipse){
    printf("test_intersection_ellipse_with_ellipse\n");
    Ellipse ellipse_2;
    ellipse_input(ellipse);
             
    Point *root;
     
    root = ellipse_intersection_with_ellipse(ellipse, ellipse_2);
    for (int i = 0; i<8; i++){
        if (((*(root+i)).x!=0) || ((*(root+i)).y !=0)) 
        {
            printf("Point %i\n",  i+1);
            printf("x: %lf\n", (*(root+i)).x);
            printf("y: %lf\n", (*(root+i)).y);
        }
    }
    printf("Test completed!\n");
}


void test_intersection_ellipse_with_line(Ellipse ellipse){
             
    double *root;
    double m, c;
    printf("test_intersection_ellipse_with_line y = mx+c\n");
    printf("m = ");
    scanf("%lf", &m);
    printf("c = ");
    scanf("%lf", &c);

    root = ellipse_intersection_with_line(ellipse, m, c);
    
    for (int i = 0; i<4; i++){
        if (((*(root+i))!=0) || ((*(root+i+1)) !=0)) 
        {
            

            printf("Point \n");
            printf("x: %lf\n", (*(root+i)));
            i++;
            printf("y: %lf\n", (*(root+i)));
            
        }
    }
    printf("Test completed!\n");
}







Parabola test_create_parabol(){
    Parabola parabola;
    parabola_input(parabola);
    printf("\n");
    parabola_print(parabola);
    printf("Test complited!\n");
    return parabola; 
}



void test_check_point_parabola(Parabola parabola  ){
    Point x;
    printf("Is inside point test\n");
    printf("Enter point \n");
    printf("x = ");
    scanf("%lf", &x.x);
    printf("y = ");
    scanf("%lf", &x.y);
    printf("Point: x = %lf y = %lf\n", x.x, x.y);
    int res = parabola_check_point(parabola, x);
    
    printf("Test complited!\n");
    printf("Result: %i\n", res); 
} 


void test_get_value_parabola(Parabola parabola){
    double x;
    printf("Get value test\n");
    printf("Enter x\n");
    printf("x = ");
    scanf("%lf", &x);

    double res = parabola_get_value(parabola, x);
    printf("Point: f(x) = %lf", res);
    printf("Test complited!\n");
} 



void test_get_focus_parabola(Parabola parabola  ){
    printf("Get focus test\n");

    Point res = parabola_get_focus(parabola);
    printf("Point: x = %lf y = %lf\n", res.x, res.y);
    if (parabola_check_point(parabola, res)) printf("Test complited!\n");
    else printf("Test failed!\n");
} 


void parabola_intersection(Parabola parabola){
    int choice;
    double *root;
    printf("Intersection test\n");
    printf("Intersection with 1 -- line, 2 -- parabola\n");
    scanf("%i", &choice);
    if (choice == 1){
        printf("LINE\n");
        double k, m;
        printf("k = ");
        scanf("%lf", &k);
        printf("m = ");
        scanf("%lf", &m);
        root = parabola_intersection_with_line(parabola, k, m);
        
    }
    else{
        Parabola parabola_2;
        parabola_input(parabola_2);
        root = parabola_intersection_with_parabola(parabola, parabola_2);
                
    }

    for (int i = 0; i<4; i++){
        if (((*(root+i))!=0) || ((*(root+i+1)) !=0)) 
        {
            
            printf("Point \n");
            printf("x: %lf\n", (*(root+i)));
            i++;
            printf("y: %lf\n", (*(root+i)));
            
        }
    }
    printf("Test completed!\n");
}



void test_parabola_intersection_square(Parabola parabola){
    int choice;
    double root;
    printf("Intersection square\n");
    printf("Intersection with 1 -- line, 2 -- parabola\n");
    scanf("%i", &choice);
    if (choice == 1){
        printf("LINE\n");
        double k, m;
        printf("k = ");
        scanf("%lf", &k);
        printf("m = ");
        scanf("%lf", &m);
        root = parabola_intersection_square_with_line(parabola, k, m);
        
    }
    else{
        Parabola parabola_2;
        parabola_input(parabola_2);
        root = parabola_intersection_square(parabola_2, parabola);
                
    }
    printf("Result: %lf\n", root);
    printf("Test completed!\n");
}



Hyperbole test_create_hyperbole(){
    Hyperbole hyperbole;
    hyperbole_input(hyperbole);
    printf("\n");
    hyperbole_print(hyperbole);
    printf("Test complited!\n");
    return hyperbole; 
}


void test_check_point_hyperbole(Hyperbole hyperbole  ){
    Point x;
    printf("Is inside point test\n");
    printf("Enter point \n");
    printf("x = ");
    scanf("%lf", &x.x);
    printf("y = ");
    scanf("%lf", &x.y);
    printf("Point: x = %lf y = %lf\n", x.x, x.y);
    int res = hyperbole_check_point(hyperbole, x);
    
    printf("Test complited!\n");
}




void test_get_value_hyperbole(Hyperbole hyperbole){
    double x;
    printf("Get value test\n");
    printf("Enter x\n");
    printf("x = ");
    scanf("%lf", &x);

    double res = hyperbole_get_value(hyperbole, x, 1);
    printf("Result: %lf\n", res);
    printf("Test complited!\n");
} 



void test_get_foci_hyperbole(Hyperbole hyperbole  ){
    printf("Get focus test\n");

    Point *res = hyperbole_get_foci(hyperbole);
    printf("Point1: x = %lf  y = %lf", (*(res)).x, (*(res)).y);
    printf("Point2: x = %lf  y = %lf", (*(res+1)).x, (*(res+1)).y);
    if (hyperbole_check_point(hyperbole, *(res))) printf("Test complited!\n");
    else printf("Test failed!\n");
} 




void test_hyperbole_intersection(Hyperbole hyperbole){
    int choice;
    Point *root;
    printf("Intersection test\n");
    printf("Intersection with 1 -- parabola, 2 -- hyperbole\n");
    scanf("%i", &choice);
    if (choice == 1){
        printf("Parabola\n");
        Parabola parabola;
        parabola_input(parabola);
        root = hyperbole_intersection_p(hyperbole, parabola);
        
    }
    else{
        printf("Hyperbole\n");
        Hyperbole hyperbole_2;
        hyperbole_input(hyperbole);
        root = hyperbole_intersection(hyperbole, hyperbole_2);
                
    }

    for (int i = 0; i<4; i++){
        // if (((*(root+i)).x!=0) || ((*(root+i)).y !=0)) 
        // {
            printf("Point %i \n", i+1);

            printf("x: %lf\n", (*(root+i)).x);
            printf("y: %lf\n", (*(root+i)).y);
        // }
    }
    printf("Test completed!\n");
}







int main(){
    Parabola p;
    Hyperbole h;
    Ellipse e;
    
    

    return 0;
}
