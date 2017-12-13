//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.h"
#include "CImg.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <string>


using namespace std;
using namespace cimg_library;

//const float AXIS_SIZE=5000;


//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D {
  public:
    vector<_vertex3f> vertices;

    _puntos3D();
    void 	draw_puntos(float r, float g, float b, int grosor);
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D {
  public:
    _triangulos3D();
    void 	draw_aristas(float r, float g, float b, int grosor);
    void  draw_solido (float r, float g, float b);
    void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
    void  draw_solido_colores();
    void  ponerColor();
    void  dibujar(int accion);

    vector<_vertex3f> colores;
    vector<_vertex3i> caras;

    ////////// Practica 4 /////////

    void calcularNormalesCaras();
    void calcularNormalesVertices();

    void draw_iluminacion_plana();
    void draw_iluminacion_suave();
    void draw_textura(GLuint textura);

    vector<_vertex3f> normales_caras;
    vector<_vertex3f> normales_vertices;
    vector<_vertex2f> textura_coord;


    GLfloat ambiente_difusa[4],
            especular[4],
            brillo;

    bool b_normales_caras,
         b_normales_vertices,
         b_normales_coord,
         text;

    GLfloat plano_s[4], plano_t[4];
    float anchura, altura;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D {
  public:
    _cubo(float tam=0.5);

};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D {
  public:
  	_piramide(float tam=0.5, float al=0.75);

};


//*************************************************************************
// clase tedraedro
//*************************************************************************

class _tetraedro: public _triangulos3D {
  public:
  	_tetraedro(float tam=0.75, float al=0.75);
};

//*************************************************************************
// clase para objetos ply
//*************************************************************************

class _objeto_ply: public _triangulos3D {
  public:
      _objeto_ply();

  void parametros(char* archivo);
};

//*************************************************************************
// clase para objetos por revolución
//*************************************************************************

class _rotacion: public _triangulos3D {
  public:
    _rotacion();
    void parametros(const vector<_vertex3f>& perfil, unsigned num);

  vector<_vertex3f> perfil;
  unsigned n_rotaciones;
};

class _rotacionX: public _triangulos3D {
  public:
    _rotacionX();
    void parametrosX(const vector<_vertex3f>& perfil, unsigned num);

  vector<_vertex3f> perfil;
  unsigned n_rotaciones;
};


class _desplazar: public _triangulos3D {
  public:
    _desplazar();
    void parametros(const vector<_vertex3f>& base, unsigned num);

  vector<_vertex3f> base;
  unsigned n_repeticiones;
};


//********************************************************
//** Clases para practica 4
//********************************************************
class _tablero: public _triangulos3D{
  public:
    _tablero();
    _tablero(float alto=0.5, float ancho=0.125);

    void cargar_imagen ();
    void ajustar_textura(float altura=0.5, float anchura=0.125, GLuint id=0);

    GLuint id;


};