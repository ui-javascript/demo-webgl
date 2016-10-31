### 纹理
+ 凹凸贴图和法线贴图  添加深度和细节 后者更细致
+ 光照贴图 假阴影 静态场景
+ 环境贴图 材质上的反光细节
    + 创建一个CubeMap对象 6个纹理的集合
    + 创建一个带有这个CubeMap对象的方块
    + 将CubeMap作为纹理
+ 高光贴图 让网格的某些部分变得光亮 
+ 修改网格的UV贴图 对贴图进行微调
+ HTML5画布和视频元素作为纹理输入

### 纹理的用法
+ 定义网格的颜色
+ 高光 + 凹凸 + 反光

### 注意
+ 最好使用正方形图片 ∵mipmap
+ 256 x 256, 512 x 512, 1024 x 1024
+ 等待纹理加载完成
```
texture = THREE.ImageUtils.loadTexture('texture.png', {},
0020function() { renderer.render(scene); }); // ??
```
+ magFilter LinearFilter
+ minFilter LinearMipMapLinearFilter
+ [关于UV贴图](http://stackoverflow.com/questions/15137695/three-js-lightmap-causes-an-error-webglrenderingcontext-gl-error-gl-invalid-op)
+ 计算环境反光特别耗费CPU 光线追踪法 
+ [环境贴图示例图片来源](http://www.humus.name/index.php?page=Textures)
+ 最好的效果往往是用低光亮度实现的
+ 高光贴图还会受到光照的影响

### 纹理的高级用途
+ 定制UV映射 指定哪一部分显示在物体表面
+ [literally库](http://literallycanvas.com/) 创建交互式的画布
+ [Perlin噪音](https://github.com/wwwtyro/perlin.js)
+ 图片加载是异步的  渲染循环 回调函数
+ 纹理的repeat属性  包裹属性 ClampToEdgeWrapping → RepeatWrapping

### 后期处理
+ 