/**
 * 设置相机和渲染器的常用参数
 * @param camera
 * @param webGLRenderer
 */
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

/**
 * 设置统计条的常用参数
 * @returns {Stats}
 */
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

/**
 * 设置相机参数
 * @param camera
 * @param x
 * @param y
 * @param z
 */
function setCamaraPara(scene, camera, x, y, z) {
    camera.position.x = x;
    camera.position.y = y;
    camera.position.z = z;
    camera.lookAt(scene.position);
}

/**
 * 设置渲染器常用参数
 * @param renderer
 * @param isShadowMapEnabled
 */
function  setWebGLRendererPara(renderer, isShadowMapEnabled) {
    renderer.setClearColor(0xEEEEEE);  //  设置背景色
    renderer.setSize(window.innerWidth, window.innerHeight);
    renderer.shadowMapEnabled = isShadowMapEnabled; // 允许捕捉阴影,阴影计算耗费大量资源，默认关闭
}

/**
 * 设置平面的常用参数
 * @param scene
 * @param plane
 * @param mType
 * @param isReceiveShadow
 */
function setPlanePara(scene, plane, mType, isReceiveShadow) {
    var planeGeometry = new THREE.PlaneGeometry(60,20);
    if(mType === "basic" || mType === "b") {
        var planeMaterial = new THREE.MeshBasicMaterial({color: 0xcccccc});
    } else if(mType === "lambert" || mType === "l"){
        var planeMaterial =    new THREE.MeshLambertMaterial({color: 0xffffff});
    }

    plane = new THREE.Mesh(planeGeometry,planeMaterial);
    plane.receiveShadow  = isReceiveShadow;  // 是否允许生成阴影

    plane.rotation.x=-0.5*Math.PI; // 平面往负方向旋转90度
    plane.position.x= 15;
    plane.position.y= 0;
    plane.position.z= 0;
    scene.add(plane); // 添加至场景
}

/**
 * 设置正方体常用参数
 * @param scene
 * @param cube
 * @param len
 * @param mType
 * @param isCastShadow
 */
function addCubePara(scene, cube, len, mType, isCastShadow) {
    var cubeGeometry = new THREE.CubeGeometry(len, len, len);
    if(mType === "basic" || mType === "b") {
        var cubeMaterial = new THREE.MeshBasicMaterial({color: 0xff0000, wireframe: true});
    } else if(mType === "lambert" || mType === "l"){
        var cubeMaterial = new THREE.MeshLambertMaterial({color: 0xff0000});
    }

    cube = new THREE.Mesh(cubeGeometry, cubeMaterial);

    cube.castShadow = isCastShadow;  // 允许生成阴影

    cube.position.x=-4;
    cube.position.y=3;
    cube.position.z=0;
    scene.add(cube);
}

/**
 * 设置球体的常用参数
 * @param scene
 * @param sphere
 * @param len
 * @param mType
 * @param isCastShadow
 */
function addSpherePara(scene, sphere, len, mType, isCastShadow) {
    var sphereGeometry = new THREE.SphereGeometry(4,20,20);
    if(mType === "basic" || mType === "b") {
        var sphereMaterial = new THREE.MeshBasicMaterial({color: 0x7777ff, wireframe: true});
    } else if(mType === "lambert" || mType === "l"){
        var sphereMaterial = new THREE.MeshLambertMaterial({color: 0x7777ff});
    }

    sphere = new THREE.Mesh(sphereGeometry,sphereMaterial);
    sphere.castShadow = isCastShadow;  // 允许生成阴影

    sphere.position.x=20;
    sphere.position.y=4;
    sphere.position.z=2;
    scene.add(sphere);
}

function addSpotLight(scene, spotLight, isCastShadow) {
    spotLight = new THREE.SpotLight( 0xffffff );
    spotLight.position.set( -40, 60, -10);
    spotLight.castShadow = isCastShadow; // 不是所有的光源都可以产生阴影
    scene.add(spotLight);
}


