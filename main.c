//#include<windows.h>
#include<stdio.h>
#include<GL/glut.h>
#include<math.h>
// Rotation angle and speed variables
GLfloat rSpinner;
GLfloat rSpinnerSpeed = 0.1f;

// Spinner leafs coordinates
GLfloat sp_c[][3] = {
	{0.0,0.0,0.0},{-0.5,0.0,0.0},{-1.0,0.0,0.0},{-0.5,0.5,0.0},
	{0.0,0.5,0.0},{0.0,1.0,0.0},{0.5,0.5,0.0},{0.5,0.0,0.0},
	{1.0,0.0,0.0},{0.5,-0.5,0.0},{0.0,-0.5,0.0},{0.0,-1.0,0.0},
	{-0.5,-0.5,0.0},
	{0.0,0.03,0},{0.02,0.02,0},{0.03,0.0,0.0},{0.02,-0.02,0.0},
	{0.0,-0.03,0.0},{-0.02,-0.02,0},{-0.03,0.0,0.0},{-0.02,-0.02,0.0}

};

// Spinner Stick coordinates
GLfloat st_c[][3] = {
	{-0.03,0.03,0.0},
	{0.03,0.03,0.0},
	{0.03,-2.0,0.0},
	{-0.03,-2.0,0.0}
};

// Converts Decimal to RGB
float crgb(float rgbcolor)
{
	float clr;
	clr = rgbcolor*(1.0/255.0);
	return clr;
}

// Draws Single Leaf
void draw_leaf(int a, int b, int c, int d, int e)
{
	glBegin(GL_POLYGON);
	glVertex3fv(sp_c[a]);
	glVertex3fv(sp_c[b]);
	glVertex3fv(sp_c[c]);
	glVertex3fv(sp_c[d]);
	glVertex3fv(sp_c[e]);
	glEnd();
}

// Draws Triangle
void draw_triangle(int a, int b, int c)
{
	glBegin(GL_POLYGON);
	glVertex3fv(sp_c[a]);
	glVertex3fv(sp_c[b]);
	glVertex3fv(sp_c[c]);
	glEnd();
}

// Draws hole
void draw_hole()
{
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(sp_c[13]);
	glVertex3fv(sp_c[14]);
	glVertex3fv(sp_c[15]);
	glVertex3fv(sp_c[16]);
	glVertex3fv(sp_c[17]);
	glVertex3fv(sp_c[18]);
	glVertex3fv(sp_c[19]);
	glVertex3fv(sp_c[20]);
	glEnd();
}

// Draws spinner stick
void draw_stick()
{
	glColor3f(crgb(196),crgb(167),crgb(141));
	glBegin(GL_POLYGON);
	glVertex3fv(st_c[0]);
	glVertex3fv(st_c[1]);
	glVertex3fv(st_c[2]);
	glVertex3fv(st_c[3]);
	glEnd();
}

// Draws 4 leafs 
void draw_spinner()
{
	// Draws hole
	draw_hole();

	// Leaf 1 - Top-Left
	glColor3f(crgb(255),crgb(152),crgb(0));
	draw_triangle(0,3,4);
	glColor3f(crgb(255.0),crgb(188.0),crgb(0.0));
	draw_leaf(0,1,2,3,4);

	// Leaf 2 - Top-Right
	glColor3f(crgb(173),crgb(20),crgb(87));
	draw_triangle(0,6,7);
	glColor3f(crgb(219.0),crgb(68.0),crgb(55.0));
	draw_leaf(0,4,5,6,7);
	
	// Leaf 3 - Bottom-Right
	glColor3f(crgb(51),crgb(102),crgb(211));
	draw_triangle(0,9,10);
	glColor3f(crgb(66.0),crgb(133.0),crgb(244.0));
	draw_leaf(0,7,8,9,10);
	
	// Leaf 4 - Bottom-Left
	glColor3f(crgb(15),crgb(157),crgb(88));
	draw_triangle(0,12,1);
	glColor3f(crgb(139.0),crgb(195.0),crgb(74.0));
	draw_leaf(0,10,11,12,1);
}

// Axis control variables
static GLfloat theta[]={0,0,0};
static GLint axis=2;

// Display function
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,0.0f); 
	glRotatef(rSpinner,0.0f,0.0f,1.0f);
	draw_spinner();
	glLoadIdentity();                   
	draw_stick();
	rSpinner-=rSpinnerSpeed;
	glutPostRedisplay();
}

// Reshape function
void myReshape(int w,int h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2,2,-2*(GLfloat)h/(GLfloat)w,2*(GLfloat)h/(GLfloat)w,-10,10);
	else
		glOrtho(-2,2,-2*(GLfloat)w/(GLfloat)h,2*(GLfloat)w/(GLfloat)h,-10,10);
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

// Key Controls
void keys(unsigned char key,int x, int y)
{
	if(key=='a'){
		if(rSpinnerSpeed<=0.1f)
			rSpinnerSpeed = 0.0f;
		rSpinnerSpeed-=0.01f;
	}
	else{

	}
	if(key=='d') rSpinnerSpeed+=0.01f;
	if(key=='s') rSpinnerSpeed=0.0f;
	display();
}

// Main function
int main(int argc, char **argv)
{
	printf("Keyboard Controls: \n a : Slows down spinning \n s : Stops spinning \n d : Speeds up spinning \n");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutCreateWindow("Wind Spinner");
	glutDisplayFunc(display);
	glEnable(GL_DEPTH_TEST);
	glutReshapeFunc(myReshape);
	glClearColor(crgb(237),crgb(237),crgb(237),1.0);
	glutKeyboardFunc(keys);
	glutMainLoop();
}