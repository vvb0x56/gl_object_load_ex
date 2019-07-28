#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <cstdio>
#include <glm/glm.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

class ObjectModel {
private:
    std::vector< glm::vec3 > vertexes;
    std::vector< glm::vec2 > textures;
    std::vector< glm::vec3 > normals;
    std::vector< int > v_indexes;
    std::vector< int > vn_indexes;
    std::vector< int > vt_indexes;
    glm::vec3 color; 
public:
    ObjectModel( const char * filename ) {
        std::string line;
        std::string word;
        std::ifstream file(filename); 
        if ( file.is_open() ) {
            while (std::getline(file, line)) {
                std::stringstream stream(line);
                stream >> word; 
                if (word.compare("v") == 0) {
                    glm::vec3 vertex;
                    stream >> vertex.x >> vertex.y >> vertex.z;
                    vertexes.push_back(vertex);
                }
                else if (word.compare("vt") == 0) {
                    glm::vec2 texture; 
                    stream >> texture.x >> texture.y;
                    textures.push_back(texture);
                }
                else if (word.compare("vn") == 0) {
                    glm::vec3 normal; 
                    stream >> normal.x >> normal.y >> normal.z;
                    normals.push_back(normal);
                }
                else if (word.compare("f") == 0) {
                    std::string tmp_str;
                    for (int i = 0; i < 3; i++) { // 7/7/3 6/8/3 8/5/3
                        int v, vt, vn;
                        stream >> tmp_str;
                        //sscanf(tmp_str.c_str(), "%d/%d/%d", &v, &vt, &vn);
                        sscanf(tmp_str.c_str(), "%d//%d", &v, &vn);
                        v_indexes.push_back(v);
                        //vt_indexes.push_back(vt);
                        vn_indexes.push_back(vn);    
                    }
                }
            }
        }
        color.x = 1.0;
        color.y = 0.5;
        color.z = 0.1;
    }

    void gl_draw() {
        glBegin(GL_TRIANGLES);

        //glColor3f(color.x, color.y, color.z);
        glColor3f(1, 0, 0);

        //glNormal3f(0.0, 1.0, 0.0); glVertex3f(-1.0, 1.0,-1.0);
        //glNormal3f(0.0, 1.0, 0.0); glVertex3f( 1.0, 1.0, 1.0);
        //glNormal3f(0.0, 1.0, 0.0); glVertex3f( 1.0, 1.0,-1.0);

        //glNormal3f(0.0, 0.0, 1.0); glVertex3f( 1.0, 1.0, 1.0);
        //glNormal3f(0.0, 0.0, 1.0); glVertex3f(-1.0,-1.0, 1.0);
        //glNormal3f(0.0, 0.0, 1.0); glVertex3f( 1.0,-1.0, 1.0);

        //glNormal3f(-1.0, 0.0, 0.0); glVertex3f(-1.0, 1.0, 1.0);
        //glNormal3f(-1.0, 0.0, 0.0); glVertex3f(-1.0,-1.0,-1.0);
        //glNormal3f(-1.0, 0.0, 0.0); glVertex3f(-1.0,-1.0, 1.0);

        for (int i = 0; i < v_indexes.size(); i++) {
            glm::vec3 normal = normals[vn_indexes[i] - 1];
            glNormal3f(normal.x, normal.y, normal.z);
            
            glm::vec3 vertex = vertexes[v_indexes[i] - 1];
            glVertex3f(vertex.x, vertex.y, vertex.z);

        }
        glEnd();
    }

    void print_debug() {
        for (int i = 0; i < vertexes.size(); i++) {
            std::cout << vertexes[i].x << "," << vertexes[i].y << ",";
            std::cout << vertexes[i].z << "; ";
        }
        std::cout << std::endl;
        for (int i = 0; i < v_indexes.size(); i++) {
            std::cout << v_indexes[i] << ",";
        }
        std::cout << std::endl;

        for (int i = 0; i < normals.size(); i++) {
            std::cout << normals[i].x << "," << normals[i].y << ",";
            std::cout << normals[i].z << "; ";
        }
        std::cout << std::endl;
        for (int i = 0; i < vn_indexes.size(); i++) {
            std::cout << vn_indexes[i] << ",";
        }
        std::cout << std::endl;
    }
    
    ~ObjectModel() { std::cout << "Object Model destroyed\n"; }
};

ObjectModel * model = nullptr;

static int rotate_y = 0;
static float radius = 5;

static float eyeX = 5;
static float eyeY = 0;
static float eyeZ = 0;

static float cameraY = 0;




static void update_cam_pos() {
    // Y
    eyeX = cos(rotate_y * M_PI / 180.0f) * radius;
    eyeZ = sin(rotate_y * M_PI / 180.0f) * radius;
}

void init(void) {
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {30.0};
    GLfloat light0_position[] = {0.0, 1.0, 5.0, 0.0};
    //GLfloat light1_position[] = {0.0, 5.0, 5.0, 0.0};
    //GLfloat light2_position[] = {0.0, 10.0, 5.0, 0.0};
    //GLfloat light3_position[] = {0.0, 15.0, 5.0, 0.0};
    //GLfloat light4_position[] = {0.0, 20.0, 5.0, 0.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    //glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    //glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    //glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    //glLightfv(GL_LIGHT4, GL_POSITION, light4_position);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHT2);
    //glEnable(GL_LIGHT3);
    //glEnable(GL_LIGHT4);
    glEnable(GL_DEPTH_TEST);

    //model = new ObjectModel("untitled.obj");
    model = new ObjectModel("human.obj");

    //model->print_debug();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    
    glPushMatrix();
    
    gluLookAt(eyeX, eyeY, eyeZ, 0.0, cameraY, 0.0, 0.0, 1.0, 0.0); 

    glBegin(GL_LINES);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(-3.0, 0.0, 0.0);
        glVertex3f( 3.0, 0.0, 0.0);

        glColor3f(1.0, 0.0, 0.0);
        glVertex3f( 0.0, -3.0, 0.0);
        glVertex3f( 0.0,  3.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f( 0.0,  0.0, -3.0);
        glVertex3f( 0.0,  0.0,  3.0);
    glEnd();

    model->gl_draw();


    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void keyboard(unsigned char key, int w, int h) {
    switch(key) {
        case 'y': 
            rotate_y = (rotate_y + 10) % 360;
            break;
        case 'Y': 
            rotate_y = (rotate_y - 10) % 360;
            break;
        case 'u':
            eyeY += 1.0f;
            break;
        case 'U':
            eyeY -= 1.0f;
            break;
        case 'c':
            cameraY += 0.2f;
            break;
        case 'C':
            cameraY -= 0.2f;
            break;
        default:
            break;
    }   
    update_cam_pos();
    glutPostRedisplay();
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    delete model;
    return 0;

}
