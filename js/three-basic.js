function setBasic(camera, webGLRenderer) {
    webGLRenderer.setClearColor(0x000, 1.0);
    webGLRenderer.setSize(window.innerWidth, window.innerHeight);
    webGLRenderer.shadowMapEnabled = true; // 允许捕捉阴影

    // position and point the camera to the center of the scene
    camera.position.x = 100;
    camera.position.y = 100;
    camera.position.z = 300;
    camera.lookAt(new THREE.Vector3(0, 0, 0));
}

function initStats() {
    var stats = new Stats();
    stats.setMode(0); // 0: fps, 1: ms

    // Align top-left
    // 设置统计块位置
    stats.domElement.style.position = 'absolute';
    stats.domElement.style.left = '0px';
    stats.domElement.style.top = '0px';

    $("#Stats-output").append(stats.domElement);
    return stats;
}