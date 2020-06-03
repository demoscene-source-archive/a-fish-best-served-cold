/* File generated with Shader Minifier 1.1.1
 * http://www.ctrl-alt-test.fr
 */
#ifndef SHADER_CODE_H_
# define SHADER_CODE_H_

const char fragment_glsl[] = ""
 "#version 130\n"
 "float v(float x,float v,float z)"
 "{"
   "return-log(exp(-z*x)+exp(-z*v))/z;"
 "}"
 "float t(float x,float f,float d)"
 "{"
   "return-v(-x,-f,d);"
 "}"
 "uvec2 r=uvec2(uvec2(gl_FragCoord.xy+gl_TexCoord[0].xy));"
 "float t(in vec3 v)"
 "{"
   "return dot(v,v);"
 "}"
 "float v(in vec2 v)"
 "{"
   "return dot(v,v);"
 "}"
 "float t(in vec3 r,in float x,in float f,in float y)"
 "{"
   "vec2 m=vec2(length(r.xz),r.y),d=vec2(y,x),z=vec2(y-f,2.*x),i=vec2(m.x-min(m.x,m.y<0.?f:y),abs(m.y)-x),p=m-d+z*clamp(dot(d-m,z)/v(z),0.,1.);"
   "float g=p.x<0.&&i.y<0.?-1.:1.;"
   "return g*sqrt(min(v(i),v(p)));"
 "}"
 "uvec2 s(uvec2 v)"
 "{"
   "uint g[4],z=0U,m=-1640531527U;"
   "g[0]=-1556008596U;"
   "g[1]=-939442524U;"
   "g[2]=-1383041155U;"
   "g[3]=2123724318U;"
   "for(uint x=0U;x<4U;++x)"
     "z+=m,v.x+=(v.y<<4U)+g[0]^v.y+z^(v.y>>5U)+g[1],v.y+=(v.x<<4U)+g[2]^v.x+z^(v.x>>5U)+g[3];"
   "return v;"
 "}"
 "float s()"
 "{"
   "return r=s(r),float(r.x&1048575U)/(1U<<20U);"
 "}"
 "vec3 f(vec3 v)"
 "{"
   "float x=4096.*sin(dot(v,vec3(17,59.4,15)));"
   "return vec3(fract(64.*x),fract(8.*x),fract(512.*x))-.5;"
 "}"
 "float p(vec3 v)"
 "{"
   "vec3 x=floor(v+dot(v,vec3(1./3.))),m=v-x+dot(x,vec3(1./6.)),z=step(vec3(0),m-m.yzx),d=z*(1.-z.zxy),y=1.-z.zxy*(1.-z),i=m-d+vec3(1./6.),l=m-y+vec3(1./3.);"
   "vec4 g=pow(max(.6-vec4(dot(m,m),dot(i,i),dot(l,l),dot(m-.5,m-.5)),0.),vec4(4));"
   "return dot(g*vec4(dot(f(x),m),dot(f(x+d),i),dot(f(x+y),l),dot(f(x+1.),m-.5)),vec4(52));"
 "}"
 "mat2 m(float v)"
 "{"
   "return mat2(cos(v),sin(v),-sin(v),cos(v));"
 "}"
 "float f(in vec3 v,in vec3 x)"
 "{"
   "float z=length(v/x),m=length(v/(x*x));"
   "return z*(z-1.)/m;"
 "}"
 "float x(vec3 v)"
 "{"
   "return v.x=abs(v.x),mix(.1,1.,step(0,distance(v,vec3(.2,.65,.3))-.05));"
 "}"
 "vec2 m(vec2 v,vec2 r)"
 "{"
   "return r.x<v.x?r:v;"
 "}"
 "float g;"
 "vec2 n(vec3 r)"
 "{"
   "vec3 x=r;"
   "vec2 z=vec2(20,1);"
   "r.y-=.1;"
   "z.x=min(z.x,f(r-vec3(0,.5,0),vec3(.5,.6,.5)/2));"
   "z.x=v(z.x,f(r-vec3(0,.1,0.),vec3(.4)),7);"
   "z.x=t(z.x,-r.y-.1,20);"
   "z.x=min(z.x,f(r-vec3(0,.5,.2),vec3(.2,.13,.32))+.06);"
   "r.x=abs(r.x);"
   "vec3 i=r;"
   "i.xz*=m(-.2);"
   "float d=t(-i.y-.1,f(i-vec3(.17,-.07,.1),vec3(.2,.14,.35)),90);"
   "r.xy*=m(.35);"
   "z.x=v(z.x,f(r-vec3(.46,.15,0.),vec3(.07,.2,.1)),60);"
   "g=0.;"
   "if(d<z.x)"
     "g=1.;"
   "z.x=min(z.x,d);"
   "return z;"
 "}"
 "float f(vec3 v,vec3 x,float z)"
 "{"
   "vec3 r=abs(v)-x;"
   "return length(max(r,0.))-z+min(max(r.x,max(r.y,r.z)),0.);"
 "}"
 "vec2 n(vec3 r,int x)"
 "{"
   "float z=1.;"
   "vec2 g=vec2(20,0);"
   "float i=20;"
   "i=t(-(length(r.xz)-7.),-(length(vec2((m(-.55)*r.xz).x,r.y+.5))-1),32);"
   "i=v(i,r.y+.9,4.);"
   "r.y+=.9;"
   "vec2 d=n(r);"
   "d=m(d,vec2(length(vec2(max(0.,abs(r.y-.8)-.2),max(0.,length(r.xz)-.15)))-.05,2));"
   "d=m(d,vec2(length(vec2(max(0.,abs(r.y-.85)-.05),max(0.,length(r.xz)-.27)))-.05,2));"
   "i=v(i,length(vec2(max(0.,abs(r.y-.1)-.2),max(0.,length(r.xz-.93)-.5)))-.05,32);"
   "g=m(g,vec2(i,0));"
   "g=m(g,d);"
   "float y;"
   "vec3 l=r-vec3(1.06,.7,.8);"
   "l.xz*=m(.7);"
   "y=v(f(l,vec3(.5,.25,.2)/2.5),t(-(l-vec3(-.2,0,0)).zxy,.1,0.,.1),140);"
   "y+=p(r*22)*.01;"
   "g=m(g,vec2(y,4));"
   "g.x+=p(r*150)*.0005;"
   "g.x+=p(r*18)*.002;"
   "g.x+=p(r*48)*.00075;"
   "g.x+=p(r*6)*.004;"
   "g.x+=p(r*2)*.02;"
   "if(x==0)"
     "{"
       "r-=vec3(1,.7,.8);"
       "r.xz*=m(.45);"
       "float c=abs(f(r,vec3(.3),0.)-.05)-.015;"
       "c+=p(r*2)*.02;"
       "c+=p(r*6)*.004;"
       "c+=p(r*58)*.025*(pow(p(r*3+3)+p(r*6)/2.,3.)+.05);"
       "g=m(g,vec2(c,3));"
     "}"
   "g.x=min(g.x,20);"
   "return g;"
 "}"
 "float d(vec3 v)"
 "{"
   "return n(v,0).x;"
 "}"
 "vec3 h(vec3 v)"
 "{"
   "vec2 r=vec2(1e-05,0);"
   "return vec3(d(v+r.xyy),d(v+r.yxy),d(v+r.yyx))-vec3(d(v-r.xyy),d(v-r.yxy),d(v-r.yyx));"
 "}"
 "float d(const vec3 v,const vec3 z)"
 "{"
   "float r=.001,x=0.,g=2.5;"
   "for(int i=0;i<60;i++)"
     "{"
       "float y=r*float(i*i);"
       "vec3 d=z*y+v;"
       "float m=n(d,0).x;"
       "x+=-(m-y)*g;"
       "g*=.7;"
     "}"
   "return clamp(1.-5.*x,0.,1.);"
 "}"
 "float d(in vec3 v,in vec3 x,in float m,in float z)"
 "{"
   "float g=1.,i=m,d=1e+10;"
   "for(int r=0;r<32;r++)"
     "{"
       "float y=n(v+x*i,1).x,s=y*y/(2.*d),l=sqrt(y*y-s*s);"
       "g=min(g,.75*l/max(0.,i-s));"
       "d=y;"
       "i+=y;"
       "if(g<.0001||i>z)"
         "{"
           "break;"
         "}"
     "}"
   "return clamp(g,0.,1.);"
 "}"
 "vec2 e(vec2 v)"
 "{"
   "float x=v.x*acos(-1.)*2,d=sqrt(v.y);"
   "return vec2(cos(x),sin(x))*d;"
 "}"
 "void i(vec2 v)"
 "{"
   "float r=3.6;"
   "vec3 z=vec3(-.7,-.3,6.);"
   "vec2 i=e(vec2(s(),s()));"
   "vec3 m=z+vec3(i,0)*.03,l=z+vec3(v.xy*1.5,-6.),y=normalize(l-m);"
   "y.xz=mat2(cos(r),sin(r),sin(r),-cos(r))*y.xz;"
   "m.xz=mat2(cos(r),sin(r),sin(r),-cos(r))*m.xz;"
   "float f=20.;"
   "vec3 c=vec3(0),a=vec3(1);"
   "float U=0.,u=0.,k=1,t=0;"
   "for(int o=0;o<350;++o)"
     "{"
       "vec2 C=n(m+y*U,0);"
       "u=C.x;"
       "t=C.y;"
       "if(abs(u)<1e-05)"
         "{"
           "if(C.y==3.)"
             "{"
               "U+=.0001;"
               "vec3 F=normalize(h(m+y*U));"
               "y=s()>.8?reflect(y,F):k>0.?refract(y,F*-sign(dot(y,F)),1./1.01):y;"
               "k=-k;"
               "c+=pow(max(0.,dot(F,normalize(-y+normalize(vec3(4.5,2,1))))),120.)*18;"
               "c+=pow(max(0.,dot(F,normalize(-y+normalize(vec3(4.5,2,3))))),220.)*12;"
               "a*=vec3(.95,.95,1);"
             "}"
           "else"
             "{"
               "break;"
             "}"
         "}"
       "U+=u*.8*k;"
       "if(U>25.)"
         "{"
           "break;"
         "}"
     "}"
   "if(U>25.)"
     "gl_FragColor.xyz=vec3(.25)*0;"
   "else"
     "{"
       "vec3 F=m+y*U,o=normalize(h(F));"
       "gl_FragColor.xyz=vec3(1-dot(-y,o))*.3+x(F-vec3(0,-.9,0))*(.75+.3*dot(o,normalize(vec3(1))))*1.1;"
       "F.y+=.9;"
       "if(t>.5)"
         "{"
           "gl_FragColor.xyz*=mix(vec3(1,.7,.4),mix(vec3(1),vec3(.5,.5,1),max(step(0.,-F.z),step(.2,length((F.xy-vec2(0,.26))*vec2(1,.99))))),max(step(0.,-F.z),step(.2,length((F.xy-vec2(0,.6))*vec2(1.5,3)))));"
           "if(g>.5)"
             "gl_FragColor.xyz=vec3(1,.7,.4);"
         "}"
       "else"
         " gl_FragColor.xyz*=vec3(.7,.75,1);"
       "if(t==2)"
         "gl_FragColor.xyz=vec3(.7,1,.4)/2;"
       "if(t==4)"
         "{"
           "gl_FragColor.xyz=vec3(1.,.4,.2)*2*smoothstep(.5,.8,F.y);"
           "if(length(F.xy-vec2(1.12,.73))<.03)"
             "gl_FragColor.xyz=vec3(1);"
           "if(length(F.xy-vec2(1.12,.73))<.02)"
             "gl_FragColor.xyz=vec3(.01);"
         "}"
       "F.y-=.9;"
       "gl_FragColor.xyz*=mix(.4,1.,d(F,normalize(vec3(1,2,1)),.0001,4.))*1.1;"
       "gl_FragColor.xyz*=mix(.1,1.,pow(clamp(d(F,normalize(o+.25)),0,1),2.5));"
       "gl_FragColor.xyz*=1.+p(F*6)*.1;"
       "gl_FragColor.xyz*=1-smoothstep(0.,8.,length(F))+smoothstep(9.,19.,length(F))*smoothstep(0.,1.,-F.y+F.z/2+5)/2;"
       "gl_FragColor.xyz+=c;"
     "}"
   "gl_FragColor.xyz=max(gl_FragColor.xyz*a,0.);"
   "gl_FragColor.xyz+=.01;"
   "gl_FragColor.xyz-=vec3(dot(gl_FragColor.xyz,vec3(1./3.)))*.1;"
 "}"
 "void main()"
 "{"
   "vec2 r=(gl_FragCoord.xy+vec2(s(),s())*1.5)/vec2(1920,1080)*2-1.;"
   "if(abs(r.x)>2./3.||abs(r.y)>1.)"
     "discard;"
   "r*=1.5;"
   "r.y/=1.77778;"
   "vec2 v=r.xy;"
   "vec3 g=vec3(0);"
   "gl_FragColor.xyz=vec3(0);"
   "i(v);"
   "g+=clamp(gl_FragColor.xyz,0.,1.);"
   "gl_FragColor.xyz=g;"
   "gl_FragColor.xyz*=1.-(pow(abs(v.x),3.)*2+pow(abs(v.y*1.5),3.))*.15;"
   "gl_FragColor.xyz+=vec3(1,.5,.2)*.01;"
   "gl_FragColor.xyz+=vec3(1,.9,.9)*p(vec3(v*200,0))*.002;"
   "gl_FragColor.xyz/=(gl_FragColor.xyz+.75)*.55;"
   "gl_FragColor.xyz=pow(gl_FragColor.xyz,vec3(1./2.2));"
   "gl_FragColor/=gl_TexCoord[0].z;"
 "}";

#endif // SHADER_CODE_H_
