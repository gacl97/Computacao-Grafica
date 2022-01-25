#include <iostream>
#include <SOIL/SOIL.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <math.h>

using namespace std;

// Compilar
// g++ main.cpp -o a -Wall -lglfw -lm -lGL -lGLU -lSOIL

#define WINDOW_WIDTH 1300
#define WINDOW_HEIGHT 800

/* Posição da luz (x, y, z, intensidade)*/
GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };

void resize(int width, int height) {

  glViewport(0, 0, width, height);

  float aspect = float(width)/float(height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(100.0, aspect, 0.1, 500.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(-1.0, 0.0, -5.0);
}

// Função para carregar o arquivo de textura
GLuint loadTexture(const char* texture_file) {
  GLuint texture = SOIL_load_OGL_texture(texture_file, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

  if (!texture) {
    printf("Erro ao carregar imagem\n");
  }

  return texture;
}

GLUquadricObj * initPlanetObject(GLUquadricObj *planet_object) {
  planet_object = gluNewQuadric();
  gluQuadricDrawStyle(planet_object, GLU_FILL);
  gluQuadricTexture(planet_object, GL_TRUE);
  gluQuadricNormals(planet_object, GLU_SMOOTH);

  return planet_object;
}

void createObject(GLUquadricObj *obj, float obj_size, float obj_X, float obj_Y, float obj_rotate, const char* img_directory) {

	glPushMatrix();
		glTranslatef(obj_X, 0, obj_Y);
		glRotatef(obj_rotate, 0, 1, 0);
		glRotatef(-90, 1, 0, 0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, loadTexture(img_directory));
		gluSphere(obj, obj_size, 40, 40);
	glPopMatrix();
}

void rotateAndTranslatePlanet(float *obj_angle, float *obj_velocity, float *obj_radius, float *obj_X, float *obj_Y, float *obj_rotate, float rotation_value) {
  *obj_angle -= *obj_velocity/10000;

  // Translação em volta do sol
	*obj_X = *obj_radius * cos(*obj_angle);
	*obj_Y = *obj_radius * sin(*obj_angle);
  printf("--> %f, %f\n", *obj_X, *obj_Y);
	
	// Velocidade de rotação do planeta
	*obj_rotate += rotation_value;
}
//======================================================================================================================
float sun_size = 1.4;
float sun_rotate = 0.0;
float sun_X = 0.0;
float sun_Y = 0.0;

void rotateSun() {
	sun_rotate += 2.0;
}

//======================================================================================================================
float mercury_size = 0.5;
float mercury_radius = 5;
float mercury_velocity = 1000;

float mercury_angle = 0.0;
float mercury_rotate = 14.0;
float mercury_X = 2.0;
float mercury_Y = -0.1;
//======================================================================================================================
float uranus_size = 0.5;
float uranus_radius = 6;
float uranus_velocity = 70;

float uranus_angle = 0.0;
float uranus_rotate = 0.0;
float uranus_X =  3.0;
float uranus_Y = -0.4;
//======================================================================================================================
float venus_size = 0.5;
float venus_radius = 7;
float venus_velocity = 300;

float venus_angle = 0.0;
float venus_rotate = 0.0;
float venus_X = 12.0;
float venus_Y = -0.08;
//======================================================================================================================
float earth_size = 0.5;
float earth_radius = 8;
float earth_velocity = 200;

float earth_angle = 0.0;
float earth_rotate = 0.0;
float earth_X = 5.0;
float earth_Y = -0.31;
//======================================================================================================================
float mars_size = 0.3;
float mars_radius = 9;
float mars_velocity = 170;

float mars_angle = 0.0;
float mars_rotate = 0.0;
float mars_X = 7.0;
float mars_Y = -0.30;
//======================================================================================================================

void creatAllPlanets() {

	glTranslatef(0.0, 0.0, -9.0);
	glColor3f(1.0, 1.0, 1.0);

  GLUquadricObj *obj_sun = NULL;
  obj_sun = initPlanetObject(obj_sun);

  GLUquadricObj *obj_mercury = NULL;
  obj_mercury = initPlanetObject(obj_mercury);

  GLUquadricObj *obj_uranus = NULL;
  obj_uranus = initPlanetObject(obj_uranus);

  GLUquadricObj *obj_venus = NULL;
  obj_venus = initPlanetObject(obj_venus);

  GLUquadricObj *obj_earth = NULL;
  obj_earth = initPlanetObject(obj_earth);

  GLUquadricObj *obj_mars = NULL;
  obj_mars = initPlanetObject(obj_mars);

	createObject(obj_sun, sun_size, sun_X, sun_Y, sun_rotate, "img/sol.png");
	createObject(obj_mercury, mercury_size, mercury_X, mercury_Y, mercury_rotate, "img/mercurio.png");
	createObject(obj_uranus, uranus_size, uranus_X, uranus_Y, uranus_rotate, "img/urano.png");
	createObject(obj_venus, venus_size, venus_X, venus_Y, venus_rotate, "img/venus.png");
	createObject(obj_earth, earth_size, earth_X, earth_Y, earth_rotate, "img/terra.png");
	createObject(obj_mars, mars_size, mars_X, mars_Y, mars_rotate, "img/marte.png");
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
    0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, // centro
	  0.0, 1.0, 0.0
  );

	glRotatef(0.0, 1.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 1.0, 0.0);

  // Profundidade
  glEnable(GL_DEPTH_TEST);
	creatAllPlanets();
}

void controlRotation(GLFWwindow *window, int key, int scanCode, int action, int mod){

  cout << "Key: " << key << endl;

  // Tecla correspondete ao Y
  if(key == 89) {
    cout << "Movimentando planetas" << endl;
    rotateSun();
    rotateAndTranslatePlanet(&mercury_angle, &mercury_velocity, &mercury_radius, &mercury_X, &mercury_Y, &mercury_rotate, 14.0);
    rotateAndTranslatePlanet(&venus_angle, &venus_velocity, &venus_radius, &venus_X, &venus_Y, &venus_rotate, 5.0);
    rotateAndTranslatePlanet(&uranus_angle, &uranus_velocity, &uranus_radius, &uranus_X, &uranus_Y, &uranus_rotate, 4.0);
    rotateAndTranslatePlanet(&earth_angle, &earth_velocity, &earth_radius, &earth_X, &earth_Y, &earth_rotate, 20.0);
    rotateAndTranslatePlanet(&mars_angle, &mars_velocity, &mars_radius, &mars_X, &mars_Y, &mars_rotate, 10.0);

    /* Define os parâmetros da Luz, utilizando a luz difusa */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0);
    // ativação da iluminação
    glEnable(GL_LIGHTING);
  }
}

int main(int argc, char *argv[]) {
  
  GLFWwindow* window;

  if(!glfwInit()) {
    return -1;
  }

  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sistema solar", NULL, NULL);

  if(!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glClearColor(0.0,0,0,0);

  while(!glfwWindowShouldClose(window)) {    

    glfwPollEvents();

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }  

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    int largura, altura;
		glfwGetFramebufferSize(window, &largura, &altura);

    display();
    resize(largura, altura);
    glfwSetKeyCallback(window, controlRotation);
    
    glfwSwapBuffers(window);
  }

  glfwTerminate();
  return 0;
}