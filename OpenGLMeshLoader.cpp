
#include "TextureBuilder.h"
#include "Model_3DS.h"
#include "GLTexture.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>


double valx = 1.0f;
double valy = 1.0f;
double valz = 1.0f;
bool s = true;
int WIDTH = 1280;
int HEIGHT = 720;
int counterStart = 0;
bool high = false;
bool first = false;
bool start = false;
int level = 1;
#define DEG2RAD(a) (a * 0.0174532925)
#define GLUT_KEY_ESCAPE 27
void pacman(double x, double z);
void ghost_blue(double x, double z);
void ghost_red(double x, double z);
void ghost_pink(double x, double z);
void ghost_orange(double x, double z);
void coin(double x, double z);
bool game_over = false;

GLuint tex;
char title[] = "3D Model Loader Sample";
int cameraZoom = 0;
double pacmanx = 6 * 3;
double pacmanz = 6 * 3;
double ghost_bluex = 0;
double ghost_bluey = 0;
double ghost_redx = -3 * 2;
double ghost_redy = -3;
double ghost_pinkx = -3 * 2;
double ghost_pinky = -3;
double ghost_orangex = 0;
double ghost_orangey = 0;
int ghost_red_counter = 0;
bool ghost_red_dir = false;
int ghost_blue_counter = 0;
bool ghost_blue_dir = false;
int ghost_pink_counter = 0;
bool ghost_pink_dir = false;
int ghost_orange_counter = 0;
bool ghost_orange_dir = false;
bool eaten = false;
bool trophy = false;

int rotpac = 180;
int pacMi = 14;
int pacMj = 14;

int gbMi = 8;
int gbMj = 8;

int grMi = 7;
int grMj = 7;

int goMi = 8;
int goMj = 7;

int gpMi = 7;
int gpMj = 8;

bool firstPerson = false;

//bool taken[10] = { false,false,false,false,false,false,false,false,false,false };
bool taken[2] = { false,false };
// 3D Projection Options
GLdouble fovy = 45.0;
GLdouble aspectRatio = (GLdouble)WIDTH / (GLdouble)HEIGHT;
GLdouble zNear = 0.1;
GLdouble zFar = 1000;
double rotatecoin = 0;
int score = 0;
int Map[16][16] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 5,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,3,3,0,0,0,0,0,4,1 },
{ 1,0,0,0,0,0,1,3,3,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1 },
{ 1,0,0,1,1,1,4,0,0,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,4,2,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

int Map2[16][16] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 5,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0 },
{ 0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,1,1,1,1,0,1,1,1,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1 },
{ 1,0,0,1,1,1,1,3,3,0,1,1,1,0,4,1 },
{ 1,0,0,1,1,1,1,3,3,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1 },
{ 1,0,0,1,1,1,4,0,0,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,4,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,4,2,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
};

class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f &v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f &v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = -1.264875f, float eyeY = 35.230526f, float eyeZ = 68.915672f, float centerX = -1.307430f, float centerY = 34.825375f, float centerZ = 68.002411f, float upX = 0.012106f, float upY = 0.913811f, float upZ = -0.405959f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
		//printf("eyex = %f eyey = %f eyez = %f", eye.x, eye.y, eye.z);
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {

		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}


};

Camera camera;

// Model Variables
Model_3DS model_pacman_high;
Model_3DS model_pacman_low;
Model_3DS model_ghost_blue;
Model_3DS model_ghost_red;
Model_3DS model_ghost_orange;
Model_3DS model_ghost_pink;
Model_3DS model_coin;
Model_3DS model_wall;
Model_3DS model_ground;
Model_3DS model_trophy;



//=======================================================================
// Lighting Configuration Function
//=======================================================================
void InitLightSource()
{
	// Enable Lighting for this OpenGL Program
	glEnable(GL_LIGHTING);

	// Enable Light Source number 0
	// OpengL has 8 light sources
	glEnable(GL_LIGHT0);

	// Define Light source 0 ambient light
	GLfloat ambient[] = { 0.1f, 0.1f, 0.1, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	// Define Light source 0 diffuse light
	GLfloat diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);

	// Define Light source 0 Specular light
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);

	// Finally, define light source 0 position in World Space
	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

//=======================================================================
// Material Configuration Function
//======================================================================
void InitMaterial()
{
	// Enable Material Tracking
	glEnable(GL_COLOR_MATERIAL);

	// Sich will be assigneet Material Properties whd by glColor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Set Material's Specular Color
	// Will be applied to all objects
	GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);

	// Set Material's Shine value (0->128)
	GLfloat shininess[] = { 96.0f };
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
}

void anime() {
	rotatecoin += 1;
	if (valx >= 0.5f) {
		valx -= 0.25;
	}
	else {
		valx = 1.0f;
	}

	if (valy >= 0.5f) {
		valy -= 0.1;
	}
	else {
		valy = 1.0f;
	}

	if (valz >= 0.5f) {
		valz -= 0.01;
	}
	else {
		valz = 1.0f;
	}
	glutPostRedisplay();
}

void timer(int x) {
	high = !high;
	counterStart++;
	//printf("%d", counterStart);
	if (counterStart == 4) {
		start = true;
		ghost_bluex = 3 * 2;
		ghost_bluey = 3;
		ghost_redx = -3 * 2 + 3 * -6;
		ghost_redy = -3 + 3 * -6;
		ghost_pinkx = 3 * 4;
		ghost_pinky = -3 * 7;
		ghost_orangex = 3;
		ghost_orangey = 3 * 2;

		Map[gbMi][gbMj] = 0;
		Map[grMi][grMj] = 0;
		Map[goMi][goMj] = 0;
		Map[gpMi][gpMj] = 0;

		gbMi = 9;
		gbMj = 10;

		grMi = 1;
		grMj = 1;

		gpMi = 1;
		gpMj = 14;

		goMi = 10;
		goMj = 8;

		Map[gbMi][gbMj] = 3;
		Map[grMi][grMj] = 3;
		Map[goMi][goMj] = 3;
		Map[gpMi][gpMj] = 3;

	}
	if (start) {
		//----------Ghost Red------------------
		if (!ghost_red_dir) {

			if (ghost_red_counter < 13) {
				if (grMi + 1 < 15) {
					if (Map[grMi + 1][grMj] == 0) {
						ghost_red_counter++;
						ghost_redy += 3;
						Map[grMi][grMj] = 0;
						Map[grMi + 1][grMj] = 3;
						grMi++;
					}
					else if (Map[grMi + 1][grMj] == 2) {
						ghost_red_counter++;
						ghost_redy += 3;
						Map[grMi][grMj] = 0;
						Map[grMi + 1][grMj] = 3;
						grMi++;
						game_over = true;
					}
				}
			}
			else {
				ghost_red_counter = 0;
				ghost_red_dir = !ghost_red_dir;
			}
		}
		else {
			if (ghost_red_counter < 13) {
				if (grMi - 1 > 0) {
					if (Map[grMi - 1][grMj] == 0) {
						ghost_red_counter++;
						ghost_redy -= 3;
						Map[grMi][grMj] = 0;
						Map[grMi - 1][grMj] = 3;
						grMi--;
					}
					else if (Map[grMi - 1][grMj] == 2) {
						ghost_red_counter++;
						ghost_redy -= 3;
						Map[grMi][grMj] = 0;
						Map[grMi - 1][grMj] = 3;
						grMi--;
						game_over = true;
					}
				}
			}
			else {
				ghost_red_counter = 0;
				ghost_red_dir = !ghost_red_dir;
			}

		}
		//----------Ghost Pink------------------
		if (!ghost_pink_dir) {

			if (ghost_pink_counter < 12) {
				if (gpMj - 1 > 0) {
					if (Map[gpMi][gpMj - 1] == 0) {
						ghost_pink_counter++;
						ghost_pinkx -= 3;
						Map[gpMi][gpMj] = 0;
						Map[gpMi][gpMj - 1] = 3;
						gpMj--;
					}
					else if (Map[gpMi][gpMj - 1] == 0) {
						ghost_pink_counter++;
						ghost_pinkx -= 3;
						Map[gpMi][gpMj] = 0;
						Map[gpMi][gpMj - 1] = 3;
						gpMj--;
						game_over = true;
					}
				}
			}
			else {
				ghost_pink_counter = 0;
				ghost_pink_dir = !ghost_pink_dir;
			}
		}
		else {
			if (ghost_pink_counter < 12) {
				if (gpMj + 1 < 15) {
					if (Map[gpMi][gpMj + 1] == 0) {
						ghost_pink_counter++;
						ghost_pinkx += 3;
						Map[gpMi][gpMj] = 0;
						Map[gpMi][gpMj + 1] = 3;
						gpMj++;
					}
					else if (Map[gpMi][gpMj + 1] == 2) {
						ghost_pink_counter++;
						ghost_pinkx += 3;
						Map[gpMi][gpMj] = 0;
						Map[gpMi][gpMj + 1] = 3;
						gpMj++;
						game_over = true;
					}
				}
			}
			else {
				ghost_pink_counter = 0;
				ghost_pink_dir = !ghost_pink_dir;
			}

		}
		//----------Ghost Blue------------------
		if (!ghost_blue_dir) {

			if (ghost_blue_counter < 4) {
				if (gbMj + 1 < 15) {
					if (Map[gbMi][gbMj + 1] == 0) {
						ghost_blue_counter++;
						ghost_bluex += 3;
						Map[gbMi][gbMj] = 0;
						Map[gbMi][gbMj + 1] = 3;
						gbMj++;
					}
					else if (Map[gbMi][gbMj + 1] == 2) {
						ghost_blue_counter++;
						ghost_bluex += 3;
						Map[gbMi][gbMj] = 0;
						Map[gbMi][gbMj + 1] = 3;
						gbMj++;
						game_over = true;
					}
				}
			}
			else {
				ghost_blue_counter = 0;
				ghost_blue_dir = !ghost_blue_dir;
			}
		}
		else {
			if (ghost_blue_counter < 4) {
				if (gbMj - 1 > 0) {
					if (Map[gbMi][gbMj - 1] == 0) {
						ghost_blue_counter++;
						ghost_bluex -= 3;
						Map[gbMi][gbMj] = 0;
						Map[gbMi][gbMj - 1] = 3;
						gbMj--;
					}
					else if (Map[gbMi][gbMj - 1] == 2) {

						ghost_blue_counter++;
						ghost_bluex -= 3;
						Map[gbMi][gbMj] = 0;
						Map[gbMi][gbMj - 1] = 3;
						gbMj--;
						game_over = true;
					}
				}
			}
			else {
				ghost_blue_counter = 0;
				ghost_blue_dir = !ghost_blue_dir;
			}

		}
		//----------Ghost Orange------------------
		if (!ghost_orange_dir) {

			if (ghost_orange_counter < 6) {
				if (goMj - 1 > 0) {
					if (Map[goMi][goMj - 1] == 0) {
						ghost_orange_counter++;
						ghost_orangex -= 3;
						Map[goMi][goMj] = 0;
						Map[goMi][goMj - 1] = 3;
						goMj--;
					}
					else if (Map[goMi][goMj - 1] == 0) {
						ghost_orange_counter++;
						ghost_orangex -= 3;
						Map[goMi][goMj] = 0;
						Map[goMi][goMj - 1] = 3;
						goMj--;
						game_over = true;
					}
				}
			}
			else {
				ghost_orange_counter = 0;
				ghost_orange_dir = !ghost_orange_dir;
			}
		}
		else {
			if (ghost_orange_counter < 6) {
				if (goMj + 1 < 15) {
					if (Map[goMi][goMj + 1] == 0) {
						ghost_orange_counter++;
						ghost_orangex += 3;
						Map[goMi][goMj] = 0;
						Map[goMi][goMj + 1] = 3;
						goMj++;
					}
					else if (Map[goMi][goMj + 1] == 2) {
						ghost_orange_counter++;
						ghost_orangex += 3;
						Map[goMi][goMj] = 0;
						Map[goMi][goMj + 1] = 3;
						goMj++;
						game_over = true;
					}
				}
			}
			else {
				ghost_orange_counter = 0;
				ghost_orange_dir = !ghost_orange_dir;
			}

		}
	}
	glutPostRedisplay();
	glutTimerFunc(500, timer, 0);
}

void print(int x, int y, char *string)
{
	int len, i;
	glRasterPos2f(x, y);
	len = (int)strlen(string);
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//=======================================================================
// OpengGL Configuration Function
//=======================================================================
void myInit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(fovy, aspectRatio, zNear, zFar);
	//*******************************************************************************************//
	// fovy:			Angle between the bottom and top of the projectors, in degrees.			 //
	// aspectRatio:		Ratio of width to height of the clipping plane.							 //
	// zNear and zFar:	Specify the front and back clipping planes distances from camera.		 //
	//*******************************************************************************************//

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	camera.look();
	//*******************************************************************************************//
	// EYE (ex, ey, ez): defines the location of the camera.									 //
	// AT (ax, ay, az):	 denotes the direction where the camera is aiming at.					 //
	// UP (ux, uy, uz):  denotes the upward orientation of the camera.							 //
	//*******************************************************************************************//

	InitLightSource();

	InitMaterial();

	glEnable(GL_DEPTH_TEST);

	glEnable(GL_NORMALIZE);
}

//=======================================================================
// Render Ground Function
//=======================================================================
void RenderGround()
{
	glDisable(GL_LIGHTING);	// Disable lighting 

	glColor3f(0.6, 0.6, 0.6);	// Dim the ground texture a bit

	glEnable(GL_TEXTURE_2D);	// Enable 2D texturing

								// Bind the ground texture

	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);	// Set quad normal direction.
	glTexCoord2f(0, 0);		// Set tex coordinates ( Using (0,0) -> (5,5) with texture wrapping set to GL_REPEAT to simulate the ground repeated grass texture).
	glVertex3f(-20, 0, -20);
	glTexCoord2f(5, 0);
	glVertex3f(20, 0, -20);
	glTexCoord2f(5, 5);
	glVertex3f(20, 0, 20);
	glTexCoord2f(0, 5);
	glVertex3f(-20, 0, 20);
	glEnd();
	glPopMatrix();

	glEnable(GL_LIGHTING);	// Enable lighting again for other entites coming throung the pipeline.

	glColor3f(1, 1, 1);	// Set material back to white instead of grey used for the ground texture.
}

//=======================================================================
// Display Function
//=======================================================================
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myInit();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	myInit();

	GLfloat lmodel_ambient[] = { valx, valy, valz, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

	GLfloat l0Diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat l0Spec[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat l0Ambient[] = { 0.1f, 0.0f, 0.0f, 1.0f };
	GLfloat l0Position[] = { 50.0f, 50.0f, 0.0f, s };
	GLfloat l0Direction[] = { 0, -1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0Diffuse);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0Ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, l0Position);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 30.0);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 90.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l0Direction);

	if (!game_over) {
		if (!trophy) {
			glPushMatrix();
			glRotated(90, 1.0, 0, 0);
			model_ground.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.6, 0.5, 1);
			glTranslated(-0.4, 6, 4);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.6, 0.5, 1);
			glTranslated(-0.4, 6, -4.3);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 0.3);
			glTranslated(-4.5, 6, -1);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(2.5, 0.5, 1);
			glTranslated(0, 6, 22.25);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(2.5, 0.5, 1);
			glTranslated(0, 6, -22.25);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 2.2);
			glTranslated(22.5, 6, 0);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 1.5);
			glTranslated(-22.5, 6, 5);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 1);
			glTranslated(-22.5, 6, -3);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 0.45);
			glTranslated(4.5, 6, 23);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 0.5);
			glTranslated(-4.5, 6, -22);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(10, 6, -10.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.45, 0.5, 1);
			glTranslated(-23, 6, 10.3);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();


			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(-20, 6, -10.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(21, 6, 7.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.8, 0.8, 0.8);
			glTranslated(-27, 5, -20);
			glRotated(90, 1, 0, 0);
			model_trophy.Draw();
			glPopMatrix();

			glPushMatrix();
			glRotated(90, 1.0, 0, 0);
			model_ground.Draw();
			glPopMatrix();


			pacman(pacmanx, pacmanz);
			ghost_blue(ghost_bluex, ghost_bluey);
			ghost_red(ghost_redx, ghost_redy);
			ghost_pink(ghost_pinkx, ghost_pinky);
			ghost_orange(ghost_orangex, ghost_orangey);
			int k = 0;
			if (Map[13][14] == 4) {
				coin(3 * 6, 3 * 5);
			}

			if (Map[14][13] == 4) {
				coin(3 * 5, 3 * 6);
			}

			if (Map[7][14] == 4) {
				coin(3 * 6, -3);
			}

			if (Map[11][6] == 4) {
				coin(3 * -2, 3 * 3);
			}

			if (Map[2][3] == 4) {
				coin(3 * -5, 3 * -6);
			}

			//--------Print Score----------
			// setup 2d projection
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0f, 1600, 800, 0.0f, -1.0f, 10.0f);

			// setup 2d modelview
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			// draw the 2d interface

			glColor3f(1.0f, 1.0f, 1.0f);
			char* info[20];
			char* info2[20];
			sprintf((char *)info, "Score: %d", score);
			sprintf((char *)info2, "Level: %d", level);
			print(100, 100, (char *)info);
			print(100, 300, (char *)info2);

			// revert to original modelview matrix
			glPopMatrix();
			// revert to original projection matrix
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();

		}
		else {
			glPushMatrix();
			glRotated(90, 1.0, 0, 0);
			model_ground.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.6, 0.5, 1);
			glTranslated(-0.4, 6, 4);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.6, 0.5, 1);
			glTranslated(-0.4, 6, -4.3);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 0.3);
			glTranslated(-4.5, 6, -1);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(2.5, 0.5, 1);
			glTranslated(0, 6, 22.25);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(2.5, 0.5, 1);
			glTranslated(0, 6, -22.25);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 2.2);
			glTranslated(22.5, 6, 0);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 1.5);
			glTranslated(-22.5, 6, 5);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 1);
			glTranslated(-22.5, 6, -3);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 0.45);
			glTranslated(4.5, 6, 23);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(1, 0.5, 0.5);
			glTranslated(-4.5, 6, -22);
			glRotated(90, 0, 1, 0);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(10, 6, -10.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.45, 0.5, 1);
			glTranslated(-23, 6, 10.3);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();


			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(-20, 6, -10.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(21, 6, 7.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(-21, 6, 1.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();


			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(-21, 6, -1.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.5, 0.5, 1);
			glTranslated(21, 6, -1.5);
			glRotated(90, 1, 0, 0);
			model_wall.Draw();
			glPopMatrix();

			glPushMatrix();
			glScaled(0.8, 0.8, 0.8);
			glTranslated(-27, 5, -20);
			glRotated(90, 1, 0, 0);
			model_trophy.Draw();
			glPopMatrix();

			glPushMatrix();
			glRotated(90, 1.0, 0, 0);
			model_ground.Draw();
			glPopMatrix();


			pacman(pacmanx, pacmanz);
			ghost_blue(ghost_bluex, ghost_bluey);
			ghost_red(ghost_redx, ghost_redy);
			ghost_pink(ghost_pinkx, ghost_pinky);
			ghost_orange(ghost_orangex, ghost_orangey);
			int k = 0;
			if (Map[13][14] == 4) {
				coin(3 * 6, 3 * 5);
			}

			if (Map[14][13] == 4) {
				coin(3 * 5, 3 * 6);
			}

			if (Map[7][14] == 4) {
				coin(3 * 6, -3);
			}

			if (Map[11][6] == 4) {
				coin(3 * -2, 3 * 3);
			}

			if (Map[2][3] == 4) {
				coin(3 * -5, 3 * -6);
			}

			//--------Print Score----------
			// setup 2d projection
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			glOrtho(0.0f, 1600, 800, 0.0f, -1.0f, 10.0f);

			// setup 2d modelview
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();

			// draw the 2d interface

			glColor3f(1.0f, 1.0f, 1.0f);
			char* info[20];
			char* info2[20];
			sprintf((char *)info, "Score: %d", score);
			sprintf((char *)info2, "Level: %d", level);
			print(100, 100, (char *)info);
			print(100, 300, (char *)info2);

			// revert to original modelview matrix
			glPopMatrix();
			// revert to original projection matrix
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
		}
	}
	else {
		// setup 2d projection
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glOrtho(0.0f, 1600, 800, 0.0f, -1.0f, 10.0f);

		// setup 2d modelview
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();

		// draw the 2d interface

		glColor3f(1.0f, 1.0f, 1.0f);
		char* info[20];
		sprintf((char *)info, "GAME OVER");
		print(700, 400, (char *)info);

		// revert to original modelview matrix
		glPopMatrix();
		// revert to original projection matrix
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();

	}

	glPushMatrix();

	GLUquadricObj * qobj;
	qobj = gluNewQuadric();
	glTranslated(50, 0, 0);
	glRotated(90, 1, 0, 1);
	glBindTexture(GL_TEXTURE_2D, tex);
	gluQuadricTexture(qobj, true);
	gluQuadricNormals(qobj, GL_SMOOTH);
	gluSphere(qobj, 100, 100, 100);
	gluDeleteQuadric(qobj);


	glPopMatrix();

	glutSwapBuffers();
}


void checkAndRot(int b, int a, int d) {
	switch (b) {
	case 180:
		if (a == -90) { //works
			camera.rotateY(90);
			camera.moveX(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
		}
		else if (a == 90) {
			camera.rotateY(-90);
			camera.moveX(-d);
			camera.moveZ(5 * d);

		}
		else if (a == 180) { // works 
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
		}
		else if (a == 0) { //works
			camera.rotateY(180);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);

		}
		break;

	case 0:
		if (a == 90) { //works
			camera.rotateY(90);
			camera.moveX(2 * d);
			camera.moveZ(5 * d);

		}
		else if (a == -90) { // works
			camera.rotateY(-90);
			camera.moveX(-2 * d);
			camera.moveZ(6 * d);
		}
		else if (a == 0) { //works
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
		}
		else if (a == 180) {  //works
			camera.rotateY(180);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);

		}
		break;

	case -90:
		if (a == 0) { //works
			camera.rotateY(90);
			camera.moveX(2 * d);
			camera.moveZ(5 * d);
		}
		else if (a == 180) {  //works
			camera.rotateY(-90);
			camera.moveX(-2 * d);
			camera.moveZ(4 * d);
		}
		else if (a == -90) { //works
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
		}
		else if (a == 90) {  //works
			camera.rotateY(180);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);

		}
		break;

	case 90:
		if (a == 180) { //works
			camera.rotateY(90);
			camera.moveX(2 * d);
			camera.moveZ(4 * d);
		}
		else if (a == 0) {  //works
			camera.rotateY(-90);
			camera.moveX(-2 * d);
			camera.moveZ(5 * d);
		}
		else if (a == 90) { //works
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
		}
		else if (a == -90) {  //works
			camera.rotateY(180);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);
			camera.moveZ(d);

		}
		break;
	}
}


//=======================================================================
// Keyboard Function
//=======================================================================
void myKeyboard(unsigned char button, int x, int y)
{
	float d = 1;
	switch (button)
	{
	case 't':
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		break;
	case 'r':
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;
	case 'w':
		camera.moveY(d);
		break;

	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;

	case 'y':
		printf("eye.x= %f ; eye.y= %f; eye.z= %f; center.x= %f ; center.y= %f; center.z= %f; up.x= %f ; up.y= %f; up.z= %f;"
			, camera.eye.x, camera.eye.y, camera.eye.z, camera.center.x, camera.center.y, camera.center.z, camera.up.x, camera.up.y, camera.up.z);
		break;


	case '1':


		camera.eye.x = 0.421472;
		camera.eye.y = 1.959137;
		camera.eye.z = 0.614647;

		camera.center.x = 0.471493;
		camera.center.y = 0.966458;
		camera.center.z = 0.504704;

		camera.up.x = -0.040009;
		camera.up.y = 0.108001;
		camera.up.z = -0.993346;
		break;
	case '2':


		camera.eye.x = 1.505262;
		camera.eye.y = 1.935594;
		camera.eye.z = 0.492203;

		camera.center.x = 1.482961;
		camera.center.y = 0.935847;
		camera.center.z = 0.494791;

		camera.up.x = 0.004352;
		camera.up.y = -0.002686;
		camera.up.z = -0.999987;
		break;

	case '3':
		camera.eye.x = -0.969803;
		camera.eye.y = 0.605619;
		camera.eye.z = 0.460467;

		camera.center.x = 0.024999;
		camera.center.y = 0.507486;
		camera.center.z = 0.487671;

		camera.up.x = 0.098839;
		camera.up.y = 0.994765;
		camera.up.z = -0.025969;
		break;
	case '4':
		camera.eye.x = 3.008220;
		camera.eye.y = 0.688090;
		camera.eye.z = 0.474046;

		camera.center.x = 2.015584;
		camera.center.y = 0.568918;
		camera.center.z = 0.495739;

		camera.up.x = -0.119189;
		camera.up.y = 0.992871;
		camera.up.z = 0.000509;
		break;
	case 'b':
		firstPerson = false;
		camera.eye.x = -1.539898;
		camera.eye.y = 69.700180;
		camera.eye.z = 2.666390;
		camera.center.x = -1.568853;
		camera.center.y = 68.700760;
		camera.center.z = 2.648357;
		camera.up.x = -0.033451;
		camera.up.y = 0.018999;
		camera.up.z = -0.999260;
		break;

	case 'n':
		firstPerson = true;
		camera.eye = Vector3f(20.244595, 4.062043, 17.911158);
		camera.center = Vector3f(20.175312, 4.047151, 16.913671);
		camera.up = Vector3f(0.027770, 0.999472, -0.016850);
		printf("\nPac location: %d, %d\n", pacMi, pacMj);
		if (pacMi != 14 || pacMj != 14) {
			for (int i = 0; i < (14 - pacMi); i++) {
				printf("entered once\n");
				checkAndRot(180, 180, d);
			}
			for (int j = 0; j < (14 - pacMj); j++) {
				if (j == 0) checkAndRot(180, -90, d);
				else {
					checkAndRot(-90, -90, d);
				}
			}
			if (rotpac == 180) {
				camera.rotateY(-90);
				camera.moveX(-4 * d);
				camera.moveZ(2 * d);
			}
			else if (rotpac == 0) {
				camera.rotateY(90);
				camera.moveX(5 * d);
				camera.moveZ(2 * d);
			}
			else if (rotpac == 90) {
				camera.rotateY(180);
				//camera.moveX(5 * d);
				camera.moveZ(5 * d);
			}
		}

		break;

	case 'i':
		if (pacMi - 1 > 0) {
			if (!(Map[pacMi - 1][pacMj] == 1)) {
				if (Map[pacMi - 1][pacMj] == 4) {
					Map[pacMi - 1][pacMj] = 0;
					score++;
					printf("score: %d", score);
				}
				else {
					if (pacMi - 1 == 2 && pacMj == 1) {
						if (level == 2) {
							game_over = true;
						}
						trophy = true;
						level = 2;
						memcpy(Map, Map2, sizeof(Map));
						score = 0;
						pacmanx = 18;
						pacmanz = 18;
						pacMi = 14;
						pacMj = 14;


						ghost_bluex = 0;
						ghost_bluey = 0;
						ghost_redx = -3 * 2;
						ghost_redy = -3;
						ghost_pinkx = -3 * 2;
						ghost_pinky = -3;
						ghost_orangex = 0;
						ghost_orangey = 0;
						ghost_red_counter = 0;
						ghost_red_dir = false;
						ghost_blue_counter = 0;
						ghost_blue_dir = false;
						ghost_pink_counter = 0;
						ghost_pink_dir = false;
						ghost_orange_counter = 0;
						ghost_orange_dir = false;
						pacMi = 14;
						pacMj = 14;
						gbMi = 8;
						gbMj = 8;
						grMi = 7;
						grMj = 7;
						goMi = 8;
						goMj = 7;
						gpMi = 7;
						gpMj = 8;
						start = false;
						counterStart = 0;

					}
				}
				if (firstPerson) {
					checkAndRot(rotpac, 180, d);
				}
				pacmanz -= 3;
				rotpac = 180;
				Map[pacMi][pacMj] = 0;
				pacMi = pacMi - 1;
				Map[pacMi][pacMj] = 2;
			}
		}
		break;
	case 'k':
		if (pacMi + 1 < 15) {
			if (!(Map[pacMi + 1][pacMj] == 1)) {
				if (Map[pacMi + 1][pacMj] == 4) {
					Map[pacMi + 1][pacMj] = 0;
					score++;
					printf("score: %d", score);
				}
				else {
					if (pacMi + 1 == 2 && pacMj == 1) {
						if (level == 2) {
							game_over = true;
						}
						level = 2;
						trophy = true;
						memcpy(Map, Map2, sizeof(Map));
						score = 0;
						pacmanx = 18;
						pacmanz = 18;
						pacMi = 14;
						pacMj = 14;


						ghost_bluex = 0;
						ghost_bluey = 0;
						ghost_redx = -3 * 2;
						ghost_redy = -3;
						ghost_pinkx = -3 * 2;
						ghost_pinky = -3;
						ghost_orangex = 0;
						ghost_orangey = 0;
						ghost_red_counter = 0;
						ghost_red_dir = false;
						ghost_blue_counter = 0;
						ghost_blue_dir = false;
						ghost_pink_counter = 0;
						ghost_pink_dir = false;
						ghost_orange_counter = 0;
						ghost_orange_dir = false;
						pacMi = 14;
						pacMj = 14;
						gbMi = 8;
						gbMj = 8;
						grMi = 7;
						grMj = 7;
						goMi = 8;
						goMj = 7;
						gpMi = 7;
						gpMj = 8;
						start = false;
						counterStart = 0;
					}
				}
				if (firstPerson) {
					checkAndRot(rotpac, 0, d);
				}
				pacmanz += 3;
				rotpac = 0;
				Map[pacMi][pacMj] = 0;
				pacMi = pacMi + 1;
				Map[pacMi][pacMj] = 2;
			}
		}
		break;
	case 'l':
		if (pacMj + 1 < 15) {
			if (!(Map[pacMi][pacMj + 1] == 1)) {
				if (Map[pacMi][pacMj + 1] == 4) {
					Map[pacMi][pacMj + 1] = 0;
					score++;
					printf("score: %d", score);
				}
				else {
					if (pacMi == 2 && pacMj + 1 == 1) {
						trophy = true;
						memcpy(Map, Map2, sizeof(Map));
						score = 0;
						pacmanx = 18;
						pacmanz = 18;
						pacMi = 14;
						pacMj = 14;
						if (level == 2) {
							game_over = true;
						}
						level = 2;
						ghost_bluex = 0;
						ghost_bluey = 0;
						ghost_redx = -3 * 2;
						ghost_redy = -3;
						ghost_pinkx = -3 * 2;
						ghost_pinky = -3;
						ghost_orangex = 0;
						ghost_orangey = 0;
						ghost_red_counter = 0;
						ghost_red_dir = false;
						ghost_blue_counter = 0;
						ghost_blue_dir = false;
						ghost_pink_counter = 0;
						ghost_pink_dir = false;
						ghost_orange_counter = 0;
						ghost_orange_dir = false;
						pacMi = 14;
						pacMj = 14;
						gbMi = 8;
						gbMj = 8;
						grMi = 7;
						grMj = 7;
						goMi = 8;
						goMj = 7;
						gpMi = 7;
						gpMj = 8;
						start = false;
						counterStart = 0;
					}
				}
				if (firstPerson) {
					checkAndRot(rotpac, 90, d);
				}
				pacmanx += 3;
				rotpac = 90;
				Map[pacMi][pacMj] = 0;
				pacMj = pacMj + 1;
				Map[pacMi][pacMj] = 2;

			}
		}
		break;
	case 'j':
		if (pacMj - 1 > 0) {
			if (!(Map[pacMi][pacMj - 1] == 1)) {
				if (Map[pacMi][pacMj - 1] == 4) {
					Map[pacMi][pacMj - 1] = 0;
					score++;
					printf("score: %d", score);
				}
				else {
					if (pacMi == 2 && pacMj - 1 == 1) {
						trophy = true;
						memcpy(Map, Map2, sizeof(Map));
						score = 0;
						pacmanx = 18;
						pacmanz = 18;
						pacMi = 14;
						pacMj = 14;
						if (level == 2) {
							game_over = true;
						}
						level = 2;
						ghost_bluex = 0;
						ghost_bluey = 0;
						ghost_redx = -3 * 2;
						ghost_redy = -3;
						ghost_pinkx = -3 * 2;
						ghost_pinky = -3;
						ghost_orangex = 0;
						ghost_orangey = 0;
						ghost_red_counter = 0;
						ghost_red_dir = false;
						ghost_blue_counter = 0;
						ghost_blue_dir = false;
						ghost_pink_counter = 0;
						ghost_pink_dir = false;
						ghost_orange_counter = 0;
						ghost_orange_dir = false;
						pacMi = 14;
						pacMj = 14;
						gbMi = 8;
						gbMj = 8;
						grMi = 7;
						grMj = 7;
						goMi = 8;
						goMj = 7;
						gpMi = 7;
						gpMj = 8;
						start = false;
						counterStart = 0;
					}
				}
				if (firstPerson) {
					checkAndRot(rotpac, -90, d);
				}
				pacmanx -= 3;
				rotpac = -90;
				Map[pacMi][pacMj] = 0;
				pacMj = pacMj - 1;
				Map[pacMi][pacMj] = 2;
			}
		}
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}


	glutPostRedisplay();
}

//=======================================================================
// Motion Function
//=======================================================================
void myMotion(int x, int y)
{
	y = HEIGHT - y;

	if (cameraZoom - y > 0)
	{
		camera.eye.x += -0.1;
		camera.eye.z += -0.1;
	}
	else
	{
		camera.eye.x += 0.1;
		camera.eye.z += 0.1;
	}

	cameraZoom = y;

	glLoadIdentity();	//Clear Model_View Matrix

	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
		camera.center.x, camera.center.y, camera.center.z,
		camera.up.x, camera.up.y, camera.up.z);	//Setup Camera with modified paramters

	GLfloat light_position[] = { 0.0f, 10.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glutPostRedisplay();	//Re-draw scene 
}

//=======================================================================
// Mouse Function
//=======================================================================
void myMouse(int button, int state, int x, int y)
{
	y = HEIGHT - y;

	if (state == GLUT_DOWN)
	{
		cameraZoom = y;
	}
}

void coin(double x, double z) {
	glPushMatrix();
	glTranslated(x, 1, z);
	glPushMatrix();
	glTranslated(1.4, 2.8, 1.2);
	glScaled(3, 3, 3);
	glRotated(rotatecoin, 0, 1, 0);
	glRotated(90, 1, 0, 0);
	model_coin.Draw();
	glPopMatrix();
	glPopMatrix();
}

void pacman(double x, double z) {
	if (high) {
		glPushMatrix();
		glTranslated(x, 0, z);

		glPushMatrix();
		glTranslated(1.4, 2.8, 1.2);
		glScaled(3, 3, 3);
		glRotated(rotpac, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		model_pacman_high.Draw();
		glPopMatrix();

		glPopMatrix();
	}
	else {
		glPushMatrix();
		glTranslated(x, 0, z);

		glPushMatrix();
		glTranslated(1.4, 2.8, 1.2);
		glScaled(3, 3, 3);
		glRotated(rotpac, 0, 1, 0);
		glRotated(90, 1, 0, 0);
		model_pacman_low.Draw();
		glPopMatrix();

		glPopMatrix();
	}

}
void ghost_blue(double x, double z) {

	glPushMatrix();
	glTranslated(x, 0, z);

	glPushMatrix();
	glTranslated(1.4, 2.8, 1.2);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	model_ghost_blue.Draw();
	glPopMatrix();

	glPopMatrix();

}

void ghost_red(double x, double z) {

	glPushMatrix();
	glTranslated(x, 0, z);

	glPushMatrix();
	glTranslated(1.4 + 3, 2.8, 1.2);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	model_ghost_red.Draw();
	glPopMatrix();

	glPopMatrix();

}

void ghost_pink(double x, double z) {

	glPushMatrix();
	glTranslated(x, 0, z);

	glPushMatrix();
	glTranslated(1.4 + 3 + 3, 2.8, 1.2);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	model_ghost_pink.Draw();
	glPopMatrix();

	glPopMatrix();

}

void ghost_orange(double x, double z) {

	glPushMatrix();
	glTranslated(x, 0, z);

	glPushMatrix();
	glTranslated(1.4 - 3, 2.8, 1.2);
	glScaled(0.3, 0.3, 0.3);
	glRotated(90, 1, 0, 0);
	model_ghost_orange.Draw();
	glPopMatrix();

	glPopMatrix();

}
void Mouse(int x, int y) {

	// Getting the angle between the  mouse and the Hero 



	//	printf("%f ", HeroRot);
	glutPostRedisplay();
}

//=======================================================================
// Reshape Function
//=======================================================================
void myReshape(int w, int h)
{
	if (h == 0) {
		h = 1;
	}

	WIDTH = w;
	HEIGHT = h;

	// set the drawable region of the window
	glViewport(0, 0, w, h);

	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, (GLdouble)WIDTH / (GLdouble)HEIGHT, zNear, zFar);

	// go back to modelview matrix so we can move the objects about
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera.eye.x, camera.eye.y, camera.eye.z,
		camera.center.x, camera.center.y, camera.center.z,
		camera.up.x, camera.up.y, camera.up.z);
}

//=======================================================================
// Assets Loading Function
//=======================================================================
void LoadAssets()
{
	// Loading Model files
	model_pacman_high.Load("models/Pacman/Pac-Man/PacmanHigh.3ds");
	model_pacman_low.Load("models/Pacman/Pac-Man/PacmanLow.3ds");
	model_coin.Load("models/Coins/coin/Ring/Ring.3ds");
	model_ground.Load("models/Ground/Ground/No-Man's Land (Alt.3ds");
	model_wall.Load("models/Wall/Wall.3ds");
	model_ghost_blue.Load("models/Ghosts/Maze Ghosts/Ghost Blue/MazeGhostBlue.3ds");
	model_ghost_orange.Load("models/Ghosts/Maze Ghosts/Ghost Orange/MazeGhostOrange.3ds");
	model_ghost_pink.Load("models/Ghosts/Maze Ghosts/Ghost Pink/MazeGhostPink.3ds");
	model_ghost_red.Load("models/Ghosts/Maze Ghosts/Ghost Red/MazeGhostRed.3ds");
	model_trophy.Load("models/Trophy/Pac-Man Cup Trophy/pactrophy.3ds");
	loadBMP(&tex, "Textures/ground.bmp", true);
}

//=======================================================================
// Main Function
//=======================================================================
void main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(WIDTH, HEIGHT);

	glutInitWindowPosition(100, 150);

	glutCreateWindow(title);


	glutDisplayFunc(myDisplay);

	glutIdleFunc(anime);

	glutKeyboardFunc(myKeyboard);

	glutMotionFunc(myMotion);

	glutSpecialFunc(Special);

	glutPassiveMotionFunc(Mouse);

	glutMouseFunc(myMouse);
	glutTimerFunc(500, timer, 0);

	glutReshapeFunc(myReshape);

	myInit();

	LoadAssets();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}