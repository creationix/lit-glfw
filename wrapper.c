#include "wrapper.h"
#include <stdlib.h>
#include <assert.h>

static GLFWEvent* GLFWEventHead = NULL;
static GLFWEvent* GLFWEventTail = NULL;

// Poll of used instances ready for reuse.
static GLFWEvent* GLFWEventPool = NULL;
static int GLFWEventPoolSize = 0;
#define GLFWEventPoolMaxSize 10

GLFWEvent* glfwEventShift() {
  if (!GLFWEventHead) return NULL;
  GLFWEvent* event = GLFWEventHead;
  GLFWEventHead = GLFWEventHead->next;
  if (!GLFWEventHead) GLFWEventTail = NULL;
  return event;
}

void glfwEventRelease(GLFWEvent* event) {
  if (!event) return;
  assert(GLFWEventPoolSize == 0 || GLFWEventPool);
  if (GLFWEventPoolSize < GLFWEventPoolMaxSize) {
    event->next = GLFWEventPool;
    GLFWEventPool = event;
    GLFWEventPoolSize++;
  }
  else {
    // The recycling pool is large enough, let's free this one.
    free(event);
  }
}

static GLFWEvent* glfwEventPush() {
  GLFWEvent* event;
  // If there is an old event in the pool, reuse it.
  if (GLFWEventPool) {
    GLFWEventPoolSize--;
    event = GLFWEventPool;
    GLFWEventPool = event->next;
  }
  // Otherwise allocate a new event.
  else {
    assert(GLFWEventPoolSize == 0);
    event = malloc(sizeof(*event));
  }
  event->next = NULL;
  if (GLFWEventTail) {
    GLFWEventTail->next = event;
  }
  else {
   GLFWEventHead = event;
  }
  GLFWEventTail = event;
  return event;
}

void glfwErrorCallback(int error, const char* description) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWerrorevt;
  event->error = error;
  event->description = description;
}
void glfwWindowPosCallback(GLFWwindow* window, int xpos, int ypos) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWwindowposevt;
  event->window = window;
  event->xpos = xpos;
  event->ypos = ypos;
}
void glfwWindowSizeCallback(GLFWwindow* window, int width, int height) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWwindowsizeevt;
  event->window = window;
  event->width = width;
  event->height = height;
}
void glfwWindowCloseCallback(GLFWwindow* window) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWwindowcloseevt;
  event->window = window;
}
void glfwWindowRefreshCallback(GLFWwindow* window) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWwindowrefreshevt;
  event->window = window;
}
void glfwWindowFocusCallback(GLFWwindow* window, int focused) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWwindowfocusevt;
  event->window = window;
  event->focused = focused;
}
void glfwWindowIconifyCallback(GLFWwindow* window, int iconified) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWwindowiconifyevt;
  event->window = window;
  event->iconified = iconified;
}
void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWframebuffersizeevt;
  event->window = window;
  event->width = width;
  event->height = height;
}
void glfwMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWmousebuttonevt;
  event->window = window;
  event->button = button;
  event->action = action;
  event->mods = mods;
}
void glfwCursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWcursorposevt;
  event->window = window;
  event->xpos = xpos;
  event->ypos = ypos;
}
void glfwCursorEnterCallback(GLFWwindow* window, int entered) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWcursorenterevt;
  event->window = window;
  event->entered = entered;
}
void glfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWscrollevt;
  event->window = window;
  event->xoffset = xoffset;
  event->yoffset = yoffset;
}
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWkeyevt;
  event->window = window;
  event->key = key;
  event->scancode = scancode;
  event->action = action;
  event->mods = mods;
}
void glfwCharCallback(GLFWwindow* window, unsigned int codepoint) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWcharevt;
  event->window = window;
  event->codepoint = codepoint;
}
void glfwCharModsCallback(GLFWwindow* window, unsigned int codepoint, int mods) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWcharmodsevt;
  event->window = window;
  event->codepoint = codepoint;
  event->mods = mods;
}
void glfwDropCallback(GLFWwindow* window, int count, const char** paths) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWdropevt;
  event->window = window;
  event->count = count;
  // TODO: make copy of paths.
  event->paths = paths;
}
void glfwMonitorCallback(GLFWmonitor* monitor, int action) {
  GLFWEvent* event = glfwEventPush();
  event->type = GLFWmonitorevt;
  event->monitor = monitor;
  event->event = action;
}
