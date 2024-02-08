#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>

#define STB_IMAGE_IMPLEMENTATION 
#include <learnopengl/stb_image.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1960;
const unsigned int SCR_HEIGHT = 1080;

Camera camera(glm::vec3(0.0f, 0.0f, 0.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Eddy Arias Ci: 1725589681", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("shaders/shader_B2T2.vs", "shaders/shader_B2T2.fs");

    float vertices[] = {
        // positions         //normales                   // texture coords
        -0.5f, -0.5f, 0.5f, 0.0f,  0.0f,  1.0f,  0.533f, 0.5f,      //a
        0.5f, -0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.724f, 0.5f,       //b
        0.5f,  0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.724f, 0.326f,      //c
        -0.5f,  0.5f, 0.5f, 0.0f,  0.0f,  1.0f,  0.533f, 0.326f,     //d
        0.5f,  0.5f, 0.5f,  0.0f,  0.0f,  1.0f,  0.724f, 0.326f,      //c
        -0.5f, -0.5f, 0.5f, 0.0f,  0.0f,  1.0f,  0.533f, 0.5f,       //a

        -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f, 0.338f, 0.5f,        //h
         -0.5f, -0.5f, 0.5f,  -1.0f, 0.0f, 0.0f, 0.533f, 0.5f,       //a    
         -0.5f,  0.5f, 0.5f,  -1.0f, 0.0f, 0.0f, 0.533f, 0.326f,     //d
         -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.338f, 0.326f,     //g
         -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.338f, 0.5f,        //h
         -0.5f,  0.5f, 0.5f,  -1.0f, 0.0f, 0.0f, 0.533f, 0.326f,     //d
         
         0.5f,  0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.724f, 0.326f,      //c
         0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.724f,  0.5f,       //b
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.925f, 0.326f,     //e
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.925f, 0.5f,      //f
         0.5f, -0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.724f,  0.5f,       //b
         0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.925f, 0.326f,     //e

        -0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f, 0.533f, 0.5f,       //a    
         0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f, 0.724f,  0.5f,       //b
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.533f, 0.745f,    //h
         0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.724f, 0.745f,     //f
         0.5f, -0.5f, 0.5f,  0.0f, -1.0f, 0.0f, 0.724f,  0.5f,       //b
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.533f, 0.745f,    //h

          0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.143f, 0.326f,     //e
         -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.339f, 0.326f,     //g
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.143f, 0.5f,       //f
         -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.369f, 0.5f,       //h
         -0.5f,  0.5f, -0.5f, 0.0f,  0.0f, -1.0f, 0.339f, 0.326f,     //g
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.143f, 0.5f,       //f

         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.533f, 0.079f,       //g
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  0.729f, 0.079f,        //e
         -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.533f, 0.326f,        //d
         0.5f,  0.5f, 0.5f,    0.0f, 1.0f, 0.0f,  0.729f, 0.326f,         //c
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f,  0.729f, 0.079f,        //e
         -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,  0.533f, 0.326f,        //d
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3(-1.5f, -0.5f, 0.0f),
        glm::vec3(1.5f,  -0.5f, 0.0f),
        glm::vec3(0.0f,  -0.5f,  0.0f),
        glm::vec3(0.0, 1.0f, 0.0f),
        glm::vec3(0.0, -2.0f, 0.0f)
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    const int cantidadTexturas = 5;
    unsigned int textures[cantidadTexturas];

    std::string imagenesJpg[cantidadTexturas] = {"texture1","texture2","texture3","texture4","texture5"};

    for (int i = 0; i < cantidadTexturas; i++) {
        glGenTextures(1, &textures[i]);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(false); // tell stb_image.h to flip loaded texture's on the y-axis.
        std::string ruta = "textures/" + imagenesJpg[i] + ".jpg";
        unsigned char* data = stbi_load(ruta.c_str(), &width, &height, &nrChannels, 0);    if (data)
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
    }

    float animationSpeed = 1.0f;  // Velocidad de la animación
    float animationTime = 0.0f;  // Tiempo transcurrido desde el inicio de la animación

    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		ourShader.setMat4("projection", projection);
		
		 // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);

        animationTime += deltaTime * animationSpeed;

        for (unsigned int i = 0; i < cantidadTexturas; i++)
        {
            // Calcula la posición del cubo en función del tiempo
            float xOffset = sin(animationTime + i) * 1.5f; // Trayectoria sinusoidal en el eje X
            float yOffset = cos(animationTime + i) * 0.75f; // Trayectoria sinusoidal en el eje Y
            cubePositions[i] = glm::vec3(xOffset, yOffset, 0.0f);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::translate(model, glm::vec3(xOffset, yOffset, -8.0f));
            model = glm::rotate(model, glm::radians(animationTime*(i+1) *10.0f), glm::vec3(1.0f, 1.0f, 1.0f));

            ourShader.setMat4("model", model);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textures[i]);

            ourShader.use();
            ourShader.setInt("texture1", 0);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    // Subir la cámara en el eje Y cuando se presiona la tecla ESPACIO
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UPWARD, deltaTime);

    // Bajar la cámara en el eje Y cuando se presiona la tecla SHIFT
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWNWARD, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);    
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}