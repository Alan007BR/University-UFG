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
    primary: '#0f0',    // verde matrix (objetos não selecionados)
    selecionado: '#f00' // vermelho (objeto selecionado)
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

  // aplica transformação a todos os pontos de um objeto específico
  // rotação aqui é em torno da origem
  function aplicarTransformacao(obj, matriz) {
    for (let i = 0; i < obj.pontos.length; i++) {
      const p = obj.pontos[i];
      const resultado = multiplicarPontoMatriz([p[0], p[1], p[2], 1], matriz);
      obj.pontos[i] = [resultado[0], resultado[1], resultado[2]];
    }
  }

  // aplicar transformação no objeto selecionado

  function transladar(tx, ty, tz) {
    const obj = objetos[objetoSelecionado];
    aplicarTransformacao(obj, matrizTranslacao(tx, ty, tz));
  }

  function rotacionar(eixo, graus) {
    let m;
    if (eixo === 'x') m = matrizRotacaoX(graus);
    else if (eixo === 'y') m = matrizRotacaoY(graus);
    else if (eixo === 'z') m = matrizRotacaoZ(graus);
    const obj = objetos[objetoSelecionado];
    aplicarTransformacao(obj, m);
  }

  function escalonar(sx, sy, sz) {
    const obj = objetos[objetoSelecionado];
    aplicarTransformacao(obj, matrizEscala(sx, sy, sz));
  }

  // Estrutura de dados do objeto 3D (com faces)
  // Cada objeto tem:
  //   nome: string com o nome
  //   pontos: array de [x, y, z]
  //   linhas: array de [indiceA, indiceB] (índices base 0)
  //   faces: array de { vertices: [...], cor: [r, g, b], zMedio: 0 }
  //   rotacao: [rx, ry, rz] em graus
  //    escala: [sx, sy, sz]
  //   translacao: [tx, ty, tz]

  // criar um objeto 3D vazio
  function criarObjeto(nome) {
    return {
      nome: nome || 'sem nome',
      pontos: [],
      linhas: [],
      faces: [],
      rotacao: [0, 0, 0],
      escala: [1, 1, 1],
      translacao: [0, 0, 0]
    };
  }

  // adicionar uma face ao objeto
  // vertices = array de índices (base 0, sentido anti-horário)
  // cor = [r, g, b] valores reais de 0 a 1
  function adicionarFace(obj, vertices, cor) {
    obj.faces.push({
      vertices: vertices,
      cor: cor,
      zMedio: 0
    });
  }

  // criar uma cópia profunda do objeto (pra não compartilhar referências)
  // n tem uso, mas prof surgeriu
  function copiarObjeto(obj) {
    const copia = criarObjeto(obj.nome + ' (cópia)');

    // copiar pontos
    for (let i = 0; i < obj.pontos.length; i++) {
      copia.pontos.push([obj.pontos[i][0], obj.pontos[i][1], obj.pontos[i][2]]);
    }

    // copiar linhas
    for (let i = 0; i < obj.linhas.length; i++) {
      copia.linhas.push([obj.linhas[i][0], obj.linhas[i][1]]);
    }

    // copiar faces
    for (let i = 0; i < obj.faces.length; i++) {
      const f = obj.faces[i];
      copia.faces.push({
        vertices: f.vertices.slice(),
        cor: [f.cor[0], f.cor[1], f.cor[2]],
        zMedio: f.zMedio
      });
    }

    // copiar transformações
    copia.rotacao = [obj.rotacao[0], obj.rotacao[1], obj.rotacao[2]];
    copia.escala = [obj.escala[0], obj.escala[1], obj.escala[2]];
    copia.translacao = [obj.translacao[0], obj.translacao[1], obj.translacao[2]];

    return copia;
  }

  // imprimir o conteúdo completo de um objeto no console (depuração)
  function imprimirObjeto(obj) {
    console.log('=== Objeto: ' + obj.nome + ' ===');
    console.log('Pontos (' + obj.pontos.length + '):');
    for (let i = 0; i < obj.pontos.length; i++) {
      console.log('  P' + i + ': (' + obj.pontos[i][0] + ', ' + obj.pontos[i][1] + ', ' + obj.pontos[i][2] + ')');
    }
    console.log('Linhas (' + obj.linhas.length + '):');
    for (let i = 0; i < obj.linhas.length; i++) {
      console.log('  L' + i + ': ' + obj.linhas[i][0] + ' -> ' + obj.linhas[i][1]);
    }
    console.log('Faces (' + obj.faces.length + '):');
    for (let i = 0; i < obj.faces.length; i++) {
      const f = obj.faces[i];
      console.log('  F' + i + ': vértices=[' + f.vertices.join(', ') + '] cor=(' + f.cor[0] + ', ' + f.cor[1] + ', ' + f.cor[2] + ') zMedio=' + f.zMedio);
    }
    console.log('Rotação: (' + obj.rotacao.join(', ') + ')');
    console.log('Escala: (' + obj.escala.join(', ') + ')');
    console.log('Translação: (' + obj.translacao.join(', ') + ')');
    console.log('==========================');
  }

  // lista e controle de objetos

  let objetos = [];           // lista de todos os objetos na cena
  let objetoSelecionado = 0;  // índice do objeto atualmente selecionado

  // projeções da câmera

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

    // mostrar qual objeto está selecionado
    if (objetos.length > 0) {
      const nomeObj = objetos[objetoSelecionado].nome;
      ctx.textAlign = 'left';
      ctx.fillText('Selecionado: ' + nomeObj + ' (' + (objetoSelecionado + 1) + '/' + objetos.length + ')', 10, 20);
    }

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

  // calcula a profundidade média (z médio) pra usar depois no pintor
  function calcularZMedioFaces(obj) {
    for (let i = 0; i < obj.faces.length; i++) {
      const f = obj.faces[i];
      let somaZ = 0;
      for (let j = 0; j < f.vertices.length; j++) {
        somaZ += obj.pontos[f.vertices[j]][2];
      }
      f.zMedio = somaZ / f.vertices.length;
    }
  }

  // loop principal pra desenhar tudo na tela
  function desenhar() {
    clear();

    const zoom = 1; // sem zoom extra aqui, a escala já vem do arquivo

    for (let idx = 0; idx < objetos.length; idx++) {
      const obj = objetos[idx];
      const estaSelecionado = (idx === objetoSelecionado);

      // calcular z médio das faces (pra uso futuro)
      calcularZMedioFaces(obj);

      // pipeline: ponto → projeção → tela
      const pontosProjetados = [];
      for (let i = 0; i < obj.pontos.length; i++) {
        const p = obj.pontos[i];

        // aplicar projeção
        const proj = projetar(p[0], p[1], p[2]);

        // converter pra tela
        pontosProjetados.push(paraTela(proj[0], proj[1]));
      }

      // cor: vermelho se selecionado, verde se não
      if (estaSelecionado) {
        ctx.fillStyle = styles.selecionado;
      } else {
        ctx.fillStyle = styles.primary;
      }

      // desenhar cada aresta usando DDA
      for (let i = 0; i < obj.linhas.length; i++) {
        const a = obj.linhas[i][0];
        const b = obj.linhas[i][1];
        lineDDA(
          pontosProjetados[a].x, pontosProjetados[a].y,
          pontosProjetados[b].x, pontosProjetados[b].y
        );
      }
    }

    // HUD, pontos de fuga e status
    desenharHUD();
    desenharPontosDeFuga();

    if (objetos.length > 0) {
      const obj = objetos[objetoSelecionado];
      status.textContent = 'Objetos: ' + objetos.length +
        ' | Selecionado: ' + obj.nome +
        ' (' + obj.pontos.length + ' pontos, ' + obj.linhas.length + ' arestas, ' + obj.faces.length + ' faces)';
    } else {
      status.textContent = 'Nenhum objeto carregado';
    }
  }

  // atalhos e controles do teclado

  // Incrementos
  const TRANSLACAO_STEP = 0.1;   // unidades do mundo
  const ROTACAO_STEP = 5;        // graus
  const ESCALA_STEP = 1.1;       // fator multiplicativo (10%)

  let mostrandoAjuda = false;

  window.addEventListener('keydown', (e) => {
    // se não tem objetos carregados, ignora tudo exceto F1
    if (objetos.length === 0 && e.key.toLowerCase() !== 'f1') return;

    let atualizar = true;

    // TAB / SHIFT+TAB pra selecionar objetos (lista circular)
    if (e.key === 'Tab') {
      e.preventDefault(); // evita o tab sair do canvas
      if (e.shiftKey) {
        // SHIFT+TAB: voltar ao objeto anterior
        objetoSelecionado = (objetoSelecionado - 1 + objetos.length) % objetos.length;
      } else {
        // TAB: avançar pro próximo objeto
        objetoSelecionado = (objetoSelecionado + 1) % objetos.length;
      }
      desenhar();
      return;
    }

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
            'TAB = selecionar próximo objeto',
            'SHIFT+TAB = selecionar objeto anterior',
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

  // parser do figure.dat (agora com suporte a faces)
  // Formato:
  //   # Nome da figura
  //   Xmin Xmax Ymin Ymax
  //   n (quantidade de objetos)
  //   para cada objeto:
  //     # Nome do objeto
  //     p l f (pontos, linhas, faces)
  //     p linhas com coordenadas x y z
  //     l linhas com indices Pa Pb (base 1)
  //     f linhas com: N Ip1 Ip2 ... IpN R G B (indices base 1)
  //     rotação: theta_x theta_y theta_z
  //     escala: Sx Sy Sz
  //     translação: Tx Ty Tz

  function carregarArquivo(texto) {
    const linhas = texto.trim().split('\n');
    let offset = 0;

    // 1a linha: # nome da figura
    const nomeFigura = linhas[offset].trim();
    console.log('Figura: ' + nomeFigura);
    offset++;

    // 2a linha: Xmin Xmax Ymin Ymax (limites do universo)
    const limites = linhas[offset].trim().split(/\s+/);
    const xMin = parseFloat(limites[0]);
    const xMax = parseFloat(limites[1]);
    const yMin = parseFloat(limites[2]);
    const yMax = parseFloat(limites[3]);
    console.log('Limites do universo: X[' + xMin + ', ' + xMax + '] Y[' + yMin + ', ' + yMax + ']');
    offset++;

    // 3a linha: quantidade de objetos
    const numObjetos = parseInt(linhas[offset].trim());
    console.log('Quantidade de objetos: ' + numObjetos);
    offset++;

    // ler cada objeto
    const novosObjetos = [];

    for (let idx = 0; idx < numObjetos; idx++) {
      // # nome do objeto
      const nomeObj = linhas[offset].trim().replace(/^#\s*/, '');
      offset++;

      // p l f
      const plf = linhas[offset].trim().split(/\s+/);
      const numPontos = parseInt(plf[0]);
      const numLinhas = parseInt(plf[1]);
      const numFaces = parseInt(plf[2]);
      console.log('Objeto "' + nomeObj + '": ' + numPontos + ' pontos, ' + numLinhas + ' linhas, ' + numFaces + ' faces');
      offset++;

      const obj = criarObjeto(nomeObj);

      // ler os p pontos
      for (let i = 0; i < numPontos; i++) {
        const coords = linhas[offset].trim().split(/\s+/);
        obj.pontos.push([
          parseFloat(coords[0]),
          parseFloat(coords[1]),
          parseFloat(coords[2])
        ]);
        offset++;
      }

      // ler as l linhas (índices base 1 no arquivo → converter pra base 0)
      for (let i = 0; i < numLinhas; i++) {
        const indices = linhas[offset].trim().split(/\s+/);
        obj.linhas.push([
          parseInt(indices[0]) - 1,
          parseInt(indices[1]) - 1
        ]);
        offset++;
      }

      // ler as f faces
      // formato: N Ip1 Ip2 ... IpN R G B
      for (let i = 0; i < numFaces; i++) {
        const partes = linhas[offset].trim().split(/\s+/);
        const numVerticesFace = parseInt(partes[0]);

        // ler os índices dos vértices (base 1 → base 0)
        const verticesFace = [];
        for (let v = 0; v < numVerticesFace; v++) {
          verticesFace.push(parseInt(partes[1 + v]) - 1);
        }

        // ler a cor RGB (3 valores reais no final)
        const r = parseFloat(partes[1 + numVerticesFace]);
        const g = parseFloat(partes[2 + numVerticesFace]);
        const b = parseFloat(partes[3 + numVerticesFace]);

        adicionarFace(obj, verticesFace, [r, g, b]);
        offset++;
      }

      // ler as transformações iniciais
      // rotação
      const rot = linhas[offset].trim().split(/\s+/);
      obj.rotacao = [parseFloat(rot[0]), parseFloat(rot[1]), parseFloat(rot[2])];
      offset++;

      // escala
      const esc = linhas[offset].trim().split(/\s+/);
      obj.escala = [parseFloat(esc[0]), parseFloat(esc[1]), parseFloat(esc[2])];
      offset++;

      // translação
      const trl = linhas[offset].trim().split(/\s+/);
      obj.translacao = [parseFloat(trl[0]), parseFloat(trl[1]), parseFloat(trl[2])];
      offset++;

      // aplicar as transformações iniciais aos pontos do objeto
      // ordem: escala → rotação (X, Y, Z) → translação
      const mEsc = matrizEscala(obj.escala[0], obj.escala[1], obj.escala[2]);
      const mRotX = matrizRotacaoX(obj.rotacao[0]);
      const mRotY = matrizRotacaoY(obj.rotacao[1]);
      const mRotZ = matrizRotacaoZ(obj.rotacao[2]);
      const mTrl = matrizTranslacao(obj.translacao[0], obj.translacao[1], obj.translacao[2]);

      // concatenar: escala * rotX * rotY * rotZ * translação
      let mFinal = mEsc;
      mFinal = multiplicarMatrizes(mFinal, mRotX);
      mFinal = multiplicarMatrizes(mFinal, mRotY);
      mFinal = multiplicarMatrizes(mFinal, mRotZ);
      mFinal = multiplicarMatrizes(mFinal, mTrl);

      aplicarTransformacao(obj, mFinal);

      // imprimir no console pra depuração
      imprimirObjeto(obj);

      novosObjetos.push(obj);
    }

    // atualizar a lista global de objetos
    objetos = novosObjetos;
    objetoSelecionado = 0;

    desenhar();
  }

  // listener de upload de arquivo
  const fileInput = document.getElementById('fileInput');
  fileInput.addEventListener('change', (e) => {
    const file = e.target.files[0];
    if (!file) return;

    const reader = new FileReader();
    reader.onload = (event) => {
      carregarArquivo(event.target.result);
    };
    reader.readAsText(file);
  });

  // tenta carregar o arquivo padrão se ele estiver na mesma pasta
  fetch('figure.dat')
    .then(response => {
      if (!response.ok) throw new Error('Arquivo figure.dat não encontrado');
      return response.text();
    })
    .then(texto => {
      console.log('figure.dat carregado automaticamente');
      carregarArquivo(texto);
    })
    .catch(err => {
      console.log('figure.dat não encontrado no diretório, aguardando upload manual...');
      clear();
      // mostrar mensagem na tela
      ctx.fillStyle = styles.primary;
      ctx.font = '16px Poppins';
      ctx.textAlign = 'center';
      ctx.fillText('Carregue um arquivo .dat para começar', screen.width / 2, screen.height / 2);
      ctx.textAlign = 'left';
    });

});
