import * as THREE from 'three';

window.runThreeJSBenchmark = (gerador, limite = 1000) => {
  const container = document.getElementById('containerThree');
  document.getElementById('canvas2d').style.display = 'none';
  document.getElementById('canvasWebGL').style.display = 'none';
  container.style.display = 'block';

  // Inicializa o renderer 1 vez para não criar múltiplos canvas e estourar memória
  if (!window.threeRenderer) {
    window.threeRenderer = new THREE.WebGLRenderer({ antialias: false });
    window.threeRenderer.setSize(500, 500);
    window.threeRenderer.setClearColor(0xffffff, 1);
    container.appendChild(window.threeRenderer.domElement);
  }
  const renderer = window.threeRenderer;

  const scene = new THREE.Scene();

  // Câmera ortográfica do THREE mapeando top-left(0,0) para bottom-right(500,500)
  const camera = new THREE.OrthographicCamera(0, 500, 0, 500, 0.1, 100);
  camera.top = 0;
  camera.bottom = 500;
  camera.left = 0;
  camera.right = 500;
  camera.updateProjectionMatrix();

  camera.position.z = 10;

  // desliga o clear automatico para que mostre todos na tela
  renderer.autoClear = false;
  // limpa tudo no início antes recursão
  renderer.clear();

  const start = performance.now();
  for (let step = 0; step < limite; step++) {
    const { pontos, centroid } = gerador();
    const n = pontos.length;

    // Triangulação nativa (formato de estrela)
    const vertices = [];
    for (let i = 0; i < n; i++) {
      const pAtual = pontos[i];
      const pProx = pontos[(i + 1) % n];

      vertices.push(pProx.x, pProx.y, 0);
      vertices.push(pAtual.x, pAtual.y, 0);
      vertices.push(centroid.x, centroid.y, 0);
    }

    const geometry = new THREE.BufferGeometry();
    geometry.setAttribute('position', new THREE.Float32BufferAttribute(vertices, 3));
    const material = new THREE.MeshBasicMaterial({ color: 0xffff00 }); // Amarelo
    const mesh = new THREE.Mesh(geometry, material);
    scene.add(mesh);

    // Contorno Preto usando o LineLoop do Three.js
    const outlineGeometry = new THREE.BufferGeometry();
    const outlinePts = [];
    for (let i = 0; i < n; i++) {
      outlinePts.push(pontos[i].x, pontos[i].y, 0);
    }
    outlineGeometry.setAttribute('position', new THREE.Float32BufferAttribute(outlinePts, 3));
    const outlineMaterial = new THREE.LineBasicMaterial({ color: 0x000000 });
    const line = new THREE.LineLoop(outlineGeometry, outlineMaterial);
    scene.add(line);

    // Renderiza essa "fatia" na tela sobrepondo o que já estava lá
    renderer.render(scene, camera);

    // Remove da cena e descarta para não gerar lentidão contínua crescendo o grafo
    scene.remove(mesh);
    scene.remove(line);
    geometry.dispose();
    material.dispose();
    outlineGeometry.dispose();
    outlineMaterial.dispose();
  }
  const end = performance.now();
  return end - start;

};
