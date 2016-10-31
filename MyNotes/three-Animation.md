### 基础动画
+ 位置
+ 旋转
+ 缩放
+ [Tween.js](https://github.com/sole/tween.js/)

### 移动相机
+ 相机控件
    + 第一人称控件 FirstPersonControls
        + 
    + 飞行控件 FlyControls
        + 按住左键和中键 往前移动
        + 按住右键 往后移动
        + 移动鼠标 往四周看
        + W 往前移动
        + S 往后移动
        + A 左移
        + D 右
        + R 上
        + F 下
        + G 向左翻滚
        + E 向右翻滚
    + 翻滚控件 RollControls
        + 按住左键 往前移动
        + 按住右键 往后移动
        + W 前移
        + A 左移
        + S 后移
        + D 右移
        + Q 往左翻滚
        + E 往右翻滚
        + R 上移
        + F 下移
    + 轨迹球控件 最常用 TrackballControls
        + 右键平移 左键旋转翻滚相机 中键缩放
    + 轨道控件 模拟轨道中的卫星 OrbitControls
    + 路径控件 过山车... PathControls
        + 自定义路径 缓慢螺旋式上升
+ 

### 变形和蒙皮
+ 变形动画 定义几何体之间的过渡
    + MorphAnimMesh 变形动画网格
    + parseAnimations() playAnimation(name, fps)
+ 骨骼动画 骨骼和蒙皮技术处理过渡
    + 如何从Blender中较好的导出数据
    + SkinnedMesh 

### 加载外部动画
+ 带有JSON导出器的Blender
+ Collada模型
+ MD2模型 老雷神引擎使用的简单格式  保存角色动画的文件格式
    + [转化](http://oos.moxiecode.com/js_webgl/md2_converter/)

### Blender创建动画注意
+ 模型中的顶点至少要在一个顶点组中
+ Blender中顶点组的名字必须跟控制这个顶点组的骨头的名字相对应
+ 只有第一个action可以导出
+ 创建keyframes 关键帧名, 最好选择所有的骨头
+ 导出模型, 要保证模型处于静止状态。