"#version 130\n"
"\n"
"float smin(float a,float b,float k){ return -log(exp(-k*a)+exp(-k*b))/k;}//from iq\n"
"float smax(float a,float b,float k){ return -smin(-a,-b,k);}\n"
"\n"
"uvec2 rstate=uvec2(uvec2(gl_FragCoord.xy)+4096U);\n"
"\n"
"float dot2( in vec3 v ) { return dot(v,v); }\n"
"float dot2( in vec2 v ) { return dot(v,v); }\n"
"float sdCappedCone( in vec3 p, in float h, in float r1, in float r2 )\n"
"{\n"
"    vec2 q = vec2( length(p.xz), p.y );\n"
"\n"
"    vec2 k1 = vec2(r2,h);\n"
"    vec2 k2 = vec2(r2-r1,2.0*h);\n"
"    vec2 ca = vec2(q.x-min(q.x,(q.y < 0.0)?r1:r2), abs(q.y)-h);\n"
"    vec2 cb = q - k1 + k2*clamp( dot(k1-q,k2)/dot2(k2), 0.0, 1.0 );\n"
"    float s = (cb.x < 0.0 && ca.y < 0.0) ? -1.0 : 1.0;\n"
"    return s*sqrt( min(dot2(ca),dot2(cb)) );\n"
"}\n"
"\n"
"\n"
"// Tiny Encryption Algorithm for random numbers: \n"
"uvec2 encrypt(uvec2 v)\n"
"{\n"
"    uint k[4],sum=0U,delta=0x9e3779b9U;\n"
"    k[0] = 0xA341316CU;\n"
"    k[1] = 0xC8013EA4U;\n"
"    k[2] = 0xAD90777DU;\n"
"    k[3] = 0x7E95761EU;\n"
"    for(uint i=0U;i<4U;++i)\n"
"    {\n"
"        sum += delta;\n"
"        v.x += ((v.y << 4U) + k[0]) ^ (v.y + sum) ^ ((v.y >> 5U) + k[1]);\n"
"        v.y += ((v.x << 4U) + k[2]) ^ (v.x + sum) ^ ((v.x >> 5U) + k[3]);\n"
"    }\n"
"\n"
"    return v;\n"
"}\n"
"\n"
"float rand()\n"
"{\n"
"    rstate=encrypt(rstate);\n"
"    return float(rstate.x&0xfffffU)/(1U<<20U);\n"
"}\n"
"\n"
"float hash(float n)\n"
"{\n"
"    return fract(sin(n)*43758.5453);\n"
"}\n"
"\n"
"float noise(vec2 p)\n"
"{\n"
"    return hash(p.x + p.y*57.0);\n"
"}\n"
"\n"
"float smoothNoise2(vec2 p)\n"
"{\n"
"    vec2 p0 = floor(p + vec2(0.0, 0.0));\n"
"    vec2 p1 = floor(p + vec2(1.0, 0.0));\n"
"    vec2 p2 = floor(p + vec2(0.0, 1.0));\n"
"    vec2 p3 = floor(p + vec2(1.0, 1.0));\n"
"\n"
"    vec2 pf = smoothstep(0.0, 1.0, fract(p));\n"
"\n"
"    return mix( mix(noise(p0), noise(p1), pf.x), \n"
"               mix(noise(p2), noise(p3), pf.x), pf.y);\n"
"}\n"
"\n"
"float smoothNoise3(vec3 p)\n"
"{\n"
"    vec2 offset = vec2(1.0);\n"
"    float f0 = smoothNoise2(p.xy + floor(p.z) * offset);\n"
"    float f1 = smoothNoise2(p.xy + (floor(p.z) + 1.0) * offset);\n"
"\n"
"    return mix(f0, f1, smoothstep(0.0, 1.0, fract(p.z)));\n"
"}\n"
"\n"
"\n"
"/*   NIKAT'S 3D SIMPLEX NOISE   */\n"
"vec3 hash3(vec3 c){\n"
"    float j = 4096.0*sin(dot(c,vec3(17, 59.4, 15)));\n"
"    return vec3(fract(64.0*j), fract(8.0*j), fract(512.0*j))-0.5;\n"
"}\n"
"\n"
"float simplex(vec3 p){\n"
"    vec3 s = floor(p + dot(p, vec3(1.0/3.0)));\n"
"    vec3 x = p - s + dot(s, vec3(1.0/6.0));\n"
"    vec3 e = step(vec3(0), x - x.yzx);\n"
"    vec3 i1 = e*(1.0 - e.zxy);\n"
"    vec3 i2 = 1.0 - e.zxy*(1.0 - e);\n"
"    vec3 x1 = x - i1 + vec3(1.0/6.0);\n"
"    vec3 x2 = x - i2 + vec3(1.0/3.0);\n"
"    vec4 w = pow(max(0.6 - vec4(dot(x, x), dot(x1, x1), dot(x2, x2), dot(x-0.5,x-0.5)), 0.0),vec4(4));\n"
"    return dot(w*vec4(dot(hash3(s),x),dot(hash3(s+i1),x1),dot(hash3(s+i2),x2),dot(hash3(s+1.0),x-0.5)),vec4(52));\n"
"}\n"
"\n"
"\n"
"mat2 rotmat(float a)\n"
"{\n"
"    return mat2(cos(a),sin(a),-sin(a),cos(a));\n"
"}\n"
"\n"
"float getLine(float cx,float r)\n"
"{\n"
"    return r * cx / sqrt(pow(cx,4.) - pow(r,2.) * pow(cx,2.));\n"
"}\n"
"\n"
"float roundedCone(vec3 p,vec3 o,vec3 d,float r,float q)\n"
"{\n"
"    float t=dot(p-o,d)/length(d);\n"
"    float e=distance(p,o+d*t/length(d));\n"
"\n"
"    float fx=length(d);\n"
"\n"
"    float a = 1. / (r*r) - 1. / (q*q);\n"
"    float b = -2.*fx / (q*q);\n"
"    float c = -(fx*fx) / (q*q);\n"
"    float x0 = (-b+sqrt(b*b-4*a*c))/(2*a);\n"
"\n"
"    float t2=getLine(x0,r);\n"
"\n"
"    float dd=x0/(1*1+t2*t2);\n"
"    float dd2=(x0+fx)/(1*1+t2*t2);\n"
"\n"
"    float f = t+x0;\n"
"\n"
"    float sd = min(distance(p,o)-r,distance(p,o+d)-q);\n"
"\n"
"    if(f>=dd&&f<=dd2)\n"
"        return min(sd,dot(vec2(t+x0,e),normalize(vec2(-t2,1))));\n"
"    return sd;\n"
"}\n"
"\n"
"\n"
"float sdEllipsoid( in vec3 p, in vec3 r )\n"
"{\n"
"    float k0 = length(p/r);\n"
"    float k1 = length(p/(r*r));\n"
"    return k0*(k0-1.0)/k1;\n"
"}\n"
"\n"
"\n"
"float eyes(vec3 p)\n"
"{\n"
"    p.x=abs(p.x);\n"
"    return mix(.1,1.,step(0,distance(p,vec3(.2,.65,.3))-.05));\n"
"}\n"
"\n"
"vec2 U(vec2 a,vec2 b)\n"
"{\n"
"    return b.x<a.x?b:a;\n"
"    return mix(a, b, step(b.x, a.x));\n"
"}\n"
"\n"
"float feet;\n"
"vec2 penguinf(vec3 p)\n"
"{\n"
"    vec3 op=p;\n"
"    vec2 d=vec2(20,1);\n"
"\n"
"    p.y-=.1;\n"
"\n"
"    d.x=min(d.x,sdEllipsoid(p-vec3(0,.5,0),vec3(.5,.6,.5)/2));\n"
"\n"
"    d.x=smin(d.x,sdEllipsoid(p-vec3(0,.1,0.),vec3(.4)),7);\n"
"\n"
"    d.x=smax(d.x,-p.y-.1,20);\n"
"\n"
"    d.x=min(d.x,sdEllipsoid(p-vec3(0,.5,0.2),vec3(.2,.13,.32))+.06);\n"
"\n"
"    p.x=abs(p.x);\n"
"\n"
"    vec3 p2=p;\n"
"    p2.xz*=rotmat(-.2);   \n"
"    float feetd=smax(-p2.y-.1,sdEllipsoid(p2-vec3(.17,-.07,0.1),vec3(.2,.14,.35)),90);\n"
"\n"
"    p.xy*=rotmat(.35);\n"
"    d.x=smin(d.x,sdEllipsoid(p-vec3(.46,.15,0.),vec3(.07,.2,.1)),60);\n"
"\n"
"    feet=0.;\n"
"    if(feetd<d.x)feet=1.;\n"
"    d.x=min(d.x,feetd);\n"
"\n"
"    return d;\n"
"}\n"
"\n"
"float sdRoundBox( vec3 p, vec3 b, float r )\n"
"{\n"
"    vec3 d = abs(p) - b;\n"
"    return length(max(d,0.0)) - r\n"
"        + min(max(d.x,max(d.y,d.z)),0.0); // remove this line for an only partially signed sdf \n"
"}\n"
"\n"
"\n"
"vec2 f(vec3 p,int noice)\n"
"{\n"
"    float an=1.;\n"
"\n"
"    vec2 d=vec2(20,0);\n"
"\n"
"    float roomd=20;\n"
"\n"
"    roomd=smax(-(length(p.xz)-7.),-(length(vec2((rotmat(-.55)*p.xz).x,p.y+.5))-1),32);\n"
"\n"
"    roomd=smin(roomd,p.y+.9,4.);\n"
"\n"
"    p.y+=.9;\n"
"    vec2 penguind=penguinf(p);\n"
"\n"
"    // hat\n"
"    penguind=U(penguind,vec2(length(vec2(max(0.,abs(p.y-.8)-.2),max(0.,length(p.xz)-.15)))-.05,2));\n"
"    penguind=U(penguind,vec2(length(vec2(max(0.,abs(p.y-.85)-.05),max(0.,length(p.xz)-.27)))-.05,2));\n"
"\n"
"    roomd=smin(roomd,length(vec2(max(0.,abs(p.y-.1)-.2),max(0.,length(p.xz-.93)-.5)))-.05,32);\n"
"\n"
"    d=U(d,vec2(roomd,0));\n"
"    d=U(d,penguind);\n"
"\n"
"    // fish\n"
"    float fishd;\n"
"    vec3 p2=p-vec3(1.06,.7,.8);\n"
"    p2.xz*=rotmat(.7);\n"
"    fishd=smin( sdEllipsoid(p2,vec3(.5,.25,.2)/2.5),\n"
"               sdCappedCone(-(p2-vec3(-0.2,0,0)).zxy,.1,0.,.1), 140);\n"
"    fishd+=simplex(p*22)*.01;\n"
"\n"
"    d=U(d,vec2(fishd,4));\n"
"\n"
"    d.x+=simplex(p*150)*.0005;\n"
"    d.x+=simplex(p*18)*.002;\n"
"    d.x+=simplex(p*48)*.00075;\n"
"    d.x+=simplex(p*6)*.004;\n"
"    d.x+=simplex(p*2)*.02;\n"
"\n"
"    if(noice==0)\n"
"    {\n"
"        p-=vec3(1,.7,.8);\n"
"        p.xz*=rotmat(.45);\n"
"        float iced=abs(sdRoundBox(p,vec3(.3),.0)-.05)-.015;\n"
"        iced+=simplex(p*2)*.02;\n"
"        iced+=simplex(p*6)*.004;\n"
"        iced+=simplex(p*58)*.025*(pow(simplex(p*3+3)+simplex(p*6)/2.,3.)+0.05);\n"
"        d=U(d,vec2(iced,3));\n"
"    }\n"
"\n"
"    d.x=min(d.x,20);\n"
"\n"
"    return d;\n"
"}\n"
"\n"
"float dist(vec3 p){return f(p,0).x;}\n"
"\n"
"vec3 distG(vec3 p)\n"
"{\n"
"    vec2 e=vec2(1e-5,0);\n"
"    return vec3(dist(p+e.xyy),dist(p+e.yxy),dist(p+e.yyx))-\n"
"        vec3(dist(p-e.xyy),dist(p-e.yxy),dist(p-e.yyx));\n"
"}\n"
"\n"
"\n"
"float calcAO( const vec3 pos, const vec3 nor ) {\n"
"    //return 1.;  \n"
"    float aodet=0.001;\n"
"    float totao = 0.0;\n"
"    float sca = 2.5;\n"
"    for( int aoi=0; aoi<60; aoi++ ) {\n"
"        float hr = aodet*float(aoi*aoi);\n"
"        vec3 aopos =  nor * hr + pos;\n"
"        float dd = f( aopos, 0 ).x;\n"
"        totao += -(dd-hr)*sca;\n"
"        sca *= 0.7;\n"
"    }\n"
"    return clamp( 1.0 - 5.0*totao, 0., 1.0 );\n"
"}\n"
"\n"
"\n"
"// Soft shadow for SDF, from IQ and Sebastian Aaltonen:\n"
"// https://www.shadertoy.com/view/lsKcDD\n"
"float calcSoftshadow( in vec3 ro, in vec3 rd, in float mint, in float tmax)\n"
"{\n"
"    float res = 1.0;\n"
"    float t = mint;\n"
"    float ph = 1e10; // big, such that y = 0 on the first iteration\n"
"    for( int i=0; i<32; i++ )\n"
"    {\n"
"        float h = f( ro + rd*t, 1 ).x;\n"
"\n"
"		// use this if you are getting artifact on the first iteration, or unroll the\n"
"		// first iteration out of the loop\n"
"		//float y = (i==0) ? 0.0 : h*h/(2.0*ph); \n"
"\n"
"		float y = h*h/(2.0*ph);\n"
"		float d = sqrt(h*h-y*y);\n"
"		res = min( res, 0.75*d/max(0.0,t-y) );\n"
"		ph = h;\n"
"\n"
"        t += h;\n"
"\n"
"        if( res<0.0001 || t>tmax )\n"
"		{\n"
"			break;\n"
"		}\n"
"\n"
"    }\n"
"    return clamp( res, 0.0, 1.0 );\n"
"}\n"
"\n"
"vec2 disc(vec2 uv)\n"
"{\n"
"    float a = uv.x * acos(-1.) * 2;\n"
"    float r = sqrt(uv.y);\n"
"    return vec2(cos(a), sin(a)) * r;\n"
"}\n"
"\n"
"vec2 polygon(vec2 uv, float n)\n"
"{\n"
"    float s = 1. / n;\n"
"    float b = 2. / n * acos(-1.);\n"
"    float a = b * floor(uv.y * n);\n"
"    uv = vec2(uv.x, mod(uv.y, s) / s);\n"
"\n"
"    if (uv.x + uv.y > 1.)\n"
"        uv = vec2(1) - uv;\n"
"\n"
"    uv = vec2(uv.x, 0) + vec2(cos(b), sin(b)) * uv.y;\n"
"\n"
"    return uv * mat2(cos(a), sin(a), -sin(a), cos(a));\n"
"}\n"
"\n"
"vec2 cone(vec2 v)\n"
"{\n"
"    return disc(vec2(v.x, 1 - sqrt(1 - v.y)));\n"
"}\n"
"\n"
"\n"
"\n"
"void sampleImage(vec2 p)\n"
"{\n"
"    float an=3.6;\n"
"\n"
"    vec3 cam=vec3(-0.7,-.25,6.);\n"
"    vec2 lens=disc(vec2(rand(),rand()));\n"
"    vec3 ro=cam+vec3(lens,0)*.03;\n"
"    vec3 rt=cam+vec3(p.xy*1.5,-6.);\n"
"    vec3 rd=normalize(rt-ro);\n"
"\n"
"    rd.xz=mat2(cos(an),sin(an),sin(an),-cos(an))*rd.xz;\n"
"    ro.xz=mat2(cos(an),sin(an),sin(an),-cos(an))*ro.xz;\n"
"\n"
"    float s=20.;\n"
"    vec3 icespec=vec3(0);\n"
"    vec3 absorp=vec3(1);\n"
"    float t=0.,d=0.,m=+1,id=0;\n"
"    for(int i=0;i<350;++i)\n"
"    {\n"
"        vec2 r=f(ro+rd*t, 0);\n"
"        d=r.x;\n"
"        id=r.y;\n"
"        if(abs(d)<1e-5)\n"
"        {\n"
"            if(r.y==3.)\n"
"            {\n"
"                t+=1e-4;\n"
"                vec3 n=normalize(distG(ro+rd*t));\n"
"                rd=rand()>.8 ? reflect(rd,n) : (m>0.?refract(rd,n*-sign(dot(rd,n)),1./1.01):rd);\n"
"                    m=-m;\n"
"                icespec+=pow(max(0.,dot(n,normalize(-rd + normalize(vec3(4.5,2,1))))),120.)*18;\n"
"                icespec+=pow(max(0.,dot(n,normalize(-rd + normalize(vec3(4.5,2,3))))),220.)*12;\n"
"                absorp*=vec3(.95,.95,1);\n"
"            }\n"
"            else\n"
"			{\n"
"				break;\n"
"			}\n"
"        }\n"
"        t+=d*.8*m;\n"
"        if(t>25.)\n"
"		{\n"
"			break;\n"
"		}\n"
"    }\n"
"\n"
"    if(t>25.)\n"
"    {\n"
"        gl_FragColor.rgb=vec3(.25)*0;\n"
"    }   \n"
"    else\n"
"    {\n"
"        vec3 rp=ro+rd*t;\n"
"        vec3 n=normalize(distG(rp));\n"
"\n"
"        gl_FragColor.rgb=vec3(1-dot(-rd,n))*.3+eyes(rp-vec3(0,-.9,0))*(.75+.3*dot(n,normalize(vec3(1))))*1.1;\n"
"        rp.y+=.9;\n"
"        if(id>.5)\n"
"        {\n"
"            gl_FragColor.rgb*=mix(vec3(1,.7,.4), mix(vec3(1),vec3(.5,.5,1),max(step(0.,-rp.z),step(.2,length((rp.xy-vec2(0,.26)) * vec2(1,.99) )))),\n"
"                                  max(step(0.,-rp.z),step(.2,length((rp.xy-vec2(0,.6)) * vec2(1.5,3) ))));\n"
"\n"
"            if(feet>0.5)\n"
"			{\n"
"                gl_FragColor.rgb=vec3(1,.7,.4);\n"
"			}\n"
"        }\n"
"        else\n"
"        {\n"
"            gl_FragColor.rgb*=vec3(.7,.75,1);\n"
"        }\n"
"\n"
"        if(id==2)\n"
"		{\n"
"            gl_FragColor.rgb=vec3(.7,1,.4)/2;\n"
"		}\n"
"		\n"
"        if(id==4)\n"
"        {\n"
"            gl_FragColor.rgb=vec3(1.,.4,.2)*2*smoothstep(0.5,.8,rp.y);\n"
"            if((length(rp.xy-vec2(1.12,.73)))<.03)\n"
"			{\n"
"                gl_FragColor.rgb=vec3(1);\n"
"			}\n"
"			\n"
"            if((length(rp.xy-vec2(1.12,.73)))<.02)\n"
"			{\n"
"                gl_FragColor.rgb=vec3(.01);\n"
"			}\n"
"        }\n"
"\n"
"        rp.y-=.9;\n"
"\n"
"        gl_FragColor.rgb*=mix(.4,1.,calcSoftshadow(rp,normalize(vec3(1,2,1)),1e-4,4.))*1.1;\n"
"\n"
"        gl_FragColor.rgb*=mix(.1,1.,pow(clamp(calcAO(rp,normalize(n+0.25)),0,1),2.5));\n"
"\n"
"        gl_FragColor.rgb*=1.+simplex(rp*6)*.1;\n"
"\n"
"        gl_FragColor.rgb*=1-smoothstep(0.,8.,length(rp))+smoothstep(9.,19.,length(rp))*smoothstep(0.,1.,-rp.y+rp.z/2+5)/2;\n"
"        gl_FragColor.rgb+=icespec;\n"
"    }\n"
"    gl_FragColor.rgb=max(gl_FragColor.rgb*absorp,0.);\n"
"    gl_FragColor.rgb+=.01;\n"
"\n"
"    gl_FragColor.rgb-=vec3(dot(gl_FragColor.rgb,vec3(1./3.)))*.1;\n"
"\n"
"}\n"
"\n"
"\n"
"void main()\n"
"{\n"
"    vec2 t=gl_FragCoord.xy/vec2(1920,1080)*2-1.;\n"
"    t.y/=1920./1080.;\n"
"    vec2 p=t.xy;\n"
"    int N=1;\n"
"    vec3 c=vec3(0);\n"
"    for(int y=0;y<N;++y)\n"
"	{\n"
"        for(int x=0;x<N;++x)\n"
"        {\n"
"            gl_FragColor.rgb=vec3(0);\n"
"            sampleImage(p+vec2(x,y)/float(N)*.002);\n"
"            c+=clamp(gl_FragColor.rgb,0.,1.);\n"
"        }\n"
"	}\n"
"    c/=float(N*N);\n"
"    gl_FragColor.rgb=c;\n"
"    gl_FragColor.rgb*=1.-(pow(abs(p.x),3.)*2+pow(abs(p.y*2.),3.))*.15;\n"
"\n"
"    gl_FragColor.rgb+=vec3(1,.5,.2)*.01;\n"
"\n"
"    gl_FragColor.rgb+=vec3(1,.9,.9)*simplex(vec3(p*200,0))*.002;\n"
"\n"
"    gl_FragColor.rgb/=(gl_FragColor.rgb+.75)*.55;\n"
"    gl_FragColor.rgb=pow(gl_FragColor.rgb,vec3(1./2.2));\n"
"}\n"
"\n"
"\n"