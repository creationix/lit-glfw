#include <GLFW/glfw3.h>

// A simple linked list node of events
// The type field tells you what kind of event data it is.
// The union contains all the possible values with named aliases.
typedef struct GLFWEvent{
  struct GLFWEvent* next;
  enum {
    GLFWerrorevt,
    GLFWwindowposevt,
    GLFWwindowsizeevt,
    GLFWwindowcloseevt,
    GLFWwindowrefreshevt,
    GLFWwindowfocusevt,
    GLFWwindowiconifyevt,
    GLFWframebuffersizeevt,
    GLFWmousebuttonevt,
    GLFWcursorposevt,
    GLFWcursorenterevt,
    GLFWscrollevt,
    GLFWkeyevt,
    GLFWcharevt,
    GLFWcharmodsevt,
    GLFWdropevt,
    GLFWmonitorevt,
  } type;
  union {
    int prev;
    struct {
      int error;
      const char* description;
    };
    struct {
      union {
        GLFWmonitor* monitor;
        GLFWwindow* window;
      };
      union {
        int focused;
        int iconified;
        int entered;
        int event;
        // struct { int xpos; int ypos; };
        struct { double xpos; double ypos; };
        struct { int width; int height; };
        struct { int mods; union {
          unsigned int codepoint;
          struct { int action; union {
            int button;
            struct { int key; int scancode; };
          };};
        };};
        struct { double xoffset; double yoffset; };
        struct { int count; const char** paths; };
      };
    };
  };
} GLFWEvent;

// Call this to get the next event from the queue.  Will return NULL if empty
GLFWEvent* glfwEventShift();
// Call this when done to release the event to prevent leaks.
void glfwEventRelease(GLFWEvent* event);

void glfwErrorCallback(int error, const char* description);
void glfwWindowPosCallback(GLFWwindow* window, int xpos, int ypos);
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
void glfwWindowCloseCallback(GLFWwindow* window);
void glfwWindowRefreshCallback(GLFWwindow* window);
void glfwWindowFocusCallback(GLFWwindow* window, int focused);
void glfwWindowIconifyCallback(GLFWwindow* window, int iconified);
void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
void glfwCursorEnterCallback(GLFWwindow* window, int entered);
void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void glfwCharCallback(GLFWwindow* window, unsigned int codepoint);
void glfwCharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
void glfwDropCallback(GLFWwindow* window, int count, const char** paths);
void glfwMonitorCallback(GLFWmonitor* monitor, int action);
