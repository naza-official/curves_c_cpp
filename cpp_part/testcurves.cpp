#include "curves.h"
#include <string>
// #include <fstream>
// #include <istream>
// #include <ostream>

Ellipse test_create_ellipse(ostream& out = cout, istream& inp = cin){
    Ellipse ellipse;
    ellipse.input(inp);
    out << endl;
    ellipse.print(out);
    out << "Test complited!" << endl;
    out << "Result: " << &ellipse << endl; 
    return ellipse; 
}


void test_check_point_ellipse_console(Ellipse ellipse, ostream& out = cout){
    Point x;
    out << "Is inside point test" << endl;
    cout << "Enter point " << endl;
    cout << "x = ";
    cin >> x.x;
    cout << "y = ";
    cin >> x.y;
    out << "Point: x = " << x.x << " y = " << x.y << endl;
    int res = ellipse.is_inside(x);
    
    out << "Test complited!" << endl;
    out << "Result: " << res << endl; 
} 



void test_square_ellipse(Ellipse ellipse, ostream& out = cout){
    cout << "Square of ellipse: " << &ellipse << endl;
    double res = ellipse.get_square();
    out << "Square of ellipse: " << &ellipse << endl;
    if (res >= 0) out << "Test complited!" << endl;
    else out << "Test failed!" << endl;
    out << "Result: " << res << endl; 
}


void test_get_value_ellipse(Ellipse ellipse, ostream& out = cout){
    double res, x;
    out << "Value in the point!" << endl;
    cin >> x;
    
    res = ellipse.get_value(x, 1);
    if (abs(res) == abs(ellipse.get_value(x, -1))){
        out << "Test completed!" << endl;
    }
    else out << "Test failed!" << endl;
    
    out << res << endl;
    
}


void test_intersection_ellipse(Ellipse ellipse, ostream& out = cout, istream& inp = cin){
    int t;
    Point *root;
    cout << "enter 1 -- intersection with line | 0 -- ellipse" << endl;
    inp >> t;
    
    if (!t){
    out << "test_intersection_ellipse_with_ellipse" << endl;
    Ellipse ellipse_2;
    ellipse_2 = test_create_ellipse(cout, inp);
             
     
    ellipse.intersection(ellipse_2);
    for (int i = 0; i<4; i++){
        if (((*(root+i)).x!=0) || ((*(root+i)).y !=0)) 
        {
            out << "Point " << i+1 << endl;

            out << "x: " << (*(root+i)).x << endl;
            out << "y: " << (*(root+i)).y << endl;
        }
    }
    out << "Test completed!" << endl;}
    else{
        
        double m, c;
        out << "test_intersection_ellipse_with_line y = mx+c" << endl;
        cout << "m = ";
        inp >> m;
        cout << "c = ";
        inp >>c;

        root = ellipse.intersection(m, c);
    
        for (int i = 0; i<2; i++){
            if (((*(root+i)).x!=0) || ((*(root+i)).y !=0)) 
            {
                out << "Point " << i+1 << endl;

                out << "x: " << (*(root+i)).x << endl;
                out << "y: " << (*(root+i)).y << endl;
            }
        }
        out << "Test completed!" << endl;
    
    }
}




Parabola test_create_parabola(ostream& out = cout, istream& inp = cin){
    Parabola parabola;
    parabola.input(inp);
    out << endl;
    parabola.print(out);
    out << "Test complited!" << endl;
    out << "Result: " << &parabola << endl; 
    return parabola; 
}



void test_check_point_parabola(Parabola parabola, ostream& out = cout){
    Point x;
    out << "Is inside point test" << endl;
    cout << "Enter point " << endl;
    cout << "x = ";
    cin >> x.x;
    cout << "y = ";
    cin >> x.y;
    out << "Point: x = " << x.x << " y = " << x.y << endl;
    int res = parabola.check_point(x);
    
    out << "Test complited!" << endl;
    out << "Result: " << res << endl; 
} 


void test_get_value_parabola(Parabola parabola, ostream& out = cout){
    double x;
    out << "Get value test" << endl;
    cout << "Enter x" << endl;
    cout << "x = ";
    cin >> x;

    double res = parabola.get_value(x);
    out << "Point: f(x) = " << res << endl;
    out << "Test complited!" << endl;
} 



void test_get_focus_parabola(Parabola parabola, ostream& out = cout){
    out << "Get focus test" << endl;

    Point res = parabola.get_focus();
    out << "Point: x = " << res.x << " y = " << res.y << endl;
    if (parabola.check_point(res)) out << "Test complited!" << endl;
    else out << "Test failed!" << endl;
} 


void parabola_intersection(Parabola parabola, ostream& out = cout, istream& inp = cin){
    int choice;
    Point *root;
    out << "Intersection test" << endl;
    cout << "Intersection with 1 -- line, 2 -- parabola" << endl;
    inp >> choice;
    if (choice == 1){
        out << "LINE" << endl;
        double k, m;
        cout << "k = ";
        inp >> k;
        cout << "m = ";
        inp >> m;
        root = parabola.intersection(k, m);
        
    }
    else{
        Parabola parabola_2;
        parabola_2.input(inp);
        root = parabola.intersection(parabola_2);
                
    }

    for (int i = 0; i<2; i++){
        if (((*(root+i)).x!=0) || ((*(root+i)).y !=0)) 
        {
            out << "Point " << i+1 << endl;

            out << "x: " << (*(root+i)).x << endl;
            out << "y: " << (*(root+i)).y << endl;
        }
    }
    out << "Test completed!" << endl;
}



void parabola_intersection_square(Parabola parabola, ostream& out = cout, istream& inp = cin){
    int choice;
    double root;
    out << "Intersection square" << endl;
    cout << "Intersection with 1 -- line, 2 -- parabola" << endl;
    inp >> choice;
    if (choice == 1){
        out << "LINE" << endl;
        double k, m;
        cout << "k = ";
        inp >> k;
        cout << "m = ";
        inp >> m;
        root = parabola.intersection_square(k, m);
        
    }
    else{
        Parabola parabola_2;
        parabola_2.input(inp);
        root = parabola.intersection_square(parabola_2);
                
    }
    out << "Result: " << root << endl;
    out << "Test completed!" << endl;
}



Hyperbole test_create_hyperbole(ostream& out = cout, istream& inp = cin){
    Hyperbole hyperbole;
    hyperbole.input(inp);
    out << endl;
    hyperbole.print(out);
    out << "Test complited!" << endl;
    out << "Result: " << &hyperbole << endl; 
    return hyperbole; 
}


void test_check_point_hyperbole(Hyperbole hyperbole, ostream& out = cout){
    Point x;
    out << "Is inside point test" << endl;
    cout << "Enter point " << endl;
    cout << "x = ";
    cin >> x.x;
    cout << "y = ";
    cin >> x.y;
    out << "Point: x = " << x.x << " y = " << x.y << endl;
    int res = hyperbole.check_point(x);
    
    out << "Test complited!" << endl;
    out << "Result: " << res << endl; 
}




void test_get_value_hyperbole(Hyperbole hyperbole, ostream& out = cout){
    double x;
    out << "Get value test" << endl;
    cout << "Enter x" << endl;
    cout << "x = ";
    cin >> x;

    double res = hyperbole.get_value(x);
    out << "Point: f(x) = " << res << endl;
    out << "Test complited!" << endl;
} 



void test_get_foci_hyperbole(Hyperbole hyperbole, ostream& out = cout){
    out << "Get focus test" << endl;

    Point *res = hyperbole.get_foci();
    out << "Point1: x = " << (*(res)).x << " y = " << (*(res)).y << endl;
    out << "Point2: x = " << (*(res + 1)).x << " y = " << (*(res+1)).y << endl;
    if (hyperbole.check_point(*(res))) out << "Test complited!" << endl;
    else out << "Test failed!" << endl;
} 




void hyperbole_intersection(Hyperbole hyperbole, ostream& out = cout, istream& inp = cin){
    int choice;
    Point *root;
    out << "Intersection test" << endl;
    cout << "Intersection with 1 -- parabola, 2 -- hyperbole" << endl;
    inp >> choice;
    if (choice == 1){
        out << "Parabola" << endl;
        Parabola parabola;
        parabola.input(inp);
        root = hyperbole.intersection(parabola);
        
    }
    else{
        out << "Hyperbole" << endl;
        Hyperbole hyperbole_2;
        hyperbole_2.input(inp);
        root = hyperbole.intersection(hyperbole_2);
                
    }

    for (int i = 0; i<4; i++){
        // if (((*(root+i)).x!=0) || ((*(root+i)).y !=0)) 
        // {
            out << "Point " << i+1 << endl;

            out << "x: " << (*(root+i)).x << endl;
            out << "y: " << (*(root+i)).y << endl;
        // }
    }
    out << "Test completed!" << endl;
}




int main(){
    
    
    Hyperbole hyp;
    Ellipse ellipse;
    Parabola parabola;
    
    ofstream fout;
    int output, c;
    cout << "Choose way of output 1 - file | else console" << endl;
    cin >> output;
    
    if (output == 1){
        string ofilename;
        cout << "Input name of txt file" << endl;
        getline(cin, ofilename);
        fout.open(ofilename);
        if(!fout.good()) exit(1);
    }
    
    
    cout << "How to input figure 1 - console | else -- file" << endl;
    cin >> c;
    
    if (c==1){
        if (output == 1)
        { 
            hyp = test_create_hyperbole(fout);
            ellipse = test_create_ellipse(fout);
            parabola = test_create_parabola(fout);
        }
        else{
             
            hyp = test_create_hyperbole();
            ellipse = test_create_ellipse();
            parabola = test_create_parabola();
            }
    }
    else{
        string filename;
        cout << "Input name of txt file" << endl;
        getline(cin, filename);
        ifstream ifs;
        ifs.open(filename);
        if(!ifs.good()) exit(1);
        if (output == 1) hyp = test_create_hyperbole(fout, ifs);
        else hyp = test_create_hyperbole(cout, ifs);
        ifs.close();
    }
    
    if (output == 1){
        test_get_foci_hyperbole(hyp, fout);
        test_get_value_hyperbole(hyp, fout);
        test_check_point_hyperbole(hyp, fout);

        test_get_focus_parabola(parabola, fout);
        test_get_value_parabola(parabola, fout);
        test_check_point_parabola(parabola, fout);
        
        test_check_point_ellipse_console(ellipse, fout);
        test_get_value_ellipse(ellipse, fout);
        test_square_ellipse(ellipse, fout);

        
        }
    else {

        test_get_foci_hyperbole(hyp);
        test_get_value_hyperbole(hyp);
        test_check_point_hyperbole(hyp);

        test_get_focus_parabola(parabola);
        test_get_value_parabola(parabola);
        test_check_point_parabola(parabola);
        
        test_check_point_ellipse_console(ellipse);
        test_get_value_ellipse(ellipse);
        test_square_ellipse(ellipse);

        };
    
    
    cout << "How to get data for intersection test(hyperbole) 1 - console | else -- file" << endl;
    cin >> c;
    
    if (c==1){
        if (output == 1) hyperbole_intersection(hyp, fout);
        else hyperbole_intersection(hyp);
    }
    else{
        string filename;
        cout << "Input name of txt file" << endl;
        getline(cin, filename);
        ifstream ifs;
        ifs.open(filename);
        if(!ifs.good()) exit(1);
        if (output == 1) hyperbole_intersection(hyp, fout, ifs);
        else hyperbole_intersection(hyp, cout, ifs);
        ifs.close();
    }
    
    
    cout << "How to get data for intersection test(ellipse) 1 - console | else -- file" << endl;
    cin >> c;
    
    if (c==1){
        if (output == 1) test_intersection_ellipse(ellipse, fout);
        else test_intersection_ellipse(ellipse);
    }
    else{
        string filename;
        cout << "Input name of txt file" << endl;
        getline(cin, filename);
        ifstream ifs;
        ifs.open(filename);
        if(!ifs.good()) exit(1);
        if (output == 1) test_intersection_ellipse(ellipse, fout, ifs);
        else test_intersection_ellipse(ellipse, cout, ifs);
        ifs.close();
    }
    
    
    
    cout << "How to get data for intersection test(parabola) 1 - console | else -- file" << endl;
    cin >> c;
    
    if (c==1){
        if (output == 1) parabola_intersection(parabola, fout);
        else parabola_intersection(parabola);
    }
    else{
        string filename;
        cout << "Input name of txt file" << endl;
        getline(cin, filename);
        ifstream ifs;
        ifs.open(filename);
        if(!ifs.good()) exit(1);
        if (output == 1) parabola_intersection(parabola, fout, ifs);
        else parabola_intersection(parabola, cout, ifs);
        ifs.close();
    }
    
    

    cout << "How to get data for intersection square test(parabola) 1 - console | else -- file" << endl;
    cin >> c;
    
    if (c==1){
        if (output == 1) parabola_intersection_square(parabola, fout);
        else parabola_intersection_square(parabola);
    }
    else{
        string filename;
        cout << "Input name of txt file" << endl;
        getline(cin, filename);
        ifstream ifs;
        ifs.open(filename);
        if(!ifs.good()) exit(1);
        if (output == 1) parabola_intersection_square(parabola, fout, ifs);
        else parabola_intersection_square(parabola, cout, ifs);
        ifs.close();
    }
    
    return 0;
}
