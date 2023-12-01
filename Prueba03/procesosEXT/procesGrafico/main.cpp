#include "funciones/funciones.h"
#include "funciones/funciones.cpp"


struct Point {
    float x, y;
};

string title;
vector<Point> points;

void loadData(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        exit(EXIT_FAILURE);
    }
    string line;
    while (getline(file, line)) {
        /*if (line.find("titulo:") != string::npos) {
            title = line.substr(line.find(":") + 1);
        }*/
        if (line.find("x:") != string::npos && line.find("y:") != string::npos) {
            Point p;
            sscanf(line.c_str(), "x:%f,y:%f", &p.x, &p.y);
            points.push_back(p);
        }
    }
    file.close();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_LINES);
    glVertex2f(-100.0, 0.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(0.0, -100.0);
    glVertex2f(0.0, 100.0);
    glEnd();


    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(90.0, -5.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X'); // Poner la X del eje


    glRasterPos2f(-5.0, 90.0);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y'); // poner la Y del eje

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100.0, 100.0, -100.0, 100.0); // Establece el rango de -100 a 100 en ambos ejes
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "\n### Error al llamar la función ###\nDebe ejecutarse como ./app <path_archivo>\n\n";
        exit(EXIT_FAILURE);
    }
    

    cout << endl;
    string path = argv[1];

    // Verificar la existencia y extension del archivo
    if (!fs::exists(path)) { cerr << "El archivo no existe.\n\n"; exit(EXIT_FAILURE); }
    string ext = path.substr(path.length() - 4);
    if (ext != ".gra"){ cerr << "Error!!! Debe ingresar un archivo '.gra'\n\n"; exit(EXIT_FAILURE); }

    auto resultado = validarPrimeraLinea(path); 
    if (!resultado.first) {
        cout << "Formato del archivo no valido! (titulo)" << endl;
        exit(EXIT_FAILURE);
    }

    //cout << resultado.second << endl;
    string titulo = resultado.second; // titulo del grafico


    // Validando desde segunda linea con el formato x:int,y:int
    bool flag = validarArchivo(path);
    if (!flag) {
        cout << "Formato del archivo no valido (lineas)!" << endl;
        exit(EXIT_FAILURE);
    }
    


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    const char* titulo_cstr = titulo.c_str(); // convirtiendo el string titulo a char
    glutCreateWindow(titulo_cstr);

    init();
    loadData(path);

    cout << "Para continuar cerrar la grafica" << endl;
    glutDisplayFunc(display);
    glutMainLoop();


    return EXIT_SUCCESS;
}


