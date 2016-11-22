###  材质
+ 网格基础材质 MeshBasicMaterial
+ 网格深度材质 MeshDepthMaterial 网格到相机的距离
    + 逐渐消失的效果
    + wireframe wireframeLinewidth
    + 设置cameraNear 
    + 设置cameraFar  超出可见距离看不见
+ 网格法向材质 MeshNormalMaterial
    + 决定光的反射方向
    + THREE.FlatShading 平面着色
    + THREE.SmoothShading 平滑着色
+ 网格面材质 MeshFaceMaterial
+ 网格朗伯材质 MeshLambertMaterial   光照 不光亮物体 
    + ambient 环境色
    + emissive 材质发射的颜色 不是光源 不受其他光照影响
+ 网格Phong式材质 MeshPhongMaterial  光照 光亮物体
    + ambient emissive
    + specular 镜面的 金属/塑料质感
    + shininess 高光部分的亮度
+ 着色器材质  ShaderMaterial 自定义 顶点
    + 属性...
    + [例子](https://www.shadertoy.com/view/4dXGR4)
+ 直线基础材质 LineBasicMaterial 直线几何体
+ 虚线材质 LineDashedMaterial 同上
    + 短划线长度
    + 短划线中间空格长度
    + 必须调用computeLineDistances()

### 材质属性
+ 基础属性
+ 融合属性 与背景的融合
+ 高级属性 控制底层webgl上下文渲染物体
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/light-type.jpg)

###  纹理
+ 二维高频细节
+ 几何建模限制
+ 环境纹理映射 Enviroment mapping
    + 环境包装盒和曲面法向之间的映射
+ 纹理空间 物体空间 纹理坐标 ==> 函数映射
+ 

### 材质
+ color = Normal
+ Normal = color 贴图

### UV工具 美工
+ 


