window.addEventListener('DOMContentLoaded', () => {
  const canvas = document.getElementById('screen');
  const ctx = canvas.getContext('2d');
  const status = document.getElementById('status');

  const screen = {
    width: canvas.width,
    height: canvas.height,
    pixelSize: 1
  };
  const styles = {
    background: '#000',
    primary: '#0f0' //verde matrix
  };

  function draw(x, y) {
    ctx.fillRect(x, y, screen.pixelSize, screen.pixelSize);
  }

  // Limpar (pintar tudo de preto)
  function clear() {
    ctx.fillStyle = styles.background;
    ctx.fillRect(0, 0, screen.width, screen.height);
  }

  // algoritmo DDA
  function lineDDA(x0, y0, x1, y1) {
    let dx = x1 - x0;
    let dy = y1 - y0;

    let steps;

    if (Math.abs(dx) > Math.abs(dy)) {
      steps = Math.abs(dx);
    } else {
      steps = Math.abs(dy);
    }

    if (steps === 0) {
      draw(Math.round(x0), Math.round(y0));
      return;
    }

    let xIncrement = dx / steps;
    let yIncrement = dy / steps;

    let x = x0;
    let y = y0;

    ctx.fillStyle = styles.primary;
    draw(Math.round(x), Math.round(y));

    for (let i = 0; i <= steps; i++) {
      draw(Math.round(x), Math.round(y));
      x += xIncrement;
      y += yIncrement;
    }
  }

  // Matriz identidade 4x4
  function matrizIdentidade() {
    return [
      [1, 0, 0, 0],
      [0, 1, 0, 0],
      [0, 0, 1, 0],
      [0, 0, 0, 1]
    ];
  }

  // Multiplicação de duas matrizes 4x4
  function multiplicarMatrizes(A, B) {
    const R = [
      [0, 0, 0, 0],
      [0, 0, 0, 0],
      [0, 0, 0, 0],
      [0, 0, 0, 0]
    ];

    for (let i = 0; i < 4; i++) {
      for (let j = 0; j < 4; j++) {
        for (let k = 0; k < 4; k++) {
          R[i][j] += A[i][k] * B[k][j];
        }
      }
    }

    return R;
  }

  // multiplica ponto [x, y, z, 1] por matriz 4x4
  // convenção vetor-linha × matriz
  function multiplicarPontoMatriz(ponto, matriz) {
    const resultado = [0, 0, 0, 0];

    for (let j = 0; j < 4; j++) {
      for (let k = 0; k < 4; k++) {
        resultado[j] += ponto[k] * matriz[k][j];
      }
    }

    return resultado;
  }

  // Matrizes de transformação

  function matrizEscala(sx, sy, sz) {
    const m = matrizIdentidade();
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    return m;
  }

  function matrizRotacaoX(graus) {
    const rad = graus * Math.PI / 180;
    const c = Math.cos(rad);
    const s = Math.sin(rad);
    const m = matrizIdentidade();
    m[1][1] = c;
    m[1][2] = s;
    m[2][1] = -s;
    m[2][2] = c;
    return m;
  }

  function matrizRotacaoY(graus) {
    const rad = graus * Math.PI / 180;
    const c = Math.cos(rad);
    const s = Math.sin(rad);
    const m = matrizIdentidade();
    m[0][0] = c;
    m[0][2] = -s;
    m[2][0] = s;
    m[2][2] = c;
    return m;
  }

  // Estrutura de dados do objeto 3D (wireframe)
  // n pontos (X, Y, Z) e m linhas (indice A, indice B)
  const objeto = {
    pontos: [
      // cubo centrado na origem (-1 a 1)
      [-1, -1, -1],  // 0
      [1, -1, -1],  // 1
      [1, 1, -1],  // 2
      [-1, 1, -1],  // 3
      [-1, -1, 1],  // 4
      [1, -1, 1],  // 5
      [1, 1, 1],  // 6
      [-1, 1, 1]   // 7
    ],
    linhas: [
      // face da frente (z = -1)
      [0, 1], [1, 2], [2, 3], [3, 0],
      // face de trás (z = 1)
      [4, 5], [5, 6], [6, 7], [7, 4],
      // conectando frente e trás?
      [0, 4], [1, 5], [2, 6], [3, 7]
    ]
  };

  // projeção cavaleira
  // x_tela = x + z * cos(alfa) * fator
  // y_tela = y + z * sin(alfa) * fator
  // alfa = 45 graus, fator = 0.5
  function projecaoCavaleira(x, y, z) {
    const alfa = 45 * Math.PI / 180;
    const fator = 0.5;

    const xTela = x + z * Math.cos(alfa) * fator;
    const yTela = y + z * Math.sin(alfa) * fator;

    // deslocar pro centro da tela e inverter o Y
    return {
      x: Math.round(xTela + screen.width / 2),
      y: Math.round(-yTela + screen.height / 2)
    };
  }

  // desenhar o objeto na tela com zoom
  function desenhar() {
    clear();

    // aplicar escala (zoom) e uma rotação fixa pra visualizar em 3D
    const zoom = 80;
    const mEscala = matrizEscala(zoom, zoom, zoom);
    const mRotX = matrizRotacaoX(25);
    const mRotY = matrizRotacaoY(35);

    // concatenar: Escala × RotX × RotY
    let mComposta = multiplicarMatrizes(mEscala, mRotX);
    mComposta = multiplicarMatrizes(mComposta, mRotY);

    // transformar e projetar cada ponto
    const pontosProjetados = [];
    for (let i = 0; i < objeto.pontos.length; i++) {
      const p = objeto.pontos[i];
      const pTransformado = multiplicarPontoMatriz([p[0], p[1], p[2], 1], mComposta);
      const pTela = projecaoCavaleira(pTransformado[0], pTransformado[1], pTransformado[2]);
      pontosProjetados.push(pTela);
    }

    // desenhar cada aresta usando DDA
    ctx.fillStyle = styles.primary;
    for (let i = 0; i < objeto.linhas.length; i++) {
      const a = objeto.linhas[i][0];
      const b = objeto.linhas[i][1];
      lineDDA(
        pontosProjetados[a].x, pontosProjetados[a].y,
        pontosProjetados[b].x, pontosProjetados[b].y
      );
    }

    status.textContent = 'Objeto: ' + objeto.pontos.length + ' pontos, ' + objeto.linhas.length + ' arestas';
  }

  // carga de arquivo 3D
  const fileInput = document.getElementById('fileInput');
  fileInput.addEventListener('change', (e) => {
    const file = e.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = (event) => {
      const texto = event.target.result;
      const linhas = texto.trim().split('\n');

      // ler n e m
      // "8 12" na mesma linha ou "8" e "12" em linhas separadas
      let n, m;
      let offset = 0; // indice da próxima linha a ler

      const partes = linhas[0].trim().split(/\s+/);
      if (partes.length >= 2) {
        // formato: "n m" na mesma linha
        n = parseInt(partes[0]);
        m = parseInt(partes[1]);
        offset = 1;
      } else {
        // formato: n na primeira linha, m na segunda linha
        n = parseInt(linhas[0].trim());
        m = parseInt(linhas[1].trim());
        offset = 2;
      }

      console.log('Carregando: ', n, ' pontos, ', m, ' arestas');

      // ler os n pontos
      const novosPontos = [];
      for (let i = 0; i < n; i++) {
        const coords = linhas[offset + i].trim().split(/\s+/);
        novosPontos.push([
          parseFloat(coords[0]),
          parseFloat(coords[1]),
          parseFloat(coords[2])
        ]);
      }

      // ler as m arestas
      const novasLinhas = [];
      for (let i = 0; i < m; i++) {
        const indices = linhas[offset + n + i].trim().split(/\s+/);
        novasLinhas.push([
          parseInt(indices[0]),
          parseInt(indices[1])
        ]);
      }

      // Atualizar o objeto
      objeto.pontos = novosPontos;
      objeto.linhas = novasLinhas;

      desenhar();
    };
    reader.readAsText(file);
  });

  clear();
  desenhar();

});
