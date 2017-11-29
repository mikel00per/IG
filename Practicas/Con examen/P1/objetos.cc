#include "objetos.h"

_puntos3D::_puntos3D(){

}

void 	_puntos3D::draw_puntos(float r, float g, float b, int grosor){
  glColor3f(r,g,b);
  glPointSize(grosor);

  glBegin(GL_POINTS);
    for (int i = 0; i < vertices.size(); i++)
      glVertex3fv((GLfloat *) &vertices[i]);
  glEnd();
}

_triangulos3D::_triangulos3D(){

}

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(r,g,b);
  glPointSize(grosor);

  glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); i++){
      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

void _triangulos3D::draw_solido (float r, float g, float b){
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glColor3f(r,g,b);

  glBegin(GL_TRIANGLES);
    for(int i=0; i<caras.size(); i++){
      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2){

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);
    for (int i = 0; i < caras.size(); i++) {
      if (i % 2 == 0)   glColor3f(r1,g1,b1);
      else              glColor3f(r2,g2,b2);

      glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
      glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
      glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }
  glEnd();

}

void _triangulos3D::draw_solido_colores(){
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glShadeModel(GL_SMOOTH);
  glBegin(GL_TRIANGLES);
    for(int i=0; i < caras.size(); i++){
      glColor3f(colores[i].r, colores[i].g, colores[i].b);
      glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
      glColor3f(colores[i+1].r, colores[i+1].g, colores[i+1].b);
      glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
      glColor3f(colores[i+2].r, colores[i+2].g, colores[i+2].b);
      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }

  glEnd();
  glShadeModel(GL_FLAT);
}


_tetraedro::_tetraedro(float tam, float r){

  vertices.resize(4);
  vertices[0].x = 0;    vertices[0].y = -r; vertices[0].z = tam;
  vertices[1].x = tam;  vertices[1].y = -r; vertices[1].z = -tam;
  vertices[2].x = -tam; vertices[2].y = -r; vertices[2].z = -tam;
  vertices[3].x = 0;    vertices[3].y = r; vertices[3].z = 0;

  colores.resize(4);
  colores[0].r= 0.1; colores[0].g = 0.6;  colores[0].b = 0.2;
  colores[1].r= 0.3; colores[1].g = 0.2; colores[1].b = 0.4;
  colores[2].r= 0.5; colores[2].g = 0.8; colores[2].b = 0.9;
  colores[3].r= 0.2; colores[3].g = 0.3; colores[3].b = 0.2;

  caras.resize(4);
  caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 3;
  caras[1]._0 = 1; caras[1]._1 = 2; caras[1]._2 = 3;
  caras[3]._0 = 0; caras[3]._1 = 1; caras[3]._2 = 2;
  caras[2]._0 = 2; caras[2]._1 = 0; caras[2]._2 = 3;

}

_cubo::_cubo(float tam){
  vertices.resize(8);
  vertices[0].x = -tam; vertices[0].y = -tam; vertices[0].z = tam;
  vertices[1].x = tam;  vertices[1].y = -tam; vertices[1].z = tam;
  vertices[2].x = tam;  vertices[2].y = -tam; vertices[2].z = -tam;
  vertices[3].x = -tam; vertices[3].y = -tam; vertices[3].z = -tam;
  vertices[4].x = -tam; vertices[4].y = tam;  vertices[4].z = tam;
  vertices[5].x = tam;  vertices[5].y = tam;  vertices[5].z = tam;
  vertices[6].x = tam;  vertices[6].y = tam;  vertices[6].z = -tam;
  vertices[7].x = -tam; vertices[7].y = tam;  vertices[7].z = -tam;

  colores.resize(8);
  colores[0].r= 0.1; colores[0].g = 0.6;  colores[0].b = 0.2;
  colores[1].r= 0.3; colores[1].g = 0.2; colores[1].b = 0.4;
  colores[2].r= 0.5; colores[2].g = 0.8; colores[2].b = 0.9;
  colores[3].r= 0.2; colores[3].g = 0.3; colores[3].b = 0.2;
  colores[4].r= 0.7; colores[4].g = 0.9; colores[4].b = 0.1;
  colores[5].r= 0.2; colores[4].g = 0.5; colores[4].b = 0.5;
  colores[6].r= 0.3; colores[4].g = 0.2; colores[4].b = 0.6;
  colores[7].r= 0.5; colores[4].g = 0.7; colores[4].b = 0.9;


  caras.resize(12);
  caras[0]._0=0; caras[0]._1=1; caras[0]._2=4;
  caras[1]._0=1; caras[1]._1=5; caras[1]._2=4;
  caras[2]._0=1; caras[2]._1=2; caras[2]._2=5;
  caras[3]._0=2; caras[3]._1=6; caras[3]._2=5;
  caras[4]._0=2; caras[4]._1=3; caras[4]._2=6;
  caras[5]._0=3; caras[5]._1=7; caras[5]._2=6;
  caras[6]._0=3; caras[6]._1=0; caras[6]._2=7;
  caras[7]._0=0; caras[7]._1=4; caras[7]._2=7;
  caras[8]._0=4; caras[8]._1=5; caras[8]._2=6;
  caras[9]._0=4; caras[9]._1=6; caras[9]._2=7;
  caras[10]._0=3; caras[10]._1=1; caras[10]._2=2;
  caras[11]._0=3; caras[11]._1=1; caras[11]._2=0;
}

_piramide::_piramide(float tam, float al){

  vertices.resize(5);
  vertices[0].x=-tam; vertices[0].y=-al; vertices[0].z = tam;
  vertices[1].x=tam;  vertices[1].y=-al; vertices[1].z = tam;
  vertices[2].x=tam;  vertices[2].y=-al; vertices[2].z = -tam;
  vertices[3].x=-tam; vertices[3].y=-al; vertices[3].z = -tam;
  vertices[4].x=-0;   vertices[4].y=al; vertices[4].z = 0;

  colores.resize(5);
  colores[0].r= 0.1; colores[0].g = 0.6;  colores[0].b = 0.2;
  colores[1].r= 0.3; colores[1].g = 0.2; colores[1].b = 0.4;
  colores[2].r= 0.5; colores[2].g = 0.8; colores[2].b = 0.9;
  colores[3].r= 0.2; colores[3].g = 0.3; colores[3].b = 0.2;
  colores[4].r= 0.7; colores[4].g = 0.9; colores[4].b = 0.1;

  caras.resize(6);
  caras[0]._0=0; caras[0]._1=1; caras[0]._2=3;
  caras[1]._0=1; caras[1]._1=2; caras[1]._2=3;
  caras[2]._0=0; caras[2]._1=1; caras[2]._2=4;
  caras[3]._0=1; caras[3]._1=2; caras[3]._2=4;
  caras[4]._0=2; caras[4]._1=3; caras[4]._2=4;
  caras[5]._0=0; caras[5]._1=4; caras[5]._2=3;
}
