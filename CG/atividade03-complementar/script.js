window.addEventListener('DOMContentLoaded', () => {
  const canvas = document.getElementById('canvas2d');
  const ctx = canvas.getContext('2d');
  const status = document.getElementById('status');
  const pixelRage = document.getElementById('pixelSize');

  const btnManual = document.getElementById('btnManual');
  const btnWebGL = document.getElementById('btnWebGL');
  const btnThree = document.getElementById('btnThree');

  const screen = {
    width: canvas.width,
    height: canvas.height,
    pixelSize: 1
  };
  const styles = {
    background: '#FFF',
    primary: '#0c0a0a',
    cursor: '#ff0000'
  };

  // Limpar (pintar tudo de preto)
  function clear() {
    ctx.fillStyle = styles.background;
    ctx.fillRect(0, 0, screen.width, screen.height);
  }

  function randomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
  }

  function randomColor() {
    const r = Math.floor(Math.random() * 256).toString(16).padStart(2, '0');
    const g = Math.floor(Math.random() * 256).toString(16).padStart(2, '0');
    const b = Math.floor(Math.random() * 256).toString(16).padStart(2, '0');
    return `#${r}${g}${b}`;
  }

  function draw(x, y) {
    ctx.fillRect(x, y, screen.pixelSize, screen.pixelSize);
  }

  function lineAnalytic(x0, y0, x1, y1) {
    ctx.fillStyle = styles.primary;

    if (x0 === x1) {
      const yStart = Math.min(y0, y1);
      const yEnd = Math.max(y0, y1);

      for (let y = yStart; y <= yEnd; y++) {
        draw(x0, y);
      }
      return;
    }

    const m = (y1 - y0) / (x1 - x0);
    const b = y0 - m * x0;

    const xStart = Math.min(x0, x1);
    const xEnd = Math.max(x0, x1);

    for (let x = xStart; x <= xEnd; x++) {
      const y = m * x + b;
      draw(x, Math.round(y));
    }
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

  // Gerar polígonos
  function gerarPoligono() {
    // Sort numero de lados entre 3 e 10
    const n = randomInt(5, 10);

    // Margem para evitar pontos próximos da borda
    const margem = 15;

    // Sortear pares de coordenadas (x, y)
    const pontos = [];
    let cx = 0;
    let cy = 0;
    for (let i = 0; i < n; i++) {
      const x = randomInt(margem, screen.width - margem);
      const y = randomInt(margem, screen.height - margem);
      pontos.push({ x: x, y: y });
      cx += x;
      cy += y;
    }

    // antes dessa nova adição, os polígnos se cruzam estranhamente, a solução foi
    // geometricamente calcular os pontos médios
    // e depois ordenar os pontos por radianos em volta do centro
    cx = cx / n; // X Médio
    cy = cy / n; // Y Médio

    // Ordenar por radianos em volta do Centro
    pontos.sort((a, b) => {
      const anguloA = Math.atan2(a.y - cy, a.x - cx);
      const anguloB = Math.atan2(b.y - cy, b.x - cx);
      return anguloA - anguloB;
    });

    return { pontos, centroid: { x: cx, y: cy } };
  }

  // Desenhar e preencher o polígono com contorno
  function desenharPoligono(pontos, corContorno, corPreenchimento) {
    const n = pontos.length; // numero de lados

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

    // Interseção com a linha de varredura
    // algebra linear
    // limites
    let Ymin = screen.height;
    let Ymax = 0;

    for (let i = 0; i < pontos.length; i++) {
      if (pontos[i].y < Ymin) {
        Ymin = pontos[i].y;
      }
      if (pontos[i].y > Ymax) {
        Ymax = pontos[i].y;
      }
    }

    // Percorrer cada linha de varredura
    ctx.fillStyle = corPreenchimento;
    for (let Yvarredura = Ymin; Yvarredura <= Ymax; Yvarredura++) {
      const intersecoes = [];

      // Para cada lado, verificar se a linha de varredura intercepta
      for (let j = 0; j < tabelaLados.length; j++) {
        const lado = tabelaLados[j];

        // Ignorar se Yvarredura < Ymin || Yvarredura > Ymax
        if (Yvarredura >= lado.Ymin && Yvarredura < lado.Ymax) {
          // X = (1/m) * (Yvarredura - Ymin) + xParaYmin
          const x = lado.inversoM * (Yvarredura - lado.Ymin) + lado.xParaYmin;
          intersecoes.push(Math.round(x));
        }
      }

      // Ordenar interseções em ordem crescente e pintar
      intersecoes.sort(function (a, b) { return a - b; });
      for (let k = 0; k < intersecoes.length - 1; k += 2) {
        const xInicio = intersecoes[k];
        const xFim = intersecoes[k + 1];
        ctx.fillRect(xInicio, Yvarredura, xFim - xInicio + 1, 1);
      }
    }

    // Contorno do polígono usando DDA
    styles.primary = corContorno;
    ctx.fillStyle = styles.primary;
    for (let i = 0; i < n; i++) {
      const p0 = pontos[i];
      const p1 = pontos[(i + 1) % n];
      lineDDA(p0.x, p0.y, p1.x, p1.y);
    }
  }

  if (pixelRage) {
    pixelRage.addEventListener('input', () => {
      const valor = parseInt(pixelRage.value);
      screen.width = valor;
      screen.height = valor;
      canvas.width = valor;
      canvas.height = valor;
      console.log(valor);
      clear();
    })
  }

  clear();

  const manualRoutine = (limit = 1000) => {
    document.getElementById('containerThree').style.display = 'none';
    document.getElementById('canvasWebGL').style.display = 'none';
    canvas.style.display = 'block';

    clear();

    const start = performance.now();
    for (let i = 0; i < limit; i++) {
      const { pontos } = gerarPoligono();
      const corContorno = "#000000";
      const corPreenchimento = "#ffff00";
      desenharPoligono(pontos, corContorno, corPreenchimento);
    }
    const end = performance.now();
    return end - start;
  }

  const webGLRoutine = () => {
    if (window.runWebGLBenchmark) {
      const resultTime = window.runWebGLBenchmark(gerarPoligono, 1000);
      status.textContent = `[WEBGL] ${(resultTime).toFixed(3)} ms`;
    }
  }

  const threeJSRoutine = () => {
    if (window.runThreeJSBenchmark) {
      const resultTime = window.runThreeJSBenchmark(gerarPoligono, 1000);
      status.textContent = `[THREE] ${(resultTime).toFixed(3)} ms`;
    }
  }

  btnManual.addEventListener('click', (e) => {
    if (e.target === btnManual) {
      e.preventDefault();
      status.textContent = "Calculando Manual...";
      // Timeout para permitir que o navegador atualize o texto de "Calculando..."
      setTimeout(() => {
        const time = manualRoutine(1000);
        status.textContent = `[MANUAL] ${time.toFixed(3)} ms`;
      }, 10);
    }
  });

  btnWebGL.addEventListener('click', (e) => {
    if (e.target === btnWebGL) {
      e.preventDefault();
      webGLRoutine();
    }
  });

  btnThree.addEventListener('click', (e) => {
    if (e.target === btnThree) {
      e.preventDefault();
      threeJSRoutine();
    }
  });

});
