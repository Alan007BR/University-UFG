window.addEventListener('DOMContentLoaded', () => {
  const canvas = document.getElementById('screen');
  const ctx = canvas.getContext('2d');
  const status = document.getElementById('status');
  const ajuda = document.getElementById('ajuda');

  const screen = {
    width: window.innerWidth,
    height: window.innerHeight,
    pixelSize: 1
  };

  function redimensionarCanvas() {
    canvas.width = window.innerWidth;
    canvas.height = window.innerHeight;
    screen.width = canvas.width;
    screen.height = canvas.height;
    if (typeof desenhar === 'function') {
      desenhar();
    }
  }

  window.addEventListener('resize', redimensionarCanvas);

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

    // Transformar os eixos locais também, se existirem
    if (obj.eixos) {
      for (let i = 0; i < obj.eixos.length; i++) {
        const p = obj.eixos[i];
        const resultado = multiplicarPontoMatriz([p[0], p[1], p[2], 1], matriz);
        obj.eixos[i] = [resultado[0], resultado[1], resultado[2]];
      }
    }
  }

  // aplicar transformação no objeto selecionado

  function transladar(tx, ty, tz) {
    const obj = objetos[objetoSelecionado];
    aplicarTransformacao(obj, matrizTranslacao(tx, ty, tz));
  }

  // Calcula o centroide (centro geométrico) do objeto
  function calcularCentroide(obj) {
    let cx = 0, cy = 0, cz = 0;
    const n = obj.pontos.length;
    for (let i = 0; i < n; i++) {
      cx += obj.pontos[i][0];
      cy += obj.pontos[i][1];
      cz += obj.pontos[i][2];
    }
    return [cx / n, cy / n, cz / n];
  }

  function rotacionar(eixo, graus) {
    let mRot;
    if (eixo === 'x') mRot = matrizRotacaoX(graus);
    else if (eixo === 'y') mRot = matrizRotacaoY(graus);
    else if (eixo === 'z') mRot = matrizRotacaoZ(graus);
    const obj = objetos[objetoSelecionado];

    // Transladar o objeto para a origem, rotacionar, e voltar
    const c = calcularCentroide(obj);
    const mParaOrigem = matrizTranslacao(-c[0], -c[1], -c[2]);
    const mDeVolta = matrizTranslacao(c[0], c[1], c[2]);

    // Concatenar: T(-c) * R * T(c)
    let mFinal = mParaOrigem;
    mFinal = multiplicarMatrizes(mFinal, mRot);
    mFinal = multiplicarMatrizes(mFinal, mDeVolta);

    aplicarTransformacao(obj, mFinal);
  }

  function escalonar(sx, sy, sz) {
    const obj = objetos[objetoSelecionado];

    // Transladar o objeto para a origem, escalar, e voltar
    const c = calcularCentroide(obj);
    const mParaOrigem = matrizTranslacao(-c[0], -c[1], -c[2]);
    const mDeVolta = matrizTranslacao(c[0], c[1], c[2]);

    // Concatenar: T(-c) * S * T(c)
    let mFinal = mParaOrigem;
    mFinal = multiplicarMatrizes(mFinal, matrizEscala(sx, sy, sz));
    mFinal = multiplicarMatrizes(mFinal, mDeVolta);

    aplicarTransformacao(obj, mFinal);
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
      translacao: [0, 0, 0],
      // [Origem, X, Y, Z] em coordenadas locais para desenhar o eixo do objeto
      eixos: [
        [0, 0, 0],
        [10, 0, 0],
        [0, 10, 0],
        [0, 0, 10]
      ]
    };
  }

  // adicionar uma face ao objeto
  // vertices = array de índices (base 0, sentido anti-horário)
  // cor = [r, g, b] valores reais de 0 a 1
  function adicionarFace(obj, vertices, cor) {
    obj.faces.push({
      vertices: vertices,
      cor: cor,
      zMedio: 0,
      normal: [0, 0, 0],
      visivel: true
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
        zMedio: f.zMedio,
        normal: [f.normal[0], f.normal[1], f.normal[2]],
        visivel: f.visivel
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
      console.log('  F' + i + ': vértices=[' + f.vertices.join(', ') + '] cor=(' + f.cor[0] + ', ' + f.cor[1] + ', ' + f.cor[2] + ') zMedio=' + f.zMedio + ' normal=(' + f.normal.join(', ') + ') visivel=' + f.visivel);
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

  // calcular a normal de cada face e testar visibilidade
  // produto vetorial de dois vetores da face -> normal
  // se nz > 0, ta virada pro observador
  function calcularNormaisFaces(obj) {
    for (let i = 0; i < obj.faces.length; i++) {
      const f = obj.faces[i];

      // pegar 3 vertices pra montar os vetores
      const p0 = obj.pontos[f.vertices[0]];
      const p1 = obj.pontos[f.vertices[1]];
      const p2 = obj.pontos[f.vertices[2]];

      // vetores das arestas
      const v1x = p1[0] - p0[0];
      const v1y = p1[1] - p0[1];
      const v1z = p1[2] - p0[2];

      const v2x = p2[0] - p0[0];
      const v2y = p2[1] - p0[1];
      const v2z = p2[2] - p0[2];

      // produto vetorial v1 x v2
      const nx = v1y * v2z - v1z * v2y;
      const ny = v1z * v2x - v1x * v2z;
      const nz = v1x * v2y - v1y * v2x;

      f.normal = [nx, ny, nz];
    }
  }

  // preenchimento de poligono por scan-line
  // recebe pontos 2D ja em coordenadas de tela e a cor como string rgb
  function preencherPoligono(pontos, cor) {
    const n = pontos.length; // numero de lados
    if (n < 3) return;

    // Scan line

    // Montar a tabela de lados
    // Ymin, Ymax, X para Ymin, 1/m por LADO
    const tabelaLados = [];

    for (let i = 0; i < n; i++) {
      const p0 = pontos[i];
      const p1 = pontos[(i + 1) % n]; // % n faz com que o último lado se conecte ao primeiro

      // Lados horizontais podem ser desconsiderados
      if (p0.y === p1.y) {
        continue;
      }

      let Ymin, Ymax, xParaYmin;
      if (p0.y < p1.y) {
        // p0 é o ponto inicial
        Ymin = p0.y;
        Ymax = p1.y;
        xParaYmin = p0.x;
      } else {
        // p1 é o ponto inicial
        Ymin = p1.y;
        Ymax = p0.y;
        xParaYmin = p1.x;
      }

      // 1/m = deltaX / deltaY
      const inversoM = (p1.x - p0.x) / (p1.y - p0.y);

      tabelaLados.push({
        Ymin: Ymin,
        Ymax: Ymax,
        xParaYmin: xParaYmin,
        inversoM: inversoM
      });
    }

    // limites Y do poligono
    let yMin = pontos[0].y;
    let yMax = pontos[0].y;
    for (let i = 1; i < n; i++) {
      if (pontos[i].y < yMin) yMin = pontos[i].y;
      if (pontos[i].y > yMax) yMax = pontos[i].y;
    }

    // varrer cada linha e pintar os spans
    ctx.fillStyle = cor;
    for (let yVarredura = yMin; yVarredura <= yMax; yVarredura++) {
      const intersecoes = [];

      for (let j = 0; j < tabelaLados.length; j++) {
        const lado = tabelaLados[j];

        if (yVarredura >= lado.Ymin && yVarredura < lado.Ymax) {
          const x = lado.inversoM * (yVarredura - lado.Ymin) + lado.xParaYmin;
          intersecoes.push(Math.round(x));
        }
      }

      // ordenar e pintar de par em par
      intersecoes.sort(function (a, b) { return a - b; });
      for (let k = 0; k < intersecoes.length - 1; k += 2) {
        ctx.fillRect(intersecoes[k], yVarredura, intersecoes[k + 1] - intersecoes[k] + 1, 1);
      }
    }
  }

  // loop de renderização
  function desenhar() {
    clear();

    // projetar pontos e calcular normais de todos os objetos
    const dadosObjetos = [];

    for (let idx = 0; idx < objetos.length; idx++) {
      const obj = objetos[idx];

      calcularZMedioFaces(obj);
      calcularNormaisFaces(obj);

      // projetar todos os pontos do objeto pra 2D
      const pontosProjetados = [];
      for (let i = 0; i < obj.pontos.length; i++) {
        const p = obj.pontos[i];
        const proj = projetar(p[0], p[1], p[2]);
        pontosProjetados.push(paraTela(proj[0], proj[1]));
      }

      dadosObjetos.push({
        obj: obj,
        idx: idx,
        pontos2d: pontosProjetados
      });
    }

    // juntar faces visiveis de todos os objetos numa lista so
    // visibilidade determinada pelo sentido dos vertices projetados na tela
    // (area com sinal negativo em coords de tela = face virada pra camera)
    const listaFaces = [];

    for (let d = 0; d < dadosObjetos.length; d++) {
      const dados = dadosObjetos[d];
      const obj = dados.obj;

      for (let i = 0; i < obj.faces.length; i++) {
        const f = obj.faces[i];

        // montar pontos 2D da face
        const pontosFace = [];
        for (let v = 0; v < f.vertices.length; v++) {
          pontosFace.push(dados.pontos2d[f.vertices[v]]);
        }

        // area com sinal (shoelace) pra checar orientação na tela
        let area2 = 0;
        for (let v = 0; v < pontosFace.length; v++) {
          const prox = (v + 1) % pontosFace.length;
          area2 += pontosFace[v].x * pontosFace[prox].y;
          area2 -= pontosFace[prox].x * pontosFace[v].y;
        }

        // area negativa em tela (Y invertido) = anti-horario no mundo = visivel
        f.visivel = (area2 < 0);
        if (!f.visivel) continue;

        listaFaces.push({
          face: f,
          objIdx: dados.idx,
          pontosFace: pontosFace
        });
      }
    }

    // ordenar por z medio (menor = mais longe, pintar primeiro)
    listaFaces.sort(function (a, b) {
      return a.face.zMedio - b.face.zMedio;
    });

    // algoritmo do pintor: pintar do mais longe pro mais perto
    for (let i = 0; i < listaFaces.length; i++) {
      const entrada = listaFaces[i];
      const f = entrada.face;
      const pontosFace = entrada.pontosFace;
      const estaSelecionado = (entrada.objIdx === objetoSelecionado);

      // Iluminação Local
      const intensidade = calcularIntensidadeLuz(f.normal);

      // Multiplicar a cor original RGB da face pela intensidade
      // C = r*R + g*G + b*B onde r,g,b são os coeficientes de mistura (intensidade luminosa)
      const r = Math.round(f.cor[0] * intensidade * 255);
      const g = Math.round(f.cor[1] * intensidade * 255);
      const b = Math.round(f.cor[2] * intensidade * 255);
      const corStr = 'rgb(' + r + ',' + g + ',' + b + ')';

      // preencher a face com scan-line (cor sombreada)
      preencherPoligono(pontosFace, corStr);

      // contorno por cima: vermelho se selecionado, preto se nao
      if (estaSelecionado) {
        ctx.fillStyle = styles.selecionado;
      } else {
        ctx.fillStyle = '#000';
      }
      for (let v = 0; v < pontosFace.length; v++) {
        const pA = pontosFace[v];
        const pB = pontosFace[(v + 1) % pontosFace.length];
        lineDDA(pA.x, pA.y, pB.x, pB.y);
      }
    }

    // Desenhar os eixos do sistema global (da origem 0,0,0)
    if (typeof desenharEixosSistema === 'function') {
      desenharEixosSistema(ctx, projetar, paraTela, lineDDA);
    }

    // Desenhar os eixos do objeto selecionado a partir de sua translação
    if (objetos.length > 0 && typeof desenharEixosObjeto === 'function') {
      desenharEixosObjeto(objetos[objetoSelecionado], ctx, projetar, paraTela, lineDDA);
    }

    // HUD e status
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
  const TRANSLACAO_STEP = 0.5;   // unidades do mundo
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

  // interação com o mouse (rotação livre)
  let isDragging = false;
  let lastMouseX = 0;
  let lastMouseY = 0;

  canvas.addEventListener('mousedown', (e) => {
    isDragging = true;
    lastMouseX = e.clientX;
    lastMouseY = e.clientY;
  });

  canvas.addEventListener('mousemove', (e) => {
    if (!isDragging || objetos.length === 0) return;

    const deltaX = e.clientX - lastMouseX;
    const deltaY = e.clientY - lastMouseY;

    // Sensibilidade do mouse
    const sensibilidade = 0.8;

    // Arrastar na horizontal roda o objeto no eixo Y
    if (Math.abs(deltaX) > 0) {
      rotacionar('y', deltaX * sensibilidade);
    }

    // Arrastar na vertical roda o objeto no eixo X
    if (Math.abs(deltaY) > 0) {
      rotacionar('x', deltaY * sensibilidade);
    }

    lastMouseX = e.clientX;
    lastMouseY = e.clientY;

    desenhar();
  });

  canvas.addEventListener('mouseup', () => {
    isDragging = false;
  });

  canvas.addEventListener('mouseleave', () => {
    isDragging = false;
  });

  // parser do figure.dat
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

      // Aplicar harmonia de cores
      // Escolhe um Matiz aleatório (0 a 360) com Saturação 80% e Luminosidade 50% (Me inspirei no adobe colors)
      const hBase = Math.floor(Math.random() * 360);
      aplicarHarmoniaCoresObj(obj, hBase, 80, 50, 'splitComplementary', novosObjetos.length);

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

  // Inicializa o tamanho da tela de forma certa ao carregar o arquivo
  redimensionarCanvas();

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
