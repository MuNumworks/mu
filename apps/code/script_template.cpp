#include "script_template.h"

namespace Code {

constexpr ScriptTemplate emptyScriptTemplate(".py", "\x01" R"(from math import *)" "\n" R"(from mu import *)" "\n");

// constexpr ScriptTemplate pygameScriptTemplate("pygame.py", "\x01" R"(from kandinsky import fill_rect as fl,fill_circle as fc,draw_string as dr,draw_line as dl,wait_vblank
// from ion import*
// import time as sys_time
// K_OK=KEY_OK
// K_BACK=KEY_BACK
// K_LEFT=KEY_LEFT
// K_RIGHT=KEY_RIGHT
// K_UP=KEY_UP
// K_DOWN=KEY_DOWN
// LOC_KEYS_=K_OK,K_DOWN,K_UP,K_RIGHT,K_LEFT
// FULLSCREEN=1
// NOFRAME=16
// QUIT=268435456
// KEYDOWN=256
// KEYUP=512
// __all__=['Display','Display.set_mode','Display.set_caption','Display.flip','Surface','Surface.fillRect','Rect.colliderect','Rect.move_to','Rect.move','draw','draw.rect','draw.line','draw.circle','time','time.delay','time.Clock','Clock','Clock.tick','Clock.get_fpskey','key.get_pressed']
// presses={key:[None,None]for key in LOC_KEYS_}
// def presses_update():
// 	for key in presses.keys():presses[key][-2]=presses[key][-1];presses[key][-1]=keydown(key)
// click=lambda key:presses[key][-1]and not presses[key][-2]
// release=lambda key:presses[key][-2]and not presses[key][-1]
// class init:
// 	def __init__(self):return
// class Surface:
// 	def __init__(self,width,height):self.width=width;self.height=height;self.to_do={'rect':list(),'line':list(),'circle':list(),'polygon':list()};return
// 	def fill(self,color):Check._color(color);fl(0,display.YPLUS,self.width,self.height,color);return
// class Check:
// 	def __init__():return
// 	def _int(*args):
// 		for i in args:
// 			if type(i)!=int:raise ValueError('An integer was expected instead of %s'%i)
// 		return
// 	def _color(*args):
// 		for i in args:
// 			if not(type(i)==str and len(i)==7 and i[0]=='#'or type(i)==tuple):raise ValueError('A tuple was expected instead of %s'%i)
// 		return
// 	def _rect(*args):
// 		for i in args:
// 			if type(i)!=Rect:raise ValueError('A pygame.Rect object was expected instead of %s'%i)
// 		return
// 	def _tuple(*args):
// 		for i in args:
// 			if type(i)!=tuple:raise ValueError('A tuple was expected instead of %s'%i)
// 		return
// 	def _surface(*args):
// 		for i in args:
// 			if type(i)!=Surface:raise ValueError('A pygame.Surface object was expected instead of %s'%i)
// 		return
// class Display:
// 	def __init__(self):self.width,self.height=None,None;self.caption='Pygame window';self.YPLUS=18;self.surface=None;return
// 	def __refresh_screen(self):
// 		if not self.surface:fl(0,self.YPLUS,self.width,self.height,'#000000')
// 		if self.YPLUS:fl(0,0,self.width,self.YPLUS,'#ffffff');dr(self.caption[:self.width//10-1],5,0)
// 		return
// 	def set_caption(self,caption):self.caption=caption;self.__refresh_screen();return
// 	def set_mode(self,size,flags=0):
// 		self.width,self.height=size;Check._int(self.width,self.height)
// 		if flags&NOFRAME:self.YPLUS=0
// 		if flags&FULLSCREEN:self.width=320;self.height=222-self.YPLUS
// 		if self.height+self.YPLUS>222:self.height=222
// 		self.surface=Surface(self.width,self.height);self.__refresh_screen();return self.surface
// 	def flip(self):self.__refresh_screen();wait_vblank();[fl(*rect)for rect in self.surface.to_do['rect']];[fc(*circle)for circle in self.surface.to_do['circle']];[dl(*line)for line in self.surface.to_do['line']];self.surface.to_do={'rect':list(),'circle':list(),'line':list(),'polygon':list()};return
// 	def get_surface(self):return self.surface
// class draw:
// 	@staticmethod
// 	def rect(surface,color,rect):Check._color(color);Check._rect(rect);surface.to_do['rect'].append(rect._get_infos(display.YPLUS)+(color,));return
// 	@staticmethod
// 	def circle(surface,color,pos,radius,width=0):Check._color(color);Check._int(radius,width);Check._tuple(pos);surface.to_do['circle'].append((pos[0],pos[1]+display.YPLUS,radius,color));return
// 	@staticmethod
// 	def line(surface,color,startpos,endpos):Check._color(color);Check._tuple(startpos,endpos);surface.to_do['line'].append((startpos[0],startpos[1]+display.YPLUS,endpos[0],endpos[1]+display.YPLUS,color));return
// class Rect:
// 	def __init__(self,x,y,width,height):self.x,self.y=x,y;self.width,self.height=width,height
// 	def __str__(self):return'Rect({%s}, {%s}, {%s}, {%s})'%(self.x,self.y,self.width,self.height)
// 	def _get_infos(self,yplus=0):Check._int(yplus);return self.x,self.y+yplus,self.width,self.height
// 	def move(self,x,y):Check._int(x,y);return Rect(self.x+x,self.y+y,self.width,self.height)
// 	def move_to(self,x,y):Check._int(x,y);self.x,self.y=x,y;return
// 	def colliderect(self,other):return mu.colliderect((self.x,self.y,self.width,self.height),(other.x,other.y,other.width,other.height))
// class key:
// 	@staticmethod
// 	def get_pressed():return{key:keydown(key)for key in LOC_KEYS_}
// class time:
// 	@staticmethod
// 	def Clock():return Clock()
// 	@staticmethod
// 	def delay(delay):sys_time.sleep(delay/1000);return
// class Clock:
// 	def __init__(self):self.start_time=sys_time.monotonic();self.last_elapse=None;self.elapsed_time=[];return
// 	def tick(self,fps=60):
// 		if not self.last_elapse:self.last_elapse=self.start_time
// 		while sys_time.monotonic()-self.last_elapse<1/fps:0
// 		self.elapsed_time.append(sys_time.monotonic()-self.last_elapse)
// 		if len(self.elapsed_time)>30:del self.elapsed_time[0]
// 		self.last_elapse=sys_time.monotonic();return
// 	def get_fps(self):return 1/(sum(self.elapsed_time)/len(self.elapsed_time)+1e-05+1e-05)
// display=Display()
// event=Events())");

constexpr ScriptTemplate perfScriptTemplate("blue.py", "\x01" R"(_D='#000000'
_C=True
_B=False
_A=None
from time import monotonic
from kandinsky import fill_rect
from ion import keydown,KEY_OK,KEY_DOWN,KEY_UP,KEY_RIGHT,KEY_LEFT
try:from kandinsky import fill_circle,draw_circle
except ImportError:
  from kandinsky import set_pixel
  def fill_circle(x,y,r,color):
    C=color;A,B=0,r;D=1-r
    while A<=B:
      fill_rect(x-A,y+B,2*A+1,1,C);fill_rect(x-A,y-B,2*A+1,1,C);fill_rect(x-B,y+A,2*B+1,1,C);fill_rect(x-B,y-A,2*B+1,1,C)
      if D<0:D+=2*A+3
      else:D+=2*(A-B)+5;B-=1
      A+=1
  def draw_circle(x,y,r,color):
    C=color;A,B=0,r
    while A<=B:
      set_pixel(x+A,y+B,C);set_pixel(x-A,y-B,C);set_pixel(x+B,y+A,C);set_pixel(x-B,y-A,C);set_pixel(x+B,y-A,C);set_pixel(x-B,y+A,C);set_pixel(x+A,y-B,C);set_pixel(x-A,y+B,C);D=(A+1)*(A+1)+(B-.5)*(B-.5)-r*r
      if D>0:B-=1
      A+=1
class Clock:
  def __init__(A):A.__creationTimeStamp=monotonic()
  def getElapsedTime(A):return monotonic()-A.__creationTimeStamp
  def restart(A):B=A.getElapsedTime();A.__creationTimeStamp=monotonic();return B
class Rect:
  def __init__(A,x,y,width,height,color=_D):A.__x=x;A.__y=y;A.__w=width;A.__h=height;A.__color=color;A.__origin=0,0;A.__isDirty=_C
  def getBounds(A):return tuple(A.__x,A.__y,A.__w,A.__h)
  def moveBy(A,x,y):A.__x+=x;A.__y+=y;return A
  def resizeBy(A,x,y):A.__w+=x;A.__h+=y;return A
  def setPosition(A,x,y):A.__x=x;A.__y=y;return A
  def getPosition(A):return A.__x,A.__y
  def setSize(A,width,height):A.__w=width;A.__h=height;return A
  def getSize(A):return A.__w,A.__h
  def setColor(A,color):A.__color=color;return A
  def getColor(A):return A.__color
  def setOrigin(A,origin):
    B=origin
    if not(0<B[0]<A.__w and 0<B[1]<A.__h):return
    A.__origin=B;return A
  def getOrigin(A):return A.__origin
  def collideRect(A,target):B,C,D,E=target.getBounds();return A.__x<D and A.__w>B and A.__y<E and A.__h>C
  def markAsDirty(A):A.__isDirty=_C;return A
  def draw(A):
    if A.__isDirty:fill_rect(int(A.__x-A.__origin[0]),int(A.__y-A.__origin[1]),int(A.__w),int(A.__h),A.__color);A.__isDirty=_B
    return A
  def copy(A):return Rect(A.__x,A.__y,A.__w,A.__h,A.__color)
class Circle:
  def __init__(A,x,y,radius,color=_D,outlineColor=_A):A.__x=x;A.__y=y;A.__r=radius;A.__origin=0,0;A.__color=color;A.__outlineColor=outlineColor;A.__isDirty=_C
  def moveBy(A,x,y):A.__x+=x;A.__y+=y;return A
  def setPosition(A,x,y):A.__x=x;A.__y=y;return A
  def getPosition(A):return A.__x,A.__y
  def setRadius(A,radius):A.__r=radius;return A
  def getRadius(A):return A.__r
  def setOrigin(A,origin):
    B=origin;C,D=B
    if not(0<=C<=A.__r*2 and 0<=D<=A.__r*2):return
    A.__origin=B;return A
  def getOrigin(A):return A.__origin
  def setColor(A,color):A.__color=color;return A
  def getColor(A):return A.__color
  def setOutlineColor(A,color):A.__outlineColor=color;return A
  def getOutlineColor(A):return A.__outlineColor
  def collideCircle(A,target):B=target;E,F=B.getPosition();G=B.getRadius();C=E-A.__x;D=F-A.__y;return C*C+D*D<=(G+A.__r)**2
  def collideOutlineCircle(A,target):B=target;G,H=B.getPosition();C=B.getRadius();D=G-A.__x;E=H-A.__y;F=D*D+E*E;return F<=(A.__r+C)**2 and F>=(A.__r-C)**2
  def collideRect(A,target):B=target;C,D=A.__x,A.__y;E=A.__r;F,G=B.getPosition();J,K=B.getSize();L=max(F,min(C,F+J));M=max(G,min(D,G+K));H=C-L;I=D-M;return H*H+I*I<=E*E
  def markAsDirty(A):A.__isDirty=_C;return A
  def draw(A):
    if A.__isDirty:
      if A.__color!=_A:fill_circle(int(A.__x-A.__origin[0]),int(A.__y-A.__origin[1]),A.__r,A.__color)
      if A.__outlineColor!=_A:draw_circle(int(A.__x-A.__origin[0]),int(A.__y-A.__origin[1]),int(A.__r),A.__outlineColor)
      A.__isDirty=_B
    return A
  def copy(A):return Circle(A.__x,A.__y,A.__r,A.__color,A.__outlineColor)
class Keyboard:
  def __init__(A):A.__presses={A:[_A,_A]for A in(KEY_OK,KEY_UP,KEY_DOWN,KEY_LEFT,KEY_RIGHT)}
  def addKey(A,keycode):
    B=keycode
    if B not in A.__presses.keys():A.__presses[B]=[_A,_A]
    return A
  def update(A):
    for B in A.__presses.keys():A.__presses[B][-2]=A.__presses[B][-1];A.__presses[B][-1]=keydown(B)
    return A
  def click(A,keycode):
    B=keycode
    if not B in A.__presses.keys():return _B
    return A.__presses[B][-1]and not A.__presses[B][-2]
  def release(A,keycode):
    B=keycode
    if not B in A.__presses.keys():return _B
    return A.__presses[B][-2]and not A.__presses[B][-1]
  def press(A,keycode):
    B=keycode
    if not B in A.__presses.keys():return _B
    return A.__presses[B][-1]
  def getTargetedKeys(A):return A.__presses.keys()
def clear(color=(0,0,0)):fill_rect(0,0,333,222,color)
def bench(function,*B):A=monotonic();function(*B);A=monotonic()-A;print('Take %.5f seconds.'%A);return A)");


const ScriptTemplate * ScriptTemplate::Empty() {
  return &emptyScriptTemplate;
}

// const ScriptTemplate * ScriptTemplate::Pygame() {
//   return &pygameScriptTemplate;
// }
const ScriptTemplate * ScriptTemplate::Blue() {
  return &perfScriptTemplate;
}

}
