window.addEventListener('DOMContentLoaded', () => {
  const canvas = document.getElementById('screen');
  const ctx = canvas.getContext('2d');
  const screen = {
    width: canvas.width,
    height: canvas.height,
    pixelSize: 1
  }
  const styles = {
    background: '#ffffff',
    primary: '#0c0a0a',
    cursor: '#ff0000'
  };

  let position = { x: 0, y: 0 };
  // Posição inicial: centro da tela)
  position.x = Math.floor(screen.width / 2) * screen.pixelSize;
  position.y = Math.floor(screen.height / 2) * screen.pixelSize;

  // Limpar (ou seja, pintar tudo de branco)
  function clear() {
    ctx.fillStyle = styles.background;
    ctx.fillRect(0, 0, screen.width, screen.height);
  }

  // Desenha (pintar de preto)
  function draw() {
    ctx.fillStyle = styles.primary;
    ctx.fillRect(position.x, position.y, screen.pixelSize, screen.pixelSize);
  }

  // Desenhar posição atual em vermelho
  function pointer() {
    ctx.fillStyle = styles.cursor;
    ctx.fillRect(position.x, position.y, screen.pixelSize, screen.pixelSize);
  }

  // Move o quadrado e desenha
  function move(dx, dy) {
    draw();
    position.x = Math.max(0, Math.min(screen.width - screen.pixelSize, position.x + dx * screen.pixelSize));
    position.y = Math.max(0, Math.min(screen.height - screen.pixelSize, position.y + dy * screen.pixelSize));
    pointer();
  }

  // INIT
  clear();
  pointer();
  canvas.focus();

  // Teclas
  document.addEventListener('keydown', (e) => {
    const tecla = e.key;

    switch (tecla) {
      case 'w': case 'W': case '8':
        move(0, -1);
        break;
      case 's': case 'S': case '2':
        move(0, 1);
        break;
      case 'a': case 'A': case '4':
        move(-1, 0);
        break;
      case 'd': case 'D': case '6':
        move    (1, 0);
        break;
      case 'x': case 'X': case '5':
        clear();
        pointer();
        break;
      case 'Escape': {
        let seconds = 3;
        const msg = document.createElement('p');
        const updateMessage = () => {
          msg.textContent = `Aplicação encerrada. Recarregando em ${seconds}...`;
        };        
        document.body.innerHTML = '';
        document.body.appendChild(msg);

        updateMessage();

        const timer = setInterval(() => {
          seconds--;
          seconds <= 0 ? msg.textContent = 'Recarregando.....' : updateMessage();
          seconds > 0 ? updateMessage() : (clearInterval(timer), window.location.reload());
        }, 1000);
        break;
      }
      default:
        // Ignorar outras teclas
        return; 
    }
  });
});