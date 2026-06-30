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
    background: '#fff',
    primary: '#000'
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

  // Valores de dt disponíveis
  const deltas = [0.1, 0.05, 0.01, 0.005, 0.001];
  let dtAtual = 0.001;

  // Bezier: P(t) = (1-t)²·B0 + 2·t·(1-t)·B1 + t²·B2
  function p(t, b0, b1, b2) {
    const u = 1 - t;
    return {
      x: (u * u) * b0.x + (2 * u * t) * b1.x + (t * t) * b2.x,
      y: (u * u) * b0.y + (2 * u * t) * b1.y + (t * t) * b2.y
    };
  }

  // Pontos de controle
  const B0 = { x: 50, y: 100 };
  let B1 = { x: 300, y: 50 };
  const B2 = { x: 550, y: 100 };

  // valores de B1 para experimentar
  // coloquei alguns extras por curiosidade
  const valoresB1 = [
    { x: 300, y: 50 },
    { x: 300, y: 150 },
    { x: 50, y: 150 },
    { x: 1, y: 150 },
    { x: 600, y: 50 },
    { x: 600, y: 400 },
    { x: 1, y: 400 },
    { x: 1, y: 100 },
    { x: 300, y: 300 },
    { x: 300, y: 100 }
  ];
  let indiceB1 = 0;

  function desenhar() {
    clear();

    // Desenhar curva de Bézier com dt atual
    ctx.fillStyle = styles.primary;
    let anterior = p(0, B0, B1, B2);

    for (let t = 0; t <= 1; t += dtAtual) {
      const atual = p(t, B0, B1, B2);
      lineDDA(anterior.x, anterior.y, atual.x, atual.y);
      anterior = atual;
    }

    // Garantir que o ponto final (t=1) seja alcançado
    const final_ = p(1, B0, B1, B2);
    lineDDA(anterior.x, anterior.y, final_.x, final_.y);

    // Desenhar pontos de controle em vermelho
    ctx.fillStyle = '#f00';
    ctx.fillRect(B0.x - 4 / 2, B0.y - 4 / 2, 4, 4);
    ctx.fillRect(B1.x - 4 / 2, B1.y - 4 / 2, 4, 4);
    ctx.fillRect(B2.x - 4 / 2, B2.y - 4 / 2, 4, 4);

    ctx.font = '12px';
    ctx.fillStyle = '#f00';
    ctx.fillText('B0', B0.x, B0.y - 10);
    ctx.fillText('B1', B1.x, B1.y - 10);
    ctx.fillText('B2', B2.x, B2.y - 10);

    // Info
    status.textContent = 'dt = ' + dtAtual + ' | B1 = <' + B1.x + ', ' + B1.y + '>';
  }

  // Controles por teclado
  document.addEventListener('keydown', (e) => {
    // Teclas 1-5: mudar dt
    if (e.key === '1') dtAtual = deltas[0]; // 0.1
    if (e.key === '2') dtAtual = deltas[1]; // 0.05
    if (e.key === '3') dtAtual = deltas[2]; // 0.01
    if (e.key === '4') dtAtual = deltas[3]; // 0.005
    if (e.key === '5') dtAtual = deltas[4]; // 0.001

    // Tecla B: ciclar entre valores de B1
    if (e.key === 'b' || e.key === 'B') {
      indiceB1 = (indiceB1 + 1) % valoresB1.length;
      B1 = valoresB1[indiceB1];
    }

    desenhar();
  });

  clear();
  desenhar();

});
