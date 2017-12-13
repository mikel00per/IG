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
      if(i%2 == 0)      glColor3f(r1,g2,b2);
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

void _triangulos3D::ponerColor() {
  colores.resize(caras.size());

  float color1, color2, color3;
  bool repetido;
  for (size_t i = 0; i < colores.size(); i++) {
    repetido = true;
    while (repetido) {
      repetido = false;
      color1 = (float) rand() / (float) RAND_MAX;
      color2 = (float) rand() / (float) RAND_MAX;
      color3 = (float) rand() / (float) RAND_MAX;

      colores[i].r = color1;
      colores[i].g = color2;
      colores[i].b = color3;

      for (unsigned j = 0; j < i && !repetido; ++j)
        if (colores[i] == colores[j])
          repetido = true;
    }
  }
}


_tetraedro::_tetraedro(float tam, float r){

  vertices.resize(4);
  vertices[0].x = 0;    vertices[0].y = -r; vertices[0].z = tam;
  vertices[1].x = tam;  vertices[1].y = -r; vertices[1].z = -tam;
  vertices[2].x = -tam; vertices[2].y = -r; vertices[2].z = -tam;
  vertices[3].x = 0;    vertices[3].y = r; vertices[3].z = 0;


  caras.resize(4);
  caras[0]._0 = 0; caras[0]._1 = 1; caras[0]._2 = 3;
  caras[1]._0 = 1; caras[1]._1 = 2; caras[1]._2 = 3;
  caras[3]._0 = 0; caras[3]._1 = 1; caras[3]._2 = 2;
  caras[2]._0 = 2; caras[2]._1 = 0; caras[2]._2 = 3;

  ponerColor();
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


  caras.resize(12);
  caras[0]._0=0; caras[0]._1=1; caras[0]._2=4;
  caras[2]._0=1; caras[2]._1=2; caras[2]._2=5;
  caras[3]._0=2; caras[3]._1=6; caras[3]._2=5;
  caras[1]._0=1; caras[1]._1=5; caras[1]._2=4;
  caras[4]._0=2; caras[4]._1=3; caras[4]._2=6;
  caras[5]._0=3; caras[5]._1=7; caras[5]._2=6;
  caras[6]._0=3; caras[6]._1=0; caras[6]._2=7;
  caras[7]._0=0; caras[7]._1=4; caras[7]._2=7;
  caras[8]._0=4; caras[8]._1=5; caras[8]._2=6;
  caras[9]._0=4; caras[9]._1=6; caras[9]._2=7;
  caras[10]._0=3; caras[10]._1=1; caras[10]._2=2;
  caras[11]._0=3; caras[11]._1=1; caras[11]._2=0;

  ponerColor();
}

_piramide::_piramide(float tam, float al){

  vertices.resize(5);
  vertices[0].x=-tam; vertices[0].y=-al; vertices[0].z = tam;
  vertices[1].x=tam;  vertices[1].y=-al; vertices[1].z = tam;
  vertices[2].x=tam;  vertices[2].y=-al; vertices[2].z = -tam;
  vertices[3].x=-tam; vertices[3].y=-al; vertices[3].z = -tam;
  vertices[4].x=-0;   vertices[4].y=al; vertices[4].z = 0;


  caras.resize(6);
  caras[0]._0=0; caras[0]._1=1; caras[0]._2=3;
  caras[1]._0=1; caras[1]._1=2; caras[1]._2=3;
  caras[2]._0=0; caras[2]._1=1; caras[2]._2=4;
  caras[3]._0=1; caras[3]._1=2; caras[3]._2=4;
  caras[4]._0=2; caras[4]._1=3; caras[4]._2=4;
  caras[5]._0=0; caras[5]._1=4; caras[5]._2=3;

  ponerColor();
}

_objeto_ply::_objeto_ply(){

}

void _objeto_ply::parametros(char *name){

  _file_ply file;

  if (file.open(name)){
    file.read(vertices,caras);

    std::cout << "He leido el archivo ply" << std::endl;
    file.close();
  }
  else
    std::cout << "No se puede leer el archivo ply" << std::endl;

  ponerColor();
}

_rotacion::_rotacion(){

}

void _rotacion::parametros(const vector<_vertex3f>& p, unsigned num){

  this->perfil = p;
  this->n_rotaciones = num;

  float gr = 0;

  // NOTE: Moviendo puntos
  for (int i = 0; i < n_rotaciones; i++) {
    for (int j = 0; j < perfil.size(); j++) {
      gr = 2.0 * M_PI * i / (1.0 * n_rotaciones);
      vertices.emplace_back(
        perfil[j].x*cos(gr) + perfil[j].z*sin(gr),
        perfil[j].y,
        perfil[j].x*sin(gr) + perfil[j].z*cos(gr)
      );
    }
  }

  bool banderaSuperior = false, banderaInferior = false;

  if(perfil[0].x != 0)
    banderaInferior = true;

  if(perfil[perfil.size()-1].x != 0)
    banderaSuperior = true;

  auto centro = 0u;
  auto anterior = [](int actual) { return actual - 1; };
  auto siguiente = [this] (int actual) { return actual + perfil.size(); };

  // NOTE: Uniendo caras
  for (auto i = 0u; i < n_rotaciones - 1; i++) {
    for (auto j = 1u; j < perfil.size(); j++) {
      auto actual = i * perfil.size() + j;
      caras.emplace_back(actual, anterior(actual), siguiente(anterior(actual)));
      caras.emplace_back(actual, siguiente(anterior(actual)), siguiente(actual));
    }
  }

  for (auto i = 1u; i < perfil.size(); i++) {
    auto actual = (n_rotaciones - 1) * perfil.size() + i;
    auto siguiente = i;
    caras.emplace_back(actual, anterior(actual), anterior(siguiente));
    caras.emplace_back(actual, anterior(siguiente), siguiente);
  }

  // Tapa inferior
  if (banderaInferior) {
    vertices.emplace_back(0, vertices.front().y, 0);
    for (size_t i = 0; i <= n_rotaciones-1; i++) {
      if(i != n_rotaciones-1){
        centro = vertices.size()-1;
        auto actual = i * perfil.size();
        caras.emplace_back(centro, siguiente(actual), actual);
      }else
        caras.emplace_back(vertices.size()-1, 0, (n_rotaciones-1)* perfil.size());
    }
  }

  // Tapa Superior
  if (banderaSuperior) {
    vertices.emplace_back(0, vertices[perfil.size()-1].y, 0);
    for (size_t i = 0; i <= n_rotaciones-1; i++) {
      if (i!=n_rotaciones-1) {
        centro = vertices.size()-1;
        auto actual = i * perfil.size() + (perfil.size()-1);
        caras.emplace_back(centro, actual, siguiente(actual));
      }else
        caras.emplace_back(vertices.size()-1, perfil.size()-1, n_rotaciones* perfil.size()-1);
    }
  }

  ponerColor();
}


_rotacionX::_rotacionX(){

}

void _rotacionX::parametrosX(const vector<_vertex3f>& p, unsigned num){

  this->perfil = p;
  this->n_rotaciones = num;

  float gr = 0;

  // NOTE: Moviendo puntos
  for (int i = 0; i < n_rotaciones; i++) {
    for (int j = 0; j < perfil.size(); j++) {
      gr = 2.0 * M_PI * i / (1.0 * n_rotaciones);
      vertices.emplace_back(
        perfil[j].x,
        perfil[j].y*cos(gr) + perfil[j].z*sin(gr),
        perfil[j].y*sin(gr) + perfil[j].z*cos(gr)
      );
    }
  }
  bool banderaSuperior = false, banderaInferior = false;

  if(perfil[0].x != 0)
    banderaInferior = true;

  if(perfil[perfil.size()-1].x != 0)
    banderaSuperior = true;

  auto centro = 0u;

  auto anterior = [](int actual) { return actual - 1; };
  auto siguiente = [this](int actual) { return actual + perfil.size(); };

  // NOTE: Uniendo caras
  for (auto i = 0u; i < n_rotaciones - 1; i++) {
    for (auto j = 1u; j < perfil.size(); j++) {
      auto actual = i * perfil.size() + j;
      caras.emplace_back(actual, anterior(actual), siguiente(anterior(actual)));
      caras.emplace_back(actual, siguiente(anterior(actual)), siguiente(actual));
    }
  }

  for (auto i = 1u; i < perfil.size(); i++) {
    auto actual = (n_rotaciones - 1) * perfil.size() + i;
    auto siguiente = i;
    caras.emplace_back(actual, anterior(actual), anterior(siguiente));
    caras.emplace_back(actual, anterior(siguiente), siguiente);
  }

  // Tapa inferior
  if (banderaInferior) {
    vertices.emplace_back(0, vertices.front().y, 0);
    for (size_t i = 0; i <= n_rotaciones-1; i++) {
      if(i != n_rotaciones-1){
        centro = vertices.size()-1;
        auto actual = i * perfil.size();
        caras.emplace_back(centro, siguiente(actual), actual);
      }else
        caras.emplace_back(vertices.size()-1, 0, (n_rotaciones-1)* perfil.size());
    }
  }

  // Tapa Superior
  if (banderaSuperior) {
    vertices.emplace_back(0, vertices[perfil.size()-1].y, 0);
    for (size_t i = 0; i <= n_rotaciones-1; i++) {
      if (i!=n_rotaciones-1) {
        centro = vertices.size()-1;
        auto actual = i * perfil.size() + (perfil.size()-1);
        caras.emplace_back(centro, actual, siguiente(actual));
      }else
        caras.emplace_back(vertices.size()-1, perfil.size()-1, n_rotaciones* perfil.size()-1);
    }
  }

  ponerColor();
}

_desplazar::_desplazar(){

}


void _desplazar::parametros(const vector<_vertex3f>& b, unsigned num){
  this->base = b;
  this->n_repeticiones = num;

  // Vertices
  for (int i = 0; i < n_repeticiones; i++)
    for (int j = 0; j < base.size(); j++){
      vertices.emplace_back(base[j].x,(i*0.9), base[j].z);

    }

    // Caras
    //for (size_t i = 0; i < n_repeticiones; i++) {
      for (size_t j = 0; j < base.size(); j++) {
        caras.emplace_back(j,j+1, (base.size()+j)%base.size());
        //caras.emplace_back(j,base.size()+((base.size()+j+1 )% base.size()),base.size()+j);
      }
    //}
}
