#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SharderM.h>
#include<CameraM.h>
#include <iostream>
#include <string>
#include<map>
#include<vector>
#include"bone.h"
#include "ccd.h"
#include <algorithm>

using namespace std;
string image1 = "../img/wall.jpg";
string faceimg = "../img/face.png";
string imageMa = "../img/maCome.png";
string maFace = "../img/maFace.png";
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const float maxDEG = 60;
const int maxPart = 3;
const float changeRate = 1;
const int iterTimes = 1000;
float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;
// settings

float degree[4][3] = {0};
GLFWwindow *window;
Shader *ShaderG;
unsigned int VBO, VAO;
unsigned int texture1, texture2, texture3, texture4;
Bone *root;
glm::vec3 target(0.0f, 0.5f, 0.0f);
int effector = 111111;
int axisNum;

int init();

int loadImg(string path, unsigned int &texture);

int loadImg2(string path, unsigned int &texture);

void drawBone(Bone *thisBone);

void drawBone(Bone *thisBone) {

    Shader &ourShader = *ShaderG;
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
    glm::mat4 previous = thisBone->M;
    if (thisBone->parent != NULL) {
//        vec4 endPosition = thisBone->getEndPosition();
//        vec4 startPosition = thisBone->parent->getEndPosition();
//        thisBone->M = glm::translate(thisBone->M, glm::vec3(0.0f, 0.0f, thisBone->parent->length));
////
////        thisBone->M = glm::translate(thisBone->M, glm::vec3(startPosition.x,startPosition.y,startPosition.z));
//
//        thisBone->M = glm::rotate(thisBone->M, thisBone->rotation.x,
//                                  glm::vec3(thisBone->M * glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)));
//        thisBone->M = glm::rotate(thisBone->M, thisBone->rotation.y,
//                                  glm::vec3(thisBone->M * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)));
//        thisBone->M = glm::rotate(thisBone->M, thisBone->rotation.z,
//                                  glm::vec3(thisBone->M * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)));
////
//        thisBone->M = thisBone->parent->M * thisBone->M;
        thisBone->M = thisBone->getTransform();


    } else {
//        thisBone->M = glm::rotate(thisBone->M, thisBone->rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
//        thisBone->M = glm::rotate(thisBone->M, thisBone->rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//        thisBone->M = glm::rotate(thisBone->M, thisBone->rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        thisBone->M = thisBone->getTransform();
    }

    int have = 0;
    for (std::vector<Bone *>::iterator it = thisBone->bones.begin(); it != thisBone->bones.end(); it++) {
        drawBone(*it);
        have = 1;
    }
    if (thisBone->parent != nullptr) {
        if (have == 0) {
            thisBone->M = glm::scale(thisBone->M, glm::vec3(0.125f, 0.125f, 0.5f));

        }
        ourShader.setMat4("model", thisBone->M);
//        cout << "(" << thisBone->M[3].y << "," << thisBone->M[3].z << ") ";
        if (have == 0) {
            ourShader.setInt("texture1", 3);
            ourShader.setInt("texture2", 3);
            glDrawArrays(GL_TRIANGLES, 36, 48);
        } else {
            ourShader.setInt("texture1", 0);
            ourShader.setInt("texture2", 1);
            glDrawArrays(GL_TRIANGLES, 0, 36);

        }
    }
    thisBone->M = previous;
}

void drawTarget();

void drawTarget() {
    Shader &ourShader = *ShaderG;
    ourShader.setInt("texture1", 2);
    ourShader.setInt("texture2", 2);
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 tartemp = glm::vec3(target.x, -target.z, target.y);
    model = glm::translate(model, target);
    cout << "now pos= " << tartemp.x << " " << tartemp.y << " " << tartemp.z << endl;
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 0.125f));
    ourShader.setMat4("model", model);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main() {
    for (int i = 0; i <= 35; i++) {
        for (int j = 0; j <= 4; j++) {
            if (j == 2 && j <= 2) {
                vertices[i * 5 + j] += 0.5f;
//                vertices[i*5+j]/=2;
            }
        }
    }

    for (int i = 0; i <= 35; i++) {
        for (int j = 0; j <= 4; j++) {
            if (j != 2 && j <= 2) {
                vertices[i * 5 + j] /= 8;
            }
        }
    }
    root = new Bone(0);
    init();


    Shader &ourShader = *ShaderG;
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
            glm::vec3(-1.0f, 0.0f, 0.0f),
            glm::vec3(0.0f, 0.0f, 0.0f),
            glm::vec3(1.0f, 0.0f, 0.0f),
            glm::vec3(2.0f, 0.0f, 0.0f)

    };
    glm::mat4 lastModel[] = {
            glm::mat4(1.0f),
            glm::mat4(1.0f),
            glm::mat4(1.0f),
            glm::mat4(1.0f)
    };
    glm::vec3 dirvec = glm::vec3(1.0f, 0.0f, 0.0f);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, texture3);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, texture4);

        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f,
                                                100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);

        cout << "boneM.y=";
        drawBone(root);
        cout << endl;
        drawTarget();

//        for (unsigned int i = 0; i <= maxPart; i++) {
//            // calculate the model matrix for each object and pass it to shader before drawing
//            glm::mat4 model = glm::mat4(1.0f);
//
//            if (i >= 1) {
//                //移动至上一个方块的末端
//                glm::vec4 lastpos = lastModel[i - 1] * glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
//
//                model = glm::translate(model, glm::vec3(lastpos.x, lastpos.y, lastpos.z));
//                //旋转轴位置 取上一个model的右侧位置
//                for (int axis = 0; axis <= 2; ++axis) {
//                    float sumdeg = 0;
//                    for (int j = 1; j <= i; ++j) {
//                        sumdeg += degree[j][axis];
//                    }
//                    model = glm::rotate(model, glm::radians(sumdeg),
//                                        glm::vec3(axis == 0 ? 1 : 0, axis == 1 ? 1 : 0, axis == 2 ? 1 : 0));
//                }
//                //旋转 定位至转轴
//                model = glm::translate(model, glm::vec3(0.5f, 0.0f, 0.0f));
//                //旋转轴距离 取边长/2
//
////                glm::vec4 pos = model * glm::vec4(0.5f, 0.0f, 0.0f, 1.0f);
////                cout << "x=" << pos.x << " y=" << pos.y << " z=" << pos.z << endl;
//            } else {
//                model = glm::translate(model, cubePositions[i]);
//            }
//            //压缩长宽
//            model = glm::scale(model, glm::vec3(1.0f, 0.25f, 0.25f));
//
//            //保存旋转矩阵
//            lastModel[i] = model;
//
//
////            float angle = 20.0f * i;
////            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//
////            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
int partnum = maxPart;
map<int, int> lastKey;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    int control = -1;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        control = 1;
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && control == -1)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && control == -1)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && control == 1)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && control == 1)
        camera.ProcessKeyboard(DOWN, deltaTime);

    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS && lastKey[GLFW_KEY_EQUAL] == GLFW_RELEASE) {
        partnum = std::min(partnum + 1, maxPart);
        axisNum = std::min(axisNum * 10 + 1, effector);
        cout << "axisNum=" << axisNum << endl;
//        root->bone(1)->rotate(-0.1f, 0.0f, 0.0f);

    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS && lastKey[GLFW_KEY_MINUS] == GLFW_RELEASE) {
        partnum = std::max(partnum - 1, 1);
        axisNum = std::max(axisNum / 10, 0);
        cout << "axisNum=" << axisNum << endl;
//        root->bone(11)->rotate(-0.1f, 0.0f, 0.0f);

    }
    if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS && lastKey[GLFW_KEY_ENTER] == GLFW_RELEASE) {
        ccd::findNewAngles(root->bone(effector), target, iterTimes);
    }
    lastKey[GLFW_KEY_ENTER] = glfwGetKey(window, GLFW_KEY_ENTER);
    lastKey[GLFW_KEY_EQUAL] = glfwGetKey(window, GLFW_KEY_EQUAL);
    lastKey[GLFW_KEY_MINUS] = glfwGetKey(window, GLFW_KEY_MINUS);
    int shift = 1;
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        shift = -1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        shift = -1;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS) {
        shift = -1;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        shift = -1;
    }
    if (axisNum == 0) {
        ccd::findNewAngles(root->bone(effector), target, 50);
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        if (axisNum == 0) {
            target.x += shift * deltaTime;
        } else {
            root->bone(axisNum)->rotate(shift * deltaTime, 0.0f, 0.0f);
        }
        degree[partnum][0] += changeRate * shift;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        if (axisNum == 0) {
            target.y += shift * deltaTime;
        } else {
            root->bone(axisNum)->rotate(0.0f, shift * deltaTime, 0.0f);
        }
        degree[partnum][1] += changeRate * shift;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (axisNum == 0) {
            target.z += shift * deltaTime;
        } else {
            root->bone(axisNum)->rotate(0.0f, 0.0f, shift * deltaTime);
        }
        degree[partnum][2] += changeRate * shift;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        camera.ProcessMouseMovement(-deltaTime * 1500, 0);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        camera.ProcessMouseMovement(deltaTime * 1500, 0);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.ProcessMouseMovement(0, deltaTime * 1000);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        camera.ProcessMouseMovement(0, -deltaTime * 1000);
    }
    for (int a = maxPart; a >= 1; --a) {
        for (int degaxis = 0; degaxis <= 2; ++degaxis) {
            if (degree[a][degaxis] > maxDEG) {
//                degree[a - 1][degaxis] += degree[a][degaxis] - maxDEG;
                degree[a][degaxis] = maxDEG;
            }
        }
    }
    for (int a = maxPart; a >= 1; --a) {
        for (int degaxis = 0; degaxis <= 2; ++degaxis) {
            if (degree[a][degaxis] < -maxDEG) {
//                degree[a - 1][degaxis] += degree[a][degaxis] + maxDEG;
                degree[a][degaxis] = -maxDEG;
            }
        }
    }
//    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
//        degree[maxPart] += changeRate;
//        for (int a = maxPart; a >= 2; --a) {
//            if (degree[a] > maxDEG) {
//                degree[a - 1] += degree[a] - maxDEG;
//                degree[a] = maxDEG;
//            }
//        }
//        if (degree[1] > maxDEG) {
//            degree[1] = maxDEG;
//        }
//    }
//    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
//        degree[maxPart] -= changeRate;
//        for (int a = maxPart; a >= 2; --a) {
//            if (degree[a] < -maxDEG) {
//                degree[a - 1] += maxDEG + degree[a];
//                degree[a] = -maxDEG;
//            }
//        }
//        if (degree[1] < -maxDEG) {
//            degree[1] = -maxDEG;
//        }
//    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float mousex = (xpos-lastX) / SCR_WIDTH;
    float mousey = (lastY-ypos) / SCR_HEIGHT;
//    cout<<"mouse x="<<xpos<<"mouse y="<<ypos<<endl;
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
    target+=camera.Right*mousex;
    target+=glm::vec3(0.0f, 1.0f, 0.0f) *mousey;
    lastX = xpos;
    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(yoffset);
}

int init() {

    axisNum = effector;
    Bone *temp = root;
    while (axisNum > 0) {
        target.z += 0.8f;
        axisNum /= 10;
        temp = temp->add(new Bone(1));
    }
    axisNum = 0;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glEnable(GL_DEPTH_TEST);
    // build and compile our shader zprogram
    // ------------------------------------
    ShaderG = new Shader("../6.3.coordinate_systems.vs", "../6.3.coordinate_systems.fs");
    Shader &ourShader = *ShaderG;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    stbi_set_flip_vertically_on_load(true);
    loadImg(image1, texture1);
    loadImg(faceimg, texture2);
//    loadImg(faceimg,texture2);
    loadImg(imageMa, texture3);
    loadImg(maFace, texture4);
//    glGenTextures(1, &texture1);
//    glBindTexture(GL_TEXTURE_2D, texture1);
//    // set the texture wrapping parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    // set texture filtering parameters
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//    unsigned char *data = stbi_load(image1.c_str(), &width, &height, &nrChannels, 0);
//    if (data)
//    {
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else
//    {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    stbi_image_free(data);
    // texture 2
    // ---------


    // texture 2
    // ---------


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);
}

int loadImg(string path, unsigned int &texture) {
    int width, height, nrChannels;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        if (path.find(".png") != -1) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return 0;
}

int loadImg2(string path, unsigned int &texture) {
    int width, height, nrChannels;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA

        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return 0;
}
