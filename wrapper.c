#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "wrapper.h"

static GLFWEvent* GLFWEventHead = NULL;
static GLFWEvent* GLFWEventTail = NULL;

GLFWEvent* GLFWEventShift() {
  // printf("head=%p tail=%p\n", GLFWEventHead, GLFWEventTail);
  if (!GLFWEventHead) return NULL;
  GLFWEvent* event = GLFWEventHead;
  GLFWEventHead = GLFWEventHead->next;
  if (!GLFWEventHead) GLFWEventTail = NULL;
  return event;
}

void GLFWEventRelease(GLFWEvent* event) {
  // TODO: free string copies once we make them.
  // TODO: recycle these in some sort of free-list.
  free(event);
}

static GLFWEvent* GLFWEventPush() {
  GLFWEvent* event = malloc(sizeof(*event));
  // TODO: pull from free-list once implemented.
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
  printf("GLFWwindowposCallback\n");
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowposevt;
  event->window = window;
  event->xpos = xpos;
  event->ypos = ypos;
}
void GLFWwindowsizeCallback(GLFWwindow* window, int width, int height) {
  printf("GLFWwindowsizeCallback\n");
  GLFWEvent* event = GLFWEventPush();
  event->type = GLFWwindowsizeevt;
  event->window = window;
  event->width = width;
  event->height = height;
  glfwPostEmptyEvent();
}
// void GLFWwindowcloseCallback(GLFWwindow*) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWwindowrefreshCallback(GLFWwindow*) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWwindowfocusCallback(GLFWwindow*,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWwindowiconifyCallback(GLFWwindow*,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWframebuffersizeCallback(GLFWwindow*,int,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWmousebuttonCallback(GLFWwindow*,int,int,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWcursorposCallback(GLFWwindow*,double,double) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWcursorenterCallback(GLFWwindow*,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWscrollCallback(GLFWwindow*,double,double) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWkeyCallback(GLFWwindow*,int,int,int,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWcharCallback(GLFWwindow*,unsigned int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWcharmodsCallback(GLFWwindow*,unsigned int,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWdropCallback(GLFWwindow*,int,const char**) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
// void GLFWmonitorCallback(GLFWmonitor*,int) {
//   GLFWEvent* event = GLFWEventPush();
//   event->type = ;
// }
