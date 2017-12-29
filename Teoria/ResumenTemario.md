# Prosibles preguntas

### Estructuras para solidos por fronteras
HAy distintas formas de representar un sólido por fronteras que serían:
  - Lista de triangulos aislados: La malla es una lista de triangulos, cada uno formado por 3 vertices
  - Tiras de triandulos: Cada triangulo de la tira comparte una arista y dos vertidos que en principio no hay que repetir.
  - Lista de vértices y triangulos: Información de la geometria por un lado (vertices) y de la topología por otro (conectividad de vertices)
    - Lista de vertices que no se repiten.
    - Lista de caras una entrada por triangulo compuesto por indices a los vertices anteriores.
  - Lista de vértices, aristas y triangulos
    - Lista de vértices: una entrada por cada vértice, por tanto no se repiten
    - Lista de aristas: una entrada por arista que contiene los índices a los vértices extremos de la arista
    - Lista de caras: una entrada por triángulo que contiene los índices a los vértices correspondientes de la lista de vértices

### Generación de modelos por fronteras
Entre ellos podemos encontrar:
  - Revolución: Dado un perfil este se revoluciona.
  - Barrido: Dada la planta esta se superpone x veces.
  - Operaciones booleanas: Se usan sólidos, 2 o más, ya creados y usando las operaciones unión, intersección y diferencia se contruye un modelo nuevo como convinación de las figuras anteriores según la operación realizada.
  - Geometría constructiva: Se usan sólidos básicos para construir modelos jerarquicos, por ejemplo una la grua que contruí en practicas.

### Tipos de proyecciones
Hay que diferenciar entre dos tipos de proyecciones:
  - Perspectivas (1,2,3 puntos de fuga) pudiendo ser frontal, oblicua y cónica:
    - Produce la ilusión de disminución en el tamaño de los objetos cuando nos vamos alejando del centro de proyección.
    - No se pueden tomar medidas, ángulos y distancias exactas, salvo ángulos en caras paralelas al plano de proyección

  - Paralelas que se dividen en:
    - Oblicua/Caballera: Permite medir ángulos y distancias para las caras paralelas al plano de proyección y solamente distancias con un cierto factor de escala para las restantes caras.
    - Vistas múltiples (triédricas): Permiten medir tanto ángulos como distancias directamente sobre los dibujos, pero es difícil de deducir las características 3D de los objeto. (alzado, planta y perfil)

### Perspectivas definiciones
En la formación de una perspectiva podemos encontrar:
  - PO, punto en el plano de proyección. Punto inicial dosde donde se observa.
  - PM, punto de mira (o altura de la cámara). A donde se va a mirar desde PO.
  - PM-PO, normal al plano de estos dos puntos. Vector resultande de unir PM-PO.
  - VI, vector de inclinación de la cámara.
  - CP, centro de posición (posición de la cámara).
  - F y T, planos de recorte frontal y trasero.

Para que un objeto se vea tiene que estar delante del plano PP y detrás de T y evidenetemente delante del CP. El vector VI no coicide con el eje Y. CP es desde donde miramos, nuestro punto de fuga.

### Proceso Transformación de vista en 3D
Los pasos son, partiendo de una escena con un objeto y los datos: PM, PO, VI y los vectores X_0, Y_0 y Z_0:
  - Inversión del eje Z_0
  - Traslación al origen del sistema de coordenadas del observador al origen del sistema de coordenadas mundial.
  - Rotación del eje Z_0 con respecto a X
  - Rotación del eje Z_0 con respecto a Y
  - Rotación del eje Y_0 con respecto a Z

### Rasterización
También llamado discretización. Los elementos geométricos son continuos, pero si los queremos visualizar en un dispositivo raster se tienen que representar por puntos discretos que corresponderán a pixeles.

### ¿Que es el z-buffer?
Devuelve para cada pixel el color del objeto más cercano al observador. Puede emplearse cualquier tipo de objeto, no solo los que estén definidos por caras planas

Esto quiere decir que aquellos puntos que no se ven no son devueltos por el algoritmo de manera que los puntos no visibles pero existentes, no serán mostrados.

      void Z-Buffer (...){
        int pz, y, x;
        for (y=0; y<YMAX; y++){
          for (x=0; x<XMAX; x++){
            put-pixel(x,y,color_fondo);
            put_z_buffer(x,y,ZMAX);
          }
        }
        for (cada polígono Q de la escena){
          for (cada pixel (x,y) de la rasterización de Q){
            pz= valor de z del polígono Q en el pixel (x,y);
            if (pz<=read_z_buffer(x,y)){
              put_pixel(x,y,color del polígono Q en el pixel (x,y));
              put_z_b(x,y,pz);
            }
          }
        }
      }


### Modelos de iluminación local
Luz como partícula:
  - Explica la absorción y emisión de luz
  - Explica la reflexión especular. Los partículas luminosas son elásticas y en la reflexión se produce un choque elástico
  - Explica de forma incompleta la transmisión

Luz como onda:
  - Explica la transmisión, incluyendo que en medios con mayor índice de refracción la velocidad de la luz es menor
  - Explica las interferencias y la difracción

En general, un modelo de iluminación determina que intensidad luminosa ha de asignarse a cada punto de una superficie. Los modelos de iluminación local son llamados modelos empíricos locales. Empíricos porque están basados en la óptica geométrica y locales porque se considera que la única luz que puede iluminar una superficie procede de las fuentes de luz de la escena (luz directa). Los objetos no producen sombreas a otros objetos. Se usan las tres longitudes del modelo RGB. **El modelo más simple es el ambiental** que aproxima toda la iluminación indirecta. Asignar un valor constante de intensidad a cada punto de una cara

La iluminación tiene tres componentes en los modelos locales, que son:
  - Difusa
  - Especular
  - Ambiental

### Pasos para la iluminación.
  - Definir las luces (características). Una luz es un objeto más de la escena.
  - Habilitar la iluminación (glEnable (GL_LIGHTING)
  - Usar normales a las caras o a los vértices según el modo de suavizado
  - Definir los materiales de los objetos
  - Cambiar el modelo de iluminación

### Pasos para las texturas
  - Cargar la imagen. OpenGL no dispone de funciones para ello. Habría que usar una librería externa que dejará los datos en la memoría de la gráfica.
  - Habilitar uso de texturas. glEnable (GL_TEXTURE_2D)
  - Especificar la imagen usada como textura de OpenGL. glTexImage2D()
  - Indicar como la textura se aplica (filtros, repetición). glTexParameteri()
  - Especificar las coordenadas de textura (texels) para los vértices de los objetos (explícita y procedural) glTexCoord2()

### Que es y tipos de selección
La selección permite identificar interactivamente elementos del modelo geométrico, permite al usuario referenciar componentes de un modelo geométrico através de identificadores o etiquetas. Estas se asocian a distinto nivel pudiendo controlar diferentes ambitos en la selección: vertive, primitiva, objeto...

  - Intersección rayo escena
  - Identificando los objetos incluidos en un subvolumen de visión centrado en la posición dada (OpenGL)
  - Codificando el identificador de objeto como color y leyendo del frame buffer

### Pasos para una selección
  - Indicar un “buffer de selección” que será el que contenga el resultado de la selección. Se usa glSelectBuffer().
  - Entrar en el modo selección con glRenderMode(GL_SELECT).
  - Inicializar la pila de nombres que designaran los elementos a seleccionar. Se usa glInitNames() y glPushName().
  - Definir el volumen de vista para la selección, de modo que haya una pequeña ventana de selección (mínimo un píxel):
    - Se tiene que calcular una matriz de proyección restringida a una pequeña región del viewport alrededor del cursor usado en la selección
    - En el modo de selección solo se hace el dibujado de la escena para esta pequeña región del viewport
    - Esta matriz de proyección se llama matriz de selección (picking)
    - En la selección se determina que elementos gráficos están más cerca del cursor
    - Se realiza la transformación de coordenadas de dispositivo (región del viewport) a coordenadas de vista (región de selección)
    - Se usa la función gluPickMatrix() para calcular la matriz de selección
  - Dibujar la escena asignado nombres a los elementos que se quieran seleccionar,
  - Salir del modo de selección y procesar el “buffer de selección”.

### Ray tracing
Es un algoritmo para calcular las direcciones de los rayos que se lanzan a la
escena.

Lo que conseguimos con este algoritmo es generar efectos como sombras, hacer objetos translucidos, endefinitiva superficies difusas y especulares, sombras arrojadas,
transmisión y reflexión.
