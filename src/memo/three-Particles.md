### 粒子系统
+ 模拟雨滴和雪花
+ 三维效果
+ 使用CanvasRenderer 可以直接使用THREE.Particle对象
+ 使用WebGLRenderer 使用THREE.Sprite
+ 使用ParticleSystem类来显示 几何体 + 材质
    + 用来创建大量粒子
    + ParticleSystem:FrustrumCulled  落在相机可见范围外的粒子不被渲染 
+ ParticleCanvasMaterial canvas画布内容作为纹理
+ ParticleBasicMaterial 贴图

### 精灵 THREE.Sprite
+ HUD Head-Up display 平视显示器
    + 基于屏幕坐标移动，定位和移动的对象
    + 相当于蒙上一层
+ “广告牌” 总是面向镜头

### 注意点
+ 粒子来自于几何体的顶点
+ 三维建模工具
    + [Blender](https://www.blender.org/) 
        + blender导入three扩展
        + 自己作死 要先进user pre先激活
    + 3D Studio Max
+ 测试性的材质来检测, 用js控制台输出材质信息