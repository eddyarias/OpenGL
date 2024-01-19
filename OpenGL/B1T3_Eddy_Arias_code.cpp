#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <learnopengl/shader_s.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    /*Se inicia el gestor de ventanas*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*Se crea la ventana segun los parametros adecuados, ancho y alto, nombre de ventana "Primer triangulo"*/
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "B1T3 Eddy Arias Imagen 1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);  //Establecer la ventana actual de OpenGL
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: cargar todos los punteros de funciones de OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Crea y toma argumentos de entrada.
    Shader ourShader("shaders/B1P3_Eddy_Arias_code_VerShader.vs", "shaders/B1P3_Eddy_Arias_code_FragShader.fs");

    float vertices[] = {
        // Posiciones        // Colores      
        //Triángulos morados
        0.4f, 0.0f, 0.0f,    0.4157f, 0.4f, 0.7843f, 
        0.8f, 0.0f, 0.0f,    0.4157f, 0.4f, 0.7843f, 
        0.4f, 0.4f, 0.0f,    0.4157f, 0.4f, 0.7843f,
        0.4f, 0.0f, 0.0f,    0.4157f, 0.4f, 0.7843f,
        0.4f, 0.4f, 0.0f,    0.4157f, 0.4f, 0.7843f,
        0.0f, 0.4f, 0.0f,    0.4157f, 0.4f, 0.7843f,

        // Triángulo verde lima
        0.0f, 0.8f, 0.0f,    0.6f, 0.8f, 0.2f,        
        0.4f, 0.4f, 0.0f,    0.6f, 0.8f, 0.2f,
       -0.4f, 0.4f, 0.0f,    0.6f, 0.8f, 0.2f,

        // Triángulo NARANJA
       -0.8f, 0.0f, 0.0f,    1.0f, 0.6039f, 0.2509f,
       -0.4f, 0.0f, 0.0f,    1.0f, 0.6039f, 0.2509f,
       -0.4f, 0.4f, 0.0f,    1.0f, 0.6039f, 0.2509f,

       //Triángulo celeste
        -0.4f, 0.4f, 0.0f,   0.1882f, 0.5961f, 0.9804f,
        0.0f, 0.4f, 0.0f,    0.1882f, 0.5961f, 0.9804f,
        -0.4f, 0.0f, 0.0f,   0.1882f, 0.5961f, 0.9804f,

       // Triángulo verde/celeste
      0.0f, -0.4f, 0.0f,     0.0f, 0.7961f, 0.4392f,
       0.0f, 0.4f, 0.0f,     0.0f, 0.7961f, 0.4392f,
      -0.8f, -0.4f, 0.0f,    0.0f, 0.7961f, 0.4392f,

      // Triángulo amarillo
     0.8f, -0.4f, 0.0f,      1.0f, 0.8039f, 0.2157f,
     0.0f, -0.4f, 0.0f,      1.0f, 0.8039f, 0.2157f,
      0.0f, 0.4f, 0.0f,      1.0f, 0.8039f, 0.2157f,

      // Triángulos rosa
     -0.2f, -0.4f, 0.0f,     1.0f, 0.4118f, 0.4f,
      0.2f, -0.4f, 0.0f,     1.0f, 0.4118f, 0.4f,
      -0.2f, -0.8f, 0.0f,    1.0f, 0.4118f, 0.4f,
      0.2f, -0.4f, 0.0f,     1.0f, 0.4118f, 0.4f,
      -0.2f, -0.8f, 0.0f,    1.0f, 0.4118f, 0.4f,
      0.2f, -0.8f, 0.0f,     1.0f, 0.4118f, 0.4f,
    };

    //Se crea el VAO, VBO 
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Aqui comienza la recopilacion de informacion del VAO
    glBindVertexArray(VAO);
    //Se añade el VBO al buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Se envia los vertices en el VBO para mover los datos de la CPU a la GPU 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Se describe como se debe interpretar la informacion del arreglo de vertices del VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //Se cierra el VAO, VBO 
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        //Se procesa la informacion dada por dispositivos de entrada del computador
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);               //fondo             
        glClear(GL_COLOR_BUFFER_BIT);                       //se limpia la memoria del buffer de pixeles

        /*se carga la informacion(datos) del VAO y dibuja los objetos*/
        ourShader.use();// activar el shader program para realizar cálculos y producir el resultado visual.
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 27);
        
        float timeValue = glfwGetTime();
        float r1 = sin(timeValue)/ 2.0f + 0.5f;
        float g1 = r1;  // Utilizando el mismo valor de r1
        float b1 = r1;  // Utilizando el mismo valor de r1

        float vx1 = sin(timeValue) / 3.0f;

        ourShader.setFloat("r1", r1);
        ourShader.setFloat("g1", g1);
        ourShader.setFloat("b1", b1);
        ourShader.setFloat("vx1", vx1);

        /*Se muestran los buffers de la ventana*/
        glfwSwapBuffers(window);
        /*Gestiona eventos que ocurran en la ventana*/
        glfwPollEvents();
    }

    //Limpian los buffers ya utilizados para limpiar la memoria
    glDeleteVertexArrays(4, &VAO);
    glDeleteBuffers(4, &VBO);

    /*Finaliza el programa*/
    glfwTerminate();
    return 0;
}
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: cada vez que cambia el tamaño de la ventana (por el sistema operativo o el cambio de tamaño del usuario), se ejecuta esta función de devolución de llamada
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // asegúrese de que la ventana gráfica coincida con las dimensiones de la nueva ventana; tenga en cuenta que el ancho y el alto serán significativamente mayores que los especificados en las pantallas retina.
    glViewport(0, 0, width, height);
}