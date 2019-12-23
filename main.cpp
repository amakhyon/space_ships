

//test and get min and max ranges of falling speed and x position
//implement score for players as text, handle it on collision
//implement win and lose states, terminate on win
//try to implement a programmed player that avoids falling objects and tries to catch the other player (computer plays as red)
//implement sound if  a player touches a diamond
//try to enhance collision detection using imaginary rectangles around objects and
//apply decorations for background



#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <iostream>
#import <thread>
#include<fstream>
using namespace std;
int w = 0;
int h = 0;
static void display();

double diamond_angle = 0;
double diamond_x;
double diamond_y = 3;
double diamont_scale;
double diamond_rotating_speed = 3;
double diamond_falling_speed = 0.09;

double x_position_one = -6.35;
double y_position_one = 3;

double x_position_two = 6.3;
double y_position_two = 3;

double speed_one = 0.3;
double speed_two = 0.6;

int score_one =0;
int score_two =0;

int diamonds_count = 50;



class Diamond {
    public:
    double distance_to_player1;
    double distance_to_player2;

    double diamond_angle = 0;
    double diamond_x;
    double diamond_y = 3;
    double diamond_scale =0.1;
    double diamond_rotating_speed;
    double diamond_falling_speed;

    double RandomDouble(float a, float b) {

        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }
    bool check_collision(){
        double region = 0.3;
        if ( (fabs(fabs(-this->diamond_y) - fabs(y_position_two)) <= region) && (fabs(fabs(this->diamond_x) - fabs(x_position_two)) <= region) ){  //for player two
            printf("\n==player 2\n");
            return true;

        } else if((fabs(fabs(-this->diamond_y) - fabs(y_position_one)) <= region) && (fabs(fabs(this->diamond_x) - fabs(x_position_one)) <= region)){ //for player one
            printf("\n=player 1\n");
            score_one ++;
            return true;
        }
        else{
            return false;
        }

    }

    void reset(){ this->diamond_y = 6.3;}

    bool check_bottom_of_screen(){
        if(this->diamond_y <= -6.3)
            return true;
        else
            return false;
    }
    public:
    void draw_falling_diamondd(double diamond_x, double diamond_y, double diamond_scale){
        if(check_bottom_of_screen()){  reset();}
        if(check_collision()){ reset(); }

        glPushMatrix();
        glTranslatef(-diamond_x, diamond_y, -6.0f);  // Move left and into the screen

        double diamond_dims[4][3][3] = {
        {{0,diamond_scale, 0}, {-diamond_scale, -diamond_scale, diamond_scale}, {diamond_scale, -diamond_scale, diamond_scale}}, //front
        {{0, diamond_scale, 0}, {diamond_scale, -diamond_scale, diamond_scale}, {diamond_scale, -diamond_scale, -diamond_scale}}, //right
        {{0,diamond_scale,0}, {diamond_scale, -diamond_scale, -diamond_scale}, {-diamond_scale, -diamond_scale, -diamond_scale}}, //back
        {{0, diamond_scale,0}, {-diamond_scale,-diamond_scale,-diamond_scale}, {-diamond_scale,-diamond_scale,diamond_scale}} //left
        };

        glRotatef(diamond_angle, 0, 1, 0.0f);
        glBegin(GL_TRIANGLES);
        double diamond_color = 1;
        for(int i=0; i < 4; i++){ //for each face
            for(int j=0; j < 3; j++){ //for each point in each face
                glColor3f(diamond_color,diamond_color,diamond_color);
                glVertex3f( diamond_dims[i][j][0], diamond_dims[i][j][1], diamond_dims[i][j][2]);
            }
            diamond_color -= 0.1;
        }
        glEnd();
        glPopMatrix();

            //================= down side======================
        glPushMatrix();
        glTranslatef(-diamond_x, diamond_y, -6);  // Move left and into the screen
        //glTranslatef(0,-diamond_scale*2 ,0);


        glRotatef(diamond_angle, 0, 1, 0);
        glBegin(GL_TRIANGLES);
        diamond_color = 1;
        for(int i=0; i < 4; i++){ //for each face
            for(int j=0; j < 3; j++){ //for each point in each face
                glColor3f(diamond_color, diamond_color,diamond_color);
                glVertex3f( -diamond_dims[i][j][0], -diamond_dims[i][j][1], -diamond_dims[i][j][2]);
            }
            diamond_color -= 0.1;
        }


        glEnd();
        glPopMatrix();


    } //end of draw falling diamond




    Diamond(){

            diamond_y = 6.3;
            diamond_x =   RandomDouble(-6.3,6.3);              //between -6.3 and 6.
            diamond_falling_speed = RandomDouble(0.09, 0.01);
            diamond_scale = RandomDouble(0.1, 0.4);
            diamond_rotating_speed = RandomDouble(2,7);
            draw_falling_diamondd(this->diamond_x, this->diamond_y-diamond_falling_speed, this->diamond_scale);
        }

    void reduce_y_of_diamond(){
        this -> diamond_y -= this -> diamond_falling_speed;
    }
    void increase_angle_of_diamond(){
        this-> diamond_angle += diamond_rotating_speed;
    }
    double get_y(){ return this->diamond_y;}
    double get_x(){ return this->diamond_x;}
    double get_scale(){ return this->diamond_scale;}

};

Diamond diamonds[50];
static void resize(int width, int height)
{
    //const float ar = (float) width / (float) height;
    GLfloat sideRange = 200;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,2,1,200);
    glMatrixMode(GL_MODELVIEW);
    w = width;
    h = height;
    glOrtho(-sideRange, sideRange, -sideRange, sideRange, sideRange, -sideRange);
    glLoadIdentity() ;
}





void spaceShip_one(double size){ //white
    glColor3f(1,1,1);
    glPushMatrix();
        glTranslated(x_position_one,-y_position_one,-6);
        glRotated(90,1,0,0);
        glutSolidSphere(size,50,50);
    glPopMatrix();

    //glColor3f(0.3333,0.3333,0.3333);
    glColor3f(1,1,1);
    glPushMatrix();
        glTranslated(x_position_one,-y_position_one ,-6);
        glRotated(82.5,1,0,0);
        glutSolidTorus(size / 3.3333333, size,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslated(x_position_one - 0.15,-y_position_one - 0.2,-6); //left leg
        glRotated(90,1,0,0);
        glRotated(-20,0,1,0);
        glutSolidCone(size /5 , size / 0.8333333,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslated(x_position_one + 0.15,-y_position_one - 0.2,-6); //right leg
        glRotated(90,1,0,0);
        glRotated(20,0,1,0);
        glutSolidCone(size /5 , size / 0.8333333,50,50);
    glPopMatrix();


}


void spaceShip_two(double size){ //red
    glColor3f(1,0,0);
    glPushMatrix();
        glTranslated(x_position_two,-y_position_two,-6);
        glRotated(90,1,0,0);
        glutSolidSphere(size,50,50);
    glPopMatrix();

    //glColor3f(0.3333,0.3333,0.3333);
    glColor3f(1,0,0);
    glPushMatrix();
        glTranslated(x_position_two,-y_position_two ,-6);
        glRotated(82.5,1,0,0);
        glutSolidTorus(size / 3.3333333, size,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslated(x_position_two - 0.15,-y_position_two- 0.2,-6); //left leg
        glRotated(90,1,0,0);
        glRotated(-20,0,1,0);
        glutSolidCone(size /5 , size / 0.8333333,50,50);
    glPopMatrix();

    glPushMatrix();
        glTranslated(x_position_two + 0.15,-y_position_two - 0.2,-6); //right leg
        glRotated(90,1,0,0);
        glRotated(20,0,1,0);
        glutSolidCone(size /5 , size / 0.8333333,50,50);
    glPopMatrix();

}




void draw_falling_diamond(double diamond_x, double diamond_y, double diamond_scale){
    glPushMatrix();
    glTranslatef(-diamond_x, diamond_y, -6.0f);  // Move left and into the screen

    double diamond_dims[4][3][3] = {
    {{0,diamond_scale, 0}, {-diamond_scale, -diamond_scale, diamond_scale}, {diamond_scale, -diamond_scale, diamond_scale}}, //front
    {{0, diamond_scale, 0}, {diamond_scale, -diamond_scale, diamond_scale}, {diamond_scale, -diamond_scale, -diamond_scale}}, //right
    {{0,diamond_scale,0}, {diamond_scale, -diamond_scale, -diamond_scale}, {-diamond_scale, -diamond_scale, -diamond_scale}}, //back
    {{0, diamond_scale,0}, {-diamond_scale,-diamond_scale,-diamond_scale}, {-diamond_scale,-diamond_scale,diamond_scale}} //left
    };

    glRotatef(diamond_angle, 0, 1, 0.0f);
    glBegin(GL_TRIANGLES);
    double diamond_color = 1;
    for(int i=0; i < 4; i++){ //for each face
        for(int j=0; j < 3; j++){ //for each point in each face
            glColor3f(diamond_color,diamond_color,diamond_color);
            glVertex3f( diamond_dims[i][j][0], diamond_dims[i][j][1], diamond_dims[i][j][2]);
        }
        diamond_color -= 0.1;
    }


    glEnd();
   glPopMatrix();

    //================= down side======================
   glPushMatrix();
    glTranslatef(-diamond_x, diamond_y, -6);  // Move left and into the screen
    glTranslatef(0,-diamond_scale *2,0);


    glRotatef(diamond_angle, 0, 1, 0);
    glBegin(GL_TRIANGLES);
    diamond_color = 1;
    for(int i=0; i < 4; i++){ //for each face
        for(int j=0; j < 3; j++){ //for each point in each face
            glColor3f(diamond_color, diamond_color,diamond_color);
            glVertex3f( -diamond_dims[i][j][0], -diamond_dims[i][j][1], -diamond_dims[i][j][2]);
        }
        diamond_color -= 0.1;
    }


    glEnd();
   glPopMatrix();
}

bool collision_detection_between_players(){
    double region = 0.6;
    if ( (fabs(y_position_one - y_position_two) <= region) && (fabs(x_position_one - x_position_two) <= region) ){ // top - bottom collision
        printf("===are they touching ?===\n");
        return true;

    } else {
        return false;
    }

    //printf(" y difference is %f\n", fabs(y_position_one - y_position_two));
    //printf(" x difference is %f\n\n", fabs(x_position_one - x_position_two));

}
void reset_player_positions(){
    x_position_one = -6.35;
    y_position_one = 3;

    x_position_two = 6.3;
    y_position_two = 3;
}

void handle_collision_between_players(){
    reset_player_positions();
    display();

}

void keyboard(unsigned char key, int x, int y) {
    printf(" %c  key is pressd \n", key);
    if(collision_detection_between_players() == true)
        handle_collision_between_players();
    switch(key) {
		case 'W': case 'w':
			y_position_one -= speed_one;
			break;
        case 'S' :case 's':
            y_position_one += speed_one;
            break;
        case 'a':
            x_position_one -= speed_one;
            break;
        case 'd':
            x_position_one += speed_one;
            break;

        case '8':
            y_position_two -= speed_two;
            break;
        case '5':
            y_position_two += speed_two;
            break;
        case '4':
            x_position_two -= speed_two;
            break;
        case '6':
            x_position_two += speed_two;
            break;

        case 'q':
            exit(0);


	}
        printf("x position one is %f\n", x_position_one);
        printf("y position one is %f\n", y_position_one);
        printf("x position two is %f\n", x_position_two);
        printf("y position two is %f\n", y_position_two);



}

void playMusic(){
      PlaySound("C:\\Users\\Assem\\Desktop\\dino\\aliens.wav",NULL, SND_FILENAME);
}

void falling_diamond_timer(int){

    for(int i=0; i < diamonds_count; i++){
        diamonds[i].reduce_y_of_diamond();
    }
    diamond_y -= diamond_falling_speed;
    display();
    glutTimerFunc(1000/60,falling_diamond_timer,0);
}

void rotating_diamond_timer(int){
    for(int i=0; i < diamonds_count; i++){
        diamonds[i].increase_angle_of_diamond();
    }
    diamond_angle += diamond_rotating_speed;
    display();
    glutTimerFunc(1000/60,rotating_diamond_timer,0);

}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    spaceShip_one(0.25);
    spaceShip_two(0.25);
    draw_falling_diamond(1.5, diamond_y,0.1);
    draw_falling_diamond(-1.5, diamond_y,0.4);
    for(int i=0; i < diamonds_count; i++){
        diamonds[i].draw_falling_diamondd(diamonds[i].get_x(), diamonds[i].get_y(), diamonds[i].get_scale());
    }
    glutSwapBuffers();

}

int main(int argc, char *argv[])
{


    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("my game");

    std::thread musicThread (playMusic);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, falling_diamond_timer, 0);
    glutTimerFunc(0,rotating_diamond_timer,0);
    //glutKeyboardFunc(keyboard_thread);




    glClearColor(0,0,0,0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
