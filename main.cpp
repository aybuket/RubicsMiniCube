//
//  main.cpp
//  graphics_rubics_cube
//
//  Created by Aybüke Buket Akgül on 23.04.2021.
//  Copyright © 2021 Aybüke Buket Akgül. All rights reserved.
//

#include "Angel.h"

typedef vec4  color4;
typedef vec4  point4;

const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

// Create a vertex array object
GLuint vao[8];

// Create and initialize a buffer object
GLuint buffer;

point4 points[8][NumVertices];
color4 colors[8][NumVertices];
float offset = 0.04;

int upFaceCubes[4]        = {4, 5, 7, 6};
int downFaceCubes[4]      = {0, 1, 3, 2};

int leftFaceCubes[4]      = {4, 5, 1, 0};
int leftFaceBackCubes[4]  = {6, 7, 3, 2};

int rightFaceCubes[4]     = {5, 7, 3, 1};
int rightFaceBackCubes[4] = {4, 6, 2, 0};

bool turnRightFace     = false;
bool turnLeftFace      = false;
bool turnRightBackFace = false;
bool turnLeftBackFace  = false;
bool turnUpFace        = false;
bool turnDownFace      = false;

bool blockOtherTurns   = false;

int turnRightFaceCount     = 0;
int turnLeftFaceCount      = 0;
int turnRightBackFaceCount = 0;
int turnLeftBackFaceCount  = 0;
int turnUpFaceCount        = 0;
int turnDownFaceCount      = 0;

enum { Left = -1, Right = 1 };
int direction = Right;
bool cubeChangedDirection = false;


// Vertices of a unit cube centered at origin, sides aligned with axes
point4 vertices1[8] = {
    point4(      -1,      -1, -offset, 1.0 ),
    point4(      -1, -offset, -offset, 1.0 ),
    point4( -offset, -offset, -offset, 1.0 ),
    point4( -offset,      -1, -offset, 1.0 ),
    point4(      -1,      -1,      -1, 1.0 ),
    point4(      -1, -offset,      -1, 1.0 ),
    point4( -offset, -offset,      -1, 1.0 ),
    point4( -offset,      -1,      -1, 1.0 ),
};

point4 vertices2[8] = {
    point4( offset,      -1, -offset, 1.0 ),
    point4( offset, -offset, -offset, 1.0 ),
    point4(      1, -offset, -offset, 1.0 ),
    point4(      1,      -1, -offset, 1.0 ),
    point4( offset,      -1,      -1, 1.0 ),
    point4( offset, -offset,      -1, 1.0 ),
    point4(      1, -offset,      -1, 1.0 ),
    point4(      1,      -1,      -1, 1.0 )
};

point4 vertices3[8] = {
    point4(      -1, offset, -offset, 1.0 ),
    point4(      -1,      1, -offset, 1.0 ),
    point4( -offset,      1, -offset, 1.0 ),
    point4( -offset, offset, -offset, 1.0 ),
    point4(      -1, offset,      -1, 1.0 ),
    point4(      -1,      1,      -1, 1.0 ),
    point4( -offset,      1,      -1, 1.0 ),
    point4( -offset, offset,      -1, 1.0 )
};

point4 vertices4[8] = {
    point4( offset, offset, -offset, 1.0 ),
    point4( offset,      1, -offset, 1.0 ),
    point4(      1,      1, -offset, 1.0 ),
    point4(      1, offset, -offset, 1.0 ),
    point4( offset, offset,      -1, 1.0 ),
    point4( offset,      1,      -1, 1.0 ),
    point4(      1,      1,      -1, 1.0 ),
    point4(      1, offset,      -1, 1.0 )
};

point4 vertices5[8] = {
    point4(      -1,      -1,      1, 1.0 ),
    point4(      -1, -offset,      1, 1.0 ),
    point4( -offset, -offset,      1, 1.0 ),
    point4( -offset,      -1,      1, 1.0 ),
    point4(      -1,      -1, offset, 1.0 ),
    point4(      -1, -offset, offset, 1.0 ),
    point4( -offset, -offset, offset, 1.0 ),
    point4( -offset,      -1, offset, 1.0 )
};

point4 vertices6[8] = {
    point4( offset,      -1,      1, 1.0 ),
    point4( offset, -offset,      1, 1.0 ),
    point4(      1, -offset,      1, 1.0 ),
    point4(      1,      -1,      1, 1.0 ),
    point4( offset,      -1, offset, 1.0 ),
    point4( offset, -offset, offset, 1.0 ),
    point4(      1, -offset, offset, 1.0 ),
    point4(      1,      -1, offset, 1.0 )
};

point4 vertices7[8] = {
    point4(      -1, offset,      1, 1.0 ),
    point4(      -1,      1,      1, 1.0 ),
    point4( -offset,      1,      1, 1.0 ),
    point4( -offset, offset,      1, 1.0 ),
    point4(      -1, offset, offset, 1.0 ),
    point4(      -1,      1, offset, 1.0 ),
    point4( -offset,      1, offset, 1.0 ),
    point4( -offset, offset, offset, 1.0 )
};

point4 vertices8[8] = {
    point4( offset, offset,      1, 1.0 ),
    point4( offset,      1,      1, 1.0 ),
    point4(      1,      1,      1, 1.0 ),
    point4(      1, offset,      1, 1.0 ),
    point4( offset, offset, offset, 1.0 ),
    point4( offset,      1, offset, 1.0 ),
    point4(      1,      1, offset, 1.0 ),
    point4(      1, offset, offset, 1.0 )
};

// RGBA olors
color4 vertex_colors[7] = {
    color4(   0.0/256,   0.0/256,   0.0/256, 1.0 ),  // black
    color4( 256.0/256,   0.0/256,   0.0/256, 1.0 ),  // red
    color4( 256.0/256, 256.0/256,   0.0/256, 1.0 ),  // yellow
    color4(  50.0/256, 205.0/256,  50.0/256, 1.0 ),  // green
    color4(   0.0/256,   0.0/256, 256.0/256, 1.0 ),  // blue
    color4( 255.0/256, 140.0/256,   0.0/256, 1.0 ),  // orange
    color4( 256.0/256, 256.0/256, 256.0/256, 1.0 ),  // white
};

// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int  Axis = Xaxis;
GLfloat  Theta[NumAxes] = { 0.0, 0.0, 0.0 };

// Model-view and projection matrices uniform location
GLuint  ModelView, Projection;

mat4  model_view[8];

//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices

int Index = 0;

void
quad( int colorInd, int a, int b, int c, int d )
{
    // Initialize colors
    int colorChoice[8];
    for(int i=0; i<8; i++){
        bool cond1 = colorInd==1 && i<4;
        bool cond2 = colorInd==2 && i%2==0;
        bool cond3 = colorInd==3 && (i==2 || i==3 || i==6 || i==7);
        bool cond4 = colorInd==4 && (i==0 || i==1 || i==4 || i==5);
        bool cond5 = colorInd==5 && i>3;
        bool cond6 = colorInd==6 && i%2==1;
        if (cond1 || cond2 || cond3 || cond4 ||cond5 || cond6)
        {
            colorChoice[i] = 0;
        }
        else{
            colorChoice[i] = colorInd;
        }
    }
    for (int i=0; i<8; i++){
        colors[i][Index] = vertex_colors[colorChoice[i]];
    }
    
    points[0][Index] = vertices1[a];
    points[1][Index] = vertices2[a];
    points[2][Index] = vertices3[a];
    points[3][Index] = vertices4[a];
    points[4][Index] = vertices5[a];
    points[5][Index] = vertices6[a];
    points[6][Index] = vertices7[a];
    points[7][Index] = vertices8[a]; Index++;

    for (int i=0; i<8; i++){
        colors[i][Index] = vertex_colors[colorChoice[i]];
    }
    points[0][Index] = vertices1[b];
    points[1][Index] = vertices2[b];
    points[2][Index] = vertices3[b];
    points[3][Index] = vertices4[b];
    points[4][Index] = vertices5[b];
    points[5][Index] = vertices6[b];
    points[6][Index] = vertices7[b];
    points[7][Index] = vertices8[b]; Index++;
    
    for (int i=0; i<8; i++){
        colors[i][Index] = vertex_colors[colorChoice[i]];
    }
    points[0][Index] = vertices1[c];
    points[1][Index] = vertices2[c];
    points[2][Index] = vertices3[c];
    points[3][Index] = vertices4[c];
    points[4][Index] = vertices5[c];
    points[5][Index] = vertices6[c];
    points[6][Index] = vertices7[c];
    points[7][Index] = vertices8[c]; Index++;
    
    for (int i=0; i<8; i++){
        colors[i][Index] = vertex_colors[colorChoice[i]];
    }
    points[0][Index] = vertices1[a];
    points[1][Index] = vertices2[a];
    points[2][Index] = vertices3[a];
    points[3][Index] = vertices4[a];
    points[4][Index] = vertices5[a];
    points[5][Index] = vertices6[a];
    points[6][Index] = vertices7[a];
    points[7][Index] = vertices8[a]; Index++;

    for (int i=0; i<8; i++){
        colors[i][Index] = vertex_colors[colorChoice[i]];
    }
    points[0][Index] = vertices1[c];
    points[1][Index] = vertices2[c];
    points[2][Index] = vertices3[c];
    points[3][Index] = vertices4[c];
    points[4][Index] = vertices5[c];
    points[5][Index] = vertices6[c];
    points[6][Index] = vertices7[c];
    points[7][Index] = vertices8[c]; Index++;
    
    for (int i=0; i<8; i++){
        colors[i][Index] = vertex_colors[colorChoice[i]];
    }
    points[0][Index] = vertices1[d];
    points[1][Index] = vertices2[d];
    points[2][Index] = vertices3[d];
    points[3][Index] = vertices4[d];
    points[4][Index] = vertices5[d];
    points[5][Index] = vertices6[d];
    points[6][Index] = vertices7[d];
    points[7][Index] = vertices8[d]; Index++;
}

//----------------------------------------------------------------------------

// generate 12 triangles: 36 vertices and 36 colors
void
colorcube()
{
    quad( 1, 0, 1, 2, 3 );
    quad( 2, 2, 3, 7, 6 );
    quad( 3, 3, 0, 4, 7 );
    quad( 4, 6, 5, 1, 2 );
    quad( 5, 4, 5, 6, 7 );
    quad( 6, 5, 4, 0, 1 );
}

//----------------------------------------------------------------------------

// OpenGL initialization
void
init()
{
    colorcube();
    
    // Load shaders and use the resulting shader program
    GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );
    
    glGenVertexArrays( 8, vao );
    
    for(int i=0; i<8; i++){
        
        glBindVertexArray( vao[i] );
        glGenBuffers( 1, &buffer );
        glBindBuffer( GL_ARRAY_BUFFER, buffer );
        glBufferData( GL_ARRAY_BUFFER, sizeof(points[i]) + sizeof(colors[i]), NULL, GL_STATIC_DRAW );
        glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(points[i]), points[i]);
        glBufferSubData( GL_ARRAY_BUFFER, sizeof(points[i]), sizeof(colors[i]), colors[i] );
    
        // set up vertex arrays
        GLuint vPosition = glGetAttribLocation( program, "vPosition" );
        glEnableVertexAttribArray( vPosition );
        glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    
        GLuint vColor = glGetAttribLocation( program, "vColor" );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(colors[i])) );
    }
    
    // Retrieve transformation uniform variable locations
    ModelView = glGetUniformLocation( program, "ModelView" );
    Projection = glGetUniformLocation( program, "Projection" );
    
    // Set current program object
    glUseProgram( program );
    
    for (int i = 0; i<8 ; i++){
        model_view[i] = Scale(0.5, 0.5, 0.5) * RotateX(-50) * RotateZ(-30) * identity();
    }
        
    // Set projection matrix
    mat4  projection;
    projection = Ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Ortho(): user-defined function in mat.h
    //projection = Perspective( 45.0, 1.0, 0.5, 3.0 );
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );

    // Enable hiddden surface removal
    glEnable( GL_DEPTH_TEST );
    
    // Set state variable "clear color" to clear buffer with.
    glClearColor( 220.0/256, 220.0/256, 220.0/256, 1.0 );
   }

//----------------------------------------------------------------------------
void upTurn();
void rightTurn();
void rightBackTurn();
void downTurn();
void leftTurn();
void leftBackTurn();

void
display( void )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //  Generate tha model-view matrix
    
    // Scale(), Translate(), RotateX(), RotateY(), RotateZ(): user-defined functions in mat.h
    //use this to have rotation around fixed axes
    
    if (turnUpFace)
    {
        upTurn();
    }
    if (turnRightFace)
    {
        rightTurn();
    }
    if (turnDownFace)
    {
        downTurn();
    }
    if (turnLeftFace)
    {
        leftTurn();
    }
    if(turnLeftBackFace)
    {
        leftBackTurn();
    }
    if(turnRightBackFace)
    {
        rightBackTurn();
    }
    
    for(int i =0; i<8; i++)
    {
        glBindVertexArray( vao[i] );
        glUniformMatrix4fv( ModelView, 1, GL_TRUE, model_view[i] );
        glDrawArrays( GL_TRIANGLES, 0, NumVertices );
    }
    glutSwapBuffers();

}

//---------------------------------------------------------------------
//
// reshape
//

void reshape( int w, int h )
{
    glViewport( 0, 0, w, h );
    
    mat4  projection;
    if (w <= h)
        projection = Ortho(-1.0, 1.0, -1.0 * (GLfloat) h / (GLfloat) w,
                           1.0 * (GLfloat) h / (GLfloat) w, -1.0, 1.0);
    else  projection = Ortho(-1.0* (GLfloat) w / (GLfloat) h, 1.0 *
                             (GLfloat) w / (GLfloat) h, -1.0, 1.0, -1.0, 1.0);
    glUniformMatrix4fv( Projection, 1, GL_TRUE, projection );
    
}


//----------------------------------------------------------------------------

void
idle( void )
{
    
    // use this to have rotation around fixed axes
    Theta[0] = Theta[1] = Theta[2] = 3.0 * direction;
    
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void shiftUpTurn();
void shiftRightTurn();
void shiftRightBackTurn();
void shiftDownTurn();
void shiftLeftTurn();
void shiftLeftBackTurn();
void print_helper();

void
keyboard( unsigned char key,int x, int y )
{
    if(key == 'Q' | key == 'q')
    {
        exit(0);
    }
    else if(key == 'H' | key == 'h')
    {
        print_helper();
    }
    else if((key == 'C' | key == 'c') && !blockOtherTurns)
    {
        direction *= -1;
    }
    else if((key == 'W' | key == 'w') && !blockOtherTurns)
    {
        // if direction is changed due to whole cube rotation, return to user choice
        if(cubeChangedDirection)
        {
            direction *= -1;
            cubeChangedDirection = false;
        }
        
        turnUpFace = true;
        blockOtherTurns = true;
    }
    else if((key == 'A' | key == 'a') && !blockOtherTurns)
    {
        // if direction is changed due to whole cube rotation, return to user choice
        if(cubeChangedDirection)
        {
            direction *= -1;
            cubeChangedDirection = false;
        }
        
        turnLeftFace = true;
        blockOtherTurns = true;
    }
    else if((key == 'S' | key == 's') && !blockOtherTurns)
    {
        // if direction is changed due to whole cube rotation, return to user choice
        if(cubeChangedDirection)
        {
            direction *= -1;
            cubeChangedDirection = false;
        }
        
        turnDownFace = true;
        blockOtherTurns = true;
    }
    else if((key == 'D' | key == 'd') && !blockOtherTurns)
    {
        // if direction is changed due to whole cube rotation, return to user choice
        if(cubeChangedDirection)
        {
            direction *= -1;
            cubeChangedDirection = false;
        }
        
        turnRightFace = true;
        blockOtherTurns = true;
    }
}

void arrowKeys(int key, int x, int y)
{
    if(key == GLUT_KEY_UP && !blockOtherTurns)
    {
        turnRightFace = true;
        turnRightBackFace = true;
        
        if (direction == Left) {
            cubeChangedDirection = true;
        }
        direction = Right;
        
        blockOtherTurns = true;
    }
    else if(key == GLUT_KEY_DOWN && !blockOtherTurns)
    {
        turnRightFace = true;
        turnRightBackFace = true;
        
        if (direction == Right) {
            cubeChangedDirection = true;
        }
        direction = Left;
        
        blockOtherTurns = true;
    }
    else if(key == GLUT_KEY_LEFT && !blockOtherTurns)
    {
        // check if direction is changed due to whole cube rotation.
        if (direction == Right) {
            cubeChangedDirection = true;
        }
        
        direction = Left;
        turnUpFace = true;
        turnDownFace = true;
        blockOtherTurns = true;
    }
    else if(key == GLUT_KEY_RIGHT && !blockOtherTurns)
    {
        // check if direction is changed due to whole cube rotation.
        if (direction == Left) {
            cubeChangedDirection = true;
        }
        
        direction = Right;
        turnUpFace = true;
        turnDownFace = true;
        blockOtherTurns = true;
    }
}

void upTurn()
{
    for(int i: upFaceCubes)
    {
        model_view[i] = RotateX(-50) * RotateZ(-30) * RotateZ(Theta[2]) * RotateZ(30) * RotateX(50) * model_view[i];
    }
    
    turnUpFaceCount++;
    
    if(turnUpFaceCount==30)
    {
        shiftUpTurn();
        turnUpFaceCount=0;
        turnUpFace=false;
        blockOtherTurns = false;
    }
}

void leftTurn()
{
    for(int i: leftFaceCubes)
    {
        model_view[i] = RotateX(-50) * RotateZ(-30) * RotateY(Theta[1]) * RotateZ(30) * RotateX(50) * model_view[i];
    }
    
    turnLeftFaceCount++;
    
    if(turnLeftFaceCount==30)
    {
        shiftLeftTurn();
        turnLeftFaceCount=0;
        turnLeftFace=false;
        blockOtherTurns = false;
    }
}

void leftBackTurn()
{
    for(int i: leftFaceBackCubes)
    {
        model_view[i] = RotateX(-50) * RotateZ(-30) * RotateY(Theta[1]) * RotateZ(30) * RotateX(50) * model_view[i];
    }
    
    turnLeftBackFaceCount++;

    if(turnLeftBackFaceCount==30)
    {
        shiftLeftBackTurn();
        turnLeftBackFaceCount=0;
        turnLeftBackFace=false;
        blockOtherTurns = false;
    }
}


void downTurn()
{
    for(int i: downFaceCubes)
    {
        model_view[i] = RotateX(-50) * RotateZ(-30) * RotateZ(Theta[2]) * RotateZ(30) * RotateX(50) * model_view[i];
    }
    
    turnDownFaceCount++;
    
    if(turnDownFaceCount==30)
    {
        shiftDownTurn();
        turnDownFaceCount=0;
        turnDownFace=false;
        blockOtherTurns = false;
    }
}

void rightTurn()
{
    for(int i: rightFaceCubes)
    {
        model_view[i] = RotateX(-50) * RotateZ(-30) * RotateX(-Theta[0]) * RotateZ(30) * RotateX(50) * model_view[i];
    }
    
    turnRightFaceCount++;

    if(turnRightFaceCount==30)
    {
        shiftRightTurn();
        turnRightFaceCount=0;
        turnRightFace=false;
        blockOtherTurns = false;
    }
}

void rightBackTurn()
{
    for(int i: rightFaceBackCubes)
    {
        model_view[i] = RotateX(-50) * RotateZ(-30) * RotateX(-Theta[0]) * RotateZ(30) * RotateX(50) * model_view[i];
    }
    
    turnRightBackFaceCount++;

    if(turnRightBackFaceCount==30)
    {
        shiftRightBackTurn();
        turnRightBackFaceCount=0;
        turnRightBackFace=false;
        blockOtherTurns = false;
    }
}


void shiftUpTurn()
{
    if (direction == Right)
    {
        int temp = upFaceCubes[3];
        upFaceCubes[3] = upFaceCubes[2];
        upFaceCubes[2] = upFaceCubes[1];
        upFaceCubes[1] = upFaceCubes[0];
        upFaceCubes[0] = temp;
    }
    else
    {
        int temp = upFaceCubes[0];
        upFaceCubes[0] = upFaceCubes[1];
        upFaceCubes[1] = upFaceCubes[2];
        upFaceCubes[2] = upFaceCubes[3];
        upFaceCubes[3] = temp;
    }
    
    leftFaceCubes[0] = upFaceCubes[0];
    leftFaceCubes[1] = upFaceCubes[1];
    
    leftFaceBackCubes[0] = upFaceCubes[3];
    leftFaceBackCubes[1] = upFaceCubes[2];
    
    rightFaceCubes[0] = upFaceCubes[1];
    rightFaceCubes[1] = upFaceCubes[2];
    
    rightFaceBackCubes[0] = upFaceCubes[0];
    rightFaceBackCubes[1] = upFaceCubes[3];
}


void shiftLeftTurn()
{
    if (direction == Right)
    {
        int temp = leftFaceCubes[3];
        leftFaceCubes[3] = leftFaceCubes[2];
        leftFaceCubes[2] = leftFaceCubes[1];
        leftFaceCubes[1] = leftFaceCubes[0];
        leftFaceCubes[0] = temp;
    }
    else
    {
        int temp = leftFaceCubes[0];
        leftFaceCubes[0] = leftFaceCubes[1];
        leftFaceCubes[1] = leftFaceCubes[2];
        leftFaceCubes[2] = leftFaceCubes[3];
        leftFaceCubes[3] = temp;
    }
    
    upFaceCubes[0] = leftFaceCubes[0];
    upFaceCubes[1] = leftFaceCubes[1];
    
    rightFaceCubes[0] = leftFaceCubes[1];
    rightFaceCubes[3] = leftFaceCubes[2];
    
    rightFaceBackCubes[0] = leftFaceCubes[0];
    rightFaceBackCubes[3] = leftFaceCubes[3];
    
    downFaceCubes[1] = leftFaceCubes[2];
    downFaceCubes[0] = leftFaceCubes[3];
}

void shiftLeftBackTurn()
{
    if (direction == Right)
    {
        int temp = leftFaceBackCubes[3];
        leftFaceBackCubes[3] = leftFaceBackCubes[2];
        leftFaceBackCubes[2] = leftFaceBackCubes[1];
        leftFaceBackCubes[1] = leftFaceBackCubes[0];
        leftFaceBackCubes[0] = temp;
    }
    else
    {
        int temp = leftFaceBackCubes[0];
        leftFaceBackCubes[0] = leftFaceBackCubes[1];
        leftFaceBackCubes[1] = leftFaceBackCubes[2];
        leftFaceBackCubes[2] = leftFaceBackCubes[3];
        leftFaceBackCubes[3] = temp;
    }
    
    upFaceCubes[3] = leftFaceBackCubes[0];
    upFaceCubes[2] = leftFaceBackCubes[1];
    
    rightFaceCubes[1] = leftFaceBackCubes[1];
    rightFaceCubes[2] = leftFaceBackCubes[2];
    
    rightFaceBackCubes[1] = leftFaceBackCubes[0];
    rightFaceBackCubes[2] = leftFaceBackCubes[3];
    
    downFaceCubes[2] = leftFaceBackCubes[2];
    downFaceCubes[3] = leftFaceBackCubes[3];
}

void shiftDownTurn()
{
    if (direction == Right)
    {
        int temp = downFaceCubes[3];
        downFaceCubes[3] = downFaceCubes[2];
        downFaceCubes[2] = downFaceCubes[1];
        downFaceCubes[1] = downFaceCubes[0];
        downFaceCubes[0] = temp;
    }
    else
    {
        int temp = downFaceCubes[0];
        downFaceCubes[0] = downFaceCubes[1];
        downFaceCubes[1] = downFaceCubes[2];
        downFaceCubes[2] = downFaceCubes[3];
        downFaceCubes[3] = temp;
    }
    
    leftFaceCubes[3] = downFaceCubes[0];
    leftFaceCubes[2] = downFaceCubes[1];
    
    leftFaceBackCubes[3] = downFaceCubes[2];
    leftFaceBackCubes[2] = downFaceCubes[3];
    
    rightFaceCubes[3] = downFaceCubes[1];
    rightFaceCubes[2] = downFaceCubes[2];
    
    rightFaceBackCubes[3] = downFaceCubes[0];
    rightFaceBackCubes[2] = downFaceCubes[3];
}

void shiftRightTurn()
{
    if (direction == Right)
    {
        int temp = rightFaceCubes[3];
        rightFaceCubes[3] = rightFaceCubes[2];
        rightFaceCubes[2] = rightFaceCubes[1];
        rightFaceCubes[1] = rightFaceCubes[0];
        rightFaceCubes[0] = temp;
    }
    else
    {
        int temp = rightFaceCubes[0];
        rightFaceCubes[0] = rightFaceCubes[1];
        rightFaceCubes[1] = rightFaceCubes[2];
        rightFaceCubes[2] = rightFaceCubes[3];
        rightFaceCubes[3] = temp;
    }
    
    upFaceCubes[1] = rightFaceCubes[0];
    upFaceCubes[2] = rightFaceCubes[1];
    
    leftFaceCubes[1] = rightFaceCubes[0];
    leftFaceCubes[2] = rightFaceCubes[3];
    
    leftFaceBackCubes[1] = rightFaceCubes[1];
    leftFaceBackCubes[2] = rightFaceCubes[2];
    
    downFaceCubes[2] = rightFaceCubes[2];
    downFaceCubes[1] = rightFaceCubes[3];
}

void shiftRightBackTurn()
{
    if (direction == Right)
    {
        int temp = rightFaceBackCubes[3];
        rightFaceBackCubes[3] = rightFaceBackCubes[2];
        rightFaceBackCubes[2] = rightFaceBackCubes[1];
        rightFaceBackCubes[1] = rightFaceBackCubes[0];
        rightFaceBackCubes[0] = temp;
    }
    else
    {
        int temp = rightFaceBackCubes[0];
        rightFaceBackCubes[0] = rightFaceBackCubes[1];
        rightFaceBackCubes[1] = rightFaceBackCubes[2];
        rightFaceBackCubes[2] = rightFaceBackCubes[3];
        rightFaceBackCubes[3] = temp;
    }
    
    upFaceCubes[0] = rightFaceBackCubes[0];
    upFaceCubes[3] = rightFaceBackCubes[1];
    
    leftFaceCubes[0] = rightFaceBackCubes[0];
    leftFaceCubes[3] = rightFaceBackCubes[3];
    
    leftFaceBackCubes[0] = rightFaceBackCubes[1];
    leftFaceBackCubes[3] = rightFaceBackCubes[2];
    
    downFaceCubes[3] = rightFaceBackCubes[2];
    downFaceCubes[0] = rightFaceBackCubes[3];
}

//----------------------------------------------------------------------------

void mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
        switch( button ) {
            case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
            case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
            case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
        }
    }
}

void print_helper()
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "Q/q : Quit" << std::endl;
    std::cout << "H/h : Helper" << std::endl;
    std::cout << "I/i : Initialize" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << "Use Keys to rotate the faces" << std::endl;
    std::cout << "W/w : Turn upper face" << std::endl;
    std::cout << "A/a : Turn left face" << std::endl;
    std::cout << "S/s : Turn bottom face" << std::endl;
    std::cout << "D/d : Turn right face" << std::endl;
    std::cout << "C/c : Change turning direction" << std::endl;
    std::cout << "------------------------------" << std::endl;
    

}


//----------------------------------------------------------------------------
void timer( int p )
{
    Theta[Axis] += 2.0;
    if ( Theta[Axis] > 360.0 ) {
        Theta[Axis] -= 360.0;
    }
    glutPostRedisplay();
    
    glutTimerFunc(100,timer,0);
}


//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(  GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_3_2_CORE_PROFILE);
    glutInitWindowSize( 512, 512 );
    glutCreateWindow( "Color Cube" );
    
    glewExperimental = GL_TRUE;
    glewInit();

    init();
    
    glutDisplayFunc( display ); // set display callback function
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );
    glutMouseFunc( mouse );
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrowKeys);

    //glutTimerFunc(5,timer,0);
    

    glutMainLoop();
    return 0;
}
