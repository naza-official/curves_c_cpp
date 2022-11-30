
extern "C"{
    #include "c_part/ccurves.h"
}

#include "c_part/ccurves.c"
#include "cpp_part/curves.cpp"




int main(){
    
    
    
    ofstream fout;
    int output, c;
    cout << "Choose way of output 1 - file | else console" << endl;
    cin >> output;
    
    if (output == 1){
        string ofilename;
        cout << "Input name of txt file" << endl;
        cin.ignore();
        getline(cin, ofilename);
        fout.open(ofilename);
        if(!fout.good()) exit(1);
    }
    
    
    
    CEllipse e_c;
    Ellipse e_cpp;

    cellipse_input(stdin, &e_c);
    
    Point verts[4];
    for (int i = 0; i<4; i++){
        verts[i].x = e_c.verteces[i].x;
        verts[i].y = e_c.verteces[i].y;
    } 
    
    e_cpp = Ellipse(verts);
    
    if (output == 1){
        double c_square = cellipse_get_square(e_c);
        double cpp_square = e_cpp.get_square();
        if (c_square == cpp_square){
            fout << "Square test complited!" << endl;
        }
        else {
            fout << "Square test failed!" << endl;
        }

        fout << "Square C/Cpp " << c_square << " " << cpp_square << endl;

        Point cpp_center = e_cpp.get_center();
        CPoint c_center = cellipse_get_center(e_c);
        
        if (c_center.x == cpp_center.x){
            fout << "Center test complited!" << endl;
        }
        else {
            fout << "Center test failed!" << endl;
        }

        fout << c_center.x << " " << c_center.y << " " << cpp_center.x << " " << cpp_center.y << endl;        

    }
    else {
        
        double c_square = cellipse_get_square(e_c);
        double cpp_square = e_cpp.get_square();
        if (c_square == cpp_square){
            cout << "Square test complited!" << endl;
        }
        else {
            cout << "Square test failed!" << endl;
        }

        cout << "Square C/Cpp " << c_square << " " << cpp_square << endl;

        Point cpp_center = e_cpp.get_center();
        CPoint c_center = cellipse_get_center(e_c);
        
        if (c_center.x == cpp_center.x){
            cout << "Center test complited!" << endl;
        }
        else {
            cout << "Center test failed!" << endl;
        }

        cout << c_center.x << " " << c_center.y << " | " << cpp_center.x << " " << cpp_center.y << endl;        
    }

    
    
    
   
    return 0;
}
