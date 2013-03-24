#include <GL/glew.h>
#include <GL/gl.h>

#include <SDL/SDL.h>


#include <iostream>

int kScreenWidth = 1024;
int kScreenHeight = 768;
int kScreenBpp = 32;

bool InitSdl()
{
  if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
    return false;
  }
  if( SDL_SetVideoMode( kScreenWidth, kScreenHeight, kScreenBpp, SDL_OPENGL) == NULL ){
    return false;
  }
  SDL_WM_SetCaption("OpenGL Screen", NULL);
}

bool InitGl()
{
  GLenum error = glewInit();
  if( error != GLEW_OK ){
    return false;
  }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0,kScreenWidth,0.0f, kScreenHeight, 1.0f,-1.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.0f,0.0f,0.0f,1.0f);

  error = glGetError();
  if(error != GL_NO_ERROR){
    return false;
  }

  const GLubyte *renderer = glGetString( GL_RENDERER );
  const GLubyte *vendor = glGetString( GL_VENDOR );
  const GLubyte *glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );
  GLint major, minor;
  glGetIntegerv(GL_MAJOR_VERSION, &major);
  glGetIntegerv(GL_MINOR_VERSION, &minor);

  std::cout << "Vendor: " << vendor << std::endl;
  std::cout << "Renderer: " << renderer << std::endl;
  std::cout << "Version: " << major << "." << minor << std::endl;
  std::cout << "GLSL Version: " << glslVersion << std::endl;

  GLint num_extensions;
  glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
  for(int i = 0; i < num_extensions; i++){
    std::cout << glGetStringi( GL_EXTENSIONS, i) << std::endl;
  }

  return true;
}

int main()
{
  InitSdl();
  InitGl();
  bool quit = false;
  SDL_Event event;
  while(!quit){
    while( SDL_PollEvent( &event ) )
    {
      if( event.type == SDL_QUIT )
      {
        quit = true;
      }
    }
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f,0.0f,0.0f);
    glVertex3f(kScreenWidth/2,kScreenHeight,0.0f);
    glVertex3f(kScreenWidth,0.0f,0.0f);
    glEnd();
    SDL_GL_SwapBuffers();
  }
  SDL_Quit();
  return 0;
}
