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
GLFWEvent* GLFWEventShift();
// Call this when done to release the event to prevent leaks.
void GLFWEventRelease(GLFWEvent* event);

void GLFWerrorCallback(int error, const char* description);
void GLFWwindowposCallback(GLFWwindow* window, int xpos, int ypos);
void GLFWwindowsizeCallback(GLFWwindow* window, int width, int height);
void GLFWwindowcloseCallback(GLFWwindow*);
void GLFWwindowrefreshCallback(GLFWwindow*);
void GLFWwindowfocusCallback(GLFWwindow*,int);
void GLFWwindowiconifyCallback(GLFWwindow*,int);
void GLFWframebuffersizeCallback(GLFWwindow*,int,int);
void GLFWmousebuttonCallback(GLFWwindow*,int,int,int);
void GLFWcursorposCallback(GLFWwindow*,double,double);
void GLFWcursorenterCallback(GLFWwindow*,int);
void GLFWscrollCallback(GLFWwindow*,double,double);
void GLFWkeyCallback(GLFWwindow*,int,int,int,int);
void GLFWcharCallback(GLFWwindow*,unsigned int);
void GLFWcharmodsCallback(GLFWwindow*,unsigned int,int);
void GLFWdropCallback(GLFWwindow*,int,const char**);
void GLFWmonitorCallback(GLFWmonitor*,int);
