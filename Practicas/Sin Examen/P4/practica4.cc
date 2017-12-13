//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013-2016
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "objetos.h"
#include <file_ply_stl.h>

// tamaño de los ejes
const int AXIS_SIZE=5000;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,
				Window_height,
				Front_plane,
				Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int UI_window_pos_x=50,
		UI_window_pos_y=50,
		UI_window_width=500,
		UI_window_height=500;


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

int accion=1;
bool jerarquico=false;
float anguloTronco = 0, v_tronco = 5;
float anguloEnganche = 23, v_enganche = 2;
float tamCable = 1.5, v_cable = 0.3;
_objeto_ply esfera;

_cubo cubo(3);
_piramide piramide(2,1.5);
_tetraedro tetraedro(3,3.5);

_objeto_ply ply;

GLuint textura_id;
float altura=5.0, anchura=1.001;
_tablero tablero(5,1);

bool ilu=false, tex=false;
int som=1;

_triangulos3D *figura_puntero;

void dibuja (void){
	GLfloat vertices[] = {-altura, -altura , anchura,
	                      altura , -altura , anchura,
	                      altura, altura, anchura,
	                      -altura, altura, anchura};

	GLfloat texVertices[] = {0.0,1.0,
	    1.0,1.0,
	    1.0,0.0,
	    0.0,0.0};

	  glEnable(GL_TEXTURE_2D);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	  glActiveTexture(GL_TEXTURE0);
	  glBindTexture(GL_TEXTURE_2D, textura_id);

	  glVertexPointer(3, GL_FLOAT, 0, vertices);
	  glTexCoordPointer(2, GL_FLOAT, 0, texVertices);

	  glDrawArrays(GL_QUADS, 0, 4);

	  glDisableClientState(GL_VERTEX_ARRAY);
	  glBindTexture(GL_TEXTURE_2D, 0);
	  glDisable(GL_TEXTURE_2D);

}


//**************************************************************************
//
//***************************************************************************

void clear_window(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
	//  Front_plane>0  Back_plane>PlanoDelantero)
	glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer(){
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	glBegin(GL_LINES);
		// eje X, color rojo
		glColor3f(1,0,0);
		glVertex3f(-AXIS_SIZE,0,0);
		glVertex3f(AXIS_SIZE,0,0);
		// eje Y, color verde
		glColor3f(0,1,0);
		glVertex3f(0,-AXIS_SIZE,0);
		glVertex3f(0,AXIS_SIZE,0);
		// eje Z, color azul
		glColor3f(0,0,1);
		glVertex3f(0,0,-AXIS_SIZE);
		glVertex3f(0,0,AXIS_SIZE);
	glEnd();
}

void dibujaMaza(float tamCable) {
	glPushMatrix();
		glScalef(1,1,1);
		glTranslatef(0,-9.0*tamCable,-1.0);
		ply.dibujar(accion);
	glPopMatrix();
}

void dibujaCable(float tamCable){

	glPushMatrix();
		glScalef(0.1, tamCable, 0.1);
		glTranslatef(0.0,-3.0,0.0);
		cubo.dibujar(accion);
	glPopMatrix();

	dibujaMaza(tamCable);
}

void dibujarSoporte(float anguloE, float tamCable){

	glPushMatrix();
		glScalef(0.3,0.3,0.3);
		glTranslatef(0,66.6,anguloE);
		cubo.dibujar(accion);
		dibujaCable(tamCable);
	glPopMatrix();

}

void objetoJerarquico(float anguloT, float anguloE, float tamCable, int accion){
	// Base
	glPushMatrix();
		glScalef(1.5,0.2,1.5);
		cubo.dibujar(accion);
	glPopMatrix();

	glPushMatrix();
		glRotatef(anguloT,0.0,1.0,0);

		// Tronco
		glPushMatrix();
			glScalef(0.3,3.0,0.3);
			glTranslatef(0,3.2,0);
			cubo.dibujar(accion);
		glPopMatrix();

		// Cabina
		glPushMatrix();
			glScalef(0.7,0.7,0.7);
			glTranslatef(0.0,29.6,0.0);
			cubo.dibujar(accion);
		glPopMatrix();

		//TechoCabinamake
		glPushMatrix();
			glScalef(1.0,1.0,1.0);
			glTranslatef(0.0,24.3,0.0);
			piramide.dibujar(accion);
		glPopMatrix();

		//brazo
		glPushMatrix();
			glScalef(0.25,0.25,3.5);
			glTranslatef(0,80.0,3.6);
			cubo.dibujar(accion);
		glPopMatrix();

		//Cola
		glPushMatrix();
			glScalef(0.25,0.10,0.6);
			glTranslatef(0,200.0,-6.5);
			cubo.dibujar(accion);
		glPopMatrix();

		//Contrapeso
		glPushMatrix();
			glScalef(0.4,0.5,0.4);
			glTranslatef(0,39.0,-17.3);
			cubo.dibujar(accion);
		glPopMatrix();

		dibujarSoporte(anguloE,tamCable);

	glPopMatrix();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){
	if (!jerarquico){
		if(tex) dibuja();
		figura_puntero->dibujar(accion);
	}else
		objetoJerarquico(anguloTronco, anguloEnganche, tamCable, accion);


}


void luces() {
	if(ilu){			//NOTE Modificar posicion según teclas
		GLfloat posicion[4] 	= {0.0, 5.0, 10.0, 1.0},
		        ambiente[4] 	= {0.2,0.2,0.2,1.0},
						intensidad[4] = {1.0,1.0,1.0,1.0};

		glLightfv(GL_LIGHT2, GL_POSITION, posicion);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambiente);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, intensidad);
		glLightfv(GL_LIGHT2, GL_SPECULAR, intensidad);
	}
}

void draw_scene(void){
	clear_window();
	change_observer();
	luces();
	draw_axis();
	draw_objects();
	glutSwapBuffers();
}

//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1){
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y){
	if (toupper(Tecla1)=='Q') exit(0);

	if(toupper(Tecla1) != 'Z' && toupper(Tecla1) != 'C' && toupper(Tecla1) != 'X'){
		switch (toupper(Tecla1)) {
			case 'P': accion=1; 																				break;
			case 'L': accion=2;																					break;
			case 'F': accion=3; 																				break;
			case 'W': accion=4; 																				break;
			case 'A': accion=5;																					break;
			case 'I': if(ilu) ilu=false; else ilu=true;									break;
			case 'T': if(tex) tex=false; else tex=true;									break;
			case 'S': if(som%2) accion=6; else accion=7; som++;					break;

			case '1':	figura_puntero = &tetraedro;	jerarquico = false;	break;
			case '2':	figura_puntero = &cubo;				jerarquico = false;	break;
			case '3':	figura_puntero = &piramide;		jerarquico = false;	break;
			case '4': figura_puntero = &ply;				jerarquico = false;	break;
			case '5': jerarquico = true;																break;
			case '6': figura_puntero = &tablero;		jerarquico=false;	 break;
		}
	}else{
		switch (Tecla1) {
			case 'z':	anguloTronco-=v_tronco;			break;
			case 'Z':	anguloTronco+=v_tronco;			break;
			case 'x':	anguloEnganche-=v_enganche;	break;
			case 'X':	anguloEnganche+=v_enganche;	break;
			case 'c':	tamCable-=v_cable;					break;
			case 'C':	tamCable+=v_cable;					break;
		}

		if (anguloEnganche > 65) anguloEnganche = 65;
		if (anguloEnganche < 23) anguloEnganche = 23;
		if (tamCable < 1.5) tamCable = 1.5;
		if (tamCable > 10) tamCable = 10;
	}

	cout << "ilu: " << ilu << endl;
	cout << "tex: " << tex << endl;

	glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void special_keys(int Tecla1,int x,int y){
	switch (Tecla1){
		case GLUT_KEY_LEFT:Observer_angle_y--;					break;
		case GLUT_KEY_RIGHT:Observer_angle_y++;					break;
		case GLUT_KEY_UP:Observer_angle_x--;						break;
		case GLUT_KEY_DOWN:Observer_angle_x++;					break;
		case GLUT_KEY_PAGE_UP:Observer_distance*=1.4;		break;
		case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.4;	break;
	}

	glutPostRedisplay();
}

//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void){
	// se inicalizan la ventana y los planos de corte
	Window_width=5;
	Window_height=5;
	Front_plane=10;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=2*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(1,1,1,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	//
	change_projection();
	//
	glViewport(0,0,UI_window_width,UI_window_height);
}

void initTexture(){
  std::vector<unsigned char> data;

  cimg_library::CImg<unsigned char> img;
	img.load("graffiti.jpg");
	// img.load("logo.jpg");

  // Extraer los datos
  for (long y = 0; y < img.height(); y ++)
     for (long x = 0; x < img.width(); x ++){
        unsigned char *r = img.data(x, y, 0, 0);
        unsigned char *g = img.data(x, y, 0, 1);
        unsigned char *b = img.data(x, y, 0, 2);
        data.push_back(*r);
        data.push_back(*g);
        data.push_back(*b);
     }

  // Se crea la textura
  glGenTextures(1, &textura_id);
  // Se asocia la textura
  glBindTexture(GL_TEXTURE_2D, textura_id);
  // Activar textura 0
  glActiveTexture(GL_TEXTURE0);
  // Repetir componente S(U) de la textura hasta rellenar el modelo.
  // GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP...
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  // Repetir componente T(V) de la textura hasta rellenar el modelo
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // Asigna el tipo de filtrado píxel-coordenada {GL_NEAREST, GL_LINEAR}
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // Enviar los datos a la GPU
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img.width(),img.height(),0,GL_RGB,GL_UNSIGNED_BYTE,&data[0]);

	cout << "IDDD: " << textura_id << endl;
}



//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv){

	cout << "Practica 3 de IG 									"	<< endl << endl
	 		 << "1 -> Pinta tetraedro	 							"	<< endl
	 		 << "2 -> Pinta cubo 										"	<< endl
	 		 << "3 -> Pinta piramide								"	<< endl
			 << "4 -> Pinta ply											" << endl
	 		 << "P -> Pinta puntos									"	<< endl
	 		 << "L -> Pinta aristas									" << endl
	 		 << "F -> Pinta relleno									" << endl
	 		 << "W -> Pinta ajedrez									" << endl
			 																					<< endl
			 << "5 -> Pinta jerarquico 							" << endl
			 << "Z/z -> +/- primer grado libertad		" << endl
			 << "X/x -> +/- segundo grado libertad	" << endl
			 << "C/c -> +/- tercer grado libertad		" << endl
			 																					<< endl
			 << "6 -> Pinta tablero		 							" << endl
			 << "I -> poner/quitar iluminación			" << endl
			 << "T -> poner/quitar textura					" << endl
			 << "S/s ->FLAT/SMOOTH									" << endl

			 << endl;

 	if (argc < 2) {
 		cout << "No se lee ningún archivo" << endl;
		figura_puntero = &cubo;
 	}else{
 		ply.parametros(argv[1]);
		figura_puntero = &cubo;
		//rotaX.parametrosX(figura_puntero->vertices,10);
 	}



	// se llama a la inicialización de glut
	glutInit(&argc, argv);

	// se indica las caracteristicas que se desean para la visualización con OpenGL
	// Las posibilidades son:
	// GLUT_SIMPLE -> memoria de imagen simple
	// GLUT_DOUBLE -> memoria de imagen doble
	// GLUT_INDEX -> memoria de imagen con color indizado
	// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
	// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
	// GLUT_DEPTH -> memoria de profundidad o z-bufer
	// GLUT_STENCIL -> memoria de estarcido
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	// posicion de la esquina inferior izquierdad de la ventana
	glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

	// tamaño de la ventana (ancho y alto)
	glutInitWindowSize(UI_window_width,UI_window_height);

	// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
	// al bucle de eventos)
	glutCreateWindow("Practica 4");

	// asignación de la funcion llamada "dibujar" al evento de dibujo
	glutDisplayFunc(draw_scene);

	// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
	glutReshapeFunc(change_window_size);
	// asignación de la funcion llamada "tecla_normal" al evento correspondiente
	glutKeyboardFunc(normal_keys);
	// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
	glutSpecialFunc(special_keys);

	// funcion de inicialización
	initialize();

	initTexture();


	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
