#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <learnopengl/shader_s.h>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION h
#include <learnopengl/stb_image.h> 

// nuevos include's
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// Definir Variables Globales para Transformaciones

glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
float scale = 0.5f;
float rotation = 0.0f;

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Eddy Arias 1725589681", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader zprogram
    Shader ourShader("shaders/B2T1_vertexshader.vs", "shaders/B2T1_fragmentshader.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    float vertices[] = {
            // Triángulo morado
            0.4f, 0.0f, 0.0f,    0.4157f, 0.4f, 0.7843f,   0.7f, 0.5f,
            0.8f, 0.0f, 0.0f,    0.4157f, 0.4f, 0.7843f,   0.9f, 0.5f,
            0.4f, 0.4f, 0.0f,    0.4157f, 0.4f, 0.7843f,   0.7f, 0.7f,

            0.4f, 0.0f, 0.0f,    0.4157f, 0.4f, 0.7843f,   0.7f, 0.5f,
            0.4f, 0.4f, 0.0f,    0.4157f, 0.4f, 0.7843f,   0.7f, 0.7f,
            0.0f, 0.4f, 0.0f,    0.4157f, 0.4f, 0.7843f,   0.5f, 0.7f,

            // Triángulo verde lima
            0.0f, 0.8f, 0.0f,    0.6f, 0.8f, 0.2f,         0.5f, 0.9f,
            0.4f, 0.4f, 0.0f,    0.6f, 0.8f, 0.2f,         0.7f, 0.7f,
            -0.4f, 0.4f, 0.0f,    0.6f, 0.8f, 0.2f,        0.3f, 0.7f,

            // Triángulo NARANJA
            -0.8f, 0.0f, 0.0f,    1.0f, 0.6039f, 0.2509f,   0.1f, 0.5f,
            -0.4f, 0.0f, 0.0f,    1.0f, 0.6039f, 0.2509f,   0.3f, 0.5f,
            -0.4f, 0.4f, 0.0f,    1.0f, 0.6039f, 0.2509f,   0.3f, 0.7f,

            // Triángulo celeste
            -0.4f, 0.4f, 0.0f,   0.1882f, 0.5961f, 0.9804f, 0.3f, 0.7f,
            0.0f, 0.4f, 0.0f,    0.1882f, 0.5961f, 0.9804f, 0.5f, 0.7f,
            -0.4f, 0.0f, 0.0f,   0.1882f, 0.5961f, 0.9804f, 0.3f, 0.5f,

            // Triángulo verde/celeste
            0.0f, -0.4f, 0.0f,   0.0f, 0.7961f, 0.4392f,   0.5f, 0.3f,
            0.0f, 0.4f, 0.0f,    0.0f, 0.7961f, 0.4392f,   0.5f, 0.7f,
            -0.8f, -0.4f, 0.0f,   0.0f, 0.7961f, 0.4392f,   0.1f, 0.3f,

            // Triángulo amarillo
            0.8f, -0.4f, 0.0f,   1.0f, 0.8039f, 0.2157f,   0.9f, 0.3f,
            0.0f, -0.4f, 0.0f,   1.0f, 0.8039f, 0.2157f,   0.5f, 0.3f,
            0.0f, 0.4f, 0.0f,   1.0f, 0.8039f, 0.2157f,   0.5f, 0.7f,

            // Triángulos rosa
            -0.2f, -0.4f, 0.0f,  1.0f, 0.4118f, 0.4f,      0.4f, 0.3f,
            0.2f, -0.4f, 0.0f,  1.0f, 0.4118f, 0.4f,      0.6f, 0.3f,
            -0.2f, -0.8f, 0.0f,  1.0f, 0.4118f, 0.4f,      0.4f, 0.1f,
            0.2f, -0.4f, 0.0f,  1.0f, 0.4118f, 0.4f,      0.6f, 0.3f,
            -0.2f, -0.8f, 0.0f,  1.0f, 0.4118f, 0.4f,      0.4f, 0.1f,
            0.2f, -0.8f, 0.0f,  1.0f, 0.4118f, 0.4f,      0.6f, 0.1f,
    };
    unsigned int indices[] = {
        0, 1, 2,  // Triángulo Azul 1
        3, 4, 5,  // Triángulo Azul 2
        6, 7, 8,  // Triángulo verde lima
        9, 10, 11, // Triángulo NARANJA
        12, 13, 14, // Triángulo celeste
        15, 16, 17, // Triángulo verde/celeste
        18, 19, 20, // Triángulo amarillo
        21, 22, 23, // Triángulo rosa 1
        24, 25, 26  // Triángulo rosa 2
    };

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // para que la imagen salga girada
    stbi_set_flip_vertically_on_load(true);

    unsigned char* data = stbi_load("textures/texture1.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    unsigned int texture2;
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps

    unsigned char* data2 = stbi_load("textures/texture2.jpg", &width, &height, &nrChannels, 0);
    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture2" << std::endl;
    }
    stbi_image_free(data2);

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);      

        // render container
        ourShader.use();
        glBindVertexArray(VAO);

        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int))); // Ajusta para dibujar los triángulos restantes
           
            //Nuevo 
                // create transformations
                glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                transform = glm::rotate(transform, (float)glfwGetTime()*2, glm::vec3(0.0f, 0.0f, 1.0f));
                transform = glm::scale(transform, glm::vec3(sin(glfwGetTime()) / 2.0f + 0.5f, sin(glfwGetTime()) / 2.0f + 0.5f, 0.5));
                transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

                // get matrix's uniform location and set matrix
                ourShader.use();
                unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

                // set the texture mix value in the shader
                float timeValue = glfwGetTime(); //tiempo de ejecucion
                float visibilyFactor = sin(timeValue) / 2.0f + 0.5f; //oscila entre 0 y 1  
                ourShader.setFloat("visibleColor", visibilyFactor);

        //segundo MODELO
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, 15, GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int))); // Ajusta para dibujar los triángulos restantes

                transform = glm::mat4(1.0f); //RESET THE TRANSFORMATION MATRIX   
                transform = glm::translate(transform, position);
                transform = glm::scale(transform, glm::vec3(scale, scale, scale));
                transform = glm::scale(transform, glm::vec3(0.5625, 1.0, 1.0));
                transform = glm::rotate(transform, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

                glUniformMatrix4fv(transformLoc, 1, GL_FALSE, &transform[0][0]);
    
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Movimiento
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        position.y += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        position.y -= 0.001f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        position.x -= 0.001f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        position.x += 0.001f;

    // Escala
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        scale += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        scale -= 0.001f;

    // Rotación
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        rotation += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        rotation -= 0.001f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}