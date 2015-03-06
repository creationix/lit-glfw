#include "wrapper.h"
#include <stdlib.h>
#include <assert.h>

static GLFWEvent* GLFWEventHead = NULL;
static GLFWEvent* GLFWEventTail = NULL;

// Poll of used instances ready for reuse.
static GLFWEvent* GLFWEventPool = NULL;
static int GLFWEventPoolSize = 0;
#define GLFWEventPoolMaxSize 10

GLFWEvent* GLFWEventShift() {
  if (!GLFWEventHead) return NULL;
  GLFWEvent* event = GLFWEventHead;
  GLFWEventHead = GLFWEventHead->next;
  if (!GLFWEventHead) GLFWEventTail = NULL;
  return event;
}

void GLFWEventRelease(GLFWEvent* event) {
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

static GLFWEvent* GLFWEventPush() {
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

void GLFWerrorCallback(int error, const char* description) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWerrorevt;
  event->error = error;
  event->description = description;
}
void GLFWwindowposCallback(GLFWwindow* window, int xpos, int ypos) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowposevt;
  event->window = window;
  event->xpos = xpos;
  event->ypos = ypos;
}
void GLFWwindowsizeCallback(GLFWwindow* window, int width, int height) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowsizeevt;
  event->window = window;
  event->width = width;
  event->height = height;
}
void GLFWwindowcloseCallback(GLFWwindow* window) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowcloseevt;
  event->window = window;
}
void GLFWwindowrefreshCallback(GLFWwindow* window) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowrefreshevt;
  event->window = window;
}
void GLFWwindowfocusCallback(GLFWwindow* window, int focused) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowfocusevt;
  event->window = window;
  event->focused = focused;
}
void GLFWwindowiconifyCallback(GLFWwindow* window, int iconified) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowiconifyevt;
  event->window = window;
  event->iconified = iconified;
}
void GLFWframebuffersizeCallback(GLFWwindow* window, int width, int height) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWframebuffersizeevt;
  event->window = window;
  event->width = width;
  event->height = height;
}
void GLFWmousebuttonCallback(GLFWwindow* window, int button, int action, int mods) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWmousebuttonevt;
  event->window = window;
  event->button = button;
  event->action = action;
  event->mods = mods;
}
void GLFWcursorposCallback(GLFWwindow* window, double xpos, double ypos) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWcursorposevt;
  event->window = window;
  event->xpos = xpos;
  event->ypos = ypos;
}
void GLFWcursorenterCallback(GLFWwindow* window, int entered) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWcursorenterevt;
  event->window = window;
  event->entered = entered;
}
void GLFWscrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWscrollevt;
  event->window = window;
  event->xoffset = xoffset;
  event->yoffset = yoffset;
}
void GLFWkeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWkeyevt;
  event->window = window;
  event->key = key;
  event->scancode = scancode;
  event->action = action;
  event->mods = mods;
}
void GLFWcharCallback(GLFWwindow* window, unsigned int codepoint) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWcharevt;
  event->window = window;
  event->codepoint = codepoint;
}
void GLFWcharmodsCallback(GLFWwindow* window, unsigned int codepoint, int mods) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWcharmodsevt;
  event->window = window;
  event->codepoint = codepoint;
  event->mods = mods;
}
void GLFWdropCallback(GLFWwindow* window, int count, const char** paths) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWdropevt;
  event->window = window;
  event->count = count;
  // TODO: make copy of paths.
  event->paths = paths;
}
void GLFWmonitorCallback(GLFWmonitor* monitor, int action) {
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWmonitorevt;
  event->monitor = monitor;
  event->event = action;
}
