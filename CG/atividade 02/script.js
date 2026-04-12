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
  primary: '#0c0a0a',
  cursor: '#ff0000'
};

let running = true;
let timer = null;

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

function drawCircle(xc, yc, x, y) {
  draw(xc + x, yc + y);
  draw(xc - x, yc + y);
  draw(xc + x, yc - y);
  draw(xc - x, yc - y);
  draw(xc + y, yc + x);
  draw(xc - y, yc + x);
  draw(xc + y, yc - x);
  draw(xc - y, yc - x);
}

// alternativa analitica usando a equação da reta, para comparação de resultados
function lineAnalytic(x0, y0, x1, y1) {
ctx.fillStyle = styles.primary;

// Caso especial: se a reta for vertical
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

// algoritmo DDA (Digital Differential Analyzer)
function lineDDA(x0, y0, x1, y1) {
  let dx = x1 - x0;
  let dy = y1 - y0;

  let steps;

  if(Math.abs(dx) > Math.abs(dy)) {
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

  for(let i=0; i<=steps; i++) {
    draw(Math.round(x), Math.round(y));
    x += xIncrement;
    y += yIncrement;
  }

}

function circBrasenham(xc, yc, r) {
let x = 0;
let y = r;

let di = 3 - (2 * r);

while (x <= y) {
  drawCircle(xc, yc, x, y);

  if (di < 0) {
    di = di + (4 * x) + 6;
  } else {
    y = y - 1;
    di = di + (4 * (x - y)) + 10;
  }

  x++;
}
}

function drawRandom() {
  if (!running) {
    return;
  }

  const color = randomColor();
  const drawLine = Math.random() < 0.5; // 50% de chance cada

  styles.primary = color;
  ctx.fillStyle = styles.primary;

  if (drawLine) {
    const x0 = randomInt(0, screen.width);
    const y0 = randomInt(0, screen.height);
    const x1 = randomInt(0, screen.width);
    const y1 = randomInt(0, screen.height);
    lineDDA(x0, y0, x1, y1);
    status.textContent = `Linha DDA: (${x0}, ${y0}) -> (${x1}, ${y1}), cor ${color}`;
    return;
  } else {
  const maxRadius = Math.floor(Math.min(screen.width, screen.height) / 4);
  const r = randomInt(5, maxRadius);
  const xc = randomInt(r, screen.width - r);
  const yc = randomInt(r, screen.height - r);
  circBrasenham(xc, yc, r);
  status.textContent = `Bresenham: centro (${xc}, ${yc}) raio ${r}, cor ${color}`;
  }

}


function stopDrawing() {
  running = false;
  if (timer !== null) {
    clearInterval(timer);
    timer = null;
  }
  status.textContent = 'parado (ESC pressionado).';
}

clear();
timer = setInterval(drawRandom, 120);

document.addEventListener('keydown', (e) => {
  if (e.key === 'Escape') {
    stopDrawing();
  }
});

});