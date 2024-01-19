#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <learnopengl/shader_s.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;


int main()
{
    /*Se inicia el gestor de ventanas*/
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*Se crea la ventana segun los parametros adecuados, ancho y alto, nombre de ventana "Primer triangulo"*/
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Figura 20 ", NULL, NULL);
    /*Se verifican problemas en la creacion de la ventana*/
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    /*Se establece el contexto de la ventana creada*/
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Se carga glad.c para utilizarlo en el programa
     y se emite un mensaje en caso de error. */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //Crea y toma argumentos de entrada.
    Shader ourShader("shaders/B1P3_Eddy_Arias_code_VerShader.vs", "shaders/B1P3_Eddy_Arias_code_FragShader.fs");

    // Configuración de los vértices y colores
    float vertices[] = {
        // Posiciones        // Colores
        0.4f, 0.0f, 0.0f,   0.6f, 0.8f, 0.2f,
        0.8f, 0.0f, 0.0f,   1.0f, 0.6039f, 0.2509f,
        0.4f, 0.4f, 0.0f,   0.1882f, 0.5961f, 0.9804f,

        // Triángulo morado
       -0.8f, 0.0f, 0.0f,   0.4157f, 0.4f, 0.7843f,
       -0.4f, 0.0f, 0.0f,   0.4157f, 0.4f, 0.7843f,
       -0.4f, 0.4f, 0.0f,   0.4157f, 0.4f, 0.7843f,

       // Triángulo verde lima
      -0.4f, 0.4f, 0.0f,   0.0f, 0.7961f, 0.4392f,
       0.0f, 0.4f, 0.0f,   0.0f, 0.7961f, 0.4392f,
       0.0f, 0.8f, 0.0f,   0.0f, 0.7961f, 0.4392f,

       // Triángulo celeste
       0.0f, 0.4f, 0.0f,   0.1882f, 0.5961f, 0.9804f,
       0.4f, 0.4f, 0.0f,   0.1882f, 0.5961f, 0.9804f,
       0.0f, 0.8f, 0.0f,   0.1882f, 0.5961f, 0.9804f,

       // Triángulo naranja
       0.4f, 0.4f, 0.0f,   1.0f, 0.6039f, 0.2509f,
       0.8f, 0.0f, 0.0f,   1.0f, 0.6039f, 0.2509f,
       0.8f, 0.4f, 0.0f,   1.0f, 0.6039f, 0.2509f,

       // Triángulo verde/celeste
      -0.4f, 0.4f, 0.0f,   0.0f, 0.7961f, 0.4392f,
       0.0f, 0.8f, 0.0f,   0.0f, 0.7961f, 0.4392f,
      -0.8f, 0.4f, 0.0f,   0.0f, 0.7961f, 0.4392f,

      // Triángulo amarillo
     -0.8f, 0.4f, 0.0f,   1.0f, 0.8039f, 0.2157f,
     -0.2f, -0.4f, 0.0f,  1.0f, 0.8039f, 0.2157f,
      0.2f, -0.4f, 0.0f,  1.0f, 0.8039f, 0.2157f,

      // Triángulo rosa
     -0.2f, -0.4f, 0.0f,   1.0f, 0.4118f, 0.4f,
      0.2f, -0.4f, 0.0f,   1.0f, 0.4118f, 0.4f,
      0.0f, -0.8f, 0.0f,   1.0f, 0.4118f, 0.4f
    };


    //Se crea el VAO, VBO 
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Aqui comienza la recopilacion de informacion del VAO
    glBindVertexArray(VAO);
    //Se añade el VBO al buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //Se colocan la informacion de los vertices en el VBO para mover los datos de la CPU a la GPU 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Se describe como se debe interpretar loa informacion del arreglo de vertices del VBO
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
        /*Se procesa la informacion dada por
        dispositivos de entrada del computador*/
        processInput(window);

        /*Se indica el color de fondo de la ventana*/
                    /*R     G      B     a*/
        //fondo Blanco como el de la figura asignada
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        /*se limpia la memoria del buffer de pixeles*/
        glClear(GL_COLOR_BUFFER_BIT);

        /*se carga la informacion(datos) del VAO y dibuja los objetos*/
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 27);


        float timeValue = glfwGetTime();
        float offset1 = sin(timeValue) / 2.0f + 0.5f;
        float offset2 = sin(timeValue) / 2.0f + 0.5f;
        float offset3 = sin(timeValue) / 2.0f + 0.5f;

        ourShader.setFloat("xOffset1", offset1);
        ourShader.setFloat("xOffset2", offset2);
        ourShader.setFloat("xOffset3", offset3);


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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}