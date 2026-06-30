window.addEventListener('DOMContentLoaded', () => {
  const canvas = document.getElementById('screen');
  const ctx = canvas.getContext('2d');
  const status = document.getElementById('status');
  const ajuda = document.getElementById('ajuda');

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


  // Coordenadas homogêneas: ponto (x, y, z) representado como (x, y, z, 1)
  // permite expressar todas as transformações (inclusive translação) como multiplicação de matrizes 4x4

  // Matriz identidade 4x4
  function matrizIdentidade() {
    return [
      [1, 0, 0, 0],
      [0, 1, 0, 0],
      [0, 0, 1, 0],
      [0, 0, 0, 1]
    ];
  }

  // Concatenação de matrizes 4x4 (multiplicação)
  // permite combinar várias transformações em uma única matriz
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

  // multiplica ponto em coordenadas homogêneas [x, y, z, 1] por matriz 4x4
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

  // Matrizes de transformação em coordenadas homogêneas

  // Translação (deslocamento no espaço)
  // em coordenadas homogêneas a translação vira multiplicação de matriz
  function matrizTranslacao(tx, ty, tz) {
    const m = matrizIdentidade();
    m[3][0] = tx;
    m[3][1] = ty;
    m[3][2] = tz;
    return m;
  }

  // Escala (mudança de tamanho)
  function matrizEscala(sx, sy, sz) {
    const m = matrizIdentidade();
    m[0][0] = sx;
    m[1][1] = sy;
    m[2][2] = sz;
    return m;
  }

  // Rotação em torno do eixo X (ângulo de Euler)
  // sentido positivo dado pela regra da mão direita
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

  // Rotação em torno do eixo Y (ângulo de Euler)
  // sentido positivo dado pela regra da mão direita
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

  // Rotação em torno do eixo Z (ângulo de Euler)
  // sentido positivo dado pela regra da mão direita
  function matrizRotacaoZ(graus) {
    const rad = graus * Math.PI / 180;
    const c = Math.cos(rad);
    const s = Math.sin(rad);
    const m = matrizIdentidade();
    m[0][0] = c;
    m[0][1] = s;
    m[1][0] = -s;
    m[1][1] = c;
    return m;
  }

  // aplica transformação a todos os pontos do objeto
  // rotação aqui é em torno da origem
  function aplicarTransformacao(matriz) {
    for (let i = 0; i < objeto.pontos.length; i++) {
      const p = objeto.pontos[i];
      const resultado = multiplicarPontoMatriz([p[0], p[1], p[2], 1], matriz);
      objeto.pontos[i] = [resultado[0], resultado[1], resultado[2]];
    }
  }

  // aplicar transformação no obj

  function transladar(tx, ty, tz) {
    aplicarTransformacao(matrizTranslacao(tx, ty, tz));
  }

  function rotacionar(eixo, graus) {
    let m;
    if (eixo === 'x') m = matrizRotacaoX(graus);
    else if (eixo === 'y') m = matrizRotacaoY(graus);
    else if (eixo === 'z') m = matrizRotacaoZ(graus);
    aplicarTransformacao(m);
  }

  function escalonar(sx, sy, sz) {
    aplicarTransformacao(matrizEscala(sx, sy, sz));
  }

  // Estrutura de dados do objeto 3D (wireframe)
  // n pontos (X, Y, Z) e m linhas (indice A, indice B)
  const objeto = {
    pontos: [
      // cubo centrado na origem (-1 a 1)
      [-1, -1, -1],    // 0
      [1, -1, -1],     // 1
      [1, 1, -1],      // 2
      [-1, 1, -1],     // 3
      [-1, -1, 1],     // 4
      [1, -1, 1],      // 5
      [1, 1, 1],       // 6
      [-1, 1, 1]       // 7
    ],
    linhas: [
      // face da frente (z = -1)
      [0, 1], [1, 2], [2, 3], [3, 0],
      // face de trás (z = 1)
      [4, 5], [5, 6], [6, 7], [7, 4],
      // conectando frente e trás
      [0, 4], [1, 5], [2, 6], [3, 7]
    ]
  };

  // projeções
  // lista circular: P alterna entre elas
  const projecoes = ['Cavaleira', 'Cabinet', 'Isométrica', '1 Ponto de Fuga', '2 Pontos de Fuga'];
  let projecaoAtual = 0;

  // projeção paralela oblíqua (cavaleira e cabinet)
  // projeta Z no plano XY com angulo de 45 graus
  // cavaleira: fator = 1 (escala Z inteira)
  // cabinet: fator = 0.5 (escala Z pela metade, mais realista)
  function projecaoObliqua(x, y, z, fator) {
    const alfa = 45 * Math.PI / 180;
    const xp = x - z * Math.cos(alfa) * fator;  // tem que ser negativa por causa da convenção de profundidade do mundo -z se desloca esquerda baixo, a face traseira aparece atrás (professor visualizou e pediu pra corrigir na tarefa 4)
    const yp = y - z * Math.sin(alfa) * fator;  // e paraTela inverte o mundo em -yMundo
    return [xp, yp];
  }

  // projeção isométrica
  // rotaciona o objeto pra alinhar os 3 eixos a 120 graus entre si
  // depois aplica projeção ortográfica no plano Z=0 (anula Z)
  function projecaoIsometrica(x, y, z) {
    // rotação padrão isométrica: 35.26 em X, 45° em Y
    const mRotY = matrizRotacaoY(45);
    const mRotX = matrizRotacaoX(35.264);
    const mRot = multiplicarMatrizes(mRotY, mRotX);

    // projeção ortográfica z=0 (anula a coordenada z)
    const mOrtho = [
      [1, 0, 0, 0],
      [0, 1, 0, 0],
      [0, 0, 0, 0],
      [0, 0, 0, 1]
    ]; // tem que achatar o objeto tridimensional contra a tela

    const mFinal = multiplicarMatrizes(mRot, mOrtho);
    const p = multiplicarPontoMatriz([x, y, z, 1], mFinal);
    return [p[0], p[1]];
  }

  // perspectiva com 1 ponto de fuga (no eixo Z)
  // x' = x / (1 - z/fz)
  // y' = y / (1 - z/fz)
  // com base nos slides??
  const FZ_1PF = 400;
  function perspectiva1PF(x, y, z) {
    const d = 1 - z / FZ_1PF;
    if (Math.abs(d) < 0.001) return [x, y]; // evita divisão por zero
    return [x / d, y / d];
  }

  // perspectiva com 2 pontos de fuga (eixos X e Z)
  // matriz com -1/fx e -1/fz na 4a coluna
  // depois divide por w (homogeneização)
  const FX_2PF = 300;
  const FZ_2PF = 300;
  function perspectiva2PF(x, y, z) {
    // w = 1 + x*(-1/fx) + z*(-1/fz)
    const w = 1 - x / FX_2PF - z / FZ_2PF;
    if (Math.abs(w) < 0.001) return [x, y]; // evita divisão por zero
    return [x / w, y / w];
  }

  // aplica a projeção atual sobre um ponto (x, y, z)
  // retorna [xProjetado, yProjetado]
  function projetar(x, y, z) {
    switch (projecaoAtual) {
      case 0: return projecaoObliqua(x, y, z, 1);     // cavaleira
      case 1: return projecaoObliqua(x, y, z, 0.5);   // cabinet
      case 2: return projecaoIsometrica(x, y, z);      // isométrica
      case 3: return perspectiva1PF(x, y, z);          // 1 ponto de fuga
      case 4: return perspectiva2PF(x, y, z);          // 2 pontos de fuga
    }
    return [x, y];
  }

  // converter coordenadas do mundo pra coordenadas da tela
  function paraTela(xMundo, yMundo) {
    return {
      x: Math.round(xMundo + screen.width / 2),
      y: Math.round(-yMundo + screen.height / 2)
    };
  }

  // desenhar nome da projeção no canto direito
  function desenharHUD() {
    ctx.fillStyle = styles.primary;
    ctx.font = '14px';
    ctx.textAlign = 'right';
    ctx.fillText(projecoes[projecaoAtual], screen.width - 10, 20);
    ctx.textAlign = 'left';
  }

  // desenhar marcador de ponto de fuga (cruz vermelha)
  function desenharPontoFuga(xTela, yTela, label) {
    const tam = 8;
    ctx.strokeStyle = '#f00';
    ctx.stroke();

    ctx.fillStyle = '#f00';
    ctx.font = '11px';
    ctx.textAlign = 'left';
    ctx.fillText(label, xTela + tam + 3, yTela + 4);
  }

  // desenhar os pontos de fuga da projeção atual
  function desenharPontosDeFuga() {
    if (projecaoAtual === 3) {
      // 1PF: ponto de fuga no eixo Z
      // linhas paralelas a Z convergem pra (0, 0) no mundo projetado
      const vp = paraTela(0, 0);
      desenharPontoFuga(vp.x, vp.y, 'PF_z');
    }
    if (projecaoAtual === 4) {
      // 2PF: ponto de fuga em Z (convergencia pra centro)
      const vpZ = paraTela(0, 0);
      desenharPontoFuga(vpZ.x, vpZ.y, 'PF_z');

      // ponto de fuga em X: linhas paralelas a X convergem pra x' = -fx
      // no espaço projetado, quando x→∞, x'/w → -fx
      const vpX = paraTela(-FX_2PF, 0);
      desenharPontoFuga(vpX.x, vpX.y, 'PF_x');
    }
  }

  // desenhar o objeto na tela
  function desenhar() {
    clear();

    const zoom = 80;
    const mZoom = matrizEscala(zoom, zoom, zoom);

    // pipeline: ponto → zoom → projeção → tela
    const pontosProjetados = [];
    for (let i = 0; i < objeto.pontos.length; i++) {
      const p = objeto.pontos[i];

      // aplicar zoom
      const pZoom = multiplicarPontoMatriz([p[0], p[1], p[2], 1], mZoom);

      // aplicar projeção
      const proj = projetar(pZoom[0], pZoom[1], pZoom[2]);

      // converter pra tela
      pontosProjetados.push(paraTela(proj[0], proj[1]));
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

    // HUD, pontos de fuga e status
    desenharHUD();
    desenharPontosDeFuga();
    status.textContent = 'Objeto: ' + objeto.pontos.length + ' pontos, ' + objeto.linhas.length + ' arestas';
  }

  // teclas do teclado para transformações

  // Incrementos
  const TRANSLACAO_STEP = 0.1;   // unidades do mundo
  const ROTACAO_STEP = 5;        // graus
  const ESCALA_STEP = 1.1;       // fator multiplicativo (10%)

  let mostrandoAjuda = false;

  window.addEventListener('keydown', (e) => {
    let atualizar = true;

    switch (e.key.toLowerCase()) {
      // translação
      case 'q':
        transladar(TRANSLACAO_STEP, 0, 0);
        break;
      case 'a':
        transladar(-TRANSLACAO_STEP, 0, 0);
        break;

      case 'w':
        transladar(0, TRANSLACAO_STEP, 0);
        break;
      case 's':
        transladar(0, -TRANSLACAO_STEP, 0);
        break;

      case 'e':
        transladar(0, 0, TRANSLACAO_STEP);
        break;
      case 'd':
        transladar(0, 0, -TRANSLACAO_STEP);
        break;

      // rotação
      case 'r':
        rotacionar('x', ROTACAO_STEP);
        break;
      case 'f':
        rotacionar('x', -ROTACAO_STEP);
        break;

      case 't':
        rotacionar('y', ROTACAO_STEP);
        break;
      case 'g':
        rotacionar('y', -ROTACAO_STEP);
        break;

      case 'y':
        rotacionar('z', ROTACAO_STEP);
        break;
      case 'h':
        rotacionar('z', -ROTACAO_STEP);
        break;

      // escala
      case 'u':
        escalonar(ESCALA_STEP, 1, 1);
        break;
      case 'j':
        escalonar(1 / ESCALA_STEP, 1, 1);
        break;

      case 'i':
        escalonar(1, ESCALA_STEP, 1);
        break;
      case 'k':
        escalonar(1, 1 / ESCALA_STEP, 1);
        break;

      case 'o':
        escalonar(1, 1, ESCALA_STEP);
        break;
      case 'l':
        escalonar(1, 1, 1 / ESCALA_STEP);
        break;

      // P = alternar projeção (lista circular)
      case 'p':
        projecaoAtual = (projecaoAtual + 1) % projecoes.length;
        break;

      // F1 = ajuda
      case 'f1':
        e.preventDefault();
        mostrandoAjuda = !mostrandoAjuda;
        if (mostrandoAjuda) {
          ajuda.textContent = [
            'CONTROLES:',
            '',
            'Translação:  Q/A = X+/X-   W/S = Y+/Y-   E/D = Z+/Z-',
            'Rotação:     R/F = X+/X-   T/G = Y+/Y-   Y/H = Z+/Z-',
            'Escala:      U/J = X+/X-   I/K = Y+/Y-   O/L = Z+/Z-',
            '',
            'P = alternar projeção',
            'F1 = fechar ajuda'
          ].join('\n');
          ajuda.style.display = 'block';
        } else {
          ajuda.style.display = 'none';
        }
        atualizar = false;
        break;

      default:
        atualizar = false;
        break;
    }

    if (atualizar) {
      desenhar();
    }
  });

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
