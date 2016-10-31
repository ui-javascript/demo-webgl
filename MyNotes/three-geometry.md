### 几何体
+ 平面 PlaneGeometry
    + 水平放置 将这个网格沿x轴向后旋转四分之一圈
    + mesh.rotation.x = -Math.PI/2;
+ 圆形 CircleGeometry
+ 塑形 ShapeGeometry
    + 自定义二维图形
    + shape对象和shapeGeometry
    + shape的辅助函数
+ 立方体 CubeGeometry
+ 球体 SphereGeometry
+ 圆柱 CylinderGeometry
+ 圆环 TorusGeometry
    + arc
+ 环面纽结 TorusKnotGeometry 
    + [wiki](http://en.wikipedia.org/wiki/Torus_knot)
    + p q
+ 多面体 PolyhedronGeometry
    + 多面体 = 平面 + 直边
    + vertices faces
    + radius detail
+ 二十面体 IcosahedronGeometry
+ 八面体 OctahedronGeometry
+ 四面体 TetraHedronGeometry

### 复杂几何体
+ 凸面体 ConvexGeometry
    + 凸包就是包围这组点的最小图形
+ 扫描面 LatheGeometry
+ 拉伸几何体 ExtrudeGeometry
+ 管状体 TubeGeometry
+ 参数几何体 ParametricGeometry
    + u v 越大越光滑
    + function 
    + slices  定义u分成多少份
    + stacks  定义v分成多少份
    + useTris 默认false四边形
    + 克莱因瓶 平面 3d莫比乌斯带...
+ 文本几何体 TextGeometry
    + 添加自定义字体
    + [typeface.js](http://typeface.neocracy.org/)提供的字体
    + TrueType/OpenType → js库

### 二元操作组合网格
+ THREE扩展库[THREEBSP](https://github.com/skalnik.ThreeBSP) 
+ coffee-script 咖啡脚本 更友好的js变体
+ 也可以不用已经编译好的js
```
<script type="text/coffeescript">
    onReady();
</script>

function onReady() { THREE.js code }
```
+ 使用未经组合的网格
+ intersect 相交
+ union 联合
+ subtract 相减


