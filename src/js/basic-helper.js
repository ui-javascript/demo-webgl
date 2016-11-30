/**
 * Created by Luo_0412 on 2016/11/23.
 */
// 统计函数
function initStats() {
    var stats = new Stats();
    stats.setMode(0); // 0: fps, 1: ms

    // Align top-left
    stats.domElement.style.position = 'absolute';
    stats.domElement.style.left = '0px';
    stats.domElement.style.top = '0px';

    $("#stats-output").append(stats.domElement);
    return stats;
}

// 初始化Scene
function initScene(scene) {
    scene = new THREE.Scene();
    return scene; // 暴露出去,给全局变量
}

// 初始化相机
function initCamera(camera, posX, posY, posZ) {
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);

    camera.position.x = posX;
    camera.position.y = posY;
    camera.position.z = posZ;
    camera.lookAt(new THREE.Vector3(10, 0, 0));
    return camera;
}

function initCameraEx(camera, posX, posY, posZ, lookX, lookY, lookZ) {
    camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);

    camera.position.x = posX;
    camera.position.y = posY;
    camera.position.z = posZ;
    camera.lookAt(new THREE.Vector3(lookX, lookY, lookZ));
    return camera;
}


// 初始化渲染器
function initRenderer(renderer) {
    renderer = new THREE.WebGLRenderer();
    renderer.setClearColor(0xEEEEEE, 1.0);
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = true;

    return renderer;
}

function initRendererEx(renderer, color, isShadowMapEnabled) {
    renderer = new THREE.WebGLRenderer();
    if(color === "black") {
        renderer.setClearColor(0x000000, 1.0);
    } else {
        renderer.setClearColor(0xEEEEEE, 1.0);
    }
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = isShadowMapEnabled;

    return renderer;
}

// 创建studio
// function initStudio() {
//     scene = initScene(scene);
//     camera = initCamera(camera);
//     renderer = initRenderer(renderer);
// }

// 初始化平面
function initPlane(plane) {
    var planeGeometry = new THREE.PlaneGeometry(60, 20, 1, 1);
    var planeMaterial = new THREE.MeshLambertMaterial({color: 0xffffff});
    plane = new THREE.Mesh(planeGeometry, planeMaterial);
    plane.receiveShadow = true;

    // rotate and position the plane
    plane.rotation.x = -0.5 * Math.PI;
    plane.position.x = 15;
    plane.position.y = 0;
    plane.position.z = 0;

    return plane;
}

// 初始化方块
function  initCube(cube) {
    var cubeGeometry = new THREE.CubeGeometry(4, 4, 4);
    var cubeMaterial = new THREE.MeshLambertMaterial({color: 0xff0000});
    cube = new THREE.Mesh(cubeGeometry, cubeMaterial);
    cube.castShadow = true;

    // position the cube
    cube.position.x = -4;
    cube.position.y = 3;
    cube.position.z = 0;
    return cube;
}

// 初始化球体
function initSphere(sphere) {
    var sphereGeometry = new THREE.SphereGeometry(4, 20, 20);
    var sphereMaterial = new THREE.MeshLambertMaterial({color: 0x7777ff});
    sphere = new THREE.Mesh(sphereGeometry, sphereMaterial);

    // position the sphere
    sphere.position.x = 20;
    sphere.position.y = 0;
    sphere.position.z = 2;
    sphere.castShadow = true;

    return sphere;
}

function initLight(light, type, color) {
    switch(type) {
        case "a":
            light = new THREE.AmbientLight(color);
            break;
        case "s":
            light = new THREE.SpotLight(0xffffff);
            light.position.set(-40, 60, -10);
            light.castShadow = true;
            break;
    }

    return light;
}

