###  IE支持webGL
+   Google Chrome Frame
+   [iewebgl](http://iewebgl/com/)

###  编辑器
+   WebStrom支持git
+   [c9.io](http://c9.io)

###  服务器
+   Python  -- Unix/Mac
+   Node.js+NPM -- HTTP Server
+   Mongoose -- Mac/Windows移植  推荐

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
![](https://github.com/luo0412/luo-webGL-threeJS/raw/master/notebook/light-type.jpg)
+  AmbientLight  
    + 整体光  不需要制定位置
    + 不影响阴影生成   
    + 用于弱化阴影或添加颜色
    + 用色要保守
+  


###  THREE.Color对象
+ setRGB(r,g,b)
Sets the value of this color based on the supplied RGB
values. The values range from 0 to 1.
+ setHSV(h,s,v)
Sets the value of this color based on the supplied HSV
values. The values range from 0 to 1.
+ setStyle(style)
Sets the value of this color based on a CSS color.
+ copy(color)
Copies the color values from the provided color to this
color.
+ copyGammaToLinear(color)
Mostly used internally:
Sets the color of this object based on the supplied
color. The color is first converted from the gamma
color space to the linear color space. The gamma color
space also uses RGB values, but uses an exponential
scale instead of a linear one.
+ copyLinearToGamma(color)
Mostly used internally:
Sets the color of this object based on the supplied
color. The color is first converted from the linear color
space to the gamma color space.
+ convertGammaToLinear()
Converts the current color from the gamma color
space to the linear color space.
+ convertLinearToGamma()
Converts the current color from the linear color space
to the gamma color space.
+ getHex()
Returns the value from this color object as a number.
+ getHexString()
Returns the value from this color object as a hex string.
+ getStyle()
Returns the value from this color object as a CSS-based
value.
+ getHSV()
Returns the value from this color object as a HSV
value.
+ add(color)
Adds the supplied color to the current color.
+ addColors(color1, color2)
Mostly used internally:
Adds the supplied colors to the current color.
+ addScalar(s)
Mostly used internally:
Adds a value to the RGB components of the current
color.
+ multiply(color)
Mostly used internally:
Multiplies the current color by the supplied color.
+ multiplyScalar(s)
Mostly used internally:
Multiplies the light by the supplied value.
+ lerp(color, alpha)
Mostly used internally:
Finds the color that is between the color of this
object and the supplied color. The resulting color is
multiplied by the supplied alpha value.
+ clone()
Creates an exact copy of this color.
