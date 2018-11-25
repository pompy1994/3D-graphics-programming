//  MYLAB8
//
//  Created by zhuweiping on 16/5/26.
//  Copyright © 2016年 zhuweiping. All rights reserved.

#include <GL/GLUT.h>
#include <math.h>   //for sqrt()

//set boundary
#define WIN_LEFT -35
#define WIN_RIGHT 40
#define WIN_BOTTOM -35
#define WIN_TOP 35
#define WIN_NEAR -35
#define WIN_FAR 35

//set arguments of object


#define HEAD_HEIGHT 1.9
#define HEAD_RADIUS1 1.0
#define HEAD_RADIUS2 1.25

#define DESK_HEIGHT 18
#define DESK_WIDTH 10
#define DESK_DEPTH 4

#define GROUND_HEIGHT 5
#define GROUND_WIDTH 80
#define GROUND_DEPTH 12


#define EYE_RADIUS 0.14

#define NECK_RADIUS 0.8
#define NECK_HEIGHT 1.0


#define BODY_HEIGHT 9.5
#define BODY_RADIUS 3.0
#define BODY_RADIUS2 2.6

#define UPPER_ARM_HEIGHT 6.3
#define UPPER_ARM_RADIUS1 0.5
#define UPPER_ARM_RADIUS2 0.7

#define LOWER_ARM_HEIGHT 5.0
#define LOWER_ARM_RADIUS1 0.3
#define LOWER_ARM_RADIUS2 0.5


#define UPPER_LEG_HEIGHT 8
#define UPPER_LEG_RADIUS1 0.8
#define UPPER_LEG_RADIUS2 1.3


#define LOWER_LEG_HEIGHT 7
#define LOWER_LEG_RADIUS1 0.8
#define LOWER_LEG_RADIUS2 0.8
#define LEG_RADIUS 0.7

#define CHIN_RADIUS 1.00
#define HAT_RADIUS  1.2



#define FOOT_WIDTH 1.2
#define FOOT_DEPTH 3.2
#define FOOT_HEIGHT 0.8

#define HAND_WIDTH 0.3
#define HAND_DEPTH 1
#define HAND_HEIGHT 2

#define BOOK_WIDTH 0.4
#define BOOK_DEPTH 6
#define BOOK_HEIGHT 4

#define SHOULDER_RADIUS 0.7

#define PIPI_RADIUS 1.25
#define SPOTLIGHT_RADIUS 0.5



#define NOSE_WIDTH 0.3
#define NOSE_DEPTH 1
#define NOSE_HEIGHT 0.4

#define MOUTH_RADIUS_IN 0.1
#define MOUTH_RADIUS_OUT 0.5
#define EYEBROW_IN 0.1
#define EYEBROW_OUT 0.5







//set the order of all parts
#define ALL 0
#define BODY 1
#define LUA 2
#define LLA 3
#define RUA 4
#define RLA 5
#define LUL 6
#define LLL 7
#define RUL 8
#define RLL 9
#define LF 10
#define RF 11

//set translating, bending and rotate velocity
#define transLeftBoudary -40.0
#define transRightBoudary 40.0
#define transVelocity 0.7/3

#define bendBODYv 0.1/2
#define bendLUAv 0.8/2
#define bendLLAv 0.4/2
#define bendRUAv 0.8/2
#define bendRLAv 0.4/2
#define bendLULv 0.8/2
#define bendLLLv 0.4/2
#define bendRULv 0.8/2
#define bendRLLv 0.4/2
#define bendLFv 0.15/2
#define bendRFv 0.15/2


#define rotateVelocity -0.25
//set rotate angle
GLfloat theta[]={0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0,0,0,0};


//set bending direction
GLfloat bendingDirection[]={0,-1,1,1,-1,-1,-1,-1,1,1,1,1};

//set states
GLboolean bending_state=GL_FALSE;
GLboolean rotate_state=GL_FALSE;



GLUquadricObj *p;//for draw cylinder, disk and sphere

//set material structure
typedef struct materialStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
} materialStruct;


materialStruct handsomeHeadMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeChinMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeFootMaterials={{93.0/255.0,64.0/255.0,44.0/255.0},{0.4,0.4,0.4},{0.85,0.65,0.49},5};
materialStruct handsomeNeckMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeBodyMaterials={{123.0/255.0,132.0/255.0,146.0/255.0},{123.0/255.0,132.0/255.0,146.0/255.0},{123.0/255.0,132.0/255.0,146.0/255.0},10};
materialStruct handsomeUpperArmMaterials={{115.0/255.0,94.0/255.0,95.0/255.0},{20,20,20},{115.0/255.0,94.0/255.0,95.0/255.0},20};
materialStruct handsomeLowerArmMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeUpperLegMaterials={{39.0/255.0,37.0/255.0,43.0/255.0 },{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct handsomeLowerLegMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct  handsomeHatMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{59.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct handsomeHandMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeEyeMaterials={{0.0,0.0,0.0},{0.4,0.4,0.4},{0.85,0.65,0.49},5};

materialStruct handsomeDeskMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};

materialStruct handsomeGroundMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeBookMaterials={{192.0/255.0,157.0/255.0,99.0/255.0},{1,1,1},{229.0/255.0,199.0/255.0,135.0/255.0},100};
materialStruct handsomeShoulderMaterials={{0.5,0.5,0.5},{1,1,1},{0.2,0.2,0.2},100};
materialStruct handsomeEyebrowMaterials={{39.0/255.0,37.0/255.0,43.0/255.0 },{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct handsomeNoseMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct handsomeMouthMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};




materialStruct officialHeadMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct officialChinMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct officialFootMaterials={{0,0,0},{0,0,0},{0,0,0},5};
materialStruct officialNeckMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct officialBodyMaterials={{0,0,0},{65.0/255.0,63.0/255.0,77.0/255.0},{84.0/255.0,104.0/255.0,178.0/255.0},5};
materialStruct officialUpperArmMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct officialLowerArmMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct officialUpperLegMaterials={{0,0,0},{65.0/255.0,63.0/255.0,77.0/255.0},{84.0/255.0,104.0/255.0,178.0/255.0},5};
materialStruct officialLowerLegMaterials={{0,0,0},{65.0/255.0,63.0/255.0,77.0/255.0},{84.0/255.0,104.0/255.0,178.0/255.0},5};

materialStruct  officialHatMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{59.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct officialHandMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct officialEyeMaterials={{0.0,0.0,0.0},{0.4,0.4,0.4},{0.85,0.65,0.49},5};

materialStruct officialDeskMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};

materialStruct officialGroundMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct officialBookMaterials={{0.5,0.5,0.5},{1,1,1},{0.2,0.2,0.2},100};
materialStruct officialShoulderMaterials={{0.5,0.5,0.5},{1,1,1},{0.2,0.2,0.2},100};
materialStruct officialEyebrowMaterials={{39.0/255.0,37.0/255.0,43.0/255.0 },{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct officialNoseMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct officialMouthMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};




materialStruct leisureHeadMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureChinMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureFootMaterials={{0.3,0.3,0.3},{207.0/255.0,213.0/255.0,213.0/255.0},{207.0/255.0,213.0/255.0,213.0/255.0},5};
materialStruct leisureNeckMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureBodyMaterials={{195.0/255.0,206.0/255.0,222.0/255.0},{195.0/255.0,206.0/255.0,222.0/255.0},{195.0/255.0,206.0/255.0,222.0/255.0},10};
materialStruct leisureUpperArmMaterials={{154.0/255.0,163.0/255.0,197.0/255.0},{0.5,0.5,0.5},{0.5,0.5,0.5},10};
materialStruct leisureLowerArmMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureUpperLegMaterials={{0,0,0},{65.0/255.0,63.0/255.0,77.0/255.0},{84.0/255.0,104.0/255.0,178.0/255.0},5};
materialStruct leisureLowerLegMaterials={{0,0,0},{65.0/255.0,63.0/255.0,77.0/255.0},{84.0/255.0,104.0/255.0,178.0/255.0},5};
materialStruct  leisureHatMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{59.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct leisureHandMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureEyeMaterials={{0.0,0.0,0.0},{0.4,0.4,0.4},{0.85,0.65,0.49},5};

materialStruct leisureDeskMaterials={{39.0/255.0,37.0/255.0,43.0/255.0},{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};

materialStruct leisureGroundMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureBookMaterials={{115.0/255.0,94.0/255.0,95.0/255.0},{1,1,1},{115.0/255.0,94.0/255.0,95.0/255.0},100};
materialStruct leisureShoulderMaterials={{0.5,0.5,0.5},{1,1,1},{0.2,0.2,0.2},100};
materialStruct leisureEyebrowMaterials={{39.0/255.0,37.0/255.0,43.0/255.0 },{65.0/255.0,63.0/255.0,77.0/255.0},{50.0/255.0,58.0/255.0,68.0/255.0},5};
materialStruct leidureNoseMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};
materialStruct leisureMouthMaterials={{58.0/255.0,33.0/255.0,24.0/255.0},{151.0/255.0,92.0/255.0,65.0/255.0},{175.0/255.0,127.0/255.0,11.0/255.00},20};


//set material of every part
materialStruct *chinMaterials;
materialStruct *headMaterials;
materialStruct *footMaterials;
materialStruct *neckMaterials;
materialStruct *bodyMaterials;
materialStruct *upperArmMaterials;
materialStruct *lowerArmMaterials;
materialStruct *upperLegMaterials;
materialStruct *lowerLegMaterials;
materialStruct *deskMaterials;
materialStruct *handMaterials;
materialStruct *hatMaterials;
materialStruct *eyeMaterials;
materialStruct *groundMaterials;
materialStruct *bookMaterials;
materialStruct *shoulderMaterials;
materialStruct *eyebrowMaterials;
materialStruct *mouthMaterials;
materialStruct *noseMaterials;


//set lighting structure
typedef struct lightingStruct
{
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
} lightingStruct;

//set white ,yellow adn red light
lightingStruct whiteLighting={{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0}};
lightingStruct yellowLighting={{0.0,0.0,0.0,1.0},{1.8,1.0,0.0,1.0},{1.0,1.0,0.0,1.0}};
lightingStruct redLighting={{0.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0},{1.0,0.0,0.0,1.0}};

//set current lighting
lightingStruct *currentLighting;


//set spot sphere's color,cutoff angle
GLfloat sphere_color[3];
GLfloat cutoff_angle;

//set light's position and direction
GLfloat light0_pos[]={WIN_RIGHT*2/3,WIN_TOP*2/3,WIN_FAR*2/3,1.0};
GLfloat light_pos1[]={-WIN_RIGHT*2/3,WIN_TOP*2/3,WIN_FAR*2/3,1.0};
GLfloat light0_direction[]={-1,-1,-1};



//draw the object

void foot()
{
    glPushMatrix();
    glTranslatef(0, -0.5*FOOT_HEIGHT,0.0);
    glScaled(FOOT_WIDTH, FOOT_HEIGHT, FOOT_DEPTH);
    glColor3f(0,0,0);
    glutSolidCube(1.0);
    glPopMatrix();
    return;
    
    
}


void hand()
{
    glPushMatrix();
    glRotatef(-10, 1.0, 0.0, 0.0);
    glTranslatef(0, -0.5*HAND_HEIGHT,0.0);
    glScaled(HAND_WIDTH, HAND_HEIGHT, HAND_DEPTH);
    glColor3f(0.50,0.36,0.173);
    glutSolidCube(1.0);
    glPopMatrix();
    return;
    
    
}
void book()
{
    glPushMatrix();
    
    glTranslatef(0, -0.5*BOOK_HEIGHT,0.0);
    glScaled(BOOK_WIDTH, BOOK_HEIGHT, BOOK_DEPTH);
    glutSolidCube(1.0);
    glPopMatrix();
    return;
    
    
}

void desk()
{
    glPushMatrix();
    glScaled(DESK_WIDTH, DESK_HEIGHT, DESK_DEPTH);
    glutSolidCube(1.0);
    glTranslatef(0, 0,0);
    
    glPopMatrix();
    return;
    
    
}

void ground()
{
    glPushMatrix();
    glScaled(GROUND_WIDTH, GROUND_HEIGHT, GROUND_DEPTH);
    glutSolidCube(1.0);
    glPopMatrix();
    return;
    
    
}

//draw the object

void nose()
{
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    glScaled(NOSE_WIDTH, NOSE_HEIGHT, NOSE_DEPTH);
    glutSolidCube(1.0);
    glPopMatrix();
}



void mouth()
{
    glPushMatrix();
    glScaled(1, 0.4, 1);
    gluDisk(p, MOUTH_RADIUS_IN, MOUTH_RADIUS_OUT, 32, 32);
    glPopMatrix();
    
    
}

void eyebrow()
{
    glPushMatrix();
    glScaled(1, 1.5,2);
    glRotatef(70, 1, 0, 0);
    gluDisk(p, EYEBROW_IN, EYEBROW_OUT, 32, 32);
    glPopMatrix();
}

void body()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,BODY_RADIUS2,BODY_RADIUS,BODY_HEIGHT,100,100);
    glTranslatef(0, 0, BODY_HEIGHT);
    glPopMatrix();
    return;
}

void head()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,HEAD_RADIUS1,HEAD_RADIUS2,HEAD_HEIGHT,100,100);
    glPopMatrix();
    return;
    
    
}



void hat()
{
    glPushMatrix();
    glRotatef(-60, 1.0, 0.0, 0.0);
    gluSphere(p,HAT_RADIUS,100,100);
    glPopMatrix();
    return;
    
}



void chin()
{
    glPushMatrix();
    gluSphere(p,CHIN_RADIUS,100,100);
    glPopMatrix();
    return;
    
}




void neck()
{
    glPushMatrix();
    glRotatef(90.0,1.0,0.0,0.0);
    gluCylinder(p, NECK_RADIUS, NECK_RADIUS, NECK_HEIGHT,100,100);
    glPopMatrix();
    return;
}

void lower_leg()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,LOWER_LEG_RADIUS1,LOWER_LEG_RADIUS2,LOWER_LEG_HEIGHT,100,100);
    glTranslatef(0, 0, LOWER_LEG_HEIGHT);
    glPopMatrix();
    return;
}


void upper_leg()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,UPPER_LEG_RADIUS1,UPPER_LEG_RADIUS2,UPPER_LEG_HEIGHT,100,100);
    glTranslatef(0, 0, UPPER_LEG_HEIGHT);
    glPopMatrix();
    return;
}

void lower_arm()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,LOWER_ARM_RADIUS1,LOWER_ARM_RADIUS2,LOWER_ARM_HEIGHT,100,100);
    glTranslatef(0, 0, LOWER_ARM_HEIGHT);
    glPopMatrix();
    return;
}

void upper_arm()
{
    glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(p,UPPER_ARM_RADIUS1,UPPER_ARM_RADIUS2,UPPER_ARM_HEIGHT,100,100);
    glTranslatef(0, 0, UPPER_ARM_HEIGHT);
    glPopMatrix();
    return;
}

void eye()
{
    glPushMatrix();
    glutSolidSphere(EYE_RADIUS, 100, 100);
    glPopMatrix();
    return;
}

void shoulder()
{
    glPushMatrix();
    glutSolidSphere(SHOULDER_RADIUS,100,100);
    glPopMatrix();
    return;
}

void pipi()
{
    glPushMatrix();
    glutSolidSphere(PIPI_RADIUS,100,100);
    glPopMatrix();
    return;
}

void leg()
{
    glPushMatrix;
    glutSolidSphere(LEG_RADIUS,100,100);
    glPopMatrix();
    return;
}



//draw the spotlight and set the spotlight's emission color
void spotlight()
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3fv(sphere_color);
    glutSolidSphere(SPOTLIGHT_RADIUS, 100, 100);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    return;
}

//make a function to set material of every part
void chooseMaterial(materialStruct *material)
{
    glMaterialfv(GL_FRONT,GL_AMBIENT,material->ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE,material->diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,material->specular);
    glMaterialfv(GL_FRONT,GL_SHININESS,&material->shininess);
    return;
}

//MAKE the whole object and put the object into world
void object()
{
    
    //make the desk
    glPushMatrix();
    chooseMaterial(deskMaterials);
    glTranslatef(0, -6, 0);
    desk();
    
    glPopMatrix();
    
    //make the ground
    glPushMatrix();
    chooseMaterial(groundMaterials);
    glTranslatef(0, -16.5, 0);
    ground();
    glPopMatrix();
    
    
    
    glRotatef(theta[ALL], 0, 1, 0);//all part should rotate some angles
    glTranslatef(22, 0, 0);
    
    //make the head
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(headMaterials);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    head();
    glPopMatrix();
    
    //hat
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(hatMaterials);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT+0.2, 0);
    glRotatef(40, 1, 0, 0);
    hat();
    glPopMatrix();
    
    
    //make the chin
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(chinMaterials);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT+0.09, 0);
    chin();
    glPopMatrix();
    
    
    //make the nose
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(noseMaterials);
    glTranslatef(0,BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT*3/4-EYE_RADIUS*2,HEAD_HEIGHT*2.5/5);
    nose();
    glPopMatrix();
    
    //make the mouth
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(mouthMaterials);
    glTranslatef(0,BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT*3/4-EYE_RADIUS*8,HEAD_HEIGHT*3/5);
    mouth();
    glPopMatrix();
    
    
    //make the right eyebrow
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(eyebrowMaterials);
    glTranslatef(HEAD_RADIUS2*2.5/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT-0.2,HEAD_HEIGHT*1/5);
    eyebrow();
    glPopMatrix();
    
    
    //make the left eyebrow
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(eyebrowMaterials);
    glTranslatef(-HEAD_RADIUS2*2.5/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT-0.2,HEAD_HEIGHT*1/5);
    eyebrow();
    glPopMatrix();
    
    
    
    //make the neck
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(neckMaterials);
    glTranslatef(0, BODY_HEIGHT+NECK_HEIGHT, 0);
    neck();
    glPopMatrix();
    
    
    //make the body
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(bodyMaterials);
    body();
    glPopMatrix();
    
    
    
    
    //make the left upper and lower arm
    glPushMatrix();
    
    chooseMaterial(upperArmMaterials);
    glTranslatef(-BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT-1, 0);
    shoulder();
    glRotatef(theta[LUA], 1, 0, 0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    upper_arm();
    chooseMaterial(lowerArmMaterials);
    glRotatef(theta[LLA], 1, 0, 0);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9,0.0);
    lower_arm();
    
    chooseMaterial(handMaterials);
    glTranslatef(0.0, -HAND_HEIGHT+2.2,0.0);
    hand();
    chooseMaterial(bookMaterials);
    glTranslatef(0.2, 0.1,0.3);
    book();
    
    glPopMatrix();
    
    
    
    
    
    
    //make the right upper and lower arm
    glPushMatrix();
    chooseMaterial(upperArmMaterials);
    glTranslatef(BODY_RADIUS*8/7, 0, 0);
    glTranslatef(0.0, BODY_HEIGHT-1, 0);
    shoulder();
    glRotatef(theta[RUA],1,0,0);
    glTranslatef(0.0, -UPPER_ARM_HEIGHT, 0.0);
    
    upper_arm();
    
    chooseMaterial(lowerArmMaterials);
    glRotatef(theta[LLA], 1, 0, 0);
    glTranslatef(0.0, -LOWER_ARM_HEIGHT*0.9,0.0);
    lower_arm();
    
    chooseMaterial(handMaterials);
    glRotatef(70,0, 1, 0);
    glTranslatef(0.0, -HAND_HEIGHT+2.2,0.0);
    glRotatef(theta[LUL], 1, 0, 0);
    hand();
    glPopMatrix();
    
    //left pipi
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(-BODY_RADIUS/2, 0, 0);
    pipi();
    glPopMatrix();
    
    //right pipi
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(BODY_RADIUS/2, 0, 0);
    pipi();
    glPopMatrix();
    
    //make the left leg
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(-BODY_RADIUS/2, 0, 0);
    glRotatef(theta[LUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT+0.1, 0.0);
    chooseMaterial(lowerLegMaterials);
    glRotatef(theta[LLL], 1, 0, 0);
    leg();
    glPopMatrix();
    
    //make the right leg
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(BODY_RADIUS/2, 0, 0);
    glRotatef(theta[RUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT+0.1, 0.0);
    chooseMaterial(lowerLegMaterials);
    glRotatef(theta[RLL], 1, 0, 0);
    leg();
    glPopMatrix();
    
    
    //make the left upper and lower leg  and foot
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(-BODY_RADIUS/2, 0, 0);
    glRotatef(theta[LUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT+0.1, 0.0);
    upper_leg();
    
    chooseMaterial(lowerLegMaterials);
    glRotatef(theta[LLL], 1, 0, 0);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT+0.1, 0.0);
    lower_leg();
    
    
    chooseMaterial(footMaterials);
    glRotatef(theta[RLL], 1, 0, 0);
    glTranslatef(0, -FOOT_HEIGHT+1,0.5);
    foot();
    
    glPopMatrix();
    
    
    //make the right upper and lower leg and foot
    glPushMatrix();
    glRotatef(theta[BODY], 1, 0, 0);
    chooseMaterial(upperLegMaterials);
    glTranslatef(BODY_RADIUS/2, 0, 0);
    glRotatef(theta[RUL], 1, 0, 0);
    glTranslatef(0.0, -UPPER_LEG_HEIGHT+0.1, 0.0);
    upper_leg();
    chooseMaterial(lowerLegMaterials);
    glRotatef(theta[RLL], 1, 0, 0);
    glTranslatef(0.0, -LOWER_LEG_HEIGHT+0.1, 0.0);
    lower_leg();
    
    chooseMaterial(footMaterials);
    glRotatef(theta[LLL], 1, 0, 0);
    glTranslatef(0, -FOOT_HEIGHT+1,0.5);
    foot();
    
    
    glPopMatrix();
    
    
    //make the left eye
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(eyeMaterials);
    glTranslatef(-HEAD_RADIUS2*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT*3/4-EYE_RADIUS,HEAD_HEIGHT*3/5);
    eye();
    
    
    glPopMatrix();
    
    //make the right eye
    glPushMatrix();
    glRotatef(theta[BODY]/2, 1, 0, 0);
    chooseMaterial(eyeMaterials);
    glTranslatef(HEAD_RADIUS2*2/5,BODY_HEIGHT+NECK_HEIGHT+HEAD_HEIGHT*3/4-EYE_RADIUS,HEAD_HEIGHT*3/5);
    eye();
    
    glPopMatrix();
    return;
}

//display function
void display()
{
    
    //clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //enable light
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    
    //set SPOTlight
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);//set current light ambient
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);//set current light diffuse
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);//set current specular
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);//set current light direction
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, cutoff_angle);//set current light cutoff angle
    glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glTranslatef(WIN_RIGHT,WIN_TOP*2/3,WIN_FAR);//move the spot sphere to where spot light is
    spotlight();//draw spot light
    
    //set the camera
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0,0.0);//isometric view
    
    object();
    
    //double buffer
    glutSwapBuffers();
    return;
}

void bendFunc(GLint order, GLfloat MaxAngle, GLfloat MinAngle)
{
    if (theta[order]>=MaxAngle)
        bendingDirection[order]=-1;
    if (theta[order]<=MinAngle)
        bendingDirection[order]=1;
    return;
}

//run the function if there is no event
void myidle(GLint x,GLint y)
{
    
    theta[BODY]+=bendBODYv*bendingDirection[BODY];
    bendFunc(BODY,7,-4);
    theta[LUA]+=bendLUAv*bendingDirection[LUA];
    bendFunc(LUA,32,-32);
    theta[LLA]+=bendLUAv*bendingDirection[LLA];
    bendFunc(LLA,0,-15);
    theta[RUA]+=bendRUAv*bendingDirection[RUA];
    bendFunc(RUA,8,-160);
    theta[RLA]+=bendRLAv*bendingDirection[RLA];
    bendFunc(RLA,20,-20);
    theta[LUL]+=bendLULv*bendingDirection[LUL];
    bendFunc(LUL,32,-32);
    theta[LLL]+=bendLLLv*bendingDirection[LLL];
    bendFunc(LLL,15,-8);
    theta[RUL]+=bendRULv*bendingDirection[RUL];
    bendFunc(RUL,32,-32);
    theta[RLL]+=bendRLLv*bendingDirection[RLL];
    bendFunc(RLL,15,-8);
    theta[LF]+=bendLFv*bendingDirection[LF];
    bendFunc(LF,25,-25);
    theta[RF]+=bendRFv*bendingDirection[RF];
    bendFunc(RF,25,-25);
    theta[ALL]+=rotateVelocity;
    if (theta[ALL]>360)
        theta[ALL]=0;
    
    
    
    theta[ALL]+=rotateVelocity;
    if (theta[ALL]>360)
    {
        theta[ALL]=0;
    }
    x=22*cos(theta[ALL]);
    y=22*sin(theta[ALL]);
    
    
    
    glutPostRedisplay();
    return;
}

//use keyboard function to change color
void changeLightByKey(unsigned char key,int x,int y)
{
    if (key=='w'||key=='W')
    {
        currentLighting=&whiteLighting;//change current lighting
        cutoff_angle=40;//cutoff angle
        //set sphere color
        sphere_color[0]=1.0;
        sphere_color[1]=1.0;
        sphere_color[2]=1.0;
        return;
    }
    if (key=='y'||key=='Y')
    {
        currentLighting=&yellowLighting;
        cutoff_angle=40;
        sphere_color[0]=1.0;
        sphere_color[1]=1.0;
        sphere_color[2]=0.0;
        return;
    }
    if (key=='r'||key=='R')
    {
        currentLighting=&redLighting;
        cutoff_angle=40;
        sphere_color[0]=1.0;
        sphere_color[1]=0.0;
        sphere_color[2]=0.0;
        return;
    }
    return;
}
//use menuL to change lightsource

void mymenuL(int id)
{
    if(id==1)
    {  glDisable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT1);
        
    }
    if(id==2)
    {
        glDisable(GL_LIGHT1);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        
    }
}
//create menuL
void createMenul()
{
    int id;
    id=glutCreateMenu(mymenuL);
    glutAddMenuEntry("Sun",1);
    glutAddMenuEntry("Spotlight",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    return;
}


//use menu2 to change materials
void mymenu(int id)
{
    if (id==1)
    {
        eyeMaterials=&handsomeEyeMaterials;
        headMaterials=&handsomeHeadMaterials;
        footMaterials=&handsomeFootMaterials;
        neckMaterials=&handsomeNeckMaterials;
        bodyMaterials=&handsomeBodyMaterials;
        upperArmMaterials=&handsomeUpperArmMaterials;
        lowerArmMaterials=&handsomeLowerArmMaterials;
        upperLegMaterials=&handsomeUpperLegMaterials;
        lowerLegMaterials=&handsomeLowerLegMaterials;
        handMaterials=&handsomeHandMaterials;
        hatMaterials=&handsomeHatMaterials;
        deskMaterials=&handsomeDeskMaterials;
        groundMaterials=&handsomeGroundMaterials;
        chinMaterials=&handsomeChinMaterials;
        bookMaterials=&handsomeBookMaterials;
        shoulderMaterials=&handsomeShoulderMaterials;
        
        return;
    }
    if (id==2)
    {
        
        eyeMaterials=&officialEyeMaterials;
        headMaterials=&officialHeadMaterials;
        footMaterials=&officialFootMaterials;
        neckMaterials=&officialNeckMaterials;
        bodyMaterials=&officialBodyMaterials;
        upperArmMaterials=&officialUpperArmMaterials;
        lowerArmMaterials=&officialLowerArmMaterials;
        upperLegMaterials=&officialUpperLegMaterials;
        lowerLegMaterials=&officialLowerLegMaterials;
        handMaterials=&officialHandMaterials;
        hatMaterials=&officialHatMaterials;
        deskMaterials=&officialDeskMaterials;
        groundMaterials=&officialGroundMaterials;
        chinMaterials=&officialChinMaterials;
        bookMaterials=&officialBookMaterials;
        shoulderMaterials=&officialShoulderMaterials;
        return;
    }
    if (id==3)
    {
        eyeMaterials=&leisureEyeMaterials;
        headMaterials=&leisureHeadMaterials;
        footMaterials=&leisureFootMaterials;
        neckMaterials=&leisureNeckMaterials;
        bodyMaterials=&leisureBodyMaterials;
        upperArmMaterials=&leisureUpperArmMaterials;
        lowerArmMaterials=&leisureLowerArmMaterials;
        upperLegMaterials=&leisureUpperLegMaterials;
        lowerLegMaterials=&leisureLowerLegMaterials;
        handMaterials=&leisureHandMaterials;
        hatMaterials=&leisureHatMaterials;
        deskMaterials=&leisureDeskMaterials;
        groundMaterials=&leisureGroundMaterials;
        chinMaterials=&leisureChinMaterials;
        bookMaterials=&leisureBookMaterials;
        shoulderMaterials=&leisureShoulderMaterials;
        return;
    }
    return;
}

//create menu2
void createMenu()
{
    int id;
    id=glutCreateMenu(mymenu);
    glutAddMenuEntry("handsome sytle",1);
    glutAddMenuEntry("official style",2);
    glutAddMenuEntry("leisure style",3);
    glutAttachMenu(GLUT_LEFT_BUTTON);
    return;
}



//initialize color,light and material
void myinit()
{
    glClearColor(52.0/255.0,54.0/255.0,52.0/255.0,0.1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    p=gluNewQuadric();
    
    currentLighting=&whiteLighting;
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, currentLighting->ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, currentLighting->diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, currentLighting->specular);
    
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
    
    eyeMaterials=&handsomeEyeMaterials;
    
    headMaterials=&handsomeHeadMaterials;
    footMaterials=&handsomeFootMaterials;
    neckMaterials=&handsomeNeckMaterials;
    bodyMaterials=&handsomeBodyMaterials;
    upperArmMaterials=&handsomeUpperArmMaterials;
    lowerArmMaterials=&handsomeLowerArmMaterials;
    upperLegMaterials=&handsomeUpperLegMaterials;
    lowerLegMaterials=&handsomeLowerLegMaterials;
    handMaterials=&handsomeHandMaterials;
    hatMaterials=&handsomeHatMaterials;
    bookMaterials=&handsomeBookMaterials;
    groundMaterials=&handsomeGroundMaterials;
    deskMaterials=&handsomeDeskMaterials;
    chinMaterials=&handsomeChinMaterials;
    shoulderMaterials=&handsomeShoulderMaterials;
    mouthMaterials=&handsomeMouthMaterials;
    noseMaterials=&handsomeNoseMaterials;
    eyebrowMaterials=&handsomeEyebrowMaterials;
    
    
    return;
}




//make sure the whole object appears in the middle of the window and stay original ratio when reshape
void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w<=h)
        glOrtho(WIN_LEFT,WIN_RIGHT,WIN_BOTTOM*(GLfloat)h/(GLfloat)w,WIN_TOP*(GLfloat)h/(GLfloat)w,WIN_NEAR,WIN_FAR);
    else
        glOrtho(WIN_LEFT*(GLfloat)w/(GLfloat)h,WIN_RIGHT*(GLfloat)w/(GLfloat)h,WIN_BOTTOM,WIN_TOP,WIN_NEAR,WIN_FAR);
    return;
}




int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800,800);
    glutCreateWindow("im Obama!");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(myidle);
    
    glutKeyboardFunc(changeLightByKey);
    glEnable(GL_DEPTH_TEST);
    myinit();
    createMenu();
    createMenul();
    glutMainLoop();
}

