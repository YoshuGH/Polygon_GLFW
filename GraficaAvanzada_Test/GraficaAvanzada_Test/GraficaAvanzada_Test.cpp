#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void proccessInput(GLFWwindow* window);

//medidas de la pantalla
const unsigned int largo = 800;
const unsigned int ancho = 800;

const char* vertexShaderSource = "#version 330 core\n"
"layout ( location = 0) in vec3 aPos;\n"
"layout ( location = 1) in vec3 aColor;\n"
"out vec3 nuestroColor;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos, 1.0);\n"
" nuestroColor = aColor;"
"}\n\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 nuestroColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(nuestroColor, 1.0f);\n"
"}\n\0";

int main()
{
    //inicialiamos glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Creacion de nuestra ventanita
    GLFWwindow* window = glfwCreateWindow(largo, ancho, "Si", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "fallaste, date de baja paro" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "oye wey no se esta ejecutando xd" << std::endl;
        return -1;
    }

    //Inicializaciones
    // Inicializacion del vertex
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // Comprobacion del vertex
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "error error error la cagaste en el vertex\n" << infoLog << std::endl;
    }

    // Inicializacion del fragment
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // Comprobacion del fragment
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "error error error la cagaste en el fragment\n" << infoLog << std::endl;
    }

    // Inicializamos el programa
    // Inicializamos todo
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Comprobar los Linkeos
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "error error error la cagaste en el Linkeo\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Configuramos el objeto
    float vertices[]{
        -0.5f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, 0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.9f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        0.5f, -0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
       -0.5f, -0.9f, 0.0f, 1.0f, 1.0f, 1.0f,
       -0.9f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    //  Unificamos
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // Habilitar nuestros atributos de nuestras coordenadas
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)( 3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Unificacion de los buffer
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(VAO);

    glUseProgram(shaderProgram);

    //Generacion del ciclo dibujado
    while (!glfwWindowShouldClose(window))
    {
        proccessInput(window);
        //Color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Porfin dibujar
        
        /*float timeValue = glfwGetTime();
        float verde = sin(timeValue * 20 / 5.0f + 0.5f);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "nuestroColor");
        glUniform4f(vertexColorLocation, 0.0f, verde, verde, 1.0f);*/

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VBO);
    glDeleteVertexArrays(1, &VAO);

    glfwTerminate();
    return 0;
}

void proccessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}