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
GLFWAPI GLFWEvent* glfwEventShift();
// Call this when done to release the event to prevent leaks.
GLFWAPI void glfwEventRelease(GLFWEvent* event);

GLFWAPI void glfwErrorCallback(int error, const char* description);
GLFWAPI void glfwWindowPosCallback(GLFWwindow* window, int xpos, int ypos);
GLFWAPI void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
GLFWAPI void glfwWindowCloseCallback(GLFWwindow* window);
GLFWAPI void glfwWindowRefreshCallback(GLFWwindow* window);
GLFWAPI void glfwWindowFocusCallback(GLFWwindow* window, int focused);
GLFWAPI void glfwWindowIconifyCallback(GLFWwindow* window, int iconified);
GLFWAPI void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height);
GLFWAPI void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
GLFWAPI void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos);
GLFWAPI void glfwCursorEnterCallback(GLFWwindow* window, int entered);
GLFWAPI void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
GLFWAPI void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
GLFWAPI void glfwCharCallback(GLFWwindow* window, unsigned int codepoint);
GLFWAPI void glfwCharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods);
GLFWAPI void glfwDropCallback(GLFWwindow* window, int count, const char** paths);
GLFWAPI void glfwMonitorCallback(GLFWmonitor* monitor, int action);
