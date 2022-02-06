#version 120
uniform sampler2D currentTexture;
uniform float time;
uniform vec2 resolution;

const float blurSize=1./512.;
const float intensity=1.95;

void main(){
	vec2 iResolution=resolution;
	vec4 sum=vec4(0);
	vec2 texcoord=gl_FragCoord.xy/iResolution.xy;
	//vec2 texcoord=gl_TexCoord[0].xy;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y))*.20;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x+blurSize,texcoord.y))*.11;
	sum+=texture2D(currentTexture,vec2(texcoord.x-blurSize,texcoord.y))*.11;
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y+blurSize))*.11;
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y-blurSize))*.11;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x+blurSize,texcoord.y+blurSize))*.07;
	sum+=texture2D(currentTexture,vec2(texcoord.x+blurSize,texcoord.y-blurSize))*.07;
	sum+=texture2D(currentTexture,vec2(texcoord.x-blurSize,texcoord.y+blurSize))*.07;
	sum+=texture2D(currentTexture,vec2(texcoord.x-blurSize,texcoord.y-blurSize))*.07;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x+2.*blurSize,texcoord.y))*.05;
	sum+=texture2D(currentTexture,vec2(texcoord.x-2.*blurSize,texcoord.y))*.05;
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y+2.*blurSize))*.05;
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y-2.*blurSize))*.05;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x+2.*blurSize,texcoord.y+2*blurSize))*.04;
	sum+=texture2D(currentTexture,vec2(texcoord.x+2.*blurSize,texcoord.y-2*blurSize))*.04;
	sum+=texture2D(currentTexture,vec2(texcoord.x-2*blurSize,texcoord.y+2.*blurSize))*.04;
	sum+=texture2D(currentTexture,vec2(texcoord.x-2*blurSize,texcoord.y-2.*blurSize))*.04;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x+3.*blurSize,texcoord.y))*.03;
	sum+=texture2D(currentTexture,vec2(texcoord.x-3.*blurSize,texcoord.y))*.03;
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y+3.*blurSize))*.03;
	sum+=texture2D(currentTexture,vec2(texcoord.x,texcoord.y-3.*blurSize))*.03;
	
	sum+=texture2D(currentTexture,vec2(texcoord.x+3.*blurSize,texcoord.y+3*blurSize))*.02;
	sum+=texture2D(currentTexture,vec2(texcoord.x+3.*blurSize,texcoord.y-3*blurSize))*.02;
	sum+=texture2D(currentTexture,vec2(texcoord.x-3*blurSize,texcoord.y+3.*blurSize))*.02;
	sum+=texture2D(currentTexture,vec2(texcoord.x-3*blurSize,texcoord.y-3.*blurSize))*.02;
	
	//increase blur with intensity!
	gl_FragColor=sum*intensity+texture2D(currentTexture,texcoord);
	
}
