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
float anguloEnganche = 40, v_enganche = 2;
float tamCable = 1.5, v_cable = 0.3;
float cuarto_grado = 0, v_cuarto=5;

_objeto_ply esfera;

_cubo cubo(3);
_piramide piramide(2,1.5);
_tetraedro tetraedro(3,3.5);

_objeto_ply ply;
_rotacion rota;
_rotacionX rotaX;
_desplazar desplazate;
_triangulos3D *figura_puntero;





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
		glScalef(3.0,3.0,3.0);
		glTranslatef(-2.0,-2.0*tamCable,-1.0);
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

void objetoJerarquico(float anguloT, float anguloE, float tamCable, float cuarto_grado, int accion){
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


		glPushMatrix();
			glRotatef(cuarto_grado, 0.0, 2.0,1.0);

			//brazo 2/2
			glPushMatrix();
				glScalef(0.25,0.25,2.5);
				glTranslatef(0,80.0,7);
				cubo.dibujar(accion);
			glPopMatrix();

			dibujarSoporte(anguloE,tamCable);

		glPopMatrix();


		//brazo 1/2
		glPushMatrix();
			glScalef(0.25,0.25,1.5);
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



	glPopMatrix();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects(){

	if (jerarquico) {
		objetoJerarquico(anguloTronco, anguloEnganche, tamCable, cuarto_grado, accion);
	}else{
		float r,g,b,r1,g1,b1;
		r	= 0.9; g = 0.4; b = 0.0; r1	= 0.0; g1	= 0.4; b1	= 0.9;
		switch (accion) {
			case 1:	figura_puntero->draw_puntos(r,g,b,2);									break;
			case 2:	figura_puntero->draw_aristas(r,g,b,7);								break;
			case 3:	figura_puntero->draw_solido(r,g,b);										break;
			case 4:	figura_puntero->draw_solido_ajedrez(r,g,b,r1,g1,b1);	break;
			case 5:	figura_puntero->draw_solido_colores(); 								break;
		}
	}
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void){
	clear_window();
	change_observer();
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

	if(toupper(Tecla1) != 'Z' && toupper(Tecla1) != 'C' && toupper(Tecla1) != 'X' && toupper(Tecla1) != 'N'){
		switch (toupper(Tecla1)) {
			case 'P': accion=1; 																				break;
			case 'L': accion=2;																					break;
			case 'F': accion=3; 																				break;
			case 'W': accion=4; 																				break;
			case 'A': accion=5;																					break;
			case 'V': figura_puntero = &rota;														break;
			case 'B': figura_puntero = &rotaX;													break;
			case 'E': figura_puntero = &desplazate;											break;
			case '1':	figura_puntero = &tetraedro;	jerarquico = false;	break;
			case '2':	figura_puntero = &cubo;				jerarquico = false;	break;
			case '3':	figura_puntero = &piramide;		jerarquico = false;	break;
			case '4': figura_puntero = &ply;				jerarquico = false;	break;
			case '5': jerarquico = true;																break;
		}
	}else{
		switch (Tecla1) {
			case 'z':	anguloTronco-=v_tronco;			break;
			case 'Z':	anguloTronco+=v_tronco;			break;
			case 'x':	anguloEnganche-=v_enganche;	break;
			case 'X':	anguloEnganche+=v_enganche;	break;
			case 'c':	tamCable-=v_cable;					break;
			case 'C':	tamCable+=v_cable;					break;
			case 'n': cuarto_grado-=v_cuarto;		break;
			case 'N': cuarto_grado+=v_cuarto;		break;
		}

		if (anguloEnganche > 75) anguloEnganche = 75;
		if (anguloEnganche < 40) anguloEnganche = 40;
		if (tamCable < 1.5)			 tamCable = 1.5;
		if (tamCable > 10) 			 tamCable = 10;
	}

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
			 << "5 -> Pinta jerarquico 							" << endl
	 		 << "P -> Pinta puntos									"	<< endl
	 		 << "L -> Pinta aristas									" << endl
	 		 << "F -> Pinta relleno									" << endl
	 		 << "C -> Pinta ajedrez									" << endl

			 << "Z/z -> +/- primer grado libertad		" << endl
			 << "X/x -> +/- segundo grado libertad	" << endl
			 << "C/c -> +/- tercer grado libertad		" << endl << endl;

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
	glutCreateWindow("Practica 3");

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

	// inicio del bucle de eventos
	glutMainLoop();
	return 0;
}
