=======
# Modeling
三维模型显示平台 目前支持以下功能：<br>
-------
1.模型 移动、旋转、缩放 对应 f3 f4 f5<br> 
2.视图 移动、旋转、缩放 对应 f1 f2 f3<br>
3.支持常用三维模型的读入<br>
* vcc
* Collada ( .dae )
* Blender 3D ( .blend )
* 3ds Max 3DS ( .3ds )
* 3ds Max ASE ( .ase )
* Wavefront Object ( .obj )
* Industry Foundation Classes (IFC/Step) ( .ifc )
* XGL ( .xgl,.zgl )
* Stanford Polygon Library ( .ply )
* *AutoCAD DXF ( .dxf )
* LightWave ( .lwo )
* LightWave Scene ( .lws )
* Modo ( .lxo )
* Stereolithography ( .stl )
* DirectX X ( .x )
* AC3D ( .ac )
* Milkshape 3D ( .ms3d )
* TrueSpace ( .cob,.scn )Biovision BVH ( .bvh )
* CharacterStudio Motion ( .csm )Ogre XML ( .xml )
* Irrlicht Mesh ( .irrmesh )
* Irrlicht Scene ( .irr )
* Quake I ( .mdl )
* Quake II ( .md2 )
* Quake III Mesh ( .md3 )
* Quake III Map/BSP ( .pk3 )
* Return to Castle Wolfenstein ( .mdc )
* Doom 3 ( .md5* )
* Valve Model ( .smd,.vta )
* Starcraft II M3 ( .m3 )
* Unreal ( .3d )BlitzBasic 3D ( .b3d )
* Quick3D ( .q3d,.q3s )
* Neutral File Format ( .nff )
* Sense8 WorldToolKit ( .nff )
* Object File Format ( .off )
* PovRAY Raw ( .raw )
* Terragen Terrain ( .ter )
* 3D GameStudio (3DGS) ( .mdl )
* 3D GameStudio (3DGS) Terrain ( .hmp )
* Izware Nendo ( .ndo )
4.允许一个三维模型里有很多的part<br>
5.支持模型拾取，选中模型会显示包围盒<br>
6.三种网格显示方式 实体显示、点显示、线显示 以及它们的组合显示<br>

还需要做的：
-------
目前这个三维模型管理平台，仅仅使用GLUT本身的功能，GLUT本省并不提供UI操作，因此交互不太好。UI方面考虑使用MFC或者QT，MFC 较熟悉，但还是感觉很难用，考虑使用QT进行做UI整合进来。

使用须知：
-------
这个工程是在windows平台VS2010下进行编译的，使用了opengl的GLUT库，以及模型导入库Open Asset Import Library<br>
使用的时候下载这个工程到本地，用VS2010或更高版本打开.vcxproj 工程文件，并配置好GLUT和assimp库文件跟头文件即可正常使用<br>
使用git下载命令：<br>
```Bash
git clone https://github.com/niewenchao/Modeling
```

