###  IE支持webGL
+   Google Chrome Frame
+   [iewebgl](http://iewebgl.com/)

###  编辑器
+   WebStrom支持git
+   [c9.io](http://c9.io)

###  服务器
+   Python  -- Unix/Mac
+   Node.js+NPM -- HTTP Server
+   Mongoose -- Mac/Windows移植  推荐
+ WebStrom对于(自己创建的域下)同名的文件会有本地保存，一直闹鬼的话浏览器手动清理下

###  三维对象
+   Plane   平面 
+   Cube    方块
+   Sphere  球体
+   Camera  相机     决定看到的输出结果 
+   Axes    轴       有助于调试

###  不推荐Canvas和SVG？
+   十分耗费CPU资源
+   缺乏某些功能：例支持复杂材质和阴影

###  一些与场景有关的函数
+  Scene.Add()
+  Scene.Remove()
+  Scene.children() 获取场景中所有子对象的列表
+  Scene.getChildByName()  

###  光的类型
+  AmbientLight  
    + 整体光  不需要指定位置
    + 不影响阴影生成   
    + 用于弱化阴影或添加颜色
    + 用色要保守
    ![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/light-type.jpg)
+  PointLight
    + 夜空中的照明弹
    + color intensity distance position visible
+  SpotLight
    +  最常用 锥形效果 手电筒
    +  属性
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/SpotLight-properties.jpg)
    +  exponent  光强以多快的速度从中心开始衰减
    +  高intensity + 高exponent
    +  小exponent + 小angle(角度太小渲染失真)
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/SpotLight-tip.jpg)
+  DirectinalLight
    +  太阳光 平行光 被方向光照亮的区域受到的光强是一样的
    +  包围对象的空间定义得越紧密，投影的效果越好
+  HemisphereLight 半球光光源
    +  室外 自然 
    +  替代方案：方向光来模拟太阳或环境光为场景提供基础色
    +  groundColor(地面发出的光线) Color(天空) intensity
+  AreaLight 平面光
    +  不在标准库中 改用THREE.WebGLDeferredRender 延迟渲染器

### 镜头眩光：朝着太阳拍照
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/LensFlare.jpg)


###  THREE.Color对象
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/THREE.Color-1.jpg)
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/THREE.Color-2.jpg)
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/MyNotes/images/THREE.Color-3.jpg)



