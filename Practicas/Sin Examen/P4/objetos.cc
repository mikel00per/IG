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
  b_normales_caras=false;
  b_normales_vertices=false;
  b_normales_coord=false;

  text=true;

  for(int i=0; i<3; i++){
    ambiente_difusa[i]=0.7;
    especular[i]=0.7;
  }

  ambiente_difusa[3]=1.0;
  especular[3]=1.0;


  brillo=100;

  for(int i=0; i<4; i++) plano_s[i] = plano_t[i] = 0.0;

  plano_s[0];
  plano_t[1];
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

  // calcular máximos y mínimos
  float max_x, min_x, max_y, min_y;
  max_x = min_x = vertices[0].x;
  max_y = min_x = vertices[0].y;

  for (int i=0;i<vertices.size();i++){
    if (vertices[i].x>max_x) max_x=vertices[i].x;
      if (vertices[i].x<min_x) min_x=vertices[i].x;
      if (vertices[i].y>max_y) max_y=vertices[i].y;
      if (vertices[i].y<min_y) min_y=vertices[i].y;
  }

  plano_s[0]/=(max_x-min_x);
  plano_t[1]/=(max_y-min_y);

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



void _triangulos3D::dibujar(int accion){
  float r,g,b,r1,g1,b1;
  r   = colores[0].r;
  g   = colores[0].g;
  b   = colores[0].b;
  r1  = colores[3].r;
  g1  = colores[3].g;
  b1  = colores[3].b;
  switch (accion) {
    case 1: this->draw_puntos(r,g,b,4);                 break;
    case 2: this->draw_aristas(r,g,b,7);                break;
    case 3: this->draw_solido(r,g,b);                   break;
    case 4: this->draw_solido_ajedrez(r,g,b,r1,g1,b1);  break;
    case 5: this->draw_solido_colores();                break;
    case 6: this->draw_iluminacion_plana();             break;
    case 7: this->draw_iluminacion_suave();             break;
    //case 8: this->draw_textura(id);                     break;
  }
}


/////////////////////////////////////////////
////  Practica 4
////

void _triangulos3D::calcularNormalesCaras(){
  normales_caras.resize(caras.size());
  for (size_t i = 0; i < caras.size(); i++) {
    auto
         a1=vertices[caras[i]._1]-vertices[caras[i]._0],
         a2=vertices[caras[i]._2]-vertices[caras[i]._0],
         n=a1.cross_product(a2);

    float m=sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
    normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
  }

  b_normales_caras = true;
  cout << "Calculo caras hecho" << endl;
}

void _triangulos3D::calcularNormalesVertices(){

  if (!b_normales_caras) {
    calcularNormalesCaras();
  }

  normales_vertices.resize(vertices.size());

  for (int i = 0; i < vertices.size(); i++){
    normales_vertices[i].x=0.0;
    normales_vertices[i].y=0.0;
    normales_vertices[i].z=0.0;
	}

	for (int i = 0; i < caras.size(); i++){
    normales_vertices[caras[i]._0]+=normales_caras[i];
    normales_vertices[caras[i]._1]+=normales_caras[i];
    normales_vertices[caras[i]._2]+=normales_caras[i];
	}

	for (int i = 0; i < vertices.size(); i++)
		normales_vertices[i].normalize();

	b_normales_vertices=true;

  cout << "Calculo vertices hecho" << endl;

  /*
  if (!b_normales_caras) {
    calcularNormalesCaras();
  }

  normales_vertices.resize(vertices.size());

  for (size_t i = 0; i < caras.size(); i++) {
    auto
        a=caras[i]._0,
        b=caras[i]._1,
        c=caras[i]._2;

    normales_vertices[a] += normales_caras[i];
    normales_vertices[b] += normales_caras[i];
    normales_vertices[c] += normales_caras[i];
  }

  b_normales_vertices = true;
  cout << "Calculo vertices hecho" << endl;

   */
}


void _triangulos3D::draw_iluminacion_plana() {
  if(!b_normales_caras) calcularNormalesCaras();

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  glShadeModel(GL_FLAT);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT2);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, (GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < caras.size(); i++) {
      glNormal3fv((GLfloat*) &normales_caras[i]);
      glVertex3fv((GLfloat*) &vertices[caras[i]._0]);
      glVertex3fv((GLfloat*) &vertices[caras[i]._1]);
      glVertex3fv((GLfloat*) &vertices[caras[i]._2]);
    }
  glEnd();

  glDisable(GL_LIGHTING);
  glDisable(GL_NORMALIZE);
}

void _triangulos3D::draw_iluminacion_suave() {
  if (!b_normales_vertices) calcularNormalesVertices();

  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT3);

  glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,(GLfloat *) &ambiente_difusa);
  glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,(GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,brillo);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glBegin(GL_TRIANGLES);
    for (size_t i = 0; i < caras.size(); i++){
      glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
      glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
    	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
      glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
      glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();

  glDisable(GL_LIGHTING);
  glDisable(GL_NORMALIZE);
}


void _triangulos3D::draw_textura(GLuint textura){
/*
  GLfloat vertices[] = {vertices[4], vertices[0], vertices[1], vertices[5]} ;
  GLfloat texVertices[] = {0,0,0,1,1,1,1,0};

*/
GLfloat vertices[] = {-altura , -altura , anchura,
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
  glBindTexture(GL_TEXTURE_2D, textura);

  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glTexCoordPointer(2, GL_FLOAT, 0, texVertices);

  glDrawArrays(GL_QUADS, 0, 4);

  glDisableClientState(GL_VERTEX_ARRAY);
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_TEXTURE_2D);

  glColor3f(1.0,1.0,1.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  glBegin(GL_TRIANGLES);

  glEnd();
}

_tablero::_tablero(){

}

_tablero::_tablero(float altura, float anchura){
  vertices.resize(8);
  vertices[0].x = -altura; vertices[0].y = -altura; vertices[0].z = anchura;
  vertices[1].x = altura;  vertices[1].y = -altura; vertices[1].z = anchura;
  vertices[2].x = altura;  vertices[2].y = -altura; vertices[2].z = -anchura;
  vertices[3].x = -altura; vertices[3].y = -altura; vertices[3].z = -anchura;
  vertices[4].x = -altura; vertices[4].y = altura;  vertices[4].z = anchura;
  vertices[5].x = altura;  vertices[5].y = altura;  vertices[5].z = anchura;
  vertices[6].x = altura;  vertices[6].y = altura;  vertices[6].z = -anchura;
  vertices[7].x = -altura; vertices[7].y = altura;  vertices[7].z = -anchura;


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

  this->altura = altura;
  this->anchura = anchura;
  ponerColor();
}
