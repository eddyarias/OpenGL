#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// configuracion tamaño de la pantalla
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

/*Asignacion colores*/

//Triangulo arriba punta
const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.6f, 0.8f, 0.2f, 1.0f);\n"
"}\n\0";

//Triangulo naranja izquierda
const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.6039f, 0.2509f, 1.0f);\n"
"}\n\0";

//Triangulo celeste izquierda
const char* fragmentShader3Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.1882f, 0.5961f, 0.9804f, 1.0f);\n"
"}\n\0";

//2 Triangulo morado derecha
const char* fragmentShader4Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.4157f, 0.4f, 0.7843f, 1.0f);\n"
"}\n\0";

//Triangulo grande verde/celeste izquierda
const char* fragmentShader5Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(0.0f, 0.7961f, 0.4392f, 1.0f);\n"
"}\n\0";

//Triangulo grande amarillo izquierda
const char* fragmentShader6Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.8039f, 0.2157f, 1.0f);\n"
"}\n\0";

//Cuadrado rosa abajo
const char* fragmentShader7Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.4118f, 0.4f, 1.0f);\n"
"}\n\0";

int main()
{
	// Inicializar y configurar GLFW
	glfwInit();  // Inicializar GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // Establecer la versión de OpenGL a 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Descomentar esta línea para solucionar problemas de compilación en OS X
#endif
	// Creación de la ventana GLFW
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "P1B2 Eddy Arias CI:1725589681", NULL, NULL);  // Crear la ventana GLFW
	if (window == NULL)
	{
		std::cout << "Fallo al crear la ventana GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);  // Establecer la ventana actual de OpenGL
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  // Establecer la función de devolución de llamada para cambios en el tamaño del marco

	// glad: cargar todos los punteros de funciones de OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Fallo al inicializar GLAD" << std::endl;
		return -1;
	}


	// Construir y compilar nuestro programa de shader

	// shader de vértices
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);  // Crear un shader de vértices
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);  // Adjuntar el código fuente del shader al objeto de shader
	glCompileShader(vertexShader);  // Compilar el shader de vértices

	//// Verificar errores de compilación del shader de vértices
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);  // Obtener el estado de compilación del shader de vértices
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);  // Obtener los registros de información del shader de vértices
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;  // Imprimir mensaje de error y registros
	}

	// fragment shader para diferentes colores
	int fragmentShaderVerdeLima = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentShaderNaranja = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentShaderCeleste = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentShaderMorado = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentShaderVerdeCeleste = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentShaderAmarillo = glCreateShader(GL_FRAGMENT_SHADER);
	int fragmentShaderRosa = glCreateShader(GL_FRAGMENT_SHADER);


	// Compilar cada shader de fragmentos individual
	glShaderSource(fragmentShaderVerdeLima, 1, &fragmentShader1Source, NULL);  // Adjuntar código fuente del shader verde lima
	glCompileShader(fragmentShaderVerdeLima);  // Compilar el shader verde lima
	glShaderSource(fragmentShaderNaranja, 1, &fragmentShader2Source, NULL);  // Adjuntar código fuente del shader naranja
	glCompileShader(fragmentShaderNaranja);  // Compilar el shader naranja
	glShaderSource(fragmentShaderCeleste, 1, &fragmentShader3Source, NULL);  // Adjuntar código fuente del shader celeste
	glCompileShader(fragmentShaderCeleste);  // Compilar el shader celeste
	glShaderSource(fragmentShaderMorado, 1, &fragmentShader4Source, NULL);  // Adjuntar código fuente del shader morado
	glCompileShader(fragmentShaderMorado);  // Compilar el shader morado
	glShaderSource(fragmentShaderVerdeCeleste, 1, &fragmentShader5Source, NULL);  // Adjuntar código fuente del shader verde celeste
	glCompileShader(fragmentShaderVerdeCeleste);  // Compilar el shader verde celeste
	glShaderSource(fragmentShaderAmarillo, 1, &fragmentShader6Source, NULL);  // Adjuntar código fuente del shader amarillo
	glCompileShader(fragmentShaderAmarillo);  // Compilar el shader amarillo
	glShaderSource(fragmentShaderRosa, 1, &fragmentShader7Source, NULL);  // Adjuntar código fuente del shader rosa
	glCompileShader(fragmentShaderRosa);  // Compilar el shader rosa

	// Vincular los shader a los shader program
	int shaderProgramVerdeLima = glCreateProgram();  // Crear el programa de shader para verde lima
	int shaderProgramNaranja = glCreateProgram();  // Crear el programa de shader para naranja
	int shaderProgramCeleste = glCreateProgram();  // Crear el programa de shader para celeste
	int shaderProgramMorado = glCreateProgram();  // Crear el programa de shader para morado
	int shaderProgramVerdeCeleste = glCreateProgram();  // Crear el programa de shader para verde celeste
	int shaderProgramAmarillo = glCreateProgram();  // Crear el programa de shader para amarillo
	int shaderProgramRosa = glCreateProgram();  // Crear el programa de shader para rosa

	/*Se vincula el (vertexShader) y el	(fragmentShader) al (shaderProgram). 
	 implica unir los shader individuales para 
	formar un programa completo que puede ejecutarse en la GPU. */

	//1. Color VerdeLima
	glAttachShader(shaderProgramVerdeLima, vertexShader);
	glAttachShader(shaderProgramVerdeLima, fragmentShaderVerdeLima);
	glLinkProgram(shaderProgramVerdeLima);
	//2. Color Naranja
	glAttachShader(shaderProgramNaranja, vertexShader);
	glAttachShader(shaderProgramNaranja, fragmentShaderNaranja);
	glLinkProgram(shaderProgramNaranja);
	//3. Color Celeste
	glAttachShader(shaderProgramCeleste, vertexShader);
	glAttachShader(shaderProgramCeleste, fragmentShaderCeleste);
	glLinkProgram(shaderProgramCeleste);
	//4. Color Morado
	glAttachShader(shaderProgramMorado, vertexShader);
	glAttachShader(shaderProgramMorado, fragmentShaderMorado);
	glLinkProgram(shaderProgramMorado);
	//5. Color VerdeCeleste
	glAttachShader(shaderProgramVerdeCeleste, vertexShader);
	glAttachShader(shaderProgramVerdeCeleste, fragmentShaderVerdeCeleste);
	glLinkProgram(shaderProgramVerdeCeleste);
	//6. Color Amarillo
	glAttachShader(shaderProgramAmarillo, vertexShader);
	glAttachShader(shaderProgramAmarillo, fragmentShaderAmarillo);
	glLinkProgram(shaderProgramAmarillo);
	//6. Color Rosa
	glAttachShader(shaderProgramRosa, vertexShader);
	glAttachShader(shaderProgramRosa, fragmentShaderRosa);
	glLinkProgram(shaderProgramRosa);

	//Elimina (liberar memoria) de un objeto de shader después de que ya no se necesita.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShaderVerdeLima);
	glDeleteShader(fragmentShaderNaranja);
	glDeleteShader(fragmentShaderCeleste);
	glDeleteShader(fragmentShaderMorado);
	glDeleteShader(fragmentShaderVerdeCeleste);
	glDeleteShader(fragmentShaderAmarillo);
	glDeleteShader(fragmentShaderRosa);

	//configurar los vertices
	float vertices[] = {
	0.4f, 0.0f, 0.0f, // A 0
	0.8f, 0.0f, 0.0f, // B 1
	0.4f, 0.4f, 0.0f, // C 2
	0.0f, 0.4f, 0.0f, // D 3
	0.0f, 0.8f, 0.0f, // E 4
	-0.4f, 0.4f, 0.0f, // F 5
	-0.8f, 0.0f, 0.0f, // G 6
	-0.4f, 0.0f, 0.0f, // H 7
	-0.8f, -0.4f, 0.0f, // I 8
	-0.2f, -0.4f, 0.0f, // J 9
	0.2f, -0.4f, 0.0f, // K 10
	-0.2f, -0.8f, 0.0f, // L 11
	0.2f, -0.8f, 0.0f, // M 12
	0.8f, -0.4f, 0.0f, // N 13
	0.0f, -0.4f, 0.0f // O 14
	};

	// EBO_ADD: Índices para la renderización de triángulos
	unsigned int indices[] = { // note that we start from 0!
	0,1,2,//triangulo morado
	0,2,3, //triangulo morado
	2,4,5, //triangulo verde lima
	3,5,7, //triangulo celeste
	5,6,7, //triangulo naranja
	3,8,14, //triangulo verde/celeste
	3,13,14, //triangulo amarillo
	9,10,11, //triangulo rosa
	10,11,12 //triangulo rosa
	};

	//EBO_MODIFY
// Definición de los identificadores de objetos de OpenGL (VBO, VAO, EBO)
	unsigned int VBO, VAO, EBO;

	// Generación de objetos de OpenGL (VBO, VAO, EBO)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Configuración del VAO y VBO
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Configuración del EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Configuración del atributo de posición del vértice
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Desvinculación de buffers y VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //esta linea sirve para solo dibujar las lineas

	// Bucle principal de renderizado
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(VAO); //Dado que solo tenemos un VAO, no es necesario vincularlo cada vez, pero lo haremos para mantener las cosas un poco más organizadas.
		

		//Renderizar diferentes triángulos coloreados en la ventana de OpenGL
		
		// GL_TRIANGLES: Especifica que se deben dibujar triángulos.
		//	3 Indica el número de vértices que forman un triángulo.
		//	GL_UNSIGNED_INT : Indica que el tipo de datos de los índices es unsigned int.
		//(void*)(...): Indica la posición del primer índice que se usará para dibujar un triángulo
		//  específico en bytes, ajustando el desplazamiento desde el inicio del búfer de índices
		
		//Del indice 0 al 3--triangulo morado
		glUseProgram(shaderProgramMorado);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		//Del indice 3 al 6 - triagulo morado
		glUseProgram(shaderProgramMorado);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(GLuint)));
		//Del indice 6 al 9 triangulo verde lima
		glUseProgram(shaderProgramVerdeLima);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(6 * sizeof(GLuint)));
		//Del indice 9 al 12 triangulo celeste
		glUseProgram(shaderProgramCeleste);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(9 * sizeof(GLuint)));
		//Del indice 12 al 15 triangulo naranja
		glUseProgram(shaderProgramNaranja);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(12 * sizeof(GLuint)));
		//Del indice 15 al 18 triangulo verde/celeste
		glUseProgram(shaderProgramVerdeCeleste);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(15 * sizeof(GLuint)));
		//Del indice 18 al 21 triangulo amarillo
		glUseProgram(shaderProgramAmarillo);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(18 * sizeof(GLuint)));
		//Del indice 21 al 24 triangulo rosa
		glUseProgram(shaderProgramRosa);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(21 * sizeof(GLuint)));
		//Del indice 24 al 27 triangulo rosa
		glUseProgram(shaderProgramRosa);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(24 * sizeof(GLuint)));

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	// Limpieza: eliminación de objetos de OpenGL
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}

// Función para procesar la entrada del teclado
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// Función de devolución de llamada para ajustar el tamaño del marco (viewport)
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}