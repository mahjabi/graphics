//
//  main.cpp
//  making a ship


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float rotateAngle = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec4 colorInfo;\n"
"void main()\n"
"{\n"
"   FragColor = colorInfo;\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    //lines, line_strip, line_loop, triangles, triangle_strip
    /*float vertices[] = {
        -0.75f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.25f, 0.5f, 0.0f,
         0.0f, -0.5f, 0.0f,
         0.25f, 0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };*/
    
    //triangle_fan
    /*float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.0f, 0.0f,
        0.33f, 0.33f, 0.0f,
         0.0f, 0.5f, 0.0f,
        -0.33f, 0.33f, 0.0f,
        -0.5f, 0.0f, 0.0f
        //-0.33f, -0.33f, 0.0f,
        //0.0f, -0.5f, 0.0f,
       // 0.33f, -0.33f, 0.0f
    };*/
    
    //triangle
    float vertices[] = {
         //big rec
       -0.8238394367840683, -0.9992554169803824,0,
-0.7758693979157234, -0.19903982130007525,0,
0.9464011357669337, -0.9957936615981304,0,
0.9941711374061282, -0.20007334698402213,0,
//left big triangle

-0.8238394367840683, -0.9992554169803824,0,
-0.7758693979157234, -0.19903982130007525,0,
-1.262587759388553, -0.19223855550894187,0,

//right big triangle
0.9464011357669337, -0.9957936615981304,0,
0.9941711374061282, -0.20007334698402213,0,
1.177549710640591, -0.1902604095762268,0,

//2nd rec
-0.7715241447713883, -0.21250343813987582,0,
-0.7474307718380924, 0.10670597027780171,0,
0.9424448439015032, -0.1958114426851667,0,
0.9387385985725116, 0.10978987756054581,0,

//2nd rec left tri
-0.7715241447713883, -0.21250343813987582,0,
-0.7474307718380924, 0.10670597027780171,0,
-0.9811020384349312, -0.1999622151900493,0,
//2nd rec right tri

1.0388794581213723, -0.19537802868867282,0,
0.9424448439015032, -0.1958114426851667,0,
0.9387385985725116, 0.10978987756054581,0,

//3rd rec
-0.416091328108287, 0.10819513631703681,0,
-0.3775619351379287, 0.41848066167870135,0,
0.8251952446705355, 0.11377395237446963,0,
0.8117983069071182, 0.42382610096879136,0,

//3rd rec left
-0.596197070010252, 0.11637443635343248,0,
-0.416091328108287, 0.10819513631703681,0,
-0.3775619351379287, 0.41848066167870135,0,

//window
-0.9236135614128187, -0.3525128287764665,0,
-0.926941958642303, -0.48286486651682403,0,
-0.7929614678287349, -0.3609143924008078,0,
-0.7981624357866605, -0.4777917001219669,0,

//4th rec
-0.03983796984438803, 0.7301108817474362,0,
-0.06293115663192905, 0.4333778786607506,0,
0.6500404241900573, 0.7332114587992764,0,
0.6564193891640941, 0.43211653279915974,0,

//4th left
-0.20881941916967905, 0.4327222010763113,0,
-0.03983796984438803, 0.7301108817474362,0,
-0.06293115663192905, 0.4333778786607506,0,

//upper
0.16156062378275937, 0.9782070552019403,0,
0.2456318259231578, 0.9785849033014477,0,
0.14995846449200245, 0.7174807533624312,0,
0.23650234904829492, 0.717869714641336,0,

//upper 2

0.4666618509555942, 0.7233985213914811,0,
0.5554783806986294, 0.7193033147835846,0,
0.48360944953644114, 0.9931376117221815,0,
0.5648078948026436, 0.9845137845098948,0,

//win2
-0.6522741732489105, -0.4771360225375276,0,
-0.647273242520136, -0.36475399588256696,0,
-0.5484215117813596, -0.476669269002842,0,
-0.5411479358658419, -0.3687714102346824,0,

//win3
-0.7172140370568969, 0.007965371332998128,0,
-0.613161338360195, 0.012927405933882197,0,
-0.7195422481406263, -0.09991026107636691,0,
-0.6154895494439244, -0.09494822647548284,0,

//win4
-0.48685449792044655, 0.01798945914934169,0,
-0.3658930967707882, 0.014038723873609937,0,
-0.49018289514993096, -0.1123625785910154,0,
-0.3663487371260765, -0.10731163855495329,0,

//win5
-0.3498178827726275, 0.3197289495545004,0,
-0.22371107956202996, 0.3202957217037615,0,
-0.3529462427729607, 0.19387219288034152,0,
-0.22456679437562, 0.1899547971428015,0,

//win6
-0.10254964118322052, 0.3208402674942281,0,
0.026029844443271166, 0.32141815282288644,0,
-0.10320531876765981, 0.19499462399946654,0,
0.022901484442937603, 0.19556139614872758,0,

0.4797642894649834, 0.017839431227478553,0,
0.5963804374703063, 0.02735231279154715,0,
0.4797087235679969, -0.09452036906868777,0,
0.5979974050726102, -0.10297749859001559,0,
0.2300289220493812, 0.62795298013797,0,
0.3464450328255533, 0.6329705806358404,0,
0.23017339338154552, 0.5200884609080022,0,
0.34618942969941613, 0.5161154992734758,0,
0.002542139787126585, 0.6269305676334206,0,
0.10164947365204036, 0.6318703758755101,0,
-0.0076041930025869675, 0.5100310335534669,0,
0.10159390775505384, 0.5195105755793439,0,
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    glLineWidth(7.0f);
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // create transformations
        /*glm::mat4 trans = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        trans = glm::translate(trans, glm::vec3(translate_X, translate_Y, 0.0f));
        trans = glm::rotate(trans, glm:: radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans,glm::vec3(scale_X, scale_Y, 1.0));*/
        glm::mat4 translationMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 scaleMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y , 0.0f));
        rotationMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, 0.5f, 1.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
        //modelMatrix = rotationMatrix * scaleMatrix;
        
        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
// draw our first triangle
        int colorLocation = glGetUniformLocation(shaderProgram, "colorInfo");
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.0, 0.6706, 0.9686,1)));
        glLineWidth(7.0f);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_LINES, 0, 6);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        
        //glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
        
        glDrawArrays(GL_TRIANGLES, 4, 3);
        glDrawArrays(GL_TRIANGLES, 7, 3);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------

         glm::mat4 translationMatrix1;
        glm::mat4 rotationMatrix1;
        glm::mat4 scaleMatrix1;
        glm::mat4 modelMatrix1;
        glm::mat4 identityMatrix1 = glm::mat4(1.0f);
        translationMatrix1 = glm::translate(identityMatrix1, glm::vec3(0.0f, 0.0f, 0.0f));
        rotationMatrix1 = glm::rotate(identityMatrix1, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix1 = glm::scale(identityMatrix1, glm::vec3(0.5f, 0.5f, 1.0f));
        modelMatrix1 = translationMatrix1 * rotationMatrix1 * scaleMatrix1;
        //modelMatrix = rotationMatrix * scaleMatrix;
        
        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        
// draw our first triangle
    
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.9961, 0.9961, 0.9961, 0.1)));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_LINES, 0, 6);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        glDrawArrays(GL_TRIANGLES, 14, 3);
         glDrawArrays(GL_TRIANGLES, 17, 3);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 10, 4);
        

        glm::mat4 translationMatrix2;
        glm::mat4 rotationMatrix2;
        glm::mat4 scaleMatrix2;
        glm::mat4 modelMatrix2;
        glm::mat4 identityMatrix2 = glm::mat4(1.0f);
        translationMatrix2 = glm::translate(identityMatrix2, glm::vec3(0.0f, 0.0f, 0.0f));
        rotationMatrix2 = glm::rotate(identityMatrix2, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix2 = glm::scale(identityMatrix2, glm::vec3(0.5f, 0.5f, 1.0f));
        modelMatrix2 = translationMatrix2 * rotationMatrix2 * scaleMatrix2;
        //modelMatrix = rotationMatrix * scaleMatrix;
        
        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        
// draw our first triangle
        
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.9961, 0.9961, 0.9961, 0.1)));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_LINES, 0, 6);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        glDrawArrays(GL_TRIANGLES, 24, 3);
        //glDrawArrays(GL_TRIANGLES, 27, 3);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 20, 4);
glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.2980, 0.4824, 0.5412, 0.1)));
 glDrawArrays(GL_TRIANGLE_STRIP, 27, 4);



  glm::mat4 translationMatrix3;
        glm::mat4 rotationMatrix3;
        glm::mat4 scaleMatrix3;
        glm::mat4 modelMatrix3;
        glm::mat4 identityMatrix3 = glm::mat4(1.0f);
        translationMatrix3 = glm::translate(identityMatrix3, glm::vec3(0.0f, 0.0f, 0.0f));
        rotationMatrix3 = glm::rotate(identityMatrix3, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix3 = glm::scale(identityMatrix3, glm::vec3(0.5f, 0.5f, 1.0f));
        modelMatrix3 = translationMatrix3 * rotationMatrix3 * scaleMatrix3;
        //modelMatrix = rotationMatrix * scaleMatrix;
        
        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        
// draw our first triangle
        
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.9961, 0.9961, 0.9961, 0.1)));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_LINES, 0, 6);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        glDrawArrays(GL_TRIANGLES, 35, 3);
         //glDrawArrays(GL_TRIANGLES, 27, 3);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 31, 4);

 
glm::mat4 translationMatrix4;
        glm::mat4 rotationMatrix4;
        glm::mat4 scaleMatrix4;
        glm::mat4 modelMatrix4;
        glm::mat4 identityMatrix4 = glm::mat4(1.0f);
        translationMatrix4 = glm::translate(identityMatrix4, glm::vec3(0.0f, 0.0f, 0.0f));
        rotationMatrix4 = glm::rotate(identityMatrix4, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix4 = glm::scale(identityMatrix4, glm::vec3(0.5f, 0.5f, 1.0f));
        modelMatrix4 = translationMatrix4 * rotationMatrix4 * scaleMatrix4;
        //modelMatrix = rotationMatrix * scaleMatrix;
        
        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        
// draw our first triangle
        
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.9961, 0.2509, 0.1922, 0.1)));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_LINES, 0, 6);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        //glDrawArrays(GL_TRIANGLES, 35, 3);
         //glDrawArrays(GL_TRIANGLES, 27, 3);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 38, 4);

 
 glm::mat4 translationMatrix5;
        glm::mat4 rotationMatrix5;
        glm::mat4 scaleMatrix5;
        glm::mat4 modelMatrix5;
        glm::mat4 identityMatrix5 = glm::mat4(1.0f);
        translationMatrix5 = glm::translate(identityMatrix5, glm::vec3(0.0f, 0.0f, 0.0f));
        rotationMatrix5 = glm::rotate(identityMatrix5, glm::radians(-1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix5 = glm::scale(identityMatrix5, glm::vec3(0.5f, 0.5f, 1.0f));
        modelMatrix5 = translationMatrix5 * rotationMatrix5 * scaleMatrix5;
        //modelMatrix = rotationMatrix * scaleMatrix;
        
        // get matrix's uniform location and set matrix
        glUseProgram(shaderProgram);
        
// draw our first triangle
        
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.9961, 0.2509, 0.1922, 0.1)));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_LINES, 0, 6);
        //glDrawArrays(GL_LINE_STRIP, 0, 6);
        //glDrawArrays(GL_LINE_LOOP, 0, 6);
        //glDrawArrays(GL_TRIANGLES, 35, 3);
         //glDrawArrays(GL_TRIANGLES, 27, 3);
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glDrawArrays(GL_TRIANGLE_STRIP, 42, 4);
        glUniform4fv(colorLocation, 1, glm::value_ptr(glm::vec4(0.2980, 0.4824, 0.5412, 0.1)));
        glDrawArrays(GL_TRIANGLE_STRIP, 46, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 50, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 54, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 58, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 62, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 66, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 70, 4);
glDrawArrays(GL_TRIANGLE_STRIP, 74, 4);
glLineWidth(0.7f);
        glfwSwapBuffers(window);
        glfwPollEvents();
    
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        rotateAngle+=1;
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        rotateAngle-=1;
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        translate_Y+=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        translate_Y-=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        translate_X+=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        translate_X-=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        scale_X+=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        scale_X-=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        scale_Y+=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    {
        scale_Y-=0.01;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
