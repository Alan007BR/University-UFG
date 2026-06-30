// arquivo com funções para desenhar elementos extras, eixos, cores etc...

// Desenha o eixo do sistema mundial (origem 0, 0, 0)
function desenharEixosSistema(ctx, projetar, paraTela, lineDDA) {
  const tamanho = 20; // tamanho da linha do eixo

  const origem = paraTela(...projetar(0, 0, 0));

  // Pontos finais dos eixos X, Y e Z
  const xEnd = paraTela(...projetar(tamanho, 0, 0));
  const yEnd = paraTela(...projetar(0, tamanho, 0));
  const zEnd = paraTela(...projetar(0, 0, tamanho));

  // Função auxiliar
  function desenharLinhaColorida(p1, p2, cor, label) {
    ctx.fillStyle = cor;
    lineDDA(p1.x, p1.y, p2.x, p2.y);

    ctx.fillRect(p2.x - 2, p2.y - 2, 4, 4); // quadrado na ponta

    ctx.font = '12px Poppins, sans-serif';
    ctx.fillText(label, p2.x + 5, p2.y + 5);
  }

  // Cores: X=Vermelho, Y=Verde, Z=Azul
  desenharLinhaColorida(origem, xEnd, '#ff3333', 'X');
  desenharLinhaColorida(origem, yEnd, '#33ff33', 'Y');
  desenharLinhaColorida(origem, zEnd, '#3333ff', 'Z');
}

// Desenha o eixo local de um objeto específico, acompanhando as transformações
function desenharEixosObjeto(obj, ctx, projetar, paraTela, lineDDA) {
  // Garantir que o objeto tenha a estrutura de eixos
  if (!obj.eixos) return;

  // A origem local projetada na tela (ponto 0 dos eixos)
  const origemLocal = obj.eixos[0];
  const origem = paraTela(...projetar(origemLocal[0], origemLocal[1], origemLocal[2]));

  // Eixos projetados na tela
  const xLocal = obj.eixos[1];
  const xEnd = paraTela(...projetar(xLocal[0], xLocal[1], xLocal[2]));

  const yLocal = obj.eixos[2];
  const yEnd = paraTela(...projetar(yLocal[0], yLocal[1], yLocal[2]));

  const zLocal = obj.eixos[3];
  const zEnd = paraTela(...projetar(zLocal[0], zLocal[1], zLocal[2]));

  function desenharLinhaColorida(p1, p2, cor, label) {
    ctx.fillStyle = cor;
    lineDDA(p1.x, p1.y, p2.x, p2.y);

    ctx.font = '10px Poppins, sans-serif';
    ctx.fillText(label, p2.x + 3, p2.y + 3);
  }

  // Cores um pouco diferentes/mais claras para os eixos do objeto
  desenharLinhaColorida(origem, xEnd, '#ff8888', 'x');
  desenharLinhaColorida(origem, yEnd, '#88ff88', 'y');
  desenharLinhaColorida(origem, zEnd, '#8888ff', 'z');
}

//Harmonia de Cores

// Converte HSL (Matiz: 0-360, Saturação: 0-100, Luminosidade: 0-100)
// para RGB em floats de 0 a 1 (para o script principal)
function hslToRgb(h, s, l) {
  s /= 100;
  l /= 100;
  const k = n => (n + h / 30) % 12;
  const a = s * Math.min(l, 1 - l);
  const f = n => l - a * Math.max(-1, Math.min(k(n) - 3, Math.min(9 - k(n), 1)));
  return [f(0), f(8), f(4)];
}

function complementary(h, s, l) {
  return [
    { h, s, l },                        // base
    { h: (h + 180) % 360, s, l }        // complementar
  ];
}

function splitComplementary(h, s, l) {
  return [
    { h, s, l },
    { h: (h + 150) % 360, s, l },
    { h: (h + 210) % 360, s, l }
  ];
}

// Aplica uma harmonia de cor nas faces do objeto (todas as faces com a mesma cor)
// indexObjeto ajuda a escolher qual cor da paleta este objeto vai receber
// Me inspirei no adobe colors https://color.adobe.com/br/create/color-wheel
function aplicarHarmoniaCoresObj(obj, h, s, l, tipo = 'splitComplementary', indexObjeto = 0) {
  let paleta = [];

  if (tipo === 'complementary') {
    paleta = complementary(h, s, l);
  } else if (tipo === 'splitComplementary') {
    paleta = splitComplementary(h, s, l);
  } else {
    paleta = [{ h, s, l }];
  }

  // Converte a paleta pra floats [r, g, b]
  const rgbPaleta = paleta.map(cor => hslToRgb(cor.h, cor.s, cor.l));

  // Escolhe uma única cor da paleta baseada no índice do objeto
  const rgb = rgbPaleta[indexObjeto % rgbPaleta.length];

  // Aplica a mesma cor para TODAS as faces deste objeto
  for (let i = 0; i < obj.faces.length; i++) {
    obj.faces[i].cor = [rgb[0], rgb[1], rgb[2]];
  }
}

// ILUMINAÇÃO LOCAL
// Vetor de luz direcional L, direção de onde a luz vem
// cima-direita-frente para a cena
const vetorLuz = [0.5, 0.8, 0.6];

// Luz ambiente mínima, para que as faces não iluminadas não fiquem totalmente pretas
const luzAmbiente = 0.15;

// Calcula a intensidade da iluminação local para uma face
// Produto escalar entre a normal da face (n) e o vetor de luz (L)
// n · L = |n|*|L|* cos(b)
// Se cos(b) ≈ 1 → luz batendo de frente → reflexo forte
// Se cos(b) ≈ 0 → luz batendo de lado → sombra
function calcularIntensidadeLuz(normal) {
  // Produto escalar n · L
  const dot = normal[0] * vetorLuz[0] + normal[1] * vetorLuz[1] + normal[2] * vetorLuz[2];

  // modulo (magnitude) do vetor normal
  const magN = Math.sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);

  // Módulo do vetor de luz
  const magL = Math.sqrt(vetorLuz[0] * vetorLuz[0] + vetorLuz[1] * vetorLuz[1] + vetorLuz[2] * vetorLuz[2]);

  // evitar divisão por zero
  if (magN < 0.0001 || magL < 0.0001) return luzAmbiente;

  // cos(b) = (n·L)/(|n|*|L|)
  const cosB = dot / (magN * magL);

  // Clampar entre 0 e 1 (valores negativos significam face oposta à luz)
  const intensidade = Math.max(0, cosB);

  // Combinar luz ambiente + luz direcional
  // garante que a intensidade final fique entre luzAmbiente e 1
  return Math.min(1, luzAmbiente + (1 - luzAmbiente) * intensidade);
}
