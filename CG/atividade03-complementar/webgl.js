// webgl.js
// desenhar poligno de 5 a 10 vértices em webgl

const createShader = (gl, type, source) => {
  const shader = gl.createShader(type);
  gl.shaderSource(shader, source);
  gl.compileShader(shader);
  const success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
  if (success) {
    return shader;
  }
  console.error("Erro na compi do shader:", gl.getShaderInfoLog(shader));
  gl.deleteShader(shader);
  return null;
}

// https://stackoverflow.com/questions/35913006/can-anyone-explain-these-snippets-related-to-webgl

const vertexShaderSource = `
attribute vec2 a_position;
 
uniform vec2 u_resolution;
 
void main() {
   // convert the rectangle from pixels to 0.0 to 1.0
   vec2 zeroToOne = a_position / u_resolution;
 
   // convert from 0->1 to 0->2
   vec2 zeroToTwo = zeroToOne * 2.0;
 
   // convert from 0->2 to -1->+1 (clipspace)
   vec2 clipSpace = zeroToTwo - 1.0;
 
   gl_Position = vec4(clipSpace, 0, 1);
}

`;

// https://webglfundamentals.org/webgl/lessons/webgl-shaders-and-glsl.html
const fragmentShaderSource = `
  precision mediump float;
  uniform vec4 u_color;
  
  void main() {
    gl_FragColor = u_color;
  }
`;

window.runWebGLBenchmark = (gerador, limit = 1000) => {
  const canvas = document.getElementById('canvasWebGL');

  document.getElementById('canvas2d').style.display = 'none';
  document.getElementById('containerThree').style.display = 'none';
  canvas.style.display = 'block';

  const gl = canvas.getContext('webgl');

  const vertexShader = createShader(gl, gl.VERTEX_SHADER, vertexShaderSource);
  const fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragmentShaderSource);

  const program = gl.createProgram();
  gl.attachShader(program, vertexShader);
  gl.attachShader(program, fragmentShader);
  gl.linkProgram(program);

  const positionAttributeLocation = gl.getAttribLocation(program, 'a_position');
  const resolutionUniformLocation = gl.getUniformLocation(program, 'u_resolution');
  const colorUniformLocation = gl.getUniformLocation(program, 'u_color');

  const positionBuffer = gl.createBuffer();
  gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

  gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

  // Limpa fundo para branco antes de começar a recursao
  gl.clearColor(1.0, 1.0, 1.0, 1.0);
  gl.clear(gl.COLOR_BUFFER_BIT);

  gl.useProgram(program);
  gl.uniform2f(resolutionUniformLocation, gl.canvas.width, gl.canvas.height);

  gl.enableVertexAttribArray(positionAttributeLocation);

  const start = performance.now();
  for (let i = 0; i < limit; i++) {
    const { pontos, centroid } = gerador();
    const n = pontos.length;

    const triangleVertices = [];
    const lineVertices = [];

    for (let j = 0; j < n; j++) {

      const pAtual = pontos[j];
      const pProx = pontos[(j + 1) % n];

      triangleVertices.push(pProx.x, pProx.y);
      triangleVertices.push(pAtual.x, pAtual.y);
      triangleVertices.push(centroid.x, centroid.y);

      lineVertices.push(pAtual.x, pAtual.y);
    }

    // preenchimento de amarelo 
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(triangleVertices), gl.STATIC_DRAW);
    gl.vertexAttribPointer(positionAttributeLocation, 2, gl.FLOAT, false, 0, 0);
    gl.uniform4f(colorUniformLocation, 1.0, 1.0, 0.0, 1.0); // Amarelo R G B A
    gl.drawArrays(gl.TRIANGLES, 0, triangleVertices.length / 2);

    // Desenhar o contorno de preto
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(lineVertices), gl.STATIC_DRAW);
    gl.vertexAttribPointer(positionAttributeLocation, 2, gl.FLOAT, false, 0, 0);
    gl.uniform4f(colorUniformLocation, 0, 0, 0, 1); // preto R G B A
    gl.drawArrays(gl.LINE_LOOP, 0, lineVertices.length / 2);
  }
  const end = performance.now();
  return end - start;
}